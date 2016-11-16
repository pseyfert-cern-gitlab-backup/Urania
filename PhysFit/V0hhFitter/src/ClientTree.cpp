// Include files 
#include <iostream>
#include <sstream>
#include <algorithm>
#include <boost/algorithm/string.hpp>

//ROOT
#include "TString.h"
#include "TObjArray.h"

// local
#include "V0hhFitter/ClientTree.h"

using namespace V0hhFit;

//-----------------------------------------------------------------------------
// Implementation file for class : ClientTree
//
// 2012-09-27 : Edmund Smith (LHCb 2010) 
//-----------------------------------------------------------------------------

bool compareSubComponents(std::string l, std::string r)
{
	int posColon = l.find_last_of(":") + 1;
	int posLBrace = l.find_first_of("(");
	int toPos = posLBrace - posColon;

	std::string s = l.substr(posColon, toPos);

	if (r.find(s) == std::string::npos) return false;
	else return true;
}
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
ClientTree::ClientTree(  ) {
}

//=============================================================================
// Constructor with pointer to RooAbsArg.
//=============================================================================
ClientTree::ClientTree(RooAbsArg* thearg,
        std::vector<std::string> oldobjects)
{
	recursiveClientCheck(thearg,oldobjects);
	removeOrphanServers();
}


//first the versions of these functions using std::stringstreams
//see below for TString versions

//=============================================================================
//recursively places clients of the "var" given in m_TreeMap 
//goes all the way up the tree until the RooAbsArg has no more clients
//=============================================================================
void ClientTree::recursiveClientCheck(RooAbsArg* var,
				      std::vector<std::string> oldobjects,
				      int currentdisp)
{
	TIterator* iter = var->clientIterator();
	RooAbsArg* client;
	int thisdisp = currentdisp+1;

	while( (client=(RooAbsArg*)iter->Next()) ){

		if (m_TreeMap.find((std::string)client->GetName())==m_TreeMap.end()) {

			TIterator* serveriter = client->serverIterator();
			RooAbsArg* serverOfClient;
			std::stringstream serverList;

			while( (serverOfClient=(RooAbsArg*)serveriter->Next()) )
				serverList << serverOfClient->GetName() << ",";

			std::string serverstring = serverList.str();

			trim_right( serverstring, "," );

			//object names from the fitter that have already been modified, don't put these in the client tree
			if ( std::find( oldobjects.begin(), oldobjects.end(), client->GetName() ) == oldobjects.end() ){  
				m_TreeMap[ client->GetName() ] = std::pair<int,std::string> (thisdisp,serverstring);
			}

			delete serveriter;serveriter=0;
		}
		recursiveClientCheck(client,oldobjects,thisdisp);
	}  
	delete iter;
}

//=============================================================================
//Looks in the map and removes servers of the clients that are not amongst the 
//keys of the map and are therefore not affected by the change in dependency on
//the new var
//=============================================================================
void ClientTree::removeOrphanServers()
{
	typedef std::map<std::string,std::pair<int,std::string> >::iterator mapiter;
	typedef std::vector<std::string>::iterator stringiter;

	std::vector<std::string> argsinmap;

	for (mapiter iter = m_TreeMap.begin(); iter != m_TreeMap.end(); iter++){
		argsinmap.push_back(iter->first);
	}

	for (mapiter iter = m_TreeMap.begin(); iter != m_TreeMap.end(); iter++){
		std::vector<std::string> strs;
		split( strs, iter->second.second, "," );
		//boost::split(strs,,boost::is_any_of(","));

		std::stringstream importantservers;
		for (stringiter s = strs.begin(); s != strs.end(); s++){
			if (std::find(argsinmap.begin(),argsinmap.end(),*s) != argsinmap.end())
				importantservers << *s << ",";
		}
		std::string importantserverstring = importantservers.str();

		TString tname( importantserverstring.c_str() );
		if( tname.EndsWith(",") ) {
			tname.Remove( tname.kTrailing, ',' );
		}
		importantserverstring = tname.Data();
		m_TreeMap[iter->first].second = importantserverstring;
	}
}

//=============================================================================
//iterates over the tree of clients defined in the map altering all the 
//dependencies in turn such that dependency is transferred from var to newvar 
//and is propagated all the way up the tree
//returns a vector of strings to use as factory commands in the RooWorkspace
//=============================================================================
std::vector<std::string> ClientTree::clientReplace(RooAbsArg* var,
        RooAbsArg* newvar,
        Fitter& rsf)
{

	typedef std::map<std::string,std::pair<int,std::string> >::iterator mapiter;
	typedef std::vector<std::string>::iterator stringiter;

	std::vector<std::string> factoryCommands;

	int maxdepth = 1;
	for (mapiter iter = m_TreeMap.begin(); iter != m_TreeMap.end(); iter++){
		if (iter->second.first>maxdepth) maxdepth = iter->second.first;
	}

	for (int treedepth = 1; treedepth<=maxdepth; treedepth++){
		for (mapiter iter = m_TreeMap.begin(); iter != m_TreeMap.end(); iter++){
			//	bool fftConv(false);
			//	if(rsf.getWS()->arg(iter->first.c_str()) != NULL)
			//	  if (std::string(rsf.getWS()->arg(iter->first.c_str())->ClassName()) == "RooFFTConvPdf")
			//	    fftConv = true;

			//if the thing we try to replace is actually the newvar, don't do this
			//because we already do this below (this happens in the case of
			//blind variables, where the newvar is actually a function that depends on
			//the oldvar, can't think of any other way it would happen at the 
			//moment
			if (strcmp(iter->first.c_str(),newvar->GetName())==0) continue;

			if(iter->second.first==treedepth && treedepth==1){
				std::stringstream factoryCMD;
				factoryCMD << "EDIT::" << iter->first << "_new("
					<< iter->first << "," << var->GetName()
					<< "=" << newvar->GetName() << ")";
				factoryCommands.push_back(factoryCMD.str());
				//put this object in the vector of ones we have modified
				m_ModObjects.push_back(iter->first);

			}
			else if (iter->second.first==treedepth){ 
				std::stringstream factoryCMD;
				//		if (fftConv)
				//		  factoryCMD << "FFTCONV::";
				//		else
				factoryCMD << "EDIT::";
				factoryCMD << iter->first << "_new("
					<< iter->first << ",";        

				std::vector<std::string> mod_servers;
				split( mod_servers, iter->second.second, "," );
				// If it is the RooFFTConvPdf
				if ( std::string(rsf.getWS()->arg(iter->first.c_str())->ClassName()) == "RooFFTConvPdf" ) {
					factoryCMD << var->GetName() << "=" << newvar->GetName() << ",";
				}

				for (stringiter s = mod_servers.begin(); s != mod_servers.end(); s++){
					factoryCMD << *s << "=" << *s << "_new" << ((s==mod_servers.end()-1)?")":",");
				}
				factoryCommands.push_back(factoryCMD.str());

				//put this object in the vector of ones we have modified
				m_ModObjects.push_back(iter->first);

				//if the absarg that we are modifying is the model make sure that the m_modelname
				//is updated so that the fit is done over the whole model
				if (strcmp(rsf.getModelName(),iter->first.c_str())==0){
					//must declare a new char here to make sure it doesn't get
					//overwritten or lost later
					char* cstr = new char [(iter->first+"_new").size()+1];
					strcpy (cstr, (iter->first+"_new").c_str());
					rsf.setModelName(cstr);
				}
			}      
		}
	}

	std::sort(factoryCommands.begin(), factoryCommands.end(), compareSubComponents);
	return factoryCommands;
}


//=============================================================================
//Now the TString versions of these functions
//recursively places clients of the "var" given in the map provided
//goes all the way up the tree
//the int is the number of displacements from the initial var and the string is
//the servers of that client
//=============================================================================
void ClientTree::recursiveClientCheckTS(RooAbsArg* var,
        int currentdisp)
{
	TIterator* iter = var->clientIterator();
	RooAbsArg* client;
	int thisdisp = currentdisp+1;

	while( (client=(RooAbsArg*)iter->Next()) ){

		if (m_TreeMap.find((std::string)client->GetName())==m_TreeMap.end()) {

			TIterator* serveriter = client->serverIterator();
			RooAbsArg* serverOfClient;

			TString serverlist = "";

			while( (serverOfClient=(RooAbsArg*)serveriter->Next()) ){
				serverlist.Append(serverOfClient->GetName());
				serverlist.Append(",");
			}

			serverlist.Remove(TString::kTrailing,',');

			m_TreeMap[(std::string)client->GetName()] = std::pair<int,std::string> (thisdisp,(std::string)serverlist);

			delete serveriter;
		}
		recursiveClientCheckTS(client,thisdisp);
	}  
	delete iter;
}

//=============================================================================
//looks in the map and removes servers of the clients that are not amongst the keys of the map
//and are therefore not affected by the change in dependency on the new var
//=============================================================================
void ClientTree::removeOrphanServersTS()
{
	typedef std::map<std::string,std::pair<int,std::string> >::iterator mapiter;
	typedef std::vector<std::string>::iterator stringiter;

	std::vector<std::string> argsinmap;

	for (mapiter iter = m_TreeMap.begin(); iter != m_TreeMap.end(); iter++){
		argsinmap.push_back(iter->first);
	}

	for (mapiter iter = m_TreeMap.begin(); iter != m_TreeMap.end(); iter++){
		std::vector<std::string> strs;

		split( strs, iter->second.second, "," );
		//boost::split(strs,iter->second.second,boost::is_any_of(","));

		TString importantservers = "";
		for (stringiter s = strs.begin(); s != strs.end(); s++){
			if (std::find(argsinmap.begin(),argsinmap.end(),*s) != argsinmap.end()){
				importantservers.Append(s->c_str());
				importantservers.Append(",");
			}
		}
		importantservers.Remove(TString::kTrailing,',');
		m_TreeMap[iter->first].second = (std::string)importantservers;
	}
}

//=============================================================================
//iterates over the tree of clients defined in the map altering all the dependencies in turn
//such that dependency is transferred from var to newvar and is propagated all the way up
//the tree
//=============================================================================
std::vector<std::string> ClientTree::clientReplaceTS(RooAbsArg* var,
        RooAbsArg* newvar)
{

	typedef std::map<std::string,std::pair<int,std::string> >::iterator mapiter;
	typedef std::vector<std::string>::iterator stringiter;

	std::vector<std::string> factoryCommands;

	int maxdepth = 1;
	for (mapiter iter = m_TreeMap.begin(); iter != m_TreeMap.end(); iter++){
		if (iter->second.first>maxdepth) maxdepth = iter->second.first;
	}

	for (int treedepth = 1; treedepth<=maxdepth; treedepth++){
		for (mapiter iter = m_TreeMap.begin(); iter != m_TreeMap.end(); iter++){

			if(iter->second.first==treedepth && treedepth==1){

				TString factoryCMD = "";
				factoryCMD.Form("EDIT::%s_new(%s,%s=%s)",
						iter->first.c_str(),
						iter->first.c_str(),
						var->GetName(),
						newvar->GetName());

				factoryCommands.push_back((std::string)factoryCMD);
			}
			else if (iter->second.first==treedepth){

				TString factoryCMD = "";
				factoryCMD.Form("EDIT::%s_new(%s,",
						iter->first.c_str(),
						iter->first.c_str());

				//servers of this client that have already been modified
				//make sure the latest version is picked up in the factory command
				std::vector<std::string> mod_servers;
				split( mod_servers, iter->second.second, "," );

				for (stringiter s = mod_servers.begin(); s != mod_servers.end(); s++){
					factoryCMD.Append(s->c_str());
					factoryCMD.Append("=");
					factoryCMD.Append(s->c_str());
					factoryCMD.Append("_new");
					factoryCMD.Append(((s==mod_servers.end()-1)?")":","));
				}

				factoryCommands.push_back((std::string)factoryCMD);

				//if (strcmp(m_Fitter.GetModelName(),iter->first.c_str())==0){
				//  TString newmodelname = "";
				//  newmodelname.Form("%s_new",m_Fitter.GetModelName());
				//  m_Fitter.SetModelName(newmodelname.Data());
				//  
				//}
			}
		}
	}
	return factoryCommands;
}

//=============================================================================
// Get the vector of objects that this class has issued commands to modify
//=============================================================================
std::vector<std::string> ClientTree::getModifiedObjectNames()
{
    return m_ModObjects;
}


//=============================================================================
// Split a string by some delimiter.
//=============================================================================
void ClientTree::split( std::vector<std::string>& splitstring, std::string stringvalue, std::string c ) 
{
	TObjArray* tokens = TString( stringvalue ).Tokenize( c.c_str() );
	TIter iTokens( tokens );
	while ( TObjString* os  = dynamic_cast<TObjString*>(iTokens.Next()) ) {
		splitstring.push_back( os->GetString().Data() );
	}
}


//=============================================================================
// remove all right-side trailing characters labelled c
//=============================================================================
void ClientTree::trim_right( std::string& stringvalue, std::string c ) 
{
	TString tname = stringvalue;
	if( tname.EndsWith( c.c_str() ) ) {
		tname.Remove( tname.Length() - c.length(), c.length() );
	}
	stringvalue = tname.Data();
}


//=============================================================================
// remove all left-side leading characters labelled c
//============================================================================
void ClientTree::trim_left( std::string& stringvalue, std::string c )
{
    TString tname = stringvalue;
    if( tname.BeginsWith( c.c_str() ) ) {
        tname.Remove( 0, c.length() );
    }
    stringvalue = tname.Data();
}

//=============================================================================
// Destructor
//=============================================================================
ClientTree::~ClientTree() {} 

//=============================================================================

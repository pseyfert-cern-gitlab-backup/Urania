// $Id: $
// Include files
// C++ libraries
#include <sstream>
#include <iostream>
#include <algorithm>

// RooFit
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooArgSet.h"
#include "RooAbsPdf.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooArgList.h"
#include "RooPlot.h"
#include "RooCategory.h"
#include "RooFormulaVar.h"
#include "RooSimultaneous.h"
#include "RooFitResult.h"
#include "RooMCStudy.h"
#include "RooRandom.h"
#include "RooMinuit.h"
#include "RooUnblindPrecision.h"
#include "RooUnblindUniform.h"

// RooStats
//#include "RooStats/SPlot.h"

// ROOT 
#include "TChain.h"
#include "TRandom3.h"
#include "TPad.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TMath.h"
#include "TTreeFormula.h"
#include "TString.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TEntryList.h"
#include "TAxis.h"
#include "TPaveLabel.h"
#include "TH1F.h"

// local
#include "V0hhFitter/SimultaneousFitter.h"
#include "V0hhFitter/ClientTree.h"
#include "V0hhFitter/Exceptions.h"
#include "V0hhFitter/string_tools.h"
#include "V0hhFitter/SPlot.h"

//-----------------------------------------------------------------------------
// Implementation file for class : SimultaneousFitter
//
// 2012-08-21 : Edmund Smith (LHCB)
//-----------------------------------------------------------------------------

using V0hhFit::IOFailure;
using V0hhFit::TDirectoryError;
using V0hhFit::GeneralException;
using V0hhFit::WSImportFailure;
using V0hhFit::WSRetrievalFailure;
using namespace V0hhFit;
//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
SimultaneousFitter::SimultaneousFitter(  ) 
    : ModelBase(), m_NegYields( true )
{}

//=============================================================================
// Constructor with name and title.
//=============================================================================
SimultaneousFitter::SimultaneousFitter( const char* name, const char* title ) 
    : ModelBase(name, title), m_NegYields( true )
{}

//=============================================================================
// Create merged dataset inside the workspace, uses dataset names as indices
//=============================================================================
void SimultaneousFitter::combineDataSets()
{
    if (!m_rws) {
        throw GeneralException("SimultaneousFitter::combineDataSets",
                "No RooWorkspace object is defined.");
    } 
    if ((m_rws->allData()).size()==0){
        throw GeneralException("SimultaneousFitter::combineDataSets",
                "No dataset objects in RooWorkspace.");
    }  

    RooCategory cat(m_catSetName, "");
    std::list<RooAbsData*> datas = m_rws->allData();
    std::map<std::string,RooDataSet*> dset_map;
    int index = 0;

    for (std::list<RooAbsData*>::iterator i=datas.begin(); i!=datas.end(); ++i) {
        const char* thename = (*i)->GetName();
        if (cat.defineType(thename, index)) {
            std::stringstream msg;
            msg << "Failed to add category type " << thename << " to RooCategory.";
            throw GeneralException("SimultaneousFitter::combineDataSets", msg.str());
        }
        std::stringstream thelabel;
        thelabel << thename;
        dset_map[thelabel.str()] = dynamic_cast<RooDataSet*>( *i );
        index++;
    }

    RooRealVar* mass = m_rws->var( m_1DFitVarName );
    if (!mass) {
        throw WSRetrievalFailure("SimultaneousFitter::combineDataSets",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    RooArgSet vars(*mass);

    RooRealVar * weight;

    if (!std::string(m_weightVarName).empty()) {
        weight = new RooRealVar(m_weightVarName.c_str(), m_weightVarName.c_str(), -1.1, 10);
        vars.add(*weight);
    }

    //get the spectators (if there are any)
    const RooArgSet* extraArgs = m_rws->set(m_spectSetName);
    if (extraArgs){
        if (!vars.add(*extraArgs)){
            throw GeneralException("SimultaneousFitter::combineDataSets",
                    "Failed to add spectators to combined dataset.");
        }
    }

    RooDataSet * combdata;

    if (m_weightVarName.empty()) {
        combdata = new RooDataSet(m_dataSetName,"",vars,RooFit::Index(cat),RooFit::Import(dset_map));    
    } else {
        std::cout << "Fitting a dataset weighted by " << m_weightVarName << std::endl;
        combdata = new RooDataSet(m_dataSetName,"",vars,RooFit::Index(cat),RooFit::Import(dset_map), RooFit::WeightVar(m_weightVarName.c_str()));
    }

    if (m_rws->import(cat)) {
        throw WSImportFailure("SimultaneousFitter::combineDataSets", *m_rws, cat);
    }
    if (m_rws->import(*combdata)) {
        throw WSImportFailure("SimultaneousFitter::combineDataSets", *m_rws, *combdata);
    }

    delete combdata;
}
    

double SimultaneousFitter::sumYields() 
{

    if (!m_rws) {
        throw GeneralException("SimultaneousFitter::sumYields",
                "No RooWorkspace object is defined.");
    }

    // Get the mass variable
    RooRealVar* mass = m_rws->var( m_1DFitVarName );
    if (!mass) {
        throw WSRetrievalFailure("SimultaneousFitter::sumYields",
                *m_rws, m_1DFitVarName, "RooRealVar");    
    }

    //Get the stuff I need from the workspace
    RooSimultaneous* model = dynamic_cast<RooSimultaneous*>( m_rws->pdf( m_modelName ) );  
    if (!model)
    { 
        throw WSRetrievalFailure("SimultaneousFitter::sumYields"
                ,*m_rws, m_modelName, "RooSimultaneous"); 
    }


    RooCategory* cat = dynamic_cast<RooCategory*>( m_rws->cat( m_catSetName ) );
    if (!cat) {
        throw WSRetrievalFailure("SimultaneousFitter::sumYields",
                *m_rws, m_catSetName, "RooCategory");
    }

    // grab the expectect number of events.
    return model->expectedEvents( RooArgSet( *mass, *cat ) );

}

//=============================================================================
// Export all pdfs in the current fitter workspace to a workspace in a file
//=============================================================================

void SimultaneousFitter::exportAllPDFsToFile(const char* filename, const char* wsname)
{
    TFile * file = TFile::Open(filename, "UPDATE");

    if (!file){
        throw GeneralException("SimultaneousFitter::exportAllPDFsToFile",
                "File does not exist.");
    }

    TObject * tmpWS = file->Get(wsname);

    RooWorkspace * newWS;

    // If there isn't a workspace present with that name, create one

    if (tmpWS) {
        RooWorkspace * oldWS = dynamic_cast<RooWorkspace *>(tmpWS);
        newWS = new RooWorkspace(*oldWS);
    }
    else {
        newWS = new RooWorkspace(wsname);
    }

    RooArgSet pdfs = m_rws->allPdfs();

    if (newWS->import(pdfs,  RooFit::RecycleConflictNodes( kTRUE )) == kTRUE) {
        std::stringstream msg;
        msg << "Could not add pdfs to workspace " << wsname;
        throw GeneralException("SimultaneousFitter::exportAllPDFsToFile", msg.str());
    }

    newWS->Write();
    file->Close();

    delete newWS;
}

//=============================================================================
// Export a named pdf in the current fitter workspace to another
// workspace in a file
//=============================================================================

void SimultaneousFitter::exportPDFToFile(const char* filename, const char* wsname,
                                         const char* pdfname, const char* newname)
{
    TFile * file = TFile::Open(filename, "UPDATE");

    if (!file){
        throw GeneralException("SimultaneousFitter::exportPDFToFile",
                "File does not exist.");
    }

    TObject * tmpWS = file->Get(wsname);

    RooWorkspace * newWS;

    // If there isn't a workspace present with that name, create one

    if (tmpWS) {
        RooWorkspace * oldWS = dynamic_cast<RooWorkspace *>(tmpWS);
        newWS = new RooWorkspace(*oldWS);
    }
    else {
        newWS = new RooWorkspace(wsname);
    }

    RooAbsPdf * pdf = this->getPdf(pdfname);

    if (newname) pdf->SetName(newname);

    if (newWS->import(*pdf,  RooFit::RecycleConflictNodes( kTRUE )) == kTRUE) {
        std::stringstream msg;
        msg << "Could not add pdf " << pdfname << " to workspace " << wsname;
        throw GeneralException("SimultaneousFitter::exportPDFToFile", msg.str());
    }

    newWS->Write();
    file->Close();

    delete newWS;
}

//=============================================================================
//Import any RooAbsPdf from a file and put it in the workspace,
//must be saved within a RooWorkspace in in the input file
//optionally set all parameters of this pdf constant with
//setConstant flag.
//=============================================================================
void SimultaneousFitter::importPDFFromFile(const char* filename, const char* pdfname,
        const char* newname, const char* wsname,
        Bool_t setConstant)
{

    if (!m_rws) {
        throw GeneralException("SimultaneousFitter::importPDFFromFile",
                "No RooWorkspace object is defined.");
    }
    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("SimultaneousFitter:importPDFFromFile",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }
    TFile* theFile = new TFile(filename);
    if (!theFile){
        throw GeneralException("SimultaneousFitter::importPDFFromFile",
                "File does not exist.");
    }


    // check is there is a ModelName flag in the file, if it was, then we need
    // to check that this is the latest version of the pdf, i.e. no further "_new" terms.

    RooWorkspace* theWS = 0;
    RooAbsPdf* thePdf = 0;
    if (strcmp(wsname,"")!=0){
        theWS = dynamic_cast<RooWorkspace*>( theFile->Get( wsname ) );
        if (!theWS){
            std::stringstream msg;
            msg << "Workspace with name - " << wsname << " - does not exist within " << theFile->GetName();
            throw GeneralException("SimultaneousFitter::importPDFFromFile",msg.str());
        }
        thePdf = dynamic_cast<RooAbsPdf*>( theWS->pdf( pdfname ) );
        if ( !thePdf ) {
            std::stringstream msg;
            msg << "Pdf with name - " << pdfname << " - does not exist within " << wsname;
            throw GeneralException("SimultaneousFitter::importPDFFromFile",msg.str());
        }
    }
    else {
        thePdf = dynamic_cast<RooAbsPdf*>( theFile->Get( pdfname ) );
        if ( !thePdf ) {
            std::stringstream msg;
            msg << "Pdf with name - " << pdfname << " - does not exist within file " << theFile->GetName() << ".";
            throw GeneralException("SimultaneousFitter::importPDFFromFile", msg.str() );
        }
    }

    //check whether this pdf from the file is fit over a variable with the same name
    //as this fit, beta test....  
    RooArgSet* obs = thePdf->getObservables(RooArgSet(*mass));
    TIterator* obsIter = obs->createIterator();
    RooAbsArg* pdfObs = 0;

    while ( (pdfObs= dynamic_cast<RooAbsArg*>( obsIter->Next() ) ) ) {
        if (strcmp(pdfObs->GetName(),m_1DFitVarName)==0) break;
    }
    //if didn't find the B mass var throw exception
    if ( !pdfObs ) {
        std::stringstream msg;
        msg << "Did not find " << m_1DFitVarName << " in servers of " << pdfname << ".";
        throw GeneralException("SimultaneousFitter::importPDFFromFile",msg.str());
    }
    delete obsIter; obsIter=0;

    //set parameters constant
    //TIterator* serverIter = thePdf->serverIterator();
    TIterator* serverIter = thePdf->getParameters( RooArgSet( *mass ) )->createIterator();
    //RooAbsArg* pdfServer = 0;  
    RooRealVar* pdfServer = 0;  
    while ( (pdfServer= dynamic_cast<RooRealVar*>( serverIter->Next() ) ) ){
        if (setConstant) {

            //std::cout << "INFO:: setting parameter " << pdfServer->GetName() << " constant."<< std::endl;
            pdfServer->setConstant(kTRUE); 
        }
    }
    delete serverIter; serverIter=0;

    std::string pdfName_original = thePdf->GetName();
    thePdf->SetName(newname);
    // Checking parameter names
    TIterator* it_parsName = thePdf->getParameters( RooArgSet( *mass ) )->createIterator();
    RooRealVar* pdf_pars = 0;  
    std::string pdfName_new  = newname;
    std::string parName;
    while ( (pdf_pars= dynamic_cast<RooRealVar*>( it_parsName->Next() ) ) ){
        parName = pdf_pars->GetName();
        if (pdfName_new.find(parName) == std::string::npos) {
            m_stringHelper.replaceAll( parName, pdfName_original, pdfName_new );
            pdf_pars->SetName(parName.c_str()); 
        }
    }
    delete it_parsName; it_parsName = 0 ;
    if ( m_rws->import( *thePdf, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure( "SimultaneousFitter::importPDFFromFile",
                *m_rws, *thePdf );
    }

    delete theFile; theFile = 0;
}

//=============================================================================
//Import any RooRealvar from a file and put it in the workspace,
//must be saved within a RooWorkspace in in the input file
//=============================================================================
void SimultaneousFitter::importVarFromFile(const char* fileName, const char* varName,
        const char* newName, const char* wsName)
{

    if (!m_rws) {
        throw GeneralException("SimultaneousFitter::importVarFromFile",
                "No RooWorkspace object is defined.");
    }
    TFile* theFile = new TFile(fileName);
    if (!theFile){
        throw GeneralException("SimultaneousFitter::importVarFromFile",
                "File does not exist.");
    }

    // Check WS configuration
    RooWorkspace* theWS = 0;
    RooRealVar* theVar = 0;
    if (strcmp(wsName,"")!=0){
        theWS = dynamic_cast<RooWorkspace*>( theFile->Get( wsName ) );
        if (!theWS){
            std::stringstream msg;
            msg << "Workspace with name - " << wsName << " - does not exist within " << theFile->GetName();
            throw GeneralException("SimultaneousFitter::importVarFromFile",msg.str());
        }
        // Check whether the var Name exists
        theVar = dynamic_cast<RooRealVar*>( theWS->var( varName ) ); 
        if (!theVar) {
            std::stringstream msg;
            msg << "Variable with name - " << varName << " - does not exist within " << wsName;
            throw GeneralException("SimultaneousFitter::importVarFromFile",msg.str());
        }
    }
    else {
        // Check whether the var Name exists
        theVar = dynamic_cast<RooRealVar*>( theFile->Get( varName ) ); 
        if (!theVar) {
            std::stringstream msg;
            msg << "Variable with name - " << varName << " - does not exist within " << theFile->GetName() << ".";
            throw GeneralException("SimultaneousFitter::importVarFromFile",msg.str());
        }
    }

    // Updating name
    theVar->SetName(newName);

    if ( m_rws->import( *theVar, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure( "SimultaneousFitter::importVarFromFile",
                *m_rws, *theVar );
    }

    delete theFile; theFile = 0;
}

//=============================================================================
// Get value of a RooRealvar from a file  within the RooWorkspace
//=============================================================================
std::vector<Double_t> SimultaneousFitter::importVarValueFromFile(const char* fileName, const char* varName,
        const char* wsName)
{

    TFile* theFile = new TFile(fileName);
    if (!theFile){
        throw GeneralException("SimultaneousFitter::importVarFromFile",
                "File does not exist.");
    }

    // Check WS configuration
    RooWorkspace* theWS = 0;
    RooRealVar* theVar = 0;
    if (strcmp(wsName,"")!=0){
        theWS = dynamic_cast<RooWorkspace*>( theFile->Get( wsName ) );
        if (!theWS){
            std::stringstream msg;
            msg << "Workspace with name - " << wsName << " - does not exist within " << theFile->GetName();
            throw GeneralException("SimultaneousFitter::importVarFromFile",msg.str());
        }
        // Check whether the var Name exists
        theVar = dynamic_cast<RooRealVar*>( theWS->var( varName ) ); 
        if (!theVar) {
            std::stringstream msg;
            msg << "Variable with name - " << varName << " - does not exist within " << wsName;
            throw GeneralException("SimultaneousFitter::importVarFromFile",msg.str());
        }
    }
    else {
        // Check whether the var Name exists
        theVar = dynamic_cast<RooRealVar*>( theFile->Get( varName ) ); 
        if (!theVar) {
            std::stringstream msg;
            msg << "Variable with name - " << varName << " - does not exist within " << theFile->GetName() << ".";
            throw GeneralException("SimultaneousFitter::importVarFromFile",msg.str());
        }
    }

    std::vector<Double_t> varValues;
    varValues.push_back(theVar->getValV());
    varValues.push_back(theVar->getError());

    delete theFile; theFile = 0;

    return varValues;
}

//=============================================================================
// Creates the necessary named sets in the workspace for each pdf category
//=============================================================================
void SimultaneousFitter::createPDFSets()
{
    RooCategory* cat = m_rws->cat(m_catSetName);
    if (!cat) {
        throw WSRetrievalFailure("SimultaneousFitter:createPDFSets",
                *m_rws, m_catSetName, "RooCategory");
    }

    TIterator* iter = cat->typeIterator();
    RooCatType* t = 0;

    while ( (t= dynamic_cast<RooCatType*>( iter->Next() ) ) )
    {
        std::stringstream tname;
        tname << t->GetName() << "_Pdfs";
        m_rws->defineSet( tname.str().c_str(), "" );
    }
    delete iter; iter=0;
}

//=============================================================================
//Adds the comma separate list of pdfs to the named set corresponding to
//that category
//=============================================================================
void SimultaneousFitter::addPDFs(const char* categoryName, const char* pdfs)
{
    std::stringstream setName;
    setName << categoryName << "_Pdfs";
    if (m_rws->extendSet(setName.str().c_str(),pdfs)){
        std::stringstream msg;
        msg << "Failed to add PDFs: " << pdfs << " to named set " << setName.str() << ".";
        throw GeneralException("SimultaneousFitter::addPDFs",msg.str());
    }

}

//=============================================================================
//Add the variables to the workspace that will be used as yields for the 
//given category. Puts them in a named set.
//=============================================================================
void SimultaneousFitter::addYields(const char* categoryName)
{
    std::stringstream pdfSet;
    pdfSet << categoryName << "_Pdfs";

    const RooArgSet* thePdfs = m_rws->set(pdfSet.str().c_str());  
    if (!thePdfs){
        std::stringstream msg;
        msg << "Failed to add yields for pdfs: " << pdfSet << ", not present in workspace.";
        throw GeneralException("SimultaneousFitter::addYields",msg.str());
    }

    TIterator* iter = thePdfs->createIterator();
    TNamed* p = 0;

    //use this for contents string of named set of yields
    std::stringstream listOfYields;

    while ( (p = dynamic_cast<TNamed*>( iter->Next() ) ) )
    {
        std::stringstream yieldname;
        yieldname << p->GetName() << "_" << categoryName << "_Yield";

        //use the size of the dataset on the slice referred to by
        //categoryName to get the max size for the yield
        RooAbsData* data = m_rws->data(categoryName);
        if(!data){
            throw WSRetrievalFailure("SimultaneousFitter::addYields",
                    *m_rws, categoryName, "RooAbsData");
        }
        RooRealVar yield( yieldname.str().c_str(), "", data->numEntries()*0.8, 
                m_NegYields ? -data->numEntries()*5.0 : 0.0, 
                data->numEntries()*5.0, "" );

        if ( m_rws->import( yield ) ){
            throw WSImportFailure("SimultaneousFitter::addYields",
                    *m_rws, yield);
        }
        listOfYields << yieldname.str() << ",";

    }

    std::stringstream yieldSet;
    yieldSet << categoryName << "_Yields";

    if ( m_rws->defineSet( yieldSet.str().c_str(), listOfYields.str().c_str() ) ){
        std::stringstream msg;
        msg << "Failed to add yields: " << listOfYields.str() << " to named set " << yieldSet.str() << ".";
        throw GeneralException("SimultaneousFitter::addYields",msg.str() );
    }

    delete iter; iter=0;

}

//Set the option of allowing yields to fluctuate to negative values
void SimultaneousFitter::setNegativeYields(bool neg)
{
    m_NegYields = neg;
}


//=============================================================================
//Picks up the relevant named sets of pdfs and yields in each category and
//builds RooAddPdfs out of them.
//=============================================================================
void SimultaneousFitter::buildAddPdfs()
{
    //the RooCategory that has all the slices in it
    RooCategory* cat = m_rws->cat(m_catSetName);
    if (!cat) {
        throw WSRetrievalFailure("SimultaneousFitter:buildAddPdfs",
                *m_rws, m_catSetName, "RooCategory");
    }

    TIterator* iter = cat->typeIterator();
    RooCatType* t=0;

    while ( (t=dynamic_cast<RooCatType*>( iter->Next() ) ) )
    {
        std::stringstream tname, pdfSetName, yieldSetName;
        tname << t->GetName() << "_AddPdf";
        pdfSetName << t->GetName() << "_Pdfs";
        yieldSetName << t->GetName() << "_Yields";

        //getting the relevant RooArgSets of pdfs and yields
        //for this RooAddPdf    
        const RooArgSet* pdfSet = m_rws->set(pdfSetName.str().c_str());
        if (!pdfSet) {
            throw WSRetrievalFailure("SimultaneousFitter::buildAddPdfs",
                    *m_rws, pdfSetName.str().c_str(), "RooArgSet");
        }
        const RooArgSet* yieldSet = m_rws->set(yieldSetName.str().c_str());
        if (!yieldSet) {
            throw WSRetrievalFailure("SimultaneousFitter::buildAddPdfs",
                    *m_rws, yieldSetName.str().c_str(), "RooArgSet");
        }

        //RooAddPdf constructor takes RooArgLists, so need to convert taking care of the order,
        //making sure that the order of pdfs is the same as their yields
        RooArgList* pdfList = RooArgSet2List(pdfSet);    
        RooArgList yieldList;

        for (int i = 0; i<pdfList->getSize(); i++){
            std::stringstream yieldName;
            yieldName << pdfList->at(i)->GetName() << "_" << t->GetName() << "_Yield";

            RooAbsArg* arg = yieldSet->find(yieldName.str().c_str());
            if(!arg){
                std::stringstream msg;
                msg << "Yield " << yieldName.str() << " not found in " << yieldSetName.str();
                throw GeneralException("SimultaneousFitter::buildAddPdfs",msg.str());
            }

            yieldList.add( *( yieldSet->find( yieldName.str().c_str() ) ) );
        }

        RooAddPdf thesliceModel(tname.str().c_str(),tname.str().c_str(),*pdfList,yieldList);
        if ( m_rws->import( thesliceModel, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
            throw WSImportFailure("SimultaneousFitter::buildAddPdfs",
                    *m_rws, thesliceModel);
        }

	delete pdfList;
    }

    delete iter; iter = 0;

}

//=============================================================================
// Creates a RooSimultaneous object from all the RooAddPdfs that are in the
// workspace and have names that correspond to those in the category.
//=============================================================================
void SimultaneousFitter::buildModel()
{
    //the RooCategory that has all the slices in it
    RooCategory* cat = m_rws->cat(m_catSetName);
    if (!cat) {
        throw WSRetrievalFailure("SimultaneousFitter::createPDFSets",
                *m_rws, m_catSetName, "RooCategory");
    }

    // Construct a simultaneous pdf using the category as index
    RooSimultaneous simPdf( m_modelName, m_modelName, *cat);

    TIterator* iter = cat->typeIterator();
    RooCatType* t=0;

    while ( (t=dynamic_cast<RooCatType*>( iter->Next() ) ) )
    {
        std::stringstream slicePdfName;
        slicePdfName << t->GetName() << "_AddPdf";
        RooAbsPdf* theslicePdf;
        theslicePdf = m_rws->pdf(slicePdfName.str().c_str());
        if (!theslicePdf){
            throw WSRetrievalFailure("SimultaneousFitter::buildModel",
                    *m_rws, slicePdfName.str().c_str(), "RooAbsPdf");
        }

        //Associate pdfs with their slices in the category
        //and add them to the simulataneous pdf
        simPdf.addPdf(*theslicePdf,t->GetName());

    }

    if ( m_rws->import( simPdf, RooFit::RecycleConflictNodes( kTRUE ) ) ) {
        throw WSImportFailure("SimultaneousFitter::buildModel",
                *m_rws, simPdf);
    }

    delete iter; iter=0;
}

//=============================================================================
// Saves the plots of the mass distribution and the pull distrubution 
// will also apply a title axis
//=============================================================================
void SimultaneousFitter::plotPrettyMassAndPull( TString saveName, 
        std::string xtitle, TString slicename, std::string fitName, std::string scale ) 
{

    TCanvas *cBmass = new TCanvas("Simultaneous Fit B","Simultaneous Fit B", 1000, 800);
    cBmass->cd();    

    RooPlot* hresidual_match = this->plotFitPulls( get1DFitVarName(), slicename, fitName.c_str());
    RooPlot* mBframe = this->plotFitResults( get1DFitVarName(), slicename );

    if( !mBframe ) {
        throw GeneralException("plotPrettyMassAndPull()",
                "Cannot plot the mass disribution.");        
    }
    if( !hresidual_match ) {
        throw GeneralException("plotPrettyMassAndPull()",
                "Cannot plot the pull disribution.");
    }

    double r = 0.2;
    double sr = 1. / r;

    TAxis* xAxis = hresidual_match->GetXaxis();
    xAxis->SetTickLength ( sr * xAxis->GetTickLength()  );
    xAxis->SetLabelSize  ( sr * xAxis->GetLabelSize()   );
    xAxis->SetTitleSize  ( 0                            );
    xAxis->SetLabelOffset( sr * xAxis->GetLabelOffset() );

    TAxis* yAxis = hresidual_match->GetYaxis();
    yAxis->SetNdivisions ( 504                          );
    yAxis->SetLabelSize  ( sr * yAxis->GetLabelSize()   );

    cBmass->Divide( 1, 2, .1, .1 );
    mBframe->GetXaxis()->SetLabelSize(0);
    mBframe->GetXaxis()->SetTitleOffset(0.68);
    //mBframe->GetYaxis()->SetTitleOffset(1.0);

    r  = .25;
    double sl = 1. / ( 1. - r );
    mBframe->GetYaxis()->SetLabelSize(sl * mBframe->GetYaxis()->GetLabelSize());
    mBframe->GetXaxis()->SetTitle( xtitle.c_str() );
    TString ytitle = mBframe->GetYaxis()->GetTitle();
    ytitle.ReplaceAll("Events", "Candidates");
    mBframe->GetYaxis()->SetTitle(ytitle);
    //  double labelSize = 0.2;
    hresidual_match->GetXaxis()->SetLabelSize((1./(1.+r)) * hresidual_match->GetXaxis()->GetLabelSize());
    hresidual_match->GetYaxis()->SetLabelSize((1./(1.+r)) * hresidual_match->GetYaxis()->GetLabelSize());
    TPad* padHisto_match = dynamic_cast<TPad*>( cBmass->cd(1) );
    TPad* padResid_match = dynamic_cast<TPad*>( cBmass->cd(2) );
    double smmatch = 0.1;
    padHisto_match->SetPad( 0., r , 1., 1. );
    padHisto_match->SetBottomMargin( smmatch );
    padResid_match->SetPad( 0., 0., 1., r  );
    padResid_match->SetBottomMargin( 0.3  );
    padResid_match->SetTopMargin   ( smmatch );
    padHisto_match->cd();
    mBframe->Draw();
    //if (mFitOptions->isConstant("plotLegend")) plotLegend(mBframe,catname);
    padResid_match->cd();
    hresidual_match->GetYaxis()->SetLabelSize(0.18); 
    hresidual_match->Draw();
    if ( scale != "log") {
        cBmass->Print( saveName+".eps" );
        cBmass->Print( saveName+".pdf" );
        cBmass->Print( saveName+".png" );
    } else {
        padHisto_match->cd();
        padHisto_match->SetLogy( kTRUE );
        mBframe->SetMinimum( 3.e-1 );
        mBframe->SetMaximum( mBframe->GetMaximum()*1.2 );
        cBmass->Print( saveName+"_log.eps" );
        cBmass->Print( saveName+"_log.pdf" );
        cBmass->Print( saveName+"_log.png" );
    }
    cBmass->Clear();

    delete hresidual_match; hresidual_match = 0;
    delete mBframe; mBframe = 0;
    delete cBmass; cBmass = 0;
}

//=============================================================================
// Saves the plots of the mass distribution and the pull distribution 
// User case : MC mass fits 
//=============================================================================
void SimultaneousFitter::plotMassAndPull( TString saveName, 
        std::string xtitle, TString slicename, std::string fitName, std::string scale ) 
{

    TCanvas *cBmass = new TCanvas("Simultaneous Fit B","Simultaneous Fit B", 1000, 800);
    cBmass->cd();    
    RooPlot* hresidual_match = this->plotFitPulls( get1DFitVarName(), slicename.Data(), fitName.c_str());
    RooPlot* mBframe = this->plotFitResults( get1DFitVarName(), slicename.Data(), fitName.c_str() );

    if( !mBframe ) {
        throw GeneralException("plotMassAndPull()",
                "Cannot plot the mass disribution.");        
    }
    if( !hresidual_match ) {
        throw GeneralException("plotMassAndPull()",
                "Cannot plot the pull disribution.");
    }

    double r = 0.2;
    double sr = 1. / r;

    TAxis* xAxis = hresidual_match->GetXaxis();
    xAxis->SetTickLength ( sr * xAxis->GetTickLength()  );
    xAxis->SetLabelSize  ( sr * xAxis->GetLabelSize()   );
    xAxis->SetTitleSize  ( 0                            );
    xAxis->SetLabelOffset( sr * xAxis->GetLabelOffset() );
    xAxis->SetTitleOffset(1.0);

    TAxis* yAxis = hresidual_match->GetYaxis();
    yAxis->SetNdivisions ( 504                          );
    yAxis->SetLabelSize  ( sr * yAxis->GetLabelSize()   );

    cBmass->Divide( 1, 2, .1, .1 );
    mBframe->GetXaxis()->SetLabelSize(0);
    mBframe->GetXaxis()->SetTitleOffset(0.65);

    r  = .25;
    double sl = 1. / ( 1. - r );
    mBframe->GetYaxis()->SetLabelSize(sl * mBframe->GetYaxis()->GetLabelSize());
    mBframe->GetXaxis()->SetTitle( "" );
    TString ytitle = mBframe->GetYaxis()->GetTitle();
    ytitle.ReplaceAll("Events", "Candidates");
    mBframe->GetYaxis()->SetTitle(ytitle);
    hresidual_match->GetXaxis()->SetLabelSize((1./(1.+r)) * hresidual_match->GetXaxis()->GetLabelSize());
    hresidual_match->GetYaxis()->SetLabelSize((1./(1.+r)) * hresidual_match->GetYaxis()->GetLabelSize());
    TPad* padHisto_match = dynamic_cast<TPad*>( cBmass->cd(1) );
    TPad* padResid_match = dynamic_cast<TPad*>( cBmass->cd(2) );
    double smmatch = 0.042;
    padHisto_match->SetPad( 0., r , 1., 1. );
    padHisto_match->SetBottomMargin( smmatch );
    padResid_match->SetPad( 0., 0., 1., r  );
    padResid_match->SetBottomMargin( 0.3  );
    padResid_match->SetTopMargin   ( smmatch );
    padHisto_match->cd();

    mBframe->Draw();
    padResid_match->cd();
    hresidual_match->GetYaxis()->SetLabelSize(0.18); 
    hresidual_match->SetMaximum( 5.0 );
    hresidual_match->SetMinimum( -5.0 );
    hresidual_match->GetXaxis()->SetTitle( xtitle.c_str() );
    hresidual_match->Draw();
    if ( scale != "log") {
        cBmass->Print( saveName+".eps" );
        cBmass->Print( saveName+".pdf" );
        cBmass->Print( saveName+".png" );
    } else {
        padHisto_match->cd();
        padHisto_match->SetLogy( kTRUE );
        mBframe->SetMinimum( 3e-1 );
        mBframe->SetMaximum( mBframe->GetMaximum()*1.2 );
        cBmass->Print( saveName+"_log.eps" );
        cBmass->Print( saveName+"_log.pdf" );
        cBmass->Print( saveName+"_log.png" );
    }
    cBmass->Clear();

    delete hresidual_match; hresidual_match = 0;
    delete mBframe; mBframe = 0;
    delete cBmass; cBmass = 0;
}

//=============================================================================
// Saves the plots of the mass distribution - User case : data mass fits 
//=============================================================================
void SimultaneousFitter::plotMass( TString saveName, 
        std::string xtitle, TString slicename, std::string scale ) 
{

    TCanvas *cBmass = new TCanvas("Simultaneous Fit B","Simultaneous Fit B", 1000, 800);
    cBmass->cd();    

    RooPlot* mBframe = this->plotFitResults( get1DFitVarName(), slicename );

    if( !mBframe ) {
        throw GeneralException("plotMass()",
                "Cannot plot the mass disribution.");        
    }

    mBframe->GetXaxis()->SetTitleOffset(1.1);
    //mBframe->GetYaxis()->SetTitleOffset(1.1);
    mBframe->GetXaxis()->SetTitle( xtitle.c_str() );
    TString ytitle = mBframe->GetYaxis()->GetTitle();
    ytitle.ReplaceAll("Events", "Candidates");
    mBframe->GetYaxis()->SetTitle(ytitle);

    TPad* padHisto_match = dynamic_cast<TPad*>( cBmass->cd(1) );
    mBframe->Draw();
    if ( scale != "log") {
        cBmass->Print( saveName+".eps" );
        cBmass->Print( saveName+".pdf" );
    } else {
        padHisto_match->SetLogy( kTRUE );
        mBframe->SetMinimum( 3.e-1 );
        mBframe->SetMaximum( mBframe->GetMaximum()*1.4 );
        //mBframe->SetMaximum( mBframe->GetMaximum()*1.2 );
        mBframe->Draw();
        cBmass->Draw();
        cBmass->Print( saveName+"_log.eps" );
        cBmass->Print( saveName+"_log.pdf" );
    }

    cBmass->Clear();

    delete mBframe; mBframe = 0;
    delete cBmass; cBmass = 0;
}

//-----------------------------------------------------------------------------
// calculate SWeights (Note that newName is only used when the RooDataSet
// is cloned). To use the current values for the fit parameters
// (instead of loading a snapshot), specify an empty string
// If no newName is specified, then the dataset with wrights will be called
// {origName}_withWeights, where {origName} is the name of the input dataset
//-----------------------------------------------------------------------------
void SimultaneousFitter::calculateSWeights(const char* fitName,
										   const char* sliceName,
										   bool saveCfactors)
{
    if (!m_rws)
    {
        throw GeneralException("SimultaneousFitter::calculateSWeights",
                "No RooWorkspace object is defined!");
    }

    //only get the dataset corresponding to the slice not sure if this is correct
    //thing to do yet
	//    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );//( sliceName ) );
	std::string cut = "Categories==Categories::"+std::string(sliceName);
    RooDataSet* rds = (RooDataSet*) (dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) ))->reduce(cut.c_str());
    if (!rds)
        throw WSRetrievalFailure("SimultaneousFitter::calculateSWeights"
                ,*m_rws, m_dataSetName, "RooDataSet");

    RooSimultaneous* model = dynamic_cast<RooSimultaneous*>( m_rws->pdf( m_modelName ) );
    if (!model)
        throw WSRetrievalFailure("SimultaneousFitter::calculateSWeights"
								 ,*m_rws, m_modelName, "RooSimultaneous");

    //sorting out the components
    RooAddPdf* theslice = dynamic_cast<RooAddPdf*>(model->getPdf(sliceName));
    if (!theslice)
    {
        std::stringstream msg;
        msg << "Failed to get RooAddPdf for slice -  " << sliceName << ".";
        throw GeneralException("SimultaneousFitter::calculateSWeights",msg.str());
    }

    // make a copy of the RooAddPdf (otherwise sPlots does not work)
	RooAddPdf* modelClone = dynamic_cast<RooAddPdf*>( theslice->cloneTree() );
    const RooArgList yields = modelClone->coefList();
	RooArgList fixedYields;
	TIterator *f_iter = yields.createIterator();
    RooRealVar* f_arg = NULL;
	while ((f_arg = (RooRealVar*) f_iter->Next()) != NULL)
		if (f_arg->isConstant())
			fixedYields.add(*f_arg);

    if (fitName&&strcmp(fitName,"")!=0)
		{
			std::cout << "INFO: Loading snapshot " << fitName << std::endl;
			if (!m_rws->loadSnapshot(fitName))
				{
					throw WSRetrievalFailure("SimultaneousFitter::calculateSWeights",
											 *m_rws, fitName, "fit snapshot");
				}
		}
	
    TString weightedName=sliceName;
    weightedName.Append("_withSWeights");

    // create sPlot object
    std::cout << "Constructing sWeights..." << std::endl;
    RooStats::SPlot* splot = new RooStats::SPlot("sPlot", "An sPlot",
												 *rds, modelClone,
												 yields, fixedYields, RooArgSet(),
												 kTRUE, kTRUE,
												 weightedName.Data());
    RooDataSet* rds_withWeights=splot->GetSDataSet();

    if (!rds_withWeights)
        throw GeneralException("SimultaneousFitter::calculateSWeights",
                "No dataset with sWeight variables returned by sPlot object!");

	//	Get the c(i)'s.
	if (saveCfactors && fixedYields.getSize() != 0)
		{
			std::cout << "INFO: Calculating the c(i) factors for fixed yields" << std::endl;
			RooArgList *cFactors = new RooArgList(splot->GetSWeightCoefs());
			for (unsigned int i = 0 ; i < cFactors->getSize() ; i++)
				this->getWS()->import(*(new RooRealVar(*((RooRealVar*) &(*cFactors)[i]))));
		}
    std::cout << "Checking SWeights:" << std::endl;
    RooRealVar *arg=0;
    TIterator *iter = yields.createIterator();
    assert(iter);
    while ( (arg = dynamic_cast<RooRealVar*>( iter->Next() ) ) )
		{
			std::cout << "Yield " << arg->GetName()
					  << " = " << arg->getVal()
					  << " . From sWeights it is "
					  << (splot->GetYieldFromSWeight(arg->GetName())+splot->GetSWeightCoef(arg->GetName()))
					  << " . " << std::endl;
		}
    delete iter;iter=0;
	if( m_rws->import( *rds_withWeights ) )
	    {
	        throw WSImportFailure("SimultaneousFitter::calculateSWeights",
								  *m_rws, *rds_withWeights);
	    }
	RooArgSet weights( splot->GetSWeightVars() );
	if (weights.getSize()<1) {
		std::stringstream msg;
		msg << "Failed to get RooArgSet of sWeight variables";
		throw GeneralException("SimultaneousFitter::calculateSWeights",
							   msg.str());
	}
	
	if (m_rws->defineSet(m_sWeightVarSetName, weights ) )
		throw WSImportFailure("SimultaneousFitter::calculateSWeights",
							  *m_rws, weights, m_sWeightVarSetName);

    // replace current name with weighted dataset
	delete modelClone; modelClone=0;
	delete splot; splot=0;
}

//=============================================================================
// Calculates the ci of nuisance species
//=============================================================================

double SimultaneousFitter::calculateSPlotFactors(const char * sliceName, const char * signalYieldName, bool createVar)
{
	//Prepare the global items: dataset, model, slice
    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( sliceName ) );
    if (!rds)
		{
			throw WSRetrievalFailure("SimultaneousFitter::calculateSPlotFactors"
									 ,*m_rws, m_dataSetName, "RooDataSet");
		}
    RooSimultaneous* model = dynamic_cast<RooSimultaneous*>( m_rws->pdf( m_modelName ) );
    if (!model)
		{
			throw WSRetrievalFailure("SimultaneousFitter::calculateSPlotFactors"
									 ,*m_rws, m_modelName, "RooSimultaneous");
		}
    RooAddPdf* theslice = dynamic_cast<RooAddPdf*>(model->getPdf(sliceName));
    if (!theslice)
		{
			std::stringstream msg;
			msg << "Failed to get RooAddPdf for slice -  " << sliceName << ".";
			throw GeneralException("SimultaneousFitter::calculateSPlotFactors",msg.str());
		}
    RooAddPdf* modelClone = dynamic_cast<RooAddPdf*>( theslice->cloneTree() );
    assert(modelClone);
	
	//    modelClone->Print();

    const RooArgList yields = modelClone->coefList();

    TIterator * modelItr = modelClone->serverIterator();
    RooAbsArg * pdf;
	
    while ( (pdf = dynamic_cast<RooAbsArg *>(modelItr->Next())) ) {
        TIterator * paramItr = pdf->serverIterator();
        RooRealVar * param;
        while ( (param = dynamic_cast<RooRealVar *>(paramItr->Next())) ) {
			// Ensure that nuisance params are fixed AND the yield of the nuisance
			// species
            if (std::string(param->GetName()).find(std::string(sliceName)) == std::string::npos &&
				std::string(param->GetName()).find(this->get1DFitVarName()) == std::string::npos){
				std::cout << "Setting constant: " << param->GetName() << std::endl;
				param->setConstant();
            }
        }
    }
    RooFitResult * yFixedResult = modelClone->fitTo(*rds, RooFit::Extended(kTRUE), RooFit::Save(kTRUE),RooFit::PrintLevel(-1),RooFit::PrintEvalErrors(-1));
	//	yFixedResult->Print();
    RooArgList floatingParams = yFixedResult->floatParsFinal();
    int nFloat = floatingParams.getSize();	

    double signalYield = 0;
    double signalYieldError = 0;

    TIterator * floatItr = floatingParams.createIterator();
    RooRealVar * floatParam;

    int n = 0;
    bool yieldNotFound = true;
    while ( (floatParam = dynamic_cast<RooRealVar *>(floatItr->Next())) ) {
        if (!std::string(floatParam->GetName()).compare(std::string(signalYieldName))) {
            signalYield = floatParam->getVal();
            signalYieldError = floatParam->getError();
            yieldNotFound = false;
            break;
        }
        n++;
    }

    if (yieldNotFound) {
        std::stringstream msg;
        msg << "Signal yield name " << signalYieldName << " not present in floating parameters.";
        throw GeneralException("SimultaneousFitter::calculateSPlotFactors",msg.str());        
    }

    double covColSum = 0;
	
    TMatrixDSym covarianceM = yFixedResult->covarianceMatrix();
	
    for (int i = 0; i < nFloat; i++) {
        covColSum += covarianceM(i, n);
    }
	
    std::cout << "sig yield: " << signalYield << std::endl;
    std::cout << "sig yield error: " << signalYieldError << std::endl;
	
    double cFactor = signalYield - covColSum;
    double deviation = cFactor / signalYieldError;
	
    std::cout << "cFactor for " << signalYieldName << ": " << cFactor << " +/- " << deviation << std::endl;
	
	if (createVar)
		{
			RooRealVar cFactorVar((std::string(signalYieldName)+"_cFactor").c_str(),(std::string("cFactor for ")+signalYieldName).c_str(),cFactor,cFactor-deviation,cFactor+deviation);
			this->getWS()->import(cFactorVar);
		}

    return cFactor;
}

//==============================================================================
//Pass in sliceName as called in SimultaneousFitter::calculateSWeights method,
//pass in a filename for which you need to store sWeights in, 
//pass in the treename of the file, 
//pass in newfilename which will be created with the signal sweights as branch, 
//pass in the sigpdfname, the categoryname as called by addYields method,
//and the cut for which the new file will be created with.
//==============================================================================

void SimultaneousFitter::fillwithSWeights(const char* sliceName, std::string filename, std::string treename, std::string newfilename, std::string sigpdfname, std::string categoryname, std::string cut)
{
    if (!m_rws)
		{
			throw GeneralException("SimultaneousFitter::fillwithSWeights",
								   "No RooWorkspace object is defined!");
		}
	
	std::stringstream weightedName;
    weightedName << sliceName << "_withSWeights";
	
	std::cout << " Getting the RooAbsData " << std::endl;
    RooAbsData* rds_withWeights = dynamic_cast<RooAbsData*>( m_rws->data(weightedName.str().c_str()) );
    if (!rds_withWeights)
		{
			throw WSRetrievalFailure("SimultaneousFitter::fillwithSWeights", *m_rws, (weightedName).str(), "RooAbsData");
		}
	
	std::cout << " Reading the Root File" << std::endl;
	
	//Import the Root file
	TFile *File = 0;
	TTree *Tree0= 0;
	File = new TFile (filename.c_str(),"READ");
	Tree0= (TTree*) File->Get((treename).c_str());

	TFile* newFile = 0;
	TTree *newTree0 = 0;
	std::cout << " Recreating and Copying the Root File" << std::endl;
	newFile = new TFile(newfilename.c_str(), "RECREATE");
	newTree0 = Tree0->CopyTree(cut.c_str());

	//define new variables
	Double_t signal_sw(0.);
	//Create new branches for storing sweights for each event
	TBranch *swBranchsig     = newTree0->Branch("signal_sw", &signal_sw, "signal_sw/D");

	Int_t Evts_inrds(0);
	Evts_inrds = rds_withWeights->numEntries();
	std::cout << "Sum of Entries in RooAbsSet are " << Evts_inrds << std::endl;
	std::cout << "Number of Entries in the new Tree are " << newTree0->GetEntries() << std::endl;
	if (Evts_inrds != newTree0->GetEntries()) {
        throw GeneralException("SimultaneousFitter::fillwithSWeights",
							   "The Events is TTree and the events in dataset with sWeights do not match. Apply same cuts you applied when making RooDataSet to the TTree");
	}
	
	//iterate through the each event to store the sweights value in
	std::cout << " Is the RooAbsData Weighted " << rds_withWeights->isWeighted() << std::endl;
	for (Long64_t j = 0; j < newTree0->GetEntries(); ++j)
		{   
			const RooArgSet* row = rds_withWeights->get(j);
			if (!row)
				{
					std::stringstream msg;
					msg << "Failed to extract RooArgSet from workspace.";
					throw GeneralException("SimultaneousFitter::fillwithSWeights",msg.str());
				}
			signal_sw = row->getRealValue((sigpdfname+"_"+categoryname+"_Yield_sw").c_str());
			swBranchsig->Fill();
		}

	std::cout << "Writing" << std::endl;
	newFile->Write("", TObject::kOverwrite);

	delete Tree0;
	File->Close();
	delete newTree0;
	newFile->Close();
	std::cout << "Successfully Filled the tree" << std::endl;
}

//=============================================================================
// Gets the yield of the given pdf in the range given
//=============================================================================
double SimultaneousFitter::getYield(const char* pdfname, 
        const char* yieldname,
        double start, double stop,
        Bool_t getError)
{

    if (!m_rws) {
        throw GeneralException("SimultaneousFitter::getYield",
                "No RooWorkspace object is defined");
    }

    RooAbsPdf* thePdf = dynamic_cast<RooAbsPdf*>(m_rws->pdf(pdfname));
    if (!thePdf) {
        throw WSRetrievalFailure("SimultaneousFitter::getYield",
                *m_rws, pdfname, "RooAbsPdf");
    }

    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("SimultaneousFitter::getYield",
                *m_rws, m_1DFitVarName, "RooRealVar");
    }

    RooRealVar* yield = m_rws->var(yieldname);
    if (!yield) {
        throw WSRetrievalFailure("SimultaneousFitter::getYield",
                *m_rws, yieldname, "RooRealVar");
    }

    //create a range called "rangename" of the fit variable
    //prints out its own errors if start and stop are not appropriate
    //values
    mass->setRange("rangename",start,stop);

    //must delete this integral since new memory is allocated here 
    RooRealVar * integral = dynamic_cast<RooRealVar*>( thePdf->createIntegral(
                *mass, 
                RooFit::NormSet( *mass ),
                RooFit::Range("rangename")
                )
            );

    double integralVal = integral->getVal();  
    delete integral; integral = 0;

    if ( getError ) {
        return integralVal*yield->getError();
    } else {
        return integralVal*yield->getVal();
    }
}


//-----------------------------------------------------------------------------
// Returns the chi2 goodness of fit measure for a given slice of data 
// and the projected pdf
//-----------------------------------------------------------------------------
double SimultaneousFitter::chi2FitMeasure( const char* name, const char* slicename,
        const char* fitName )
{
    RooPlot* rp = this->plotFitResults( name, slicename, fitName, "", kFALSE);
    std::string histName = this->getDataHistName( slicename );
    std::string curveName = this->getModelCurveName( slicename );

    Int_t bins = rp->GetNbinsX();
    double chi2 = rp->chiSquare( curveName.c_str(), histName.c_str() ) * bins ;

    std::cout << "SimultaneousFitter::chi2FitMeasure - fit to " << name << " using slice " << 
        slicename << " : " << chi2 << " (" << bins << ")" << std::endl;

    delete rp; rp=0;
    return chi2;
}

//-----------------------------------------------------------------------------
// Returns the probability goodness of fit measure for a given slice of data 
// and the projected pdf
//-----------------------------------------------------------------------------
double SimultaneousFitter::probFitMeasure( const char* name, const char* slicename,
        const char* fitName )
{
    RooFitResult* theresult = dynamic_cast<RooFitResult*>( getFitResult( fitName ) );
    if (!theresult){
        throw GeneralException("Fitter::probFitMeasure",
                "Default fit has not been performed."); 
    }

    RooPlot* rp = this->plotFitResults( name, slicename, fitName, "", kFALSE);
    std::string histName = this->getDataHistName( slicename );
    std::string curveName = this->getModelCurveName( slicename );

    Int_t bins = rp->GetNbinsX();
    double chi2 = rp->chiSquare( curveName.c_str(), histName.c_str() ) * bins ;
    Int_t ndofmine = static_cast<Int_t>( theresult->floatParsFinal().getSize() );

    double probability = TMath::Prob( chi2, bins - ndofmine);

    std::cout << "SimultaneousFitter::probFitMeasure - fit to " << name << " using slice " << 
        slicename << " : " << probability << " (" << chi2 << "," << bins - ndofmine << ")" << std::endl;
    delete rp; rp=0;
    return probability;

}


//-----------------------------------------------------------------------------
// Plots the pulls between the observable with name 'name' and the 
// combined signal+background model PDF
// NB. The variable must be an observable in the model PDF
//
// The function returns a RooHist pointer. Note that the user is responsible
//for deleting this object.
//-----------------------------------------------------------------------------
RooPlot* SimultaneousFitter::plotFitPulls(const char* name, const char* slicename,
        const char* fitName, double pmsigma, double pmline )
{
    // get the fit results plot
    //RooPlot* rp = this->plotFitResults( name, fitName, "", kFALSE);
    RooPlot* rp = this->plotFitResults( name, slicename, fitName, "", kFALSE);

    std::string histName = this->getDataHistName( slicename );
    std::string curveName = this->getModelCurveName( slicename );

    RooHist* hist = rp->pullHist(histName.c_str(), curveName.c_str() );

    if( !hist ) {
        throw GeneralException( "SimultaneousFitter::plotFitPulls",
                "Pull plot is NULL and was not created!");
    }

    RooRealVar* var = m_rws->var( name );
    if ( !var ) {
        throw WSRetrievalFailure( "SimultaneousFitter::plotFitPulls",
                *m_rws, name, "RooRealVar");
    }

    RooPlot* rp_pull = var->frame( rp->GetNbinsX() );

    // set the maximum range of the pull histograms, defaults to +/- 5
    rp_pull->SetMinimum( -pmsigma );
    rp_pull->SetMaximum( pmsigma );

    TAxis* xAxis = rp_pull->GetXaxis();

    // Add the 2 sigma lines to the plot
    double xMin = xAxis->GetXmin();
    double xMax = xAxis->GetXmax();

    TLine* midLine = 0;
    TLine* uppLine = 0;
    TLine* lowLine = 0;

    midLine = new TLine( xMin,  0., xMax,  0. );
    uppLine = new TLine( xMin,  pmline, xMax,  pmline );
    lowLine = new TLine( xMin, -pmline, xMax, -pmline );

    uppLine->SetLineColor( kRed );
    lowLine->SetLineColor( kRed );

    // N.B. addPlotable transfers ownership of the RooHist
    //rp_pull->addPlotable( hist, "BX" );
    rp_pull->addPlotable( hist, "PE1" );
    rp_pull->addObject( lowLine );
    rp_pull->addObject( midLine );
    rp_pull->addObject( uppLine );

    delete rp; rp=0;
    return rp_pull;
}

// Plot the observable with name 'name', showing the fit results
// NB. The variable must be an observable in the model PDF
//
// Optionally, a range can be specified. This will be used to extrapolate the
// yields to the given range. The function will raise an exception if the
// range does not exist for the given observable.
//
// By default, the extrapolated yields will be labelled "yieldTitle (range)".
// If rangeTitle is specified, then the label will be "yieldTitle (rangeTitle)"
//
// If sumWErrors is true, then plot sum-of-weights-squared errors (default is
// Poissonian errors). RooFit will force sum-of-weights-squared errors if the
// dataset is weighted.
//
// If printChi2 is true, then the chi^2, and number of degrees of freedom
// of the fit are shown.
//
// If a chi^2 test statistic has been set, then this will be calculated,
// and the p-value and significance will be determined and plotted
//
// If the fit was produced in extended mode, and the chi^2 or a
// chi^2 test statistic have been requested, then extendedMode should
// be set to true.
//
// excludedComponents is a comma separated list of pdf components on the slice
// that are not to be plotted
//
// The function returns a RooPlot pointer. Note that the user is responsible
// for deleting this object.
RooPlot* SimultaneousFitter::plotFitResults(const char* name,
        const char* slicename,
        const char* fitName,
        const char* excludedComponents,
        Bool_t sumW2Errors
        )
{
    if (!m_rws) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "No RooWorkspace object is defined!");
    }
    // check that name is specified
    if (!name||strcmp(name,"")==0) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "No variable name has been specified!");
    }

    // get the dataset
    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( m_dataSetName ) );
    if (!rds) {
        throw WSRetrievalFailure("SimultaneousFitter::plotFitResults"
                ,*m_rws, m_dataSetName, "RooDataSet");
    }

    // get the model PDF
    RooSimultaneous* model = dynamic_cast<RooSimultaneous*>( m_rws->pdf( m_modelName ) );
    if (!model)
    {
        throw WSRetrievalFailure("SimultaneousFitter::plotFitResults"
                ,*m_rws, m_modelName, "RooSimultaneous");
    }

    // get the list of observables
    const RooArgSet* observables = model->getObservables( *rds );
    assert(observables);

    // get the plot variable
    RooRealVar* var = m_rws->var( name );
    if (!var) {
        throw WSRetrievalFailure("SimultaneousFitter::plotFitResults"
                ,*m_rws, name, "RooRealVar");
    }

    // check that the plot variable is in the list of observables
    if (!observables->contains(*var)) {
        std::stringstream msg;
        msg << "Plot variable " << name << " is not in the list of observables "
            << "for model PDF " << model->GetName();
        throw GeneralException("SimultaneousFitter::plotFitResults", msg.str());
    }

    if (fitName&&strcmp(fitName,"")!=0) {

        if (!m_rws->loadSnapshot(fitName)) {

            throw WSRetrievalFailure("SimultaneousFitter::plotFitResults"
                    ,*m_rws, fitName, "fit snapshot");
        }
    }    

    // make the RooPlotFitter::PlotLikelihoodScan:
    Int_t nPlotBins = m_plotBinMap.find( name ) == m_plotBinMap.end() ? m_globalPlotBins : m_plotBinMap[ name ];

    RooPlot* rp = var->frame(RooFit::Bins(nPlotBins));
    if (!rp) {
        std::stringstream msg;
        msg << "Failed to get RooPlot for RooRealVar " << name;
        throw GeneralException("SimultaneousFitter::plotFitResults", msg.str());
    }

    RooAbsData::ErrorType errorType = (!sumW2Errors)?RooAbsData::Poisson
        :RooAbsData::SumW2;
    //rp->GetYaxis()->SetTitleOffset(1.2);
    if (strcmp(var->GetTitle(),"")==0) {
        rp->GetXaxis()->SetTitle(TString::Format("%s %s", var->GetName(),
                    rp->GetXaxis()->GetTitle()));
    }

    RooLinkedList argList;
    RooCmdArg* arg = 0;  

    try {
        //create the cut to apply to the indexed dataset
        std::stringstream datacut;
        datacut << m_catSetName << "==" << m_catSetName << "::" << slicename;
        arg = new RooCmdArg(RooFit::Cut(datacut.str().c_str()));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }

    try {
        arg = new RooCmdArg(RooFit::LineColor(m_dataSetLineColor));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }

    try {
        arg = new RooCmdArg(RooFit::LineStyle(m_dataSetLineStyle));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::LineWidth(m_dataSetLineWidth));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::MarkerColor(m_dataSetMarkerColor));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::MarkerStyle(m_dataSetMarkerStyle));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::MarkerSize(m_dataSetMarkerSize));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::FillColor(m_dataSetFillColor));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::FillStyle(m_dataSetFillStyle));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::DrawOption(m_dataSetDrawOption));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::DataError(errorType));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        //name the data hist within the rooplot
        std::stringstream dataname;
        dataname << slicename << "_Data";
        arg = new RooCmdArg(RooFit::Name(dataname.str().c_str()));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::plotFitResults",
                "Got std::bad_alloc when creating new RooCmdArg");
    }

    //get the RooCategory
    RooCategory* cat = m_rws->cat(m_catSetName);
    if (!cat) {
        throw WSRetrievalFailure("SimultaneousFitter:createPDFSets",
                *m_rws, m_catSetName, "RooCategory");
    }

    rds->plotOn(rp,argList);

    std::stringstream AddPdfName;
    AddPdfName << slicename << "_AddPdf";

    model->plotOn(rp, RooFit::Slice(*cat,slicename),RooFit::ProjWData(RooArgSet(*cat),*rds),
            RooFit::LineColor(m_modelLineColor),
            RooFit::LineStyle(m_modelLineStyle),
            RooFit::LineWidth(m_modelLineWidth),
            RooFit::Name(AddPdfName.str().c_str()));

    //sorting out the components
    RooAddPdf* theslice = dynamic_cast<RooAddPdf*>(model->getPdf(slicename));
    if (!theslice) {
        std::stringstream msg;
        msg << "Failed to get RooAddPdf for slice -  " << slicename << ".";
        throw GeneralException("SimultaneousFitter::plotFitResults",msg.str());
    }

    const RooArgList components = theslice->pdfList();

    //put excluded pdf component names in a vector
    std::vector<std::string> excludes;
    std::string dummy( excludedComponents );  
    m_stringHelper.replaceAll( dummy, " ", "" ); // remove all whitespaces
    m_stringHelper.split( excludes, dummy, "," );
    TIterator* iter = components.createIterator();
    RooAbsPdf* pdf;
    Int_t color = 6;

    while( ( pdf = dynamic_cast<RooAbsPdf*>( iter->Next() ) ) ){
        std::string name( pdf->GetName() );

        // If only one component, don't plot
        if ( std::find( excludes.begin(), excludes.end(), name ) == excludes.end() && components.getSize() > 1) {

            if( color == 10 || color == 0 || color == 18 || color == 19 || color == m_modelLineColor ) {
                color++; // we do this just to avoid plotting with any dodgy colours such as white, user
                // should specify what it is that they want if they do not want default plotting styles.
            }
            model->plotOn(rp, RooFit::Slice( *cat, slicename ), RooFit::ProjWData( RooArgSet( *cat ), *rds ),
						  RooFit::Components( name.c_str() ),
                    RooFit::LineColor( ( m_pdfLineColorMap.find( name ) != m_pdfLineColorMap.end() ) ? m_pdfLineColorMap[name] : color++ ),
                    RooFit::LineStyle( ( m_pdfLineStyleMap.find( name ) != m_pdfLineStyleMap.end() ) ? m_pdfLineStyleMap[name] : 2 ),
                    RooFit::LineWidth( ( m_pdfLineWidthMap.find( name ) != m_pdfLineWidthMap.end() ) ? m_pdfLineWidthMap[name] : 2 ) 
                    );
        }

        // Plot PDF sub-components
        // Check that the pdf is one that actually has components

        if (m_plotSubComponents && (pdf->ClassName() == std::string("RooAddPdf") || pdf->ClassName() == std::string("RooProdPdf"))) {

            const RooArgList subComponents = (pdf->ClassName() == std::string("RooAddPdf")) ? dynamic_cast<RooAddPdf *>(pdf)->pdfList() : dynamic_cast<RooProdPdf *>(pdf)->pdfList();

            TIterator * subComponentItr = subComponents.createIterator();

            while(RooAbsPdf * s = dynamic_cast<RooAbsPdf *>(subComponentItr->Next())) {
                std::string subComponentName = s->GetName();

                if( color == 10 || color == 0 || color == 18 || color == 19 || color == 7 || color == 3 || color == m_modelLineColor ) {
                    color++;
                }

                model->plotOn(rp, RooFit::Slice( *cat, slicename ), RooFit::ProjWData( RooArgSet( *cat ), *rds ),
                        RooFit::Components( subComponentName.c_str() ),
                        RooFit::LineColor( ( m_pdfLineColorMap.find( subComponentName ) != m_pdfLineColorMap.end() ) ? m_pdfLineColorMap[subComponentName] : color++ ),
                        RooFit::LineStyle( ( m_pdfLineStyleMap.find( subComponentName ) != m_pdfLineStyleMap.end() ) ? m_pdfLineStyleMap[subComponentName] : 2 ),
                        RooFit::LineWidth( ( m_pdfLineWidthMap.find( subComponentName ) != m_pdfLineWidthMap.end() ) ? m_pdfLineWidthMap[subComponentName] : 2 ));
            }
        }
    }
    delete iter; iter=0;

    ClientTree ct;  // just for trimming the lines
    //if the pdf has a blind yield in it, draw a label over it +/- 150 MeV around the mean
    //of the signal
    const RooArgList yields = theslice->coefList();
    iter = yields.createIterator();
    RooAbsReal* yield = 0;
    while( (yield=dynamic_cast<RooAbsReal*>( iter->Next() ) ) ) {

        //check whether it inherits from RooAbsHiddenReal
        if( dynamic_cast<RooAbsHiddenReal*>(yield) ) {

            std::string yieldname( yield->GetName() );
            //extract the pdf name from this yieldname
            std::string pdfname = yieldname;
            ct.trim_left( pdfname, "ub_" );
            ct.trim_right( pdfname, "_Yield" );
            ct.trim_right( pdfname, slicename );
            ct.trim_right( pdfname, "_" );

            //create an iterator over the pdflist on this slice and try and find the pdf name
            TIterator* pdfIterator = components.createIterator();
            RooAbsPdf* thePdf = 0;
            while( (thePdf=dynamic_cast<RooAbsPdf*>( pdfIterator->Next() ) ) ) {
                std::string name( thePdf->GetName() );
                if ( name.find(pdfname)!=std::string::npos ) {
                    //try and find the mean of this signal pdf
                    //it will contain "_mu"
                    RooArgList* nodes = new RooArgList;
                    thePdf->treeNodeServerList(nodes,0,kTRUE,kTRUE,kFALSE,kTRUE);

                    TIterator* serverIterator = nodes->createIterator();

                    RooAbsReal* theParam=0;
                    //std::cout << "parameters: " << std::endl;

                    while( (theParam=dynamic_cast<RooAbsReal*>( serverIterator->Next() ) ) ) {
                        //std::cout << theParam->GetName() << std::endl;
                        std::string paramName( theParam->GetName() );
                        if ( paramName.find("_mu") != std::string::npos ) {
                            //when a mean is found make a pavelabel over it +/- 150 MeV around the mean
                            //of the signal
                            TPaveLabel *blindpav = new TPaveLabel(theParam->getVal()-80,0.03,theParam->getVal()+80,
                                    rp->GetMaximum(),"","");
                            blindpav->SetBorderSize(0);
                            blindpav->SetTextSize(0.1);
                            blindpav->SetTextAngle(30);
                            blindpav->SetFillColor(0);
                            blindpav->SetTextColor(2);
                            //add object to RooPlot to be drawn later, this transfers ownership of pavelabel   
                            rp->addObject(blindpav);
                            //exit loop now that mean is found
                            break;   
                        }
                    }
                    //if the end of the loop searching for mean was reached throw exception
                    if (!theParam){
                        std::stringstream msg;
                        msg << "Did not find mean of pdf " << pdfname << ".";
                        throw GeneralException("SimultaneousFitter::plotFitResults",msg.str());  
                    }

                    delete serverIterator; serverIterator=0;
                    delete nodes; nodes=0;
                    //exit loop when signal pdf is found
                    break;
                }
            }
            //if the end of the pdfList is reached throw exception
            if (!thePdf) {
                std::stringstream msg;
                msg << "Did not find pdf corresponding to yield called " << yield->GetName() << ".";
                throw GeneralException("SimultaneousFitter::plotFitResults",msg.str());
            }
            delete pdfIterator; pdfIterator=0;

        }
    }

    delete iter; iter=0;


    return rp;
}


//-----------------------------------------------------------------------------
// Get the name of the data histogram in a RooPlot of the specified
// fit variable.
// This function is used to get the pull plot.
// NB. You may need to be override this method in a derived class.
//-----------------------------------------------------------------------------
std::string SimultaneousFitter::getDataHistName( const char* slicename ) const {
    // construct the histogram name from the dataset name
    std::stringstream dataname;
    dataname << slicename << "_Data";
    return dataname.str();
}


//-----------------------------------------------------------------------------
// Get the name of the model PDF curve in a RooPlot of the specified
// fit variable.
// This function is used to get the pull plot.
// NB. You may need to be override this method in a derived class.
//-----------------------------------------------------------------------------
std::string SimultaneousFitter::getModelCurveName(const char* name) const {
    // construct the curve name for the model PDF
    std::stringstream addPdfName;
    addPdfName << name << "_AddPdf";
    return addPdfName.str();
}


//=============================================================================
// Simple function to plot a variable with given weight from given dataset.
// Written primarily to plot vars from sWeighted datasets. May be updated.
//=============================================================================
RooPlot* SimultaneousFitter::makePlot(const char* varName,
        const char* datasetName,
        const char* wgtVarName,
        Bool_t sumW2Errors
        )
{
    if (!m_rws)
    {
        throw GeneralException("SimultaneousFitter::makePlot",
                "No RooWorkspace object is defined!");
    }
    // check that name is specified
    if (!varName||strcmp(varName,"")==0)
    {
        throw GeneralException("SimultaneousFitter::makePlot",
                "No variable name has been specified!");
    }

    // get the dataset
    RooDataSet* rds = dynamic_cast<RooDataSet*>( m_rws->data( datasetName ) );
    if (!rds)
    {
        throw WSRetrievalFailure("SimultaneousFitter::makePlot"
                ,*m_rws, datasetName, "RooDataSet");
    }
    //if wgtVarName is specified make a weighted copy
    bool madeCopy=false;
    if (wgtVarName && strcmp(wgtVarName,"")!=0){
        rds = new RooDataSet(rds->GetName(), rds->GetTitle(), rds, *rds->get(),
                "", wgtVarName);
        madeCopy=true;
    }

    // get the plot variable
    RooRealVar* var = m_rws->var(varName);
    if (!var)
    {
        throw WSRetrievalFailure("SimultaneousFitter::makePlot"
                ,*m_rws, varName, "RooRealVar");
    }

    // make the RooPlot
    Int_t nPlotBins=m_plotBinMap.find(varName)==m_plotBinMap.end()?m_globalPlotBins:m_plotBinMap[varName];

    RooPlot* rp = var->frame(RooFit::Bins(nPlotBins));
    if (!rp)
    {
        std::stringstream msg;
        msg << "Failed to get RooPlot for RooRealVar " << varName;
        throw GeneralException("SimultaneousFitter::makePlot", msg.str());
    }
    RooAbsData::ErrorType errorType = (!sumW2Errors)?RooAbsData::Poisson
        :RooAbsData::SumW2;
    //    rp->GetYaxis()->SetTitleOffset(1.2);

    if (strcmp(var->GetTitle(),"")==0) {
        rp->GetXaxis()->SetTitle(TString::Format("%s %s", var->GetName(),
                    rp->GetXaxis()->GetTitle()));
    }

    RooLinkedList argList;
    RooCmdArg* arg = 0;

    try {
        arg = new RooCmdArg(RooFit::LineColor(m_dataSetLineColor));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::makePlot",
                "Got std::bad_alloc when creating new RooCmdArg");
    }

    try {
        arg = new RooCmdArg(RooFit::LineStyle(m_dataSetLineStyle));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::makePlot",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::LineWidth(m_dataSetLineWidth));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::makePlot",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::MarkerColor(m_dataSetMarkerColor));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::makePlot",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::MarkerStyle(m_dataSetMarkerStyle));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::makePlot",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::MarkerSize(m_dataSetMarkerSize));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::makePlot",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::FillColor(m_dataSetFillColor));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::makePlot",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::FillStyle(m_dataSetFillStyle));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::makePlot",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::DrawOption(m_dataSetDrawOption));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::makePlot",
                "Got std::bad_alloc when creating new RooCmdArg");
    }
    try {
        arg = new RooCmdArg(RooFit::DataError(errorType));
        argList.Add(arg->Clone());
        delete arg;
    }
    catch (std::bad_alloc& e) {
        throw GeneralException("SimultaneousFitter::makePlot",
                "Got std::bad_alloc when creating new RooCmdArg");
    }

    rds->plotOn(rp,argList);

    if (madeCopy) delete rds;

    return rp;
}


//=============================================================================
//=============================================================================
//TOY STUDIES
//=============================================================================
//=============================================================================
void SimultaneousFitter::doRooMCStudy(Int_t nSamples, const char* fname, UInt_t seed,
        Double_t nEvtPerSampleScaleFactor,
        Bool_t binnedMode)
{
    RooRandom::randomGenerator()->SetSeed(seed);
    gRandom = RooRandom::randomGenerator();

    //Get the stuff I need from the workspace
    RooSimultaneous* model = dynamic_cast<RooSimultaneous*>( m_rws->pdf( m_modelName ) );  
    if (!model)
    { 
        throw WSRetrievalFailure("SimultaneousFitter::doRooMCStudy"
                ,*m_rws, m_modelName, "RooSimultaneous"); 
    }
    //make a clone of this for use in this function
    RooSimultaneous* modelClone = dynamic_cast<RooSimultaneous*>( model->cloneTree() );

    RooRealVar* mass = m_rws->var(m_1DFitVarName);
    if (!mass) {
        throw WSRetrievalFailure("SimultaneousFitter::doRooMCStudy",
                *m_rws, m_1DFitVarName, "RooRealVar");    
    }

    RooCategory* cat = m_rws->cat(m_catSetName);
    if (!cat) {
        throw WSRetrievalFailure("SimultaneousFitter::doRooMCStudy",
                *m_rws, m_catSetName, "RooCategory");
    }

    RooArgSet* observables = new RooArgSet(*mass,*cat);

    //*** from roofit tutorial rf801 ***
    // C r e a t e   m a n a g e r
    // ---------------------------

    // Instantiate RooMCStudy manager on model with x as observable and given choice of fit options
    //
    // The Silence() option kills all messages below the PROGRESS level, leaving only a single message
    // per sample executed, and any error message that occur during fitting
    //
    // The Extended() option has two effects:
    //    1) The extended ML term is included in the likelihood and
    //    2) A poisson fluctuation is introduced on the number of generated events
    //
    // The FitOptions() given here are passed to the fitting stage of each toy experiment.
    // If Save() is specified, the fit result of each experiment is saved by the manager
    //
    // A Binned() option is added in this example to bin the data between generation and fitting
    // to speed up the study at the expense of some precision

    //if a scale factor has been specified alter the number of expected events
    if (nEvtPerSampleScaleFactor!=1.0){

        //multiply all the yields by the scale factor
        RooArgSet* fitParams = modelClone->getParameters(*observables);
        TIterator* paramIter = fitParams->createIterator();
        RooRealVar* par=0;

        while ( (par=dynamic_cast<RooRealVar*>( paramIter->Next() ) ) )
        {
            TString theName(par->GetName());
            if (theName.EndsWith("_Yield")) {

                //double init = par->getVal();
                //make sure that the value i'm going to set this yield to is
                //inside the range, if not extend the range by an appropriate amount.
                if (par->getVal()*nEvtPerSampleScaleFactor > par->getMax()){
                    par->setMax(0,par->getVal()*nEvtPerSampleScaleFactor*1.1);
                }

                par->setVal(par->getVal()*nEvtPerSampleScaleFactor);
                //double final = par->getVal();

                //std::cout << par->GetName() << "  " << final/init << std::endl;
            }
        }
        delete paramIter;
    }
    //std::cout << "New expected events = " << modelClone->expectedEvents(observables);
    //throw GeneralException("SimultaneousFitter::doSimpleMCStudy",
    //                       "Intentional break in program.");
    RooMCStudy* mcstudy = new RooMCStudy(*modelClone,*observables,RooFit::Binned(binnedMode),RooFit::Silence(),RooFit::Extended(),
            RooFit::FitOptions(RooFit::Save(kTRUE),RooFit::PrintEvalErrors(0))) ;



    // G e n e r a t e   a n d   f i t   e v e n t s
    // ---------------------------------------------

    // Generate and fit nSamples samples of Poisson(nExpected) events
    mcstudy->generateAndFit(nSamples);

    RooRealVar covQual("covQual","covQual", 0, 3,"");
    RooRealVar status("status","status", -100, 100, "");
    RooArgSet vars(covQual,status);
    RooDataSet fitStatusData("Status","StatusData", vars);

    for (int i = 0; i < nSamples; i++){
        int cq = mcstudy->fitResult(i)->covQual();
        int stat = mcstudy->fitResult(i)->status();
        covQual.setVal(cq);
        status.setVal(stat);
        fitStatusData.add(vars);
    }

    // S a v e  t h e  D a t a s e t
    // -----------------------------
    TFile* outfile = new TFile(fname,"recreate");
    outfile->cd();
    mcstudy->fitParDataSet().Write("fitParData");
    fitStatusData.Write("fitStatusData");

    outfile->Close();
    delete mcstudy; mcstudy=0;
    delete observables; observables=0;
    delete modelClone; modelClone=0;

}


//=============================================================================
// Destructor
//=============================================================================
SimultaneousFitter::~SimultaneousFitter() {}
//=============================================================================

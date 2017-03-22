#include "P2VV/P2VVFoam.h"

using namespace::std;
using namespace::RooFit;

//Constructor with correct argument
P2VVFoam::P2VVFoam( RooWorkspace& ws, RooAbsReal& pdf, std::list<string> py_obsList, int seed){
  // fill our vector of the observables and which are discrete
  RooArgSet vars;
  for( auto varName : py_obsList ){
    if(ws.var(varName.c_str())) {
      m_continuous.push_back(varName);
      m_minima.push_back(ws.var(varName.c_str())->getMin());
      m_ranges.push_back(ws.var(varName.c_str())->getMax()-ws.var(varName.c_str())->getMin());
      vars.add(*(ws.var(varName.c_str())),false);
    }
    else if(ws.cat(varName.c_str())) m_discrete.push_back(varName);
    else cout << "Error::P2VVFoam:: Given observable: " << varName.c_str() << " is neither continuous or discrete" << endl;
  }

  m_ws=&ws;
  m_seed = seed;
  //m_dataSet = RooDataSet();

  // Make the binding
  m_binding = new RooTFoamBinding(pdf,vars);

  cout << "Initializing Generator(s)" << endl;

  // If there are no discrete variables, then nothing more to do
  if(m_discrete.size()==0){
    this->Init();
    return;
  }

  // Fill all possible values
  for( unsigned int discreteIndex = 0; discreteIndex < m_discrete.size(); ++discreteIndex ){
    vector<string> v_indexTrack;
    RooCategory* disc_var = ws.cat( m_discrete[discreteIndex].c_str() );
    TIterator* iter = disc_var->typeIterator();
    iter->Next();
    while(*(*iter)){
      RooCatType* type = dynamic_cast<RooCatType*>(*(*iter));
      v_indexTrack.push_back(type->GetName());
      iter->Next();
    }
    m_indexTrack.push_back(v_indexTrack);
  }

  cout << "... creating all combinations of discrete observables" << endl;

  // Now make all possible combinations
  bool finished=false;
  vector<int> indices;
  for (unsigned int observableIndex = 0; observableIndex < m_indexTrack.size(); ++observableIndex ){
    //Just initialise the counter
    indices.push_back(0);
  }

  while(!finished){
    vector<string> oneCombination;
    for (unsigned int observableIndex = 0; observableIndex < m_discrete.size(); ++observableIndex ){
      oneCombination.push_back( m_indexTrack[unsigned(observableIndex)][ unsigned(indices[unsigned(observableIndex)]) ] );
    }
    m_combinations.push_back(oneCombination);

    //Increment the indices
    for ( int observableIndex = int(m_indexTrack.size()) - 1; observableIndex >= 0; --observableIndex ){
      ++indices[unsigned(observableIndex)];

      //Check if the index has reached its maximum
      if ( indices[unsigned(observableIndex)] == int(m_indexTrack[unsigned(observableIndex)].size()) ){
        if ( observableIndex == 0 ){
          //If the most significant index has reached its maximum, all combinations have been found
          finished = true;
        }
        else{
          //Zero this index, and examine the next most significant
          indices[unsigned(observableIndex)] = 0;
        }
      }
      else{
        break;
      }
    }
  }

  // Print the combinations to check
  cout << "P2VVFoam::INFO: Found the following combinations" << endl;
  for( auto combination : m_combinations ){
    for(auto value : combination) cout << value.c_str() << "\t" << endl;
    cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << endl;
  }

  this->Init();
}

void P2VVFoam::Init()
{
  // initialise all discrete values
  for(unsigned int n=0;n<m_discrete.size();n++){
    m_ws->cat( m_discrete[n].c_str() )->setLabel( m_combinations[0][n].c_str() ); 
  }

  // increment iterators and set the values of the categories
  // to the next value
  for(unsigned int n=0;n<m_combinations.size();n++){
    for(unsigned int m=0;m<m_combinations[n].size();m++){
      m_ws->cat( m_discrete[m].c_str() )->setLabel( m_combinations[n][m].c_str() );  
    }
      
    //      Generate unique name for this foam instance
    TString Name("Foam-");
    Name+=n;
    TString FoamName("Foam_");FoamName+=n;
    TString RootName(Name);
    RootName.Append(".root");

    cout << "Generating Foam:\t" << Name << endl;
    TFile* MC_Cache = new TFile( RootName, "RECREATE" );
    TRandom3* rand = new TRandom3(m_seed+n);
    //Initialise Foam
    TFoam* foamGenerator = new TFoam( Name );
    foamGenerator->SetkDim( Int_t(m_continuous.size()) );
    ApplySettings(foamGenerator,rand);
    foamGenerator->Initialize();

    cout << "Storing TFOAM TObject in:\t\t" << RootName << endl;  
    foamGenerator->Write( Name, TObject::kOverwrite );
    MC_Cache->Write( "", TObject::kOverwrite );

    //Store the foam generator
    m_files.push_back( MC_Cache );
    m_foamGens.push_back( foamGenerator );
  }

  // if discrete size is zero, only need one foam
  if(m_discrete.size()==0){
    //      Generate unique name for this foam instance
    TString Name("Foam");
    TString FoamName("Foam");
    TString RootName(Name);
    RootName.Append(".root");

    cout << "Generating Foam:\t" << Name << endl;
    TFile* MC_Cache = new TFile( RootName, "RECREATE" );
    TRandom3* rand = new TRandom3(m_seed);
    //Initialise Foam
    TFoam* foamGenerator = new TFoam( Name );
    foamGenerator->SetkDim( Int_t(m_continuous.size()) );
    ApplySettings(foamGenerator,rand);
    foamGenerator->Initialize();

    cout << "Storing TFOAM TObject in:\t\t" << RootName << endl;  
    foamGenerator->Write( Name, TObject::kOverwrite );
    MC_Cache->Write( "", TObject::kOverwrite );

    //Store the foam generator
    m_files.push_back( MC_Cache );
    m_foamGens.push_back( foamGenerator );
  }
}

void P2VVFoam::ApplySettings(TFoam* foamGenerator, TRandom3* rand){
  foamGenerator->SetPseRan( rand );
  foamGenerator->SetRho( m_binding );	//	Can afford to Boot Foam's ability if we're using just one cached instance :D
  foamGenerator->SetnCells( 1000 );	//	1000	Total number of bins to construct
  foamGenerator->SetnSampl( 200 );	//	200	Samples to take when constructing bins
  foamGenerator->SetnBin( 8 );		//	8	Bins along each axis
  foamGenerator->SetOptRej( 1 );	//	1/0	Don't/Use Weighted Distribution
  foamGenerator->SetOptDrive( 2 );	//	1/2	Best Variance/Weights
  foamGenerator->SetEvPerBin( 25 );	//	25	Weights per bin... This doesn't Saturate as object is written before generating events
  foamGenerator->SetChat( 0 );		//	0	verbosity
  foamGenerator->SetMaxWtRej( 1.1 );	//	1.1	Unknown what effect this has, something to do with weights
}

//Use accept/reject method to create data
void P2VVFoam::GenerateData( int DataAmount ){
  cout << "Requested P2VVFoam to generate: " << DataAmount << " events" << endl;
  if(m_fractions.size()==0 && m_discrete.size()!=0) cout << "P2VVFoam::Error: Tell me the fractions of the discrete categories to generate"
    << endl;

  int ev_count = 0;

  RooArgSet varListTemp;
  for(unsigned int n=0; n<m_discrete.size();n++) varListTemp.add(*(m_ws->cat( m_discrete[n].c_str() )));
  for(unsigned int n = 0; n < m_continuous.size(); ++n ) varListTemp.add(*(m_ws->var( m_continuous[ n ].c_str() )));
  const RooArgSet varList = varListTemp;
  varList.Print();

  delete m_dataSet;
  RooDataSet* p2vv_dataSet = new RooDataSet("P2VVFoamDataSet","P2VVFoamDataSet",varList);

  // If have no discrete observables, just generate the dataset
  if(m_discrete.size()==0){
    for(int dataIndex = 0; dataIndex < DataAmount; ++dataIndex ){
      ev_count++;
      const int size = m_continuous.size();
      Double_t* generatedEvent = new Double_t[size];
      for(int a=0; a<size; a++) generatedEvent[a]=0.0;
      m_foamGens[0]->MakeEvent();
      m_foamGens[0]->GetMCvect(generatedEvent);
      // Store the continuous observables
      for(unsigned int continuousIndex = 0; continuousIndex < m_continuous.size(); ++continuousIndex ){
        m_ws->var( m_continuous[ continuousIndex ].c_str() )->setVal(m_minima[continuousIndex]+(generatedEvent[continuousIndex]*m_ranges[continuousIndex]));
      }
      // Store the event
      p2vv_dataSet->add(varList);
    }
  }
  
  for(unsigned int n=0;n<m_combinations.size();n++){
    int c_dataAmount = int(DataAmount*m_fractions[n] + 0.5);
    stringstream setname;
    //setname << "Subset_" << n;
    //RooDataSet subset(setname.str().c_str(),setname.str().c_str(),varList);
    cout << ".. generating " << c_dataAmount << " events for this subset:" << endl;
    for(unsigned int a=0; a<m_discrete.size(); a++) {
      cout << "Discrete var: " << m_discrete[a].c_str() << ",\t Val: " << m_ws->cat( m_discrete[a].c_str() )->getLabel() << endl;
    }

    // Set the discrete observables
    int discVar=0;
    for(auto value : m_combinations[n]){
      m_ws->cat( m_discrete[discVar].c_str() )->setLabel( value.c_str() ); 
      discVar++;
    }

    for(int dataIndex = 0; dataIndex < c_dataAmount; ++dataIndex ){
      ev_count++;
      // Select a Foam generator and generate an event with it
      const int size = m_continuous.size();
      Double_t* generatedEvent = new Double_t[size];
      for(int a=0; a<size; a++) generatedEvent[a]=0.0;

      //cout << "About to generate event" << endl;
      m_foamGens[n]->MakeEvent();
      m_foamGens[n]->GetMCvect(generatedEvent);
      //cout << "Generated event:" << endl;
      //for(unsigned int a=0; a<size; a++) {
      //  cout << "Var: " << m_continuous[a] << ",\t Val: " << generatedEvent[a] << endl;
      //}

      // Store the continuous observables
      for(unsigned int continuousIndex = 0; continuousIndex < m_continuous.size(); ++continuousIndex ){
        m_ws->var( m_continuous[ continuousIndex ].c_str() )->setVal(m_minima[continuousIndex]+(generatedEvent[continuousIndex]*m_ranges[continuousIndex]));
      }
      //cout << "Stored continuous variables" << endl;

      // Store the event
      p2vv_dataSet->add(varList);
      //cout << "... added data point" << endl;
    }
    //m_dataSet.append(subset);
    //cout << "... added subset for combination" << endl;
  }
  cout << "... updating member dataset" << endl;
  m_dataSet = p2vv_dataSet;
  cout << "Generated " <<  ev_count << " events" << endl; 
}

//Return data set
RooDataSet* P2VVFoam::GetDataSet()
{
  return m_dataSet;
}

//Return data set
void P2VVFoam::FillFractions(RooDataSet protoData)
{
  // Initialise counters
  for(unsigned int n=0;n<m_combinations.size();n++){
    m_fractions.push_back(0.0);
  }

  // loop over the dataset
  for(int n=0;n<protoData.numEntries();n++){
    
    const RooArgSet* vars = protoData.get(n);
    vector<string> vec_CatsIndices;
    
    // get vector for the data point
    for(unsigned int d=0;d<m_discrete.size();d++){
      RooCategory* var = dynamic_cast<RooCategory*>(vars->find(m_discrete[d].c_str()));
      string index = var->getLabel();
      vec_CatsIndices.push_back(index);
    }
      
    // Find the corresponding combination
    for(unsigned int n=0;n<m_combinations.size();n++){
      if(vec_CatsIndices==m_combinations[n]) m_fractions[n]+=1.0;
    }  
  }
  
  // Normalise counters
  for(unsigned int m=0;m<m_combinations.size();m++) m_fractions[m]=m_fractions[m]/protoData.numEntries();
}

// Destructor
P2VVFoam::~P2VVFoam()
{
  delete m_dataSet;
  delete m_binding;
}

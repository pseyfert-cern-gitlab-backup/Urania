/*
 * author: S Benson (sean.benson@cern.ch)
 * date: 20/12/2016
 *
 * P2VVFoam:
 *     Class designed to generate simulated datasets from
 *     a RooFit based PDF using TFoam.
 *
 *     The class will account for discrete variables in the PDF such
 *     as flavour tags and time period.
 *
 * Todo:
 *     Optimise decay time generation.
 */
#ifndef FOAM_H
#define FOAM_H

#include "TRandom3.h"
#include "TFoam.h"
#include "TFile.h"
#include <vector>
#include <string>
#include "RooDataSet.h"
#include "RooCategory.h"
#include "RooAbsArg.h"
#include "RooAbsReal.h"
#include "RooSimultaneous.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooTFoamBinding.h"

#include <boost/python.hpp>
using namespace boost;

using namespace::std;
using namespace::RooFit;

class P2VVFoam
{
  public:
    P2VVFoam( RooWorkspace&, RooAbsReal& , std::list<string>, int);
    ~P2VVFoam();

    void GenerateData( int );

    void FillFractions(RooDataSet);
    RooDataSet* GetDataSet();
    void UpdateSeed(int);

  protected:
    void Init();

  private:
    void ApplySettings(TFoam*, TRandom3*);
    vector<TFile*> m_files;
    vector<TFoam*> m_foamGens;
    int m_seed=0;
    RooDataSet* m_dataSet=nullptr; // The generated dataset
    
    RooWorkspace* m_ws=nullptr;
    RooTFoamBinding* m_binding=nullptr;
    vector<vector<string> > m_indexTrack;
    vector<vector<string> > m_combinations;
    vector<string> m_discrete;
    vector<string> m_continuous;
    vector<float> m_minima;
    vector<float> m_ranges;
    vector<float> m_fractions;
};

/*
 * This wouldn't recognise the init function in
 * the bindings so using cppyy instead
 */
// Wrap using boost
/*
BOOST_PYTHON_MODULE(pyP2VVFoam){
  class_<P2VVFoam>("pyP2VVFoam", no_init)//, init< >())
    .def(init<RooWorkspace&,RooSimultaneous&,vector<string>,int>())
    .add_property("GetDataSet",&P2VVFoam::GetDataSet)
    .def("GenerateData",&P2VVFoam::GenerateData);
}
*/
#endif

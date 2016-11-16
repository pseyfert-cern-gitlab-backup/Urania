
/***************************
 * FitterPulls                *
 *                         *
 * © 2004 Thomas Latham    *
 *    and Nicole Chevalier *
 ***************************/

// STL includes
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>    // std::min_element, std::max_element

// ROOT
#include "TArrow.h"
#include "TCanvas.h"
#include "TH2F.h"
#include "TKey.h"
#include "TMath.h"

// RooFit
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooHist.h"
#include "RooArgList.h"
#include "RooFitResult.h"
#include "RooGaussian.h"

// local include
#include "V0hhFitter/Exceptions.h"
#include "V0hhFitter/FitterPulls.h"

using namespace V0hhFit;

FitterPulls::FitterPulls() : 
    m_nBins(20),
    m_nVars(0),
    m_dataRes(0),
    m_dataNll(0)
{ 
}

FitterPulls::FitterPulls(const RooArgList& floatList) : 
    m_nBins(20),
    m_nVars(0),
    m_dataRes(0),
    m_dataNll(0)
{ 
    this->createVectors(floatList);
}

FitterPulls::FitterPulls(std::vector<std::string> files, std::string dataFitName, bool syst):
    m_nBins(20),
    m_nVars(0),
    m_dataRes(0),
    m_dataNll(0)
  
{
    std::vector<RooFitResult*> results;
    unsigned int nFits(0),nFailed(0);
    std::map<std::string,RooFitResult*> dataFits;
    RooFitResult *dataFit = NULL;
    if (syst)
    {
        TFile *temp = TFile::Open(files[0].c_str(),"READ");
        dataFit = (RooFitResult*) temp->Get(dataFitName.c_str());
        if (dataFit == NULL)
            throw GeneralException("FitterPulls::FitterPulls",
                    (("Did not find any data fit named "+ dataFitName).c_str()));
    }
    for (std::vector<std::string>::const_iterator itFiles = files.begin() ; itFiles != files.end() ; ++itFiles)
    {
        TFile *temp = TFile::Open(itFiles->c_str(),"READ");
        TList *listOfKeys = temp->GetListOfKeys();  
        if (listOfKeys == NULL)
            throw GeneralException("Fitter::findItem",
                    (std::string("No list of keys in the file ")+temp->GetName()).c_str());
        TIterator* it = listOfKeys->MakeIterator();
        TKey* key = NULL;
        unsigned int nFits_i(0), nFailed_i(0);
        while ((key = (TKey*) it->Next()) != NULL)
            if (std::string(key->GetClassName()) == "RooFitResult")
            {
                if ( std::string(key->ReadObj()->GetName()).find("FAILED") == std::string::npos && std::string(key->ReadObj()->GetName()).find("dataFit") == std::string::npos)
                {
                    results.push_back((RooFitResult*) key->ReadObj());
                    nFits_i++;
                }
                else if ( std::string(key->ReadObj()->GetName()).find("FAILED") != std::string::npos)
                    nFailed_i++;
                else if (std::string(key->ReadObj()->GetName()).find(dataFitName.c_str()) != std::string::npos)
                    m_dataRes = (RooFitResult*) key->ReadObj();
            }
        std::cout << "INFO: In " << *itFiles << ", nFits = " << nFits_i << " , nFailed = " << nFailed_i << "." << std::endl;
        temp->Close();
        nFits += nFits_i;
        nFailed += nFailed_i;
    }
    //OK now we got all of them.
    std::cout << "INFO: Nfits: " << nFits 
        << ". Nfailed: " << nFailed 
        << "(Convergency rate: " << (nFits*100.)/((double)nFits+nFailed) << "%)" 
        << std::endl;
    RooArgSet initParams = results[0]->floatParsInit();
    this->createVectors(initParams);
    for (std::vector<RooFitResult*>::const_iterator it = results.begin() ; it != results.end() ; ++it)
        if (!syst)
            this->fillVectors(*it);
        else		  
            this->fillVectors_Syst(dataFit,*it);
    //Filling m_constants.
    //Firstly we got to determine which parameters change.
    if (results.size() < 2)
        throw GeneralException("FitterPulls::FitterPulls","This constructor is only suited for 2 or more RooFitResults.");
    RooFitResult *res0 = results[0];
    RooFitResult *res1 = results[1];
    std::vector<int> indexes;
    std::vector<double> dummyVect;

    for (int i = 0 ; i < res0->constPars().getSize() ; i++)
    {
        RooRealVar* var0 = ((RooRealVar*) &(res0->constPars()[i]));
        RooRealVar* var1 = ((RooRealVar*) &(res1->constPars()[i]));
        // If the names differ, this indicates something unhealthy in your RFR:
        // they are not classified in the same order.
        if (std::string(var0->GetName()) != var1->GetName())
            std::cout << "WARNING: Different names: " << var0->GetName() << " " << var1->GetName() << std::endl;

        if (var0->getVal() != var1->getVal())
        {
            std::cout << "INFO: Adding " << var0->GetName() << " to the constant parameters whose values change over RFR. Index: " << i << "." << std::endl;
            indexes.push_back(i);
            m_constName.push_back(var0->GetName());
            m_constants.push_back(dummyVect);
        }
    }
    for (std::vector<RooFitResult*>::const_iterator it = results.begin() ; it != results.end() ; ++it)
    {
        unsigned int i = 0;
        for (std::vector<int>::iterator itIndex = indexes.begin() ; itIndex != indexes.end() ; ++itIndex)
        {				  
            double val = ((RooRealVar*) &((*it)->constPars()[*itIndex]))->getVal();
            m_constants[i].push_back(val);
            i++;
        }
    }  
}

FitterPulls::~FitterPulls()
{
    //if (m_dataRes) {
    //    delete m_dataRes; m_dataRes=0;
    //}
    std::vector<const RooFitResult*>::iterator iter = m_results.begin();
    const std::vector<const RooFitResult*>::const_iterator end = m_results.end();
    for (; iter != end; ++iter) {
        if ( *iter ){
            delete (*iter); *iter = 0;
        }
    }
}

void FitterPulls::createVectors(const RooArgList& floatList) 
{
    m_nVars = floatList.getSize();

    // get names of floating parameters
    for (Int_t i=0; i<m_nVars; ++i) {
        m_paramName.push_back( floatList[i].GetName() );
        std::vector<Double_t> dummyVect;
        m_errors.push_back(dummyVect);
        m_errorLo.push_back(dummyVect);
        m_errorHi.push_back(dummyVect);
        m_pulls.push_back(dummyVect);
        m_values.push_back(dummyVect);
        m_toyValues.push_back(dummyVect);
        m_residuals.push_back(dummyVect);
        m_toyResiduals.push_back(dummyVect);
        m_SystI.push_back(dummyVect);
        m_SystII.push_back(dummyVect);
    }
}

void FitterPulls::fillVectors(const RooFitResult* fitres) 
{  
    const RooArgList& initList  = fitres->floatParsInit();
    const RooArgList& floatList = fitres->floatParsFinal();

    Int_t size = floatList.getSize();

    if (size==0) {
        std::cerr << "ERROR in FitterPulls::fillVectors : No floating parameters in fit." << std::endl;
        return;
    }

    if (m_nVars == 0) {
        this->createVectors(floatList);
    }

    if (m_nVars != size) {
        std::cerr << "ERROR in FitterPulls::fillVectors : nVars_ of unexpected size: " << m_nVars << "." << std::endl;
        return;
    }

    for (Int_t j=0; j<size; ++j) {

        RooRealVar& var( dynamic_cast<RooRealVar&>(floatList[j]) );
        RooRealVar& varInit( dynamic_cast<RooRealVar&>(initList[j]) );

        m_values[j].push_back( var.getVal() );
        // calculate the residual
        Double_t residual = var.getVal()-varInit.getVal();
        m_residuals[j].push_back( residual );

        // Add systematics type I values
        //m_SystI[j].push_back( residual );

        // calculate the pull
        if (var.getAsymErrorHi() && var.getAsymErrorLo()){
            if (residual < 0) {
                m_pulls[j].push_back(residual/var.getAsymErrorHi());
            }  
            else {
                m_pulls[j].push_back(-residual/var.getAsymErrorLo());
            }
        }
        else if (var.getError())
        {
            m_pulls[j].push_back(residual/var.getError());
        }
        else {
            std::cerr << "ERROR in FitterPulls::fillVectors : All errors zero - cannot calculate pull." << std::endl;
            m_pulls[j].push_back(0);
        }
        m_errors[j].push_back(var.getError());
        if (var.getAsymErrorHi() && var.getAsymErrorLo())
        {
            m_errorLo[j].push_back(var.getAsymErrorLo());
            m_errorHi[j].push_back(var.getAsymErrorHi());
        }
        else
        {
            m_errorLo[j].push_back(-1.*var.getError());
            m_errorHi[j].push_back(var.getError());
        }
    }

    // also store the nll value,
    m_nlls.push_back(fitres->minNll());
    // the estimated distance to minimum,
    m_edm.push_back( fitres->edm() );
    // the fit status,
    m_status.push_back( fitres->status() );
    // and the MINUIT quality code of covariance matrix.
    m_covQual.push_back( fitres->covQual() );  

}

void FitterPulls::fillVectors(const RooArgSet* genParams, 
			  const RooArgSet*    toyParams, 
	    		  const RooFitResult* toyFitRes) 
{  
    const RooArgList& initList ( *genParams );
    const RooArgList& floatList = toyFitRes->floatParsFinal();

    Int_t size = floatList.getSize();

    if (size==0) {
        std::cerr << "ERROR in FitterPulls::fillVectors : No floating parameters in fit."
            << std::endl;
        return;
    }

    if (m_nVars == 0) {
        this->createVectors(floatList);
    }

    if (m_nVars != size) {
        std::cerr << "ERROR in FitterPulls::fillVectors : nVars_ of unexpected size: "
            << m_nVars << "." << std::endl;
        return;
    }

    for (Int_t j=0; j<size; ++j) {

        RooRealVar& var( dynamic_cast<RooRealVar&>(floatList[j]) );
        RooRealVar& varInit( dynamic_cast<RooRealVar&>(initList[j]) );

        m_values[j].push_back( var.getVal() );
        // calculate the residual
        Double_t residual = var.getVal()-varInit.getVal();
        m_residuals[j].push_back( residual );

        // Add systematics type I values
        m_SystI[j].push_back( residual );

        // calculate the pull
        if (var.getAsymErrorHi() && var.getAsymErrorLo()){
            m_errorLo[j].push_back(var.getAsymErrorLo());
            m_errorHi[j].push_back(var.getAsymErrorHi());
            if (residual < 0) 
                m_pulls[j].push_back(residual/var.getAsymErrorHi());
            else 
                m_pulls[j].push_back(-residual/var.getAsymErrorLo());
        }
        else if (var.getError())
        {
            m_errorLo[j].push_back(var.getAsymErrorLo());
            m_errorHi[j].push_back(var.getAsymErrorHi());
            m_pulls[j].push_back(residual/var.getError());
        }
        else {
            std::cerr << "ERROR in FitterPulls::fillVectors : All errors zero - cannot calculate pull." << std::endl;
            m_pulls[j].push_back(0);
        }
        m_errors[j].push_back(var.getError());
    }
    //Iteration for toyParams;
    if (toyParams != NULL)
    {
        const RooArgList& toyList = *toyParams;
        for (Int_t j=0; j<size; ++j) {
            RooRealVar& var( dynamic_cast<RooRealVar&>(floatList[j]) );
            RooRealVar& varToy( dynamic_cast<RooRealVar&>(toyList[j]) );
            m_toyValues[j].push_back(varToy.getVal());
            // calculate the residual
            Double_t toyResidual = var.getVal()-varToy.getVal();
            m_toyResiduals[j].push_back( toyResidual );
        }
    }

    // also store the nll value,
    m_nlls.push_back( toyFitRes->minNll() );
    // the estimated distance to minimum,
    m_edm.push_back( toyFitRes->edm() );
    // the fit status,
    m_status.push_back( toyFitRes->status() );
    // and the MINUIT quality code of covariance matrix.
    m_covQual.push_back( toyFitRes->covQual() );

}


//==================================================//
//     Fill vectors for Systematics studies         //
//==================================================//
void FitterPulls::createVectors_Syst(const RooArgList& floatList) 
{
    m_nVars = floatList.getSize();

    // get names of floating parameters
    for (Int_t i=0; i<m_nVars; ++i) {
        m_paramName.push_back( floatList[i].GetName() );
        std::vector<Double_t> dummyVect;
        m_SystI.push_back(dummyVect);
        m_SystII.push_back(dummyVect);
    }
}

//==================================================//
//     Fill vectors for Systematics studies II      //
//==================================================//
void FitterPulls::createVectors_SystII(std::vector<std::string> names) 
{
    m_nVars = names.size();
    // get names of floating parameters
    for (std::vector<std::string>::iterator it = names.begin() ; it != names.end() ; ++it)
    {
        m_paramName.push_back( it->c_str() );
        std::vector<Double_t> dummyVect;
        m_SystII.push_back(dummyVect);
    }
}

void FitterPulls::fillVectors_Syst(const RooFitResult* fitres_official, const RooFitResult* fitres_toyMC) 
{  

    // Benchmark fit init/results
    //const RooArgList& initList_i  = fitres_official->floatParsInit();
    const RooArgList& floatList_i = fitres_official->floatParsFinal();
    // Toy MC fit init/results
    //const RooArgList& initList_f  = fitres_toyMC->floatParsInit();
    const RooArgList& floatList_f = fitres_toyMC->floatParsFinal();

    Int_t size = floatList_f.getSize();

    if (size==0) {
        std::cerr << "ERROR in FitterPulls::fillVectors : No floating parameters in fit." << std::endl;
        return;
    }

    if (m_nVars == 0) {
        this->createVectors_Syst(floatList_f);
    }

    if (m_nVars != size) {
        std::cerr << "ERROR in FitterPulls::fillVectors : m_nVars of unexpected size: " << m_nVars << "." << std::endl;
        return;
    }

    for (Int_t j=0; j<size; ++j) {

        RooRealVar& varFit_i( dynamic_cast<RooRealVar&>(floatList_i[j]) );
        RooRealVar& varFit_f( dynamic_cast<RooRealVar&>(floatList_f[j]) );

        // calculate the difference between fit results and Toy MC one
        Double_t diff_results = varFit_i.getVal()-varFit_f.getVal();
        // Add systematics values
        m_SystI[j].push_back( diff_results );
        m_SystII[j].push_back( diff_results );

    }
}

void FitterPulls::fillVectors_SystII(std::vector<std::string> files)
{
    std::vector<std::pair<RooFitResult*,RooFitResult*> > results;

    for (std::vector<std::string>::const_iterator itFiles = files.begin() ; itFiles != files.end() ; ++itFiles)
    {
        TFile *temp = TFile::Open(itFiles->c_str(),"READ");
        TList *listOfKeys = temp->GetListOfKeys();  
        std::vector<RooFitResult*> results_official;
        if (listOfKeys == NULL)
        {
            //Throw some exception
            assert(0);
        }
        TIterator* it = listOfKeys->MakeIterator();
        TKey* key = NULL;
        while ((key = (TKey*) it->Next()) != NULL)
            if (std::string(key->GetClassName()) == "RooFitResult")
                if (std::string(key->ReadObj()->GetName()).find("FAILED") == std::string::npos &&
                        std::string(key->ReadObj()->GetName()).find("Official") != std::string::npos)
                    results_official.push_back((RooFitResult*) key->ReadObj());
        for (std::vector<RooFitResult*>::iterator itRes = results_official.begin() ; itRes != results_official.end() ; itRes++)
        {
            std::string benchName = TString(((*itRes)->GetName())).ReplaceAll("Official","BenchMark").Data();
            if  (((RooFitResult*) temp->Get(benchName.c_str())) != NULL)
                results.push_back(std::make_pair(*itRes,(RooFitResult*) temp->Get(benchName.c_str())));
        }		  		  
        temp->Close();
    }
    std::cout << "INFO: We managed to get " << results.size() << " pairs of results." << std::endl;
    //OK now we got all of them.
    for (std::vector<std::pair<RooFitResult*,RooFitResult*> >::const_iterator it = results.begin() ; it != results.end() ; ++it)
        this->fillVectors_SystII(it->first,it->second);
}

void FitterPulls::fillVectors_SystII(const RooFitResult* fitres_official, const RooFitResult* fitres_toyMC) 
{  
    // Benchmark fit init/results
    //const RooArgList& initList_i  = fitres_official->floatParsInit();
    const RooArgList& floatList_i = fitres_official->floatParsFinal();
    // Toy MC fit init/results
    //const RooArgList& initList_f  = fitres_toyMC->floatParsInit();
    const RooArgList& floatList_f = fitres_toyMC->floatParsFinal();

    Int_t sizeI = floatList_i.getSize();
    Int_t sizeF = floatList_f.getSize();

    if (sizeI==0) {
        std::cerr << "ERROR in FitterPulls::fillVectors : No floating parameters in fit." << std::endl;
        return;
    }

    if (sizeF==0) {
        std::cerr << "ERROR in FitterPulls::fillVectors : No floating parameters in fit." << std::endl;
        return;
    }

    std::vector<std::string> names;
    for (Int_t i=0; i<sizeI; ++i)
        for (Int_t j=0; j<sizeF; ++j)
            if (std::string(floatList_i[i].GetName()) == std::string(floatList_f[j].GetName()))
                names.push_back(floatList_i[i].GetName());	

    if (m_nVars == 0) {
        this->createVectors_SystII(names);
    }


    unsigned int i=0;
    for (std::vector<std::string>::iterator itStr = names.begin() ; itStr != names.end() ; ++itStr)
    {
        RooRealVar& varFit_i( dynamic_cast<RooRealVar&>(floatList_i[floatList_i.index(itStr->c_str())]) );
        RooRealVar& varFit_f( dynamic_cast<RooRealVar&>(floatList_f[floatList_f.index(itStr->c_str())]) );
        // calculate the difference between fit results and Toy MC one
        Double_t diff_results = varFit_i.getVal()-varFit_f.getVal();
        // Add systematics type II values
        m_SystII[i].push_back( diff_results );			
        i++;
    }
}

void FitterPulls::writeVectors(TString fileName) const
{
    std::cout << "Writing pull results to " << fileName << "..." << std::flush;

    // create output stream
    std::ofstream outFile(fileName, std::ios::out);
    if (!outFile) {
        std::cerr << "ERROR in FitterPulls::writeVectors : Cannot open file \"" << fileName << "\"." << std::endl;
        std::exit(1);
    }

    for (Int_t i=0; i<m_nVars; ++i) {
        // write the variables name
        TString name = m_paramName[i];
        outFile << name << " ";

        // iterate through the pulls and write them to the stream
        std::vector<Double_t>::const_iterator iter = m_pulls[i].begin();
        const std::vector<Double_t>::const_iterator end = m_pulls[i].end();

        for (; iter != end; ++iter) {
            outFile << (*iter) << " ";
        }
        outFile << std::endl;
    }
    outFile.close();

    std::cout << " done." << std::endl;

}

void FitterPulls::plotPulls(TString filename, Int_t nCores, Double_t plotLimit, Double_t fitLimit ) const
{
    TCanvas* c1 = new TCanvas("c1","Pull Plots" );

    for (Int_t i=0; i<m_nVars; ++i) {

        std::cout << m_paramName[i] << std::endl;

        // create dataset to store the pulls
        TString title(m_paramName[i]);
        title += " Pull";
        RooRealVar pull( "pull", title, -fitLimit, fitLimit );
        RooDataSet pulls( "pulls", title, pull );

        // iterate through the pulls and add them into the dataset
        std::vector<Double_t>::const_iterator iter = m_pulls[i].begin();
        const std::vector<Double_t>::const_iterator end = m_pulls[i].end();
        for (; iter != end; ++iter) {
            if ((*iter) >= -fitLimit && (*iter) <= fitLimit) {
                pull.setVal(*iter);
                pulls.add(pull);
            }
        }

        // create a gaussian pdf
        RooRealVar mean("mean","Pull Gaussian Mean", 0.0, -fitLimit, fitLimit );
        RooRealVar sigma("sigma","Pull Gaussian Sigma",1.0,0.0,2.0*fitLimit );
        RooGaussian gauss("gauss","Pull Gaussian", pull, mean, sigma );

        // fit it to the pull data
        gauss.fitTo( pulls, RooFit::NumCPU( nCores ), RooFit::PrintLevel(-1) );
        //	std::cout << "NO FIT << std::endl;

        // make an empty plot
        RooPlot* plot = pull.frame(-plotLimit,plotLimit);
        plot->SetTitle(title);

        // plot the pulls and the gaussian
        pulls.plotOn( plot, RooFit::Binning(m_nBins) );
        gauss.plotOn( plot );
        gauss.paramOn( plot, RooFit::Parameters( RooArgSet(mean, sigma) ),
                RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.92 ) );

        // draw the plot
        c1->cd();
        plot->Draw();
        plot->SetMinimum(1e-1);

        // save canvas to file
        TString fileName( m_paramName[i] );
        fileName += "_";  fileName += filename;
        c1->SaveAs( fileName + ".png");
    }
    delete c1; c1=0;
}

void FitterPulls::plotPulls_DP(TString filename, Int_t nCores, Double_t plotLimit, Double_t fitLimit ) const
{
    TCanvas* c1 = new TCanvas("c1","Pull Plots" );

    for (Int_t i=0; i<m_nVars; ++i) {

        std::cout << m_paramName[i] << std::endl;

        // create dataset to store the pulls
        TString title(m_paramName[i]);
	if (title.Contains("mu")){
	    title.ReplaceAll("Bd2KSpipiDD_2011_pdf_mu","#it{B^{0}#rightarrow}#it{K}^{0}_{S}#it{h^{+}h^{#font[122]{-}}} #mu");
	    title.ReplaceAll("Bs2KSpipiDD_2011_pdf_mu","#it{B^{0}_{s}#rightarrow}#it{K}^{0}_{S}#it{h^{+}h^{#font[122]{-}}} #mu");
	}
	if (title.Contains("sigma")){
	    title.ReplaceAll("Bd2KSpipiDD_2011_pdf_sigma","#it{B^{0}#rightarrow}#it{K}^{0}_{S}#it{h^{+}h^{#font[122]{-}}} DD #sigma");
	    title.ReplaceAll("Bd2KSpipiLL_2011_pdf_sigma","#it{B^{0}#rightarrow}#it{K}^{0}_{S}#it{h^{+}h^{#font[122]{-}}} LL #sigma");
	    title.ReplaceAll("Bs2KSpipiDD_2011_pdf_sigma","#it{B^{0}_{s}#rightarrow}#it{K}^{0}_{S}#it{h^{+}h^{#font[122]{-}}} DD #sigma");
	    title.ReplaceAll("Bs2KSpipiLL_2011_pdf_sigma","#it{B^{0}_{s}#rightarrow}#it{K}^{0}_{S}#it{h^{+}h^{#font[122]{-}}} LL #sigma");
	}
	if (title.Contains("width")){
	    title.ReplaceAll("ratio_width_", "Ratio width ");
	}
	
	title.ReplaceAll("Bd2KSpipi","#it{B^{0}#rightarrow}#it{K}^{0}_{S}#it{#pi^{+}#pi^{#font[122]{-}}}"); 
	title.ReplaceAll("Bs2KSpipi","#it{B^{0}_{s}#rightarrow}#it{K}^{0}_{S}#it{#pi^{+}#pi^{#font[122]{-}}}"); 
	title.ReplaceAll("Bd2KSKK","#it{B^{0}#rightarrow}#it{K}^{0}_{S}#it{K^{+}K^{#font[122]{-}}}"); 
	title.ReplaceAll("Bs2KSKK","#it{B^{0}_{s}#rightarrow}#it{K}^{0}_{S}#it{K^{+}K^{#font[122]{-}}}"); 
	title.ReplaceAll("Bd2KSKpi","#it{B^{0}#rightarrow}#it{K}^{0}_{S}#it{K^{+}#pi^{#font[122]{-}}}"); 
	title.ReplaceAll("Bs2KSKpi","#it{B^{0}_{s}#rightarrow}#it{K}^{0}_{S}#it{K^{+}#pi^{#font[122]{-}}}"); 
	title.ReplaceAll("Bd2KSpiK","#it{B^{0}#rightarrow}#it{K}^{0}_{S}#it{#pi^{+}K^{#font[122]{-}}}"); 
	title.ReplaceAll("Bs2KSpiK","#it{B^{0}_{s}#rightarrow}#it{K}^{0}_{S}#it{#pi^{+}K^{#font[122]{-}}}"); 
	title.ReplaceAll("_pdf_KSpipiDD_2011_"," "); title.ReplaceAll("_pdf_KSpipiDD_2012a_"," "); title.ReplaceAll("_pdf_KSpipiDD_2012b_"," ");
	title.ReplaceAll("_pdf_KSpipiLL_2011_"," "); title.ReplaceAll("_pdf_KSpipiLL_2012a_"," "); title.ReplaceAll("_pdf_KSpipiLL_2012b_"," ");
	title.ReplaceAll("_pdf_KSKKDD_2011_"," "); title.ReplaceAll("_pdf_KSKKDD_2012a_"," "); title.ReplaceAll("_pdf_KSKKDD_2012b_"," ");
	title.ReplaceAll("_pdf_KSKKLL_2011_"," "); title.ReplaceAll("_pdf_KSKKLL_2012a_"," "); title.ReplaceAll("_pdf_KSKKLL_2012b_"," ");
	title.ReplaceAll("_pdf_KSKpiDD_2011_"," "); title.ReplaceAll("_pdf_KSKpiDD_2012a_"," "); title.ReplaceAll("_pdf_KSKpiDD_2012b_"," ");
	title.ReplaceAll("_pdf_KSKpiLL_2011_"," "); title.ReplaceAll("_pdf_KSKpiLL_2012a_"," "); title.ReplaceAll("_pdf_KSKpiLL_2012b_"," ");
	title.ReplaceAll("_pdf_KSpiKDD_2011_"," "); title.ReplaceAll("_pdf_KSpiKDD_2012a_"," "); title.ReplaceAll("_pdf_KSpiKDD_2012b_"," ");
	title.ReplaceAll("_pdf_KSpiKLL_2011_"," "); title.ReplaceAll("_pdf_KSpiKLL_2012a_"," "); title.ReplaceAll("_pdf_KSpiKLL_2012b_"," ");
	title.ReplaceAll("DD_"," DD "); title.ReplaceAll("LL_"," LL ");

	// Combinatorics
	title.ReplaceAll("combinatoric_KSpipi", "Comb #it{K}^{0}_{S}#it{#pi^{+}#pi^{#font[122]{-}}}");
	title.ReplaceAll("combinatoric_KSKK", "Comb #it{K}^{0}_{S}#it{K^{+}K^{#font[122]{-}}}");
	title.ReplaceAll("combinatoric_KSKpi", "Comb #it{K}^{0}_{S}#it{K^{+}#pi^{#font[122]{-}}}");
	title.ReplaceAll("combinatoric_KSpiK", "Comb #it{K}^{0}_{S}#it{#pi^{+}K^{#font[122]{-}}}");
	title.ReplaceAll("ratio_combinatoric_2011","Ratio Comb 2011");
	title.ReplaceAll("ratio_combinatoric_2012a","Ratio Comb 2012a");
	title.ReplaceAll("ratio_combinatoric_2012b","Ratio Comb 2012b");
	
	// Add final name
        title += " Pull";
        RooRealVar pull( "pull", title, -fitLimit, fitLimit );
        RooDataSet pulls( "pulls", title, pull );

        // iterate through the pulls and add them into the dataset
        std::vector<Double_t>::const_iterator iter = m_pulls[i].begin();
        const std::vector<Double_t>::const_iterator end = m_pulls[i].end();
        for (; iter != end; ++iter) {
            if ((*iter) >= -fitLimit && (*iter) <= fitLimit) {
                pull.setVal(*iter);
                pulls.add(pull);
            }
        }

        // create a gaussian pdf
        RooRealVar mean("mean","Pull Gaussian Mean", 0.0, -fitLimit, fitLimit );
        RooRealVar sigma("sigma","Pull Gaussian Sigma",1.0,0.0,2.0*fitLimit );
        RooGaussian gauss("gauss","Pull Gaussian", pull, mean, sigma );

        // fit it to the pull data
        gauss.fitTo( pulls, RooFit::NumCPU( nCores ) );

        // make an empty plot
        RooPlot* plot = pull.frame(-plotLimit,plotLimit);
        plot->SetTitle(title);

        // plot the pulls and the gaussian
        pulls.plotOn( plot, RooFit::Binning(m_nBins) );
        gauss.plotOn( plot );
        gauss.paramOn( plot, RooFit::Parameters( RooArgSet(mean, sigma) ),
                RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.92 ) );

        // draw the plot
        c1->cd();
        plot->Draw();
        plot->SetMinimum(1e-1);

        // save canvas to file
        TString fileName( m_paramName[i] );
        fileName += "_";  fileName += filename;
        c1->SaveAs( fileName + ".eps" );
        c1->SaveAs( fileName + ".pdf");
    }

    delete c1; c1=0;
}

void FitterPulls::plotConstant(TString dir, TString filename, Int_t nCores) const
{
    TCanvas* c1 = new TCanvas("c1","Pull Plots" );
    Int_t compNameSize = m_constName.size();
    for (Int_t i=0; i<compNameSize; ++i) {
        TArrow *arrow(0);
        // create dataset to store the pulls
        double minVal = *std::min_element( m_constants[i].begin(), m_constants[i].end() );
        double maxVal = *std::max_element( m_constants[i].begin(), m_constants[i].end() );
        TString title(m_constName[i]);
        title += " values";
        RooRealVar pull( "value", title, minVal, maxVal );
        RooDataSet pulls( "values", title, pull );

        // iterate through the pulls and add them into the dataset
        std::vector<Double_t>::const_iterator iter = m_constants[i].begin();
        const std::vector<Double_t>::const_iterator end = m_constants[i].end();
        for (; iter != end; ++iter) {
            if ((*iter) >= minVal && (*iter) <= maxVal) {
                pull.setVal(*iter);
                pulls.add(pull);
            }
        }

        // create a gaussian pdf
        RooRealVar mean("mean","Pull Gaussian Mean",0.5*(maxVal+minVal),minVal,maxVal);		
        RooRealVar sigma("sigma","Pull Gaussian Sigma",0.5*(maxVal-minVal),0.,maxVal-minVal);
        RooGaussian gauss("gauss","Pull Gaussian", pull, mean, sigma );

        // fit it to the pull data
        gauss.fitTo( pulls, RooFit::NumCPU( nCores ), RooFit::PrintLevel(-1) );

        // make an empty plot
        RooPlot* plot = pull.frame(minVal,maxVal);

        plot->SetTitle(title);

        // plot the pulls and the gaussian
        pulls.plotOn( plot, RooFit::Binning(m_nBins) );
        gauss.plotOn( plot );
        gauss.paramOn( plot, RooFit::Parameters( RooArgSet(mean, sigma) ),
                RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.92 ) );

        // draw the plot
        c1->cd();
        RooHist* hist = dynamic_cast<RooHist*>( plot->getObject(0) );
        Double_t arrowTop = 0.4 * hist->getYAxisMax();
        RooArgList dataConst = m_dataRes->constPars();		
        double v = ((RooRealVar*) &dataConst[dataConst.index(m_constName[i].Data())])->getVal();
        arrow = new TArrow( v, arrowTop, v, 0, 0.05, ">" ) ;
        arrow->SetFillColor(2);
        arrow->SetLineColor(2);
        arrow->SetLineWidth(2);
        arrow->SetFillStyle(1001);
        plot->addObject(arrow);
        plot->Draw();
        plot->SetMinimum(1e-1);

        // save canvas to file
        TString fileName( dir+m_constName[i] );
        fileName += "_";  fileName += filename;
        c1->SaveAs( fileName + ".png");
        delete arrow; arrow = 0;
    }
    delete c1; c1=0;
}

void FitterPulls::plotNlls(TString filename) const
{
    // create a canvas
    TCanvas* canvas = new TCanvas("nlls","Minimum Negative Log Likelihood" );

    // check that there are nlls to plot
    if (!m_nlls.size())
    {
        std::cerr << "ERROR in FitterPulls::plotNlls : Vectors not yet filled." << std::endl;
        return;
    }

    // make the title
    TString title = "Minimum Negative Log Likelihood";

    // create the variable setting the extreme values.
    RooRealVar nll("nll", title, *std::min_element( m_nlls.begin(), m_nlls.end() ), *std::max_element( m_nlls.begin(), m_nlls.end() ) );

    // now create the empty dataset
    RooDataSet nlls("nlls", title, RooArgSet( nll ) );

    // iterate again through the nlls and add them into the dataset
    std::vector< Double_t >::const_iterator iter = m_nlls.begin();
    const std::vector< Double_t >::const_iterator enditer = m_nlls.end();
    for (; iter != enditer; ++iter) {
        std::cout << *iter << std::endl;
        nll.setVal( (*iter) );
        nlls.add( RooArgSet( nll ) );
    }

    // create a gaussian pdf
    RooRealVar mean( "mean", "Nll Gaussian Mean", nlls.meanVar( nll )->getVal(), nll.getMin(), nll.getMax() );
    RooRealVar sigma( "sigma", "Nll Gaussian Sigma", nlls.rmsVar( nll )->getVal(), 0.0, nll.getMax()-nll.getMin() );
    RooGaussian gauss( "gauss", "Nll Gaussian", nll, mean, sigma );

    // make an empty plot
    std::cout << "Plot created" << std::endl;
    RooPlot* plot = nll.frame();
    // plot the nlls and the gaussian
    nlls.plotOn( plot, RooFit::Binning(m_nBins) );

    // draw the plot
    plot->Draw();
    plot->SetMinimum(1e-1);

    // save canvas to file
    canvas->SaveAs(filename + ".eps");
    canvas->SaveAs(filename + ".pdf");
    canvas->SaveAs(filename + ".png");

    delete canvas; canvas = 0;
}

void FitterPulls::plotEdms(TString filename) const
{
    // create a canvas
    TCanvas* canvas = new TCanvas("Edms","Estimated distance to minimum" );

    // check that there are nlls to plot
    if (!m_edm.size())
    {
        std::cerr << "ERROR in FitterPulls::plotEdms : Vectors not yet filled." << std::endl;
        return;
    }

    // make the title
    TString title = "Estimated distance to minimum";

    // create the variable setting the extreme values.
    RooRealVar edm("edm", title, *std::min_element( m_edm.begin(), m_edm.end() ), *std::max_element( m_edm.begin(), m_edm.end() ) );

    // now create the empty dataset
    RooDataSet edms("edms", title, RooArgSet( edm ) );

    // iterate again through the edms and add them into the dataset
    std::vector< Double_t >::const_iterator iter = m_edm.begin();
    const std::vector< Double_t >::const_iterator enditer = m_edm.end();
    for (; iter != enditer; ++iter) {
        edm.setVal( (*iter) );
        edms.add( RooArgSet( edm ) );
    }

    // make an empty plot
    RooPlot* plot = edm.frame();
    //plot->SetTitle("");
    // plot the nlls and the gaussian
    edms.plotOn( plot, RooFit::Binning(m_nBins) );
    // draw the plot
    plot->Draw();
    plot->SetMinimum(1e-1);

    // save canvas to file
    canvas->SaveAs(filename + ".eps");
    canvas->SaveAs(filename + ".pdf");
    canvas->SaveAs(filename + ".png");

    delete canvas; canvas = 0;
}

void FitterPulls::plotErrorVsResiduals(TString dir, TString filename) const
{
    // create a canvas
    TCanvas* canvas = new TCanvas( "values", "Minimum Negative Log Likelihood" );
    std::vector<double> err;
    for (Int_t i=0; i<m_nVars; ++i) {    
        std::cout << m_paramName[i] << std::endl;
        //Create the error vector
        double minErrLo = -(*std::min_element( m_errorLo[i].begin(), m_errorLo[i].end() ));
        double maxErrLo = -(*std::max_element( m_errorLo[i].begin(), m_errorLo[i].end() ));
        double minErrHi = +(*std::min_element( m_errorHi[i].begin(), m_errorHi[i].end() ));
        double maxErrHi = +(*std::max_element( m_errorHi[i].begin(), m_errorHi[i].end() ));
        TH2F *hist = NULL;
        if (minErrLo != maxErrLo) //Asym error filled
        {
            hist = new TH2F("hist","hist",
                    30,
                    *std::min_element( m_residuals[i].begin(), m_residuals[i].end() ),
                    *std::max_element( m_residuals[i].begin(), m_residuals[i].end() ),
                    30,
                    (minErrLo < minErrHi) ? minErrLo : minErrHi,
                    (maxErrLo < maxErrHi) ? maxErrLo : maxErrHi			  
                    );
            for (unsigned int j = 0 ; j < m_values[i].size() ;  j++)
            {
                if (m_residuals[i][j] < 0)	  
                    hist->Fill(m_residuals[i][j],m_errorHi[i][j]);
                else
                    hist->Fill(m_residuals[i][j],-m_errorLo[i][j]);
            }
        }
        else
        {
            hist = new TH2F("hist","hist",
                    30,
                    *std::min_element( m_residuals[i].begin(), m_residuals[i].end() ),
                    *std::max_element( m_residuals[i].begin(), m_residuals[i].end() ),
                    30,
                    *std::min_element( m_errors[i].begin(), m_errors[i].end() ),
                    *std::max_element( m_errors[i].begin(), m_errors[i].end() )
                    );
            for (unsigned int j = 0 ; j < m_values[i].size() ;  j++)
                hist->Fill(m_residuals[i][j],m_errors[i][j]);
        }
        canvas->cd();
        hist->Draw("colz");

        // save canvas to file
        TString fileName( dir+filename+m_paramName[i] );
        canvas->SaveAs( fileName + ".png");
        delete hist;
    }
}

void FitterPulls::plotValues(TString dir, TString filename, Int_t nCores) const
{
    // create a canvas
    TCanvas* canvas = new TCanvas( "values", "Minimum Negative Log Likelihood" );

    for (Int_t i=0; i<m_nVars; ++i) {

        std::cout << m_paramName[i] << std::endl;

        // create dataset to store the pulls
        TString title(m_paramName[i]);
        title += " Value";

        // check that there are nlls to plot
        if (!m_values.size())
        {
            std::cerr << "ERROR in FitterPulls::plotValues : Vectors not yet filled." << std::endl;
            return;
        }

        // make the title

        // create the variable setting the extreme values.
        RooRealVar value("value", title, *std::min_element( m_values[i].begin(), m_values[i].end() ), *std::max_element( m_values[i].begin(), m_values[i].end() ) );

        // now create the empty dataset
        RooDataSet values("values", title, RooArgSet( value ) );

        // iterate again through the nlls and add them into the dataset
        std::vector< Double_t >::const_iterator iter = m_values[i].begin();
        const std::vector< Double_t >::const_iterator enditer = m_values[i].end();
        for (; iter != enditer; ++iter) {
            value.setVal( (*iter) );
            values.add( RooArgSet( value ) );
        }

        // create a gaussian pdf
        RooRealVar mean( "mean", "Value Gaussian Mean", values.meanVar( value )->getVal(), value.getMin(), value.getMax() );
        RooRealVar sigma( "sigma", "Value Gaussian Sigma", values.rmsVar( value )->getVal(), 0.0, value.getMax() - value.getMin());
        RooGaussian gauss( "gauss", "Value Gaussian", value, mean, sigma );

        // fit it to the nll data
        gauss.fitTo( values, RooFit::NumCPU( nCores ), RooFit::PrintLevel(-1) );

        // make an empty plot
        RooPlot* plot = value.frame();
        //plot->SetTitle("");
        // plot the nlls and the gaussian
        values.plotOn( plot, RooFit::Binning(m_nBins) );
        RooHist* hist = dynamic_cast<RooHist*>( plot->getObject(0) );
        Double_t arrowTop = 0.4 * hist->getYAxisMax();
        gauss.plotOn( plot );

        // add an arrow for the data value
        // (DON'T DELETE the arrow because the RooPlot destructor does it for you)
        TArrow *arrow(0);
        RooRealVar* var(0);
        //RooRealVar* measured(0);
        if (m_dataRes)
        {
            double v(0.);
            RooFIter paramIter = m_dataRes->floatParsFinal().fwdIterator();
            while ( (var = dynamic_cast<RooRealVar*>( paramIter.next() ) ) ) {
                std::string name = var->GetName();
                std::string classname = var->ClassName();
                if (classname!="RooRealVar") {
                    continue; 
                }
                if( TString( var->GetName() ) == m_paramName[i] ) {
                    v = var->getVal();
                    //measured = dynamic_cast<RooRealVar*>( var->Clone("meas") );
                    break;
                }
            }
            arrow = new TArrow( v, arrowTop, v, 0, 0.05, ">" ) ;
            arrow->SetFillColor(2);
            arrow->SetLineColor(2);
            arrow->SetLineWidth(2);
            arrow->SetFillStyle(1001);
            plot->addObject(arrow);
        }

        gauss.paramOn( plot, RooFit::Parameters( RooArgSet(  mean, sigma ) ),
                RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.92 ) );

        // draw the plot
        canvas->cd();
        plot->Draw();
        plot->SetMinimum(1e-1);

        // save canvas to file
        TString fileName( dir+filename+m_paramName[i]);
        fileName += "_";  fileName += filename;
        canvas->SaveAs( fileName + ".eps" );
        canvas->SaveAs( fileName + ".pdf" );
        canvas->SaveAs( fileName + ".png" );

        if(arrow)
            delete arrow; 
        arrow = 0;
        // draw the plot
    }

    delete canvas; canvas = 0;

}

void FitterPulls::plotValues(TString filename, Int_t nCores) const
{
    // create a canvas
    TCanvas* canvas = new TCanvas( "values", "Minimum Negative Log Likelihood" );

    for (Int_t i=0; i<m_nVars; ++i) {

        std::cout << m_paramName[i] << std::endl;

        // create dataset to store the pulls
        TString title(m_paramName[i]);
        title += " Value";

        // check that there are nlls to plot
        if (!m_values.size())
        {
            std::cerr << "ERROR in FitterPulls::plotValues : Vectors not yet filled." << std::endl;
            return;
        }

        // make the title

        // create the variable setting the extreme values.
        RooRealVar value("value", title, *std::min_element( m_values[i].begin(), m_values[i].end() ), *std::max_element( m_values[i].begin(), m_values[i].end() ) );

        // now create the empty dataset
        RooDataSet values("values", title, RooArgSet( value ) );

        // iterate again through the nlls and add them into the dataset
        std::vector< Double_t >::const_iterator iter = m_values[i].begin();
        const std::vector< Double_t >::const_iterator enditer = m_values[i].end();
        for (; iter != enditer; ++iter) {
            value.setVal( (*iter) );
            values.add( RooArgSet( value ) );
        }

        // create a gaussian pdf
        RooRealVar mean( "mean", "Value Gaussian Mean", values.meanVar( value )->getVal(), value.getMin(), value.getMax() );
        RooRealVar sigma( "sigma", "Value Gaussian Sigma", values.rmsVar( value )->getVal(), 0.0, value.getMax() - value.getMin());
        RooGaussian gauss( "gauss", "Value Gaussian", value, mean, sigma );

        // fit it to the nll data
        gauss.fitTo( values, RooFit::NumCPU( nCores ), RooFit::PrintLevel(-1) );

        // make an empty plot
        RooPlot* plot = value.frame();
        //plot->SetTitle("");
        // plot the nlls and the gaussian
        values.plotOn( plot, RooFit::Binning(m_nBins) );
        RooHist* hist = dynamic_cast<RooHist*>( plot->getObject(0) );
        Double_t arrowTop = 0.4 * hist->getYAxisMax();
        gauss.plotOn( plot );

        // add an arrow for the data value
        // (DON'T DELETE the arrow because the RooPlot destructor does it for you)
        TArrow *arrow(0);
        RooRealVar* var(0);
        //RooRealVar* measured(0);
        if (m_dataRes)
        {
            double v(0.);
            RooFIter paramIter = m_dataRes->floatParsFinal().fwdIterator();
            while ( (var = dynamic_cast<RooRealVar*>( paramIter.next() ) ) ) {
                std::string name = var->GetName();
                std::string classname = var->ClassName();
                if (classname!="RooRealVar") {
                    continue; 
                }
                if( TString( var->GetName() ) == m_paramName[i] ) {
                    v = var->getVal();
                    //measured = dynamic_cast<RooRealVar*>( var->Clone("meas") );
                    break;
                }
            }
            arrow = new TArrow( v, arrowTop, v, 0, 0.05, ">" ) ;
            arrow->SetFillColor(2);
            arrow->SetLineColor(2);
            arrow->SetLineWidth(2);
            arrow->SetFillStyle(1001);
            plot->addObject(arrow);
        }

        gauss.paramOn( plot, RooFit::Parameters( RooArgSet(  mean, sigma ) ),
                RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.92 ) );

        // It would be cool if we could just add the actual measured value numbers so central and error,
        // but I really cant be bothered so this measured variable is actually pointless right now :(
        //delete measured; measured = 0;
        // draw the plot
        canvas->cd();
        plot->Draw();
        plot->SetMinimum(1e-1);

        // save canvas to file

        TString fileName( m_paramName[i] );
        fileName += "_";  fileName += filename;
        canvas->SaveAs( fileName + ".eps" );
        canvas->SaveAs( fileName + ".pdf");
        canvas->SaveAs( fileName + ".png");

        if(arrow)
            delete arrow; 
        arrow = 0;
        // draw the plot
    }

    delete canvas; canvas = 0;

}

void FitterPulls::plotResiduals( TString filename, Int_t nCores ) const
{
    // create a canvas
    TCanvas* canvas = new TCanvas( "residuals", "Minimum Negative Log Likelihood" );
    for (Int_t i=0; i<m_nVars; ++i) {

        std::cout << m_paramName[i] << " " << *std::max_element( m_residuals[i].begin(), m_residuals[i].end() ) << std::endl;

        // create dataset to store the pulls
        TString title(m_paramName[i]);
        title += " Value";

        // check that there are nlls to plot
        if (!m_residuals.size())
        {
            std::cerr << "ERROR in FitterPulls::plotValues : Vectors not yet filled." << std::endl;
            return;
        }

        // make the title

        // create the variable setting the extreme values.
        RooRealVar value("value", title,1.*(*std::min_element( m_residuals[i].begin(), m_residuals[i].end() )),1.*(*std::max_element( m_residuals[i].begin(), m_residuals[i].end() )) );

        // now create the empty dataset
        RooDataSet values("values", title, RooArgSet( value ) );

        // iterate again through the nlls and add them into the dataset
        std::vector< Double_t >::const_iterator iter = m_residuals[i].begin();
        const std::vector< Double_t >::const_iterator enditer = m_residuals[i].end();
        for (; iter != enditer; ++iter) {
            value.setVal( (*iter) );
            values.add( RooArgSet( value ) );
        }

        // create a gaussian pdf
        RooRealVar mean( "mean", "Value Gaussian Mean", values.meanVar( value )->getVal(), value.getMin(), value.getMax() );
        RooRealVar sigma( "sigma", "Value Gaussian Sigma", values.rmsVar( value )->getVal(), 0.0, value.getMax() - value.getMin());
        RooGaussian gauss( "gauss", "Value Gaussian", value, mean, sigma );

        // fit it to the nll data
        gauss.fitTo( values, RooFit::NumCPU( nCores ), RooFit::PrintLevel(-1));

        // make an empty plot
        RooPlot* plot = value.frame();
        //plot->SetTitle("");
        // plot the nlls and the gaussian
        values.plotOn( plot, RooFit::Binning(m_nBins) );
        RooHist* hist = dynamic_cast<RooHist*>( plot->getObject(0) );
        Double_t arrowTop = 0.4 * hist->getYAxisMax();
        gauss.plotOn( plot );

        // add an arrow for the data value
        // (DON'T DELETE the arrow because the RooPlot destructor does it for you)
        TArrow *arrow(0);
        RooRealVar* var(0);
        if (m_dataRes)
        {
            double v(0.);
            RooFIter paramIter = m_dataRes->floatParsFinal().fwdIterator();
            while ( (var = dynamic_cast<RooRealVar*>( paramIter.next() ) ) ) {
                std::string name = var->GetName();
                std::string classname = var->ClassName();
                if (classname!="RooRealVar") {
                    continue; 
                }
                if( TString( var->GetName() ) == m_paramName[i] ) {
                    v = var->getVal();
                    break;
                }
            }
            arrow = new TArrow( v, arrowTop, v, 0, 0.05, ">" ) ;
            arrow->SetFillColor(2);
            arrow->SetLineColor(2);
            arrow->SetLineWidth(2);
            arrow->SetFillStyle(1001);
            plot->addObject(arrow);
        }

        gauss.paramOn( plot, RooFit::Parameters( RooArgSet(  mean, sigma ) ),
                RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.92 ) );

        // draw the plot
        canvas->cd();
        plot->Draw();
        plot->SetMinimum(1e-1);

        // save canvas to file
        TString fileName( m_paramName[i] );
        fileName += "_";  fileName += filename;
        canvas->SaveAs( fileName + ".eps" );
        canvas->SaveAs( fileName + ".pdf");
        canvas->SaveAs( fileName + ".png");

        if(arrow)
            delete arrow; 
        arrow = 0;
    }

    delete canvas; canvas = 0;

}

void FitterPulls::plotResiduals( TString dir, std::string paramName, Int_t nCores ) const
{
    // create a canvas
    TCanvas* canvas = new TCanvas( "residuals", "Minimum Negative Log Likelihood" );
	std::ofstream f;
	f.open((dir+"residuals.txt").Data());
    for (Int_t i=0; i<m_nVars; ++i) {

        std::cout << m_paramName[i] << " " << *std::max_element( m_residuals[i].begin(), m_residuals[i].end() ) << std::endl;

        // create dataset to store the pulls
        TString title(m_paramName[i]);
        title += " Value";

        // check that there are nlls to plot
        if (!m_residuals.size())
        {
            std::cerr << "ERROR in FitterPulls::plotValues : Vectors not yet filled." << std::endl;
            return;
        }

        // make the title

        // create the variable setting the extreme values.
        RooRealVar value("value", title,
                1.*(*std::min_element( m_residuals[i].begin(), m_residuals[i].end() )),
                1.*(*std::max_element( m_residuals[i].begin(), m_residuals[i].end() )) );
        // now create the empty dataset
        RooDataSet values("values", title, RooArgSet( value ) );

        // iterate again through the nlls and add them into the dataset
        std::vector< Double_t >::const_iterator iter = m_residuals[i].begin();
        const std::vector< Double_t >::const_iterator enditer = m_residuals[i].end();
        for (; iter != enditer; ++iter) {
            value.setVal( (*iter) );
            values.add( RooArgSet( value ) );
        }

        // create a gaussian pdf
        RooRealVar mean( "mean", "Value Gaussian Mean", values.meanVar( value )->getVal(), value.getMin(), value.getMax() );
        RooRealVar sigma( "sigma", "Value Gaussian Sigma", values.rmsVar( value )->getVal(), 0.0, value.getMax() - value.getMin());
        RooGaussian gauss( "gauss", "Value Gaussian", value, mean, sigma );

        // fit it to the nll data
        gauss.fitTo( values, RooFit::NumCPU( nCores ), RooFit::PrintLevel(-1));
		f << m_paramName[i] << " " << mean.getVal() << " " << mean.getError() << " " << sigma.getVal() << " " << sigma.getError() << std::endl;
        // make an empty plot
        RooPlot* plot = value.frame();
        //plot->SetTitle("");
        // plot the nlls and the gaussian
        values.plotOn( plot, RooFit::Binning(m_nBins) );
        RooHist* hist = dynamic_cast<RooHist*>( plot->getObject(0) );
        Double_t arrowTop = 0.4 * hist->getYAxisMax();
        gauss.plotOn( plot );

        // add an arrow for the data value
        // (DON'T DELETE the arrow because the RooPlot destructor does it for you)
        TArrow *arrow(0);
        RooRealVar* var(0);
        if (m_dataRes)
        {
            double v(0.);
            RooFIter paramIter = m_dataRes->floatParsFinal().fwdIterator();
            while ( (var = dynamic_cast<RooRealVar*>( paramIter.next() ) ) ) {
                std::string name = var->GetName();
                std::string classname = var->ClassName();
                if (classname!="RooRealVar") {
                    continue; 
                }
                if( TString( var->GetName() ) == m_paramName[i] ) {
                    v = var->getVal();
                    break;
                }
            }
            arrow = new TArrow( v, arrowTop, v, 0, 0.05, ">" ) ;
            arrow->SetFillColor(2);
            arrow->SetLineColor(2);
            arrow->SetLineWidth(2);
            arrow->SetFillStyle(1001);
            plot->addObject(arrow);
        }

        gauss.paramOn( plot, RooFit::Parameters( RooArgSet(  mean, sigma ) ),
                RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.92 ) );

        // draw the plot
        canvas->cd();
        plot->Draw();
        plot->SetMinimum(1e-1);

        // save canvas to file
        TString fileName( dir );
        fileName += paramName;
        fileName += "_";  
        fileName +=  m_paramName[i] ;
        fileName += "_";  
        fileName += "SystI";  
        fileName += "_";  
        fileName += paramName;  
        canvas->SaveAs( fileName + ".eps" );
        canvas->SaveAs( fileName + ".pdf");
        canvas->SaveAs( fileName + ".png");
        if(arrow)
            delete arrow; 
        arrow = 0;
    }
	f.close();
    delete canvas; canvas = 0;
}

void FitterPulls::plotToyResiduals( TString filename, Int_t nCores ) const
{
    // create a canvas
    TCanvas* canvas = new TCanvas( "toy residuals", "Minimum Negative Log Likelihood" );

    for (Int_t i=0; i<m_nVars; ++i) {

        // create dataset to store the pulls
        TString title(m_paramName[i]);
        title += " toy residual";
        if (!title.Contains("Yield"))
            continue;
        // check that there are nlls to plot
        if (!m_toyResiduals.size())
        {
            std::cerr << "ERROR in FitterPulls::plotValues : Vectors not yet filled." << std::endl;
            return;
        }

        // make the title

        // create the variable setting the extreme values.
        RooRealVar value("toyResidual", title,
                1.*(*std::min_element( m_toyResiduals[i].begin(), m_toyResiduals[i].end() )),
                1.*(*std::max_element( m_toyResiduals[i].begin(), m_toyResiduals[i].end() )) );
        // now create the empty dataset
        RooDataSet values("toyResiduals", title, RooArgSet( value ) );

        // iterate again through the nlls and add them into the dataset
        std::vector< Double_t >::const_iterator iter = m_toyResiduals[i].begin();
        const std::vector< Double_t >::const_iterator enditer = m_toyResiduals[i].end();
        for (; iter != enditer; ++iter) {
            value.setVal( (*iter) );
            values.add( RooArgSet( value ) );
        }

        // create a gaussian pdf
        RooRealVar mean( "mean", "Value Gaussian Mean", values.meanVar( value )->getVal(), value.getMin(), value.getMax() );
        RooRealVar sigma( "sigma", "Value Gaussian Sigma", values.rmsVar( value )->getVal(), 0.0, value.getMax() - value.getMin());
        RooGaussian gauss( "gauss", "Value Gaussian", value, mean, sigma );

        // fit it to the nll data
        gauss.fitTo( values, RooFit::NumCPU( nCores ), RooFit::PrintLevel(-1));

        // make an empty plot
        RooPlot* plot = value.frame();
        // plot the nlls and the gaussian
        values.plotOn( plot, RooFit::Binning(m_nBins) );
        RooHist* hist = dynamic_cast<RooHist*>( plot->getObject(0) );
        Double_t arrowTop = 0.4 * hist->getYAxisMax();
        gauss.plotOn( plot );

        // add an arrow for the data value
        // (DON'T DELETE the arrow because the RooPlot destructor does it for you)
        TArrow *arrow(0);
        RooRealVar* var(0);
        if (m_dataRes)
        {
            double v(0.);
            RooFIter paramIter = m_dataRes->floatParsFinal().fwdIterator();
            while ( (var = dynamic_cast<RooRealVar*>( paramIter.next() ) ) ) {
                std::string name = var->GetName();
                std::string classname = var->ClassName();
                if (classname!="RooRealVar") {
                    continue; 
                }
                if( TString( var->GetName() ) == m_paramName[i] ) {
                    v = var->getVal();
                    break;
                }
            }
            arrow = new TArrow( v, arrowTop, v, 0, 0.05, ">" ) ;
            arrow->SetFillColor(2);
            arrow->SetLineColor(2);
            arrow->SetLineWidth(2);
            arrow->SetFillStyle(1001);
            plot->addObject(arrow);
        }

        gauss.paramOn( plot, RooFit::Parameters( RooArgSet(  mean, sigma ) ),
                RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.92 ) );

        // draw the plot
        canvas->cd();
        plot->Draw();
        plot->SetMinimum(1e-1);

        // save canvas to file
        TString fileName( m_paramName[i] );
        fileName += "_";  fileName += filename;
        canvas->SaveAs( fileName + ".eps" );
        canvas->SaveAs( fileName + ".pdf");
        canvas->SaveAs( fileName + ".png");

        if(arrow)
            delete arrow; 
        arrow = 0;
    }
    delete canvas; canvas = 0;
}

void FitterPulls::plotToyValues( TString filename, Int_t nCores ) const
{
    // create a canvas
    TCanvas* canvas = new TCanvas( "toy values", "Minimum Negative Log Likelihood" );

    for (Int_t i=0; i<m_nVars; ++i) {
        std::cout << m_paramName[i] << " TOYVALUES " << *std::max_element( m_toyResiduals[i].begin(), m_toyResiduals[i].end() ) << std::endl;

        // create dataset to store the pulls
        TString title(m_paramName[i]);
        title += " toy residual";

        // check that there are nlls to plot
        if (!m_toyValues[i].size())
        {
            std::cerr << "ERROR in FitterPulls::plotValues : Vectors not yet filled." << std::endl;
            return;
        }

        // make the title

        // create the variable setting the extreme values.
        RooRealVar value("toyValue", title,
                1.*(*std::min_element( m_toyValues[i].begin(), m_toyValues[i].end() )),
                1.*(*std::max_element( m_toyValues[i].begin(), m_toyValues[i].end() )) );
        // now create the empty dataset
        RooDataSet values("toyValues", title, RooArgSet( value ) );

        // iterate again through the nlls and add them into the dataset
        std::vector< Double_t >::const_iterator iter = m_toyValues[i].begin();
        const std::vector< Double_t >::const_iterator enditer = m_toyValues[i].end();
        for (; iter != enditer; ++iter) {
            value.setVal( (*iter) );
            values.add( RooArgSet( value ) );
        }

        // create a gaussian pdf
        RooRealVar mean( "mean", "Value Gaussian Mean", values.meanVar( value )->getVal(), value.getMin(), value.getMax() );
        RooRealVar sigma( "sigma", "Value Gaussian Sigma", values.rmsVar( value )->getVal(), 0.0, value.getMax() - value.getMin());
        RooGaussian gauss( "gauss", "Value Gaussian", value, mean, sigma );

        // fit it to the nll data
        gauss.fitTo( values, RooFit::NumCPU( nCores ), RooFit::PrintLevel(-1));

        // make an empty plot
        RooPlot* plot = value.frame();
        // plot the nlls and the gaussian
        //Homemade binning...
        unsigned int nBins = TMath::Min(m_nBins,(int) (value.getMax()-value.getMin()));
        values.plotOn( plot, RooFit::Binning(nBins) );
        RooHist* hist = dynamic_cast<RooHist*>( plot->getObject(0) );
        Double_t arrowTop = 0.4 * hist->getYAxisMax();
        gauss.plotOn( plot );
        std::cout << "ok" << std::endl;

        // add an arrow for the data value
        // (DON'T DELETE the arrow because the RooPlot destructor does it for you)
        TArrow *arrow(0);
        RooRealVar* var(0);
        if (m_dataRes)
        {
            double v(0.);
            RooFIter paramIter = m_dataRes->floatParsFinal().fwdIterator();
            while ( (var = dynamic_cast<RooRealVar*>( paramIter.next() ) ) ) {
                std::string name = var->GetName();
                std::string classname = var->ClassName();
                if (classname!="RooRealVar") {
                    continue; 
                }
                if( TString( var->GetName() ) == m_paramName[i] ) {
                    v = var->getVal();
                    break;
                }
            }
            arrow = new TArrow( v, arrowTop, v, 0, 0.05, ">" ) ;
            arrow->SetFillColor(2);
            arrow->SetLineColor(2);
            arrow->SetLineWidth(2);
            arrow->SetFillStyle(1001);
            plot->addObject(arrow);
        }

        gauss.paramOn( plot, RooFit::Parameters( RooArgSet(  mean, sigma ) ),
                RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.92 ) );

        // draw the plot
        canvas->cd();
        plot->Draw();
        plot->SetMinimum(1e-1);

        // save canvas to file
        TString fileName( m_paramName[i] );
        fileName += "_";  fileName += filename;
        canvas->SaveAs( fileName + ".eps" );
        canvas->SaveAs( fileName + ".pdf");

    }
    delete canvas; canvas = 0;
}

// plot information about the Systematics studies Type I
void FitterPulls::plotSystI(TString dir, std::string paramName, Int_t nCores) const
{

    // create a canvas
    TCanvas* canvas = new TCanvas( "values", "Systematics Type I" );
	std::ofstream f;
	f.open((dir+"/"+paramName.c_str()+".txt").Data());
    for (Int_t i=0; i<m_nVars; ++i) {

        std::string listPar = (m_paramName[i]).Data();
        std::cout << m_paramName[i] << std::endl;
		
        // create dataset to store the pulls
        TString title(m_paramName[i]);
        title += " Residual";

        // create the variable setting the extreme values.
        RooRealVar value("value", title,
						 1.*(*std::min_element( m_SystI[i].begin(), m_SystI[i].end() )),
						 1.*(*std::max_element( m_SystI[i].begin(), m_SystI[i].end() )) );

        RooDataSet values("values", title, RooArgSet( value ) );

        // iterate again through the nlls and add them into the dataset
        std::vector< Double_t >::const_iterator iter          = m_SystI[i].begin();
        const std::vector< Double_t >::const_iterator enditer = m_SystI[i].end();
        for (; iter != enditer; ++iter) {
            value.setVal( (*iter) );
            values.add( RooArgSet( value ) );
        }

        // create a gaussian pdf
        RooRealVar mean( "mean", "Value Gaussian Mean", /*0.0, -0.5, 0.5);//*/values.meanVar( value )->getVal(), value.getMin(), value.getMax() );
        RooRealVar sigma( "sigma", "Value Gaussian Sigma", /*1.0, 0.0, 2.0);//*/values.rmsVar( value )->getVal(), 0.0, value.getMax() - value.getMin());
        RooGaussian gauss( "gauss", "Value Gaussian", value, mean, sigma );

        // fit it to the nll data
        gauss.fitTo( values, RooFit::NumCPU( nCores ), RooFit::PrintLevel(-1), RooFit::PrintEvalErrors(-1) );
		f << m_paramName[i] << " " << mean.getVal() << " " << mean.getError() << " " << sigma.getVal() << " " << sigma.getError() << std::endl;
        // make an empty plot
        RooPlot* plot = value.frame();

        plot->SetTitleOffset(1.0);
        // plot the nlls and the gaussian
        values.plotOn( plot, RooFit::Binning(m_nBins) );
        RooHist* hist = dynamic_cast<RooHist*>( plot->getObject(0) );
        Double_t arrowTop = 0.4 * hist->getYAxisMax();
        gauss.plotOn( plot );

        // add an arrow for the data value
        TArrow *arrow(0);
        RooRealVar* var(0);
        if (m_dataRes)
        {
            double v(0.);
            RooFIter paramIter = m_dataRes->floatParsFinal().fwdIterator();
            while ( (var = dynamic_cast<RooRealVar*>( paramIter.next() ) ) ) {
                std::string name = var->GetName();
                std::string classname = var->ClassName();
                if (classname!="RooRealVar") {
                    continue; 
                }
                if( TString( var->GetName() ) == m_paramName[i] ) {
                    v = var->getVal();
                    break;
                }
            }
            arrow = new TArrow( v, arrowTop, v, 0, 0.05, ">" ) ;
            arrow->SetFillColor(2);
            arrow->SetLineColor(2);
            arrow->SetLineWidth(2);
            arrow->SetFillStyle(1001);
            plot->addObject(arrow);
        }

        gauss.paramOn( plot, RooFit::Parameters( RooArgSet(  mean, sigma ) ),
                RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.82 ) );

        // draw the plot
        canvas->cd();
        plot->Draw();
        plot->SetMinimum(1e-1);

        // save canvas to file
        TString fileName( dir );
        fileName += paramName;
        fileName += "_";  
        fileName +=  m_paramName[i] ;
        fileName += "_";  
        fileName += "SystI";  
        fileName += "_";  
        fileName += paramName;  
        canvas->SaveAs( fileName + ".eps" );
        canvas->SaveAs( fileName + ".pdf");
        canvas->SaveAs( fileName + ".png");
    }
	f.close();
    delete canvas; canvas = 0;
}

// plot information about the Systematics studies Type I
void FitterPulls::plotSystI_DP(TString dir, std::string paramName, Int_t nCores) const
{

    // create a canvas
    TCanvas* canvas = new TCanvas( "values", "Systematics Type I" );

    for (Int_t i=0; i<m_nVars; ++i) {

        std::string listPar = (m_paramName[i]).Data();
        if (listPar.find("Yield")!=std::string::npos){
            std::cout << m_paramName[i] << std::endl;

            // create dataset to store the pulls
            TString title(m_paramName[i]);
            title += " Residual";

            // create the variable setting the extreme values.
            RooRealVar value("value", title, -0.5, 0.5);
            RooDataSet values("values", title, RooArgSet( value ) );

            // iterate again through the nlls and add them into the dataset
            std::vector< Double_t >::const_iterator iter = m_SystI[i].begin();
            const std::vector< Double_t >::const_iterator enditer = m_SystI[i].end();
            for (; iter != enditer; ++iter) {
                value.setVal( (*iter) );
                values.add( RooArgSet( value ) );
            }

            // create a gaussian pdf
            RooRealVar mean( "mean", "Value Gaussian Mean", 0.0, -0.5, 0.5);//values.meanVar( value )->getVal(), value.getMin(), value.getMax() );
            RooRealVar sigma( "sigma", "Value Gaussian Sigma", 1.0, 0.0, 2.0);//values.rmsVar( value )->getVal(), 0.0, value.getMax() - value.getMin());
            RooGaussian gauss( "gauss", "Value Gaussian", value, mean, sigma );

            // fit it to the nll data
            gauss.fitTo( values, RooFit::NumCPU( nCores ), RooFit::PrintLevel(-1), RooFit::PrintEvalErrors(-1) );

            // make an empty plot
            RooPlot* plot = value.frame();

            plot->SetTitleOffset(1.0);
            // plot the nlls and the gaussian
            values.plotOn( plot, RooFit::Binning(m_nBins) );
            RooHist* hist = dynamic_cast<RooHist*>( plot->getObject(0) );
            Double_t arrowTop = 0.4 * hist->getYAxisMax();
            gauss.plotOn( plot );

            TArrow *arrow(0);
            RooRealVar* var(0);
            if (m_dataRes)
            {
                double v(0.);
                RooFIter paramIter = m_dataRes->floatParsFinal().fwdIterator();
                while ( (var = dynamic_cast<RooRealVar*>( paramIter.next() ) ) ) {
                    std::string name = var->GetName();
                    std::string classname = var->ClassName();
                    if (classname!="RooRealVar") {
                        continue; 
                    }
                    if( TString( var->GetName() ) == m_paramName[i] ) {
                        v = var->getVal();
                        break;
                    }
                }
                arrow = new TArrow( v, arrowTop, v, 0, 0.05, ">" ) ;
                arrow->SetFillColor(2);
                arrow->SetLineColor(2);
                arrow->SetLineWidth(2);
                arrow->SetFillStyle(1001);
                plot->addObject(arrow);
            }

            gauss.paramOn( plot, RooFit::Parameters( RooArgSet(  mean, sigma ) ),
                    RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.82 ) );

            // draw the plot
            canvas->cd();
            plot->Draw();
            plot->SetMinimum(1e-1);

            // save canvas to file
            TString fileName( dir );
            fileName +=  m_paramName[i] ;
            fileName += "_";  
            fileName += "SystI";  
            fileName += "_";  
            fileName += paramName;  
            canvas->SaveAs( fileName + ".eps" );
            canvas->SaveAs( fileName + ".pdf");
        }
    }
    delete canvas; canvas = 0;
}

// plot information about the Systematics studies Type II
void FitterPulls::plotSystII(TString dir, Int_t nCores) const
{
    // create a canvas
    TCanvas* canvas = new TCanvas( "values", "Systematics Type II" );

    for (Int_t i=0; i<m_nVars; ++i) {

        std::string listPar = (m_paramName[i]).Data();
        if (listPar.find("Yield")!=std::string::npos){
            std::cout << m_paramName[i] << std::endl;

            // create dataset to store the pulls
            TString title(m_paramName[i]);
            title += " Diff";

            // create the variable setting the extreme values.
            RooRealVar value("value", title,1.*(*std::min_element( m_SystII[i].begin(), m_SystII[i].end() )), 1.*(*std::max_element( m_SystII[i].begin(), m_SystII[i].end() )) );
            RooDataSet values("values", title, RooArgSet( value ) );

            // iterate again through the nlls and add them into the dataset
            std::vector< Double_t >::const_iterator iter = m_SystII[i].begin();
            const std::vector< Double_t >::const_iterator enditer = m_SystII[i].end();
            for (; iter != enditer; ++iter) {
                value.setVal( (*iter) );
                values.add( RooArgSet( value ) );
            }

            // create a gaussian pdf
            RooRealVar mean( "mean", "Value Gaussian Mean", 0.5*(1.*(*std::max_element( m_SystII[i].begin(), m_SystII[i].end() )) + 1.*(*std::min_element( m_SystII[i].begin(), m_SystII[i].end() ))), 1.*(*std::min_element( m_SystII[i].begin(), m_SystII[i].end() )), 1.*(*std::max_element( m_SystII[i].begin(), m_SystII[i].end() )) );
            RooRealVar sigma( "sigma", "Value Gaussian Sigma", 1.0, 0.0,1.*(*std::max_element( m_SystII[i].begin(), m_SystII[i].end() )) -1.*(*std::min_element( m_SystII[i].begin(), m_SystII[i].end() )) );
            RooGaussian gauss( "gauss", "Value Gaussian", value, mean, sigma );

            // fit it to the nll data
            RooFitResult *res = gauss.fitTo( values, RooFit::NumCPU( nCores ), RooFit::PrintLevel(-1), RooFit::PrintEvalErrors(-1), RooFit::Save() );
            if (res->covQual() != 3 || res->status() != 0 || res->edm() > 1e-2)
                assert(0);

            // make an empty plot
            RooPlot* plot = value.frame();

            plot->SetTitleOffset(1.0);
            // plot the nlls and the gaussian
            values.plotOn( plot, RooFit::Binning(m_nBins) );
            RooHist* hist = dynamic_cast<RooHist*>( plot->getObject(0) );
            Double_t arrowTop = 0.4 * hist->getYAxisMax();
            gauss.plotOn( plot );

            // add an arrow for the data value
            TArrow *arrow(0);
            RooRealVar* var(0);
            if (m_dataRes)
            {
                double v(0.);
                RooFIter paramIter = m_dataRes->floatParsFinal().fwdIterator();
                while ( (var = dynamic_cast<RooRealVar*>( paramIter.next() ) ) ) {
                    std::string name = var->GetName();
                    std::string classname = var->ClassName();
                    if (classname!="RooRealVar") {
                        continue; 
                    }
                    if( TString( var->GetName() ) == m_paramName[i] ) {
                        v = var->getVal();
                        break;
                    }
                }
                arrow = new TArrow( v, arrowTop, v, 0, 0.05, ">" ) ;
                arrow->SetFillColor(2);
                arrow->SetLineColor(2);
                arrow->SetLineWidth(2);
                arrow->SetFillStyle(1001);
                plot->addObject(arrow);
            }

            gauss.paramOn( plot, RooFit::Parameters( RooArgSet(  mean, sigma ) ),
                    RooFit::Format( "NEU", RooFit::AutoPrecision( 2 ) ), RooFit::Layout( 0.59, 0.92, 0.82 ) );

            //delete measured; measured = 0;
            // draw the plot
            canvas->cd();
            plot->Draw();
            plot->SetMinimum(1e-1);

            // save canvas to file
            TString fileName( dir );
            fileName +=  m_paramName[i] ;
            fileName += "_";  
            fileName += "SystII";  
            canvas->SaveAs( fileName + ".eps" );
            canvas->SaveAs( fileName + ".pdf");
			//            double errSyst = TMath::Sqrt(mean.getVal()*mean.getVal() + sigma.getVal()*sigma.getVal());
        }
    }
    delete canvas; canvas = 0;
}


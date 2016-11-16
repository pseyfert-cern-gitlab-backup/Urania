// STL include
#include <iostream>
#include <fstream>

// ROOT
#include "TH1F.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TStyle.h"

// Local include
#include "V0hhFitter/FitterLikesRatioPlot.h"

using namespace V0hhFit;

FitterLikesRatioPlot::FitterLikesRatioPlot(TString compThatsRatioNumerator) :
    m_likeRatNum( compThatsRatioNumerator ), m_lhcbStyle()
{}

FitterLikesRatioPlot::~FitterLikesRatioPlot()
{}

void FitterLikesRatioPlot::dataVsToyPlot(TH1F DataHisto, std::vector<TH1F> componentToyHistos, Double_t scaleFactor,
        UInt_t numBins, Double_t startRange, Double_t endRange,
        Bool_t drawDataVsToyLeg, Bool_t doLog,
        Bool_t useROOTDefaultYAxisRange, Double_t minYAxisValue)
{ 
    if (minYAxisValue <= 0.0) {std::cout << "minYAxisValue must be > 0.0 ..  using ROOT default y-axis range ........." << std::endl;}

    // x-axis label
    TString xLabel = "Likelihood (";
    xLabel        += m_likeRatNum;
    xLabel        += ") / Likelihood (Total)";

    // y-axis label
    TString yLabel = "Number Of Events";

    // output file name
    TString EpsFileName = m_likeRatNum;
    EpsFileName        += "LikelihoodRatioPlot_DataVsToy.eps";

    // toy histo (sum of toy component histos) 
    TH1F ToyHisto("ToyHisto","",numBins,startRange,endRange);
    for (std::vector<TH1F>::iterator iter = componentToyHistos.begin(); iter != componentToyHistos.end(); ++iter)
    {
        ToyHisto.Add(&(*iter));
    }

    // scale to normalise with data histo
    ToyHisto.Scale((1./scaleFactor));

    // set line color of toy histo to green (data histo to be black markers, with error bars)
    ToyHisto.SetLineColor(3);

    // make a canvas
    TCanvas* myCanvas = new TCanvas("myCanvas","");
    myCanvas->SetFillColor(0);
    gStyle->SetOptStat(0);

    // make y-axis logarithmic. 
    if(doLog) {myCanvas->SetLogy();}

    // plot histos
    if ((ToyHisto.GetMaximum()) > (DataHisto.GetMaximum()))
    {
        ToyHisto.SetXTitle(xLabel);
        ToyHisto.SetYTitle(yLabel);
        if (!useROOTDefaultYAxisRange && (minYAxisValue > 0.0)) {ToyHisto.SetMinimum(minYAxisValue);}
        ToyHisto.Draw();
        DataHisto.Draw("same");
    }
    else
    {
        DataHisto.SetXTitle(xLabel);
        DataHisto.SetYTitle(yLabel);
        if (!useROOTDefaultYAxisRange && (minYAxisValue > 0.0)) {DataHisto.SetMinimum(minYAxisValue);}
        DataHisto.Draw();
        ToyHisto.Draw("same");
    }

    // make a legend and draw it
    TLegend leg(0.55,0.70,0.75,0.85);
    leg.SetFillColor(0);
    leg.SetTextSize(0.045);
    leg.AddEntry(&DataHisto,"Data","l");
    leg.AddEntry(&ToyHisto,"Toy MC","l");
    if (drawDataVsToyLeg) {leg.Draw();}

    // save as eps file
    myCanvas->SaveAs(EpsFileName);

    // clean up
    delete myCanvas; myCanvas = 0;
}

void FitterLikesRatioPlot::toyCompsPlot(std::vector<TH1F> componentToyHistos, std::vector<TString> componentNames, Int_t numComps, Int_t numeratorComp,
        Double_t scaleFactor, UInt_t numBins, Double_t startRange, Double_t endRange,
        Double_t toyCompsLegTextSize, Double_t toyCompsLegPosXStart,
        Double_t toyCompsLegPosYStart, Double_t toyCompsLegPosXEnd,
        Double_t toyCompsLegPosYEnd, Bool_t drawToyCompsLeg, Bool_t doLog,
        Bool_t useROOTDefaultYAxisRange, Double_t minYAxisValue)
{
    if (minYAxisValue <= 0.0) {
        std::cout << "minYAxisValue must be > 0.0 ..  using ROOT default y-axis range ........." << std::endl;
    }

    // x-axis label
    TString xLabel = "Likelihood (";
    xLabel        += m_likeRatNum;
    xLabel        += ") / Likelihood (Total)";

    // y-axis label
    TString yLabel = "Number Of Events";

    // output file name
    TString EpsFileName = m_likeRatNum;
    EpsFileName        += "LikelihoodRatioPlot_ToyComps.eps";

    // let's say we have histos a, b, c and d
    // want to plot histos (a+b+c+d), (a+b+c), (a+b) and (a)
    // where a has the largest number of entries and c the least --- excluding the numerator component, d
    // (likelihood ratio = L(numerator comp.)/L(total))
    std::vector<Int_t> numberOfEntries;
    std::vector<Int_t> orderOfCompsByNumEvntsWithNumtrLast;
    std::vector<TH1F> summedComponentToyHistos;

    // default fill colours for histos
    Int_t numDefaultColours(4);
    Int_t colour[4] = {38, 42, 3, 7}; // ensure number of elements is equal to numDefaultColors

    // (i) sort histos passed by their # of entries, but (ii) with numerator component last
    for (Int_t i = 0; i < numComps; ++i) {

        numberOfEntries.push_back((Int_t)componentToyHistos[i].GetEntries());
        orderOfCompsByNumEvntsWithNumtrLast.push_back(i);
    }
    

    for (Int_t i = 0; i < (numComps - 1); ++i) // (ii)
    {
        if (i == numeratorComp)
        {
            FitterLikesRatioPlot::swap(numberOfEntries[i],numberOfEntries[numComps - 1]);
            FitterLikesRatioPlot::swap(orderOfCompsByNumEvntsWithNumtrLast[i],orderOfCompsByNumEvntsWithNumtrLast[numComps - 1]);
        }
    }
    
   
    for (Int_t i = 0; i < (numComps - 2); i++) // (i)
    {
        Int_t maxIndex = i;
        for (Int_t j = (i + 1); j < (numComps - 1); ++j ) {

            if ( numberOfEntries[j] > numberOfEntries[maxIndex] ) {

                maxIndex = j;
            }
        }
        if (maxIndex > i) {

            FitterLikesRatioPlot::swap( numberOfEntries[i], numberOfEntries[maxIndex] );
            FitterLikesRatioPlot::swap( orderOfCompsByNumEvntsWithNumtrLast[i], orderOfCompsByNumEvntsWithNumtrLast[maxIndex] );
        }
    }

    // make summed histos (we're plotting (a), (a+b), (a+b+c), (a+b+c+d) .., rather than a, b, c, d ..) and set attributes
    for (Int_t i = 0; i < numComps; ++i)
    {
        TH1F summedCompsToyHisto( componentNames[orderOfCompsByNumEvntsWithNumtrLast[i]], "", numBins, startRange, endRange );
        for (Int_t j = i; j > -1; --j) {

            summedCompsToyHisto.Add(&(componentToyHistos[orderOfCompsByNumEvntsWithNumtrLast[j]]));
        }
        summedCompsToyHisto.Scale((1./scaleFactor));
        summedCompsToyHisto.SetLineWidth(0);
        if (i < numDefaultColours) {

            summedCompsToyHisto.SetFillColor(colour[i]);
        }  else {
            summedCompsToyHisto.SetFillColor( ( ( 5 * i ) - 1 ) );
        }
        if (i == (numComps - 1)) {

            summedCompsToyHisto.SetFillColor( 2 ); // want numerator component summed histo to be red
            summedCompsToyHisto.SetXTitle( xLabel );
            summedCompsToyHisto.SetYTitle( yLabel );
        }
        summedComponentToyHistos.push_back( summedCompsToyHisto );
    }

    // make a canvas
    TCanvas* myCanvas = new TCanvas( "myCanvas", "" );
    myCanvas->SetFillColor( 0 );
    gStyle->SetOptStat( 0 );

    // make y-axis logarithmic. 
    if(doLog) {myCanvas->SetLogy();}

    // plot histos
    for (Int_t i = (numComps - 1); i > -1; i--)
    {
        if (!useROOTDefaultYAxisRange && (minYAxisValue > 0.0))
        {
            if (i == (numComps - 1)) {summedComponentToyHistos[i].SetMinimum(minYAxisValue); summedComponentToyHistos[i].Draw();}
            else                     {summedComponentToyHistos[i].Draw("same");}
        }
        else
        {
            if (i == (numComps - 1)) {summedComponentToyHistos[i].Draw();}
            else                     {summedComponentToyHistos[i].Draw("same");}
        }
    }

    // make a legend and draw it
    TLegend leg(toyCompsLegPosXStart,toyCompsLegPosYStart,toyCompsLegPosXEnd,toyCompsLegPosYEnd);
    leg.SetFillColor(0);
    leg.SetTextSize(toyCompsLegTextSize);
    leg.SetHeader("(^{ 1}: + components listed below)");
    for (Int_t i = (numComps - 1); i > -1; i--)
    {
        TString legEntry = componentNames[orderOfCompsByNumEvntsWithNumtrLast[i]];
        if (i == 0) {legEntry += "";}
        else        {legEntry += "^{ 1}";}
        leg.AddEntry(&(summedComponentToyHistos[i]),legEntry,"f");
    }
    if (drawToyCompsLeg) {leg.Draw();}

    // save as eps file
    myCanvas->SaveAs(EpsFileName);

    // clean up
    delete myCanvas; myCanvas = 0;
}

void FitterLikesRatioPlot::swap(Int_t& x, Int_t& y)
{
    Int_t temp;

    temp = x;
    x    = y;
    y    = temp;
}

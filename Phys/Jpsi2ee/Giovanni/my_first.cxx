{
using namespace TMath;
using namespace RooFit;


RooRealVar Psi_MM("Psi_MM","Psi_MM",2000,3600);

/*
//TFile *emul = TFile::Open("/afs/cern.ch/user/p/pkoppenb/public/Jpsi2017-MC-1531.root");
//TTree* T = (TTree*)emul->Get("EmulatedTrigger_Tuple/DecayTree");
//RooRealVar Psi_BKGCAT("Psi_BKGCAT","Psi_BKGCAT",0,140);
//RooDataSet data1("data1","emulated ee",T,RooArgSet(Psi_MM,Psi_BKGCAT),"Psi_BKGCAT==0 || Psi_BKGCAT==50");
TFile *emul = TFile::Open("test.root");
RooDataSet* data1 = (RooDataSet*)emul->Get("data1");
*/

RooRealVar mg1("mg1", "mean gauss 1",3100,2500,3500);
RooRealVar sg1("sg1", "sigma gauss 1",1000,100,2000);
RooGaussian gauss1("gauss1","gauss PDF 1",Psi_MM,mg1,sg1);
RooRealVar mg2("mg2", "mean gauss 2",3100,2500,3500);
RooRealVar sg2("sg2", "sigma gauss 2",180,60,300);
RooGaussian gauss2("gauss2","gauss PDF 2",Psi_MM,mg2,sg2);
RooRealVar mcb("mcb","mean cb",2000,4000);
RooRealVar scb("scb","sigma cb",0,100);
RooRealVar alpha("alpha","alpha",0.1,3);
RooRealVar n("n","n",0.5,2);
RooCBShape cb("cb","cbshape PDF",Psi_MM,mcb,scb,alpha,n);
RooRealVar c1("c1","proportionality coefficient 1",0.5,0,1);
RooRealVar c2("c2","proportionality coefficient 2",0.1,0,0.2);
RooAddPdf three("three","2xGaussian and CBShape",RooArgSet(gauss1,gauss2,cb),RooArgSet(c1,c2));

//RooFitResult* rf1 = three.fitTo(*data1,Save());

//last results:

alpha.setVal(0.43);
alpha.setConstant();
c1.setVal(0.153);
c1.setConstant();
c2.setVal(0.196);
c2.setConstant();
mcb.setVal(3063.8);
mcb.setConstant();
mg1.setVal(3043);
mg1.setConstant();
mg2.setVal(3069);
mg2.setConstant();
n.setVal(1.93);
n.setConstant();
scb.setVal(37.4);
scb.setConstant();
/*
sg1.setVal(377);
sg1.setConstant();
sg2.setVal(102);
sg2.setConstant();
*/ //unlock sigmas because we reduce the MM to 3600, while montecarlo is on 4000

/*
RooPlot* Psi_MMframe = Psi_MM.frame();
data1->plotOn(Psi_MMframe);
three.plotOn(Psi_MMframe);
three.plotOn(Psi_MMframe,LineColor(kGreen),Components(cb));
three.plotOn(Psi_MMframe,LineColor(kRed),Components(gauss1));
three.plotOn(Psi_MMframe,LineColor(kOrange),Components(gauss2));
Psi_MMframe->Draw();
*/

//TFile *meas = TFile::Open("/afs/cern.ch/user/p/pkoppenb/public/Jpsi2017.root");
//TTree* T = (TTree*)meas->Get("Hlt2DiElectronJPsiEETurbo_Tuple/DecayTree");
RooRealVar Psi_PT("Psi_PT","Psi_PT",-RooNumber::infinity(),RooNumber::infinity());
RooRealVar Psi_PZ("Psi_PZ","Psi_PZ",-RooNumber::infinity(),RooNumber::infinity());
//RooDataSet data2("data2","measured ee",T,RooArgSet(Psi_MM,Psi_PT),"Psi_PT>5000"); //real.root
//RooDataSet data2("data2","measured ee",T,RooArgSet(Psi_MM,Psi_PT,Psi_PZ),"(Psi_PZ/Psi_PT)>sinh(4)");
RooRealVar Psi_ENDVERTEX_CHI2("Psi_ENDVERTEX_CHI2","Psi_ENDVERTEX_CHI2",-RooNumber::infinity(),RooNumber::infinity());
RooRealVar Psi_IPCHI2_OWNPV("Psi_IPCHI2_OWNPV","Psi_IPCHI2_OWNPV",-RooNumber::infinity(),RooNumber::infinity());
RooRealVar Psi_FDCHI2_OWNPV("Psi_FDCHI2_OWNPV","Psi_FDCHI2_OWNPV",-RooNumber::infinity(),RooNumber::infinity());
RooRealVar Psi_FD_OWNPV("Psi_FD_OWNPV","Psi_FD_OWNPV",-RooNumber::infinity(),RooNumber::infinity());
RooRealVar eplus_MC15TuneV1_ProbNNe("eplus_MC15TuneV1_ProbNNe","eplus_MC15TuneV1_ProbNNe",-RooNumber::infinity(),RooNumber::infinity());
RooRealVar eminus_MC15TuneV1_ProbNNe("eminus_MC15TuneV1_ProbNNe","eminus_MC15TuneV1_ProbNNe",-RooNumber::infinity(),RooNumber::infinity());
RooRealVar eplus_PT("eplus_PT","eplus_PT",-RooNumber::infinity(),RooNumber::infinity());
RooRealVar eminus_PT("eminus_PT","eminus_PT",-RooNumber::infinity(),RooNumber::infinity());
RooRealVar eplus_BremMultiplicity("eplus_BremMultiplicity","eplus_BremMultiplicity",-RooNumber::infinity(),RooNumber::infinity());
RooRealVar eminus_BremMultiplicity("eminus_BremMultiplicity","eminus_BremMultiplicity",-RooNumber::infinity(),RooNumber::infinity());
//RooDataSet data2("data2","featured ee",T,RooArgSet(RooArgSet(Psi_MM,Psi_PT,Psi_PZ,Psi_ENDVERTEX_CHI2,Psi_IPCHI2_OWNPV,Psi_FDCHI2_OWNPV,Psi_FD_OWNPV),RooArgSet(eplus_MC15TuneV1_ProbNNe,eminus_MC15TuneV1_ProbNNe,eplus_PT,eminus_PT,eplus_BremMultiplicity,eminus_BremMultiplicity))); //feat.root
TFile *meas = TFile::Open("feat.root");
RooDataSet* data2 = (RooDataSet*)meas->Get("data2");
data2=(RooDataSet*)data2->reduce("Psi_MM<3600"); //to reduce the feat.root which is on 4000
//data2=(RooDataSet*)data2->reduce("Psi_PT>5000");
data2=(RooDataSet*)data2->reduce("abs((eminus_PT-eplus_PT)/(eminus_PT+eplus_PT))<0.7"); //Acut


RooRealVar t("t","exponential PDF parameter",-0.00019,-0.0005,-0.000005);
RooExponential expon("expon","exponential PDF",Psi_MM,t);
RooRealVar p1("p1","1st cheb. param.",-0.11,-1,1);
RooRealVar p2("p2","2nd cheb. param.",-0.05,-1,1);
RooRealVar p3("p3","3rd cheb. param.",0,-10,10);
//RooChebychev ceb("ceb","chebyshev func",Psi_MM,RooArgSet(p1,p2,p3));
//RooRealVar c3("c3","prop. coeff. 3",0.5,0,1);
RooRealVar c3("c3","prop. coeff. 3",0.1*data2->sumEntries(),0,data2->sumEntries());
RooRealVar c4("c4","prop. coeff. 4",0.9*data2->sumEntries(),0,data2->sumEntries());
RooAddPdf five("five","MC based fit on data with exponential and or chebyshev background",RooArgSet(three,expon),RooArgSet(c3,c4)); //change ceb or expon depending on your choice


RooFitResult* rf2 = five.fitTo(*data2,Save()); //the star before data2 depends on which definition of RooDataSet is used (see below)


RooPlot* Psi_MMframe = Psi_MM.frame();
data2->plotOn(Psi_MMframe); // use a point for RooDataSet without star, arrow (->) for pointers (with *)
five.plotOn(Psi_MMframe);
five.plotOn(Psi_MMframe,LineColor(kRed),Components(expon));
//five.plotOn(Psi_MMframe,LineColor(kGreen),Components(ceb));
//expon.plotOn(Psi_MMframe); //to plot before the fit
//ceb.plotOn(Psi_MMframe); //to plot before the fit
Psi_MMframe->Draw();
TFile* newf = TFile::Open("plot.root","recreate");
newf->cd();
Psi_MMframe->Write();
newf->Close();

RooStats::SPlot* m_sData;
m_sData = new RooStats::SPlot("sData","sData",*data2,&five,RooArgSet(c3,c4));
RooDataSet * sign = new RooDataSet(data2->GetName(),data2->GetTitle(),data2,*data2->get(),0,"c3_sw");
RooDataSet * back = new RooDataSet(data2->GetName(),data2->GetTitle(),data2,*data2->get(),0,"c4_sw");
sign_sum = m_sData->GetYieldFromSWeight("c3");
back_sum = m_sData->GetYieldFromSWeight("c4");
RooPlot* overl = NULL


// to plot see overl.cxx
//this file is old. to open bigger datasets you need greg.cxx

}























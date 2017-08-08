{
using namespace TMath;
using namespace RooFit;

//select data and save file


RooRealVar Psi_M("Psi_M","Psi_M",2000,3600);
RooRealVar Psi_PT("Psi_PT","Psi_PT",0,RooNumber::infinity());


RooRealVar eplus_PT("eplus_PT","eplus_PT",-RooNumber::infinity(),RooNumber::infinity());
RooRealVar eminus_PT("eminus_PT","eminus_PT",-RooNumber::infinity(),RooNumber::infinity());

TFile *meas = TFile::Open("/eos/lhcb/user/p/pkoppenb/Jpsi2ee/Jpsi2017-1533.root");
TTree* cutT = (TTree*)meas->Get("Hlt2DiElectronJPsiEETurbo_Tuple/DecayTree"); //cutT or T
//TFile *newf = new TFile("newcut.root","recreate"); //tree needs new file
//TTree* cutT = T->CopyTree("abs((eminus_PT-eplus_PT)/(eminus_PT+eplus_PT))<0.7");
RooDataSet ds("ds","manual Psi_M",RooArgSet(Psi_M,Psi_PT));

Double_t bm,ps,ep,em;
cutT->SetBranchAddress("Psi_M",&bm);
cutT->SetBranchAddress("Psi_PT",&ps);
cutT->SetBranchAddress("eminus_PT",&em);
cutT->SetBranchAddress("eplus_PT",&ep);
int numEntries=cutT->GetEntries("");
for (int i=0; i < numEntries; i++){
        cutT->GetEntry(i);
        if (abs((em-ep)/(em+ep))<0.7){
                Psi_M.setVal(bm);
		Psi_PT.setVal(ps);
                ds.add(RooArgSet(Psi_M,Psi_PT));
        }
	int j=i%10000;
        Double_t d=(Double_t)i/numEntries;
        if (j==0){
                cout << d << endl;
        }

}
TFile* newf = TFile::Open("Acut.root","recreate");
newf->cd();
ds.Write();
newf->Close();


/*

//fit data

TFile *meas = TFile::Open("Acut.root");
RooDataSet* data2 = (RooDataSet*)meas->Get("ds");
data2=(RooDataSet*)data2->reduce("Psi_M<3600&&Psi_M>2000");

RooRealVar mg1("mg1", "mean gauss 1",3100,2500,3500);
RooRealVar sg1("sg1", "sigma gauss 1",1000,100,2000);
RooGaussian gauss1("gauss1","gauss PDF 1",Psi_M,mg1,sg1);
RooRealVar mg2("mg2", "mean gauss 2",3100,2500,3500);
RooRealVar sg2("sg2", "sigma gauss 2",180,60,300);
RooGaussian gauss2("gauss2","gauss PDF 2",Psi_M,mg2,sg2);
RooRealVar mcb("mcb","mean cb",2000,4000);
RooRealVar scb("scb","sigma cb",0,100);
RooRealVar alpha("alpha","alpha",0.1,3);
RooRealVar n("n","n",0.5,2);
RooCBShape cb("cb","cbshape PDF",Psi_M,mcb,scb,alpha,n);
RooRealVar c1("c1","proportionality coefficient 1",0.5,0,1);
RooRealVar c2("c2","proportionality coefficient 2",0.1,0,0.2);
RooAddPdf three("three","2xGaussian and CBShape",RooArgSet(gauss1,gauss2,cb),RooArgSet(c1,c2));

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

//sg1.setVal(377);
//sg1.setConstant();
//sg2.setVal(102);
//sg2.setConstant();


RooRealVar t("t","exponential PDF parameter",-0.00019,-0.0005,-0.000005);
RooExponential expon("expon","exponential PDF",Psi_M,t);
//RooRealVar p1("p1","1st cheb. param.",-0.11,-1,1);
//RooRealVar p2("p2","2nd cheb. param.",-0.05,-1,1);
//RooRealVar p3("p3","3rd cheb. param.",0,-10,10);
//RooChebychev ceb("ceb","chebyshev func",Psi_M,RooArgSet(p1,p2,p3));
RooRealVar c3("c3","prop. coeff. 3",0.1*data2->sumEntries(),0,data2->sumEntries());
RooRealVar c4("c4","prop. coeff. 4",0.9*data2->sumEntries(),0,data2->sumEntries());
RooAddPdf five("five","MC based fit on data with exponential and or chebyshev background",RooArgSet(three,expon),RooArgSet(c3,c4));

RooFitResult* rf2 = five.fitTo(*data2,Save());


RooPlot* Psi_MMframe = Psi_M.frame();
data2->plotOn(Psi_MMframe); // use a point for RooDataSet without star, arrow (->) for pointers (with *)
five.plotOn(Psi_MMframe);
five.plotOn(Psi_MMframe,LineColor(kRed),Components(expon));
//five.plotOn(Psi_MMframe,LineColor(kGreen),Components(ceb));
Psi_MMframe->Draw();

*/


//RooStats::SPlot* m_sData;
//m_sData = new RooStats::SPlot("sData","sData",*data2,&five,RooArgSet(c3,c4));


}

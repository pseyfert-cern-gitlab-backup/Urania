{
using namespace RooFit;

TFile *emul = TFile::Open("/afs/cern.ch/user/p/pkoppenb/public/Jpsi2017-MC-1531.root");
TTree* T = (TTree*)emul->Get("EmulatedTrigger_Tuple/DecayTree");
RooRealVar Psi_BKGCAT("Psi_BKGCAT","Psi_BKGCAT",0,140);
RooRealVar Psi_M("Psi_M","Psi_M",2000,3600);
RooRealVar Psi_PT("Psi_PT","Psi_PT",8000,9000);
RooDataSet data1("data1","emulated ee",T,RooArgSet(Psi_M,Psi_PT,Psi_BKGCAT),"Psi_BKGCAT==0 || Psi_BKGCAT==50");
RooRealVar mg1("mg1", "mean gauss 1",3100,2500,3500);
RooRealVar sg1("sg1", "sigma gauss 1",1000,100,2000);
RooGaussian gauss1("gauss1","gauss PDF 1",Psi_M,mg1,sg1);
RooRealVar mg2("mg2", "mean gauss 2",3100,2500,3500);
RooRealVar sg2("sg2", "sigma gauss 2",180,60,300);
RooGaussian gauss2("gauss2","gauss PDF 2",Psi_M,mg2,sg2);
RooRealVar mcb("mcb","mean cb",2000,4000);
RooRealVar scb("scb","sigma cb",0,100);
RooRealVar alpha("alpha","alpha",0.1,3);
RooRealVar n("n","n",0.5,5);
RooCBShape cb("cb","cbshape PDF",Psi_M,mcb,scb,alpha,n);
RooRealVar c1("c1","proportionality coefficient 1",0.5,0,1);
RooRealVar c2("c2","proportionality coefficient 2",0.1,0,1);
RooAddPdf three("three","2xGaussian and CBShape",RooArgSet(gauss1,gauss2,cb),RooArgSet(c1,c2));
	alpha.setVal(0.258);
        alpha.setConstant();
        c1.setVal(0.100);
        c1.setConstant();
        c2.setVal(0.206);
        c2.setConstant();
        mcb.setVal(3067);
        mcb.setConstant();
        mg1.setVal(3209);
        mg1.setConstant();
        mg2.setVal(3077);
        mg2.setConstant();
        sg1.setVal(220);
        sg1.setConstant();
        sg2.setVal(78.6);
        sg2.setConstant();
        n.setVal(2.51);
        n.setConstant();
        scb.setVal(32.3);
        scb.setConstant();
RooFitResult* rf1 = three.fitTo(data1);
RooPlot* Psi_Mframe = Psi_M.frame();
data1.plotOn(Psi_Mframe);
three.plotOn(Psi_Mframe);
three.plotOn(Psi_Mframe,LineColor(kGreen),Components(cb));
three.plotOn(Psi_Mframe,LineColor(kRed),Components(gauss1));
three.plotOn(Psi_Mframe,LineColor(kOrange),Components(gauss2));
Psi_Mframe->Draw();













}

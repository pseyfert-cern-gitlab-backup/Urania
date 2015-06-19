import GaudiPython, os
from GaudiPython.Bindings import gbl
std  = gbl.std
from ROOT import Double

from Configurables import BsMuMuBDTSelectionToolX as BDT



class BDTntuple:
    """
    Class to retrieve BDTS using as input the list variables: BIPS,muonsDOCA,SVCHI2,BDIRA,BIP,minIPmuons
    - Usage from any ntuple:
      myc=BDTSntuple()
      t1.GetEntry(1)

      myc.B_tau=t1.B_tau
      myc.minIPSalldaug=t1.minIPSalldaug
      myc.iso5=t1.iso5
      myc.B_PT=t1.B_PT
      myc.mu_CDFiso=t1.mu_CDFiso
      myc.mu_minPT=t1.mu_minPT
      myc.mu_polar=t1.mu_polar
      myc.mu_DOCA=t1.DOCA
      myc.B_IP=t1.B_IP

    - Usage from CERN ntuple:
      myc=BDTSntuple()
      t1.GetEntry(1)
      myc.calculateInCERNntuple(t1)
    """

    def __init__(self,bdtname="BDT9",with_bdts=0):

        ## with_bdts=0/"03"/"05" value of BDTS cut before the BDT training!
        self.bdtname=bdtname
        bdt = BDT(bdtname)
        bdt.varNumb=9

        if with_bdts:
            files=["TMVAClassification_BDT9_BDTS"+with_bdts+"_root30.weights.xml",
                   "Hflat_BDT9_BDTS"+with_bdts+"_withsm.root"]
            
        else:
            files=["TMVAClassification_BDT9_root30.weights.xml",
                   "Hflat_BDT9_withsm.root"]

        bdt.WeightsFile = os.path.join(os.environ["BS2MUMUROOT"],"operators/"+files[0])   # training process weights
        bdt.FlatHistoFile = os.path.join(os.environ["BS2MUMUROOT"],"operators/"+files[1])  # root file containing a definition histograme used for flatten BDTS
        self.B_tau=0.
        self.minIPSalldaug=0.
        self.iso5=0.
        self.B_PT=0.
        self.mu_CDFiso=0.
        self.mu_minPT=0.
        self.mu_polar=0.
        self.mu_DOCA=0.
        self.B_IP=0.

        self.toolStarted=False

        
    def startTool(self):

        self._gaudi = GaudiPython.AppMgr()
        if self._gaudi.state()==1: self._gaudi.initialize()
        
        self._bdttool=self._gaudi.toolsvc().create("BsMuMuBDTSelectionToolX/"+self.bdtname,interface="IBsMuMuBDTSelectionTool")
        self.toolStarted=True
        
        
    def calculate(self):
        res_flat=Double(0)
        res_unflat=Double(0)
        invars = std.vector('double')()
        invars.push_back(self.B_tau)
        invars.push_back(self.minIPSalldaug)
        invars.push_back(self.iso5)
        invars.push_back(self.B_PT)
        invars.push_back(self.mu_CDFiso)
        invars.push_back(self.mu_minPT)
        invars.push_back(self.mu_polar)
        invars.push_back(self.mu_DOCA)
        invars.push_back(self.B_IP)

        if not self.toolStarted: self.startTool()
        sc=self._bdttool.getBDTValFromVars(invars,res_flat,res_unflat)
        if sc.isFailure(): return -1.,-1.
        return float(res_flat),float(res_unflat)


    def calculateInCERNntuple(self,t1):
        
        self.B_tau=getattr(t1,"LF_time")
        self.minIPSalldaug=getattr(t1,"lessIPSmu")
        self.iso5=getattr(t1,"isoSum")
        self.B_PT=getattr(t1,"Bpt")
        self.mu_CDFiso=getattr(t1,"yet_another_CDF_iso")
        self.mu_minPT=getattr(t1,"minpt")
        self.mu_polar=getattr(t1,"Cosnk")
        self.mu_DOCA=getattr(t1,"DOCA")
        self.B_IP=getattr(t1,"Bip_r")

        return self.calculate()


    def addBDT_fromVars(self, algo, CandidateInfo, Done):
        """
        B_tau
        minIPSalldaug
        iso5
        B_PT
        mu_CDFiso
        mu_minPT
        mu_polar
        mu_DOCA
        B_IP    
        """
        ##"Blife_ps", "lessIPSmu", "isoSum", "Bpt", "yet_another_CDF_iso", "minpt", "Cosnk", "DOCA", "Bip_r"
        CandidateInfo["isoSum"] = CandidateInfo["mu1iso5"] + CandidateInfo["mu2iso5"]
        CandidateInfo["minpt"] =  min(CandidateInfo["mu1pt"],CandidateInfo["mu2pt"])
        
        self.B_tau=CandidateInfo["LF_time"]
        self.minIPSalldaug=CandidateInfo["lessIPSmu"]
        self.iso5=CandidateInfo["isoSum"]
        self.B_PT=CandidateInfo["Bpt"]
        self.mu_CDFiso=CandidateInfo["yet_another_CDF_iso"]
        self.mu_minPT=CandidateInfo["minpt"]
        self.mu_polar=CandidateInfo["Cosnk"]
        self.mu_DOCA=CandidateInfo["DOCA"]
        self.B_IP=CandidateInfo["Bip_r"]
        res_flat,res_unflat=self.calculate()
        CandidateInfo[self.bdtname]=res_flat
        CandidateInfo[self.bdtname+"_unflat"]=res_unflat

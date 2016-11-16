import GaudiPython, os
from GaudiPython.Bindings import gbl
std  = gbl.std
from ROOT import Double

from Configurables import BsMuMuBDTSelectionToolX as BDTS


class BDTSntuple:
    """
    Class to retrieve BDTS using as input the list variables: BIPS,muonsDOCA,SVCHI2,BDIRA,BIP,minIPmuons
    - Usage from any ntuple:
      myc=BDTSntuple()
      t1.GetEntry(1)
      myc.bips=t1.BIPS
      myc.doca=t1.muonsDOCA
      myc.bvertchi2=t1.SVCHI2
      myc.dira=t1.BDIRA
      myc.bip=t1.BIP
      myc.daughmip=t1.minIPmuons
      myc.calculate()
    - Usage from CERN ntuple:
      myc=BDTSntuple()
      t1.GetEntry(1)
      myc.calculateInCERNntuple(t1)
    """

    def __init__(self):


        bdts = BDTS()
        bdts.WeightsFile = os.path.join(os.environ["BS2MUMUROOT"],'options/BDTS_TOOL/TMVAClassification_BDTS_new_ROOT30.weights.xml')   # training process weights
        bdts.FlatHistoFile = os.path.join(os.environ["BS2MUMUROOT"],'options/BDTS_TOOL/HflatBDTS_new.root')  # root file containing a definition histograme used for flatten BDTS

        self.toolStarted=False
        
        self.bips=0.
        self.doca=0.
        self.bvertchi2=0.
        self.dira=0.
        self.bip=0.
        self.daughmip=0.


    def startTool(self):

        self._gaudi = GaudiPython.AppMgr()
        if self._gaudi.state()==1: self._gaudi.initialize()

        self._bdtstool=self._gaudi.toolsvc().create("BsMuMuBDTSelectionToolX",interface="IBsMuMuBDTSelectionTool")
        self.toolStarted=True

    
    def calculate(self):
        res_flat=Double(0)
        res_unflat=Double(0)
        invars = std.vector('double')()
        invars.push_back(self.bips)
        invars.push_back(self.doca)
        invars.push_back(self.bvertchi2)
        invars.push_back(self.dira)
        invars.push_back(self.bip)
        invars.push_back(self.daughmip)

        if not self.toolStarted: self.startTool()

        sc=self._bdtstool.getBDTValFromVars(invars,res_flat,res_unflat)
        if sc.isFailure(): return -1.,-1.
        return float(res_flat),float(res_unflat)


    def calculateInCERNntuple(self,t1):
        self.bips=getattr(t1,"Bips_r")
        ## always with respect to muons...
        self.doca=getattr(t1,"DOCA")
        ## jpsichi2 same as Vchi2 for b->hh/mumu!
        self.bvertchi2=getattr(t1,"JPsiChi2")
        self.dira=getattr(t1,"DIRA")
        self.bip=getattr(t1,"Bip_r")
        ## always with respect to muons...
        self.daughmip=getattr(t1,"minIPdaug")
        return self.calculate()


    def addBDTS_cx_fromVars(self, algo, CandidateInfo, Done):

        CandidateInfo["minIPdaug"] = min(CandidateInfo["mu1mip"],CandidateInfo["mu2mip"])
        self.bips=CandidateInfo["Bips_r"]
        ## always with respect to muons...
        self.doca=CandidateInfo["DOCA"]
        ## jpsichi2 same as Vchi2 for b->hh/mumu!
        self.bvertchi2=CandidateInfo["JPsiChi2"]
        self.dira=CandidateInfo["DIRA"]
        self.bip=CandidateInfo["Bip_r"]
        ## always with respect to muons...
        self.daughmip=CandidateInfo["minIPdaug"]
        res_flat,res_unflat=self.calculate()
        CandidateInfo["BDTS_cx"]=res_flat
        CandidateInfo["BDTS_cx_unflat"]=res_unflat
        

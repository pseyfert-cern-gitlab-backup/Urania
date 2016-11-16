from Urania import *
AccessPackage("Bs2MuMu")
from SomeUtils.TMVAoperators import *
import TMVA_cut
##import TMVA_cut_conf4
from OurSites import MY_TUPLE_PATH as MY_PATH
from smartpyROOT import *


glBDT = TMVAoperator(os.environ["KS2PI0MUMUROOT"] + "/operators/TMVAClassification_BDT.class.C","BDT",TMVA_cut.variables_BDT )
#BREAK
glBDTG = TMVAoperator(os.environ["KS2PI0MUMUROOT"] + "/operators/TMVAClassification_BDTG.class.C","BDTG",TMVA_cut.variables_BDT)
glBDTD = TMVAoperator(os.environ["KS2PI0MUMUROOT"] + "/operators/TMVAClassification_BDTD.class.C","BDTD",TMVA_cut.variables_BDT)

#######################
## FLATTERING NTUPLE ##
#######################
from ROOT import TFile
signal_train, f1      = getTuple(MY_PATH + "kspi0mm_DTFMC12_Strip_GL_1_basic",thing = "T") ##ml, this doesnt change, the signal that was used for training has to be here 
f2 = TFile("/tmp/another_file_with_a_name_none_else_is_using.root", "recreate")
t2 = signal_train.CopyTree(TMVA_cut.mycutSig)
#BREAK
uf1 = DoCummulative(t2,glBDT)
uf2 = DoCummulative(t2,glBDTG)
uf3 = DoCummulative(t2,glBDTD)

import cPickle

cPickle.dump(uf1,file(os.environ["KS2PI0MUMUROOT"] + "/operators/uf_BDT_basic","w"))
cPickle.dump(uf2,file(os.environ["KS2PI0MUMUROOT"] + "/operators/uf_BDTG_basic","w"))
cPickle.dump(uf3,file(os.environ["KS2PI0MUMUROOT"] + "/operators/uf_BDTD_basic","w"))

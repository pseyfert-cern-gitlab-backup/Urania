#!/usr/bin/env python
import os, sys
import optparse
from Urania import *
AccessPackage("Bs2MuMu")
from SomeUtils.TMVAoperators import *
#import TMVA_cut_conf4 as TMVA_cut
import TMVA_cut
from OurSites import MY_TUPLE_PATH as MY_PATH
from smartpyROOT import *
from ROOT import *
import cPickle

gROOT.ProcessLine(
"struct MyStruct {\
   Float_t     structBDT;\
   Float_t     structBDTG;\
   Float_t     structBDTD;};" )

path_weights =   "./weights/"# os.environ["KS2PI0MUMUROOT"] + "/python/Ks2Pi0MuMu/weights/"
path_operators = "../../operators/"# os.environ["KS2PI0MUMUROOT"] + "/operators/"

def flatten(signal, treesig, sample):
    SAMPLE = int(float(sample))
    
    if(SAMPLE==1):
        variables = TMVA_cut.variables_BDT_nopi0
#        cut = TMVA_cut.mycutSig_nopi0
        nopi0 = "_nopi0"
    else:
        variables = TMVA_cut.variables_BDT
 #       cut = TMVA_cut.mycutSig
        nopi0 = ""

    glBDT =  TMVAoperator(path_weights + "TMVAClassification"+nopi0+"_BDT.class.C", "BDT", variables)
    glBDTG = TMVAoperator(path_weights + "TMVAClassification"+nopi0+"_BDTG.class.C","BDTG",variables)
    glBDTD = TMVAoperator(path_weights + "TMVAClassification"+nopi0+"_BDTD.class.C","BDTD",variables)

    fullpath = signal
    f1 = TFile(fullpath, "update")
    tree = f1.Get(treesig)
    
    #f2 = TFile("/tmp/another_file_with_a_name_no_one_else_is_using.root", "recreate")
    t2 = tree#.CopyTree(cut)
    
    uf1 = DoCummulative(t2,glBDT)
    uf2 = DoCummulative(t2,glBDTG)
    uf3 = DoCummulative(t2,glBDTD)
    
    cPickle.dump(uf1,file(path_operators + "uf_BDT" +nopi0+"_basic","w"))
    cPickle.dump(uf2,file(path_operators + "uf_BDTG"+nopi0+"_basic","w"))
    cPickle.dump(uf3,file(path_operators + "uf_BDTD"+nopi0+"_basic","w"))
    
    f1.Close()
    #f2.Close()
    
def add_MVA(filename, treename, sample):
    SAMPLE = int(float(sample))
    
    if(SAMPLE==1):
        variables = TMVA_cut.variables_BDT_nopi0
        nopi0 = "_nopi0"
    else:
        variables = TMVA_cut.variables_BDT
        nopi0 = ""
        
    glBDT  = TMVAoperatorFlat(path_weights + "TMVAClassification" +nopi0+"_BDT.class.C","BDT", variables,path_operators + "uf_BDT"+ nopi0+"_basic" )
    glBDTG = TMVAoperatorFlat(path_weights + "TMVAClassification"+nopi0+"_BDTG.class.C","BDTG",variables,path_operators + "uf_BDTG"+nopi0+"_basic")
    glBDTD = TMVAoperatorFlat(path_weights + "TMVAClassification"+nopi0+"_BDTD.class.C","BDTG",variables,path_operators + "uf_BDTD"+nopi0+"_basic")
    
    fullpath = filename
    
    f1 = TFile(fullpath, "update")
    tree = f1.Get(treename)
    
    mystruct = MyStruct()

    branch_BDT  = tree.Branch("DMGLBDT",  AddressOf(mystruct, "structBDT"),  "DMGLBDT/F")
    branch_BDTG = tree.Branch("DMGLBDTG", AddressOf(mystruct, "structBDTG"), "DMGLBDTG/F")
    branch_BDTD = tree.Branch("DMGLBDTD", AddressOf(mystruct, "structBDTD"), "DMGLBDTD/F")

    for entry in tree:
        mystruct.structBDT = glBDT(entry) 
        mystruct.structBDTG = glBDTG(entry) 
        mystruct.structBDTD = glBDTD(entry) 
        
        branch_BDT.Fill()
        branch_BDTG.Fill()
        branch_BDTD.Fill()
        
        #entry["VCGLBDT"] = glBDT(entry) 
        #entry["VCGLBDTG"] = glBDTG(entry) 
        #entry["VCGLBDTD"] = glBDTD(entry) 
    
    tree.Write("",TObject.kOverwrite)
    f1.Close()
       
#add_MVA("K3pi_GL.root","T",0)

#flatten("MC_FULL_GL_1.root", "T", 0)#options.sample)
#add_MVA("MC_FULL_GL_2.root", "T", 0)#options.sample)
#add_MVA("TIS_FULL_GL_2.root", "T", 0)
#add_MVA("TIS_FULL_GL_1.root", "T", 0)

def main():
    parser = optparse.OptionParser()
    parser.add_option('-a', '--inputsigtrain', dest='inputsigtrain', help='input root file', default='./MC15_Sim09_PARTIAL_GL_2.root')
    parser.add_option('-b', '--inputsigtest', dest='inputsigtest', help='input root file', default='./MC15_Sim09_PARTIAL_GL_2.root')
    parser.add_option('-c', '--inputdata', dest='inputdata', help='input root file', default='./Data16_PARTIAL_GL_2.root')
    parser.add_option('-s', '--sample', dest="sample", help='input sample - 0 with pi0, 1 without pi0 (V0)', default=1)
    
    (options, args) = parser.parse_args()

    flatten(options.inputsigtrain, 'T', options.sample)
    add_MVA(options.inputsigtest, 'T', options.sample)
    add_MVA(options.inputdata, 'T', options.sample)
    
if __name__ == "__main__":
    main()
                                                                    

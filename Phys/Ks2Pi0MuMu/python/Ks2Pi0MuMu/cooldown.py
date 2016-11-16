#!/usr/bin/env python
import os, sys
import optparse
from Urania import *
AccessPackage("Bs2MuMu")
from SomeUtils.TMVAoperators import *
import TMVA_cut
from OurSites import MY_TUPLE_PATH as MY_PATH
from smartpyROOT import *
from ROOT import *
import cPickle

gROOT.ProcessLine(
"struct MyStruct {\
   Float_t     structBDT;\
   Float_t     structBDTG;\
   Float_t     structBDTD;\
};" );

path_weights =   os.environ["KS2PI0MUMUROOT"] + "/python/Ks2Pi0MuMu/weights/"
path_operators = os.environ["KS2PI0MUMUROOT"] + "/operators/"

def flatten(signal, treesig, sample):
    SAMPLE = int(float(sample))
    
    if(SAMPLE==1):
        variables = TMVA_cut.variables_BDT_nopi0
        cut = TMVA_cut.mycutSig_nopi0
        nopi0 = "_nopi0"
    else:
        variables = TMVA_cut.variables_BDT
        cut = TMVA_cut.mycutSig
        nopi0 = ""
    
    glBDT =  TMVAoperator(path_weights + "TMVAClassification"+nopi0+"_BDT.class.C", "BDT", variables)
    glBDTG = TMVAoperator(path_weights + "TMVAClassification"+nopi0+"_BDTG.class.C","BDTG",variables)
    glBDTD = TMVAoperator(path_weights + "TMVAClassification"+nopi0+"_BDTD.class.C","BDTD",variables)

    fullpath = MY_PATH + signal
    f1 = TFile(fullpath, "update")
    tree = f1.Get(treesig)
    
    f2 = TFile("/tmp/another_file_with_a_name_no_one_else_is_using.root", "recreate")
    t2 = tree.CopyTree(cut)
    
    uf1 = DoCummulative(t2,glBDT)
    uf2 = DoCummulative(t2,glBDTG)
    uf3 = DoCummulative(t2,glBDTD)
    
    cPickle.dump(uf1,file(path_operators + "uf_BDT" +nopi0+"_basic","w"))
    cPickle.dump(uf2,file(path_operators + "uf_BDTG"+nopi0+"_basic","w"))
    cPickle.dump(uf3,file(path_operators + "uf_BDTD"+nopi0+"_basic","w"))
    
    f1.Close()
    f2.Close()
    
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
    
    fullpath = MY_PATH + filename
    
    f1 = TFile(fullpath, "update")
    tree = f1.Get(treename)
    
    mystruct = MyStruct()
    
    branch_BDT  = tree.Branch("VCGLBDT",  AddressOf(mystruct, "structBDT"),  "BDT/F")
    branch_BDTG = tree.Branch("VCGLBDTG", AddressOf(mystruct, "structBDTG"), "BDTG/F")
    branch_BDTD = tree.Branch("VCGLBDTD", AddressOf(mystruct, "structBDTD"), "BDTD/F")

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
       

def main():
    parser = optparse.OptionParser()
    parser.add_option('-i', '--signal', dest='signal', help='signal root file', default='kspi0mumu_ntupleMC12_Up_V0_2_GL.root')
    parser.add_option('-b', '--background', dest='background', help='background root file', default='kspi0mumu_ntupleData15_TIS_2_GL.root')
    parser.add_option('-t', '--treesig', dest='treesig', help='name of the signal ROOT tree inside the ROOT file', default='T')
    parser.add_option('-o', '--treebkg', dest='treebkg', help='name of the background ROOT tree inside the ROOT file', default='T')
    parser.add_option('-s', '--sample', dest="sample", help='input sample - 0 with pi0, 1 without pi0 (V0)', default=1)    
    
    (options, args) = parser.parse_args()
    
    flatten(options.signal, options.treesig, options.sample)
    add_MVA(options.signal, options.treesig, options.sample)
    add_MVA(options.background, options.treebkg, options.sample)

if __name__ == "__main__":
    main() 

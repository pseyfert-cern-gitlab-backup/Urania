from ROOT import *
gROOT.SetBatch(True)
import os

#This file contains some functions used in profile2013_Siim.py
#to build the fit model, BDT cuts, categories, etc.


#------------------------------------------------------------------#
#Build the BDT cuts for every category
def BDT_cuts(bdtname, Binning):
    BDT = {}
    for i  in range(len(Binning[bdtname])-1):
        BDT[i+1] =  "&& "+bdtname+">=" + str(Binning[bdtname][i]) +" && "+bdtname+"<" + str(Binning[bdtname][i+1])
    return BDT
#------------------------------------------------------------------#

#Check if path exists, if so get the tree
def readTree(file,treeName):
    if os.path.exists(file):
        print '   Tree found at: ', file
        f = TFile(file)
        tree = f.Get('DecayTree')
        print ' Entries: ', tree.GetEntries()
        return tree
    else: return 'FileNotThere'
#------------------------------------------------------------------#

#Data object that contains the tree
class dataObj:

    def __init__(self, nTupleName, opts = {}):
        self.name = nTupleName
        #THE CHANNELS IN THE FILES
        self.t_name = 'B2MuMuTuple/DecayTree'
        if opts.get('channel','Bmumu')=='Bs': self.t_name = 'B2JpsiPhiTuple/DecayTree'
        if opts.get('channel','Bmumu')=='Bhh': self.t_name = 'B2HHTuple/DecayTree'
        if opts.get('channel','Bmumu')=='Bmumu': self.t_name = 'B2MuMuTuple/DecayTree'
        if opts.get('channel','Bmumu')=='Bd': self.t_name = 'B2JpsiKst/DecayTree'

        if nTupleName is 'UB_2013':
            self.lumi = 2.12 + 9.12 + 101 + 112 + 59 + 112 + 124 + 124 + 124 + 133 + 122+ 119+ 153 + 106 + 126 + 115 + 115 + 116 + 93 + 63 + 134 + 139 + 146 + 80 + 85 + 123 + 135 + 141 + 35

            dir = '/castor/cern.ch/user/r/rvazquez/UB20'
            files = ['DiMuon_Strip20_140213_a_2.12pb.root'
                ,'DiMuon_Strip20_140213_b_9.12pb.root'
                ,'DiMuon_Strip20_170113_a_101pb.root'
                ,'DiMuon_Strip20_170113_b_112pb.root'
                ,'DiMuon_Strip20_170113_c_059pb.root'
                ,'DiMuon_Strip20_170113_d_112pb.root'
                ,'DiMuon_Strip20_170113_e_124pb.root'
                ,'DiMuon_Strip20_170113_f_124pb.root'
                ,'DiMuon_Strip20_170113_g_124pb.root'
                ,'DiMuon_Strip20_170113_h_133pb.root'
                ,'DiMuon_Strip20_170113_i_122pb.root'
                ,'DiMuon_Strip20_170113_j_119pb.root'
                ,'DiMuon_Strip20_170113_k_153pb.root'
                ,'DiMuon_Strip20_241112_a_106pb.root'
                ,'DiMuon_Strip20_241112_b_126pb.root'
                ,'DiMuon_Strip20_241112_c_115pb.root'
                ,'DiMuon_Strip20_241112_d_115pb.root'
                ,'DiMuon_Strip20_241112_e_116pb.root'
                ,'DiMuon_Strip20_241112_f_093pb.root'
                ,'DiMuon_Strip20_241112_g_063pb.root'
                ,'DiMuon_Strip20r1_Down_134pb.root'
                ,'DiMuon_Strip20r1_Down_139pb.root'
                ,'DiMuon_Strip20r1_Down_146pb.root'
                ,'DiMuon_Strip20r1_Down_80pb.root'
                ,'DiMuon_Strip20r1_Down_85pb.root'
                ,'DiMuon_Strip20r1_Up_123pb.root'
                ,'DiMuon_Strip20r1_Up_135pb.root'
                ,'DiMuon_Strip20r1_Up_141pb.root'
                ,'DiMuon_Strip20r1_Up_35pb.root']

            self.tree = TChain(self.t_name) #Chain can be treated as a TTree object
            for f in files: self.tree.Add(dir+'/'+f)
            print '    Tree ',self.t_name,' from ',self.name,' data has been imported!'

#------------------------------------------------------------------#



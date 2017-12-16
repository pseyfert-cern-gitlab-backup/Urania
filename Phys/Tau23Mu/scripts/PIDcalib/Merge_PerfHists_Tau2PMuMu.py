#script to merge all the histograms from output of Test_PerfHist.cpp from different
#run ranges as a proper weighted average

import os, time
from ROOT import *

#PIDCalibRoot = '/afs/cern.ch/user/j/jrharris/cmtuser/Erasmus_v7r0p1/PIDCalib/PIDPerfScripts/x86_64-slc5-gcc43-opt/'
#PIDCalibRoot = '/afs/cern.ch/work/j/jrharris/public/Tau2PMuMu/PIDCalib/'
PIDCalibRoot = '/work/pseyfert/cmtuser/Erasmus_v8r1/PIDCalib/PIDPerfScripts/x86_64-slc5-gcc43-opt/'

def EqualKeys(list1,list2) :
    namelist1 = []
    namelist2 = []
    for i in list1 :
        namelist1.append(i.GetName())
    for i in list2 :
        namelist2.append(i.GetName())

    #return 1 if the lists of keys are the same, 0 if not
    if (namelist1==namelist2) :
        return 1
    else : return 0


def Merge(Mode,data):
    dummyList = os.listdir(PIDCalibRoot)
    fileList = []
    #filtering the list of files in that directory to what I want to merge
    #namely: files containing perfhists, that were produced for the same mode, produced from the same
    #data type (Data or MC). merging MagUp and MagDown
    for i in dummyList :
        if ((i.find('Minus')!=-1) | (i.find('Plus')!=-1)) & (i.find('PerfHist')!=-1) & (i.find(Mode)!=-1) & (i.find('Merged')==-1) & (i.find('merged')==-1) & (i.find('.root')!=-1): fileList.append(i)
        
    for i in fileList:
        print "will merge ", i
    #master file is first in list
    file = TFile(PIDCalibRoot+fileList[0])
    keylist = file.GetListOfKeys()

    #checking that all the files contain the same keys as master file
    for i in fileList :
        f = TFile(PIDCalibRoot+i)
        if (EqualKeys(keylist,f.GetListOfKeys())==0) :
            print keylist
            print f.GetListOfKeys()
            print 'Keys not equal!'
            exit()

    #dictionary of the hists in master file, to which all others will be added
    histdict = {}
    for i in keylist :
        histdict[i.GetName()] = file.Get(i.GetName())
    for i,j in histdict.iteritems() :
        #set kIsAverage bit so that the added histograms are averages
        j.SetBit(TH1.kIsAverage)

    
    for i in fileList :
        #if file is not master file process the contents and update histdict
        if (PIDCalibRoot+i!=file.GetName()) :
            tempdict = {}
            f = TFile(PIDCalibRoot+i)
            list = f.GetListOfKeys()
            for j in list :
                tempdict[j.GetName()] = f.Get(j.GetName())
            for k,v in tempdict.iteritems() :
                v.SetBit(TH1.kIsAverage)
                histdict[k].Add(histdict[k],v)

    #writing the output in the same directory
    outfile = TFile(PIDCalibRoot+'PerfHist_'+Mode+'_charged_merged.root','recreate')
    outfile.cd()
    for name,hist in histdict.iteritems() :
        hist.Write()
    outfile.Close()
    print 'Merged '+Mode+' '+data        

#all my modes
#Modes = ['Protons',
#         'Muons']
#Modes = ['Muons']
Modes = ['027','057','075','081']

#Modes = ['Protons']

#Merge All
for i in Modes :
    Merge(i, 'MC')        

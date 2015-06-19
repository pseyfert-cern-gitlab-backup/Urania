import ROOT
from ROOT import TFile, TString, TTree, TRandom3, TStopwatch

import sys
from sys import argv

if len(sys.argv) != 7 :
    print "tuplesampler:  randomly samples an ntuple into two files of size specified by ratio"
    print "author:        Conor Fitzpatrick, 2008"
    print "Syntax: " , sys.argv[0] , " <input.root> <path/to/ntuple> <ratio> <seed> <output1.root> <output2.root>"
    sys.exit(1)

inname = argv[1]   
tpath = argv[2]   
ratio = float(argv[3])
soutname1 = argv[5]
soutname2 = argv[6]
rndGen = TRandom3(int(argv[4]))
sw=TStopwatch()
print "opening " , inname 

inf = TFile.Open( inname )
slash = "/"

print "getting tree " , tpath 
inTree = inf.Get(tpath)
tpath=tpath.split(slash)[0]
total =  inTree.GetEntries()

sout1 = TFile(soutname1,"RECREATE")
sout1.mkdir(tpath)
sout1.cd(tpath)	
soutTree1 = inTree.CloneTree(0)

sout2 = TFile(soutname2,"RECREATE")
sout2.mkdir(tpath)
sout2.cd(tpath)	
soutTree2 = inTree.CloneTree(0)

print "--------TUPLESAMPLER - Conor Fitzpatrick, 2008 ----------" 
print "sampling from:         " , tpath     
print "in file:               " , inname      
print "with ratio:            " , ratio     
print "to file:               " , soutname1   
print "remainder in:          " , soutname2   
print "---------------------------------------------------------" 
#inTree.Print()
k = 0
pc = 0
sw.Start()
for i in range(total):
    inTree.GetEntry(i)
    if(rndGen.Rndm() < ratio):
        soutTree1.Fill()
    else:
        soutTree2.Fill()
        
    pc = ((100*i)/total)
    if(pc == k+10):
        k = pc
        print pc , "% complete \r",
        sys.stdout.flush()
	
print "100" , "% complete\r" 
out1 =  soutTree1.GetEntries()
out2 =  soutTree2.GetEntries()

sout1.Write()
sout2.Write()
sout1.Close()
sout2.Close()
sw.Stop()

print "--------------------------------------------------------" 
print "Input contained   " , total , " events" 
print "Output 1 contains " , out1 , " events" 
print "Output 2 contains " , out2 , " events" 
outRat = (out1*1.0)/(total*1.0)
from math import sqrt
doutRat = sqrt(outRat*(1.0-outRat)/(total*1.0))
print "Sampled ratio: " , outRat,"+\\-", doutRat 

print "--------------------------------------------------------" 
sw.Print()
print "done." 

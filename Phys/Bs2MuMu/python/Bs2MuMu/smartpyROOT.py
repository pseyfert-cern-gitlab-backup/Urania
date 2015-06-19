from ROOT import *
from SomeUtils.alyabar import vector
from math import sqrt
#from BsMuMuPy.pyUtils.integral import normintegralH
from Bs2MuMu.RTuple import RTuple
from Bs2MuMu.XTuple import XTuple
import string
from SomeUtils.dataManage import *
from SomeUtils.dataManage_part2 import *
from SomeUtils.someFunctions import *


def infGpoints(h,N):
	l = []
	l.append(h.GetBinLowEdge(1))
	l.append(h.GetBinLowEdge(h.GetNbinsX()+1))
	l2 =[]
	for i in range(2,h.GetNbinsX()):
		dx = h.GetBinCenter(i+1) - h.GetBinCenter(i-1)
		dy = abs(h.GetBinContent(i-1) - h.GetBinContent(i+1))
		l2.append([dy*1./dx,h.GetBinCenter(i)])
	l2.sort()
	l2.reverse()
	for i in range(N):
		l.append(l2[i][1])
	l.sort()
	return l

   ####
def translate(name):
    """Converts .xroot file into .root file
    """
    filename = name+".xroot"
    f = open(filename,"r")
    lines = f.readlines()
    print " number of rows ",len(lines)-1
    labels = lines[0].split()
    rlabels = map(lambda x: x+"/F",labels)
    tup = RTuple(name,rlabels)
    for line in lines[1:]:
        words = line.split()
        vars = map(float,words)
        for i in range(len(labels)):
            tup.fillItem(labels[i],vars[i])
        tup.fill()
    tup.close()


def savevents(b,chose):
    """
    """
    f=open(chose+"_evt.txt","w")
    string=""
    for event in b[chose]:
            string = string +str(event[0]["evt"])+" "


    f.write(string)
    f.close()

def fromRootToListDic(t,labels = []):
    """fromRootToListDic( root tuple )
    Converts a Root Tuple in a list of Dictionaries
    """
    print "creating list of dictionaries from Root Tuple"
    N=t.GetEntries()
    labels2 = []
    list=[]
    a=t.GetListOfBranches()
    if not labels:
	    for branch in a:
		    labels.append(branch.GetName())
    for label in labels:
	    if hasattr(t,label): labels2.append(label)
	    else: print "ignoring ", label
    for i in range(N):
        thing={}
        t.GetEntry(i)
        for label in labels2:
            thing[label]=getattr(t,label)
        list.append(thing)
    labels = []
    return list


def fromRootToDictionary(t):
    print "creating dictionary from Root Tuple"
    N=t.GetEntries()
    #labels=[]
    #list=[]
    output = {}
    a=t.GetListOfBranches()
    #n01 = len(a)
    
    for branch in a:
        label = branch.GetName()
        output[label] = N*[0.]
    for i in range(N):
        #thing={}
        t.GetEntry(i)
        for label in labels:
            output[label][i]=getattr(t,label)
        #list.append(thing)
    return output

def saveInTuple(list,name,type="R",tname = "T", keytypes = {}):
    """saveInTuple( list of dictionaries, filename , type = 'R')
    Saves the data in a .xroot ( type = 'X' ) or .root file (type = 'R' )
    """
    if keytypes == {}:
	    for key in list[0].keys(): keytypes[key] = "F"
    
    print "saving data"
    labels=[]
    vvv=vector(0,0,0)
    if len(list)==0:
        print "list size = 0"
        return 0
    for i in range(4):
        if 'has_key' in dir(list[0]):break
        list=desagrupate(list)
    for key in list[0].keys():
        if (dir(list[0][key])==dir(vvv))or(dir(list[0][key])==dir(labels)):
                                             
            s=len(list[0][key])
            for j in range(s):                                                        
                labels.append(key+str(j+1)+"/" + keytypes[key])
        else: labels.append(key+"/"+keytypes[key])
    if type in ["X", "ASCII"]:
        TUP=XTuple(name,labels)
    if type=="R":
        TUP=RTuple(name,labels,tname)
    if type=="M":
        TUP=MTuple(name,labels)
    for thing in list:
        for key in thing.keys():
            if key+"1/" + keytypes[key] in labels:
                s=len(thing[key])
                for j in range(s):
                    TUP.fillItem(key+str(j+1),thing[key][j])
            else: TUP.fillItem(key,thing[key])
        TUP.fill()
    TUP.close()
    
def getTuple(n,type="R",thing = "T"):
    """Extracts the tuple from a .root file
    """
    if type == "R":
        n=n+".root"
        print "getting file "+n
        
        file=TFile(n)
        t=file.Get(thing)
    if type=="X":
        translate(n)
        t,file=getTuple(n,"R")
    return t,file

def savage(t):
    """savage( root tuple ) plots the histogram of each key in tuple
    DANGER: Use very very carefully
    """
    a=t.GetListOfBranches()
    n=0
    for i in range(len(a)):
        if a[i]: n= n+1
        else: break
    size0=sqrt(n)
    size1=int(size0)
    if size0==size1: size=size1
    else: size=size1+1
    print size,n
    c=TCanvas()
    c.Divide(size,size)
    for i in range(n):
        c.cd(i+1)
        t.Draw(a[i].GetName())
    return c

## def makeTMVAfile(listdicS,listdicB,name):
##     file = TFile(name+".root","recreate")
##     triS = TTree("TreeS","TreeS")
##     n = len(listdicS)
##     kis = listdicS[0].keys()
##     a ={}
##     b ={}
    
##     for ki in kis:
##         #a = 0.
##         a[ki] = array("f",[0])
##         triS.Branch(ki,a[ki],ki+"/F")
##     for entry in listdicS:
##         for ki in kis:
##             value = entry[ki]
##             value = float(value)
##             a[ki] = value
##         triS.Fill()
##     triB = TTree("TreeB","TreeB")
##     n = len(listdicB)
##     kis = listdicB[0].keys()
##     for ki in kis:
##         #a = 0.
##         b[ki] = array("f",[0])
##         triB.Branch(ki,b[ki],ki+"/F")
##     for entry in listdicB:
##         for ki in kis:
##             value = entry[ki]
##             value = float(value)
##             b[ki] = value
    
##         triB.Fill()
##     file.Write()
##     file.Close()
##     return True
    
def convertInGraph(histo):
    N = histo.GetNbinsX()
    g = TGraph()
    for i in range(N):
        x = histo.GetBinLowEdge(i) + 0.5*histo.GetBinWidth(i)
        y = histo.GetBinContent(i)
        g.SetPoint(i,x,y)
    return g

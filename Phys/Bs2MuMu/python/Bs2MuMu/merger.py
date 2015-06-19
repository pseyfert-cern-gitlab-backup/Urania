from ROOT import *

import os

LBD5 = "/afs/cern.ch/project/lbcern/vol5/diegoms/"

os.system("whoami>eraseme.txt")
user = file("eraseme.txt").readlines()[0][:-1]
os.system("rm eraseme.txt")
print user

def merge(filename,n, lost =[], path = "Bs2MuMu/Bs2MuMu",s = "Bs", folder = os.environ["HOME"]+"/NTuples/"):
    ch = TChain(path)
    for i in range(n):
        if i in lost: continue
        ch.Add(folder + filename + "_"+ str(i) + ".root")
    ch.Merge(folder + filename + "_" + s + ".root")
    return 1


    
def CopyFromCastor(filename,n, lost =[], folder = "/tmp/"+user + "/"):
    for i in range(n):
        if i in lost: continue
        print i
        os.system("rfcp " + os.environ["CASTOR_HOME"] +"/"+ filename + "_"+str(i) + ".root " + folder)
    return 1

#CopyFromCastor("/V02010/D02Kpi",49,[],"D02Kpi/D02Kpi","Tot")

def check_duplicates(t):
    d, d2  = {}, {}
    l = []
    for entry in t:
        run, evt = entry.runNum, entry.evtNum
        if run not in d.keys(): d[run], d2[run] = [], []
        if evt not in d[run]: d[run].append(evt)
        else:
            d2[run].append(evt)
    for entry in t:
        run, evt = entry.runNum, entry.evtNum
        if evt in d2[run]:
            l.append([run, evt, entry.evt, getattr(entry,"Bmass")])
    l.sort()
    for x in l: print x
        
            
    return d, d2,l
        
    

s1 = "DOCA<0.3 && mu1_track_Chi2DoF<5 && mu2_track_Chi2DoF<5 && Bips<5 && Bmass>4769.6 && Bmass< 5969.6"
s2 = "mu1_track_Chi2DoF<5 && mu2_track_Chi2DoF<5 && Bips<5 && Bmass>4769.6 && Bmass< 5969.6"
shh = s1 + " && Bdissig>15 && lessIPSmu>5 && Vchi2<9"
sBu = s1 + " && dDsig>15 && k1ips>5 && JPsiChi2<9"
sBu2 = s2 + " && dDsig>15 && k1ips>5"

sBd2 = s2 + " && dDsig>15 &&kstips>5"

def mergeAll(filename,n,lost = [], folder = "/scratch/diegoms/NTuples/",paths = ["Bs2MuMu","Bu2JPsiK","B2hh", "Bs2JPsiPhi", "Bd2JPsiKstar"] ):
    #paths = ["Bs2MuMu","Bu2JPsiK","B2hh", "Bs2JPsiPhi", "Bd2JPsiKstar"]
    #paths += ["Bu2JPsiKUnbiased", "Bs2JPsiPhiUnbiased","Bs2JPsiPhiDetached"]
    
    files, trees= {}, {}
    for path in paths:
        merge(filename, n ,lost, path +"/"+path , path +"eraseme",folder)
        files[path] = TFile(folder +"/"+filename+ "_"+path + "eraseme.root")
        trees[path] = files[path].Get(path)
    out = TFile(folder + "/"+filename +"_merged.root","recreate")
    for path in paths:
        if not isinstance(trees[path],TTree):continue
        t = trees[path].CopyTree("1")
        t.Write()
    out.Close()
    os.system("rm  " + folder + "*eraseme*")
    
def mergeSamples(filenames, finalname, folder = "/scratch/diegoms/NTuples/",paths = ["T"],ofolder =  "/scratch/diegoms/NTuples/"):
    #paths = ["Bs2MuMu","Bu2JPsiK","Bd2JPsiKstar","B2hh", "Bs2JPsiPhi"]#, "JPsi2MuMu"]
    #paths += ["Bu2JPsiKUnbiased", "Bs2JPsiPhiUnbiased","Bs2JPsiPhiDetached"]
    
    #paths = ["Bs2MuMu","Bu2JPsiK","Bd2JPsiKstar", "Bu2JPsiKUnbiased", "B2hh","Bs2JPsiPhiUnbiased","Bs2JPsiPhiDetached","Bs2JPsiPhi"]
    ch = {}
    files, trees= {}, {}
    for path in paths:
        if path.find("/") != -1:
            path0 = path[:path.find("/")]
        else : path0 = path
        ch = TChain(path )#+"/"+path)
        for filename in filenames:
            print filename
            os.system("ls -l " + folder + filename + ".root")
            ch.Add(folder +"/"+filename +".root")
        ch.Merge(ofolder +"/"+ finalname+"_"+path0+"eraseme.root")
       
        files[path] = TFile(ofolder +"/"+finalname+ "_"+path0 + "eraseme.root")
        trees[path] = files[path].Get(path0)
    out = TFile(ofolder + "/"+finalname +"_merged.root","recreate")
    for path in paths:
        t = trees[path].CopyTree("1")
        t.Write()
    out.Close()
    os.system("rm  " + folder + "*eraseme*")
    
#mergeSamples(["MC10_B02Kpi_sm1_2011_md_j132","MC10_B02Kpi_sm1_2011_mu_j143"],"MC10_B02Kpi_sm1_2011", folder = "/afs/cern.ch/lhcb/group/physics/bsmumu/ntuples/2011/smearedMC/",paths = ["B2hh"], ofolder = "~/vol5/NTuples")
## cuts = "Bips<5 && PIDk>0 && PIDpi<0 && Vchi2<15 && lessIPS > 3 && Kst_pt>900 && Jpsi_pt>900 && sqrt(mu2p1**2+mu2p2**2)>500 && sqrt(mu1p1**2+mu1p2**2)>500 && kaon_pt>500 && pion_pt>500 && JPsiChi2<9 && KstChi2<9 && Bdissig>15"


## from ROOT import *

## #xError: invalid syntax
## fmc = TFile('/afs/cern.ch/project/lbcern/vol5/diegoms/NTuples/bdjpsikst_constrained_jpsiMCmc10d.root')
## tmc = fmc.Get("Bd2JPsiKstar/Bd2JPsiKstar")
## from BsMuMuPy.pyAna import B2JpsiModels as B
## from BsMuMuPy.pyAna import distribution as D


## cuts0 = "Bips<5&& PIDpi<0 && Vchi2<15 && lessIPS > 3 && Kst_pt>900 && Jpsi_pt>900 && sqrt(mu2p1**2+mu2p2**2)>500 && sqrt(mu1p1**2+mu1p2**2)>500 && kaon_pt>500 && pion_pt>500 && JPsiChi2<9 && KstChi2<9 && Bdissig>15"


## cutspi = "Bips<5&& PIDk>0 && abs(KstMass-895.94)<40 && Vchi2<15 && lessIPS > 3 && Kst_pt>900 && Jpsi_pt>900 && sqrt(mu2p1**2+mu2p2**2)>500 && sqrt(mu1p1**2+mu1p2**2)>500 && kaon_pt>500 && pion_pt>500 && JPsiChi2<9 && KstChi2<9 && Bdissig>15"
## #hmc0 = D.do_distribution(tmc, B.DoubleGaussian, "GLsb.", [0.,.2,.4,.6,.8,1.], cuts + "&& Bmass>4900 && Bmass<5320 && lessIPS>3")
## hmc0 = D.do_distribution(tmc, B.SigGaussFiter, "sqrt(p1p1**2+p1p2**2+p1p3**2)", range(0,80000,10000) + [200000], cutspi + "&& Bmass>4900 && Bmass<5320 &&  JPsi_Dsig>13 && lessIPS>3 && mu1ips>5 && mu2ips>5 && L0Decision&& Hlt1Decision&& Hlt2Decision")

## hmc = D.do_distribution(tmc, B.SigGaussFiter, "sqrt(p1p1**2+p1p2**2+p1p3**2)", range(0,80000,10000) + [200000], cutspi + "&& PIDpi<0 && Bmass>4900 && Bmass<5320 &&  JPsi_Dsig>13 && lessIPS>3 && mu1ips>5 && mu2ips>5 && L0Decision&& Hlt1Decision&& Hlt2Decision")

## f = TFile('/afs/cern.ch/project/lbcern/vol5/diegoms/NTuples/stp12_constrained_jpsi_BdAP.root')
## t = f.Get("T")

## hd0 = D.do_distribution(t, B.SigGaussFiter, "sqrt(p1p1**2+p1p2**2+p1p3**2)", range(0,80000,10000) + [200000], cutspi + "&&Bmass>4900 && Bmass<5320 &&  JPsi_Dsig>13 && lessIPS>3 && mu1ips>5 && mu2ips>5 && L0Decision&& Hlt1Decision&& Hlt2Decision")

## hd = D.do_distribution(t, B.SigGaussFiter, "sqrt(p1p1**2+p1p2**2+p1p3**2)", range(0,80000,10000) + [200000], cutspi + "&& PIDpi < 0 && Bmass>4900 && Bmass<5320 &&  JPsi_Dsig>13 && lessIPS>3 && mu1ips>5 && mu2ips>5 && L0Decision&& Hlt1Decision&& Hlt2Decision")

## ## h = D.do_distribution(t, B.DoubleGaussian, "GLsb.", [0.,.2,.4,.6,.8,1.], cuts + "&& Bmass>4900 && Bmass<5320 &&  JPsi_Dsig>13 && mu1ips>5 && mu2ips>5 && L0Decision && Hlt1Decision && Hlt2Decision")

## ## L0exMu = "(L0HadronDecision || L0ElectronDecision || L0Tis || L0PhotonDecision)"
## ## Hlt1ExMu = '(Hlt1TrackAllL0Decision||Hlt1TrackPhotonDecision||Hlt1DiHadronDecision||Hlt1SingleHadronDecision || Hlt1Tis)'
## ## Hlt2ExMu = '(Hlt2Bs2PhiGammaDecision||Hlt2CharmOSTF3BodyDecision||Hlt2CharmOSTF2BodyDecision||Hlt2IncPhiDecision||Hlt2TopoOSTF2BodyDecision||Hlt2BiasedTFDiElectronDecision||Hlt2TopoOSTF3BodyDecision||Hlt2TopoOSTF4BodyDecision||Hlt2CharmOSTF3BodyWideMassDecision||Hlt2CharmOSTF2BodyWideMassDecision||Hlt2Bd2KstGammaDecision||Hlt2B2HHDecision||Hlt2Tis)'


def mergeG(filename ="Output",jobs = {},path = "Bs2MuMu/Bs2MuMu", folder = "/scratch/diegoms/gangadir/workspace/diegoms/LocalXML/",s = "Bs"):
    ch = TChain(path)
    for job in jobs.keys():
        if jobs[job] == "X":  ch.Add(folder + "/"+ str(job) + "//output/" + filename + ".root")
        else:
            for i in range(jobs[job]): ch.Add(folder + "/"+ str(job) + "/" + str(i) + "/output/" + filename + ".root")
    ch.Merge(folder + filename + "_" + s + ".root")
    return 1


def mergeAllG(filename ="Output",jobs = {}, folder = "/scratch/diegoms/gangadir/workspace/diegoms/LocalXML/", paths = ["Bs2MuMu","Bu2JPsiK","B2hh", "Bs2JPsiPhi", "Bd2JPsiKstar"], ofolder = 0):
   
    #paths += ["Bu2JPsiKUnbiased", "Bs2JPsiPhiUnbiased","Bs2JPsiPhiDetached"]
    if not ofolder : ofolder = folder
    files, trees= {}, {}
    for path in paths:
        mergeG(filename, jobs , path +"/"+path ,folder, s = path + "eraseme")
        files[path] = TFile(folder +"/"+filename+ "_"+path + "eraseme.root")
        trees[path] = files[path].Get(path)
    out = TFile(ofolder + "/"+filename +"_merged.root","recreate")
    for path in paths:
        if not isinstance(trees[path],TTree):continue
        t = trees[path].CopyTree("1")
        t.Write()
    out.Close()
    os.system("rm  " + folder + "*eraseme*")
    

def merge4MuG(filename ="B24Mu",jobs = {}, folder = "/scratch/diegoms/gangadir/workspace/diegoms/LocalXML/"):
    paths = ["B24mu","Bd2JPsiKstar"]
    #paths += ["Bu2JPsiKUnbiased", "Bs2JPsiPhiUnbiased","Bs2JPsiPhiDetached"]
    
    files, trees= {}, {}
    for path in paths:
        mergeG(filename, jobs , path +"/"+path ,folder, s = path + "eraseme")
        files[path] = TFile(folder +"/"+filename+ "_"+path + "eraseme.root")
        trees[path] = files[path].Get(path)
    out = TFile(folder + "/"+filename +"_merged.root","recreate")
    for path in paths:
        if not isinstance(trees[path],TTree):continue
        t = trees[path].CopyTree("1")
        t.Write()
    out.Close()
    os.system("rm  " + folder + "*eraseme*")

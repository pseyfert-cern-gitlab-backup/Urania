from smartpyROOT import *
from SomeUtils.alyabar import *

import os, cPickle




def prepareBs2MuMu(tree,outputfile, debug = False):
    names = []
    labels = []
    debug = int(debug)
    a = tree.GetListOfBranches()
    for branch in a:
        names.append(branch.GetName())
        labels.append(branch.GetName() + "/F")
    
    ls = ["life_ps/F","lessIPSmu/F","Bip/F","DOCA/F","life/F"]
   
        
    for i in range(len(gl.keys)):
        ls.append("GLs"+str(i)+"./F")
        ls.append("GLn"+str(i)+"./F")
   
    ls.append("GLsb./F")
    #labels.append("PIDLdelta./F")
    ls.append("GLdelta./F")
    ls.append("GLchi2s./F")
    ls.append("GLchi2b./F")   
    ls.append("angle/F")
    for l in ls:
        if l not in labels: labels.append(l)
    tup = RTuple(outputfile,labels)
    
    rangeN = range(tree.GetEntries())
    rdr = {"DOCA":-1.,"lessIPSmu":-1.,"mu1iso":-1.,"mu2iso":-1., "Bip":-1., "life":-1.}
    for i in rangeN:
        tree.GetEntry(i)
        for name in names:
            tup.fillItem(name,getattr(tree,name))
        mu1o = vector(tree.mu1o1,tree.mu1o2,tree.mu1o3)
        mu2o = vector(tree.mu2o1,tree.mu2o2,tree.mu2o3)
        mu1p = vector(tree.mu1p1,tree.mu1p2,tree.mu1p3)
        mu2p = vector(tree.mu2p1,tree.mu2p2,tree.mu2p3)
        SV = vector(tree.SV1,tree.SV2,tree.SV3)
        PV = vector(tree.PV1,tree.PV2,tree.PV3)
        #print debug*i
        Bp = mu1p+mu2p
        hhh = closest_point(mu1o,mu1p,mu2o,mu2p)
        rSV = SV - PV
        life_ps = vmod(rSV)*cnv*tree.Bmass/vmod(Bp) ## in ps!!
        Bip = dpr(PV,SV,Bp)
        DOCA = 2.*vmod(hhh[0] - hhh[1])
        lessIPSmu = min(tree.mu1ips, tree.mu2ips)
        life = life_ps/1.493
        tup.fillItem("life_ps",life_ps)
        tup.fillItem("life",life)
        tup.fillItem("lessIPSmu",lessIPSmu)
        tup.fillItem("Bip",Bip)
        tup.fillItem("DOCA",DOCA)
        tup.fillItem("angle",ACO(rSV,Bp))
        
        rdr["DOCA"] = DOCA
        rdr["Bip"] = Bip
        ##rdr["life"] = life_ps
        rdr["mu1iso"] = tree.mu1iso
        rdr["mu2iso"] = tree.mu2iso
        rdr["life"] = life
        rdr["lessIPSmu"] = lessIPSmu
        
        out = gl(rdr)
        for ki in out.keys():
            tup.fillItem("GL"+ki+".",out[ki])
        #xyz.fillItem("GL",out["sb"][0])
        #xyz.fillItem("Mass",tree.Bmass)
       

        #pid1 = pid([[tree.PIDmu1],[tree.PIDmu1-tree.PIDk1]])["delta"][0]
        #pid2 = pid([[tree.PIDmu2],[tree.PIDmu2-tree.PIDk2]])["delta"][0]

        #out2 = mixer.Operator([[pid1],[pid2]])
        #for ki in out2.keys():
         #   tup.fillItem("PIDL"+ki+".",out2[ki][0])
        #xyz.fillItem("PIDL",out2["sb"][0])
        tup.fill()
        #xyz.fill()
    tup.close()
    #xyz.close()
                        
def addGL(tree,outputfile, gl, glname = "GL"):
    names = []
    labels = []
    #debug = int(debug)
    a = tree.GetListOfBranches()
    for branch in a:
        names.append(branch.GetName())
        labels.append(branch.GetName() + "/F")
    
    #ls = ["life_ps/F","lessIPSmu/F","Bip/F","DOCA/F","life/F"]
    ls = []
        
    for i in range(len(gl.keys)):
        ls.append(glname + ('isos' in dir(gl))*"m" + "s"+str(i)+"./F")
        ls.append(glname + ('isos' in dir(gl))*"m" + "n"+str(i)+"./F")
   
    ls.append(glname + "sb./F")
    #labels.append("PIDLdelta./F")
    ls.append(glname +"delta./F")
    ls.append(glname + "chi2s./F")
    ls.append(glname + "chi2b./F")
    
    #ls.append("angle/F")
    if 'isos' in dir(gl):
        ls.append(glname + "msb./F")
        #labels.append("PIDLdelta./F")
        ls.append(glname +"mdelta./F")
        ls.append(glname + "mchi2s./F")
        ls.append(glname + "mchi2b./F")   
    #ls.append("angle/F")
    for l in ls:
        if l not in labels: labels.append(l)
    tup = RTuple(outputfile,labels)
    
    rangeN = range(tree.GetEntries())
    #rdr = {"DOCA":-1.,"lessIPSmu":-1.,"mu1iso":-1.,"mu2iso":-1., "Bip":-1., "life":-1.}
    for i in rangeN:
        tree.GetEntry(i)
        for name in names:
            tup.fillItem(name,getattr(tree,name))
        rdr = {}
        for k in gl.keys:
            rdr[k] = getattr(tree,k)
        if 'isos' in dir(gl):
            for k in gl.isos:
                rdr[k] = getattr(tree,k)
        out = gl(rdr)
        for ki in out.keys():
            tup.fillItem(glname+ ki+".",out[ki])
       
        tup.fill()
        
    tup.close()
                        
def addMVA(tree,outputfile, gl, glname = "BDTflat", glkeys = []):
    names = []
    labels = []
    #debug = int(debug)
    a = tree.GetListOfBranches()
    for branch in a:
        names.append(branch.GetName())
        labels.append(branch.GetName() + "/F")
    
    #ls = ["life_ps/F","lessIPSmu/F","Bip/F","DOCA/F","life/F"]
    ls = []
        
 
    ls.append(glname + "/F")
    
    for l in ls:
        if l not in labels: labels.append(l)
    tup = RTuple(outputfile,labels)
    
    rangeN = range(tree.GetEntries())
    #rdr = {"DOCA":-1.,"lessIPSmu":-1.,"mu1iso":-1.,"mu2iso":-1., "Bip":-1., "life":-1.}
    for i in rangeN:
        tree.GetEntry(i)
        for name in names:
            tup.fillItem(name,getattr(tree,name))
        rdr = {}
        rdr["minpt"] = min(tree.mu1pt,tree.mu2pt)
        rdr["isoSum"] = tree.mu1iso5 + tree.mu2iso5
        
        for k in glkeys:
            if k == "minpt": continue
            if k == "isoSum": continue
            rdr[k] = getattr(tree,k)
        
        tup.fillItem(glname,gl(rdr))
       
        tup.fill()
        
    tup.close()
                        


def addMVAs(tree,outputfile, gl,bdt, glname, bdtname = "BDTflat", glkeys = ["Bip","Bip_r","Blife_ps","Blife_ps_r","DOCA","lessIPSmu","mu1iso5","mu2iso5","isoSum","Bpt","minpt","Cosnk","CDF_iso_CDF"]):
    names = []
    labels = []
    #debug = int(debug)
    a = tree.GetListOfBranches()
    for branch in a:
        names.append(branch.GetName())
        labels.append(branch.GetName() + "/F")
    
    #ls = ["life_ps/F","lessIPSmu/F","Bip/F","DOCA/F","life/F"]
    ls = []
        
 
    ls.append(bdtname + "/F")
    ls.append(glname + "/F")
    
    for l in ls:
        if l not in labels: labels.append(l)
    tup = RTuple(outputfile,labels)
    
    rangeN = range(tree.GetEntries())
    #rdr = {"DOCA":-1.,"lessIPSmu":-1.,"mu1iso":-1.,"mu2iso":-1., "Bip":-1., "life":-1.}
    for i in rangeN:
        tree.GetEntry(i)
        for name in names:
            tup.fillItem(name,getattr(tree,name))
        rdr = {}
        rdr["minpt"] = min(tree.mu1pt,tree.mu2pt)
        rdr["isoSum"] = tree.mu1iso5 + tree.mu2iso5
        
        for k in glkeys:
            if k == "minpt": continue
            if k == "isoSum": continue
            rdr[k] = getattr(tree,k)
        
        tup.fillItem(bdtname,bdt(rdr))
        out = gl(rdr)
        #for ki in out.keys():
        tup.fillItem(glname,out["sb"])
       
        tup.fill()
        
    tup.close()
                        
from ROOT import *
from TMVAoperators import *
import os


yury = TMVAoperatorFlat("Y9.C","BDTD",["Bip_r","DOCA","lessIPSmu","Blife_ps_r","Bpt","isoSum","CDF_iso_CDF","minpt", "Cosnk"], "Y9_U")
y6 = TMVAoperatorFlat("Y6_2iso.C","BDTG",["Bip_r","DOCA","lessIPSmu","Blife_ps_r","Bpt","mu1iso5","mu2iso5", "Cosnk"], "Y6_2iso_U")
gl = cPickle.load(file("GL_2011_r"))

fkpi = TFile("~/vol5/NTuples/MC10_B02Kpi_sm1_2011_merged.root")
tkpi = fkpi.Get("B2hh")

addMVAs(tkpi,"~/vol5/NTuples/MC10_B02Kpi_sm1_2011_BDT", gl,yury, "GL11", bdtname = "BDTflat", glkeys = ["Bip","Bip_r","Blife_ps","Blife_ps_r","DOCA","lessIPSmu","mu1iso5","mu2iso5","isoSum","Bpt","minpt","Cosnk","CDF_iso_CDF"])


fkpi = TFile("~/vol5/NTuples/MC10_Bs2Kpi_sm1_2011_merged.root")
tkpi = fkpi.Get("B2hh")

addMVAs(tkpi,"~/vol5/NTuples/MC10_Bs2Kpi_sm1_2011_BDT", gl,yury, "GL11", bdtname = "BDTflat", glkeys = ["Bip","Bip_r","Blife_ps","Blife_ps_r","DOCA","lessIPSmu","mu1iso5","mu2iso5","isoSum","Bpt","minpt","Cosnk","CDF_iso_CDF"])

fkpi = TFile("~/vol5/NTuples/MC10_B02pipi_sm1_2011_merged.root")
tkpi = fkpi.Get("B2hh")

addMVAs(tkpi,"~/vol5/NTuples/MC10_B02pipi_sm1_2011_BDT", gl,yury, "GL11", bdtname = "BDTflat", glkeys = ["Bip","Bip_r","Blife_ps","Blife_ps_r","DOCA","lessIPSmu","mu1iso5","mu2iso5","isoSum","Bpt","minpt","Cosnk","CDF_iso_CDF"])


fkpi = TFile("~/vol5/NTuples/MC10_Bs2KK_sm1_2011_merged.root")
tkpi = fkpi.Get("B2hh")

addMVAs(tkpi,"~/vol5/NTuples/MC10_Bs2KK_sm1_2011_BDT", gl,yury, "GL11", bdtname = "BDTflat", glkeys = ["Bip","Bip_r","Blife_ps","Blife_ps_r","DOCA","lessIPSmu","mu1iso5","mu2iso5","isoSum","Bpt","minpt","Cosnk","CDF_iso_CDF"])

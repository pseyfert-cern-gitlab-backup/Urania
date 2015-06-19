from ROOT import *
import os
from SomeUtils.alyabar import *

f1=TRFIOFile("/castor/cern.ch/user/o/ooleroy/stripping17b/upAndDown_2011_dimuon_dv33r0p1tag_961pb.root")
t1 = f1.Get("BdTuple/DecayTree")
f2=TRFIOFile("/castor/cern.ch/user/o/ooleroy/stripping20/updAndDown_dimuon_strip20_reco14_dv33r0p1tag_1041pb.root")
t2 = f2.Get("BdTuple/DecayTree")


sel = "muplus_MINIPCHI2 > 25 && muminus_MINIPCHI2 > 25 && Kplus_MINIPCHI2 > 4 && piminus_MINIPCHI2 > 4  && Kplus_PT > 500 && piminus_PT>500 && piminus_PIDK<-6 && Kplus_PIDK > 6 && J_psi_1S_FDCHI2_TOPPV > 169 &&  J_psi_1S_LOKI_DOCA_1_2<0.3"
sel += "&&  J_psi_1S_ENDVERTEX_CHI2 < 9 && B0_IPCHI2_OWNPV < 25"

f4 = TFile("~/vol5/BsJPsiKst_2012OL_GL.root")
t4 = f4.Get("T")

#gl.keys = ['max_DOCA', 'lessIPS', 'B0_IP_OWNPV,', 'B0_PT',"Blife_ps"] # B0_LOKI_DTF_CTAU
#def addStuff(t, name):
 #   fx =
light_cte = 3.3356409519815204
import cPickle
gl = cPickle.load(file(os.environ["BSJPSIKSTROOT"] + "/operators/GL_JPsiKst_Sept5"))

def doDOCA(t,p1name,p2name):
    n1 = p1name+ "_TRACK_FirstMeasurement"
    n2 = p2name+ "_TRACK_FirstMeasurement"
    N1 = p1name + "_P"
    N2 = p2name + "_P"
    
    o1 = vector(getattr(t,n1+"X"), getattr(t,n1+"Y"),getattr(t,n1+"Z"))
    o2 = vector(getattr(t,n2+"X"), getattr(t,n2+"Y"),getattr(t,n2+"Z"))
    p1 = vector(getattr(t,N1+"X"), getattr(t,N1+"Y"),getattr(t,N1+"Z"))
    p2 = vector(getattr(t,N2+"X"), getattr(t,N2+"Y"),getattr(t,N2+"Z"))

    hhh = closest_point(o1,p1,o2,p2)
    DOCA = 2.*vmod(hhh[0] - hhh[1])

    return DOCA
os.sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu")
from RTuple import *

def addGL(tree,outputfile, gl, glname = "GL"):
    names = []
    labels = []
    #debug = int(debug)
    a = tree.GetListOfBranches()
    for branch in a:
        name = branch.GetName()
        if "_COV_" in name: continue
        if name in ["PVX","PVY","PVZ", "PVXERR","PVYERR","PVZERR","PVCHI2","PVNDOF","PVNTRACKS","RoutingBits"]: continue
        names.append(branch.GetName())
        labels.append(branch.GetName() + "/F")

    #ls = ["life_ps/F","lessIPSmu/F","Bip/F","DOCA/F","life/F"]
    ls = ["max_DOCA/F", "lessIPS/F","Mjpsik/F", "CPsi/F", "CTheta/F"]

    ls.append(glname + "sb/F")
    ls.append(glname +"delta/F")
    ls.append(glname + "chi2s/F")
    ls.append(glname + "chi2b/F")
    for i in range(len(gl.keys)):
        ls.append(glname + "s"+str(i)+"/F")
        ls.append(glname + "n"+str(i)+"/F")
    
    for l in ls:
        if l not in labels: labels.append(l)
    tup = RTuple(outputfile,labels)

    rangeN = range(tree.GetEntries())
    rdr = {"max_DOCA":-1.,"lessIPS":-1.,"B_IP":-1., "Blife_ps":-1.}
    for i in rangeN:
        tree.GetEntry(i)
        for name in names:
            #print name
            tup.fillItem(name,float(getattr(tree,name)))
        max_DOCA = []
        max_DOCA.append(doDOCA(tree,"muplus","muminus"))
        max_DOCA.append(doDOCA(tree,"muplus","piminus"))
        max_DOCA.append(doDOCA(tree,"muplus","Kplus"))
        max_DOCA.append(doDOCA(tree,"muminus","piminus"))
        max_DOCA.append(doDOCA(tree,"muminus","Kplus"))
        max_DOCA.append(doDOCA(tree,"Kplus","piminus"))        
        max_DOCA = max(max_DOCA)
        lessIPS = psqrt(min (tree.muplus_MINIPCHI2, tree.muminus_MINIPCHI2,tree.Kplus_MINIPCHI2,tree.piminus_MINIPCHI2))
        pj = vector(tree.J_psi_1S_PX, tree.J_psi_1S_PY, tree.J_psi_1S_PZ)
        pk = vector(tree.Kplus_PX, tree.Kplus_PY, tree.Kplus_PZ)
        
        
        Mjpsik = psqrt(IM2(pj,pk, tree.J_psi_1S_M,tree.Kplus_M))
        rdr["max_DOCA"] = max_DOCA
        rdr["Blife_ps"] = tree.B0_LOKI_DTF_CTAU*light_cte
        rdr["lessIPS"] = lessIPS
        rdr["Bpt"] = tree.B0_PT
        rdr["B_IP"] = tree.B0_IP_OWNPV
                        
        #rdr = {}
        #for k in gl.keys:
         #   rdr[k] = getattr(tree,k)
        #print rdr
        out = gl(rdr)
        for ki in out.keys():
            tup.fillItem(glname+ ki,out[ki])
        tup.fillItem("max_DOCA",max_DOCA)
        tup.fillItem("lessIPS",lessIPS)
        tup.fillItem("Mjpsik",Mjpsik)
        tup.fillItem("CPsi", cos(tree.B0_ThetaVtr))
        tup.fillItem("CTheta", cos(tree.B0_ThetaTr))
                     
        tup.fill()

    tup.close()

def doSelTuple(t, name):
    fx = TFile(name, "recreate")
    tx = t.CopyTree(sel)
    tx.Write()
    fx.Close()
#doSelTuple(t1,"~/vol5/OL_2011.root")
#doSelTuple(t2,"~/vol5/OL_2012.root")
f = TFile("~/vol5/OL_2012.root")
t = f.Get("DecayTree")

addGL(t, "~/vol5/OL_2012_GL",gl)

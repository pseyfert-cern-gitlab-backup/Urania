
from BsMuMuPy.pyAna import B2hhmodels as B
from BsMuMuPy.pyMyRoot.XTuple import *
from ROOT import *
from math import *

def pidloop(t, mass = "MKpi", cuts = "GLKsb.>0.25", w = [5100,5500], var = "PIDk", sg1 = ">", sg2 = ">",rang = [-10,30], N= 20, lambda_b=1, trans = 2.3, both = 0):
    var1 = var + "1"+sg1
    var2 = var + "2"+sg2
    if sg1 == ">": s1 = 1.
    else: s1 = -1.
    if sg2 == ">": s2 = 1.
    else: s2 = -1.
    a = " && "
    both = (sg1 != sg2) or both
    print "BOTH:", both

    cuts += "&& " + mass +">"+ str(w[0]) +" && "+mass +"<"+str(w[1])
    tup = XTuple("pid_loop_on_"+mass+"_fit",["cut/F","m/F","sm/F","Nsig/F","sNsig/F","t/F","st/F", "sig/F","ssig/F","N/F", "fLambda/F","sfL/F", "mL/F","sigL/F","smL/F","ssigL/F", "mean2/F","smean2/F","fd/F","sfd/F"])
    for i in range(N):
        ct = rang[0] + i*1./(N-1)*rang[1]

        cut = cuts + a + var1 + str(s1*ct) +a + var2+str(s2*ct)
        print cut

        if both:
            op = B.TwoCBpeakFiter(t, mass, cut, add_lambda = lambda_b, transition = trans)
            tup.fillItem("fd", op.f1.getVal())
            tup.fillItem("sfd", op.f1.getError())
            tup.fillItem("mean2",op.mean2.getVal())
            sm2 = sqrt(op.mean.getError()**2 + op.d1.getError()**2)
            tup.fillItem("smean2",sm2)
            
        else: op = B.SigCBFiter(t, mass, cut, add_lambda = lambda_b, transition = trans)
            
        tup.fillItem("cut",ct)
        tup.fillItem("m",op.mean.getVal())
        tup.fillItem("sm",op.mean.getError())
        tup.fillItem("sig",op.sigma.getVal())
        tup.fillItem("ssig",op.sigma.getError())
        tup.fillItem("t",trans)
        tup.fillItem("st",0.)
        tup.fillItem("Nsig", op.nsig.getVal())
        tup.fillItem("sNsig", op.nsig.getError())
        
        if lambda_b:
            tup.fillItem("fLambda",op.fLambda.getVal())
            tup.fillItem("sfL",op.fLambda.getError())
            tup.fillItem("mL",op.meanL.getVal())
            tup.fillItem("smL",op.meanL.getError())
            tup.fillItem("sigL",op.sigmaL.getVal())
            tup.fillItem("ssigL",op.sigmaL.getError())
        
        #tup.fillItem("fbs",op.fbs.getVal())
        #tup.fillItem("sfbs",op.fbs.getError())
        tup.fill()
    tup.close()
    return op


def example():
#    from ROOT import TFile
    f = TFile('/afs/cern.ch/project/lbcern/vol5//diegoms/NTuples/merged/stp12_merged.root')
    t = f.Get("B2hh")
    pidloop(t,"MKpi", lambda_b = 0, sg2 = "<", trans = 2.5)
    pidloop(t,"Mpipi", lambda_b = 0, sg1 = "<", sg2 = "<", trans = 2.5)
    pidloop(t,"MpiK", lambda_b = 0, sg1 = "<", trans = 2.5)
    pidloop(t,"MKK", w = [5200,5600], lambda_b = 0, trans = 2.5)


def glplot(t,glname, mid = 0):
    h = TH1F(glname,glname,4,0,1)
    for entry in t:
        if entry.rmo1key!=entry.rmo2key:continue
        if entry.mo1!= entry.mo2:continue
        if not entry.rmo1isB2qq:continue
        if entry.lessIPSmu < 5: continue
        if entry.Bips > 5: continue
        if entry.Vchi2> 9: continue
        if entry.DOCA > 0.3: continue
        if entry.Bdissig<15: continue
        if mid:
            if not t.mu1_pidPreslMom: continue
            if not t.mu2_pidPreslMom: continue
            if not t.mu1_pidInAcc: continue
            if not t.mu2_pidInAcc: continue
            
        h.Fill(getattr(t,glname))
    h.SetMinimum(0)
    
    for i in range(4): h.SetBinError(i+1,sqrt(h.GetBinContent(i+1)))
    return h

## def do_comparison(h1,hmumu):
##     h = TH1F("A","A",4,0,1)
##     for i in range(4):
##         fmu = hmumu.GetBinContent(i+1)/hmumu.GetSum()
##         sfmu = hmumu.GetBinError(i+1)/hmumu.GetSum()
##         f1 = h1.GetBinContent(i+1)/h1.GetSum()
##         sf1 = h1.GetBinError(i+1)/h1.GetSum()

##         x = (f1-fmu)/fmu
##         sx = sqrt((sf1/fmu)**2 + (sfmu*(1+x)/fmu)**2)
##         h.SetBinContent(i+1,x)
##         h.SetBinError(i+1,sx)
##     return h


## def glplots(tmumu, tpipi, tkk, tkpi, glname, mid=0):
##     hmumu = glplot(tmumu,glname,mid)
##     hpipi = glplot(tpipi,glname,mid)
##     hkpi = glplot(tkpi,glname,mid)
##     hkk = glplot(tkk,glname,mid)

##     hkk.SetLineColor(kMagenta)
##     hpipi.SetLineColor(kGreen)
##     hkpi.SetLineColor(kRed)
##     c  = TCanvas()
##     hmumu.DrawNormalized("err")
##     hkpi.DrawNormalized("err same")
##     hkk.DrawNormalized("err same")
##     hpipi.DrawNormalized("err same")

##     #hmumu = glplot(tmumu,glname,mid)
##     hpipib = do_comparison(hpipi,hmumu)
##     hkpib = do_comparison(hkpi,hmumu)
##     hkkb= do_comparison(hkk,hmumu)
##     hx = TH1F("x","x",10,-0.1,0.1)
##     hy = TH1F("y","y",10,-3,3)

##     for i in range(4):
##         hx.Fill(hkpib.GetBinContent(i+1))
##         hy.Fill(hkpib.GetBinContent(i+1)/hkpib.GetBinError(i+1))
##         hx.Fill(hpipib.GetBinContent(i+1))
##         hy.Fill(hpipib.GetBinContent(i+1)/hpipib.GetBinError(i+1))
        
##         hx.Fill(hkkb.GetBinContent(i+1))
##         hy.Fill(hkkb.GetBinContent(i+1)/hkkb.GetBinError(i+1))
        

   
##     return c , hmumu, hkk, hpipi, hkpi, [hpipib,hkpib,hkkb, hx, hy]


def convert_topdf(h, ntot, sntot):
    #ntot independent
    hgl = h.Clone()
    bin0 = ntot - hgl.GetBinContent(2)- hgl.GetBinContent(3)- hgl.GetBinContent(4)

    hgl.SetBinContent(1,bin0)

    # normalize

    for i in range(4):
        hgl.SetBinContent(i+1, hgl.GetBinContent(i+1)/ntot)
        hgl.SetBinError(i+1, hgl.GetBinError(i+1)/ntot)
    s2 = 0
    for i in range(2,5):
        s2 +=  hgl.GetBinError(i)**2
        hgl.SetBinError(i, hgl.GetBinContent(i)*sqrt( (hgl.GetBinError(i)/hgl.GetBinContent(i))**2  +(sntot/ntot)**2))
        

    hgl.SetBinError(1, sqrt(s2 + ((1-hgl.GetBinContent(1))*(sntot/ntot) )**2)   )
    return hgl
    
    
    
Hlt1Mu = '(Hlt1DiMuonIPCL0SegDecision||Hlt1TrackMuonDecision||Hlt1SingleMuonIPCL0Decision||Hlt1DiMuonIPC2L0Decision||Hlt1DiMuonNoIPL0DiDecision||Hlt1DiMuon4BsMuMuDecision||Hlt1SingleMuon4BsMuMuDecision||Hlt1DiMuonIPCL0DiDecision||Hlt1DiMuonNoIPL0SegDecision||Hlt1DiMuonNoIP2L0Decision||Hlt1SingleMuonNoIPL0Decision)'


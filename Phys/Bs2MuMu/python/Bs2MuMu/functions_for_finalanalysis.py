from SomeUtils.alyabar import *
from ROOT import *
import random
from NTuple_names import *
from array import array as afC
glbins = [0, .25,.4,.5,.6,.7,.8,.9,1.]
massbins = [5312.96, 5324.96, 5336.96, 5342.96, 5354.96, 5390.96, 5402.96, 5408.96, 5420.96, 5432.96]
#[5224.6300000000001, 5236.6300000000001, 5248.6300000000001, 5254.6300000000001, 5266.6300000000001, 5302.6300000000001, 5314.6300000000001, 5320.6300000000001, 5332.6300000000001, 5344.6300000000001]


Binning = {bdtname: afC('f',glbins), massname: afC('f',massbins)}

#f = TFile("/afs/cern.ch/user/d/diegoms/vol5/ntuple_1fb_unblinded.root")
#t2 = f.Get("B2MuMuTuple/DecayTree")
#f3 = TFile("/tmp/wwwww","recreate")
#t = t2.CopyTree(fiducial)
def do_kpi_coef(b_kpi, sb_kpi,Ntis_hh, sNtis_hh):
    
    c_kpi = b_kpi/Ntis_hh
    sc_kpi = c_kpi*sqrt( (sb_kpi/b_kpi)**2 + (sNtis_hh/Ntis_hh)**2)

    return c_kpi, sc_kpi
    

def calculateNormalizationFactor( c_bu, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfs, sfdfs, channel = "Bs" ):
    
    cd, scd = ponderate([c_bu,c_kpi], [sc_bu, sc_kpi])
    if channel == "Bd":
        cs = c_phi/fdfs
        scs = sc_phi/fdfs
        scs = sqrt(  (scs/cs)**2 + (sfdfs/fdfs)**2)*cs
        return ponderate([cs,cd],[scs,scd])
    cd = cd*fdfs
    scd = scd*fdfs
    print cd
    scd = sqrt( (scd/cd)**2 + (sfdfs/fdfs)**2) * cd
    return ponderate([c_phi, cd], [sc_phi,scd])


def FitInBinning_2D(tree, bins, glname, massname = "Bmass", name = "xyz", flatgl = 0):
    """Stores  'tree' data in an 3D histogram, using the binning
    defined by 'bins'
    """
    print "Entries outside Binning will be ignored"
    vars = bins.keys()
    BN = len(vars)*[0]
   # for i in range(len(BN)):
    #    BN[i] = len(bins[vars[i]]) - 1
    out = TH2F(name , name ,len(bins[glname]) - 1,bins[glname], len(bins[massname]) -1 ,bins[massname])
    t = tree
    N = t.GetEntries()
    x0, xM = bins[glname][0], bins[glname][-1]
    #y0, yM = bins["y"][0], bins["y"][-1]
    z0, zM = bins[massname][0], bins[massname][-1]
    for k in range(N):
        t.GetEntry(k)
        if flatgl : x = random.random()
        else: x = getattr(t,glname)
        if x < x0 or x > xM: continue
        #y = getattr(t,"y")
        #if y < y0 or y > yM: continue
        z = getattr(t, massname)
        if z < z0 or z > zM: continue

        out.Fill(x,z)
    return out



def doNbins(N, s0, s1):
    st = (s1-s0)*1./N
    l = []
    for i in range(N+1):
        l.append(s0 + st*i)
    return l

def fluctuateSidebands(N,sN, sNn):
    out, outn ={},{}
   ## print N, sN ,sNn
    for key in N.keys():
        out[key] = N[key] + sN[key]
        outn[key]  = N[key] - sNn[key]
    return out, outn

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

def convert_tofractions(Ns, ntot):
    #if not Ns[0]: Ns[0] = ntot - sum(Ns)
    fs = len(Ns)*[0.]
    fs[0] =  1 - sum(Ns)*1./ntot
    for i in range(1,len(fs)):
        fs[i] = Ns[i]*1./ntot

    return fs


def make_mass_for_tables(hspdf, hspdfp=[], hspdfn= []):
    mass = hspdf.ProjectionY()
    massp, massn = [], []

    for h in hspdfp:
        massp.append(h.ProjectionY())
    for h in hspdfn:
        massn.append(h.ProjectionY())  
        
    def sum_err(j):
        err = 0
        for x in  massp:
            err += (mass.GetBinContent(j)-x.GetBinContent(j))**2
        for x in  massn:
            err += (mass.GetBinContent(j)-x.GetBinContent(j))**2
        return 0.5*sqrt(err)

    for i in range(mass.GetNbinsX()):
        mass.SetBinError(i+1,sum_err(i+1))
    return mass


def smear_mass(t,sf, binning, m1 = 105.658367,m2 = 105.658367, delta =0, hname = "name"):
    if delta>0: "positive shift ? are you sure?"
    h = TH1F(hname,hname,len(binning)-1,binning)
    for entry in t:
        p1 = vector(entry.mc_mu1_px,entry.mc_mu1_py,entry.mc_mu1_pz)
        p2 = vector(entry.mc_mu2_px,entry.mc_mu2_py,entry.mc_mu2_pz)
        mc_m = sqrt(IM2(p1,p2,m1,m2))
        h.Fill( mc_m + (entry.Bmass-mc_m)*sf + delta)
    return h

#f8 = TFile("~/public/Bsmm1fbLNF.root","recreate")
#h = FitInBinning_2D(t,Binning,bdtname,massname)

#h.Write()
#f8.Close()

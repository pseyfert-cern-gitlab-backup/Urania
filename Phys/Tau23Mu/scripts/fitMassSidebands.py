from ROOT import *
from SomeMassModels import sidebands as S
#f_cern = TFile("~/vol5/Bs2mumu341.root")#
#t_cern = f_cern.Get("Bs2MuMu")
#f=TFile("/afs/cern.ch/user/a/albrecht/tauNT/stp17_mud_noBDT_698pb_flat.root")
#f=TFile("/afs/cern.ch/project/lbcern/vol9/albrecht/stp17_mud_BDTv2_698pb_flat.root")
#f=TFile("/afs/cern.ch/project/lbcern/vol9/albrecht/stp17_mud_BDTv2_698pb_flat.root")

#f=TFile("~/vol9/tau23mu/stp17_mud_BDTv2p2_1024pb_flat.root_merged.root")
f=TFile("/afs/cern.ch/project/lbcern/vol2/albrecht/Bs2mm/JA_ntuples/tau23mu/stp17_mud_BDTv3e2_1024_maybe.root")
t_cern = f.Get('Tau23Mu')

#f2 = TFile("~/vol5/Bs2mumu341.root","recreate")
#t2 = t_cern.CopyTree("Blife_ps_r<7.36  && mu1ptot<1e06 && mu2ptot <1e06 && Bpt>500 && Bmass>(5366.3-1200) && mu1_track_CloneDist>5000 && mu2_track_CloneDist>5000")
#t2.Write()
#f2.Close()
#BREAK
#op = S.sidebandsFiter(t_cern, "Bmass", "Bpt>500 && Bmass>4900 && Bmass<6000 && BDTflatNEW<0.25 && BDTflatNEW<0.75 && Blife_ps_r<7.36  && mu1ptot<1e06 && mu2ptot <1e06 &&( Bmass<5000 || Bmass>(5358+60))", left = 5000, right = 5358+60, bkgf = S.exp_bkg,left2 = 5272-60, shorTime = False,Mmin = 4900,Mmax=6000)

clean="&&L0Dec&&Hlt1Dec&&Hlt2Dec&&cleaningcut"
def getTotBkg():

    '''
    for i in range(20):
        BDL>glmapmin[i]&&BDT<glmapmax[i]&&pid>pidmapmin[i]&&pid<pidmapmax[i+1]

    '''

 #2x5 binning, like RD talk nov 16
    dc_gl = {0:-1,1:0.00299067,2:0.127991,3:0.212991,4:0.29499,5:1.}
    dc_pid = {0:-0.2,1:0.30999,2:1}
    pid=" &&min(p0_singlePID,min(p1_singlePID,p2_singlePID))>-0.03"#-0.03"#PIDMVA>-0.02"
    #pid=pid=" &&PIDMVA>"+str(dc_pid[1])+" &&PIDMVA<"+str(dc_pid[2])+"&&GeoMVA>"+str(dc_gl[4])+"&&GeoMVA<"+str(dc_gl[5])
    vetos="&&mass_p0p1>250&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20"
    mass = "mass>1600 && mass<2100"
    gl=""#&& GeoMVA > 0.616"#0.44"
    
    #t2 = t_cern.CopyTree("1"+pid+vetos)#+clean)


    #op = S.sidebandsFiter(t_cern, "mass", mass+pid+vetos+clean, left = 1777-40, right = 1777+40, bkgf = S.exp_bkg,left2 = 1777-40, shorTime = False,Mmin = 1450,Mmax=2100)
    op = S.sidebandsFiter(t_cern, "mass", mass+pid+vetos+clean+gl, left = 1777-40, right = 1777+40, bkgf = S.exp_bkg,left2 = 1777-40, shorTime = False,Mmin = 1600,Mmax=1950)

    Nsb=t_cern.GetEntries("((mass>1600&&mass<1700)||(mass>1850&&mass<1950))"+pid+vetos+clean+gl)  
    idx=op.indx.getVal()
    nBin=bkg_in_bin(1777-30,1777+30,Nsb,idx,  a = 1600, b = 1700 , c = 1850, d = 1950)

    print "total number of bkg events: ",nBin

    return op

def getBkg(tc):
    '''
    dc_gl = {}
    dc_gl[0]=-1
    dc_gl[1]=0.0349907
    dc_gl[2]=0.173991
    dc_gl[3]=0.270991
    dc_gl[4]=1
    
    dc_pid = {}
    dc_pid[0]=-0.3
    dc_pid[1]=0.150991
    dc_pid[2]=0.30799
    dc_pid[3]=0.421989
    dc_pid[4]=1
    '''

    #2x5 binning, like RD talk nov 16
    #dc_gl = {0:-1,1:0.00299067,2:0.127991,3:0.212991,4:0.29499,5:1.}
    #dc_pid = {0:-0.2,1:0.30999,2:1}
    #(starting in the pid at -0.3 instead of -1 has an efficiency of 0.979642)

    dc_gl = {0:-1,1:0.16,2:0.47,3:0.64,4:1}
    dc_pid = {0:0.02,1:1}

    fout = TFile('test_bkg.root', "RECREATE")
    fout.cd()
    
    tc=TCanvas()
    tc.Divide(2,2)

    i=0
    j=0
    n=1
    for i in range(0,4):
        for j in range(0,1):
            tc.cd(n)
            print "process bin: ",n," , bin boundaries: gl",i," and pid ",j 
            f=fit(n,dc_gl[i],dc_gl[i+1],dc_pid[j],dc_pid[j+1])
            f.plot()
            n=n+1
    #tc.cd(2)
    #f=fit(16,0.4,1,0.27,1)
    #f.plot()
    

    tc.Write()
    #tc.Close()
    fout.Write()
    fout.Close()

    return tc

def fit(iBin=16,minGL=0.4,maxGL=1,minPID=0.27,maxPID=1):

    #noptPIDMVA = [-0.3,0.150991,0.30799,0.421989,1]
    #GeoMVA = [-1,0.0349907,0.173991,0.270991,1]
    #(starting in the pid at -0.3 instead of -1 has an efficiency of 0.979642)

    #pid=" &&PIDMVA>"+str(minPID)+" &&PIDMVA<"+str(maxPID)

    pid=" &&min(p0_singlePID,min(p1_singlePID,p2_singlePID))>"+str(minPID)+" &&min(p0_singlePID,min(p1_singlePID,p2_singlePID))<"+str(maxPID)
   
    
    #pid=" &&noptPIDMVA>"+str(minPID)+" &&noptPIDMVA<"+str(maxPID)
    gl="&&GeoMVA>"+str(minGL)+"&&GeoMVA<"+str(maxGL)

    print ""
    print ""
    print "gl: ",gl," and pid ",pid
    

    vetos="&&mass_p0p1>250&&abs(mass_p0p2-1020)>20&&abs(mass_p1p2-1020)>20"
    mass = "mass>1200 && mass<2200"

    t2 = t_cern.CopyTree("1"+gl+pid+vetos+clean)

    binMinMin=1600
    binMinMax=1700
    binMaxMin=1850
    binMaxMax=1950

    if iBin ==1:
        op = S.sidebandsFiter(t2, "mass", mass, left = 1777-40, right = 1777+40, bkgf = S.exp_bkg_pos,left2 = 1777-40, shorTime = False,Mmin = binMinMin,Mmax=binMaxMax)   

    if iBin > 1:    
        op = S.sidebandsFiter(t2, "mass", mass, left = 1777-40, right = 1777+40, bkgf = S.exp_bkg,left2 = 1777-40, shorTime = False,Mmin = binMinMin,Mmax=binMaxMax)


   
 
    Nsb=t2.GetEntries("(mass>"+str(binMinMin)+"&&mass<"+str(binMinMax)+")||(mass>"+str(binMaxMin)+"&&mass<"+str(binMaxMax)+")")  #n events in sidebands
    #print "Nsb", Nsb
    idx=op.indx.getVal()
    #print "idx", idx
#    nBin=bkg_in_bin(1777-10,1777,Nsb,idx,  a = 150, b = 1600 , c = 1900, d = 2200)
    

   
    print "#### bin",iBin
    print "bkgpdf.SetBinContent(",iBin,",1,",bkg_in_bin(1777-30,1777-20,Nsb,idx,  a = binMinMin, b = binMinMax , c = binMaxMin, d = binMaxMax),")"
    print "bkgpdf.SetBinContent(",iBin,",2,",bkg_in_bin(1777-20,1777-10,Nsb,idx,  a = binMinMin, b = binMinMax , c = binMaxMin, d = binMaxMax),")"
    print "bkgpdf.SetBinContent(",iBin,",3,",bkg_in_bin(1777-10,1777,Nsb,idx,  a = binMinMin, b = binMinMax , c = binMaxMin, d = binMaxMax),")"
    print "bkgpdf.SetBinContent(",iBin,",4,",bkg_in_bin(1777,1777+10,Nsb,idx,  a = binMinMin, b = binMinMax , c = binMaxMin, d = binMaxMax),")"
    print "bkgpdf.SetBinContent(",iBin,",5,",bkg_in_bin(1777+10,1777+20,Nsb,idx,  a = binMinMin, b = binMinMax , c = binMaxMin, d = binMaxMax),")"
    print "bkgpdf.SetBinContent(",iBin,",6,",bkg_in_bin(1777+20,1777+30,Nsb,idx,  a = binMinMin, b = binMinMax , c = binMaxMin, d = binMaxMax),")"
    print "#***************"
   
    return op


#op2 = S.sidebandsFiter(t, "Bmass", "Bpt>500 && Bmass>4000 && Bmass<8000 && BDTflat<0.25", left = 5000, right = 5358+60, bkgf = S.double_exp_bkg,left2 = 5272-60, shorTime = False)


def bkg_in_bin(x,y,Nsb,idx,  a = 4900, b = 5000 , c = 5418, d = 6000):#, b = Binning["Bmass"][0], c = Binning["Bmass"][1]):
    ## a = M_min
##     b = M_b
##     c = M_c
##     d = M_max
    kl = idx
    iDk = 1./(exp(kl*a) +exp(kl*c) - exp(kl*b) - exp(kl*d))
    Nxy = iDk*Nsb*(exp(kl*x)-exp(kl*y))
    return Nxy


##  **   23 **MINOS        1000
##  **********
##  FCN=-35734.5 FROM MINOS     STATUS=SUCCESSFUL     24 CALLS          73 TOTAL
##                      EDM=1.00532e-06    STRATEGY= 1      ERROR MATRIX ACCURATE 
##   EXT PARAMETER                  PARABOLIC         MINOS ERRORS        
##   NO.   NAME      VALUE            ERROR      NEGATIVE      POSITIVE   
##    1  bkgfraction   5.90228e+03   5.37970e+01  -5.36141e+01   5.39735e+01
##    2  indx        -7.59046e-04   2.27591e-05  -2.27609e-05   2.27548e-05
##                                ERR DEF= 0.5

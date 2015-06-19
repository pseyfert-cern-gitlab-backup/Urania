from ROOT import *
from math import *
from parameters import BlindingString, WeightsBdKpi, WeightsBd
import os

if not "BSJPSIKSTROOT" in os.environ.keys(): os.environ["BSJPSIKSTROOT"] = "../../"
gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/AccAngJpsiKpi_J1.cxx++")
gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/RooPhiBkg.cxx++")

################################################################################################
# Switches
################################################################################################
DWAVE = 1 # : 0 for the old script, WITHOUT D-WAVE / 1 for the new script, WITH D-WAVE
SET0DWAVE = 0 # when using the new script: 0 to INCLUDE THE D-WAVE / 1 to NOT INCLUDE THE D-WAVE 
BLIND = 1 # : 0 for a NOT BLINDED analysis / 1 for a BLINDED analysis
NO_CP = 0 # : 0 to INCLUDE CP ASYMMETRIES / 1 to NOT INCLUDE CP ASYMMETRIES
################################################################################################

if (not DWAVE): gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/TristanJpsiKpi_J1.cxx++")
else: gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/TristanJpsiKpi_J2.cxx++")

#gROOT.ProcessLine(".x ./AngJpsiKst_Swave_Asym.cxx++")

#gROOT.ProcessLine(".L $URANIAROOT/src/RooApollonios.cxx++")

mvar = "B0_MM"# "B_s0_LOKI_MASS_JpsiConstr"

#gROOT.ProcessLine(".x AngJpsiKst_Swave_Asym.cxx++")
#gSystem.Load("AngJPsiKst_cxx")

#Kcharge = RooRealVar("Kcharge","Kcharge",-1.)
SFIT = 2
#cKname, cLname, phName = "cK", "cL", "ph" ## kozyulin MCT tuple
cKname, cLname, phName = "helcosthetaK", "helcosthetaL", "B0_Phi" ## other

CPsi = RooRealVar(cKname,cKname,-1.,1.)
CTheta = RooRealVar(cLname,cLname,-1.,1.)
Phi = RooRealVar(phName,phName,-1.*pi,pi)

Mass = RooRealVar(mvar,mvar,5150, 5650.)

sWeights_Bd =  RooRealVar("sWeights_Bd","sWeights_Bd",-3.,3.)
sWeights_Bs =  RooRealVar("sWeights_Bs","sWeights_Bs",-3.,3.)

cor_sWeights_Bd =  RooRealVar("cor_sWeights_Bd","cor_sWeights_Bd",-3.,3.)
cor_sWeights_Bs =  RooRealVar("cor_sWeights_Bs","cor_sWeights_Bs",-3.,3.)

a1_cb = RooRealVar("a1_cb","a1_cb",2.8)#, 0.5,3.5)
a2_cb = RooRealVar("a2_cb","a2_cb",2.3)#, 0.5,3.5)
a2r_cb = RooRealVar("a2r_cb","a2_cb",-1.79)#, -6,-0.5)
ncb2 = RooRealVar("ncb2","ncb2",3.1)#)
delta_m = RooRealVar("delta_m", "delta_m", 5366.3-5279)
ncb = RooRealVar("ncb","ncb",1)
f05 = RooRealVar("f05","f05",0.5)#, 0., 1.)
fBs = RooRealVar("fBs","fBs", 1e-02,1e-03,.1)
Aprod_s = RooRealVar("A_prod_s","A_prod_s", -0.00132)#wk 
Aprod_d = RooRealVar("A_prod_d","A_prod_d", 0.00030)#wk 

A_D = RooRealVar("A_D","A_D", -0.01185)# ok  

if (DWAVE): NormWeights = WeightsBdKpi
else: NormWeights = WeightsBd

if not BLIND:
    print ""
    print ""
    print ""
    print "0o0   0o0    0o0   0o0   0o0  0o0  0o0  0o0"
    print " ALARM!, ALARM!, YOU ARE UNBLINDING!!!"
    print "0o0   0o0    0o0   0o0   0o0  0o0  0o0  0o0"
    print ""
    print ""
    print ""
s_a = 5.0
class AngularPDFMOD:
    def __init__(self, namephys = "Bd", namesample = "2011", Kcharge = 0. , acc_type = 1):

        ## Parameters of interest
        self.namephys = namephys
        self.namesample = namesample
        self.Kcharge =RooRealVar("Kcharge" + self.namephys + self.namesample,"Kcharge"+ self.namephys + self.namesample,Kcharge)
        self.acc_type = acc_type
    def OwnPhys(self, equalAsym = 0):
        namephys = self.namephys
        
        self.fL = RooRealVar("fL"+namephys,"fL"+namephys,0.507,0., 1.)
        self.fpa = RooRealVar("fpa"+namephys,"fpa"+namephys,0.172,0., 1.)
        self.As2 = RooRealVar("As2"+namephys,"As2"+namephys,0.05, 0., 1.)
        self.dpa = RooRealVar("dpa"+namephys,"dpa" + namephys, 0., -2*pi, 2*pi)
        self.CSP = RooRealVar("CSP"+namephys,"CSP" + namephys, 0., 1.)
	if (DWAVE):
	    self.fD = RooRealVar("fD"+namephys,"fD"+namephys,0.,0.,1.)
	    self.f2L = RooRealVar("f2L"+namephys,"f2L"+namephys,0.3,0.,1.)
            self.f2pa = RooRealVar("f2pa"+namephys,"f2pa"+namephys,0.3,0.,1.)
            self.d20 = RooRealVar("d20"+namephys,"d20" + namephys, 0., -2*pi, 2*pi)
	    self.d2pa = RooRealVar("d2pa"+namephys,"d2pa" + namephys, 0., -2*pi, 2*pi)
	    self.CSD = RooRealVar("CSD"+namephys,"CSD" + namephys, 0., 1.)
	    self.CPD = RooRealVar("CPD"+namephys,"CPD" + namephys, 0., 1.)
	    if (SET0DWAVE):
		getattr(self, "fD").setVal(0.)
		getattr(self, "fD").setConstant(1)
		getattr(self, "f2L").setConstant(1)
		getattr(self, "f2pa").setConstant(1)
		getattr(self, "d20").setConstant(1)
		getattr(self, "d2pa").setConstant(1)
        
        if self.Kcharge.getVal() >= 0:
            self.dpe = RooRealVar("dpe"+namephys,"dpe" + namephys, 0, -2*pi, 2*pi)
            if (DWAVE):
		self.d2pe = RooRealVar("d2pe"+namephys,"d2pe" + namephys, 0, -2*pi, 2*pi)
		if (SET0DWAVE): getattr(self, "d2pe").setConstant(1)

        else :
            self.dpe_ = RooRealVar("_dpe"+namephys,"_dpe" + namephys, 0,-2*pi,2*pi)
            self.dpe = RooFormulaVar("dpe"+namephys,"dpe" + namephys,"_dpe"+namephys + " + "+str(pi),RooArgList(self.dpe_))
	    if (DWAVE):
        	self.d2pe_ = RooRealVar("_d2pe"+namephys,"_d2pe" + namephys, 0,-2*pi,2*pi)
        	self.d2pe = RooFormulaVar("d2pe"+namephys,"d2pe" + namephys,"_d2pe"+namephys + " + "+str(pi),RooArgList(self.d2pe_))
		if (SET0DWAVE): getattr(self, "d2pe_").setConstant(1)
        self.ds = RooRealVar("ds"+namephys,"ds"+namephys,0 , -2*pi,2*pi)
        self.ACPS_ = RooRealVar("ACPS"+namephys,"ACPS"+namephys,0.,-0.5, 0.5)
        self.ACPL_ = RooRealVar("ACPL"+namephys,"ACPL"+namephys,0.,-0.5, 0.5)
        if (DWAVE):
	    self.ACP2L_ = RooRealVar("ACP2L"+namephys,"ACP2L"+namephys,0.,-0.5, 0.5)
	    if (SET0DWAVE): getattr(self, "ACP2L_").setConstant(1)
        if equalAsym:
            self.ACPpa_ = RooFormulaVar("ACPpa"+namephys,"ACPpa"+namephys, self.ACPL_.GetName(), RooArgList(self.ACPL_))
            self.ACPpe_ = RooFormulaVar("ACPpe"+namephys,"ACPpe"+namephys, self.ACPL_.GetName(), RooArgList(self.ACPL_))
	    if (DWAVE):
                self.ACP2pa_ = RooFormulaVar("ACP2pa"+namephys,"ACP2pa"+namephys, self.ACP2L_.GetName(), RooArgList(self.ACP2L_))
                self.ACP2pe_ = RooFormulaVar("ACP2pe"+namephys,"ACP2pe"+namephys, self.ACP2L_.GetName(), RooArgList(self.ACP2L_))
            
        else:
            self.ACPpa_ = RooRealVar("ACPpa"+namephys,"ACPpa"+namephys,0.,-0.5, 0.5)
            self.ACPpe_ = RooRealVar("ACPpe"+namephys,"ACPpe"+namephys,0.,-0.5, 0.5)
	    if (DWAVE):
                self.ACP2pa_ = RooRealVar("ACP2pa"+namephys,"ACP2pa"+namephys,0.,-0.5, 0.5)
                self.ACP2pe_ = RooRealVar("ACP2pe"+namephys,"ACP2pe"+namephys,0.,-0.5, 0.5)
		if (SET0DWAVE):
		    getattr(self, "ACP2pa_").setConstant(1)
		    getattr(self, "ACP2pe_").setConstant(1)

        if (BLIND and NO_CP == 0):
            self.ACPS = RooUnblindPrecision("ACPS"+namephys + "_UNB", "ACPS"+namephys + "_UNB", BlindingString + "S", 0,0.5, self.ACPS_)
            self.ACPL = RooUnblindPrecision("ACPL"+namephys + "_UNB", "ACPL"+namephys + "_UNB", BlindingString + "L", 0,0.5, self.ACPL_)
            if (DWAVE):
		if (not SET0DWAVE): self.ACP2L = RooUnblindPrecision("ACP2L"+namephys + "_UNB", "ACP2L"+namephys + "_UNB", BlindingString + "2L", 0,0.5, self.ACP2L_)
		else: self.ACP2L = self.ACP2L_
            if not equalAsym:
                self.ACPpa = RooUnblindPrecision("ACPpa"+namephys + "_UNB", "ACPpa"+namephys + "_UNB", BlindingString + "pa", 0,0.5,self.ACPpa_)
                self.ACPpe = RooUnblindPrecision("ACPpe"+namephys + "_UNB", "ACPpe"+namephys + "_UNB", BlindingString +"pe",  0,0.5, self.ACPpe_)
                if (DWAVE):
		    if (not SET0DWAVE):
		        self.ACP2pa = RooUnblindPrecision("ACP2pa"+namephys + "_UNB", "ACP2pa"+namephys + "_UNB", BlindingString + "2pa", 0,0.5, self.ACP2pa_)
		        self.ACP2pe = RooUnblindPrecision("ACP2pe"+namephys + "_UNB", "ACP2pe"+namephys + "_UNB", BlindingString + "2pe", 0,0.5, self.ACP2pe_)
		    else:
			self.ACP2pa = self.ACP2pa_
			self.ACP2pe = self.ACP2pe_
	    else:
		self.ACPpa = self.ACPL
		self.ACPpe = self.ACPL
		if (DWAVE):
		    self.ACP2pa = self.ACP2L
		    self.ACP2pe = self.ACP2L

        else:
	    self.ACPS = self.ACPS_
	    self.ACPL = self.ACPL_
            self.ACPpa = self.ACPpa_
            self.ACPpe = self.ACPpe_
	    if (DWAVE):
		self.ACP2L = self.ACP2L_
        	self.ACP2pa = self.ACP2pa_
        	self.ACP2pe = self.ACP2pe_

	if (NO_CP == 1):
	    getattr(self, "ACPS_").setVal(0.)
	    getattr(self, "ACPS_").setConstant(1)
	    getattr(self, "ACPL_").setVal(0.)
	    getattr(self, "ACPL_").setConstant(1)
	    if (DWAVE):
		getattr(self, "ACP2L_").setVal(0.)
		getattr(self, "ACP2L_").setConstant(1)
	    if not equalAsym:
		getattr(self, "ACPpa_").setVal(0.)
		getattr(self, "ACPpa_").setConstant(1)
		getattr(self, "ACPpe_").setVal(0.)
		getattr(self, "ACPpe_").setConstant(1)
		if (DWAVE):
		    getattr(self, "ACP2pa_").setVal(0.)
		    getattr(self, "ACP2pa_").setConstant(1)
		    getattr(self, "ACP2pe_").setVal(0.)
		    getattr(self, "ACP2pe_").setConstant(1)

        
	# Auxiliar CP asymmetries
	self.fACPp = RooFormulaVar("fACPp" + namephys, "fACPp" + namephys, "fL" + namephys + "*" + self.ACPL.GetName() + "+fpa" + namephys + "*" + self.ACPpa.GetName() + "+(1.-fL" + namephys + "-fpa" + namephys + ")*" + self.ACPpe.GetName(), RooArgList(self.fL,self.ACPL,self.fpa,self.ACPpa,self.ACPpe))
	if (DWAVE):
	    self.fACPd = RooFormulaVar("fACPd" + namephys, "fACPd" + namephys, "f2L" + namephys + "*" + self.ACP2L.GetName() + "+f2pa" + namephys + "*" + self.ACP2pa.GetName() + "+(1.-f2L" + namephys + "-f2pa" + namephys + ")*" + self.ACP2pe.GetName(), RooArgList(self.f2L,self.ACP2L,self.f2pa,self.ACP2pa,self.ACP2pe))
	    self.ACPD = RooFormulaVar("ACPD" + namephys, "ACPD" + namephys, "(1.-fD" + namephys + ")*(fACPd" + namephys + "-fACPp" + namephys + ")/(1.+(1.-fD" + namephys + ")*fACPp" + namephys + "+fD" + namephys + "*fACPd" + namephys + ")", RooArgList(self.fD,self.fACPd,self.fACPp))        
	    self.ACPN = RooFormulaVar("ACPN" + namephys, "ACPN" + namephys, "As2" + namephys + "*" + self.ACPS.GetName() + "+(1.-As2" + namephys + ")*(1.-fD" + namephys + ")*fACPp" + namephys + "+(1.-As2" + namephys + ")*fD" + namephys + "*fACPd" + namephys, RooArgList(self.As2,self.ACPS,self.fD,self.fACPp,self.fACPd))
        else: self.ACPN = RooFormulaVar("ACPN" + namephys, "ACPN" + namephys, "As2" + namephys + "*" + self.ACPS.GetName() + "+(1.-As2" + namephys + ")*fACPp" + namephys, RooArgList(self.As2,self.ACPS,self.fACPp))

	# CP violating normalization factors entering the polarization fractions
	# (equal to 1 if all CP asymmetries are 0)
	self.normfs = RooFormulaVar("normfs" + namephys, "normfs" + namephys, "1./(1.+ACPN" + namephys + ")", RooArgList(self.ACPN))
	self.normfsbar = RooFormulaVar("normfsbar" + namephys, "normfsbar" + namephys, "1./(1.-ACPN" + namephys + ")", RooArgList(self.ACPN))
	if (DWAVE):
	    self.normfp = RooFormulaVar("normfp" + namephys, "normfp" + namephys, "(1.-As2" + namephys + ")*(1.-fD" + namephys + ")/((1.+" + self.ACPN.GetName() + "-As2" + namephys + "*(1.+" + self.ACPS.GetName() + "))*(1.-fD" + namephys + "*(1.+" + self.ACPD.GetName() + ")))", RooArgList(self.As2,self.fD,self.ACPN,self.ACPS,self.ACPD))
	    self.normfpbar = RooFormulaVar("normfpbar" + namephys, "normfpbar" + namephys, "(1.-As2" + namephys + ")*(1.-fD" + namephys + ")/((1.-" + self.ACPN.GetName() + "-As2" + namephys + "*(1.-" + self.ACPS.GetName() + "))*(1.-fD" + namephys + "*(1.-" + self.ACPD.GetName() + ")))", RooArgList(self.As2,self.fD,self.ACPN,self.ACPS,self.ACPD))
	    self.normfd = RooFormulaVar("normfd" + namephys, "normfd" + namephys, "(1.-As2" + namephys + ")/((1.+" + self.ACPN.GetName() + "-As2" + namephys + "*(1.+" + self.ACPS.GetName() + "))*(1.+" + self.ACPD.GetName() + "))", RooArgList(self.As2,self.ACPN,self.ACPS,self.ACPD))
	    self.normfdbar = RooFormulaVar("normfdbar" + namephys, "normfdbar" + namephys, "(1.-As2" + namephys + ")/((1.-" + self.ACPN.GetName() + "-As2" + namephys + "*(1.-" + self.ACPS.GetName() + "))*(1.-" + self.ACPD.GetName() + "))", RooArgList(self.As2,self.ACPN,self.ACPS,self.ACPD))
	else:
	    self.normfp = RooFormulaVar("normfp" + namephys, "normfp" + namephys, "(1.-As2" + namephys + ")/(1.+" + self.ACPN.GetName() + "-As2" + namephys + "*(1.+" + self.ACPS.GetName() + "))", RooArgList(self.As2,self.ACPN,self.ACPS))
	    self.normfpbar = RooFormulaVar("normfpbar" + namephys, "normfpbar" + namephys, "(1.-As2" + namephys + ")/(1.-" + self.ACPN.GetName() + "-As2" + namephys + "*(1.-" + self.ACPS.GetName() + "))", RooArgList(self.As2,self.ACPN,self.ACPS))

        self.CreateAmplitudes()

    def CopyStrongPhases(self, other):
        self.ds = other.ds
        self.dpa = other.dpa
	if (DWAVE):
            self.d20 = other.d20
	    self.d2pa = other.d2pa
	    self.d2pahat = other.d2pahat
        
        if self.Kcharge.getVal() != other.Kcharge.getVal():
            namephys = self.namephys
            self.dpe = RooFormulaVar("_dpe"+namephys,"_dpe" + namephys,"dpe"+namephys + " + "+str(pi),RooArgList(other.dpe))
	    if (DWAVE):
		self.d2pe = RooFormulaVar("_d2pe"+namephys,"_d2pe" + namephys,"d2pe"+namephys + " + "+str(pi),RooArgList(other.d2pe))
		self.d2pehat = RooFormulaVar("d2pehat"+namephys,"d2pehat" + namephys, "d20"+namephys +"+d2pe"+namephys, RooArgList(other.d20,self.d2pe))

        else:
	    self.dpe = other.dpe
	    if (DWAVE):
		self.d2pe = other.d2pe
		self.d2pehat = other.d2pehat
        
    def CopyFreeParams(self, other):
        self.fL = other.fL
        self.fpa = other.fpa
        self.As2 = other.As2
        self.ACPS = other.ACPS
        self.ACPL = other.ACPL
        self.ACPpe = other.ACPpe
        self.ACPpa = other.ACPpa
	self.ACPN = other.ACPN
	self.normfs = other.normfs
	self.normfsbar = other.normfsbar
	self.normfp = other.normfp
	self.normfpbar = other.normfpbar
        self.ACPS_ = other.ACPS_
        self.ACPL_ = other.ACPL_
        self.ACPpe_ = other.ACPpe_
        self.ACPpa_ = other.ACPpa_
        self.CSP = other.CSP
	if (DWAVE):
            self.f2L = other.f2L
            self.f2pa = other.f2pa
            self.fD = other.fD
	    self.ACPD = other.ACPD
	    self.normfd = other.normfd
	    self.normfdbar = other.normfdbar
            self.ACP2L = other.ACP2L
            self.ACP2pe = other.ACP2pe
            self.ACP2pa = other.ACP2pa
            self.ACP2L_ = other.ACP2L_
            self.ACP2pe_ = other.ACP2pe_
            self.ACP2pa_ = other.ACP2pa_
	    self.CSD = other.CSD
            self.CPD = other.CPD
        self.CopyStrongPhases(other)
        self.CreateAmplitudes()

    def CopyPhys(self, other):
        self.fL_ = other.fL_
        self.fpa_ = other.fpa_
        self.As2_ = other.As2_
        self.CSP = other.CSP
	if (DWAVE):
            self.f2L_ = other.f2L_
            self.f2pa_ = other.f2pa_
            self.fD_ = other.fD_
            self.CSD = other.CSD
            self.CPD = other.CPD
        self.CopyStrongPhases(other)
        
        return 1

    def CreateAmplitudes(self):
        namephys = self.namephys
        name = self.namephys + self.namesample
        
	if (DWAVE):
	    self.d2pahat = RooFormulaVar("d2pahat"+namephys,"d2pahat" + namephys, "d20"+namephys +"+d2pa"+namephys, RooArgList(self.d20,self.d2pa))
	    self.d2pehat = RooFormulaVar("d2pehat"+namephys,"d2pehat" + namephys, "d20"+namephys +"+d2pe"+namephys, RooArgList(self.d20,self.d2pe))

        if self.Kcharge.getVal() == 0:
            self.As2_ = RooFormulaVar("As2"+name,"As2" + name, " As2"+namephys, RooArgList(self.As2))
            self.fL_ = RooFormulaVar("fL"+name,"fL" + name, " fL"+namephys, RooArgList(self.fL))
            self.fpa_ = RooFormulaVar("fpa"+name,"fpa" + name, "fpa"+namephys,  RooArgList(self.fpa))
	    if (DWAVE):
                self.fD_ = RooFormulaVar("fD"+name,"fD" + name, " fD"+namephys, RooArgList(self.fD))
                self.f2L_ = RooFormulaVar("f2L"+name,"f2L" + name, " f2L"+namephys, RooArgList(self.f2L))
                self.f2pa_ = RooFormulaVar("f2pa"+name,"f2pa" + name, "f2pa"+namephys,  RooArgList(self.f2pa))

        if self.Kcharge.getVal()> 0:
            self.As2_ = RooFormulaVar("As2" + name,"As2" + name, "As2" + namephys + "*(1.+" + self.ACPS.GetName() + ")*normfs" + namephys, RooArgList(self.As2,self.ACPS,self.normfs))
            self.fL_ = RooFormulaVar("fL" + name,"fL" + name, "fL" + namephys + "*(1.+" + self.ACPL.GetName() + ")*normfp" + namephys, RooArgList(self.fL,self.ACPL,self.normfp))
            self.fpa_ = RooFormulaVar("fpa" + name,"fpa" + name, "fpa" + namephys + "*(1.+" + self.ACPpa.GetName() + ")*normfp" + namephys, RooArgList(self.fpa,self.ACPpa,self.normfp))
	    if (DWAVE):
                self.fD_ = RooFormulaVar("fD" + name,"fD" + name, "fD" + namephys + "*(1.+" + self.ACPD.GetName() + ")", RooArgList(self.fD,self.ACPD))
                self.f2L_ = RooFormulaVar("f2L" + name,"f2L" + name, "f2L" + namephys + "*(1.+" + self.ACP2L.GetName() + ")*normfd" + namephys, RooArgList(self.f2L,self.ACP2L,self.normfd))
                self.f2pa_ = RooFormulaVar("f2pa" + name,"f2pa" + name, "f2pa" + namephys + "*(1.+" + self.ACP2pa.GetName() + ")*normfd" + namephys, RooArgList(self.f2pa,self.ACP2pa,self.normfd))
            
        if self.Kcharge.getVal()< 0:
            self.As2_ = RooFormulaVar("As2" + name,"As2" + name, "As2" + namephys + "*(1.-" + self.ACPS.GetName() + ")*normfsbar" + namephys, RooArgList(self.As2,self.ACPS,self.normfsbar))
            self.fL_ = RooFormulaVar("fL" + name,"fL" + name, "fL" + namephys + "*(1.-" + self.ACPL.GetName() + ")*normfpbar" + namephys, RooArgList(self.fL,self.ACPL,self.normfpbar))
            self.fpa_ = RooFormulaVar("fpa" + name,"fpa" + name, "fpa" + namephys + "*(1.-" + self.ACPpa.GetName() + ")*normfpbar" + namephys, RooArgList(self.fpa,self.ACPpa,self.normfpbar))
	    if (DWAVE):
                self.fD_ = RooFormulaVar("fD" + name,"fD" + name, "fD" + namephys + "*(1.-" + self.ACPD.GetName() + ")", RooArgList(self.fD,self.ACPD))
                self.f2L_ = RooFormulaVar("f2L" + name,"f2L" + name, "f2L" + namephys + "*(1.-" + self.ACP2L.GetName() + ")*normfdbar" + namephys, RooArgList(self.f2L,self.ACP2L,self.normfdbar))
                self.f2pa_ = RooFormulaVar("f2pa" + name,"f2pa" + name, "f2pa" + namephys + "*(1.-" + self.ACP2pa.GetName() + ")*normfdbar" + namephys, RooArgList(self.f2pa,self.ACP2pa,self.normfdbar))

    def OwnAcc(self):
        name = self.namephys + self.namesample
        if self.acc_type == 1:
            self.c1_psi = RooRealVar("c1_psi" + name,"c1_psi" + name,-0.522,-0.522-s_a*0.014,-0.522+s_a*.014)
            self.c2_psi = RooRealVar("c2_psi" + name,"c2_psi" + name,-0.723,-0.723-s_a*0.022,-0.723+s_a*0.022)
            self.c3_psi = RooRealVar("c3_psi" + name,"c3_psi" + name,-0.190,-0.190-3*s_a,0.190+3*s_a)
            self.c4_psi = RooRealVar("c4_psi" + name,"c4_psi" + name,0.208,0.208-s_a*0.023,0.208+s_a*0.023) 
            self.y_acc = RooRealVar("y" + name,"y" + name,0.)#,0.,s_a*1.6e-04)
            self.c5_psi = RooFormulaVar("c5_psi" + name,"c5_psi" + name,"y" + name + " + (-1.-c1_psi"+ name + "-c2_psi" + name + "-c3_psi" + name + "-c4_psi" + name + ")",RooArgList(self.y_acc,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
            self.c2_theta = RooRealVar("c2_theta" + name,"c2_theta" + name,0,-0.5,0.5)
        else:
            if self.Kcharge.getVal() > 0: wdict = NormWeights["2012p_896_931"]
            else: wdict = NormWeights["2012n_896_931"] 
            
	    if (DWAVE):
		self.w_paS = RooRealVar("w_paS" + name, "w_paS", wdict["paS"])
		self.w_0S = RooRealVar("w_0S" + name, "w_0S", wdict["0S"])
		self.w_2pa0 = RooRealVar("w_2pa0" + name, "w_2pa0", wdict["2pa0"])
		self.w_peS = RooRealVar("w_peS" + name, "w_peS", wdict["peS"])
		self.w_2pe20 = RooRealVar("w_2pe20" + name, "w_2pe20", wdict["2pe20"])
		self.w_2peS = RooRealVar("w_2peS" + name, "w_2peS", wdict["2peS"])
		self.w_2pa2pa = RooRealVar("w_2pa2pa" + name, "w_2pa2pa", wdict["2pa2pa"])
		self.w_20S = RooRealVar("w_20S" + name, "w_20S", wdict["20S"])
		self.w_pepe = RooRealVar("w_pepe" + name, "w_pepe", wdict["pepe"])
		self.w_2pepa = RooRealVar("w_2pepa" + name, "w_2pepa", wdict["2pepa"])
		self.w_2pepe = RooRealVar("w_2pepe" + name, "w_2pepe", wdict["2pepe"])
		self.w_200 = RooRealVar("w_200" + name, "w_200", wdict["200"])
		self.w_0pa = RooRealVar("w_0pa" + name, "w_0pa", wdict["0pa"])
		self.w_0pe = RooRealVar("w_0pe" + name, "w_0pe", wdict["0pe"])
		self.w_pape = RooRealVar("w_pape" + name, "w_pape", wdict["pape"])
		self.w_papa = RooRealVar("w_papa" + name, "w_papa", wdict["papa"])
		self.w_00 = RooRealVar("w_00" + name, "w_00", wdict["00"])
		self.w_2pa20 = RooRealVar("w_2pa20" + name, "w_2pa20", wdict["2pa20"])
		self.w_2pe2pa = RooRealVar("w_2pe2pa" + name, "w_2pe2pa", wdict["2pe2pa"])
		self.w_2pe2pe = RooRealVar("w_2pe2pe" + name, "w_2pe2pe", wdict["2pe2pe"])
		self.w_20pa = RooRealVar("w_20pa" + name, "w_20pa", wdict["20pa"])
		self.w_20pe = RooRealVar("w_20pe" + name, "w_20pe", wdict["20pe"])
		self.w_SS = RooRealVar("w_SS" + name, "w_SS", wdict["SS"])
		self.w_2paS = RooRealVar("w_2paS" + name, "w_2paS", wdict["2paS"])
		self.w_2pe0 = RooRealVar("w_2pe0" + name, "w_2pe0", wdict["2pe0"])
		self.w_2020 = RooRealVar("w_2020" + name, "w_2020", wdict["2020"])
		self.w_2pape = RooRealVar("w_2pape" + name, "w_2pape", wdict["2pape"])
		self.w_2papa = RooRealVar("w_2papa" + name, "w_2papa", wdict["2papa"])
		self.Tristan_weights = (self.w_2paS, self.w_20S, self.w_2020, self.w_2pe0, self.w_paS, self.w_0S, self.w_peS, self.w_pape, self.w_2pe2pe, self.w_0pe, self.w_SS, self.w_2pape, self.w_2peS, self.w_0pa, self.w_2papa, self.w_2pe20, self.w_00, self.w_2pe2pa, self.w_papa, self.w_2pa0, self.w_20pe, self.w_2pa20, self.w_200, self.w_2pepa, self.w_20pa, self.w_2pepe, self.w_2pa2pa, self.w_pepe)

	    else:
                self.w_pe2 = RooRealVar("w_pepe" + name, "w_pepe", wdict["pe2"])
                self.w_S2 = RooRealVar("w_SS" + name, "w_SS", wdict["SS"])
                self.w_0pe = RooRealVar("w_0pe" + name, "w_0pe",wdict["0pe"])
                self.w_Spe = RooRealVar("w_Spe" + name, "w_Spe", wdict["Spe"])
                self.w_pape = RooRealVar("w_pape" + name, "w_pape",wdict["pape"])
                self.w_pa2 = RooRealVar("w_papa" + name, "w_papa", wdict["pa2"])
                self.w_Spa  = RooRealVar("w_Spa" + name, "w_Spa", wdict["Spa"])
                self.w_0pa  = RooRealVar("w_0pa" + name, "w_0pa", wdict["0pa"])
                self.w_S0  = RooRealVar("w_S0" + name, "w_S0", wdict["S0"])
                self.w_00 = RooRealVar("w_00" + name, "w_00", wdict["00"])
                self.Tristan_weights = (self.w_pe2, self.w_S2, self.w_0pe, self.w_Spe, self.w_pape, self.w_pa2, self.w_Spa, self.w_0pa, self.w_S0, self.w_00)

    def GetNormWeightString(self):
        out = ""
        for thing in self.Tristan_weights: out+= ","+thing.GetName()
        return out

    def FlatAcc(self):
        if self.acc_type == 1:
            name = self.namephys + self.namesample
            self.c1_psi = RooRealVar("c1_psi" + name,"c1_psi" + name,0)#-0.522,-0.522-s_a*0.014,-0.522+s_a*.014)
            self.c2_psi = RooRealVar("c2_psi" + name,"c2_psi" + name,0)#-0.723,-0.723-s_a*0.022,-0.723+s_a*0.022)
            self.c3_psi = RooRealVar("c3_psi" + name,"c3_psi" + name,0)#-0.190,-0.190-3*s_a,0.190+3*s_a)
            self.c4_psi = RooRealVar("c4_psi" + name,"c4_psi" + name,0)#0.208,0.208-s_a*0.023,0.208+s_a*0.023) 
            self.y_acc = RooRealVar("y" + name,"y" + name,1.)#,0.,s_a*1.6e-04)
        
            self.c2_theta = RooRealVar("c2_theta" + name,"c2_theta" + name,0)#-0.1783,-0.1783-s_a*0.0075,-0.1783+s_a*0.0075)
        else:
            for w in self.Tristan_weights:
                wname = w.GetName()
                if "SS" in wname or "00" in wname or "papa" in wname or "pepe" in wname or "2020" in wname or "2pa2pa" in wname or "2pe2pe" in wname: w.setVal(1.)#16.*pi/9)
                else: w.setVal(0.) 
                w.setConstant(kTRUE)
                print w.GetName(), w.getVal()
        
    def CopyAcc(self, other):
        if self.acc_type == 1:
            self.c1_psi = other.c1_psi
            self.c2_psi = other.c2_psi
            self.c3_psi = other.c3_psi
            self.c4_psi = other.c4_psi
            self.c5_psi = other.c5_psi
            self.y_acc = other.y_acc
            #self.c1_theta = other.c1_theta
            self.c2_theta = other.c2_theta
        else: self.Tristan_weights = other.Tristan_weights
    def modParamAsym(self, name, v0, v1,v2, cte):
        _min = v0 - v1
        _max = v0 + v2
        if _max <= getattr(self, name).getMin():
            #print "A"
            getattr(self, name).setMin(v0-v1)
            getattr(self, name).setMax(v0+v2)
            getattr(self, name).setVal(v0)
        else:
            #print "B"
            getattr(self, name).setMax(v0+v2)
            getattr(self, name).setMin(v0-v1)
            getattr(self, name).setVal(v0)
        getattr(self, name).setConstant(cte)
        return 1
    
    def modParam(self, name, v0, v1, cte = 0):
        return self.modParamAsym(name, v0, v1, v1, cte)
    
    def make(self):
        name = self.namephys + self.namesample

        if self.acc_type == 1: self.model = AccAngJpsiKpi_J1("angular " + name,"angular " + name, CPsi, CTheta, Phi, self.As2, self.fL_, self.fpa_, \
                                          self.dpa, self.dpe, self.ds, self.CSP, self.c1_psi, self.c2_psi, self.c3_psi, self.c4_psi, self.y_acc, self.c2_theta)#, self.c1_phi, self.c2_phi, self.c3_phi, self.c4_phi, self.c5_phi, self.c6_phi)
        else:
	    if (DWAVE): self.model = TristanJpsiKpi_J2("angular " + name,"angular " + name, CPsi, CTheta, Phi, self.As2_, self.fD_, self.fL_, self.fpa_, self.f2L_, self.f2pa_, \
                                          self.d2pehat, self.d2pahat, self.d20, self.dpa, self.dpe, self.ds, self.CPD, self.CSD, self.CSP, *self.Tristan_weights)


	    else: self.model = TristanJpsiKpi_J1("angular " + name,"angular " + name, CPsi, CTheta, Phi, self.As2_, self.fL_, self.fpa_, \
                                          self.dpa, self.dpe, self.ds, self.CSP, *self.Tristan_weights)

# Background
class FullBackground:
    def __init__(self, name = "Bkg"):
        self.name  = name
        
        self.c1_phi_bkg = RooRealVar("c1_phi"+name,"c1_phi"+name,-4.38046e-01, -1,1)
        self.c2_phi_bkg = RooRealVar("c2_phi"+name,"c2_phi"+name,1.24342e-01,0.,.3)
        self.c3_phi_bkg = RooRealVar("c3_phi"+name,"c3_phi"+name,4.63368e-02,-0.1,.1)
        self.phibkg = RooPhiBkg("phibkg" + name,"phibkg" + name,Phi,self.c1_phi_bkg,self.c2_phi_bkg,self.c3_phi_bkg)
        
        self.kbkg = RooRealVar("k"+name,"k"+name,-1e-03,-1e-02,0)
        self.massbkg = RooExponential("Mass" + name, "Mass" + name, Mass, self.kbkg)

    def OwnTheta(self):
        name = self.name
        self.c1_psi = RooRealVar("c1_psi" + name,"c1_psi" + name,-5.20101e-01)#-0.522,-0.522-s_a*0.014,-0.522+s_a*.014)
        self.c2_psi = RooRealVar("c2_psi" + name,"c2_psi" + name,-7.33299e-01)#,-0.723-s_a*0.022,-0.723+s_a*0.022)
        self.c3_psi = RooRealVar("c3_psi" + name,"c3_psi" + name,-2.90606e-01)#-0.190,-0.190-3*s_a,0.190+3*s_a)
        self.c4_psi = RooRealVar("c4_psi" + name,"c4_psi" + name,2.69475e-01 )#0.208,0.208-s_a*0.023,0.208+s_a*0.023) 
        self.y_acc = RooRealVar("y" + name,"y" + name,0.)#,0.,s_a*1.6e-04)
        self.c5_psi = RooFormulaVar("c5_psi" + name,"c5_psi" + name,"y" + name + " + (-1.-c1_psi"+ name + "-c2_psi" + name + "-c3_psi" + name + "-c4_psi" + name + ")",RooArgList(self.y_acc,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
        self.c1_theta = RooRealVar("c1_theta" + name,"c1_theta" + name,0)
        self.c2_theta = RooRealVar("c2_theta" + name,"c2_theta" + name,2.76201e-01)
        self.psibkg = RooPolynomial("psi" + name ,"psi" + name,CPsi,RooArgList(self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi))
        self.thetabkg = RooPolynomial("theta" + name,"theta" + name,CTheta,RooArgList(self.c1_theta,self.c2_theta))


    def thetaFromAcc(self, other):
        name = self.name
        self.c1_psi = other.c1_psi
        self.c2_psi = other.c2_psi
        self.c3_psi = other.c3_psi
        self.c4_psi = other.c4_psi
        self.c5_psi = other.c5_psi#RooFormulaVar("c5_psi" + name,"c5_psi" + name,"y" + name + " + (-1.-c1_psi"+ name + "-c2_psi" + name + "-c3_psi" + name + "-c4_psi" + name + ")",RooArgList(other.y_acc,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
        self.c1_theta = RooRealVar("c1_theta" + name,"c1_theta" + name,0)
        self.c2_theta = other.c2_theta
        self.psibkg = RooPolynomial("psi" + name ,"psi" + name,CPsi,RooArgList(self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi))
        self.thetabkg = RooPolynomial("theta" + name,"theta" + name,CTheta,RooArgList(self.c1_theta,self.c2_theta))

    def modParamAsym(self, name, v0, v1,v2):
        _min = v0 - v1
        _max = v0 + v2
        if _max <= getattr(self, name).getMin():
            #print "A"
            getattr(self, name).setMin(v0-v1)
            getattr(self, name).setMax(v0+v2)
            getattr(self, name).setVal(v0)
        else:
            #print "B"
            getattr(self, name).setMax(v0+v2)
            getattr(self, name).setMin(v0-v1)
            getattr(self, name).setVal(v0)
        return 1
    def modParam(self, name, v0, v1):
        return self.modParamAsym(name, v0, v1, v1)
    def make(self):
        name = self.name
        self.model = RooProdPdf("model"+name,"model"+name,RooArgList(self.psibkg,self.thetabkg,self.phibkg,self.massbkg))
       
class SignalMass:
    def __init__(self, samplename):

        self.mean1 = RooRealVar("mean1"+samplename,"mean1"+samplename,5279, 5276,5300)
        self.sigma1 = RooRealVar("sigma1"+samplename,"sigma1"+samplename, 6.,10.)

        self.delta_s = RooRealVar("delta_s"+samplename, "delta_s"+samplename, 2.,1.,15.)

        self.sigma2 = RooFormulaVar("sigma2"+samplename,"sigma2"+samplename, "sigma1"+samplename+" + delta_s"+samplename ,RooArgList(self.sigma1,self.delta_s) )
        self.mean2 = RooFormulaVar("mean2"+samplename,"mean2"+samplename, "mean1"+samplename+" + delta_m" ,RooArgList(self.mean1,delta_m) )
        self.sigb11  = RooCBShape("SigmodelB11"+samplename,"SigmodelB11"+samplename, Mass, self.mean1, self.sigma1, a1_cb, ncb)

        self.sigb12l  = RooCBShape("SigmodelB12l"+samplename,"SigmodelB12l"+samplename, Mass, self.mean1, self.sigma2, a2_cb, ncb)
        self.sigb12r  = RooCBShape("SigmodelB12r"+samplename,"SigmodelB12r"+samplename, Mass, self.mean1, self.sigma2, a2r_cb, ncb2)
        self.sigb12  = RooAddPdf("SigmodelB12"+samplename,"SigmodelB12"+samplename, self.sigb12l, self.sigb12r, f05)
        self.sigb21  = RooCBShape("SigmodelB21"+samplename,"SigmodelB21"+samplename, Mass, self.mean2, self.sigma1, a1_cb, ncb)
        self.sigb22l  = RooCBShape("SigmodelB22l"+samplename,"SigmodelB22l"+samplename, Mass, self.mean2, self.sigma2, a2_cb, ncb)
        self.sigb22r  = RooCBShape("SigmodelB22r"+samplename,"SigmodelB22r"+samplename, Mass, self.mean2, self.sigma2, a2r_cb, ncb2)
        self.sigb22  = RooAddPdf("SigmodelB22"+samplename,"SigmodelB22"+samplename, self.sigb22l, self.sigb22r, f05)

        self.fsmres = RooRealVar("f small res"+samplename,"f small res"+samplename,0.8, 0., 1.)
        self.sigBd  = RooAddPdf("SigmodelB1"+samplename,"SigmodelB1"+samplename, self.sigb11, self.sigb12, self.fsmres)
        self.sigBs  = RooAddPdf("SigmodelB2"+samplename,"SigmodelB2"+samplename, self.sigb21, self.sigb22, self.fsmres)


# class SignalMass:
#     def __init__(self, samplename):

#         self.meanBd = RooRealVar("meanBd"+samplename,"meanBd"+samplename,5279, 5276,5300)
#         self.sigma1 = RooRealVar("sigma1"+samplename,"sigma1"+samplename, 5.,20.)
#         self.d_sigma = RooRealVar("d_sigma"+samplename,"d_sigma"+samplename, 24.6)
#         self.sigma2 = RooFormulaVar("sigma2"+samplename,"sigma2"+samplename, "sigma1"+samplename + " + d_sigma"+samplename, RooArgList(self.sigma1,self.d_sigma))
    
#         self.coef = RooRealVar("coef"+samplename, "coef"+samplename, 2.,1.,15.)
#         self.meanBs = RooFormulaVar("meanBs"+samplename,"meanBs"+samplename, "meanBd"+samplename+" + delta_m" ,RooArgList(self.meanBd,delta_m) )
#         self.f1 = RooRealVar("f_Apo_1"+samplename,"f_Apo_1"+samplename, 0.93)
#         self.trans = RooRealVar("trans" + samplename,"trans" + samplename,2.2)
#         self.sigBd1  = RooApollonios("SigmodelBd1_"+samplename,"SigmodelBd1_"+samplename, Mass, self.meanBd, self.sigma1, self.coef, self.trans, ncb)
#         self.sigBs1  = RooApollonios("SigmodelBs1_"+samplename,"SigmodelBs1_"+samplename, Mass, self.meanBs, self.sigma1, self.coef, self.trans, ncb)
#         self.sigBd2  = RooApollonios("SigmodelBd2_"+samplename,"SigmodelBd2_"+samplename, Mass, self.meanBd, self.sigma2, self.coef, self.trans, ncb)
#         self.sigBs2  = RooApollonios("SigmodelBs2_"+samplename,"SigmodelBs2_"+samplename, Mass, self.meanBs, self.sigma2, self.coef, self.trans, ncb)
#         self.sigBd = RooAddPdf("SigmodelBd_"+samplename,"SigmodelBd_"+samplename, self.sigBd1, self.sigBd2, self.f1)
#         self.sigBs = RooAddPdf("SigmodelBs_"+samplename,"SigmodelBs_"+samplename, self.sigBs1, self.sigBs2, self.f1)
        


def InitSignalPdfs(namephys, namesample, acc_type = 1 ):
    sp =  AngularPDFMOD( namephys, namesample + "_pos_", 1, acc_type = acc_type)
    sn =  AngularPDFMOD( namephys, namesample + "_neg_", -1, acc_type = acc_type)
    return sp, sn

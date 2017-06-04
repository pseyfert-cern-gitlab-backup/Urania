from parameters import *
from math import exp
import numpy as np
np.random.seed(1)


gROOT.ProcessLine( "struct MyStructF{ Float_t afloat; };" )


# ################################################################
# F U N C T I O N S
# ################################################################


def ForceCompileLibs():

	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'KpiKpiSpectrumNW.cxx++')
	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'ComputeIntegrals.cxx++')
	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'MCGenComb.cxx++')
	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'lhcbStyle.C')
	gROOT.Reset()


def CompileLibs():

	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'KpiKpiSpectrumNW.cxx+')
	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'ComputeIntegrals.cxx+')
	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'MCGenComb.cxx++')
	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'lhcbStyle.C')
	gROOT.Reset()


def CompileLibsGRID():

	gROOT.ProcessLine('.x KpiKpiSpectrumNW.cxx++')
	gROOT.ProcessLine('.x ComputeIntegrals.cxx++')
	gROOT.ProcessLine('.x MCGenComb.cxx++')
	gROOT.ProcessLine('.x lhcbStyle.C')
	gROOT.Reset()


def information(FT_fit, datatype, Blinding = 1, NOCP = 0, NODIRCP = 0, SAMECP = 1, acc_type = 0, inf_t_res = 0, wide_window = 1, fix_re_amps = 0,\
fix_dirCP_asyms = 0, fix_im_amps = 0, fix_weak_phases = 0, fix_mixing_params = 0, fix_calib_params = 0, pw_alternative_model = 0):

	print "\n#####################################################################"
	print " R E L E V A N T   I N F O R M A T I O N   A B O U T   T H E   F I T"
	print "#####################################################################\n"
	if FT_fit:
		if (datatype == "real"): print " - FLAVOUR TAGGED, TIME DEPENDENT fit to REAL DATA corresponding to 2011 and 2012."
		else: print " - FLAVOUR TAGGED, TIME DEPENDENT fit to MONTE CARLO DATA."
	else:
		if (datatype == "real"): print " - FLAVOUR AVERAGED, TIME INTEGRATED fit to REAL DATA corresponding to 2011 and 2012."
		else: print " - FLAVOUR AVERAGED, TIME INTEGRATED fit to MONTE CARLO DATA."
	if (wide_window): print "   (WIDE WINDOW used in the Kpi invariant mass, from 750 to "+str(mHlimit)+" MeV.)\n"
	else: print "   (NARROW WINDOW used in the Kpi invariant mass, of 150 MeV around the Kst nominal mass.)\n"
	if NOCP: print " - CPV parameters NOT INCLUDED in the model.\n"
	else:
		print " - CPV parameters INCLUDED in the model."
		if Blinding: print "   BLINDED parameters."
		else: print "   UNBLINDED parameters !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!."
		if NODIRCP:
			if SAMECP: print "   One phi_s phase COMMON TO ALL THE CHANNELS.\n"
			else: print "   One phi_s phase FOR EACH CHANNEL.\n"
		else:
			if SAMECP: print "   One phi_s phase and direct CP violation asymmetry COMMON TO ALL THE CHANNELS.\n"
			else: print "   One phi_s phase and direct CP violation asymmetry FOR EACH CHANNEL.\n"
	if (acc_type == 0): print " - Using FLAT ACCEPTANCE.\n"
	elif (acc_type == 1): print " - Using PARAMETRIC ACCEPTANCE + SPLINES for fitting and plotting.\n"
	elif (acc_type == 2): print " - Using NORMALIZATION WEIGHTS + SPLINES for fitting and PARAMETRIC ACCEPTANCE + SPLINES for plotting.\n"
	elif (acc_type == 3): print " - Using EFFECTIVE ACCEPTANCE for Toy MC studies.\n"
	if inf_t_res: print " - INFINITE TIME RESOLUTION assumed."
	else: print " - FINITE TIME RESOLUTION included via gaussian convolutions."
	if pw_alternative_model: print "\n WARNING: an alternative mass model for systematic uncertainty studies is beeing used."
	if fix_re_amps: print "\n WARNING: wave fractions fixed."
	if fix_dirCP_asyms: print "\n WARNING: direct CP violation asymmetries fixed."
	if fix_im_amps: print "\n WARNING: strong phases fixed."
	if fix_weak_phases: print "\n WARNING: weak phases fixed."
	if fix_mixing_params: print "\n WARNING: Bs-Bsbar mixing parameters fixed."
	if fix_calib_params: print "\n WARNING: calibration parameters fixed."


def setInterval(quantity,deviation):
	value = quantity.getVal()
	quantity.setRange(min([value*deviation,value/deviation]),max([value*deviation,value/deviation]))


def component(j1,j2,h,j1p,j2p,hp):
	A_j1.setVal(j1)
	A_j2.setVal(j2)
	A_h.setVal(h)
	A_j1p.setVal(j1p)
	A_j2p.setVal(j2p)
	A_hp.setVal(hp)


def setParamVals(wide_window):

	if wide_window==0:
		reA00.setVal(0.968365623649)
		reA01.setVal(-0.167043935494)
		reA10.setVal(-0.966710240268)
		reA11par.setVal(-0.890415518954)
		reA11perp.setVal(0.0312168627535)
		imA00.setVal(0.912627474634)
		imA01.setVal(-2.59486531439)
		imA10.setVal(2.04993496693)
		imA11par.setVal(0.966836260964)
		imA11perp.setVal(1.81253096951)
		delta_m_Bs.setVal(17.5507040858)
		gamma_Bs.setVal(0.664716424507)
		delta_gamma_Bs.setVal(0.0849079528621)
		p0metac_SSK.setVal(0.00637523421071)
		p0metac_OS.setVal(0.00625437405326)
		Dp0half_SSK.setVal(-0.0080411256014)
		Dp0half_OS.setVal(0.00699301159399)
		p1_SSK.setVal(0.93250559122)
		p1_OS.setVal(0.985460013798)
		Dp1half_SSK.setVal(-0.0172717126031)
		Dp1half_OS.setVal(0.0329466032992)
		tres_p0_2011.setVal(0.0352455098926)
		tres_p1_2011.setVal(1.19983704763)
		tres_p0_2012.setVal(0.0366000812578)
		tres_p1_2012.setVal(1.21796290904)
		c1_mass_swave.setVal(-1.96228966361)
		c2_mass_swave.setVal(0.795790057951)
		c3_mass_swave.setVal(1.50856106636)
		c4_mass_swave.setVal(0.830889359762)

	else:
		reA00.setVal(4.03704561152)
		reA01.setVal(-1.37349820909)
		reA10.setVal(-0.483028649506)
		reA02.setVal(-0.707884480736)
		reA20.setVal(1.05069922861)
		reA11par.setVal(-0.711130432043)
		reA11perp.setVal(-0.689989599396)
		reA120.setVal(-2.17843579827)
		reA12par.setVal(-0.318685925826)
		reA12perp.setVal(-0.931425146016)
		reA210.setVal(-0.0167394568756)
		reA21par.setVal(0.599531917281)
		reA21perp.setVal(0.609166803777)
		reA220.setVal(0.0989428187961)
		reA22par.setVal(-0.344527229873)
		reA22perp.setVal(-0.0735597446873)
		reA22par2.setVal(-0.11027482205)
		reA22perp2.setVal(0.505071664841)
		imA00.setVal(2.95070029829)
		imA01.setVal(-5.26899838177)
		imA10.setVal(3.36115974768)
		imA02.setVal(-0.204865500918)
		imA20.setVal(-1.35090116155)
		imA11par.setVal(1.25026029189)
		imA11perp.setVal(1.78709857993)
		imA120.setVal(-1.23447971298)
		imA12par.setVal(-0.303655015558)
		imA12perp.setVal(0.646514008446)
		imA210.setVal(1.51061010948)
		imA21par.setVal(0.424495006601)
		imA21perp.setVal(-0.574615009196)
		imA220.setVal(0.139805940397)
		imA22par.setVal(0.341353948048)
		imA22perp.setVal(0.486595390889)
		imA22par2.setVal(0.112139473047)
		imA22perp2.setVal(-0.161167966518)
		delta_m_Bs.setVal(17.6181125786)
		gamma_Bs.setVal(0.665288627037)
		delta_gamma_Bs.setVal(0.0861831190265)
		p0metac_SSK.setVal(0.00726704398218)
		p0metac_OS.setVal(0.00784707299053)
		Dp0half_SSK.setVal(-0.00804652895371)
		Dp0half_OS.setVal(0.00699126866302)
		p1_SSK.setVal(0.928462109676)
		p1_OS.setVal(0.992187447845)
		Dp1half_SSK.setVal(-0.0152549266773)
		Dp1half_OS.setVal(0.0328106719053)
		tres_p0_2011.setVal(0.0347684351553)
		tres_p1_2011.setVal(1.15382952428)
		tres_p0_2012.setVal(0.0364512988556)
		tres_p1_2012.setVal(1.26162812367)
		c1_mass_swave.setVal(-0.299914513137)
		c2_mass_swave.setVal(-0.158588997743)
		c3_mass_swave.setVal(-0.121631369471)
		c4_mass_swave.setVal(-0.0659022290645)


def aux_PDF():
	for argument in options: options_list_aux.add(argument)
	for argument in observables: observables_list_aux.add(argument)
	for argument in re_amps: re_amps_list_aux.add(argument)
	for argument in dirCP_asyms: dirCP_asyms_list_aux.add(argument)
	for argument in im_amps: im_amps_list_aux.add(argument)
	for argument in weak_phases: weak_phases_list_aux.add(argument)
	for argument in mixing_params: mixing_params_list_aux.add(argument)
	for argument in calib_params_aux: calib_params_list_aux.add(argument)
	for argument in cond_distr_params: cond_distr_params_list_aux.add(argument)
	for argument in sys_studies: sys_studies_list_aux.add(argument)
	for argument in mass_integrals: mass_integrals_list_aux.add(argument)
	for argument in ang_integrals: ang_integrals_list_aux.add(argument)
	for argument in time_integrals: time_integrals_list_aux.add(argument)

	auxiliar_PDF = ROOT.KpiKpiSpectrumNW("auxiliar_PDF","auxiliar_PDF",options_list_aux,observables_list_aux,re_amps_list_aux,dirCP_asyms_list_aux,\
im_amps_list_aux,weak_phases_list_aux,mixing_params_list_aux,calib_params_list_aux,cond_distr_params_list_aux,sys_studies_list_aux,\
mass_integrals_list_aux,ang_integrals_list_aux,time_integrals_list_aux)

	return auxiliar_PDF
	

def PDF_with_integrals(name,description,options_arglist,wide_window,data_file,observables_arglist,re_amps_arglist,dirCP_asyms_arglist,im_amps_arglist,\
weak_phases_arglist,mixing_params_arglist,calib_params_arglist,sys_studies_arglist):

	ROOT.RooMsgService.instance().setGlobalKillBelow(ROOT.RooFit.WARNING)
	Integrator = ROOT.ComputeIntegrals("Integrator","Integrator",options_arglist,observables_arglist,mixing_params_arglist,calib_params_arglist,mass_integrals_list)

	# Calculation of the invariant mass integrals for normalization.
	if wide_window:
		option.setVal(100)
		integral100 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Im00.setVal(integral100.getVal())
		option.setVal(101)
		integral101 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Im01.setVal(integral101.getVal())
		option.setVal(110)
		integral110 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Im10.setVal(integral110.getVal())
		option.setVal(102)
		integral102 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Im02.setVal(integral102.getVal())
		option.setVal(120)
		integral120 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Im20.setVal(integral120.getVal())
		option.setVal(111)
		integral111 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Im11.setVal(integral111.getVal())
		option.setVal(112)
		integral112 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Im12.setVal(integral112.getVal())
		option.setVal(121)
		integral121 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Im21.setVal(integral121.getVal())
		option.setVal(122)
		integral122 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Im22.setVal(integral122.getVal())
	else:
		option.setVal(100)
		integral100 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im00.setVal(integral100.getVal())
		option.setVal(101)
		integral101 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im01.setVal(integral101.getVal())
		option.setVal(110)
		integral110 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im10.setVal(integral110.getVal())
		option.setVal(102)
		integral102 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im02.setVal(integral102.getVal())
		option.setVal(120)
		integral120 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im20.setVal(integral120.getVal())
		option.setVal(111)
		integral111 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im11.setVal(integral111.getVal())
		option.setVal(112)
		integral112 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im12.setVal(integral112.getVal())
		option.setVal(121)
		integral121 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im21.setVal(integral121.getVal())
		option.setVal(122)
		integral122 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im22.setVal(integral122.getVal())

	# Calculation of the angular integrals for visualization.
	option.setVal(21)
	integral21 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If1.setVal(integral21.getVal())
	option.setVal(22)
	integral22 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If2.setVal(integral22.getVal())
	option.setVal(23)
	integral23 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If3.setVal(integral23.getVal())
	option.setVal(24)
	integral24 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If4.setVal(integral24.getVal())
	option.setVal(25)
	integral25 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If5.setVal(integral25.getVal())
	option.setVal(26)
	integral26 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If6.setVal(integral26.getVal())
	option.setVal(27)
	integral27 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If7.setVal(integral27.getVal())
	option.setVal(28)
	integral28 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If8.setVal(integral28.getVal())
	option.setVal(29)
	integral29 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If9.setVal(integral29.getVal())
	option.setVal(210)
	integral210 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If10.setVal(integral210.getVal())
	option.setVal(211)
	integral211 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If11.setVal(integral211.getVal())
	option.setVal(212)
	integral212 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If12.setVal(integral212.getVal())
	option.setVal(213)
	integral213 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If13.setVal(integral213.getVal())
	option.setVal(214)
	integral214 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If14.setVal(integral214.getVal())
	option.setVal(215)
	integral215 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If15.setVal(integral215.getVal())
	option.setVal(216)
	integral216 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If16.setVal(integral216.getVal())
	option.setVal(217)
	integral217 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If17.setVal(integral217.getVal())
	option.setVal(218)
	integral218 = Integrator.createIntegral(ROOT.RooArgSet(cos1))
	If18.setVal(integral218.getVal())

	# Calculation of the invariant mass integrals for visualization.
	if wide_window:
		option.setVal(31)
		integral31 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih1Re.setVal(integral31.getVal())
		option.setVal(32)
		integral32 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih2Re.setVal(integral32.getVal())
		option.setVal(33)
		integral33 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih3Re.setVal(integral33.getVal())
		option.setVal(34)
		integral34 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih4Re.setVal(integral34.getVal())
		option.setVal(35)
		integral35 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih5Re.setVal(integral35.getVal())
		option.setVal(36)
		integral36 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih6Re.setVal(integral36.getVal())
		option.setVal(37)
		integral37 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih7Re.setVal(integral37.getVal())
		option.setVal(38)
		integral38 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih8Re.setVal(integral38.getVal())
		option.setVal(39)
		integral39 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih9Re.setVal(integral39.getVal())
		option.setVal(310)
		integral310 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih10Re.setVal(integral310.getVal())
		option.setVal(311)
		integral311 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih11Re.setVal(integral311.getVal())
		option.setVal(312)
		integral312 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih12Re.setVal(integral312.getVal())
		option.setVal(313)
		integral313 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih13Re.setVal(integral313.getVal())
		option.setVal(314)
		integral314 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih14Re.setVal(integral314.getVal())
		option.setVal(315)
		integral315 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih15Re.setVal(integral315.getVal())
		option.setVal(316)
		integral316 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih16Re.setVal(integral316.getVal())
		option.setVal(317)
		integral317 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih17Re.setVal(integral317.getVal())
		option.setVal(318)
		integral318 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih18Re.setVal(integral318.getVal())
		option.setVal(319)
		integral319 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih19Re.setVal(integral319.getVal())
		option.setVal(320)
		integral320 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih20Re.setVal(integral320.getVal())
		option.setVal(321)
		integral321 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih21Re.setVal(integral321.getVal())
		option.setVal(322)
		integral322 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih22Re.setVal(integral322.getVal())
		option.setVal(323)
		integral323 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih23Re.setVal(integral323.getVal())
		option.setVal(324)
		integral324 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih24Re.setVal(integral324.getVal())
		option.setVal(325)
		integral325 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih25Re.setVal(integral325.getVal())
		option.setVal(326)
		integral326 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih26Re.setVal(integral326.getVal())
		option.setVal(327)
		integral327 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih27Re.setVal(integral327.getVal())
		option.setVal(328)
		integral328 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih28Re.setVal(integral328.getVal())
		option.setVal(329)
		integral329 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih29Re.setVal(integral329.getVal())
		option.setVal(330)
		integral330 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih30Re.setVal(integral330.getVal())
		option.setVal(41)
		integral41 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih1Im.setVal(integral41.getVal())
		option.setVal(42)
		integral42 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih2Im.setVal(integral42.getVal())
		option.setVal(43)
		integral43 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih3Im.setVal(integral43.getVal())
		option.setVal(44)
		integral44 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih4Im.setVal(integral44.getVal())
		option.setVal(45)
		integral45 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih5Im.setVal(integral45.getVal())
		option.setVal(46)
		integral46 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih6Im.setVal(integral46.getVal())
		option.setVal(47)
		integral47 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih7Im.setVal(integral47.getVal())
		option.setVal(48)
		integral48 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih8Im.setVal(integral48.getVal())
		option.setVal(49)
		integral49 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih9Im.setVal(integral49.getVal())
		option.setVal(410)
		integral410 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih10Im.setVal(integral410.getVal())
		option.setVal(411)
		integral411 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih11Im.setVal(integral411.getVal())
		option.setVal(412)
		integral412 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih12Im.setVal(integral412.getVal())
		option.setVal(413)
		integral413 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih13Im.setVal(integral413.getVal())
		option.setVal(414)
		integral414 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih14Im.setVal(integral414.getVal())
		option.setVal(415)
		integral415 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih15Im.setVal(integral415.getVal())
		option.setVal(416)
		integral416 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih16Im.setVal(integral416.getVal())
		option.setVal(417)
		integral417 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih17Im.setVal(integral417.getVal())
		option.setVal(418)
		integral418 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih18Im.setVal(integral418.getVal())
		option.setVal(419)
		integral419 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih19Im.setVal(integral419.getVal())
		option.setVal(420)
		integral420 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih20Im.setVal(integral420.getVal())
		option.setVal(421)
		integral421 = Integrator.createIntegral(ROOT.RooArgSet(mKp1,mKp2))
		Ih21Im.setVal(integral421.getVal())
	else:
		option.setVal(31)
		integral31 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih1Re.setVal(integral31.getVal())
		option.setVal(32)
		integral32 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih2Re.setVal(integral32.getVal())
		option.setVal(33)
		integral33 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih3Re.setVal(integral33.getVal())
		option.setVal(34)
		integral34 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih4Re.setVal(integral34.getVal())
		option.setVal(35)
		integral35 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih5Re.setVal(integral35.getVal())
		option.setVal(36)
		integral36 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih6Re.setVal(integral36.getVal())
		option.setVal(37)
		integral37 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih7Re.setVal(integral37.getVal())
		option.setVal(38)
		integral38 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih8Re.setVal(integral38.getVal())
		option.setVal(39)
		integral39 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih9Re.setVal(integral39.getVal())
		option.setVal(310)
		integral310 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih10Re.setVal(integral310.getVal())
		option.setVal(311)
		integral311 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih11Re.setVal(integral311.getVal())
		option.setVal(312)
		integral312 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih12Re.setVal(integral312.getVal())
		option.setVal(313)
		integral313 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih13Re.setVal(integral313.getVal())
		option.setVal(314)
		integral314 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih14Re.setVal(integral314.getVal())
		option.setVal(315)
		integral315 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih15Re.setVal(integral315.getVal())
		option.setVal(316)
		integral316 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih16Re.setVal(integral316.getVal())
		option.setVal(317)
		integral317 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih17Re.setVal(integral317.getVal())
		option.setVal(318)
		integral318 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih18Re.setVal(integral318.getVal())
		option.setVal(319)
		integral319 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih19Re.setVal(integral319.getVal())
		option.setVal(320)
		integral320 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih20Re.setVal(integral320.getVal())
		option.setVal(321)
		integral321 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih21Re.setVal(integral321.getVal())
		option.setVal(322)
		integral322 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih22Re.setVal(integral322.getVal())
		option.setVal(323)
		integral323 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih23Re.setVal(integral323.getVal())
		option.setVal(324)
		integral324 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih24Re.setVal(integral324.getVal())
		option.setVal(325)
		integral325 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih25Re.setVal(integral325.getVal())
		option.setVal(326)
		integral326 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih26Re.setVal(integral326.getVal())
		option.setVal(327)
		integral327 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih27Re.setVal(integral327.getVal())
		option.setVal(328)
		integral328 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih28Re.setVal(integral328.getVal())
		option.setVal(329)
		integral329 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih29Re.setVal(integral329.getVal())
		option.setVal(330)
		integral330 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih30Re.setVal(integral330.getVal())
		option.setVal(41)
		integral41 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih1Im.setVal(integral41.getVal())
		option.setVal(42)
		integral42 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih2Im.setVal(integral42.getVal())
		option.setVal(43)
		integral43 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih3Im.setVal(integral43.getVal())
		option.setVal(44)
		integral44 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih4Im.setVal(integral44.getVal())
		option.setVal(45)
		integral45 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih5Im.setVal(integral45.getVal())
		option.setVal(46)
		integral46 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih6Im.setVal(integral46.getVal())
		option.setVal(47)
		integral47 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih7Im.setVal(integral47.getVal())
		option.setVal(48)
		integral48 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih8Im.setVal(integral48.getVal())
		option.setVal(49)
		integral49 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih9Im.setVal(integral49.getVal())
		option.setVal(410)
		integral410 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih10Im.setVal(integral410.getVal())
		option.setVal(411)
		integral411 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih11Im.setVal(integral411.getVal())
		option.setVal(412)
		integral412 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih12Im.setVal(integral412.getVal())
		option.setVal(413)
		integral413 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih13Im.setVal(integral413.getVal())
		option.setVal(414)
		integral414 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih14Im.setVal(integral414.getVal())
		option.setVal(415)
		integral415 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih15Im.setVal(integral415.getVal())
		option.setVal(416)
		integral416 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih16Im.setVal(integral416.getVal())
		option.setVal(417)
		integral417 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih17Im.setVal(integral417.getVal())
		option.setVal(418)
		integral418 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih18Im.setVal(integral418.getVal())
		option.setVal(419)
		integral419 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih19Im.setVal(integral419.getVal())
		option.setVal(420)
		integral420 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih20Im.setVal(integral420.getVal())
		option.setVal(421)
		integral421 = Integrator.createIntegral(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih21Im.setVal(integral421.getVal())
	
	# Calculation of the time integrals for visualization.
	option.setVal(91)
	integral91 = Integrator.createIntegral(ROOT.RooArgSet(t))
	IT_cosh.setVal(integral91.getVal())
	option.setVal(92)
	integral92 = Integrator.createIntegral(ROOT.RooArgSet(t))
	IT_sinh.setVal(integral92.getVal())
	option.setVal(93)
	integral93 = Integrator.createIntegral(ROOT.RooArgSet(t))
	IT_cos.setVal(integral93.getVal())
	option.setVal(94)
	integral94 = Integrator.createIntegral(ROOT.RooArgSet(t))
	IT_sin.setVal(integral94.getVal())

	# Backup of the integrals and normalization factors.
	integrals = ''
	integrals += 'Double_t Im00 = ' + str(Im00.getVal()) + ';\n'
	integrals += 'Double_t Im01 = ' + str(Im01.getVal()) + ';\n'
	integrals += 'Double_t Im10 = ' + str(Im10.getVal()) + ';\n'
	integrals += 'Double_t Im02 = ' + str(Im02.getVal()) + ';\n'
	integrals += 'Double_t Im20 = ' + str(Im20.getVal()) + ';\n'
	integrals += 'Double_t Im11 = ' + str(Im11.getVal()) + ';\n'
	integrals += 'Double_t Im12 = ' + str(Im12.getVal()) + ';\n'
	integrals += 'Double_t Im21 = ' + str(Im21.getVal()) + ';\n'
	integrals += 'Double_t Im22 = ' + str(Im22.getVal()) + ';\n\n'
	integrals += 'Double_t If1 = ' + str(If1.getVal()) + ';\n'
	integrals += 'Double_t If2 = ' + str(If2.getVal()) + ';\n'
	integrals += 'Double_t If3 = ' + str(If3.getVal()) + ';\n'
	integrals += 'Double_t If4 = ' + str(If4.getVal()) + ';\n'
	integrals += 'Double_t If5 = ' + str(If5.getVal()) + ';\n'
	integrals += 'Double_t If6 = ' + str(If6.getVal()) + ';\n'
	integrals += 'Double_t If7 = ' + str(If7.getVal()) + ';\n'
	integrals += 'Double_t If8 = ' + str(If8.getVal()) + ';\n'
	integrals += 'Double_t If9 = ' + str(If9.getVal()) + ';\n'
	integrals += 'Double_t If10 = ' + str(If10.getVal()) + ';\n'
	integrals += 'Double_t If11 = ' + str(If11.getVal()) + ';\n'
	integrals += 'Double_t If12 = ' + str(If12.getVal()) + ';\n'
	integrals += 'Double_t If13 = ' + str(If13.getVal()) + ';\n'
	integrals += 'Double_t If14 = ' + str(If14.getVal()) + ';\n'
	integrals += 'Double_t If15 = ' + str(If15.getVal()) + ';\n'
	integrals += 'Double_t If16 = ' + str(If16.getVal()) + ';\n'
	integrals += 'Double_t If17 = ' + str(If17.getVal()) + ';\n'
	integrals += 'Double_t If18 = ' + str(If18.getVal()) + ';\n\n'
	integrals += 'Double_t Ih1Re = ' + str(Ih1Re.getVal()) + ';\n'
	integrals += 'Double_t Ih2Re = ' + str(Ih2Re.getVal()) + ';\n'
	integrals += 'Double_t Ih3Re = ' + str(Ih3Re.getVal()) + ';\n'
	integrals += 'Double_t Ih4Re = ' + str(Ih4Re.getVal()) + ';\n'
	integrals += 'Double_t Ih5Re = ' + str(Ih5Re.getVal()) + ';\n'
	integrals += 'Double_t Ih6Re = ' + str(Ih6Re.getVal()) + ';\n'
	integrals += 'Double_t Ih7Re = ' + str(Ih7Re.getVal()) + ';\n'
	integrals += 'Double_t Ih8Re = ' + str(Ih8Re.getVal()) + ';\n'
	integrals += 'Double_t Ih9Re = ' + str(Ih9Re.getVal()) + ';\n'
	integrals += 'Double_t Ih10Re = ' + str(Ih10Re.getVal()) + ';\n'
	integrals += 'Double_t Ih11Re = ' + str(Ih11Re.getVal()) + ';\n'
	integrals += 'Double_t Ih12Re = ' + str(Ih12Re.getVal()) + ';\n'
	integrals += 'Double_t Ih13Re = ' + str(Ih13Re.getVal()) + ';\n'
	integrals += 'Double_t Ih14Re = ' + str(Ih14Re.getVal()) + ';\n'
	integrals += 'Double_t Ih15Re = ' + str(Ih15Re.getVal()) + ';\n'
	integrals += 'Double_t Ih16Re = ' + str(Ih16Re.getVal()) + ';\n'
	integrals += 'Double_t Ih17Re = ' + str(Ih17Re.getVal()) + ';\n'
	integrals += 'Double_t Ih18Re = ' + str(Ih18Re.getVal()) + ';\n'
	integrals += 'Double_t Ih19Re = ' + str(Ih19Re.getVal()) + ';\n'
	integrals += 'Double_t Ih20Re = ' + str(Ih20Re.getVal()) + ';\n'
	integrals += 'Double_t Ih21Re = ' + str(Ih21Re.getVal()) + ';\n'
	integrals += 'Double_t Ih22Re = ' + str(Ih22Re.getVal()) + ';\n'
	integrals += 'Double_t Ih23Re = ' + str(Ih23Re.getVal()) + ';\n'
	integrals += 'Double_t Ih24Re = ' + str(Ih24Re.getVal()) + ';\n'
	integrals += 'Double_t Ih25Re = ' + str(Ih25Re.getVal()) + ';\n'
	integrals += 'Double_t Ih26Re = ' + str(Ih26Re.getVal()) + ';\n'
	integrals += 'Double_t Ih27Re = ' + str(Ih27Re.getVal()) + ';\n'
	integrals += 'Double_t Ih28Re = ' + str(Ih28Re.getVal()) + ';\n'
	integrals += 'Double_t Ih29Re = ' + str(Ih29Re.getVal()) + ';\n'
	integrals += 'Double_t Ih30Re = ' + str(Ih30Re.getVal()) + ';\n'
	integrals += 'Double_t Ih1Im = ' + str(Ih1Im.getVal()) + ';\n'
	integrals += 'Double_t Ih2Im = ' + str(Ih2Im.getVal()) + ';\n'
	integrals += 'Double_t Ih3Im = ' + str(Ih3Im.getVal()) + ';\n'
	integrals += 'Double_t Ih4Im = ' + str(Ih4Im.getVal()) + ';\n'
	integrals += 'Double_t Ih5Im = ' + str(Ih5Im.getVal()) + ';\n'
	integrals += 'Double_t Ih6Im = ' + str(Ih6Im.getVal()) + ';\n'
	integrals += 'Double_t Ih7Im = ' + str(Ih7Im.getVal()) + ';\n'
	integrals += 'Double_t Ih8Im = ' + str(Ih8Im.getVal()) + ';\n'
	integrals += 'Double_t Ih9Im = ' + str(Ih9Im.getVal()) + ';\n'
	integrals += 'Double_t Ih10Im = ' + str(Ih10Im.getVal()) + ';\n'
	integrals += 'Double_t Ih11Im = ' + str(Ih11Im.getVal()) + ';\n'
	integrals += 'Double_t Ih12Im = ' + str(Ih12Im.getVal()) + ';\n'
	integrals += 'Double_t Ih13Im = ' + str(Ih13Im.getVal()) + ';\n'
	integrals += 'Double_t Ih14Im = ' + str(Ih14Im.getVal()) + ';\n'
	integrals += 'Double_t Ih15Im = ' + str(Ih15Im.getVal()) + ';\n'
	integrals += 'Double_t Ih16Im = ' + str(Ih16Im.getVal()) + ';\n'
	integrals += 'Double_t Ih17Im = ' + str(Ih17Im.getVal()) + ';\n'
	integrals += 'Double_t Ih18Im = ' + str(Ih18Im.getVal()) + ';\n'
	integrals += 'Double_t Ih19Im = ' + str(Ih19Im.getVal()) + ';\n'
	integrals += 'Double_t Ih20Im = ' + str(Ih20Im.getVal()) + ';\n'
	integrals += 'Double_t Ih21Im = ' + str(Ih21Im.getVal()) + ';\n\n'
	integrals += 'Double_t IT_cosh = ' + str(IT_cosh.getVal()) + ';\n'
	integrals += 'Double_t IT_sinh = ' + str(IT_sinh.getVal()) + ';\n'
	integrals += 'Double_t IT_cos = ' + str(IT_cos.getVal()) + ';\n'
	integrals += 'Double_t IT_sin = ' + str(IT_sin.getVal()) + ';\n\n'
	fintegrals = open('integrals.C','w')
	fintegrals.write(integrals)
	fintegrals.close()

	ROOT.RooMsgService.instance().setGlobalKillBelow(ROOT.RooFit.INFO)
	option.setVal(0)

	# Construction of the PDF.
	PDF = ROOT.KpiKpiSpectrumNW(name,description,options_arglist,observables_arglist,re_amps_arglist,dirCP_asyms_arglist,im_amps_arglist,weak_phases_arglist,mixing_params_arglist,\
calib_params_arglist,cond_distr_params_list,sys_studies_arglist,mass_integrals_list,ang_integrals_list,time_integrals_list)

	return PDF


def PDFs_with_integrals(name,description,options_11L0TIS_arglist,options_11L0noTIS_arglist,options_12L0TIS_arglist,options_12L0noTIS_arglist,wide_window,data_file,observables_arglist,\
re_amps_arglist,dirCP_asyms_arglist,im_amps_arglist,weak_phases_arglist,mixing_params_arglist,calib_params_arglist,sys_studies_arglist):

	ROOT.RooMsgService.instance().setGlobalKillBelow(ROOT.RooFit.WARNING)
	Integrator_11L0TIS = ROOT.ComputeIntegrals("Integrator_11L0TIS","Integrator_11L0TIS",options_11L0TIS_arglist,observables_arglist,mixing_params_arglist,calib_params_arglist,mass_integrals_11L0TIS_list)
	Integrator_11L0noTIS = ROOT.ComputeIntegrals("Integrator_11L0noTIS","Integrator_11L0noTIS",options_11L0noTIS_arglist,observables_arglist,mixing_params_arglist,calib_params_arglist,mass_integrals_11L0noTIS_list)
	Integrator_12L0TIS = ROOT.ComputeIntegrals("Integrator_12L0TIS","Integrator_12L0TIS",options_12L0TIS_arglist,observables_arglist,mixing_params_arglist,calib_params_arglist,mass_integrals_12L0TIS_list)
	Integrator_12L0noTIS = ROOT.ComputeIntegrals("Integrator_12L0noTIS","Integrator_12L0noTIS",options_12L0noTIS_arglist,observables_arglist,mixing_params_arglist,calib_params_arglist,mass_integrals_12L0noTIS_list)

	# Calculation of the invariant mass integrals for normalization.
	if wide_window: mass_argset = ROOT.RooArgSet(mKp1,mKp2)
	else: mass_argset = ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin)
	option.setVal(100)
	integral_11L0TIS_100 = Integrator_11L0TIS.createIntegral(mass_argset)
	Im_11L0TIS_00.setVal(integral_11L0TIS_100.getVal())
	option.setVal(101)
	integral_11L0TIS_101 = Integrator_11L0TIS.createIntegral(mass_argset)
	Im_11L0TIS_01.setVal(integral_11L0TIS_101.getVal())
	option.setVal(110)
	integral_11L0TIS_110 = Integrator_11L0TIS.createIntegral(mass_argset)
	Im_11L0TIS_10.setVal(integral_11L0TIS_110.getVal())
	option.setVal(102)
	integral_11L0TIS_102 = Integrator_11L0TIS.createIntegral(mass_argset)
	Im_11L0TIS_02.setVal(integral_11L0TIS_102.getVal())
	option.setVal(120)
	integral_11L0TIS_120 = Integrator_11L0TIS.createIntegral(mass_argset)
	Im_11L0TIS_20.setVal(integral_11L0TIS_120.getVal())
	option.setVal(111)
	integral_11L0TIS_111 = Integrator_11L0TIS.createIntegral(mass_argset)
	Im_11L0TIS_11.setVal(integral_11L0TIS_111.getVal())
	option.setVal(112)
	integral_11L0TIS_112 = Integrator_11L0TIS.createIntegral(mass_argset)
	Im_11L0TIS_12.setVal(integral_11L0TIS_112.getVal())
	option.setVal(121)
	integral_11L0TIS_121 = Integrator_11L0TIS.createIntegral(mass_argset)
	Im_11L0TIS_21.setVal(integral_11L0TIS_121.getVal())
	option.setVal(122)
	integral_11L0TIS_122 = Integrator_11L0TIS.createIntegral(mass_argset)
	Im_11L0TIS_22.setVal(integral_11L0TIS_122.getVal())
	option.setVal(100)
	integral_11L0noTIS_100 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Im_11L0noTIS_00.setVal(integral_11L0noTIS_100.getVal())
	option.setVal(101)
	integral_11L0noTIS_101 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Im_11L0noTIS_01.setVal(integral_11L0noTIS_101.getVal())
	option.setVal(110)
	integral_11L0noTIS_110 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Im_11L0noTIS_10.setVal(integral_11L0noTIS_110.getVal())
	option.setVal(102)
	integral_11L0noTIS_102 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Im_11L0noTIS_02.setVal(integral_11L0noTIS_102.getVal())
	option.setVal(120)
	integral_11L0noTIS_120 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Im_11L0noTIS_20.setVal(integral_11L0noTIS_120.getVal())
	option.setVal(111)
	integral_11L0noTIS_111 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Im_11L0noTIS_11.setVal(integral_11L0noTIS_111.getVal())
	option.setVal(112)
	integral_11L0noTIS_112 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Im_11L0noTIS_12.setVal(integral_11L0noTIS_112.getVal())
	option.setVal(121)
	integral_11L0noTIS_121 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Im_11L0noTIS_21.setVal(integral_11L0noTIS_121.getVal())
	option.setVal(122)
	integral_11L0noTIS_122 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Im_11L0noTIS_22.setVal(integral_11L0noTIS_122.getVal())
	option.setVal(100)
	integral_12L0TIS_100 = Integrator_12L0TIS.createIntegral(mass_argset)
	Im_12L0TIS_00.setVal(integral_12L0TIS_100.getVal())
	option.setVal(101)
	integral_12L0TIS_101 = Integrator_12L0TIS.createIntegral(mass_argset)
	Im_12L0TIS_01.setVal(integral_12L0TIS_101.getVal())
	option.setVal(110)
	integral_12L0TIS_110 = Integrator_12L0TIS.createIntegral(mass_argset)
	Im_12L0TIS_10.setVal(integral_12L0TIS_110.getVal())
	option.setVal(102)
	integral_12L0TIS_102 = Integrator_12L0TIS.createIntegral(mass_argset)
	Im_12L0TIS_02.setVal(integral_12L0TIS_102.getVal())
	option.setVal(120)
	integral_12L0TIS_120 = Integrator_12L0TIS.createIntegral(mass_argset)
	Im_12L0TIS_20.setVal(integral_12L0TIS_120.getVal())
	option.setVal(111)
	integral_12L0TIS_111 = Integrator_12L0TIS.createIntegral(mass_argset)
	Im_12L0TIS_11.setVal(integral_12L0TIS_111.getVal())
	option.setVal(112)
	integral_12L0TIS_112 = Integrator_12L0TIS.createIntegral(mass_argset)
	Im_12L0TIS_12.setVal(integral_12L0TIS_112.getVal())
	option.setVal(121)
	integral_12L0TIS_121 = Integrator_12L0TIS.createIntegral(mass_argset)
	Im_12L0TIS_21.setVal(integral_12L0TIS_121.getVal())
	option.setVal(122)
	integral_12L0TIS_122 = Integrator_12L0TIS.createIntegral(mass_argset)
	Im_12L0TIS_22.setVal(integral_12L0TIS_122.getVal())
	option.setVal(100)
	integral_12L0noTIS_100 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Im_12L0noTIS_00.setVal(integral_12L0noTIS_100.getVal())
	option.setVal(101)
	integral_12L0noTIS_101 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Im_12L0noTIS_01.setVal(integral_12L0noTIS_101.getVal())
	option.setVal(110)
	integral_12L0noTIS_110 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Im_12L0noTIS_10.setVal(integral_12L0noTIS_110.getVal())
	option.setVal(102)
	integral_12L0noTIS_102 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Im_12L0noTIS_02.setVal(integral_12L0noTIS_102.getVal())
	option.setVal(120)
	integral_12L0noTIS_120 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Im_12L0noTIS_20.setVal(integral_12L0noTIS_120.getVal())
	option.setVal(111)
	integral_12L0noTIS_111 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Im_12L0noTIS_11.setVal(integral_12L0noTIS_111.getVal())
	option.setVal(112)
	integral_12L0noTIS_112 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Im_12L0noTIS_12.setVal(integral_12L0noTIS_112.getVal())
	option.setVal(121)
	integral_12L0noTIS_121 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Im_12L0noTIS_21.setVal(integral_12L0noTIS_121.getVal())
	option.setVal(122)
	integral_12L0noTIS_122 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Im_12L0noTIS_22.setVal(integral_12L0noTIS_122.getVal())

	# Calculation of the angular integrals for visualization.
	option.setVal(21)
	integral_11L0TIS_21 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_1.setVal(integral_11L0TIS_21.getVal())
	option.setVal(22)
	integral_11L0TIS_22 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_2.setVal(integral_11L0TIS_22.getVal())
	option.setVal(23)
	integral_11L0TIS_23 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_3.setVal(integral_11L0TIS_23.getVal())
	option.setVal(24)
	integral_11L0TIS_24 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_4.setVal(integral_11L0TIS_24.getVal())
	option.setVal(25)
	integral_11L0TIS_25 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_5.setVal(integral_11L0TIS_25.getVal())
	option.setVal(26)
	integral_11L0TIS_26 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_6.setVal(integral_11L0TIS_26.getVal())
	option.setVal(27)
	integral_11L0TIS_27 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_7.setVal(integral_11L0TIS_27.getVal())
	option.setVal(28)
	integral_11L0TIS_28 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_8.setVal(integral_11L0TIS_28.getVal())
	option.setVal(29)
	integral_11L0TIS_29 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_9.setVal(integral_11L0TIS_29.getVal())
	option.setVal(210)
	integral_11L0TIS_210 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_10.setVal(integral_11L0TIS_210.getVal())
	option.setVal(211)
	integral_11L0TIS_211 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_11.setVal(integral_11L0TIS_211.getVal())
	option.setVal(212)
	integral_11L0TIS_212 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_12.setVal(integral_11L0TIS_212.getVal())
	option.setVal(213)
	integral_11L0TIS_213 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_13.setVal(integral_11L0TIS_213.getVal())
	option.setVal(214)
	integral_11L0TIS_214 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_14.setVal(integral_11L0TIS_214.getVal())
	option.setVal(215)
	integral_11L0TIS_215 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_15.setVal(integral_11L0TIS_215.getVal())
	option.setVal(216)
	integral_11L0TIS_216 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_16.setVal(integral_11L0TIS_216.getVal())
	option.setVal(217)
	integral_11L0TIS_217 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_17.setVal(integral_11L0TIS_217.getVal())
	option.setVal(218)
	integral_11L0TIS_218 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0TIS_18.setVal(integral_11L0TIS_218.getVal())
	option.setVal(21)
	integral_11L0noTIS_21 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_1.setVal(integral_11L0noTIS_21.getVal())
	option.setVal(22)
	integral_11L0noTIS_22 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_2.setVal(integral_11L0noTIS_22.getVal())
	option.setVal(23)
	integral_11L0noTIS_23 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_3.setVal(integral_11L0noTIS_23.getVal())
	option.setVal(24)
	integral_11L0noTIS_24 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_4.setVal(integral_11L0noTIS_24.getVal())
	option.setVal(25)
	integral_11L0noTIS_25 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_5.setVal(integral_11L0noTIS_25.getVal())
	option.setVal(26)
	integral_11L0noTIS_26 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_6.setVal(integral_11L0noTIS_26.getVal())
	option.setVal(27)
	integral_11L0noTIS_27 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_7.setVal(integral_11L0noTIS_27.getVal())
	option.setVal(28)
	integral_11L0noTIS_28 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_8.setVal(integral_11L0noTIS_28.getVal())
	option.setVal(29)
	integral_11L0noTIS_29 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_9.setVal(integral_11L0noTIS_29.getVal())
	option.setVal(210)
	integral_11L0noTIS_210 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_10.setVal(integral_11L0noTIS_210.getVal())
	option.setVal(211)
	integral_11L0noTIS_211 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_11.setVal(integral_11L0noTIS_211.getVal())
	option.setVal(212)
	integral_11L0noTIS_212 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_12.setVal(integral_11L0noTIS_212.getVal())
	option.setVal(213)
	integral_11L0noTIS_213 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_13.setVal(integral_11L0noTIS_213.getVal())
	option.setVal(214)
	integral_11L0noTIS_214 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_14.setVal(integral_11L0noTIS_214.getVal())
	option.setVal(215)
	integral_11L0noTIS_215 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_15.setVal(integral_11L0noTIS_215.getVal())
	option.setVal(216)
	integral_11L0noTIS_216 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_16.setVal(integral_11L0noTIS_216.getVal())
	option.setVal(217)
	integral_11L0noTIS_217 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_17.setVal(integral_11L0noTIS_217.getVal())
	option.setVal(218)
	integral_11L0noTIS_218 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_11L0noTIS_18.setVal(integral_11L0noTIS_218.getVal())
	option.setVal(21)
	integral_12L0TIS_21 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_1.setVal(integral_12L0TIS_21.getVal())
	option.setVal(22)
	integral_12L0TIS_22 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_2.setVal(integral_12L0TIS_22.getVal())
	option.setVal(23)
	integral_12L0TIS_23 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_3.setVal(integral_12L0TIS_23.getVal())
	option.setVal(24)
	integral_12L0TIS_24 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_4.setVal(integral_12L0TIS_24.getVal())
	option.setVal(25)
	integral_12L0TIS_25 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_5.setVal(integral_12L0TIS_25.getVal())
	option.setVal(26)
	integral_12L0TIS_26 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_6.setVal(integral_12L0TIS_26.getVal())
	option.setVal(27)
	integral_12L0TIS_27 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_7.setVal(integral_12L0TIS_27.getVal())
	option.setVal(28)
	integral_12L0TIS_28 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_8.setVal(integral_12L0TIS_28.getVal())
	option.setVal(29)
	integral_12L0TIS_29 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_9.setVal(integral_12L0TIS_29.getVal())
	option.setVal(210)
	integral_12L0TIS_210 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_10.setVal(integral_12L0TIS_210.getVal())
	option.setVal(211)
	integral_12L0TIS_211 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_11.setVal(integral_12L0TIS_211.getVal())
	option.setVal(212)
	integral_12L0TIS_212 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_12.setVal(integral_12L0TIS_212.getVal())
	option.setVal(213)
	integral_12L0TIS_213 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_13.setVal(integral_12L0TIS_213.getVal())
	option.setVal(214)
	integral_12L0TIS_214 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_14.setVal(integral_12L0TIS_214.getVal())
	option.setVal(215)
	integral_12L0TIS_215 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_15.setVal(integral_12L0TIS_215.getVal())
	option.setVal(216)
	integral_12L0TIS_216 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_16.setVal(integral_12L0TIS_216.getVal())
	option.setVal(217)
	integral_12L0TIS_217 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_17.setVal(integral_12L0TIS_217.getVal())
	option.setVal(218)
	integral_12L0TIS_218 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0TIS_18.setVal(integral_12L0TIS_218.getVal())
	option.setVal(21)
	integral_12L0noTIS_21 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_1.setVal(integral_12L0noTIS_21.getVal())
	option.setVal(22)
	integral_12L0noTIS_22 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_2.setVal(integral_12L0noTIS_22.getVal())
	option.setVal(23)
	integral_12L0noTIS_23 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_3.setVal(integral_12L0noTIS_23.getVal())
	option.setVal(24)
	integral_12L0noTIS_24 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_4.setVal(integral_12L0noTIS_24.getVal())
	option.setVal(25)
	integral_12L0noTIS_25 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_5.setVal(integral_12L0noTIS_25.getVal())
	option.setVal(26)
	integral_12L0noTIS_26 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_6.setVal(integral_12L0noTIS_26.getVal())
	option.setVal(27)
	integral_12L0noTIS_27 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_7.setVal(integral_12L0noTIS_27.getVal())
	option.setVal(28)
	integral_12L0noTIS_28 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_8.setVal(integral_12L0noTIS_28.getVal())
	option.setVal(29)
	integral_12L0noTIS_29 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_9.setVal(integral_12L0noTIS_29.getVal())
	option.setVal(210)
	integral_12L0noTIS_210 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_10.setVal(integral_12L0noTIS_210.getVal())
	option.setVal(211)
	integral_12L0noTIS_211 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_11.setVal(integral_12L0noTIS_211.getVal())
	option.setVal(212)
	integral_12L0noTIS_212 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_12.setVal(integral_12L0noTIS_212.getVal())
	option.setVal(213)
	integral_12L0noTIS_213 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_13.setVal(integral_12L0noTIS_213.getVal())
	option.setVal(214)
	integral_12L0noTIS_214 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_14.setVal(integral_12L0noTIS_214.getVal())
	option.setVal(215)
	integral_12L0noTIS_215 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_15.setVal(integral_12L0noTIS_215.getVal())
	option.setVal(216)
	integral_12L0noTIS_216 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_16.setVal(integral_12L0noTIS_216.getVal())
	option.setVal(217)
	integral_12L0noTIS_217 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_17.setVal(integral_12L0noTIS_217.getVal())
	option.setVal(218)
	integral_12L0noTIS_218 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(cos1))
	If_12L0noTIS_18.setVal(integral_12L0noTIS_218.getVal())

	# Calculation of the invariant mass integrals for visualization.
	option.setVal(31)
	integral_11L0TIS_31 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_1Re.setVal(integral_11L0TIS_31.getVal())
	option.setVal(32)
	integral_11L0TIS_32 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_2Re.setVal(integral_11L0TIS_32.getVal())
	option.setVal(33)
	integral_11L0TIS_33 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_3Re.setVal(integral_11L0TIS_33.getVal())
	option.setVal(34)
	integral_11L0TIS_34 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_4Re.setVal(integral_11L0TIS_34.getVal())
	option.setVal(35)
	integral_11L0TIS_35 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_5Re.setVal(integral_11L0TIS_35.getVal())
	option.setVal(36)
	integral_11L0TIS_36 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_6Re.setVal(integral_11L0TIS_36.getVal())
	option.setVal(37)
	integral_11L0TIS_37 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_7Re.setVal(integral_11L0TIS_37.getVal())
	option.setVal(38)
	integral_11L0TIS_38 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_8Re.setVal(integral_11L0TIS_38.getVal())
	option.setVal(39)
	integral_11L0TIS_39 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_9Re.setVal(integral_11L0TIS_39.getVal())
	option.setVal(310)
	integral_11L0TIS_310 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_10Re.setVal(integral_11L0TIS_310.getVal())
	option.setVal(311)
	integral_11L0TIS_311 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_11Re.setVal(integral_11L0TIS_311.getVal())
	option.setVal(312)
	integral_11L0TIS_312 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_12Re.setVal(integral_11L0TIS_312.getVal())
	option.setVal(313)
	integral_11L0TIS_313 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_13Re.setVal(integral_11L0TIS_313.getVal())
	option.setVal(314)
	integral_11L0TIS_314 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_14Re.setVal(integral_11L0TIS_314.getVal())
	option.setVal(315)
	integral_11L0TIS_315 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_15Re.setVal(integral_11L0TIS_315.getVal())
	option.setVal(316)
	integral_11L0TIS_316 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_16Re.setVal(integral_11L0TIS_316.getVal())
	option.setVal(317)
	integral_11L0TIS_317 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_17Re.setVal(integral_11L0TIS_317.getVal())
	option.setVal(318)
	integral_11L0TIS_318 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_18Re.setVal(integral_11L0TIS_318.getVal())
	option.setVal(319)
	integral_11L0TIS_319 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_19Re.setVal(integral_11L0TIS_319.getVal())
	option.setVal(320)
	integral_11L0TIS_320 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_20Re.setVal(integral_11L0TIS_320.getVal())
	option.setVal(321)
	integral_11L0TIS_321 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_21Re.setVal(integral_11L0TIS_321.getVal())
	option.setVal(322)
	integral_11L0TIS_322 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_22Re.setVal(integral_11L0TIS_322.getVal())
	option.setVal(323)
	integral_11L0TIS_323 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_23Re.setVal(integral_11L0TIS_323.getVal())
	option.setVal(324)
	integral_11L0TIS_324 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_24Re.setVal(integral_11L0TIS_324.getVal())
	option.setVal(325)
	integral_11L0TIS_325 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_25Re.setVal(integral_11L0TIS_325.getVal())
	option.setVal(326)
	integral_11L0TIS_326 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_26Re.setVal(integral_11L0TIS_326.getVal())
	option.setVal(327)
	integral_11L0TIS_327 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_27Re.setVal(integral_11L0TIS_327.getVal())
	option.setVal(328)
	integral_11L0TIS_328 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_28Re.setVal(integral_11L0TIS_328.getVal())
	option.setVal(329)
	integral_11L0TIS_329 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_29Re.setVal(integral_11L0TIS_329.getVal())
	option.setVal(330)
	integral_11L0TIS_330 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_30Re.setVal(integral_11L0TIS_330.getVal())
	option.setVal(41)
	integral_11L0TIS_41 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_1Im.setVal(integral_11L0TIS_41.getVal())
	option.setVal(42)
	integral_11L0TIS_42 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_2Im.setVal(integral_11L0TIS_42.getVal())
	option.setVal(43)
	integral_11L0TIS_43 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_3Im.setVal(integral_11L0TIS_43.getVal())
	option.setVal(44)
	integral_11L0TIS_44 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_4Im.setVal(integral_11L0TIS_44.getVal())
	option.setVal(45)
	integral_11L0TIS_45 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_5Im.setVal(integral_11L0TIS_45.getVal())
	option.setVal(46)
	integral_11L0TIS_46 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_6Im.setVal(integral_11L0TIS_46.getVal())
	option.setVal(47)
	integral_11L0TIS_47 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_7Im.setVal(integral_11L0TIS_47.getVal())
	option.setVal(48)
	integral_11L0TIS_48 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_8Im.setVal(integral_11L0TIS_48.getVal())
	option.setVal(49)
	integral_11L0TIS_49 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_9Im.setVal(integral_11L0TIS_49.getVal())
	option.setVal(410)
	integral_11L0TIS_410 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_10Im.setVal(integral_11L0TIS_410.getVal())
	option.setVal(411)
	integral_11L0TIS_411 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_11Im.setVal(integral_11L0TIS_411.getVal())
	option.setVal(412)
	integral_11L0TIS_412 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_12Im.setVal(integral_11L0TIS_412.getVal())
	option.setVal(413)
	integral_11L0TIS_413 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_13Im.setVal(integral_11L0TIS_413.getVal())
	option.setVal(414)
	integral_11L0TIS_414 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_14Im.setVal(integral_11L0TIS_414.getVal())
	option.setVal(415)
	integral_11L0TIS_415 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_15Im.setVal(integral_11L0TIS_415.getVal())
	option.setVal(416)
	integral_11L0TIS_416 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_16Im.setVal(integral_11L0TIS_416.getVal())
	option.setVal(417)
	integral_11L0TIS_417 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_17Im.setVal(integral_11L0TIS_417.getVal())
	option.setVal(418)
	integral_11L0TIS_418 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_18Im.setVal(integral_11L0TIS_418.getVal())
	option.setVal(419)
	integral_11L0TIS_419 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_19Im.setVal(integral_11L0TIS_419.getVal())
	option.setVal(420)
	integral_11L0TIS_420 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_20Im.setVal(integral_11L0TIS_420.getVal())
	option.setVal(421)
	integral_11L0TIS_421 = Integrator_11L0TIS.createIntegral(mass_argset)
	Ih_11L0TIS_21Im.setVal(integral_11L0TIS_421.getVal())
	option.setVal(31)
	integral_11L0noTIS_31 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_1Re.setVal(integral_11L0noTIS_31.getVal())
	option.setVal(32)
	integral_11L0noTIS_32 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_2Re.setVal(integral_11L0noTIS_32.getVal())
	option.setVal(33)
	integral_11L0noTIS_33 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_3Re.setVal(integral_11L0noTIS_33.getVal())
	option.setVal(34)
	integral_11L0noTIS_34 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_4Re.setVal(integral_11L0noTIS_34.getVal())
	option.setVal(35)
	integral_11L0noTIS_35 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_5Re.setVal(integral_11L0noTIS_35.getVal())
	option.setVal(36)
	integral_11L0noTIS_36 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_6Re.setVal(integral_11L0noTIS_36.getVal())
	option.setVal(37)
	integral_11L0noTIS_37 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_7Re.setVal(integral_11L0noTIS_37.getVal())
	option.setVal(38)
	integral_11L0noTIS_38 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_8Re.setVal(integral_11L0noTIS_38.getVal())
	option.setVal(39)
	integral_11L0noTIS_39 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_9Re.setVal(integral_11L0noTIS_39.getVal())
	option.setVal(310)
	integral_11L0noTIS_310 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_10Re.setVal(integral_11L0noTIS_310.getVal())
	option.setVal(311)
	integral_11L0noTIS_311 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_11Re.setVal(integral_11L0noTIS_311.getVal())
	option.setVal(312)
	integral_11L0noTIS_312 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_12Re.setVal(integral_11L0noTIS_312.getVal())
	option.setVal(313)
	integral_11L0noTIS_313 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_13Re.setVal(integral_11L0noTIS_313.getVal())
	option.setVal(314)
	integral_11L0noTIS_314 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_14Re.setVal(integral_11L0noTIS_314.getVal())
	option.setVal(315)
	integral_11L0noTIS_315 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_15Re.setVal(integral_11L0noTIS_315.getVal())
	option.setVal(316)
	integral_11L0noTIS_316 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_16Re.setVal(integral_11L0noTIS_316.getVal())
	option.setVal(317)
	integral_11L0noTIS_317 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_17Re.setVal(integral_11L0noTIS_317.getVal())
	option.setVal(318)
	integral_11L0noTIS_318 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_18Re.setVal(integral_11L0noTIS_318.getVal())
	option.setVal(319)
	integral_11L0noTIS_319 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_19Re.setVal(integral_11L0noTIS_319.getVal())
	option.setVal(320)
	integral_11L0noTIS_320 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_20Re.setVal(integral_11L0noTIS_320.getVal())
	option.setVal(321)
	integral_11L0noTIS_321 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_21Re.setVal(integral_11L0noTIS_321.getVal())
	option.setVal(322)
	integral_11L0noTIS_322 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_22Re.setVal(integral_11L0noTIS_322.getVal())
	option.setVal(323)
	integral_11L0noTIS_323 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_23Re.setVal(integral_11L0noTIS_323.getVal())
	option.setVal(324)
	integral_11L0noTIS_324 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_24Re.setVal(integral_11L0noTIS_324.getVal())
	option.setVal(325)
	integral_11L0noTIS_325 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_25Re.setVal(integral_11L0noTIS_325.getVal())
	option.setVal(326)
	integral_11L0noTIS_326 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_26Re.setVal(integral_11L0noTIS_326.getVal())
	option.setVal(327)
	integral_11L0noTIS_327 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_27Re.setVal(integral_11L0noTIS_327.getVal())
	option.setVal(328)
	integral_11L0noTIS_328 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_28Re.setVal(integral_11L0noTIS_328.getVal())
	option.setVal(329)
	integral_11L0noTIS_329 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_29Re.setVal(integral_11L0noTIS_329.getVal())
	option.setVal(330)
	integral_11L0noTIS_330 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_30Re.setVal(integral_11L0noTIS_330.getVal())
	option.setVal(41)
	integral_11L0noTIS_41 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_1Im.setVal(integral_11L0noTIS_41.getVal())
	option.setVal(42)
	integral_11L0noTIS_42 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_2Im.setVal(integral_11L0noTIS_42.getVal())
	option.setVal(43)
	integral_11L0noTIS_43 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_3Im.setVal(integral_11L0noTIS_43.getVal())
	option.setVal(44)
	integral_11L0noTIS_44 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_4Im.setVal(integral_11L0noTIS_44.getVal())
	option.setVal(45)
	integral_11L0noTIS_45 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_5Im.setVal(integral_11L0noTIS_45.getVal())
	option.setVal(46)
	integral_11L0noTIS_46 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_6Im.setVal(integral_11L0noTIS_46.getVal())
	option.setVal(47)
	integral_11L0noTIS_47 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_7Im.setVal(integral_11L0noTIS_47.getVal())
	option.setVal(48)
	integral_11L0noTIS_48 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_8Im.setVal(integral_11L0noTIS_48.getVal())
	option.setVal(49)
	integral_11L0noTIS_49 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_9Im.setVal(integral_11L0noTIS_49.getVal())
	option.setVal(410)
	integral_11L0noTIS_410 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_10Im.setVal(integral_11L0noTIS_410.getVal())
	option.setVal(411)
	integral_11L0noTIS_411 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_11Im.setVal(integral_11L0noTIS_411.getVal())
	option.setVal(412)
	integral_11L0noTIS_412 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_12Im.setVal(integral_11L0noTIS_412.getVal())
	option.setVal(413)
	integral_11L0noTIS_413 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_13Im.setVal(integral_11L0noTIS_413.getVal())
	option.setVal(414)
	integral_11L0noTIS_414 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_14Im.setVal(integral_11L0noTIS_414.getVal())
	option.setVal(415)
	integral_11L0noTIS_415 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_15Im.setVal(integral_11L0noTIS_415.getVal())
	option.setVal(416)
	integral_11L0noTIS_416 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_16Im.setVal(integral_11L0noTIS_416.getVal())
	option.setVal(417)
	integral_11L0noTIS_417 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_17Im.setVal(integral_11L0noTIS_417.getVal())
	option.setVal(418)
	integral_11L0noTIS_418 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_18Im.setVal(integral_11L0noTIS_418.getVal())
	option.setVal(419)
	integral_11L0noTIS_419 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_19Im.setVal(integral_11L0noTIS_419.getVal())
	option.setVal(420)
	integral_11L0noTIS_420 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_20Im.setVal(integral_11L0noTIS_420.getVal())
	option.setVal(421)
	integral_11L0noTIS_421 = Integrator_11L0noTIS.createIntegral(mass_argset)
	Ih_11L0noTIS_21Im.setVal(integral_11L0noTIS_421.getVal())
	option.setVal(31)
	integral_12L0TIS_31 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_1Re.setVal(integral_12L0TIS_31.getVal())
	option.setVal(32)
	integral_12L0TIS_32 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_2Re.setVal(integral_12L0TIS_32.getVal())
	option.setVal(33)
	integral_12L0TIS_33 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_3Re.setVal(integral_12L0TIS_33.getVal())
	option.setVal(34)
	integral_12L0TIS_34 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_4Re.setVal(integral_12L0TIS_34.getVal())
	option.setVal(35)
	integral_12L0TIS_35 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_5Re.setVal(integral_12L0TIS_35.getVal())
	option.setVal(36)
	integral_12L0TIS_36 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_6Re.setVal(integral_12L0TIS_36.getVal())
	option.setVal(37)
	integral_12L0TIS_37 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_7Re.setVal(integral_12L0TIS_37.getVal())
	option.setVal(38)
	integral_12L0TIS_38 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_8Re.setVal(integral_12L0TIS_38.getVal())
	option.setVal(39)
	integral_12L0TIS_39 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_9Re.setVal(integral_12L0TIS_39.getVal())
	option.setVal(310)
	integral_12L0TIS_310 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_10Re.setVal(integral_12L0TIS_310.getVal())
	option.setVal(311)
	integral_12L0TIS_311 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_11Re.setVal(integral_12L0TIS_311.getVal())
	option.setVal(312)
	integral_12L0TIS_312 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_12Re.setVal(integral_12L0TIS_312.getVal())
	option.setVal(313)
	integral_12L0TIS_313 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_13Re.setVal(integral_12L0TIS_313.getVal())
	option.setVal(314)
	integral_12L0TIS_314 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_14Re.setVal(integral_12L0TIS_314.getVal())
	option.setVal(315)
	integral_12L0TIS_315 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_15Re.setVal(integral_12L0TIS_315.getVal())
	option.setVal(316)
	integral_12L0TIS_316 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_16Re.setVal(integral_12L0TIS_316.getVal())
	option.setVal(317)
	integral_12L0TIS_317 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_17Re.setVal(integral_12L0TIS_317.getVal())
	option.setVal(318)
	integral_12L0TIS_318 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_18Re.setVal(integral_12L0TIS_318.getVal())
	option.setVal(319)
	integral_12L0TIS_319 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_19Re.setVal(integral_12L0TIS_319.getVal())
	option.setVal(320)
	integral_12L0TIS_320 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_20Re.setVal(integral_12L0TIS_320.getVal())
	option.setVal(321)
	integral_12L0TIS_321 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_21Re.setVal(integral_12L0TIS_321.getVal())
	option.setVal(322)
	integral_12L0TIS_322 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_22Re.setVal(integral_12L0TIS_322.getVal())
	option.setVal(323)
	integral_12L0TIS_323 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_23Re.setVal(integral_12L0TIS_323.getVal())
	option.setVal(324)
	integral_12L0TIS_324 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_24Re.setVal(integral_12L0TIS_324.getVal())
	option.setVal(325)
	integral_12L0TIS_325 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_25Re.setVal(integral_12L0TIS_325.getVal())
	option.setVal(326)
	integral_12L0TIS_326 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_26Re.setVal(integral_12L0TIS_326.getVal())
	option.setVal(327)
	integral_12L0TIS_327 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_27Re.setVal(integral_12L0TIS_327.getVal())
	option.setVal(328)
	integral_12L0TIS_328 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_28Re.setVal(integral_12L0TIS_328.getVal())
	option.setVal(329)
	integral_12L0TIS_329 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_29Re.setVal(integral_12L0TIS_329.getVal())
	option.setVal(330)
	integral_12L0TIS_330 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_30Re.setVal(integral_12L0TIS_330.getVal())
	option.setVal(41)
	integral_12L0TIS_41 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_1Im.setVal(integral_12L0TIS_41.getVal())
	option.setVal(42)
	integral_12L0TIS_42 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_2Im.setVal(integral_12L0TIS_42.getVal())
	option.setVal(43)
	integral_12L0TIS_43 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_3Im.setVal(integral_12L0TIS_43.getVal())
	option.setVal(44)
	integral_12L0TIS_44 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_4Im.setVal(integral_12L0TIS_44.getVal())
	option.setVal(45)
	integral_12L0TIS_45 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_5Im.setVal(integral_12L0TIS_45.getVal())
	option.setVal(46)
	integral_12L0TIS_46 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_6Im.setVal(integral_12L0TIS_46.getVal())
	option.setVal(47)
	integral_12L0TIS_47 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_7Im.setVal(integral_12L0TIS_47.getVal())
	option.setVal(48)
	integral_12L0TIS_48 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_8Im.setVal(integral_12L0TIS_48.getVal())
	option.setVal(49)
	integral_12L0TIS_49 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_9Im.setVal(integral_12L0TIS_49.getVal())
	option.setVal(410)
	integral_12L0TIS_410 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_10Im.setVal(integral_12L0TIS_410.getVal())
	option.setVal(411)
	integral_12L0TIS_411 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_11Im.setVal(integral_12L0TIS_411.getVal())
	option.setVal(412)
	integral_12L0TIS_412 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_12Im.setVal(integral_12L0TIS_412.getVal())
	option.setVal(413)
	integral_12L0TIS_413 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_13Im.setVal(integral_12L0TIS_413.getVal())
	option.setVal(414)
	integral_12L0TIS_414 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_14Im.setVal(integral_12L0TIS_414.getVal())
	option.setVal(415)
	integral_12L0TIS_415 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_15Im.setVal(integral_12L0TIS_415.getVal())
	option.setVal(416)
	integral_12L0TIS_416 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_16Im.setVal(integral_12L0TIS_416.getVal())
	option.setVal(417)
	integral_12L0TIS_417 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_17Im.setVal(integral_12L0TIS_417.getVal())
	option.setVal(418)
	integral_12L0TIS_418 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_18Im.setVal(integral_12L0TIS_418.getVal())
	option.setVal(419)
	integral_12L0TIS_419 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_19Im.setVal(integral_12L0TIS_419.getVal())
	option.setVal(420)
	integral_12L0TIS_420 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_20Im.setVal(integral_12L0TIS_420.getVal())
	option.setVal(421)
	integral_12L0TIS_421 = Integrator_12L0TIS.createIntegral(mass_argset)
	Ih_12L0TIS_21Im.setVal(integral_12L0TIS_421.getVal())
	option.setVal(31)
	integral_12L0noTIS_31 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_1Re.setVal(integral_12L0noTIS_31.getVal())
	option.setVal(32)
	integral_12L0noTIS_32 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_2Re.setVal(integral_12L0noTIS_32.getVal())
	option.setVal(33)
	integral_12L0noTIS_33 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_3Re.setVal(integral_12L0noTIS_33.getVal())
	option.setVal(34)
	integral_12L0noTIS_34 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_4Re.setVal(integral_12L0noTIS_34.getVal())
	option.setVal(35)
	integral_12L0noTIS_35 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_5Re.setVal(integral_12L0noTIS_35.getVal())
	option.setVal(36)
	integral_12L0noTIS_36 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_6Re.setVal(integral_12L0noTIS_36.getVal())
	option.setVal(37)
	integral_12L0noTIS_37 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_7Re.setVal(integral_12L0noTIS_37.getVal())
	option.setVal(38)
	integral_12L0noTIS_38 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_8Re.setVal(integral_12L0noTIS_38.getVal())
	option.setVal(39)
	integral_12L0noTIS_39 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_9Re.setVal(integral_12L0noTIS_39.getVal())
	option.setVal(310)
	integral_12L0noTIS_310 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_10Re.setVal(integral_12L0noTIS_310.getVal())
	option.setVal(311)
	integral_12L0noTIS_311 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_11Re.setVal(integral_12L0noTIS_311.getVal())
	option.setVal(312)
	integral_12L0noTIS_312 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_12Re.setVal(integral_12L0noTIS_312.getVal())
	option.setVal(313)
	integral_12L0noTIS_313 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_13Re.setVal(integral_12L0noTIS_313.getVal())
	option.setVal(314)
	integral_12L0noTIS_314 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_14Re.setVal(integral_12L0noTIS_314.getVal())
	option.setVal(315)
	integral_12L0noTIS_315 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_15Re.setVal(integral_12L0noTIS_315.getVal())
	option.setVal(316)
	integral_12L0noTIS_316 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_16Re.setVal(integral_12L0noTIS_316.getVal())
	option.setVal(317)
	integral_12L0noTIS_317 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_17Re.setVal(integral_12L0noTIS_317.getVal())
	option.setVal(318)
	integral_12L0noTIS_318 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_18Re.setVal(integral_12L0noTIS_318.getVal())
	option.setVal(319)
	integral_12L0noTIS_319 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_19Re.setVal(integral_12L0noTIS_319.getVal())
	option.setVal(320)
	integral_12L0noTIS_320 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_20Re.setVal(integral_12L0noTIS_320.getVal())
	option.setVal(321)
	integral_12L0noTIS_321 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_21Re.setVal(integral_12L0noTIS_321.getVal())
	option.setVal(322)
	integral_12L0noTIS_322 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_22Re.setVal(integral_12L0noTIS_322.getVal())
	option.setVal(323)
	integral_12L0noTIS_323 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_23Re.setVal(integral_12L0noTIS_323.getVal())
	option.setVal(324)
	integral_12L0noTIS_324 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_24Re.setVal(integral_12L0noTIS_324.getVal())
	option.setVal(325)
	integral_12L0noTIS_325 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_25Re.setVal(integral_12L0noTIS_325.getVal())
	option.setVal(326)
	integral_12L0noTIS_326 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_26Re.setVal(integral_12L0noTIS_326.getVal())
	option.setVal(327)
	integral_12L0noTIS_327 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_27Re.setVal(integral_12L0noTIS_327.getVal())
	option.setVal(328)
	integral_12L0noTIS_328 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_28Re.setVal(integral_12L0noTIS_328.getVal())
	option.setVal(329)
	integral_12L0noTIS_329 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_29Re.setVal(integral_12L0noTIS_329.getVal())
	option.setVal(330)
	integral_12L0noTIS_330 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_30Re.setVal(integral_12L0noTIS_330.getVal())
	option.setVal(41)
	integral_12L0noTIS_41 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_1Im.setVal(integral_12L0noTIS_41.getVal())
	option.setVal(42)
	integral_12L0noTIS_42 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_2Im.setVal(integral_12L0noTIS_42.getVal())
	option.setVal(43)
	integral_12L0noTIS_43 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_3Im.setVal(integral_12L0noTIS_43.getVal())
	option.setVal(44)
	integral_12L0noTIS_44 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_4Im.setVal(integral_12L0noTIS_44.getVal())
	option.setVal(45)
	integral_12L0noTIS_45 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_5Im.setVal(integral_12L0noTIS_45.getVal())
	option.setVal(46)
	integral_12L0noTIS_46 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_6Im.setVal(integral_12L0noTIS_46.getVal())
	option.setVal(47)
	integral_12L0noTIS_47 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_7Im.setVal(integral_12L0noTIS_47.getVal())
	option.setVal(48)
	integral_12L0noTIS_48 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_8Im.setVal(integral_12L0noTIS_48.getVal())
	option.setVal(49)
	integral_12L0noTIS_49 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_9Im.setVal(integral_12L0noTIS_49.getVal())
	option.setVal(410)
	integral_12L0noTIS_410 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_10Im.setVal(integral_12L0noTIS_410.getVal())
	option.setVal(411)
	integral_12L0noTIS_411 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_11Im.setVal(integral_12L0noTIS_411.getVal())
	option.setVal(412)
	integral_12L0noTIS_412 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_12Im.setVal(integral_12L0noTIS_412.getVal())
	option.setVal(413)
	integral_12L0noTIS_413 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_13Im.setVal(integral_12L0noTIS_413.getVal())
	option.setVal(414)
	integral_12L0noTIS_414 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_14Im.setVal(integral_12L0noTIS_414.getVal())
	option.setVal(415)
	integral_12L0noTIS_415 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_15Im.setVal(integral_12L0noTIS_415.getVal())
	option.setVal(416)
	integral_12L0noTIS_416 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_16Im.setVal(integral_12L0noTIS_416.getVal())
	option.setVal(417)
	integral_12L0noTIS_417 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_17Im.setVal(integral_12L0noTIS_417.getVal())
	option.setVal(418)
	integral_12L0noTIS_418 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_18Im.setVal(integral_12L0noTIS_418.getVal())
	option.setVal(419)
	integral_12L0noTIS_419 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_19Im.setVal(integral_12L0noTIS_419.getVal())
	option.setVal(420)
	integral_12L0noTIS_420 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_20Im.setVal(integral_12L0noTIS_420.getVal())
	option.setVal(421)
	integral_12L0noTIS_421 = Integrator_12L0noTIS.createIntegral(mass_argset)
	Ih_12L0noTIS_21Im.setVal(integral_12L0noTIS_421.getVal())

	# Calculation of the time integrals for visualization.
	option.setVal(91)
	integral_11L0TIS_91 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(t))
	IT_11L0TIS_cosh.setVal(integral_11L0TIS_91.getVal())
	option.setVal(92)
	integral_11L0TIS_92 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(t))
	IT_11L0TIS_sinh.setVal(integral_11L0TIS_92.getVal())
	option.setVal(93)
	integral_11L0TIS_93 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(t))
	IT_11L0TIS_cos.setVal(integral_11L0TIS_93.getVal())
	option.setVal(94)
	integral_11L0TIS_94 = Integrator_11L0TIS.createIntegral(ROOT.RooArgSet(t))
	IT_11L0TIS_sin.setVal(integral_11L0TIS_94.getVal())
	option.setVal(91)
	integral_11L0noTIS_91 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(t))
	IT_11L0noTIS_cosh.setVal(integral_11L0noTIS_91.getVal())
	option.setVal(92)
	integral_11L0noTIS_92 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(t))
	IT_11L0noTIS_sinh.setVal(integral_11L0noTIS_92.getVal())
	option.setVal(93)
	integral_11L0noTIS_93 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(t))
	IT_11L0noTIS_cos.setVal(integral_11L0noTIS_93.getVal())
	option.setVal(94)
	integral_11L0noTIS_94 = Integrator_11L0noTIS.createIntegral(ROOT.RooArgSet(t))
	IT_11L0noTIS_sin.setVal(integral_11L0noTIS_94.getVal())
	option.setVal(91)
	integral_12L0TIS_91 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(t))
	IT_12L0TIS_cosh.setVal(integral_12L0TIS_91.getVal())
	option.setVal(92)
	integral_12L0TIS_92 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(t))
	IT_12L0TIS_sinh.setVal(integral_12L0TIS_92.getVal())
	option.setVal(93)
	integral_12L0TIS_93 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(t))
	IT_12L0TIS_cos.setVal(integral_12L0TIS_93.getVal())
	option.setVal(94)
	integral_12L0TIS_94 = Integrator_12L0TIS.createIntegral(ROOT.RooArgSet(t))
	IT_12L0TIS_sin.setVal(integral_12L0TIS_94.getVal())
	option.setVal(91)
	integral_12L0noTIS_91 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(t))
	IT_12L0noTIS_cosh.setVal(integral_12L0noTIS_91.getVal())
	option.setVal(92)
	integral_12L0noTIS_92 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(t))
	IT_12L0noTIS_sinh.setVal(integral_12L0noTIS_92.getVal())
	option.setVal(93)
	integral_12L0noTIS_93 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(t))
	IT_12L0noTIS_cos.setVal(integral_12L0noTIS_93.getVal())
	option.setVal(94)
	integral_12L0noTIS_94 = Integrator_12L0noTIS.createIntegral(ROOT.RooArgSet(t))
	IT_12L0noTIS_sin.setVal(integral_12L0noTIS_94.getVal())

	# Backup of the integrals and normalization factors.
	integrals = ''
	integrals += 'Double_t Im_11L0TIS_00 = ' + str(Im_11L0TIS_00.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0TIS_01 = ' + str(Im_11L0TIS_01.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0TIS_10 = ' + str(Im_11L0TIS_10.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0TIS_02 = ' + str(Im_11L0TIS_02.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0TIS_20 = ' + str(Im_11L0TIS_20.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0TIS_11 = ' + str(Im_11L0TIS_11.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0TIS_12 = ' + str(Im_11L0TIS_12.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0TIS_21 = ' + str(Im_11L0TIS_21.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0TIS_22 = ' + str(Im_11L0TIS_22.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0noTIS_00 = ' + str(Im_11L0noTIS_00.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0noTIS_01 = ' + str(Im_11L0noTIS_01.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0noTIS_10 = ' + str(Im_11L0noTIS_10.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0noTIS_02 = ' + str(Im_11L0noTIS_02.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0noTIS_20 = ' + str(Im_11L0noTIS_20.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0noTIS_11 = ' + str(Im_11L0noTIS_11.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0noTIS_12 = ' + str(Im_11L0noTIS_12.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0noTIS_21 = ' + str(Im_11L0noTIS_21.getVal()) + ';\n'
	integrals += 'Double_t Im_11L0noTIS_22 = ' + str(Im_11L0noTIS_22.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0TIS_00 = ' + str(Im_12L0TIS_00.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0TIS_01 = ' + str(Im_12L0TIS_01.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0TIS_10 = ' + str(Im_12L0TIS_10.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0TIS_02 = ' + str(Im_12L0TIS_02.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0TIS_20 = ' + str(Im_12L0TIS_20.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0TIS_11 = ' + str(Im_12L0TIS_11.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0TIS_12 = ' + str(Im_12L0TIS_12.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0TIS_21 = ' + str(Im_12L0TIS_21.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0TIS_22 = ' + str(Im_12L0TIS_22.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0noTIS_00 = ' + str(Im_12L0noTIS_00.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0noTIS_01 = ' + str(Im_12L0noTIS_01.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0noTIS_10 = ' + str(Im_12L0noTIS_10.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0noTIS_02 = ' + str(Im_12L0noTIS_02.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0noTIS_20 = ' + str(Im_12L0noTIS_20.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0noTIS_11 = ' + str(Im_12L0noTIS_11.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0noTIS_12 = ' + str(Im_12L0noTIS_12.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0noTIS_21 = ' + str(Im_12L0noTIS_21.getVal()) + ';\n'
	integrals += 'Double_t Im_12L0noTIS_22 = ' + str(Im_12L0noTIS_22.getVal()) + ';\n'
	integrals += '\n'
	integrals += 'Double_t If_11L0TIS_1 = ' + str(If_11L0TIS_1.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_2 = ' + str(If_11L0TIS_2.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_3 = ' + str(If_11L0TIS_3.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_4 = ' + str(If_11L0TIS_4.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_5 = ' + str(If_11L0TIS_5.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_6 = ' + str(If_11L0TIS_6.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_7 = ' + str(If_11L0TIS_7.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_8 = ' + str(If_11L0TIS_8.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_9 = ' + str(If_11L0TIS_9.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_10 = ' + str(If_11L0TIS_10.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_11 = ' + str(If_11L0TIS_11.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_12 = ' + str(If_11L0TIS_12.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_13 = ' + str(If_11L0TIS_13.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_14 = ' + str(If_11L0TIS_14.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_15 = ' + str(If_11L0TIS_15.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_16 = ' + str(If_11L0TIS_16.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_17 = ' + str(If_11L0TIS_17.getVal()) + ';\n'
	integrals += 'Double_t If_11L0TIS_18 = ' + str(If_11L0TIS_18.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_1 = ' + str(If_11L0noTIS_1.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_2 = ' + str(If_11L0noTIS_2.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_3 = ' + str(If_11L0noTIS_3.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_4 = ' + str(If_11L0noTIS_4.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_5 = ' + str(If_11L0noTIS_5.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_6 = ' + str(If_11L0noTIS_6.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_7 = ' + str(If_11L0noTIS_7.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_8 = ' + str(If_11L0noTIS_8.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_9 = ' + str(If_11L0noTIS_9.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_10 = ' + str(If_11L0noTIS_10.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_11 = ' + str(If_11L0noTIS_11.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_12 = ' + str(If_11L0noTIS_12.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_13 = ' + str(If_11L0noTIS_13.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_14 = ' + str(If_11L0noTIS_14.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_15 = ' + str(If_11L0noTIS_15.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_16 = ' + str(If_11L0noTIS_16.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_17 = ' + str(If_11L0noTIS_17.getVal()) + ';\n'
	integrals += 'Double_t If_11L0noTIS_18 = ' + str(If_11L0noTIS_18.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_1 = ' + str(If_12L0TIS_1.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_2 = ' + str(If_12L0TIS_2.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_3 = ' + str(If_12L0TIS_3.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_4 = ' + str(If_12L0TIS_4.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_5 = ' + str(If_12L0TIS_5.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_6 = ' + str(If_12L0TIS_6.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_7 = ' + str(If_12L0TIS_7.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_8 = ' + str(If_12L0TIS_8.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_9 = ' + str(If_12L0TIS_9.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_10 = ' + str(If_12L0TIS_10.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_11 = ' + str(If_12L0TIS_11.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_12 = ' + str(If_12L0TIS_12.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_13 = ' + str(If_12L0TIS_13.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_14 = ' + str(If_12L0TIS_14.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_15 = ' + str(If_12L0TIS_15.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_16 = ' + str(If_12L0TIS_16.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_17 = ' + str(If_12L0TIS_17.getVal()) + ';\n'
	integrals += 'Double_t If_12L0TIS_18 = ' + str(If_12L0TIS_18.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_1 = ' + str(If_12L0noTIS_1.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_2 = ' + str(If_12L0noTIS_2.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_3 = ' + str(If_12L0noTIS_3.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_4 = ' + str(If_12L0noTIS_4.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_5 = ' + str(If_12L0noTIS_5.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_6 = ' + str(If_12L0noTIS_6.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_7 = ' + str(If_12L0noTIS_7.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_8 = ' + str(If_12L0noTIS_8.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_9 = ' + str(If_12L0noTIS_9.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_10 = ' + str(If_12L0noTIS_10.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_11 = ' + str(If_12L0noTIS_11.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_12 = ' + str(If_12L0noTIS_12.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_13 = ' + str(If_12L0noTIS_13.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_14 = ' + str(If_12L0noTIS_14.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_15 = ' + str(If_12L0noTIS_15.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_16 = ' + str(If_12L0noTIS_16.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_17 = ' + str(If_12L0noTIS_17.getVal()) + ';\n'
	integrals += 'Double_t If_12L0noTIS_18 = ' + str(If_12L0noTIS_18.getVal()) + ';\n'
	integrals += '\n'
	integrals += 'Double_t Ih_11L0TIS_1Re = ' + str(Ih_11L0TIS_1Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_2Re = ' + str(Ih_11L0TIS_2Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_3Re = ' + str(Ih_11L0TIS_3Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_4Re = ' + str(Ih_11L0TIS_4Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_5Re = ' + str(Ih_11L0TIS_5Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_6Re = ' + str(Ih_11L0TIS_6Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_7Re = ' + str(Ih_11L0TIS_7Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_8Re = ' + str(Ih_11L0TIS_8Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_9Re = ' + str(Ih_11L0TIS_9Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_10Re = ' + str(Ih_11L0TIS_10Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_11Re = ' + str(Ih_11L0TIS_11Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_12Re = ' + str(Ih_11L0TIS_12Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_13Re = ' + str(Ih_11L0TIS_13Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_14Re = ' + str(Ih_11L0TIS_14Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_15Re = ' + str(Ih_11L0TIS_15Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_16Re = ' + str(Ih_11L0TIS_16Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_17Re = ' + str(Ih_11L0TIS_17Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_18Re = ' + str(Ih_11L0TIS_18Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_19Re = ' + str(Ih_11L0TIS_19Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_20Re = ' + str(Ih_11L0TIS_20Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_21Re = ' + str(Ih_11L0TIS_21Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_22Re = ' + str(Ih_11L0TIS_22Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_23Re = ' + str(Ih_11L0TIS_23Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_24Re = ' + str(Ih_11L0TIS_24Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_25Re = ' + str(Ih_11L0TIS_25Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_26Re = ' + str(Ih_11L0TIS_26Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_27Re = ' + str(Ih_11L0TIS_27Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_28Re = ' + str(Ih_11L0TIS_28Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_29Re = ' + str(Ih_11L0TIS_29Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_30Re = ' + str(Ih_11L0TIS_30Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_1Im = ' + str(Ih_11L0TIS_1Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_2Im = ' + str(Ih_11L0TIS_2Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_3Im = ' + str(Ih_11L0TIS_3Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_4Im = ' + str(Ih_11L0TIS_4Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_5Im = ' + str(Ih_11L0TIS_5Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_6Im = ' + str(Ih_11L0TIS_6Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_7Im = ' + str(Ih_11L0TIS_7Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_8Im = ' + str(Ih_11L0TIS_8Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_9Im = ' + str(Ih_11L0TIS_9Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_10Im = ' + str(Ih_11L0TIS_10Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_11Im = ' + str(Ih_11L0TIS_11Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_12Im = ' + str(Ih_11L0TIS_12Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_13Im = ' + str(Ih_11L0TIS_13Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_14Im = ' + str(Ih_11L0TIS_14Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_15Im = ' + str(Ih_11L0TIS_15Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_16Im = ' + str(Ih_11L0TIS_16Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_17Im = ' + str(Ih_11L0TIS_17Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_18Im = ' + str(Ih_11L0TIS_18Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_19Im = ' + str(Ih_11L0TIS_19Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_20Im = ' + str(Ih_11L0TIS_20Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0TIS_21Im = ' + str(Ih_11L0TIS_21Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_1Re = ' + str(Ih_11L0noTIS_1Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_2Re = ' + str(Ih_11L0noTIS_2Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_3Re = ' + str(Ih_11L0noTIS_3Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_4Re = ' + str(Ih_11L0noTIS_4Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_5Re = ' + str(Ih_11L0noTIS_5Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_6Re = ' + str(Ih_11L0noTIS_6Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_7Re = ' + str(Ih_11L0noTIS_7Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_8Re = ' + str(Ih_11L0noTIS_8Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_9Re = ' + str(Ih_11L0noTIS_9Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_10Re = ' + str(Ih_11L0noTIS_10Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_11Re = ' + str(Ih_11L0noTIS_11Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_12Re = ' + str(Ih_11L0noTIS_12Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_13Re = ' + str(Ih_11L0noTIS_13Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_14Re = ' + str(Ih_11L0noTIS_14Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_15Re = ' + str(Ih_11L0noTIS_15Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_16Re = ' + str(Ih_11L0noTIS_16Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_17Re = ' + str(Ih_11L0noTIS_17Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_18Re = ' + str(Ih_11L0noTIS_18Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_19Re = ' + str(Ih_11L0noTIS_19Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_20Re = ' + str(Ih_11L0noTIS_20Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_21Re = ' + str(Ih_11L0noTIS_21Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_22Re = ' + str(Ih_11L0noTIS_22Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_23Re = ' + str(Ih_11L0noTIS_23Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_24Re = ' + str(Ih_11L0noTIS_24Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_25Re = ' + str(Ih_11L0noTIS_25Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_26Re = ' + str(Ih_11L0noTIS_26Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_27Re = ' + str(Ih_11L0noTIS_27Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_28Re = ' + str(Ih_11L0noTIS_28Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_29Re = ' + str(Ih_11L0noTIS_29Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_30Re = ' + str(Ih_11L0noTIS_30Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_1Im = ' + str(Ih_11L0noTIS_1Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_2Im = ' + str(Ih_11L0noTIS_2Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_3Im = ' + str(Ih_11L0noTIS_3Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_4Im = ' + str(Ih_11L0noTIS_4Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_5Im = ' + str(Ih_11L0noTIS_5Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_6Im = ' + str(Ih_11L0noTIS_6Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_7Im = ' + str(Ih_11L0noTIS_7Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_8Im = ' + str(Ih_11L0noTIS_8Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_9Im = ' + str(Ih_11L0noTIS_9Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_10Im = ' + str(Ih_11L0noTIS_10Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_11Im = ' + str(Ih_11L0noTIS_11Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_12Im = ' + str(Ih_11L0noTIS_12Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_13Im = ' + str(Ih_11L0noTIS_13Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_14Im = ' + str(Ih_11L0noTIS_14Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_15Im = ' + str(Ih_11L0noTIS_15Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_16Im = ' + str(Ih_11L0noTIS_16Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_17Im = ' + str(Ih_11L0noTIS_17Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_18Im = ' + str(Ih_11L0noTIS_18Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_19Im = ' + str(Ih_11L0noTIS_19Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_20Im = ' + str(Ih_11L0noTIS_20Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_11L0noTIS_21Im = ' + str(Ih_11L0noTIS_21Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_1Re = ' + str(Ih_12L0TIS_1Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_2Re = ' + str(Ih_12L0TIS_2Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_3Re = ' + str(Ih_12L0TIS_3Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_4Re = ' + str(Ih_12L0TIS_4Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_5Re = ' + str(Ih_12L0TIS_5Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_6Re = ' + str(Ih_12L0TIS_6Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_7Re = ' + str(Ih_12L0TIS_7Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_8Re = ' + str(Ih_12L0TIS_8Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_9Re = ' + str(Ih_12L0TIS_9Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_10Re = ' + str(Ih_12L0TIS_10Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_11Re = ' + str(Ih_12L0TIS_11Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_12Re = ' + str(Ih_12L0TIS_12Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_13Re = ' + str(Ih_12L0TIS_13Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_14Re = ' + str(Ih_12L0TIS_14Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_15Re = ' + str(Ih_12L0TIS_15Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_16Re = ' + str(Ih_12L0TIS_16Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_17Re = ' + str(Ih_12L0TIS_17Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_18Re = ' + str(Ih_12L0TIS_18Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_19Re = ' + str(Ih_12L0TIS_19Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_20Re = ' + str(Ih_12L0TIS_20Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_21Re = ' + str(Ih_12L0TIS_21Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_22Re = ' + str(Ih_12L0TIS_22Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_23Re = ' + str(Ih_12L0TIS_23Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_24Re = ' + str(Ih_12L0TIS_24Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_25Re = ' + str(Ih_12L0TIS_25Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_26Re = ' + str(Ih_12L0TIS_26Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_27Re = ' + str(Ih_12L0TIS_27Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_28Re = ' + str(Ih_12L0TIS_28Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_29Re = ' + str(Ih_12L0TIS_29Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_30Re = ' + str(Ih_12L0TIS_30Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_1Im = ' + str(Ih_12L0TIS_1Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_2Im = ' + str(Ih_12L0TIS_2Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_3Im = ' + str(Ih_12L0TIS_3Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_4Im = ' + str(Ih_12L0TIS_4Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_5Im = ' + str(Ih_12L0TIS_5Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_6Im = ' + str(Ih_12L0TIS_6Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_7Im = ' + str(Ih_12L0TIS_7Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_8Im = ' + str(Ih_12L0TIS_8Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_9Im = ' + str(Ih_12L0TIS_9Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_10Im = ' + str(Ih_12L0TIS_10Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_11Im = ' + str(Ih_12L0TIS_11Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_12Im = ' + str(Ih_12L0TIS_12Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_13Im = ' + str(Ih_12L0TIS_13Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_14Im = ' + str(Ih_12L0TIS_14Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_15Im = ' + str(Ih_12L0TIS_15Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_16Im = ' + str(Ih_12L0TIS_16Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_17Im = ' + str(Ih_12L0TIS_17Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_18Im = ' + str(Ih_12L0TIS_18Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_19Im = ' + str(Ih_12L0TIS_19Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_20Im = ' + str(Ih_12L0TIS_20Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0TIS_21Im = ' + str(Ih_12L0TIS_21Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_1Re = ' + str(Ih_12L0noTIS_1Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_2Re = ' + str(Ih_12L0noTIS_2Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_3Re = ' + str(Ih_12L0noTIS_3Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_4Re = ' + str(Ih_12L0noTIS_4Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_5Re = ' + str(Ih_12L0noTIS_5Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_6Re = ' + str(Ih_12L0noTIS_6Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_7Re = ' + str(Ih_12L0noTIS_7Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_8Re = ' + str(Ih_12L0noTIS_8Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_9Re = ' + str(Ih_12L0noTIS_9Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_10Re = ' + str(Ih_12L0noTIS_10Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_11Re = ' + str(Ih_12L0noTIS_11Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_12Re = ' + str(Ih_12L0noTIS_12Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_13Re = ' + str(Ih_12L0noTIS_13Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_14Re = ' + str(Ih_12L0noTIS_14Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_15Re = ' + str(Ih_12L0noTIS_15Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_16Re = ' + str(Ih_12L0noTIS_16Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_17Re = ' + str(Ih_12L0noTIS_17Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_18Re = ' + str(Ih_12L0noTIS_18Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_19Re = ' + str(Ih_12L0noTIS_19Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_20Re = ' + str(Ih_12L0noTIS_20Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_21Re = ' + str(Ih_12L0noTIS_21Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_22Re = ' + str(Ih_12L0noTIS_22Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_23Re = ' + str(Ih_12L0noTIS_23Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_24Re = ' + str(Ih_12L0noTIS_24Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_25Re = ' + str(Ih_12L0noTIS_25Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_26Re = ' + str(Ih_12L0noTIS_26Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_27Re = ' + str(Ih_12L0noTIS_27Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_28Re = ' + str(Ih_12L0noTIS_28Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_29Re = ' + str(Ih_12L0noTIS_29Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_30Re = ' + str(Ih_12L0noTIS_30Re.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_1Im = ' + str(Ih_12L0noTIS_1Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_2Im = ' + str(Ih_12L0noTIS_2Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_3Im = ' + str(Ih_12L0noTIS_3Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_4Im = ' + str(Ih_12L0noTIS_4Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_5Im = ' + str(Ih_12L0noTIS_5Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_6Im = ' + str(Ih_12L0noTIS_6Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_7Im = ' + str(Ih_12L0noTIS_7Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_8Im = ' + str(Ih_12L0noTIS_8Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_9Im = ' + str(Ih_12L0noTIS_9Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_10Im = ' + str(Ih_12L0noTIS_10Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_11Im = ' + str(Ih_12L0noTIS_11Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_12Im = ' + str(Ih_12L0noTIS_12Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_13Im = ' + str(Ih_12L0noTIS_13Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_14Im = ' + str(Ih_12L0noTIS_14Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_15Im = ' + str(Ih_12L0noTIS_15Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_16Im = ' + str(Ih_12L0noTIS_16Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_17Im = ' + str(Ih_12L0noTIS_17Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_18Im = ' + str(Ih_12L0noTIS_18Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_19Im = ' + str(Ih_12L0noTIS_19Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_20Im = ' + str(Ih_12L0noTIS_20Im.getVal()) + ';\n'
	integrals += 'Double_t Ih_12L0noTIS_21Im = ' + str(Ih_12L0noTIS_21Im.getVal()) + ';\n'
	integrals += '\n'
	integrals += 'Double_t IT_11L0TIS_cosh = ' + str(IT_11L0TIS_cosh.getVal()) + ';\n'
	integrals += 'Double_t IT_11L0TIS_sinh = ' + str(IT_11L0TIS_sinh.getVal()) + ';\n'
	integrals += 'Double_t IT_11L0TIS_cos = ' + str(IT_11L0TIS_cos.getVal()) + ';\n'
	integrals += 'Double_t IT_11L0TIS_sin = ' + str(IT_11L0TIS_sin.getVal()) + ';\n'
	integrals += 'Double_t IT_11L0noTIS_cosh = ' + str(IT_11L0noTIS_cosh.getVal()) + ';\n'
	integrals += 'Double_t IT_11L0noTIS_sinh = ' + str(IT_11L0noTIS_sinh.getVal()) + ';\n'
	integrals += 'Double_t IT_11L0noTIS_cos = ' + str(IT_11L0noTIS_cos.getVal()) + ';\n'
	integrals += 'Double_t IT_11L0noTIS_sin = ' + str(IT_11L0noTIS_sin.getVal()) + ';\n'
	integrals += 'Double_t IT_12L0TIS_cosh = ' + str(IT_12L0TIS_cosh.getVal()) + ';\n'
	integrals += 'Double_t IT_12L0TIS_sinh = ' + str(IT_12L0TIS_sinh.getVal()) + ';\n'
	integrals += 'Double_t IT_12L0TIS_cos = ' + str(IT_12L0TIS_cos.getVal()) + ';\n'
	integrals += 'Double_t IT_12L0TIS_sin = ' + str(IT_12L0TIS_sin.getVal()) + ';\n'
	integrals += 'Double_t IT_12L0noTIS_cosh = ' + str(IT_12L0noTIS_cosh.getVal()) + ';\n'
	integrals += 'Double_t IT_12L0noTIS_sinh = ' + str(IT_12L0noTIS_sinh.getVal()) + ';\n'
	integrals += 'Double_t IT_12L0noTIS_cos = ' + str(IT_12L0noTIS_cos.getVal()) + ';\n'
	integrals += 'Double_t IT_12L0noTIS_sin = ' + str(IT_12L0noTIS_sin.getVal()) + ';\n'
	fintegrals = open('integrals_4cats.C','w')
	fintegrals.write(integrals)
	fintegrals.close()

	ROOT.RooMsgService.instance().setGlobalKillBelow(ROOT.RooFit.INFO)
	option.setVal(0)

	# Construction of the PDFs.
	PDF_11L0TIS = ROOT.KpiKpiSpectrumNW(name+'_11L0TIS',description+'_11L0TIS',options_11L0TIS_arglist,observables_arglist,re_amps_arglist,dirCP_asyms_arglist,\
im_amps_arglist,weak_phases_arglist,mixing_params_arglist,calib_params_arglist,cond_distr_params_list,sys_studies_arglist,mass_integrals_11L0TIS_list,\
ang_integrals_11L0TIS_list,time_integrals_11L0TIS_list)
	PDF_11L0noTIS = ROOT.KpiKpiSpectrumNW(name+'_11L0noTIS',description+'_11L0noTIS',options_11L0noTIS_arglist,observables_arglist,re_amps_arglist,dirCP_asyms_arglist,\
im_amps_arglist,weak_phases_arglist,mixing_params_arglist,calib_params_arglist,cond_distr_params_list,sys_studies_arglist,mass_integrals_11L0noTIS_list,\
ang_integrals_11L0noTIS_list,time_integrals_11L0noTIS_list)
	PDF_12L0TIS = ROOT.KpiKpiSpectrumNW(name+'_12L0TIS',description+'_12L0TIS',options_12L0TIS_arglist,observables_arglist,re_amps_arglist,dirCP_asyms_arglist,\
im_amps_arglist,weak_phases_arglist,mixing_params_arglist,calib_params_arglist,cond_distr_params_list,sys_studies_arglist,mass_integrals_12L0TIS_list,\
ang_integrals_12L0TIS_list,time_integrals_12L0TIS_list)
	PDF_12L0noTIS = ROOT.KpiKpiSpectrumNW(name+'_12L0noTIS',description+'_12L0noTIS',options_12L0noTIS_arglist,observables_arglist,re_amps_arglist,dirCP_asyms_arglist,\
im_amps_arglist,weak_phases_arglist,mixing_params_arglist,calib_params_arglist,cond_distr_params_list,sys_studies_arglist,mass_integrals_12L0noTIS_list,\
ang_integrals_12L0noTIS_list,time_integrals_12L0noTIS_list)

	return PDF_11L0TIS, PDF_11L0noTIS, PDF_12L0TIS, PDF_12L0noTIS

def etacomb(q1var,eta1var,q2var,eta2var):
   p_Bs = (1.+0.5*q1var*(1.-q1var-2.*eta1var))*(1.+0.5*q2var*(1.-q2var-2.*eta2var))
   p_Bsbar = (1.-0.5*q1var*(1.+q1var-2.*eta1var))*(1.-0.5*q2var*(1.+q2var-2.*eta2var))
   return min(p_Bs,p_Bsbar)/(p_Bs+p_Bsbar)

def loadData(file_path, datatype, data_file, data_tree, MC_file, MC_tree, MC_type, TD_fit, weighted, wide_window = 1, extra_cuts = "", evnum_limit = 0, GRID = 0):

	# Information.
	print "\n#####################################################################"
	print " I N P U T   D A T A"
	print "#####################################################################\n"
	if (evnum_limit == 0): print 'All events selected.'
	else: print str(evnum_limit)+' events selected.'
	if weighted: print 'Using sWeights (only implemented for real data, not simulation).'
	else: print 'Not using sWeights.'

	# Input file.
	m1_name = "B_s0_DTF_KST1_M"
	m2_name = "B_s0_DTF_KST2_M"
	cos1_name = "B_s0_DTF_B_s0_CosTheta1"
	cos2_name = "B_s0_DTF_B_s0_CosTheta2"
	phi_name = "B_s0_DTF_B_s0_PHI_TRY4"
	t_name = "B_s0_DTF_TAU"
	terror_name = "B_s0_DTF_TAUERR"
	if (GRID == 1):
		data_file = "AnalysisOutWSWeightsSelectedAllBranchesReduced.root"
		data_tree = "AnalysisTree"
		file_in = ROOT.TFile(data_file)
		tree = file_in.Get(data_tree)
		print 'Loading data from ' + data_file + ':' + data_tree
		#print 'Loading data from InvariantMassFitOut.dat'
		#tree = ROOT.TTree("DecayTree","DecayTree")
		#tree.ReadFile("InvariantMassFitOut.dat",m1_name+":"+m2_name+":"+cos1_name+":"+cos2_name+":"+phi_name+":"+t_name+":"+terror_name+":"+dec_SSK_name+":"+dec_OS_name+":"+eta_SSK_name+":"+eta_OS_name+":itype:"+L0TISline_name+":"+L0TOSline_name+":"+mKpiKpi_name+":"+weight_name)
	else:
		br_list = [m1_name,m2_name,cos1_name,cos2_name,phi_name,t_name,terror_name,dec_SSK_name,dec_OS_name,eta_SSK_name,eta_OS_name,L0TISline_name,L0TOSline_name,"itype"]
		if (datatype == "real"):
			br_list.append("sweight")
			file_in = ROOT.TFile(file_path + data_file)
			tree = file_in.Get(data_tree)
			tree.SetBranchStatus("*",0)
			for br in br_list: tree.SetBranchStatus(br,1)
			print 'Loading data from ' + data_file + ':' + data_tree
		elif (datatype == "MC"):
			file_in = ROOT.TFile(file_path + MC_file)
			tree = file_in.Get(MC_tree)
			tree.SetBranchStatus("*",0)
			for br in br_list: tree.SetBranchStatus(br,1)
			print 'Loading data from ' + MC_file + ':' + MC_tree
			if (MC_type == 0):
				print 'Simulation type: Toy MC'
			elif (MC_type == 1):
				print 'Simulation type: VV'
			#	m1_name = "B_s0_DTF_KST1_TRUE_M"
			#	m2_name = "B_s0_DTF_KST2_TRUE_M"
			#	cos1_name = "B_s0_DTF_KST1_TRUE_COSTHETA"
			#	cos2_name = "B_s0_DTF_KST2_TRUE_COSTHETA"
			#	phi_name = "B_s0_DTF_B_s0_PHI_TRY4_TRUE_TRY4"
			#	t_name = "B_s0_DTF_TAU"
			#	terror_name = "B_s0_DTF_TAUERR"

	print 'M1 branch:',m1_name
	print 'M2 branch:',m2_name
	print 'cos1 branch:',cos1_name
	print 'cos2 branch:',cos2_name
	print 'phi branch:',phi_name
	print 't branch:',t_name
	print 'terr branch:',terror_name

	# Tree with the selected events.
	file_out = ROOT.TFile(file_path + "trash.root","recreate")
	if wide_window: range_cut = m1_name+"<="+str(mHlimit)+" && "+m2_name+"<="+str(mHlimit)+" && "+t_name+">=0. && "+t_name+"<=12. && "+eta_SSK_name+"<=0.5 && "+eta_OS_name+"<=0.5"
	else: range_cut = "abs("+m1_name+"-900.)<150. && abs("+m2_name+"-900.)<150. && "+t_name+">=0. && "+t_name+"<=12. && "+eta_SSK_name+"<=0.5 && "+eta_OS_name+"<=0.5"
	if extra_cuts == "": tree2 = tree.CopyTree(range_cut)
	else:
		tree2 = tree.CopyTree(range_cut + " && " + extra_cuts)
		print 'Additional cut string: "' + extra_cuts+ '"'

	sumwtotal = 0.
	if (datatype == "real") and weighted: sumw, sumw2 = [[0.,0.],[0.,0.]], [[0.,0.],[0.,0.]]

	for i in tree2:
		wi = 1.
		if (datatype == "real") and weighted:
			wi = eval("i."+weight_name)
			if i.itype == 71:
				if eval("i."+L0TISline_name) == 1:
					sumw[0][0] += wi
					sumw2[0][0] += wi*wi
				elif (eval("i."+L0TISline_name) == 0 and eval("i."+L0TOSline_name) == 1):
					sumw[0][1] += wi
					sumw2[0][1] += wi*wi
			elif i.itype == 81:
				if eval("i."+L0TISline_name) == 1:
					sumw[1][0] += wi
					sumw2[1][0] += wi*wi
				elif (eval("i."+L0TISline_name) == 0 and eval("i."+L0TOSline_name) == 1):
					sumw[1][1] += wi
					sumw2[1][1] += wi*wi
		sumwtotal += wi

	print 'Signal yield = '+str(int(sumwtotal))
	if (datatype == "real") and weighted:
		corrfactor = [[sumw[0][0]/sumw2[0][0],sumw[0][1]/sumw2[0][1]],[sumw[1][0]/sumw2[1][0],sumw[1][1]/sumw2[1][1]]]
		print 'Effective signal yield = '+str(int(corrfactor[0][0]*sumw[0][0]+corrfactor[0][1]*sumw[0][1]+corrfactor[1][0]*sumw[1][0]+corrfactor[1][1]*sumw[1][1]))
	print ''

	# Construction of sWeighted datasets.

	tageff_SSK = 0.
	tageff_OS = 0.
	tageff_comb = 0.
	mean_eta_SSK = 0.
	mean_eta_OS = 0.
	mean_eta_comb = 0.
	norm_mean_eta_SSK = 0.
	norm_mean_eta_OS = 0.
	norm_mean_eta_comb = 0.
	mean_deltat_2011 = 0.
	mean_deltat_2012 = 0.
	norm_mean_deltat_2011 = 0.
	norm_mean_deltat_2012 = 0.

	if (wide_window):
		data_11L0TIS_ = ROOT.RooDataSet("data_11L0TIS_","data_11L0TIS_",ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
		data_11L0noTIS_ = ROOT.RooDataSet("data_11L0noTIS_","data_11L0noTIS_",ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
		data_12L0TIS_ = ROOT.RooDataSet("data_12L0TIS_","data_12L0TIS_",ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
		data_12L0noTIS_ = ROOT.RooDataSet("data_12L0noTIS_","data_12L0noTIS_",ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
	else:
		data_11L0TIS_ = ROOT.RooDataSet("data_11L0TIS_","data_11L0TIS_",ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
		data_11L0noTIS_ = ROOT.RooDataSet("data_11L0noTIS_","data_11L0noTIS_",ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
		data_12L0TIS_ = ROOT.RooDataSet("data_12L0TIS_","data_12L0TIS_",ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
		data_12L0noTIS_ = ROOT.RooDataSet("data_12L0noTIS_","data_12L0noTIS_",ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
	TD_extravars_float_11L0TIS = ROOT.RooDataSet("TD_extravars_float_11L0TIS","TD_extravars_float_11L0TIS",ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
	TD_extravars_float_11L0noTIS = ROOT.RooDataSet("TD_extravars_float_11L0noTIS","TD_extravars_float_11L0noTIS",ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
	TD_extravars_float_12L0TIS = ROOT.RooDataSet("TD_extravars_float_12L0TIS","TD_extravars_float_12L0TIS",ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
	TD_extravars_float_12L0noTIS = ROOT.RooDataSet("TD_extravars_float_12L0noTIS","TD_extravars_float_12L0noTIS",ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
	TD_extravars_int_11L0TIS = ROOT.RooDataSet("TD_extravars_int_11L0TIS","TD_extravars_int_11L0TIS",ROOT.RooArgSet(decision_SSK,decision_OS))
	TD_extravars_int_11L0noTIS = ROOT.RooDataSet("TD_extravars_int_11L0noTIS","TD_extravars_int_11L0noTIS",ROOT.RooArgSet(decision_SSK,decision_OS))
	TD_extravars_int_12L0TIS = ROOT.RooDataSet("TD_extravars_int_12L0TIS","TD_extravars_int_12L0TIS",ROOT.RooArgSet(decision_SSK,decision_OS))
	TD_extravars_int_12L0noTIS = ROOT.RooDataSet("TD_extravars_int_12L0noTIS","TD_extravars_int_12L0noTIS",ROOT.RooArgSet(decision_SSK,decision_OS))
	hist_mistag_SSK = ROOT.RooDataHist("hist_mistag_SSK","hist_mistag_SSK",ROOT.RooArgSet(etamistag_SSK))
	hist_mistag_OS = ROOT.RooDataHist("hist_mistag_OS","hist_mistag_OS",ROOT.RooArgSet(etamistag_OS))
	hist_deltat = ROOT.RooDataHist("hist_deltat","hist_deltat",ROOT.RooArgSet(terror))
	ev_counter = 0
	ev_counter_11L0TIS = 0
	ev_counter_11L0noTIS = 0
	ev_counter_12L0TIS = 0
	ev_counter_12L0noTIS = 0

	for i in tree2:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			if (datatype == "real") and weighted: weighttag = eval("i."+weight_name)
			else: weighttag = 1.
			if eval("i."+dec_SSK_name) != 0:
				tageff_SSK += weighttag/sumwtotal
				mean_eta_SSK += weighttag * eval("i."+eta_SSK_name)
				norm_mean_eta_SSK += weighttag
			if eval("i."+dec_OS_name) != 0:
				tageff_OS += weighttag/sumwtotal
				mean_eta_OS += weighttag * eval("i."+eta_OS_name)
				norm_mean_eta_OS += weighttag
			if (eval("i."+dec_SSK_name) != 0) or (eval("i."+dec_OS_name) != 0):
				tageff_comb += weighttag/sumwtotal
				mean_eta_comb += weighttag * etacomb(eval("i."+dec_SSK_name),eval("i."+eta_SSK_name),eval("i."+dec_OS_name),eval("i."+eta_OS_name))
				norm_mean_eta_comb += weighttag
			if (wide_window):
				mKp1.setVal(eval("i."+m1_name))
				mKp2.setVal(eval("i."+m2_name))
			else:
				mKp1_narrowwin.setVal(eval("i."+m1_name))
				mKp2_narrowwin.setVal(eval("i."+m2_name))
			cos1.setVal(eval("i."+cos1_name))
			cos2.setVal(eval("i."+cos2_name))
			phi.setVal(eval("i."+phi_name))
			t.setVal(eval("i."+t_name))
			etamistag_SSK.setVal(eval("i."+eta_SSK_name))
			etamistag_OS.setVal(eval("i."+eta_OS_name))
			terror.setVal(eval("i."+terror_name))
			weight_fit.setVal(1)
			weight_plot.setVal(1)
			decision_SSK.setIndex(int(eval("i."+dec_SSK_name)))
			decision_OS.setIndex(int(eval("i."+dec_OS_name)))

			if (datatype == "real"):
				if i.itype == 71:
					mean_deltat_2011 += weighttag * eval("i."+terror_name)
					norm_mean_deltat_2011 += weighttag
					if eval("i."+L0TISline_name) == 1:
						if weighted:
							weight_fit.setVal(corrfactor[0][0]*eval("i."+weight_name))
							weight_plot.setVal(eval("i."+weight_name))
						if (wide_window): data_11L0TIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
						else: data_11L0TIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
						TD_extravars_float_11L0TIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
						TD_extravars_int_11L0TIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
						ev_counter_11L0TIS += 1
					elif (eval("i."+L0TISline_name) == 0 and eval("i."+L0TOSline_name) == 1):
						if weighted:
							weight_fit.setVal(corrfactor[0][1]*eval("i."+weight_name))
							weight_plot.setVal(eval("i."+weight_name))
						if (wide_window): data_11L0noTIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
						else: data_11L0noTIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
						TD_extravars_float_11L0noTIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
						TD_extravars_int_11L0noTIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
						ev_counter_11L0noTIS += 1
				elif i.itype == 81:
					mean_deltat_2012 += weighttag * eval("i."+terror_name)
					norm_mean_deltat_2012 += weighttag
					if eval("i."+L0TISline_name) == 1:
						if weighted:
							weight_fit.setVal(corrfactor[1][0]*eval("i."+weight_name))
							weight_plot.setVal(eval("i."+weight_name))
						if (wide_window): data_12L0TIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
						else: data_12L0TIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
						TD_extravars_float_12L0TIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
						TD_extravars_int_12L0TIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
						ev_counter_12L0TIS += 1
					elif (eval("i."+L0TISline_name) == 0 and eval("i."+L0TOSline_name) == 1):
						if weighted:
							weight_fit.setVal(corrfactor[1][1]*eval("i."+weight_name))
							weight_plot.setVal(eval("i."+weight_name))
						if (wide_window): data_12L0noTIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
						else: data_12L0noTIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
						TD_extravars_float_12L0noTIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
						TD_extravars_int_12L0noTIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
						ev_counter_12L0noTIS += 1
				if i.itype>0:
					if (etamistag_SSK.getVal() < 0.5): hist_mistag_SSK.add(ROOT.RooArgSet(etamistag_SSK),weight_fit.getVal())
					if (etamistag_OS.getVal() < 0.5): hist_mistag_OS.add(ROOT.RooArgSet(etamistag_OS),weight_fit.getVal())
					hist_deltat.add(ROOT.RooArgSet(terror),weight_fit.getVal())

			elif (datatype == "MC"):

				if (MC_type == 0):
					rannum = random.Random().uniform(0,1)
					if (rannum<=0.25):
						mean_deltat_2011 += weighttag * eval("i."+terror_name)
						norm_mean_deltat_2011 += weighttag
						if (wide_window): data_11L0TIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
						else: data_11L0TIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
						TD_extravars_float_11L0TIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
						TD_extravars_int_11L0TIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
						ev_counter_11L0TIS += 1
					elif (rannum>0.25 and rannum<=0.5):
						mean_deltat_2011 += weighttag * eval("i."+terror_name)
						norm_mean_deltat_2011 += weighttag
						if (wide_window): data_11L0noTIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
						else: data_11L0noTIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
						TD_extravars_float_11L0noTIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
						TD_extravars_int_11L0noTIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
						ev_counter_11L0noTIS += 1
					elif (rannum>0.5 and rannum<=0.75):
						mean_deltat_2012 += weighttag * eval("i."+terror_name)
						norm_mean_deltat_2012 += weighttag
						if (wide_window): data_12L0TIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
						else: data_12L0TIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
						TD_extravars_float_12L0TIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
						TD_extravars_int_12L0TIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
						ev_counter_12L0TIS += 1
					else:
						mean_deltat_2012 += weighttag * eval("i."+terror_name)
						norm_mean_deltat_2012 += weighttag
						if (wide_window): data_12L0noTIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
						else: data_12L0noTIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
						TD_extravars_float_12L0noTIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
						TD_extravars_int_12L0noTIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
						ev_counter_12L0noTIS += 1

				elif (MC_type == 1):
					if i.itype == -70:
						mean_deltat_2011 += weighttag * eval("i."+terror_name)
						norm_mean_deltat_2011 += weighttag
						if eval("i."+L0TISline_name) == 1:
							if (wide_window): data_11L0TIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
							else: data_11L0TIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
							TD_extravars_float_11L0TIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
							TD_extravars_int_11L0TIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
							ev_counter_11L0TIS += 1
						elif (eval("i."+L0TISline_name) == 0 and eval("i."+L0TOSline_name) == 1):
							if (wide_window): data_11L0noTIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
							else: data_11L0noTIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
							TD_extravars_float_11L0noTIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
							TD_extravars_int_11L0noTIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
							ev_counter_11L0noTIS += 1
					elif i.itype == -80:
						mean_deltat_2012 += weighttag * eval("i."+terror_name)
						norm_mean_deltat_2012 += weighttag
						if eval("i."+L0TISline_name) == 1:
							if (wide_window): data_12L0TIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
							else: data_12L0TIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
							TD_extravars_float_12L0TIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
							TD_extravars_int_12L0TIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
							ev_counter_12L0TIS += 1
						elif (eval("i."+L0TISline_name) == 0 and eval("i."+L0TOSline_name) == 1):
							if (wide_window): data_12L0noTIS_.add(ROOT.RooArgSet(mKp1,mKp2,cos1,cos2,phi,weight_fit,weight_plot))
							else: data_12L0noTIS_.add(ROOT.RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,weight_fit,weight_plot))
							TD_extravars_float_12L0noTIS.add(ROOT.RooArgSet(t,terror,etamistag_SSK,etamistag_OS))
							TD_extravars_int_12L0noTIS.add(ROOT.RooArgSet(decision_SSK,decision_OS))
							ev_counter_12L0noTIS += 1

			ev_counter += 1

	if TD_fit:

		data_11L0TIS_.merge(TD_extravars_float_11L0TIS)
		data_11L0noTIS_.merge(TD_extravars_float_11L0noTIS)
		data_12L0TIS_.merge(TD_extravars_float_12L0TIS)
		data_12L0noTIS_.merge(TD_extravars_float_12L0noTIS)
		data_11L0TIS_.merge(TD_extravars_int_11L0TIS)
		data_11L0noTIS_.merge(TD_extravars_int_11L0noTIS)
		data_12L0TIS_.merge(TD_extravars_int_12L0TIS)
		data_12L0noTIS_.merge(TD_extravars_int_12L0noTIS)

		for fas in [FullArgSetFitWide,FullArgSetPlotWide,FullArgSetFitNarrow,FullArgSetPlotNarrow]:
			fas.add(t)
			fas.add(terror)
			fas.add(etamistag_SSK)
			fas.add(etamistag_OS)
			fas.add(decision_SSK)
			fas.add(decision_OS)

		mean_eta_SSK = mean_eta_SSK/norm_mean_eta_SSK
		mean_eta_OS = mean_eta_OS/norm_mean_eta_OS
		mean_eta_comb = mean_eta_comb/norm_mean_eta_comb
		etac_SSK.setVal(mean_eta_SSK)
		etac_OS.setVal(mean_eta_OS)
		tagpow_SSK = tageff_SSK*(1.-2.*mean_eta_SSK)**2
		tagpow_OS = tageff_OS*(1.-2.*mean_eta_OS)**2
		tagpow_comb = tageff_comb*(1.-2.*mean_eta_comb)**2
		tag_eff_SSK.setVal(tageff_SSK)
		tag_eff_OS.setVal(tageff_OS)
		mean_deltat_2011 = mean_deltat_2011/norm_mean_deltat_2011
		mean_deltat_2012 = mean_deltat_2012/norm_mean_deltat_2012
		tres_deltatmean_2011.setVal(mean_deltat_2011)
		tres_deltatmean_2012.setVal(mean_deltat_2012)
		print 'SSK tagger:'
		print 'tagging efficiency = '+str(tageff_SSK)
		print '<eta> = '+str(mean_eta_SSK)
		print 'pre-calibration tagging power = '+str(tagpow_SSK)
		print ''
		print 'OS tagger:'
		print 'tagging efficiency = '+str(tageff_OS)
		print '<eta> = '+str(mean_eta_OS)
		print 'pre-calibration tagging power = '+str(tagpow_OS)
		print ''
		print 'SSK + OS combination:'
		print 'tagging efficiency = '+str(tageff_comb)
		print 'pre-calibration tagging power = '+str(tagpow_comb)
		print ''
		print '<delta_t> (2011) = '+str(mean_deltat_2011)
		print '<delta_t> (2012) = '+str(mean_deltat_2012)
		print ''

	print str(ev_counter) + ' events loaded.'
	if (datatype == "real") and weighted: print 'Eff. yield categ. distribution: cat[2011,L0TIS] = '+str(int(corrfactor[0][0]*sumw[0][0]))+ ', cat[2011,L0noTIS] = '+str(int(corrfactor[0][1]*sumw[0][1]))+', cat[2012,L0TIS] = '+str(int(corrfactor[1][0]*sumw[1][0]))+ ', cat[2012,L0noTIS] = '+str(int(corrfactor[1][1]*sumw[1][1]))
	else: print 'Yield categ. distribution: cat[2011,L0TIS] = '+str(ev_counter_11L0TIS)+ ', cat[2011,L0noTIS] = '+str(ev_counter_11L0noTIS)+', cat[2012,L0TIS] = '+str(ev_counter_12L0TIS)+ ', cat[2012,L0noTIS] = '+str(ev_counter_12L0noTIS)

	data_full_ = ROOT.RooDataSet("data_full_","data_full_",data_11L0TIS_.get(),ROOT.RooFit.Index(yeartrigcat),ROOT.RooFit.Import("2011_L0TIS",data_11L0TIS_),ROOT.RooFit.Import("2011_L0noTIS",data_11L0noTIS_),\
ROOT.RooFit.Import("2012_L0TIS",data_12L0TIS_),ROOT.RooFit.Import("2012_L0noTIS",data_12L0noTIS_))

	if wide_window:
		data_full_fit = ROOT.RooDataSet("data_full_fit","data_full_fit",data_full_,FullArgSetFitWide,"",weight_name+"_fit")
		data_full_plot = ROOT.RooDataSet("data_full_plot","data_full_plot",data_full_,FullArgSetPlotWide,"",weight_name+"_plot")
	else:
		data_full_fit = ROOT.RooDataSet("data_full_fit","data_full_fit",data_full_,FullArgSetFitNarrow,"",weight_name+"_fit")
		data_full_plot = ROOT.RooDataSet("data_full_plot","data_full_plot",data_full_,FullArgSetPlotNarrow,"",weight_name+"_plot")

	file_out.Close()

	return [data_full_fit,data_full_plot,data_11L0TIS_,data_11L0noTIS_,data_12L0TIS_,data_12L0noTIS_], hist_mistag_SSK, hist_mistag_OS, hist_deltat

def MCtruth(ev):
	if abs(ev.B_s0_TRUEID) == 531:
		if ev.Kplus_TRUEID == 321:
			if ev.Kminus_TRUEID == -321:
				if ev.Piplus_TRUEID == 211:
					if ev.Piminus_TRUEID == -211: return 1
	return 0

def MCsetcut(year_aux,trig_aux,set_aux):
	if trig_aux == 0: cut_aux = "B_s0_L0Global_TIS==1 && "
	else: cut_aux = "B_s0_L0Global_TIS==0 && B_s0_L0HadronDecision_TOS==1 && "
	if year_aux == 0:
		if set_aux == 0: cut_aux += "itype==-73"
		elif set_aux == 1: cut_aux += "itype==-70"
		else: cut_aux += "(itype==-73 || itype==-70)"
	else:
		if set_aux == 0: cut_aux += "itype==-83"
		elif set_aux == 1: cut_aux += "itype==-80"
		else: cut_aux += "(itype==-83 || itype==-80)"
	return cut_aux

def dataMCcorrweight(entry):

	#wPIDkaon1 = h2DPIDkaon.GetBinContent(h2DPIDkaon.FindBin(entry.Kplus_P,entry.Kplus_ETA))
	#wPIDkaon2 = h2DPIDkaon.GetBinContent(h2DPIDkaon.FindBin(entry.Kminus_P,entry.Kminus_ETA))
	#wPIDpion1 = h2DPIDpion.GetBinContent(h2DPIDpion.FindBin(entry.Piplus_P,entry.Piplus_ETA))
	#wPIDpion2 = h2DPIDpion.GetBinContent(h2DPIDpion.FindBin(entry.Piminus_P,entry.Piminus_ETA))

	#return wPIDkaon1*wPIDkaon2*wPIDpion1*wPIDpion2
	return 1.;

m1_name_MC = "B_s0_DTF_KST1_M"
m2_name_MC = "B_s0_DTF_KST2_M"
cos1_name_MC = "B_s0_DTF_KST1_COSTHETA"
cos2_name_MC = "B_s0_DTF_KST2_COSTHETA"
phi_name_MC = "B_s0_DTF_B_s0_PHI_TRY4"
t_name_MC = "B_s0_DTF_TAU"

mKp1_MC = ROOT.RooRealVar(m1_name_MC,"M(K^{+}#pi^{-}) ", 750., mHlimit,"MeV/c^{2}")
mKp2_MC = ROOT.RooRealVar(m2_name_MC,"M(K^{-}#pi^{+}) ", 750., mHlimit,"MeV/c^{2}")
mKp1_narrow_MC = ROOT.RooRealVar(m1_name_MC,"M(K^{+}#pi^{-}) ",900.-150.,900.+150.,"MeV/c^{2}")
mKp2_narrow_MC = ROOT.RooRealVar(m2_name_MC,"M(K^{-}#pi^{+}) ",900.-150.,900.+150.,"MeV/c^{2}")
cos1_MC = ROOT.RooRealVar(cos1_name_MC,"cos(#theta_{1})", -1., 1.,"")
cos2_MC = ROOT.RooRealVar(cos2_name_MC,"cos(#theta_{2})", -1., 1.,"")
phi_MC = ROOT.RooRealVar(phi_name_MC,"#varphi",0,2.*pi,"rad")
t_MC = ROOT.RooRealVar(t_name_MC,"t_{true}",0.,12.,"ps")
MCweight0 = ROOT.RooRealVar("MCweight0","MCweight0",1.)

MCdata_2011_L0TIS_wide = ROOT.RooDataSet("MCdata_2011_L0TIS_wide","MCdata_2011_L0TIS_wide",ROOT.RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
MCdata_2012_L0TIS_wide = ROOT.RooDataSet("MCdata_2012_L0TIS_wide","MCdata_2012_L0TIS_wide",ROOT.RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
MCdata_2011_L0noTIS_wide = ROOT.RooDataSet("MCdata_2011_L0noTIS_wide","MCdata_2011_L0noTIS_wide",ROOT.RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
MCdata_2012_L0noTIS_wide = ROOT.RooDataSet("MCdata_2012_L0noTIS_wide","MCdata_2012_L0noTIS_wide",ROOT.RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
MCdata_2011_L0TIS_narrow = ROOT.RooDataSet("MCdata_2011_L0TIS_narrow","MCdata_2011_L0TIS_narrow",ROOT.RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
MCdata_2012_L0TIS_narrow = ROOT.RooDataSet("MCdata_2012_L0TIS_narrow","MCdata_2012_L0TIS_narrow",ROOT.RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
MCdata_2011_L0noTIS_narrow = ROOT.RooDataSet("MCdata_2011_L0noTIS_narrow","MCdata_2011_L0noTIS_narrow",ROOT.RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
MCdata_2012_L0noTIS_narrow = ROOT.RooDataSet("MCdata_2012_L0noTIS_narrow","MCdata_2012_L0noTIS_narrow",ROOT.RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))

def LoadDataNW(NTUPLE_PATH, data_file, data_tree, datatype, wide_window):

	# Information.
	print '\nLoading MC data file ' + data_file + ', used to compute the NWs.'
	if datatype == 0: print 'MC sample: PhSp.'
	elif datatype == 1: print 'MC sample: VV.'
	else: print 'MC sample: PhSp + VV.'

	br_list = ["itype","B_s0_L0Global_TIS","B_s0_L0HadronDecision_TOS",m1_name_MC,m2_name_MC,cos1_name_MC,cos2_name_MC,phi_name_MC,t_name_MC,"B_s0_TRUEID","Kplus_TRUEID","Piminus_TRUEID","Kminus_TRUEID","Piplus_TRUEID"]

	opt_genmodel = ROOT.RooRealVar("opt_genmodel","opt_genmodel",0)
	opt_genvars = ROOT.RooRealVar("opt_genvars","opt_genvars",1)
	year_MC = ROOT.RooRealVar("year_MC","year_MC",1)
	wide_window_MC = ROOT.RooRealVar("wide_window_MC","wide_window_MC",1)
	wide_window_MC.setVal(wide_window)

	# Input data.
	file_in = ROOT.TFile(NTUPLE_PATH + data_file)
	tree_full = file_in.Get(data_tree)
	tree_full.SetBranchStatus("*",0)
	for br in br_list: tree_full.SetBranchStatus(br,1)
	file_out = ROOT.TFile(NTUPLE_PATH + "trash.root","RECREATE")

	if wide_window:
		tree_2011_L0TIS_wide = tree_full.CopyTree(m1_name_MC+"<="+str(mHlimit)+" && "+m2_name_MC+"<="+str(mHlimit)+" && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,0,datatype))
		tree_2012_L0TIS_wide = tree_full.CopyTree(m1_name_MC+"<="+str(mHlimit)+" && "+m2_name_MC+"<="+str(mHlimit)+" && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,0,datatype))
		tree_2011_L0noTIS_wide = tree_full.CopyTree(m1_name_MC+"<="+str(mHlimit)+" && "+m2_name_MC+"<="+str(mHlimit)+" && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,1,datatype))
		tree_2012_L0noTIS_wide = tree_full.CopyTree(m1_name_MC+"<="+str(mHlimit)+" && "+m2_name_MC+"<="+str(mHlimit)+" && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,1,datatype))
		invN_2011_L0TIS_wide = 1.#/tree_2011_L0TIS_wide.GetEntries()
		invN_2012_L0TIS_wide = 1.#/tree_2012_L0TIS_wide.GetEntries()
		invN_2011_L0noTIS_wide = 1.#/tree_2011_L0noTIS_wide.GetEntries()
		invN_2012_L0noTIS_wide = 1.#/tree_2012_L0noTIS_wide.GetEntries()

	else:
		tree_2011_L0TIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,0,datatype))
		tree_2012_L0TIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,0,datatype))
		tree_2011_L0noTIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(0,1,datatype))
		tree_2012_L0noTIS_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_MC+">=0. && "+t_name_MC+"<=12. && "+MCsetcut(1,1,datatype))
		invN_2011_L0TIS_narrow = 1.#/tree_2011_L0TIS_narrow.GetEntries()
		invN_2012_L0TIS_narrow = 1.#/tree_2012_L0TIS_narrow.GetEntries()
		invN_2011_L0noTIS_narrow = 1.#/tree_2011_L0noTIS_narrow.GetEntries()
		invN_2012_L0noTIS_narrow = 1.#/tree_2012_L0noTIS_narrow.GetEntries()

	PDF_gen = ROOT.MCGenComb("PDF_gen","PDF_gen",opt_genmodel,year_MC,wide_window_MC,mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,opt_genvars)

	def setvarvals(entry):
		mKp1_MC.setVal(eval("entry."+m1_name_MC))
		mKp2_MC.setVal(eval("entry."+m2_name_MC))
		cos1_MC.setVal(eval("entry."+cos1_name_MC))
		cos2_MC.setVal(eval("entry."+cos2_name_MC))
		phi_MC.setVal(eval("entry."+phi_name_MC))

	opt_genmodel.setVal(datatype)

	if wide_window:
		year_MC.setVal(0)
		for i in tree_2011_L0TIS_wide:
			if MCtruth(i):
				setvarvals(i)
				MCweight0.setVal(invN_2011_L0TIS_wide*dataMCcorrweight(i)/PDF_gen.evaluate())
				MCdata_2011_L0TIS_wide.add(ROOT.RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
		year_MC.setVal(1)
		for i in tree_2012_L0TIS_wide:
			if MCtruth(i):
				setvarvals(i)
				MCweight0.setVal(invN_2012_L0TIS_wide*dataMCcorrweight(i)/PDF_gen.evaluate())
				MCdata_2012_L0TIS_wide.add(ROOT.RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
		year_MC.setVal(0)
		for i in tree_2011_L0noTIS_wide:
			if MCtruth(i):
				setvarvals(i)
				MCweight0.setVal(invN_2011_L0noTIS_wide*dataMCcorrweight(i)/PDF_gen.evaluate())
				MCdata_2011_L0noTIS_wide.add(ROOT.RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
		year_MC.setVal(1)
		for i in tree_2012_L0noTIS_wide:
			if MCtruth(i):
				setvarvals(i)
				MCweight0.setVal(invN_2012_L0noTIS_wide*dataMCcorrweight(i)/PDF_gen.evaluate())
				MCdata_2012_L0noTIS_wide.add(ROOT.RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))

	else:
		year_MC.setVal(0)
		for i in tree_2011_L0TIS_narrow:
			if MCtruth(i):
				mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
				mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
				setvarvals(i)
				MCweight0.setVal(invN_2011_L0TIS_narrow*dataMCcorrweight(i)/PDF_gen.evaluate())
				MCdata_2011_L0TIS_narrow.add(ROOT.RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
		year_MC.setVal(1)
		for i in tree_2012_L0TIS_narrow:
			if MCtruth(i):
				mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
				mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
				setvarvals(i)
				MCweight0.setVal(invN_2012_L0TIS_narrow*dataMCcorrweight(i)/PDF_gen.evaluate())
				MCdata_2012_L0TIS_narrow.add(ROOT.RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
		year_MC.setVal(0)
		for i in tree_2011_L0noTIS_narrow:
			if MCtruth(i):
				mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
				mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
				setvarvals(i)
				MCweight0.setVal(invN_2011_L0noTIS_narrow*dataMCcorrweight(i)/PDF_gen.evaluate())
				MCdata_2011_L0noTIS_narrow.add(ROOT.RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))
		year_MC.setVal(1)
		for i in tree_2012_L0noTIS_narrow:
			if MCtruth(i):
				mKp1_narrow_MC.setVal(eval("i."+m1_name_MC))
				mKp2_narrow_MC.setVal(eval("i."+m2_name_MC))
				setvarvals(i)
				MCweight0.setVal(invN_2012_L0noTIS_narrow*dataMCcorrweight(i)/PDF_gen.evaluate())
				MCdata_2012_L0noTIS_narrow.add(ROOT.RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,MCweight0))

	print 'Data loaded.'
	file_out.Close()

def createPDF(Blinding, NOCP, NODIRCP, SAMECP, acc_type, inf_t_res, wide_window, data_file,\
fix_re_amps = 0, fix_dirCP_asyms = 0, fix_im_amps = 0, fix_weak_phases = 0, fix_mixing_params = 0, fix_calib_params = 0,\
pw_alternative_model = 0,f_Kst1410_rel2_Kst892 = 0,delta_Kst1410_rel2_Kst892 = 0,f_Kst1680_rel2_Kst892 = 0,delta_Kst1680_rel2_Kst892 = 0):

	# -----------------------------------------------------------
	# SETUP OF THE PARAMETERS ENTERING THE PDF
	# -----------------------------------------------------------

	# Mass window size.
	wide_window_opt.setVal(wide_window)
	if (wide_window):
		for argument in observables: observables_list.add(argument)
	else:
		for argument in observables_narrowwin: observables_list.add(argument)

	# CP violation options.
	blindCat.setIndex(Blinding)
	if NOCP:
		for argument in dirCP_asyms_noCP:
			dirCP_asyms_list.add(argument)
			dirCP_asyms_unblinded_list.add(argument)
		for argument in weak_phases_noCP:
			weak_phases_list.add(argument)
			weak_phases_unblinded_list.add(argument)
	else:
		if SAMECP:
			for argument in weak_phases_sameCP: weak_phases_list.add(argument)
			for argument in weak_phases_sameCP_unblinded: weak_phases_unblinded_list.add(argument)
			if NODIRCP:
				for argument in dirCP_asyms_noCP:
					dirCP_asyms_list.add(argument)
					dirCP_asyms_unblinded_list.add(argument)
			else:
				if wide_window:
					for argument in dirCP_asyms_sameCP: dirCP_asyms_list.add(argument)
					for argument in dirCP_asyms_sameCP_unblinded: dirCP_asyms_unblinded_list.add(argument)
				else:
					for argument in dirCP_asyms_sameCP_narrowwin: dirCP_asyms_list.add(argument)
					for argument in dirCP_asyms_sameCP_narrowwin_unblinded: dirCP_asyms_unblinded_list.add(argument)
		else:
			if wide_window:
				for argument in weak_phases: weak_phases_list.add(argument)
				for argument in weak_phases_unblinded: weak_phases_unblinded_list.add(argument)
			else:
				for argument in weak_phases_narrowwin: weak_phases_list.add(argument)
				for argument in weak_phases_narrowwin_unblinded: weak_phases_unblinded_list.add(argument)
			if NODIRCP:
				for argument in dirCP_asyms_noCP:
					dirCP_asyms_list.add(argument)
					dirCP_asyms_unblinded_list.add(argument)
			else:
				if wide_window:
					for argument in dirCP_asyms: dirCP_asyms_list.add(argument)
					for argument in dirCP_asyms_unblinded: dirCP_asyms_unblinded_list.add(argument)
				else:
					for argument in dirCP_asyms_narrowwin: dirCP_asyms_list.add(argument)
					for argument in dirCP_asyms_narrowwin_unblinded: dirCP_asyms_unblinded_list.add(argument)

	# Configuration of the model in order to be used for systematic uncertainty studies.
	if pw_alternative_model:
		pw_mass_altmodel.setVal(1)
		f_1410_rel2_892.setVal(f_Kst1410_rel2_Kst892)
		delta_1410_rel2_892.setVal(delta_Kst1410_rel2_Kst892)
		f_1680_rel2_892.setVal(f_Kst1680_rel2_Kst892)
		delta_1680_rel2_892.setVal(delta_Kst1680_rel2_Kst892)

	# Configuration of the rest of the parameters.
	for argument in options: options_list.add(argument)
	for argument in re_amps: re_amps_list.add(argument)
	for argument in im_amps: im_amps_list.add(argument)
	for argument in mixing_params: mixing_params_list.add(argument)
	for argument in calib_params: calib_params_list.add(argument)
	for argument in cond_distr_params: cond_distr_params_list.add(argument)
	for argument in sys_studies: sys_studies_list.add(argument)

	# If narrow window is used: removal of the unnecesary CP conserving parameters.
	if (not wide_window):
		for param in [reA02,reA20,reA120,reA12par,reA12perp,reA210,reA21par,reA21perp,reA220,reA22par,reA22perp,reA22par2,reA22perp2,imA02,imA20,imA120,imA12par,imA12perp,imA210,imA21par,imA21perp,imA220,imA22par,imA22perp,imA22par2,imA22perp2]:
			param.setVal(0)
			param.setConstant(1)

	# Printing out the list with the free physical parameters in the PDF.
	parameters = []
	print "\n#####################################################################"
	print " F R E E   P H Y S I C A L   P A R A M E T E R S"
	print "#####################################################################"
	lenghts = [len(re_amps),len(dirCP_asyms),len(im_amps),len(weak_phases),len(mixing_params),len(calib_params)]
	lists = [re_amps_list,dirCP_asyms_list,im_amps_list,weak_phases_list,mixing_params_list,calib_params_list]
	lists_unblinded = [re_amps_list,dirCP_asyms_unblinded_list,im_amps_list,weak_phases_unblinded_list,mixing_params_list,calib_params_list]
	fixed_list = [fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params]
	names = ["CP averaged wave fractions:\n","Direct CP asymmetries:\n","Strong phases:\n","Weak phases:\n","Bs-Bsbar mixing parameters:\n","Calibration parameters:\n"]
	counter = 1
	DCPcounter = -1
	empty_counter = []
	for i in range(len(lists)): empty_counter.append(0)
	for i in range(len(lists)):
		if fixed_list[i]:
			for k in range(lenghts[i]): lists_unblinded[i].at(k).setConstant(1)
		print "\n----------------------------------"
		print names[i]
		for j in range(lenghts[i]):
			if ((not lists_unblinded[i].at(j).isConstant()) and (type(lists_unblinded[i].at(j)) == type(phis))):
				if (lists[i].at(j).GetName() == "DCP_withBlinding"): DCPcounter += 1
				if ((lists[i].at(j).GetName() != "DCP_withBlinding") or ((lists[i].at(j).GetName() == "DCP_withBlinding") and (DCPcounter == 0))):
					print " Parameter #"+str(counter)+" --> "+lists_unblinded[i].at(j).GetName()
					parameters += [lists_unblinded[i].at(j)]
					counter += 1
					empty_counter[i] += 1
		if empty_counter[i] == 0: print " Parameters FIXED."
	print "\n#####################################################################\n"

	# -----------------------------------------------------------
	# ACCEPTANCE MODEL
	# -----------------------------------------------------------

	acctype.setVal(acc_type)

	# -----------------------------------------------------------
	# TIME RESOLUTION MODEL
	# -----------------------------------------------------------

	inftres.setVal(inf_t_res)

	# -----------------------------------------------------------
	# PDF CONSTRUCTION
	# -----------------------------------------------------------

	model = PDF_with_integrals("model","model",options_list,wide_window,data_file,observables_list,re_amps_list,dirCP_asyms_list,\
im_amps_list,weak_phases_list,mixing_params_list,calib_params_list,sys_studies_list)

	return model, parameters


def createSimPDF(TD_fit, Blinding, NOCP, NODIRCP, SAMECP, acc_type, inf_t_res, wide_window, data_file,\
fix_re_amps = 0, fix_dirCP_asyms = 0, fix_im_amps = 0, fix_weak_phases = 0, fix_mixing_params = 0, fix_calib_params = 0,\
pw_alternative_model = 0,f_Kst1410_rel2_Kst892 = 0,delta_Kst1410_rel2_Kst892 = 0,f_Kst1680_rel2_Kst892 = 0,delta_Kst1680_rel2_Kst892 = 0):

	# -----------------------------------------------------------
	# CONFIGURATION OF THE PDF ACCORDING TO THE TYPE OF FIT
	# -----------------------------------------------------------

	if (not TD_fit):
		alt_fit.setVal(4)
		NOCP = 1
		fix_mixing_params = 1
		fix_calib_params = 1
		imA11perp.setVal(0)
		imA11perp.setConstant(1)
		for obs in [t,terror,decision_SSK,decision_OS,etamistag_SSK,etamistag_OS]: obs.setConstant(1)

	# -----------------------------------------------------------
	# SETUP OF THE PARAMETERS ENTERING THE PDF
	# -----------------------------------------------------------

	# Mass window size.
	wide_window_opt.setVal(wide_window)
	if (wide_window):
		for argument in observables: observables_list.add(argument)
	else:
		for argument in observables_narrowwin: observables_list.add(argument)

	# CP violation options.
	blindCat.setIndex(Blinding)
	if NOCP:
		for argument in dirCP_asyms_noCP:
			dirCP_asyms_list.add(argument)
			dirCP_asyms_unblinded_list.add(argument)
		for argument in weak_phases_noCP:
			weak_phases_list.add(argument)
			weak_phases_unblinded_list.add(argument)
	else:
		if SAMECP:
			for argument in weak_phases_sameCP: weak_phases_list.add(argument)
			for argument in weak_phases_sameCP_unblinded: weak_phases_unblinded_list.add(argument)
			if NODIRCP:
				for argument in dirCP_asyms_noCP:
					dirCP_asyms_list.add(argument)
					dirCP_asyms_unblinded_list.add(argument)
			else:
				if wide_window:
					for argument in dirCP_asyms_sameCP: dirCP_asyms_list.add(argument)
					for argument in dirCP_asyms_sameCP_unblinded: dirCP_asyms_unblinded_list.add(argument)
				else:
					for argument in dirCP_asyms_sameCP_narrowwin: dirCP_asyms_list.add(argument)
					for argument in dirCP_asyms_sameCP_narrowwin_unblinded: dirCP_asyms_unblinded_list.add(argument)
		else:
			if wide_window:
				for argument in weak_phases: weak_phases_list.add(argument)
				for argument in weak_phases_unblinded: weak_phases_unblinded_list.add(argument)
			else:
				for argument in weak_phases_narrowwin: weak_phases_list.add(argument)
				for argument in weak_phases_narrowwin_unblinded: weak_phases_unblinded_list.add(argument)
			if NODIRCP:
				for argument in dirCP_asyms_noCP:
					dirCP_asyms_list.add(argument)
					dirCP_asyms_unblinded_list.add(argument)
			else:
				if wide_window:
					for argument in dirCP_asyms: dirCP_asyms_list.add(argument)
					for argument in dirCP_asyms_unblinded: dirCP_asyms_unblinded_list.add(argument)
				else:
					for argument in dirCP_asyms_narrowwin: dirCP_asyms_list.add(argument)
					for argument in dirCP_asyms_narrowwin_unblinded: dirCP_asyms_unblinded_list.add(argument)

	# Configuration of the model in order to be used for systematic uncertainty studies.
	if pw_alternative_model:
		pw_mass_altmodel.setVal(1)
		f_1410_rel2_892.setVal(f_Kst1410_rel2_Kst892)
		delta_1410_rel2_892.setVal(delta_Kst1410_rel2_Kst892)
		f_1680_rel2_892.setVal(f_Kst1680_rel2_Kst892)
		delta_1680_rel2_892.setVal(delta_Kst1680_rel2_Kst892)

	# Configuration of the rest of the parameters.
	for argument in options_11L0TIS: options_11L0TIS_list.add(argument)
	for argument in options_11L0noTIS: options_11L0noTIS_list.add(argument)
	for argument in options_12L0TIS: options_12L0TIS_list.add(argument)
	for argument in options_12L0noTIS: options_12L0noTIS_list.add(argument)
	for argument in re_amps: re_amps_list.add(argument)
	for argument in im_amps: im_amps_list.add(argument)
	for argument in mixing_params: mixing_params_list.add(argument)
	for argument in calib_params: calib_params_list.add(argument)
	for argument in cond_distr_params: cond_distr_params_list.add(argument)
	for argument in sys_studies: sys_studies_list.add(argument)

	# If narrow window is used: removal of the unnecesary CP conserving parameters.
	if (not wide_window):
		for param in [reA02,reA20,reA120,reA12par,reA12perp,reA210,reA21par,reA21perp,reA220,reA22par,reA22perp,reA22par2,reA22perp2,imA02,imA20,imA120,imA12par,imA12perp,imA210,imA21par,imA21perp,imA220,imA22par,imA22perp,imA22par2,imA22perp2]:
			param.setVal(0)
			param.setConstant(1)

	# Printing out the list with the free physical parameters in the PDF.
	parameters = []
	print "\n#####################################################################"
	print " F R E E   P H Y S I C A L   P A R A M E T E R S"
	print "#####################################################################"
	lenghts = [len(re_amps),len(dirCP_asyms),len(im_amps),len(weak_phases),len(mixing_params),len(calib_params)]
	lists = [re_amps_list,dirCP_asyms_list,im_amps_list,weak_phases_list,mixing_params_list,calib_params_list]
	lists_unblinded = [re_amps_list,dirCP_asyms_unblinded_list,im_amps_list,weak_phases_unblinded_list,mixing_params_list,calib_params_list]
	fixed_list = [fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params]
	names = ["CP averaged wave fractions:\n","Direct CP asymmetries:\n","Strong phases:\n","Weak phases:\n","Bs-Bsbar mixing parameters:\n","Calibration parameters:\n"]
	counter = 1
	DCPcounter = -1
	empty_counter = []
	for i in range(len(lists)): empty_counter.append(0)
	for i in range(len(lists)):
		if fixed_list[i]:
			for k in range(lenghts[i]): lists_unblinded[i].at(k).setConstant(1)
		print "\n----------------------------------"
		print names[i]
		for j in range(lenghts[i]):
			if ((not lists_unblinded[i].at(j).isConstant()) and (type(lists_unblinded[i].at(j)) == type(phis))):
				if (lists[i].at(j).GetName() == "DCP_withBlinding"): DCPcounter += 1
				if ((lists[i].at(j).GetName() != "DCP_withBlinding") or ((lists[i].at(j).GetName() == "DCP_withBlinding") and (DCPcounter == 0))):
					print " Parameter #"+str(counter)+" --> "+lists_unblinded[i].at(j).GetName()
					parameters += [lists_unblinded[i].at(j)]
					counter += 1
					empty_counter[i] += 1
		if empty_counter[i] == 0: print " Parameters FIXED."
	print "\n#####################################################################\n"

	# -----------------------------------------------------------
	# ACCEPTANCE MODEL
	# -----------------------------------------------------------

	acctype.setVal(acc_type)

	# -----------------------------------------------------------
	# TIME RESOLUTION MODEL
	# -----------------------------------------------------------

	inftres.setVal(inf_t_res)

	# -----------------------------------------------------------
	# PDF CONSTRUCTION
	# -----------------------------------------------------------

	model_11L0TIS,model_11L0noTIS,model_12L0TIS,model_12L0noTIS = PDFs_with_integrals("model","model",options_11L0TIS_list,options_11L0noTIS_list,options_12L0TIS_list,options_12L0noTIS_list,\
wide_window,data_file,observables_list,re_amps_list,dirCP_asyms_list,im_amps_list,weak_phases_list,mixing_params_list,calib_params_list,sys_studies_list)

	model_full = ROOT.RooSimultaneous("model_full","model_full",yeartrigcat)
	model_full.addPdf(model_11L0TIS,"2011_L0TIS")
	model_full.addPdf(model_11L0noTIS,"2011_L0noTIS")
	model_full.addPdf(model_12L0TIS,"2012_L0TIS")
	model_full.addPdf(model_12L0noTIS,"2012_L0noTIS")

	return [model_full,model_11L0TIS,model_11L0noTIS,model_12L0TIS,model_12L0noTIS], parameters

def DoFit(model_,data_,wide_window,TD_fit,num_CPU,minos_opt,strategy_option,fix_mixing,fix_calib):

   # Function to perform the fit.

   if TD_fit:

      if fix_mixing:
         if fix_calib: res = model_.fitTo(data_,ROOT.RooFit.NumCPU(num_CPU),ROOT.RooFit.Minos(minos_opt),ROOT.RooFit.Strategy(strategy_option),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.SumW2Error(kFALSE),ROOT.RooFit.Save(kTRUE),ROOT.RooFit.PrintLevel(0))
         else:
            ctrtargset = ROOT.RooArgSet(ctrt_p0metac_SSK_p1_SSK,ctrt_p0metac_OS_p1_OS,ctrt_Dp0half_SSK,ctrt_Dp1half_SSK,ctrt_Dp0half_OS,ctrt_Dp1half_OS)
            if wide_window:
               ctrtargset.add(ctrt_tres_p0_tres_p1_2011_wide)
               ctrtargset.add(ctrt_tres_p0_tres_p1_2012_wide)
            else:
               ctrtargset.add(ctrt_tres_p0_tres_p1_2011_narrow)
               ctrtargset.add(ctrt_tres_p0_tres_p1_2012_narrow)
            res = model_.fitTo(data_,ROOT.RooFit.NumCPU(num_CPU),ROOT.RooFit.Minos(minos_opt),ROOT.RooFit.Strategy(strategy_option),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.SumW2Error(kFALSE),ROOT.RooFit.Save(kTRUE),ROOT.RooFit.ExternalConstraints(ctrtargset),ROOT.RooFit.PrintLevel(0))

      else:
         if fix_calib: res = model_.fitTo(data_,ROOT.RooFit.NumCPU(num_CPU),ROOT.RooFit.Minos(minos_opt),ROOT.RooFit.Strategy(strategy_option),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.SumW2Error(kFALSE),ROOT.RooFit.Save(kTRUE),ROOT.RooFit.ExternalConstraints(ROOT.RooArgSet(ctrt_gamma_Bs_delta_gamma_Bs)),ROOT.RooFit.PrintLevel(0))
         else:
            ctrtargset = ROOT.RooArgSet(ctrt_gamma_Bs_delta_gamma_Bs,ctrt_p0metac_SSK_p1_SSK,ctrt_p0metac_OS_p1_OS,ctrt_Dp0half_SSK,ctrt_Dp1half_SSK,ctrt_Dp0half_OS,ctrt_Dp1half_OS)
            if wide_window:
               ctrtargset.add(ctrt_tres_p0_tres_p1_2011_wide)
               ctrtargset.add(ctrt_tres_p0_tres_p1_2012_wide)
            else:
               ctrtargset.add(ctrt_tres_p0_tres_p1_2011_narrow)
               ctrtargset.add(ctrt_tres_p0_tres_p1_2012_narrow)
            res = model_.fitTo(data_,ROOT.RooFit.NumCPU(num_CPU),ROOT.RooFit.Minos(minos_opt),ROOT.RooFit.Strategy(strategy_option),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.SumW2Error(kFALSE),ROOT.RooFit.Save(kTRUE),ROOT.RooFit.ExternalConstraints(ctrtargset),ROOT.RooFit.PrintLevel(0))

   else: res = model_.fitTo(data_,ROOT.RooFit.NumCPU(num_CPU),ROOT.RooFit.Minos(minos_opt),ROOT.RooFit.Strategy(strategy_option),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.SumW2Error(kFALSE),ROOT.RooFit.Save(kTRUE),ROOT.RooFit.PrintLevel(0))

   return res


def boolj1j2h(j1,j2,h):

	if ((j1 == 0) and (j2 == 0) and (h == 0)): return 1
	if ((j1 == 0) and (j2 == 1) and (h == 0)): return 1
	if ((j1 == 0) and (j2 == 2) and (h == 0)): return 1
	if ((j1 == 1) and (j2 == 0) and (h == 0)): return 1
	if ((j1 == 1) and (j2 == 1) and (h == 0)): return 1
	if ((j1 == 1) and (j2 == 1) and (h == 1)): return 1
	if ((j1 == 1) and (j2 == 1) and (h == 2)): return 1
	if ((j1 == 1) and (j2 == 2) and (h == 0)): return 1
	if ((j1 == 1) and (j2 == 2) and (h == 1)): return 1
	if ((j1 == 1) and (j2 == 2) and (h == 2)): return 1
	if ((j1 == 2) and (j2 == 0) and (h == 0)): return 1
	if ((j1 == 2) and (j2 == 1) and (h == 0)): return 1
	if ((j1 == 2) and (j2 == 1) and (h == 1)): return 1
	if ((j1 == 2) and (j2 == 1) and (h == 2)): return 1
	if ((j1 == 2) and (j2 == 2) and (h == 0)): return 1
	if ((j1 == 2) and (j2 == 2) and (h == 1)): return 1
	if ((j1 == 2) and (j2 == 2) and (h == 2)): return 1
	if ((j1 == 2) and (j2 == 2) and (h == 3)): return 1
	if ((j1 == 2) and (j2 == 2) and (h == 4)): return 1
	return 0


def boolj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp): 
	 return boolj1j2h(j1,j2,h)*boolj1j2h(j1p,j2p,hp)


indexdictextred = {}
indexdictredext = {}
index = 0
for j1 in range(3):
	for j2 in range(3):
		for h in range(5):
			for j1p in range(3):
				for j2p in range(3):
					for hp in range(5):
						for part in range(2):
							if ((boolj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp) == 1) and ((j1p+3*j2p+9*hp) <= (j1+3*j2+9*h))):
								indexdictextred[str(j1)+str(j2)+str(h)+str(j1p)+str(j2p)+str(hp)+str(part)] = index
								indexdictredext[index] = str(j1)+str(j2)+str(h)+str(j1p)+str(j2p)+str(hp)+str(part)
								index += 1
def redindex(j1,j2,h,j1p,j2p,hp,part):
	return indexdictextred[str(j1)+str(j2)+str(h)+str(j1p)+str(j2p)+str(hp)+str(part)]

def extindex(i):
	stringlist = list(indexdictredext[i])
	intlist = []
	for s in stringlist: intlist.append(eval(s))
	return intlist

for blindpar in ['DCP','phis','DCP_SS','DCP_SV','DCP_VS','DCP_ST','DCP_TS','DCP_VT','DCP_TV','DCP_TT','dphi_SS','dphi_SV','dphi_VS','dphi_ST','dphi_TS','dphi_VT','dphi_TV','dphi_TT']: blinding_strings[blindpar] = np.random.uniform(-blinding_scale,blinding_scale)

def converted_parameter(param,blinding):
   from ModelBricks import Parameter, Free
   paramname = param.GetName()
   if ('phi' in paramname or 'DCP' in paramname) and blinding:
      blstring = blinding_strings[paramname]
      return eval(('Parameter("'+paramname+'_cu",'+str(param.getVal())+'+'+str(blstring)+', limits = ('+str(param.getMin())+'+'+str(blstring)+','+str(param.getMax())+'+'+str(blstring)+'), constant = False, dtype = np.float64)').replace('+-','-'))
   return eval('Parameter("'+paramname+'_cu",'+str(param.getVal())+', limits = ('+str(param.getMin())+','+str(param.getMax())+'), constant = False, dtype = np.float64)')

def create_param_list(arglistname,numparams = 0):
   arglist = eval(arglistname)
   numparlimit = len(arglist)
   if numparams != 0: numparlimit = numparams
   exec('x = np.ones('+str(numparlimit)+').astype(np.float64)')
   for iarg in range(numparlimit): exec('x['+str(iarg)+'] = '+str(arglist.at(iarg).getVal()))
   return x

def param_list_updates(arglistname,paramnames,args_ = 0,N_ = {},blinding = 0):
   arglist = eval(arglistname)
   updates = []
   for iarg in range(len(arglist)):
      if arglist.at(iarg).isConstant() == 0:
         argname = arglist.at(iarg).GetName()
         isCPV = 0
         if '_withBlinding' in argname:
            argname = argname.replace('_withBlinding','')
            isCPV = 1
         if argname in paramnames:
            if blinding and isCPV: updates.append([iarg,eval(('np.float64(args_[N_["'+argname+'_cu"]])-'+str(blinding_strings[argname])).replace('--','+'))])
            else: updates.append([iarg,eval('np.float64(args_[N_["'+argname+'_cu"]])')])
   return updates

def param_list_updates_check(arglistname,paramnames,blinding = 0):
   arglist = eval(arglistname)
   updates = []
   for iarg in range(len(arglist)):
      if arglist.at(iarg).isConstant() == 0:
         argname = arglist.at(iarg).GetName()
         isCPV = 0
         if '_withBlinding' in argname:
            argname = argname.replace('_withBlinding','')
            isCPV = 1
         if argname in paramnames:
            if blinding and isCPV: updates.append([iarg,eval((argname+'.getVal()-'+str(blinding_strings[argname])).replace('--','+'))])
            else: updates.append([iarg,eval(argname+'.getVal()')])
   return updates

def create_data_arrays(data_list):
   int_var_name_list = ['decision_SSK','decision_OS']
   double_var_name_list = ['etamistag_SSK','etamistag_OS','mKp1','mKp2','cos1','cos2','phi','t','terror','weight_fit']
   listofarrays = []
   for i in range(4):
      data_sample = data_list[2+i]
      sample_size = data_sample.numEntries()
      listofarrays.append(eval('np.ones(('+str(sample_size)+',12)).astype(np.float64)'))
      for ev in range(sample_size):
         for ivar in range(2): listofarrays[i][ev][ivar] = eval(str(data_sample.get(ev).getCatIndex(eval(int_var_name_list[ivar]+'.GetName()'))))
         for ivar in range(10): listofarrays[i][ev][2+ivar] = eval(str(data_sample.get(ev).getRealValue(eval(double_var_name_list[ivar]+'.GetName()'))))
   return listofarrays

def create_MCdata_arrays(data_list):
   double_var_name_list = ["B_s0_DTF_KST1_M","B_s0_DTF_KST2_M","B_s0_DTF_KST1_COSTHETA","B_s0_DTF_KST2_COSTHETA","B_s0_DTF_B_s0_PHI_TRY4","MCweight0"]
   listofarrays = []
   for i in range(4):
      data_sample = data_list[i]
      sample_size = data_sample.numEntries()
      listofarrays.append(eval('np.ones('+str(sample_size)+'*6).astype(np.float64)'))
      for ev in range(sample_size):
         for ivar in range(6): listofarrays[i][6*ev+ivar] = data_sample.get(ev).getRealValue(double_var_name_list[ivar])
   return listofarrays

polar_fractions_dict = {'f_10': '(upar["reA10"]*upar["reA10"] + upar["imA10"]*upar["imA10"])/(upar["reA00"]*upar["reA00"] + upar["imA00"]*upar["imA00"] + upar["reA01"]*upar["reA01"] + upar["imA01"]*upar["imA01"] + upar["reA10"]*upar["reA10"] + upar["imA10"]*upar["imA10"] + upar["reA02"]*upar["reA02"] + upar["imA02"]*upar["imA02"] + upar["reA20"]*upar["reA20"] + upar["imA20"]*upar["imA20"] + upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"] + upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"] + upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"] + upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_par2_22': '(upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"])/(upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_12': '(upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"])/(upar["reA00"]*upar["reA00"] + upar["imA00"]*upar["imA00"] + upar["reA01"]*upar["reA01"] + upar["imA01"]*upar["imA01"] + upar["reA10"]*upar["reA10"] + upar["imA10"]*upar["imA10"] + upar["reA02"]*upar["reA02"] + upar["imA02"]*upar["imA02"] + upar["reA20"]*upar["reA20"] + upar["imA20"]*upar["imA20"] + upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"] + upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"] + upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"] + upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_L_12': '(upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"])/(upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"])', 'f_L_11': '(upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"])/(upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"])', 'f_11': '(upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"])/(upar["reA00"]*upar["reA00"] + upar["imA00"]*upar["imA00"] + upar["reA01"]*upar["reA01"] + upar["imA01"]*upar["imA01"] + upar["reA10"]*upar["reA10"] + upar["imA10"]*upar["imA10"] + upar["reA02"]*upar["reA02"] + upar["imA02"]*upar["imA02"] + upar["reA20"]*upar["reA20"] + upar["imA20"]*upar["imA20"] + upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"] + upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"] + upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"] + upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_perp_12': '(upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"])/(upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"])', 'f_perp_11': '(upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"])/(upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"])', 'f_par_12': '(upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"])/(upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"])', 'f_par_11': '(upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"])/(upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"])', 'f_perp2_22': '(upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])/(upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_01': '(upar["reA01"]*upar["reA01"] + upar["imA01"]*upar["imA01"])/(upar["reA00"]*upar["reA00"] + upar["imA00"]*upar["imA00"] + upar["reA01"]*upar["reA01"] + upar["imA01"]*upar["imA01"] + upar["reA10"]*upar["reA10"] + upar["imA10"]*upar["imA10"] + upar["reA02"]*upar["reA02"] + upar["imA02"]*upar["imA02"] + upar["reA20"]*upar["reA20"] + upar["imA20"]*upar["imA20"] + upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"] + upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"] + upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"] + upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_00': '(upar["reA00"]*upar["reA00"] + upar["imA00"]*upar["imA00"])/(upar["reA00"]*upar["reA00"] + upar["imA00"]*upar["imA00"] + upar["reA01"]*upar["reA01"] + upar["imA01"]*upar["imA01"] + upar["reA10"]*upar["reA10"] + upar["imA10"]*upar["imA10"] + upar["reA02"]*upar["reA02"] + upar["imA02"]*upar["imA02"] + upar["reA20"]*upar["reA20"] + upar["imA20"]*upar["imA20"] + upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"] + upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"] + upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"] + upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_02': '(upar["reA02"]*upar["reA02"] + upar["imA02"]*upar["imA02"])/(upar["reA00"]*upar["reA00"] + upar["imA00"]*upar["imA00"] + upar["reA01"]*upar["reA01"] + upar["imA01"]*upar["imA01"] + upar["reA10"]*upar["reA10"] + upar["imA10"]*upar["imA10"] + upar["reA02"]*upar["reA02"] + upar["imA02"]*upar["imA02"] + upar["reA20"]*upar["reA20"] + upar["imA20"]*upar["imA20"] + upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"] + upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"] + upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"] + upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_perp_22': '(upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"])/(upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_perp_21': '(upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"])/(upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"])', 'f_22': '(upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])/(upar["reA00"]*upar["reA00"] + upar["imA00"]*upar["imA00"] + upar["reA01"]*upar["reA01"] + upar["imA01"]*upar["imA01"] + upar["reA10"]*upar["reA10"] + upar["imA10"]*upar["imA10"] + upar["reA02"]*upar["reA02"] + upar["imA02"]*upar["imA02"] + upar["reA20"]*upar["reA20"] + upar["imA20"]*upar["imA20"] + upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"] + upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"] + upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"] + upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_21': '(upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"])/(upar["reA00"]*upar["reA00"] + upar["imA00"]*upar["imA00"] + upar["reA01"]*upar["reA01"] + upar["imA01"]*upar["imA01"] + upar["reA10"]*upar["reA10"] + upar["imA10"]*upar["imA10"] + upar["reA02"]*upar["reA02"] + upar["imA02"]*upar["imA02"] + upar["reA20"]*upar["reA20"] + upar["imA20"]*upar["imA20"] + upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"] + upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"] + upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"] + upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_20': '(upar["reA20"]*upar["reA20"] + upar["imA20"]*upar["imA20"])/(upar["reA00"]*upar["reA00"] + upar["imA00"]*upar["imA00"] + upar["reA01"]*upar["reA01"] + upar["imA01"]*upar["imA01"] + upar["reA10"]*upar["reA10"] + upar["imA10"]*upar["imA10"] + upar["reA02"]*upar["reA02"] + upar["imA02"]*upar["imA02"] + upar["reA20"]*upar["reA20"] + upar["imA20"]*upar["imA20"] + upar["reA110"]*upar["reA110"] + upar["imA110"]*upar["imA110"] + upar["reA11par"]*upar["reA11par"] + upar["imA11par"]*upar["imA11par"] + upar["reA11perp"]*upar["reA11perp"] + upar["imA11perp"]*upar["imA11perp"] + upar["reA120"]*upar["reA120"] + upar["imA120"]*upar["imA120"] + upar["reA12par"]*upar["reA12par"] + upar["imA12par"]*upar["imA12par"] + upar["reA12perp"]*upar["reA12perp"] + upar["imA12perp"]*upar["imA12perp"] + upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"] + upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_L_22': '(upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"])/(upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_par_22': '(upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"])/(upar["reA220"]*upar["reA220"] + upar["imA220"]*upar["imA220"] + upar["reA22par"]*upar["reA22par"] + upar["imA22par"]*upar["imA22par"] + upar["reA22perp"]*upar["reA22perp"] + upar["imA22perp"]*upar["imA22perp"] + upar["reA22par2"]*upar["reA22par2"] + upar["imA22par2"]*upar["imA22par2"] + upar["reA22perp2"]*upar["reA22perp2"] + upar["imA22perp2"]*upar["imA22perp2"])', 'f_par_21': '(upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"])/(upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"])', 'f_L_21': '(upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"])/(upar["reA210"]*upar["reA210"] + upar["imA210"]*upar["imA210"] + upar["reA21par"]*upar["reA21par"] + upar["imA21par"]*upar["imA21par"] + upar["reA21perp"]*upar["reA21perp"] + upar["imA21perp"]*upar["imA21perp"])'}

polar_phases_dict = {'delta_21perp': 'umath.atan2(upar["imA21perp"],upar["reA21perp"])', 'delta_220': 'umath.atan2(upar["imA220"],upar["reA220"])', 'delta_02': 'umath.atan2(upar["imA02"],upar["reA02"])', 'delta_22perp': 'umath.atan2(upar["imA22perp"],upar["reA22perp"])', 'delta_10': 'umath.atan2(upar["imA10"],upar["reA10"])', 'delta_210': 'umath.atan2(upar["imA210"],upar["reA210"])', 'delta_22par2': 'umath.atan2(upar["imA22par2"],upar["reA22par2"])', 'delta_12par': 'umath.atan2(upar["imA12par"],upar["reA12par"])', 'delta_11perp': 'umath.atan2(upar["imA11perp"],upar["reA11perp"])', 'delta_21par': 'umath.atan2(upar["imA21par"],upar["reA21par"])', 'delta_20': 'umath.atan2(upar["imA20"],upar["reA20"])', 'delta_22perp2': 'umath.atan2(upar["imA22perp2"],upar["reA22perp2"])', 'delta_12perp': 'umath.atan2(upar["imA12perp"],upar["reA12perp"])', 'delta_01': 'umath.atan2(upar["imA01"],upar["reA01"])', 'delta_00': 'umath.atan2(upar["imA00"],upar["reA00"])', 'delta_11par': 'umath.atan2(upar["imA11par"],upar["reA11par"])', 'delta_120': 'umath.atan2(upar["imA120"],upar["reA120"])', 'delta_22par': 'umath.atan2(upar["imA22par"],upar["reA22par"])'}

init_polar_fractions_dict = {'f_10': '(reA10.getVal()*reA10.getVal() + imA10.getVal()*imA10.getVal())/(reA00.getVal()*reA00.getVal() + imA00.getVal()*imA00.getVal() + reA01.getVal()*reA01.getVal() + imA01.getVal()*imA01.getVal() + reA10.getVal()*reA10.getVal() + imA10.getVal()*imA10.getVal() + reA02.getVal()*reA02.getVal() + imA02.getVal()*imA02.getVal() + reA20.getVal()*reA20.getVal() + imA20.getVal()*imA20.getVal() + reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal() + reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal() + reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal() + reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_par2_22': '(reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal())/(reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_12': '(reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal())/(reA00.getVal()*reA00.getVal() + imA00.getVal()*imA00.getVal() + reA01.getVal()*reA01.getVal() + imA01.getVal()*imA01.getVal() + reA10.getVal()*reA10.getVal() + imA10.getVal()*imA10.getVal() + reA02.getVal()*reA02.getVal() + imA02.getVal()*imA02.getVal() + reA20.getVal()*reA20.getVal() + imA20.getVal()*imA20.getVal() + reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal() + reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal() + reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal() + reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_L_12': '(reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal())/(reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal())', 'f_L_11': '(reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal())/(reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal())', 'f_11': '(reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal())/(reA00.getVal()*reA00.getVal() + imA00.getVal()*imA00.getVal() + reA01.getVal()*reA01.getVal() + imA01.getVal()*imA01.getVal() + reA10.getVal()*reA10.getVal() + imA10.getVal()*imA10.getVal() + reA02.getVal()*reA02.getVal() + imA02.getVal()*imA02.getVal() + reA20.getVal()*reA20.getVal() + imA20.getVal()*imA20.getVal() + reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal() + reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal() + reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal() + reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_perp_12': '(reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal())/(reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal())', 'f_perp_11': '(reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal())/(reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal())', 'f_par_12': '(reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal())/(reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal())', 'f_par_11': '(reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal())/(reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal())', 'f_perp2_22': '(reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())/(reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_01': '(reA01.getVal()*reA01.getVal() + imA01.getVal()*imA01.getVal())/(reA00.getVal()*reA00.getVal() + imA00.getVal()*imA00.getVal() + reA01.getVal()*reA01.getVal() + imA01.getVal()*imA01.getVal() + reA10.getVal()*reA10.getVal() + imA10.getVal()*imA10.getVal() + reA02.getVal()*reA02.getVal() + imA02.getVal()*imA02.getVal() + reA20.getVal()*reA20.getVal() + imA20.getVal()*imA20.getVal() + reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal() + reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal() + reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal() + reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_00': '(reA00.getVal()*reA00.getVal() + imA00.getVal()*imA00.getVal())/(reA00.getVal()*reA00.getVal() + imA00.getVal()*imA00.getVal() + reA01.getVal()*reA01.getVal() + imA01.getVal()*imA01.getVal() + reA10.getVal()*reA10.getVal() + imA10.getVal()*imA10.getVal() + reA02.getVal()*reA02.getVal() + imA02.getVal()*imA02.getVal() + reA20.getVal()*reA20.getVal() + imA20.getVal()*imA20.getVal() + reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal() + reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal() + reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal() + reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_02': '(reA02.getVal()*reA02.getVal() + imA02.getVal()*imA02.getVal())/(reA00.getVal()*reA00.getVal() + imA00.getVal()*imA00.getVal() + reA01.getVal()*reA01.getVal() + imA01.getVal()*imA01.getVal() + reA10.getVal()*reA10.getVal() + imA10.getVal()*imA10.getVal() + reA02.getVal()*reA02.getVal() + imA02.getVal()*imA02.getVal() + reA20.getVal()*reA20.getVal() + imA20.getVal()*imA20.getVal() + reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal() + reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal() + reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal() + reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_perp_22': '(reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal())/(reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_perp_21': '(reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal())/(reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal())', 'f_22': '(reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())/(reA00.getVal()*reA00.getVal() + imA00.getVal()*imA00.getVal() + reA01.getVal()*reA01.getVal() + imA01.getVal()*imA01.getVal() + reA10.getVal()*reA10.getVal() + imA10.getVal()*imA10.getVal() + reA02.getVal()*reA02.getVal() + imA02.getVal()*imA02.getVal() + reA20.getVal()*reA20.getVal() + imA20.getVal()*imA20.getVal() + reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal() + reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal() + reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal() + reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_21': '(reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal())/(reA00.getVal()*reA00.getVal() + imA00.getVal()*imA00.getVal() + reA01.getVal()*reA01.getVal() + imA01.getVal()*imA01.getVal() + reA10.getVal()*reA10.getVal() + imA10.getVal()*imA10.getVal() + reA02.getVal()*reA02.getVal() + imA02.getVal()*imA02.getVal() + reA20.getVal()*reA20.getVal() + imA20.getVal()*imA20.getVal() + reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal() + reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal() + reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal() + reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_20': '(reA20.getVal()*reA20.getVal() + imA20.getVal()*imA20.getVal())/(reA00.getVal()*reA00.getVal() + imA00.getVal()*imA00.getVal() + reA01.getVal()*reA01.getVal() + imA01.getVal()*imA01.getVal() + reA10.getVal()*reA10.getVal() + imA10.getVal()*imA10.getVal() + reA02.getVal()*reA02.getVal() + imA02.getVal()*imA02.getVal() + reA20.getVal()*reA20.getVal() + imA20.getVal()*imA20.getVal() + reA110.getVal()*reA110.getVal() + imA110.getVal()*imA110.getVal() + reA11par.getVal()*reA11par.getVal() + imA11par.getVal()*imA11par.getVal() + reA11perp.getVal()*reA11perp.getVal() + imA11perp.getVal()*imA11perp.getVal() + reA120.getVal()*reA120.getVal() + imA120.getVal()*imA120.getVal() + reA12par.getVal()*reA12par.getVal() + imA12par.getVal()*imA12par.getVal() + reA12perp.getVal()*reA12perp.getVal() + imA12perp.getVal()*imA12perp.getVal() + reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal() + reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_L_22': '(reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal())/(reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_par_22': '(reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal())/(reA220.getVal()*reA220.getVal() + imA220.getVal()*imA220.getVal() + reA22par.getVal()*reA22par.getVal() + imA22par.getVal()*imA22par.getVal() + reA22perp.getVal()*reA22perp.getVal() + imA22perp.getVal()*imA22perp.getVal() + reA22par2.getVal()*reA22par2.getVal() + imA22par2.getVal()*imA22par2.getVal() + reA22perp2.getVal()*reA22perp2.getVal() + imA22perp2.getVal()*imA22perp2.getVal())', 'f_par_21': '(reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal())/(reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal())', 'f_L_21': '(reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal())/(reA210.getVal()*reA210.getVal() + imA210.getVal()*imA210.getVal() + reA21par.getVal()*reA21par.getVal() + imA21par.getVal()*imA21par.getVal() + reA21perp.getVal()*reA21perp.getVal() + imA21perp.getVal()*imA21perp.getVal())'}

init_polar_phases_dict = {'delta_21perp': 'np.arctan2(imA21perp.getVal(),reA21perp.getVal())', 'delta_220': 'np.arctan2(imA220.getVal(),reA220.getVal())', 'delta_02': 'np.arctan2(imA02.getVal(),reA02.getVal())', 'delta_22perp': 'np.arctan2(imA22perp.getVal(),reA22perp.getVal())', 'delta_10': 'np.arctan2(imA10.getVal(),reA10.getVal())', 'delta_210': 'np.arctan2(imA210.getVal(),reA210.getVal())', 'delta_22par2': 'np.arctan2(imA22par2.getVal(),reA22par2.getVal())', 'delta_12par': 'np.arctan2(imA12par.getVal(),reA12par.getVal())', 'delta_11perp': 'np.arctan2(imA11perp.getVal(),reA11perp.getVal())', 'delta_21par': 'np.arctan2(imA21par.getVal(),reA21par.getVal())', 'delta_20': 'np.arctan2(imA20.getVal(),reA20.getVal())', 'delta_22perp2': 'np.arctan2(imA22perp2.getVal(),reA22perp2.getVal())', 'delta_12perp': 'np.arctan2(imA12perp.getVal(),reA12perp.getVal())', 'delta_01': 'np.arctan2(imA01.getVal(),reA01.getVal())', 'delta_00': 'np.arctan2(imA00.getVal(),reA00.getVal())', 'delta_11par': 'np.arctan2(imA11par.getVal(),reA11par.getVal())', 'delta_120': 'np.arctan2(imA120.getVal(),reA120.getVal())', 'delta_22par': 'np.arctan2(imA22par.getVal(),reA22par.getVal())'}

polar_params_dict = polar_fractions_dict.copy()
polar_params_dict.update(polar_phases_dict)

init_polar_params_dict = init_polar_fractions_dict.copy()
init_polar_params_dict.update(init_polar_phases_dict)

polar_namepairs_dict = {'f_L_11': 'reA11par', 'delta_22perp': 'reA220', 'delta_210': 'reA210', 'f_par2_22': 'reA220', 'f_12': 'reA120', 'f_L_12': 'reA120', 'f_10': 'reA10', 'f_11': 'reA11par', 'delta_21par': 'reA210', 'f_perp_12': 'reA120', 'f_perp_11': 'reA11par', 'f_par_12': 'reA120', 'delta_22perp2': 'reA220', 'f_par_11': 'reA11par', 'delta_10': 'reA10', 'delta_11perp': 'reA11par', 'f_perp2_22': 'reA220', 'delta_11par': 'reA11par', 'delta_120': 'reA120', 'delta_220': 'reA220', 'f_01': 'reA01', 'f_00': 'reA00', 'f_02': 'reA02', 'delta_12par': 'reA120', 'delta_01': 'reA01', 'delta_00': 'reA00', 'delta_02': 'reA02', 'delta_21perp': 'reA210', 'delta_20': 'reA20', 'f_perp_22': 'reA220', 'f_perp_21': 'reA210', 'delta_22par2': 'reA220', 'f_22': 'reA220', 'f_21': 'reA210', 'f_20': 'reA20', 'f_L_22': 'reA220', 'f_par_22': 'reA220', 'f_par_21': 'reA210', 'f_L_21': 'reA210', 'delta_12perp': 'reA120', 'delta_22par': 'reA220'}

max_strong_params = ['reA00', 'reA01', 'reA10', 'reA02', 'reA20', 'reA11par', 'reA11perp', 'reA120', 'reA12par', 'reA12perp', 'reA210', 'reA21par', 'reA21perp', 'reA220', 'reA22par', 'reA22perp', 'reA22par2', 'reA22perp2', 'imA00', 'imA01', 'imA10', 'imA02', 'imA20', 'imA11par', 'imA11perp', 'imA120', 'imA12par', 'imA12perp', 'imA210', 'imA21par', 'imA21perp', 'imA220', 'imA22par', 'imA22perp', 'imA22par2', 'imA22perp2']

par_name_dict = {'mV': 'mV', 'gammaV': 'gammaV', 'mT': 'mT', 'gammaT': 'gammaT', 'c1_mass_swave': 'c_{1}^{mass}','c2_mass_swave': 'c_{2}^{mass}','c3_mass_swave': 'c_{3}^{mass}','c4_mass_swave': 'c_{4}^{mass}','c5_mass_swave': 'c_{5}^{mass}','c6_mass_swave': 'c_{6}^{mass}','c7_mass_swave': 'c_{7}^{mass}','c8_mass_swave': 'c_{8}^{mass}','c9_mass_swave': 'c_{9}^{mass}', 'reA22perp': 'Re(A^{TT}_{#perp1})', 'reA22par2': 'Re(A^{TT}_{#parallel2})', 'delta_210': '#delta^{TV}_{0}', 'tres_p1_2012': 'p_{1}^{#sigma_{t}}(2012)', 'tres_p1_2011': 'p_{1}^{#sigma_{t}}(2011)', 'delta_00': '#delta^{SS}', 'reA10': 'Re(A^{VS})', 'p0metac_OS': 'p_{0}^{OS}-<#eta^{OS}>', 'reA220': 'Re(A^{TT}_{L})', 'reA20': 'Re(A^{TS})', 'delta_10': '#delta^{VS}', 'imA21par': 'Im(A^{TV}_{#parallel})', 'reA11par': 'Re(A^{VV}_{#parallel})', 'delta_11par': '#delta^{VV}_{#parallel}', 'DCP': '#Delta^{CP}', 'DCP_SS': 'd#Delta^{CP}_{SS}', 'DCP_SV': 'd#Delta^{CP}_{SV}', 'DCP_VS': 'd#Delta^{CP}_{VS}', 'DCP_ST': 'd#Delta^{CP}_{ST}', 'DCP_TS': 'd#Delta^{CP}_{TS}', 'DCP_VT': 'd#Delta^{CP}_{VT}', 'DCP_TV': 'd#Delta^{CP}_{TV}', 'DCP_TT': 'd#Delta^{CP}_{TT}', 'imA22perp2': 'Im(A^{TT}_{#perp2})', 'delta_12par': '#delta^{VT}_{#parallel}', 'delta_01': '#delta^{SV}', 'imA22par': 'Im(A^{TT}_{#parallel1})', 'delta_02': '#delta^{ST}', 'reA22par': 'Re(A^{TT}_{#parallel1})', 'p1_SSK': 'p_{1}^{SSK}', 'delta_22perp': '#delta^{TT}_{#perp1}', 'reA21par': 'Re(A^{TV}_{#parallel})', 'delta_21par': '#delta^{TV}_{#parallel}', 'Dp1half_SSK': '1/2 #Delta p_{1}^{SSK}', 'delta_11perp': '#delta^{VV}_{#perp}', 'f_perp2_22': 'f_{#perp2}^{TT}', 'imA210': 'Im(A^{TV}_{L})', 'tres_p0_2011': 'p_{0}^{#sigma_{t}}(2011)', 'reA120': 'Re(A^{VT}_{L})', 'imA21perp': 'Im(A^{TV}_{#perp})', 'tres_p0_2012': 'p_{0}^{#sigma_{t}}(2012)', 'delta_22perp2': '#delta^{TT}_{#perp2}', 'reA22perp2': 'Re(A^{TT}_{#perp2})', 'imA10': 'Im(A^{VS})', 'delta_21perp': '#delta^{TV}_{#perp}', 'p1_OS': 'p_{1}^{OS}', 'delta_22par2': '#delta^{TT}_{#parallel2}', 'f_22': 'f_{TT}', 'f_21': 'f_{TV}', 'f_20': 'f_{TS}', 'f_L_22': 'f_L^{TT}', 'f_par_22': 'f_{#parallel1}^{TT}', 'f_par_21': 'f_{#parallel}^{TV}', 'f_L_21': 'f_L^{TV}', 'imA12perp': 'Im(A^{VT}_{#perp})', 'delta_12perp': '#delta^{VT}_{#perp}', 'imA220': 'Im(A^{TT}_{L})', 'delta_m_Bs': '#Delta m_{B_{s}^{0}}', 'reA12par': 'Re(A^{VT}_{#parallel})', 'f_par2_22': 'f_{#parallel2}^{TT}', 'Dp1half_OS': '1/2 #Delta p_{1}^{OS}', 'f_12': 'f_{VT}', 'f_10': 'f_{VS}', 'f_11': 'f_{VV}', 'imA02': 'Im(A^{ST})', 'imA00': 'Im(A^{SS})', 'imA01': 'Im(A^{SV})', 'f_par_12': 'f_{#parallel}^{VT}', 'f_par_11': 'f_{#parallel}^{VV}', 'reA01': 'Re(A^{SV})', 'Dp0half_OS': '1/2 #Delta p_{0}^{OS}', 'reA11perp': 'Re(A^{VV}_{#perp})', 'imA120': 'Im(A^{VT}_{L})', 'f_01': 'f_{SV}', 'f_00': 'f_{SS}', 'f_02': 'f_{ST}', 'gamma_Bs': '#Gamma_{B_{s}^{0}}', 'f_perp_22': 'f_{#perp1}^{TT}', 'f_perp_21': 'f_{#perp}^{TV}', 'p0metac_SSK': 'p_{0}^{SSK}-<#eta^{SSK}>', 'imA22perp': 'Im(A^{TT}_{#perp1})', 'delta_22par': '#delta^{TT}_{#parallel1}', 'imA22par2': 'Im(A^{TT}_{#parallel2})', 'reA210': 'Re(A^{TV}_{L})', 'imA20': 'Im(A^{TS})', 'imA11perp': 'Im(A^{VV}_{#perp})', 'f_L_12': 'f_L^{VT}', 'f_L_11': 'f_L^{VV}', 'f_perp_12': 'f_{#perp}^{VT}', 'f_perp_11': 'f_{#perp}^{VV}', 'delta_120': '#delta^{VT}_{0}', 'delta_220': '#delta^{TT}_{0}', 'reA21perp': 'Re(A^{TV}_{#perp})', 'imA11par': 'Im(A^{VV}_{#parallel})', 'reA12perp': 'Re(A^{VT}_{#perp})', 'Dp0half_SSK': '1/2 #Delta p_{0}^{SSK}', 'reA00': 'Re(A^{SS})', 'reA02': 'Re(A^{ST})', 'delta_gamma_Bs': '#Delta #Gamma_{B_{s}^{0}}', 'delta_20': '#delta^{TS}', 'imA12par': 'Im(A^{VT}_{#parallel})', 'phis': '#phi_{s}', 'dphi_SS': 'd#phi_{sSS}', 'dphi_SV': 'd#phi_{sSV}', 'dphi_VS': 'd#phi_{sVS}', 'dphi_ST': 'd#phi_{sST}', 'dphi_TS': 'd#phi_{sTS}', 'dphi_VT': 'd#phi_{sVT}', 'dphi_TV': 'd#phi_{sTV}', 'dphi_TT': 'd#phi_{sTT}'}

par_result_varnw_dict = {'reA22perp': (-0.0735597446872891, 0.30306422294354984, 'Re(A^{TT}_{\\perp1})'), 'reA22par2': (-0.11027482204968209, 0.1972660406076309, 'Re(A^{TT}_{\\parallel2})'), 'delta_210': (1.5818771289499283, 0.1996357045583519, '\\delta^{TV}_{0}'), 'tres_p1_2012': (1.2616281236695952, 0.05274779635421897, 'p_{1}^{\\sigma_{t}}(2012)'), 'tres_p1_2011': (1.1538295242847139, 0.04960299287000747, 'p_{1}^{\\sigma_{t}}(2011)'), 'delta_00': (0.631168448200234, 0.11360173260090543, '\\delta^{SS}'), 'reA10': (-0.48302864950598234, 0.4763598870652409, 'Re(A^{VS})'), 'p0metac_OS': (0.007847072990527244, 0.004354351076796169, 'p_{0}^{OS}-<\\eta^{OS}>'), 'reA220': (0.09894281879607014, 0.15932942348995033, 'Re(A^{TT}_{L})'), 'reA20': (1.050699228614123, 0.31398789866659826, 'Re(A^{TS})'), 'delta_10': (1.7135280268369553, 0.13459951553288768, '\\delta^{VS}'), 'imA21par': (0.4244950066013349, 0.17314585466911223, 'Im(A^{TV}_{\\parallel})'), 'reA11par': (-0.7111304320426761, 0.1707175215323854, 'Re(A^{VV}_{\\parallel})'), 'delta_11par': (2.0879480096016994, 0.12338043142235076, '\\delta^{VV}_{\\parallel}'), 'DCP': (-3.3367627658250862, 0.032947673811672316, '\\Delta^{CP}'), 'imA22perp2': (-0.16116796651845533, 0.28192381916693593, 'Im(A^{TT}_{\\perp2})'), 'delta_12par': (-2.380342007468954, 0.4875078541657935, '\\delta^{VT}_{\\parallel}'), 'delta_01': (-1.8257969059834425, 0.1265241923734855, '\\delta^{SV}'), 'imA22par': (0.341353948048404, 0.13913848147616975, 'Im(A^{TT}_{\\parallel1})'), 'delta_02': (-2.8598839100075946, 0.4801574976201071, '\\delta^{ST}'), 'reA22par': (-0.3445272298732682, 0.12515622178853059, 'Re(A^{TT}_{\\parallel1})'), 'tres_p0_2012': (0.03645129885555397, 0.0002505952651479666, 'p_{0}^{\\sigma_{t}}(2012)'), 'delta_22perp': (1.7208325809900469, 0.609483181030259, '\\delta^{TT}_{\\perp1}'), 'reA21par': (0.5995319172808244, 0.20361029898967656, 'Re(A^{TV}_{\\parallel})'), 'delta_21par': (0.6161042782711134, 0.29462562756538346, '\\delta^{TV}_{\\parallel}'), 'Dp1half_SSK': (-0.015254926677277458, 0.022672452211574556, '1/2 \\Delta p_{1}^{SSK}'), 'delta_11perp': (1.939258354068904, 0.28906842605122646, '\\delta^{VV}_{\\perp}'), 'f_perp2_22': (0.3459135354425529, 0.16551808739606666, 'f_{\\perp2}^{TT}'), 'imA210': (1.510610109476234, 0.4920780258126781, 'Im(A^{TV}_{L})'), 'tres_p0_2011': (0.034768435155261665, 0.00024408794786592213, 'p_{0}^{\\sigma_{t}}(2011)'), 'reA120': (-2.1784357982662, 0.36055834688344035, 'Re(A^{VT}_{L})'), 'imA21perp': (-0.5746150091963251, 0.3317724599697678, 'Im(A^{TV}_{\\perp})'), 'p1_SSK': (0.9284621096763134, 0.08203189533067752, 'p_{1}^{SSK}'), 'delta_22perp2': (-0.3088856089140464, 0.5483218394248964, '\\delta^{TT}_{\\perp2}'), 'reA22perp2': (0.5050716648410116, 0.18681474451094834, 'Re(A^{TT}_{\\perp2})'), 'imA10': (3.3611597476834234, 0.5685389043191992, 'Im(A^{VS})'), 'delta_21perp': (-0.7562188100342472, 0.45664851255489214, '\\delta^{TV}_{\\perp}'), 'p1_OS': (0.9921874478452092, 0.034777221443417, 'p_{1}^{OS}'), 'delta_22par2': (2.347811003368292, 0.5558901241050392, '\\delta^{TT}_{\\parallel2}'), 'f_22': (0.009183543958251066, 0.002710016746295089, 'f_{TT}'), 'f_21': (0.03981873583149521, 0.015123580018046921, 'f_{TV}'), 'f_20': (0.03310278020366144, 0.008536957807655132, 'f_{TS}'), 'f_L_22': (0.036102805589920135, 0.06586150916120274, 'f_L^{TT}'), 'f_par_22': (0.2894851364984548, 0.14091024973977384, 'f_{\\parallel1}^{TT}'), 'f_par_21': (0.1531693158498012, 0.0767161393034345, 'f_{\\parallel}^{TV}'), 'f_L_21': (0.6477838851780799, 0.1379919834577876, 'f_L^{TV}'), 'imA12perp': (0.6465140084462302, 0.3426703743019514, 'Im(A^{VT}_{\\perp})'), 'delta_12perp': (2.53482884577029, 0.3457365178678489, '\\delta^{VT}_{\\perp}'), 'imA220': (0.13980594039667693, 0.17676002217462136, 'Im(A^{TT}_{L})'), 'delta_m_Bs': (17.618112578577502, 0.08167342453732405, '\\Delta m_{B_{s}^{0}}'), 'reA12par': (-0.3186859258260526, 0.17613552448981823, 'Re(A^{VT}_{\\parallel})'), 'c3_mass_swave': (-0.12163136947109421, 0.015311277312228132, 'c_{3}^{mass}'), 'f_par2_22': (0.03044213597889084, 0.09062559060729963, 'f_{\\parallel2}^{TT}'), 'Dp1half_OS': (0.03281067190533479, 0.005993065192385953, '1/2 \\Delta p_{1}^{OS}'), 'f_12': (0.08757804498973039, 0.016427834106826203, 'f_{VT}'), 'f_10': (0.1303213636776544, 0.026296301333162454, 'f_{VS}'), 'f_11': (0.07616112111945339, 0.004601382942301318, 'f_{VV}'), 'imA02': (-0.2048655009177569, 0.4007347003486179, 'Im(A^{ST})'), 'imA00': (2.9507002982943504, 0.5371212442342594, 'Im(A^{SS})'), 'imA01': (-5.2689983817717, 0.6839567507571603, 'Im(A^{SV})'), 'f_par_12': (0.02500600274793292, 0.016866740062547975, 'f_{\\parallel}^{VT}'), 'f_par_11': (0.3070129636679346, 0.03108602287567394, 'f_{\\parallel}^{VV}'), 'Dp0half_SSK': (-0.008046528953707959, 0.0013825312086699188, '1/2 \\Delta p_{0}^{SSK}'), 'Dp0half_OS': (0.006991268663015419, 0.0005991390332970243, '1/2 \\Delta p_{0}^{OS}'), 'reA11perp': (-0.6899895993962257, 0.5062901825849236, 'Re(A^{VV}_{\\perp})'), 'imA120': (-1.2344797129847294, 0.5482780643632025, 'Im(A^{VT}_{L})'), 'f_01': (0.3350944491270055, 0.026523196352403106, 'f_{SV}'), 'f_00': (0.28260212099378823, 0.011846024723397712, 'f_{SS}'), 'f_02': (0.006137840098960122, 0.006346585560303772, 'f_{ST}'), 'c2_mass_swave': (-0.1585889977425825, 0.019406249576048952, 'c_{2}^{mass}'), 'gamma_Bs': (0.6652886270365236, 0.0019676362639323717, '\\Gamma_{B_{s}^{0}}'), 'f_perp_22': (0.29805638649018135, 0.175797243473789, 'f_{\\perp1}^{TT}'), 'f_perp_21': (0.1990467989721187, 0.08647930477048982, 'f_{\\perp}^{TV}'), 'p0metac_SSK': (0.007267043982177306, 0.0050547756388464845, 'p_{0}^{SSK}-<\\eta^{SSK}>'), 'imA22perp': (0.48659539088895976, 0.17633566825012784, 'Im(A^{TT}_{\\perp1})'), 'delta_22par': (2.3608210338061837, 0.2476696658388352, '\\delta^{TT}_{\\parallel1}'), 'imA22par2': (0.1121394730466374, 0.15228187961329426, 'Im(A^{TT}_{\\parallel2})'), 'reA210': (-0.016739456875580316, 0.30160556974705827, 'Re(A^{TV}_{L})'), 'imA20': (-1.3509011615458704, 0.4597895405179997, 'Im(A^{TS})'), 'imA11perp': (1.7870985799327919, 0.3351760719874725, 'Im(A^{VV}_{\\perp})'), 'f_L_12': (0.8090935533665471, 0.04438116437559516, 'f_L^{VT}'), 'f_L_11': (0.148397361829253, 0.03217543911569287, 'f_L^{VV}'), 'f_perp_12': (0.16590044388551997, 0.04088094574994784, 'f_{\\perp}^{VT}'), 'f_perp_11': (0.5445896745028123, 0.035406105850297326, 'f_{\\perp}^{VV}'), 'c1_mass_swave': (-0.2999145131367409, 0.019871084784432978, 'c_{1}^{mass}'), 'c4_mass_swave': (-0.06590222906448306, 0.01627658856871813, 'c_{4}^{mass}'), 'delta_120': (-2.6260322629041277, 0.2118507085715715, '\\delta^{VT}_{0}'), 'delta_220': (0.9549109802328231, 1.0338830362523146, '\\delta^{TT}_{0}'), 'reA21perp': (0.6091668037771996, 0.2557623291630649, 'Re(A^{TV}_{\\perp})'), 'imA11par': (1.250260291892074, 0.2011418584802664, 'Im(A^{VV}_{\\parallel})'), 'reA12perp': (-0.9314251460156928, 0.26684696226308574, 'Re(A^{VT}_{\\perp})'), 'reA01': (-1.3734982090884902, 0.6999374641380647, 'Re(A^{SV})'), 'reA00': (4.037045611521224, 0.6638886334615056, 'Re(A^{SS})'), 'reA02': (-0.7078844807364177, 0.3375555170255883, 'Re(A^{ST})'), 'delta_gamma_Bs': (0.08618311902645703, 0.005877584711519312, '\\Delta \\Gamma_{B_{s}^{0}}'), 'delta_20': (-0.9097539304184619, 0.26934040460890546, '\\delta^{TS}'), 'imA12par': (-0.3036550155575686, 0.1943687862124656, 'Im(A^{VT}_{\\parallel})'), 'phis': (8.596993560492631, 0.11451831052010514, '\\phi_{s}')}

par_result_constnw_dict = {'reA22perp': (-0.07422561735003441, 0.30196831409329866, 'Re(A^{TT}_{\\perp1})'), 'reA22par2': (-0.10977919188605512, 0.1969467132682363, 'Re(A^{TT}_{\\parallel2})'), 'delta_210': (1.5821781346585668, 0.1981172086800449, '\\delta^{TV}_{0}'), 'tres_p1_2012': (1.2616172078197445, 0.05274733982469428, 'p_{1}^{\\sigma_{t}}(2012)'), 'tres_p1_2011': (1.1539493276078308, 0.04959945287409409, 'p_{1}^{\\sigma_{t}}(2011)'), 'delta_00': (0.6310210893525537, 0.11351159667910327, '\\delta^{SS}'), 'reA10': (-0.4818825157334441, 0.47365236797142235, 'Re(A^{VS})'), 'p0metac_OS': (0.007850008602655344, 0.004354135912606459, 'p_{0}^{OS}-<\\eta^{OS}>'), 'reA220': (0.0985546512663742, 0.15815104912571393, 'Re(A^{TT}_{L})'), 'reA20': (1.0516015547119792, 0.31317561659821613, 'Re(A^{TS})'), 'delta_10': (1.7132189785482739, 0.13416062005435211, '\\delta^{VS}'), 'imA21par': (0.4251439690837895, 0.1723387698462173, 'Im(A^{TV}_{\\parallel})'), 'reA11par': (-0.7109611904442712, 0.1694735475125885, 'Re(A^{VV}_{\\parallel})'), 'delta_11par': (2.087802732833163, 0.12308318381645929, '\\delta^{VV}_{\\parallel}'), 'DCP': (-3.336834100942994, 0.03287398843756592, '\\Delta^{CP}'), 'imA22perp2': (-0.16017658850499394, 0.2803961640688439, 'Im(A^{TT}_{\\perp2})'), 'delta_12par': (-2.3814153498007187, 0.4858169819583023, '\\delta^{VT}_{\\parallel}'), 'delta_01': (-1.8257092884062862, 0.1263191445923095, '\\delta^{SV}'), 'imA22par': (0.3419378753751161, 0.13752878188335022, 'Im(A^{TT}_{\\parallel1})'), 'delta_02': (-2.857160118115828, 0.47274460719310313, '\\delta^{ST}'), 'reA22par': (-0.3443091927769686, 0.12473477815416364, 'Re(A^{TT}_{\\parallel1})'), 'tres_p0_2012': (0.03645114009699407, 0.0002505979594572659, 'p_{0}^{\\sigma_{t}}(2012)'), 'delta_22perp': (1.7220630481453068, 0.6068097981807193, '\\delta^{TT}_{\\perp1}'), 'reA21par': (0.5991810972844451, 0.20048019097624487, 'Re(A^{TV}_{\\parallel})'), 'delta_21par': (0.6171011194695819, 0.2931333941312186, '\\delta^{TV}_{\\parallel}'), 'Dp1half_SSK': (-0.015252433759744, 0.02267245458974212, '1/2 \\Delta p_{1}^{SSK}'), 'delta_11perp': (1.9394703452298034, 0.2881908887576033, '\\delta^{VV}_{\\perp}'), 'f_perp2_22': (0.3460059775570623, 0.16484572975915102, 'f_{\\perp2}^{TT}'), 'imA210': (1.5102268561062537, 0.4778143327322305, 'Im(A^{TV}_{L})'), 'tres_p0_2011': (0.03476863646795697, 0.0002440777049750134, 'p_{0}^{\\sigma_{t}}(2011)'), 'reA120': (-2.1785122175811287, 0.34825829429934446, 'Re(A^{VT}_{L})'), 'imA21perp': (-0.574353831446091, 0.32886184423286374, 'Im(A^{TV}_{\\perp})'), 'p1_SSK': (0.9284973212063521, 0.08203250815863705, 'p_{1}^{SSK}'), 'delta_22perp2': (-0.3067485685969915, 0.5462375613821242, '\\delta^{TT}_{\\perp2}'), 'reA22perp2': (0.5056938564147693, 0.1840698448164958, 'Re(A^{TT}_{\\perp2})'), 'imA10': (3.360560226771071, 0.5514299069545597, 'Im(A^{VS})'), 'delta_21perp': (-0.7558653134786215, 0.4553535164687906, '\\delta^{TV}_{\\perp}'), 'p1_OS': (0.99219232383791, 0.03477676955135745, 'p_{1}^{OS}'), 'delta_22par2': (2.3483756053393314, 0.5569098125220759, '\\delta^{TT}_{\\parallel2}'), 'f_22': (0.009190427376370798, 0.0025771240213735783, 'f_{TT}'), 'f_21': (0.03980257668484872, 0.014938927020175068, 'f_{TV}'), 'f_20': (0.03306503436487386, 0.008311810262891958, 'f_{TS}'), 'f_L_22': (0.035988475857040986, 0.06528084079672292, 'f_L^{TT}'), 'f_par_22': (0.289549103216287, 0.13893711665914796, 'f_{\\parallel1}^{TT}'), 'f_par_21': (0.15325532638545658, 0.07631665134068205, 'f_{\\parallel}^{TV}'), 'f_L_21': (0.6476661360893627, 0.13665318787409053, 'f_L^{TV}'), 'imA12perp': (0.6464527993749307, 0.3380842423951303, 'Im(A^{VT}_{\\perp})'), 'delta_12perp': (2.5349053337112566, 0.3443488486550821, '\\delta^{VT}_{\\perp}'), 'imA220': (0.1398353600400437, 0.17567075415228617, 'Im(A^{TT}_{L})'), 'delta_m_Bs': (17.618187151401123, 0.08154198312412247, '\\Delta m_{B_{s}^{0}}'), 'reA12par': (-0.31930626006862717, 0.17557387952245063, 'Re(A^{VT}_{\\parallel})'), 'f_par2_22': (0.030109314086630416, 0.08987353354164121, 'f_{\\parallel2}^{TT}'), 'Dp1half_OS': (0.032810295120572514, 0.0059930725915674265, '1/2 \\Delta p_{1}^{OS}'), 'f_12': (0.08759040112806357, 0.016047487186664218, 'f_{VT}'), 'f_10': (0.13025199050985692, 0.026200440477220206, 'f_{VS}'), 'f_11': (0.07617187057781845, 0.004356888035288296, 'f_{VV}'), 'imA02': (-0.2071742359647235, 0.39858323017051434, 'Im(A^{ST})'), 'imA00': (2.950222600890669, 0.5278798586734365, 'Im(A^{SS})'), 'imA01': (-5.2699240019240055, 0.6658921641900798, 'Im(A^{SV})'), 'f_par_12': (0.025046495327613896, 0.016845628196663742, 'f_{\\parallel}^{VT}'), 'f_par_11': (0.30695364835891303, 0.030981855730300642, 'f_{\\parallel}^{VV}'), 'Dp0half_SSK': (-0.008046602303667357, 0.001382531168358857, '1/2 \\Delta p_{0}^{SSK}'), 'Dp0half_OS': (0.006991298101529059, 0.0005991385174119489, '1/2 \\Delta p_{0}^{OS}'), 'reA11perp': (-0.6905062283293439, 0.5065293296489629, 'Re(A^{VV}_{\\perp})'), 'imA120': (-1.2348994137129825, 0.5495577193175852, 'Im(A^{VT}_{L})'), 'f_01': (0.3351677332276821, 0.02634701841450725, 'f_{SV}'), 'f_00': (0.2826000021084217, 0.011196741961466809, 'f_{SS}'), 'f_02': (0.0061599640220634235, 0.00627054588714095, 'f_{ST}'), 'gamma_Bs': (0.6652948018876358, 0.0019676001535852616, '\\Gamma_{B_{s}^{0}}'), 'f_perp_22': (0.29834712928297924, 0.17467227158578624, 'f_{\\perp1}^{TT}'), 'f_perp_21': (0.19907853752518076, 0.08567343618799604, 'f_{\\perp}^{TV}'), 'p0metac_SSK': (0.0072683156443861426, 0.005054463205793598, 'p_{0}^{SSK}-<\\eta^{SSK}>'), 'imA22perp': (0.4869452914280803, 0.17006688302646072, 'Im(A^{TT}_{\\perp1})'), 'delta_22par': (2.3596499628257757, 0.24557581181269467, '\\delta^{TT}_{\\parallel1}'), 'imA22par2': (0.11150945761584197, 0.15193267680161224, 'Im(A^{TT}_{\\parallel2})'), 'reA210': (-0.01718985420287389, 0.29924764555120864, 'Re(A^{TV}_{L})'), 'imA20': (-1.3490558625999487, 0.44744884891439557, 'Im(A^{TS})'), 'imA11perp': (1.787308938055146, 0.32626556405752466, 'Im(A^{VV}_{\\perp})'), 'f_L_12': (0.8090857398581417, 0.044326949627353104, 'f_L^{VT}'), 'f_L_11': (0.14836351599278935, 0.031125824121668144, 'f_L^{VV}'), 'f_perp_12': (0.1658677648142444, 0.04083604561846762, 'f_{\\perp}^{VT}'), 'f_perp_11': (0.5446828356482976, 0.03490751511367655, 'f_{\\perp}^{VV}'), 'delta_120': (-2.625901493225181, 0.21144117432938692, '\\delta^{VT}_{0}'), 'delta_220': (0.956862406555501, 1.035629568782537, '\\delta^{TT}_{0}'), 'reA21perp': (0.6093212980725085, 0.25604379415708045, 'Re(A^{TV}_{\\perp})'), 'imA11par': (1.2503853970601604, 0.19677954156957847, 'Im(A^{VV}_{\\parallel})'), 'reA12perp': (-0.9314890543650254, 0.2669399783880778, 'Re(A^{VT}_{\\perp})'), 'reA01': (-1.37324639290979, 0.6946509686112958, 'Re(A^{SV})'), 'reA00': (4.0376408177766105, 0.6447494620532553, 'Re(A^{SS})'), 'reA02': (-0.7086282910442794, 0.3299463684258643, 'Re(A^{ST})'), 'delta_gamma_Bs': (0.08615678124351381, 0.005877617862059901, '\\Delta \\Gamma_{B_{s}^{0}}'), 'delta_20': (-0.9086752081549326, 0.26783250625243554, '\\delta^{TS}'), 'imA12par': (-0.3035928765349514, 0.1938745686541677, 'Im(A^{VT}_{\\parallel})'), 'phis': (8.597144924350035, 0.11442558567490102, '\\phi_{s}')}

def stringline_CUDA(parname,upardict):
   if parname not in upardict.keys(): return ''
   elif type(upardict[parname]) == type(0.): return ''
   else: return '$'+par_name_dict[parname]+'$ & $'+'{:L}'.format(upardict[parname])+'$ \\\\\n'

def fitprint2LaTeX_CUDA(upardict,wide_window):
	partext = '\\documentclass[11pt,a4paper]{article}\n\\usepackage[left=2.5cm,top=2.5cm,right=2.5cm,bottom=2.5cm]{geometry}\n\n\\begin{document}\n\n\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|}\n\hline\nParameter & Value \\\\\n\\hline\n\\hline\n'
	partext += '\\multicolumn{2}{|c|}{Common parameters}\\\\\n\\hline\n\\hline\n'
	partext += stringline_CUDA("phis",upardict)
	partext += stringline_CUDA("DCP",upardict)
	partext += stringline_CUDA("delta_m_Bs",upardict)
	partext += stringline_CUDA("gamma_Bs",upardict)
	partext += stringline_CUDA("delta_gamma_Bs",upardict)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{2}{|c|}{$B_{s}^{0}\\to K^{*}(892)^{0}\\bar{K}^{*}(892)^{0}$ (VV)}\\\\\n\\hline\n\\hline\n'
	partext += stringline_CUDA("reA11par",upardict)
	partext += stringline_CUDA("imA11par",upardict)
	partext += stringline_CUDA("reA11perp",upardict)
	partext += stringline_CUDA("imA11perp",upardict)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{2}{|c|}{Single $S-wave$ (SV and VS)}\\\\\n\\hline\n\\hline\n'
	partext += stringline_CUDA("reA01",upardict)
	partext += stringline_CUDA("imA01",upardict)
	partext += stringline_CUDA("reA10",upardict)
	partext += stringline_CUDA("imA10",upardict)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{2}{|c|}{Double $S-wave$ (SS)}\\\\\n\\hline\n\\hline\n'
	partext += stringline_CUDA("reA00",upardict)
	partext += stringline_CUDA("imA00",upardict)
	partext += '\\hline\n\\hline\n'
	if wide_window:
		partext += '\\multicolumn{2}{|c|}{$Scalar-Tensor$ decays (ST and TS)}\\\\\n\\hline\n\\hline\n'
		partext += stringline_CUDA("reA02",upardict)
		partext += stringline_CUDA("imA02",upardict)
		partext += stringline_CUDA("reA20",upardict)
		partext += stringline_CUDA("imA20",upardict)
		partext += '\\hline\n\\hline\n'
		partext += '\\end{tabular}\n\\end{table}\n\n'
		partext += '\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|}\n\hline\nParameter & Value \\\\\n\\hline\n\\hline\n'
		partext += '\\multicolumn{2}{|c|}{Single $D-wave$ (VT and TV)}\\\\\n\\hline\n\\hline\n'
		partext += stringline_CUDA("reA120",upardict)
		partext += stringline_CUDA("imA120",upardict)
		partext += stringline_CUDA("reA12par",upardict)
		partext += stringline_CUDA("imA12par",upardict)
		partext += stringline_CUDA("reA12perp",upardict)
		partext += stringline_CUDA("imA12perp",upardict)
		partext += stringline_CUDA("reA210",upardict)
		partext += stringline_CUDA("imA210",upardict)
		partext += stringline_CUDA("reA21par",upardict)
		partext += stringline_CUDA("imA21par",upardict)
		partext += stringline_CUDA("reA21perp",upardict)
		partext += stringline_CUDA("imA21perp",upardict)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{2}{|c|}{Double $D-wave$ (TT)}\\\\\n\\hline\n\\hline\n'
		partext += stringline_CUDA("reA220",upardict)
		partext += stringline_CUDA("imA220",upardict)
		partext += stringline_CUDA("reA22par",upardict)
		partext += stringline_CUDA("imA22par",upardict)
		partext += stringline_CUDA("reA22perp",upardict)
		partext += stringline_CUDA("imA22perp",upardict)
		partext += stringline_CUDA("reA22par2",upardict)
		partext += stringline_CUDA("imA22par2",upardict)
		partext += stringline_CUDA("reA22perp2",upardict)
		partext += stringline_CUDA("imA22perp2",upardict)
		partext += '\\hline\n\\hline\n'
	partext += '\\end{tabular}\n\\end{table}\n\n'
	partext += '\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|}\n\hline\nParameter & Value \\\\\n\\hline\n\\hline\n'
	partext += '\\multicolumn{2}{|c|}{Common parameters}\\\\\n\\hline\n\\hline\n'
	partext += stringline_CUDA("phis",upardict)
	partext += stringline_CUDA("DCP",upardict)
	partext += stringline_CUDA("delta_m_Bs",upardict)
	partext += stringline_CUDA("gamma_Bs",upardict)
	partext += stringline_CUDA("delta_gamma_Bs",upardict)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{2}{|c|}{$B_{s}^{0}\\to K^{*}(892)^{0}\\bar{K}^{*}(892)^{0}$ (VV)}\\\\\n\\hline\n\\hline\n'
	partext += stringline_CUDA("f_11",upardict)
	partext += stringline_CUDA("f_L_11",upardict)
	partext += stringline_CUDA("f_par_11",upardict)
	partext += stringline_CUDA("delta_11par",upardict)
	partext += stringline_CUDA("delta_11perp",upardict)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{2}{|c|}{Single $S-wave$ (SV and VS)}\\\\\n\\hline\n\\hline\n'
	partext += stringline_CUDA("f_01",upardict)
	partext += stringline_CUDA("f_10",upardict)
	partext += stringline_CUDA("delta_01",upardict)
	partext += stringline_CUDA("delta_10",upardict)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{2}{|c|}{Double $S-wave$ (SS)}\\\\\n\\hline\n\\hline\n'
	partext += stringline_CUDA("f_00",upardict)
	partext += stringline_CUDA("delta_00",upardict)
	partext += '\\hline\n\\hline\n'
	if wide_window:
		partext += '\\multicolumn{2}{|c|}{$Scalar-Tensor$ decays (ST and TS)}\\\\\n\\hline\n\\hline\n'
		partext += stringline_CUDA("f_02",upardict)
		partext += stringline_CUDA("f_20",upardict)
		partext += stringline_CUDA("delta_02",upardict)
		partext += stringline_CUDA("delta_20",upardict)
		partext += '\\hline\n\\hline\n'
		partext += '\\end{tabular}\n\\end{table}\n\n'
		partext += '\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|}\n\hline\nParameter & Value \\\\\n\\hline\n\\hline\n'
		partext += '\\multicolumn{2}{|c|}{Single $D-wave$ (VT and TV)}\\\\\n\\hline\n\\hline\n'
		partext += stringline_CUDA("f_12",upardict)
		partext += stringline_CUDA("f_L_12",upardict)
		partext += stringline_CUDA("f_par_12",upardict)
		partext += stringline_CUDA("f_21",upardict)
		partext += stringline_CUDA("f_L_21",upardict)
		partext += stringline_CUDA("f_par_21",upardict)
		partext += stringline_CUDA("delta_120",upardict)
		partext += stringline_CUDA("delta_12par",upardict)
		partext += stringline_CUDA("delta_12perp",upardict)
		partext += stringline_CUDA("delta_210",upardict)
		partext += stringline_CUDA("delta_21par",upardict)
		partext += stringline_CUDA("delta_21perp",upardict)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{2}{|c|}{Double $D-wave$ (TT)}\\\\\n\\hline\n\\hline\n'
		partext += stringline_CUDA("f_22",upardict)
		partext += stringline_CUDA("f_L_22",upardict)
		partext += stringline_CUDA("f_par_22",upardict)
		partext += stringline_CUDA("f_perp_22",upardict)
		partext += stringline_CUDA("f_par2_22",upardict)
		partext += stringline_CUDA("delta_220",upardict)
		partext += stringline_CUDA("delta_22par",upardict)
		partext += stringline_CUDA("delta_22perp",upardict)
		partext += stringline_CUDA("delta_22par2",upardict)
		partext += stringline_CUDA("delta_22perp2",upardict)
		partext += '\\hline\n\\hline\n'
	partext += '\\end{tabular}\n\\end{table}\n\n'
	partext += '\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|}\n\hline\nParameter & Value \\\\\n\\hline\n\\hline\n'
	partext += '\\multicolumn{2}{|c|}{SSK tagger}\\\\\n\\hline\n\\hline\n'
	partext += stringline_CUDA("p0metac_SSK",upardict)
	partext += stringline_CUDA("Dp0half_SSK",upardict)
	partext += stringline_CUDA("p1_SSK",upardict)
	partext += stringline_CUDA("Dp1half_SSK",upardict)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{2}{|c|}{OS tagger}\\\\\n\\hline\n\\hline\n'
	partext += stringline_CUDA("p0metac_OS",upardict)
	partext += stringline_CUDA("Dp0half_OS",upardict)
	partext += stringline_CUDA("p1_OS",upardict)
	partext += stringline_CUDA("Dp1half_OS",upardict)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{2}{|c|}{Time resolution}\\\\\n\\hline\n\\hline\n'
	partext += stringline_CUDA("tres_p0_2011",upardict)
	partext += stringline_CUDA("tres_p1_2011",upardict)
	partext += stringline_CUDA("tres_p0_2012",upardict)
	partext += stringline_CUDA("tres_p1_2012",upardict)
	partext += '\\hline\n\\hline\n\\end{tabular}\n\\end{table}\n\n'
	partext += '\\end{document}'
	partext = partext.replace('#','\\')
	partext = partext.replace('\\hline\n\\end{tabular}','\\end{tabular}')

	texfile = open('FitParams_CUDA.tex','w')
	texfile.write(partext)
	texfile.close()

def diagonalise(cov_array):

   (eig_vals, eig_vecs) = np.linalg.eig(cov_array)
   matrix_U = np.matrix(eig_vecs)
   matrix_IU = matrix_U.I
   return np.array(matrix_IU), eig_vals

def randomvary(vec_init_array,vec_final_array,diag_tools):

   matrix_IU_array, diag_cov_array = diag_tools
   delta_list = []
   for sigma2 in list(diag_cov_array.real): delta_list.append(np.random.normal()*sqrt(max(sigma2,0.)))
   for i in range(len(vec_final_array)):
      vi = vec_init_array[i]
      for j in range(len(vec_init_array)): vi += matrix_IU_array[i][j].real*delta_list[j]
      vec_final_array[i] = vi

def myset(l):

   ln = [0.]
   for i in l:
      if (not i in ln) and i != 0.: ln.append(i)
   return ln

dict_nw_find_value = [1, 0, 2, 3, 4, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 0, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 0, 25, 26, 27, 28, 29, 30, 31, 0, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 0, 43, 0, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 0, 60, 0, 61, 62, 0, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 0, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 0, 105, 0, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 66, 125, 126, 0, 127, 0, 128, 129, 0, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 0, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 0, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 0, 175, 0, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 72, 189, 190, 191, 192, 193, 135, 194, 195, 0, 196, 0, 197, 198, 0, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 0, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 0, 243, 0, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 76, 255, 256, 257, 258, 259, 141, 260, 261, 262, 263, 264, 265, 266, 202, 267, 268, 0, 269, 0, 270, 271, 0, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300, 0, 301, 0, 0, 302, 303, 0, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 0, 332, 0, 333, 334, 0, 0, 335, 336, 0]

dict_nw_find_example = [0, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 28, 29, 30, 31, 32, 33, 34, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 48, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 67, 69, 70, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 116, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 138, 139, 141, 143, 144, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 194, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 210, 211, 212, 213, 214, 216, 217, 219, 221, 222, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 270, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 284, 285, 286, 287, 288, 290, 291, 292, 293, 294, 295, 296, 298, 299, 301, 303, 304, 306, 307, 308, 309, 310, 311, 312, 313, 314, 315, 316, 317, 318, 319, 320, 321, 322, 323, 324, 325, 326, 327, 328, 329, 330, 331, 332, 333, 334, 336, 339, 340, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 360, 361, 362, 363, 364, 365, 366, 367, 368, 369, 371, 373, 374, 377, 378]

def DoCUDAFit(data_,params_,blinding_,wide_window_,var_nw_,minos_,output_file_name_,randomize_c_mass_,randomize_nw_,repeat_fit_for_nw_syst_,nw_syst_N_iterations_):

   print "\n#####################################################################"
   print " P R E P A R I N G   C U D A   F R A M E W O R K"
   print "#####################################################################\n"

   import pycuda.autoinit
   import pycuda.cumath
   import pycuda.driver as cudriver
   import pycuda.gpuarray as gpuarray
   from iminuit import Minuit
   from ModelBricks import Parameter, Free, Cat, ParamBox, cuRead
   from tools import plt
   from timeit import default_timer as timer
   import uncertainties
   import uncertainties.umath as umath

   mintnpoints = 500
   mintnpoints2 = mintnpoints*mintnpoints
   if wide_window_: minthlimit = mHlimit
   else: minthlimit = 1050.
   mintarray = np.ones(mintnpoints2).astype(np.float64)

   nindnws = 336
   nindnws2 = nindnws*nindnws

   block_size_maxmpdf = 500
   block_size_mint = 510
   block_size_nw = 6*85
   block_size_nwcov = 500
   block_size_fit = 12*21
   THR = 1e06

   paramnames = []
   for par in params_: paramnames.append(par.GetName())

   def getGrid_maxmpdf():
      Nbunch = mintnpoints2 * 1. / block_size_maxmpdf
      if Nbunch > int(Nbunch): Nbunch = int(Nbunch) +1
      else : Nbunch = int(Nbunch)
      return  (Nbunch,1,1)

   def getGrid_mint():
      Nbunch = mintnpoints2 * 1. / block_size_mint
      if Nbunch > int(Nbunch): Nbunch = int(Nbunch) +1
      else : Nbunch = int(Nbunch)
      return  (Nbunch,1,1)

   def getGrid_nw(thiscat):
      Nbunch = thiscat.NMCevts *1. / block_size_nw
      if Nbunch > int(Nbunch): Nbunch = int(Nbunch) +1
      else : Nbunch = int(Nbunch)
      return  (Nbunch,1,1)

   def getGrid_nwcov():
      Nbunch = nindnws2 * 1. / block_size_nwcov
      if Nbunch > int(Nbunch): Nbunch = int(Nbunch) +1
      else : Nbunch = int(Nbunch)
      return  (Nbunch,1,1)

   def getGrid_fit(thiscat):
      Nbunch = thiscat.Nevts *1. / block_size_fit
      print "thiscat.Nevts, Nbunch = ", thiscat.Nevts, Nbunch
      if Nbunch > int(Nbunch): Nbunch = int(Nbunch) +1
      else : Nbunch = int(Nbunch)
      return  (Nbunch,1,1)

   block_maxmpdf = (block_size_maxmpdf,1,1)
   grid_maxmpdf = getGrid_maxmpdf()
   block_mint = (block_size_mint,1,1)
   grid_mint = getGrid_mint()
   block_nwcov = (block_size_nwcov,1,1)
   grid_nwcov = getGrid_nwcov()

   c_mass_centers = np.array([-0.29994255, -0.15854387, -0.12167263, -0.06586275]).astype(np.float64)
   c_mass_cov_array = np.array([[0.0003947516243460034, -7.661577933574582e-05, 0.00011979980192447234, -5.0500702593427645e-05], [-7.661577933574582e-05, 0.0003759673751610742, -7.33894853808996e-05, 0.00016748362866758049], [0.00011979980192447234, -7.33894853808996e-05, 0.00023399128961875884, -4.587884618593318e-05], [-5.0500702593427645e-05, 0.00016748362866758049, -4.587884618593318e-05, 0.000264629682495723]])
   c_mass_diag_tools = diagonalise(c_mass_cov_array)
   c_mass_centers_mod = np.ones(4).astype(np.float64)

   print '\nTranslating parameters ...'
   Params = []
   for par in params_:
      Params.append(converted_parameter(par,blinding_))

   print '\nCompiling CUDA PDF ...'
   mod = cuRead("../../src/TimeDependent/Bs2KpiKpiTDPDF.cu", no_extern_c = True)
   CUDA_pdf_initializer = mod.get_function("initialize")
   CUDA_pdf = mod.get_function("evaluate")
   CUDA_max_mpdf = mod.get_function("find_max_mass_pdf")
   CUDA_int_mpdf = mod.get_function("compute_mass_integral")
   CUDA_compute_mint_array = mod.get_function("compute_mint_array")
   CUDA_set_mass_params = mod.get_function("set_mass_params")
   CUDA_set_mass_integrals = mod.get_function("set_mass_integrals")
   CUDA_compute_nw = mod.get_function("compute_nw")
   CUDA_set_nw_val = mod.get_function("set_nw_val")
   CUDA_compute_nwcov = mod.get_function("compute_nwcov")

   print '\nConverting datasets ...'
   data_arraylist = create_data_arrays(data_)
   if wide_window_: MCdatalist = [MCdata_2011_L0TIS_wide,MCdata_2011_L0noTIS_wide,MCdata_2012_L0TIS_wide,MCdata_2012_L0noTIS_wide]
   else: MCdatalist = [MCdata_2011_L0TIS_narrow,MCdata_2011_L0noTIS_narrow,MCdata_2012_L0TIS_narrow,MCdata_2012_L0noTIS_narrow]
   MCdata_arraylist = create_MCdata_arrays(MCdatalist)

   print '\nCreating categories ...'
   cat_name_list = ['11L0TIS','11L0noTIS','12L0TIS','12L0noTIS']
   cat_opt_list = [(0,0),(0,1),(1,0),(1,1)]
   options_arraylist = []
   options_arraylist.append(create_param_list('options_11L0TIS_list'))
   options_arraylist.append(create_param_list('options_11L0noTIS_list'))
   options_arraylist.append(create_param_list('options_12L0TIS_list'))
   options_arraylist.append(create_param_list('options_12L0noTIS_list'))
   cats = []
   for i in range(4):
      thiscat = Cat(cat_name_list[i], data_arraylist[i], getN = True)
      thiscat.year = cat_opt_list[i][0]
      thiscat.trig = cat_opt_list[i][1]
      thiscat.model_options = gpuarray.to_gpu(options_arraylist[i])
      thiscat.MCdata = MCdata_arraylist[i]
      thiscat.NMCevts = int(thiscat.MCdata.size/6.)
      thiscat.nwevout = np.ones(thiscat.NMCevts).astype(np.float64)
      thiscat.nwset = np.ones(380).astype(np.float64)
      thiscat.nwsetred = np.ones(nindnws).astype(np.float64)
      thiscat.nwcov = np.ones([nindnws,nindnws]).astype(np.float64)
      thiscat.nwsetmodred = np.ones(nindnws).astype(np.float64)
      thiscat.nwsetmod = np.ones(380).astype(np.float64)
      thiscat.block_nw = (block_size_nw,1,1)
      thiscat.grid_nw = getGrid_nw(thiscat)
      thiscat.block_fit = (block_size_fit,1,1)
      thiscat.grid_fit = getGrid_fit(thiscat)
      cats.append(thiscat)

   def my_getSumLL_large(cat): return gpuarray.sum(getattr(cat,"Probs"))
   def my_getSumLL_short(cat): return np.sum(getattr(cat,"Probs").get())
   def mySum1(thing): return np.float64(sum(thing))
   def mySum2(thing): return np.float64(sum(thing).get())

   def ctrt_fun_1(x,mu,sigma):
      return -(x-mu)*(x-mu)/(2.*sigma*sigma)

   def ctrt_fun_2(x_a,x_b,mu_a,mu_b,sigma_a,sigma_b,rho):
      return -1./(2.*(1-rho*rho))*((x_a-mu_a)*(x_a-mu_a)/sigma_a/sigma_a-2.*rho*(x_a-mu_a)*(x_b-mu_b)/sigma_a/sigma_b+(x_b-mu_b)*(x_b-mu_b)/sigma_b/sigma_b)

   check = np.ones(3).astype(np.float64)

   class CUDAModel(ParamBox):

      def __init__(self, pars, cats):
         ParamBox.__init__(self, pars, cats)
         sizes = []
         for k in cats: sizes.append(k.Nevts)
         if max(sizes) > THR:
            self.getSumLL = my_getSumLL_large
            self.mySum = mySum2
         else:
            self.getSumLL = my_getSumLL_short
            self.mySum = mySum1
         self.nw_computed = 0
         self.pdf = CUDA_pdf
         self.set_mass_params = CUDA_set_mass_params
         self.set_mass_integrals = CUDA_set_mass_integrals
         self.max_mpdf = CUDA_max_mpdf
         self.int_mpdf = CUDA_int_mpdf
         self.compute_mint_array = CUDA_compute_mint_array
         self.compute_nw = CUDA_compute_nw
         self.compute_nwcov = CUDA_compute_nwcov
         self.set_nw_val = CUDA_set_nw_val
         self.re_amps_list_cu = create_param_list("re_amps_list")
         self.dirCP_asyms_list_cu = create_param_list("dirCP_asyms_list")
         self.im_amps_list_cu = create_param_list("im_amps_list")
         self.weak_phases_list_cu = create_param_list("weak_phases_list")
         self.mixing_params_list_cu = create_param_list("mixing_params_list")
         self.calib_params_list_cu = create_param_list("calib_params_list")
         self.mass_integrals_list_cu = create_param_list('mass_integrals_11L0TIS_list',numparams = 9)
         CUDA_pdf_initializer(block = (1,1,1))

      def createFit(self):
         config = {}
         for par in self.params: config.update(par.getSettings())
         self.fit = Minuit(self, errordef=1, **config)

      def __call__(self,*args):

         chi2 = np.float64(0.)
         N = self.dc

         for [idx,ival] in param_list_updates("re_amps_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.re_amps_list_cu[idx] = ival
         for [idx,ival] in param_list_updates("dirCP_asyms_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.dirCP_asyms_list_cu[idx] = ival
         for [idx,ival] in param_list_updates("im_amps_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.im_amps_list_cu[idx] = ival
         for [idx,ival] in param_list_updates("weak_phases_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.weak_phases_list_cu[idx] = ival
         for [idx,ival] in param_list_updates("mixing_params_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.mixing_params_list_cu[idx] = ival
         for [idx,ival] in param_list_updates("calib_params_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.calib_params_list_cu[idx] = ival

         if var_nw_ or (not self.nw_computed):

            # Randomize c_mass_swave parameters (if needed).
            if var_nw_ == 0 and self.nw_computed == 0 and randomize_c_mass_ == 1:
               randomvary(c_mass_centers,c_mass_centers_mod,c_mass_diag_tools)
               self.calib_params_list_cu[22] = c_mass_centers_mod[0]
               self.calib_params_list_cu[23] = c_mass_centers_mod[1]
               self.calib_params_list_cu[24] = c_mass_centers_mod[2]
               self.calib_params_list_cu[25] = c_mass_centers_mod[3]
            self.set_mass_params(gpuarray.to_gpu(self.calib_params_list_cu),block = (1,1,1))

            # Compute normalisation mass integrals.
            for mpdfid in range(9):
               self.compute_mint_array(np.int32(mpdfid),np.int32(mintnpoints),np.float64(minthlimit),cudriver.Out(mintarray),block = block_mint,grid = grid_mint)
               self.mass_integrals_list_cu[mpdfid] = sum(mintarray)
            self.set_mass_integrals(gpuarray.to_gpu(self.mass_integrals_list_cu),block = (1,1,1))

            # Compute normalisation weights.
            for cat in self.cats:
               for inw in range(380):
                  j1_aux,j2_aux,h_aux,j1p_aux,j2p_aux,hp_aux,part_aux = extindex(inw)
                  self.compute_nw(gpuarray.to_gpu(cat.MCdata),np.int32(j1_aux),np.int32(j2_aux),np.int32(h_aux),np.int32(j1p_aux),np.int32(j2p_aux),np.int32(hp_aux),np.int32(part_aux),np.int32(cat.NMCevts),cudriver.Out(cat.nwevout),block = cat.block_nw,grid = cat.grid_nw)
                  cat.nwset[inw] = sum(cat.nwevout)
                  self.set_nw_val(np.float64(cat.nwset[inw]),np.int32(cat.year),np.int32(cat.trig),np.int32(inw),block = (1,1,1))

               # Randomise normalisation weights (if needed).
               if var_nw_ == 0 and self.nw_computed == 0 and randomize_nw_ == 1:
                  nwevoutlist = []
                  for inw in range(nindnws):
                     inw_instance = dict_nw_find_example[inw]
                     cat.nwsetred[inw] = cat.nwset[inw_instance]
                     j1_aux,j2_aux,h_aux,j1p_aux,j2p_aux,hp_aux,part_aux = extindex(inw_instance)
                     self.compute_nw(gpuarray.to_gpu(cat.MCdata),np.int32(j1_aux),np.int32(j2_aux),np.int32(h_aux),np.int32(j1p_aux),np.int32(j2p_aux),np.int32(hp_aux),np.int32(part_aux),np.int32(cat.NMCevts),cudriver.Out(cat.nwevout),block = cat.block_nw,grid = cat.grid_nw)
                     nwevoutlist += list(cat.nwevout)
                  nwevoutlist_array = np.array(nwevoutlist).astype(np.float64)
                  self.compute_nwcov(gpuarray.to_gpu(nwevoutlist_array),np.int32(cat.NMCevts),cudriver.Out(cat.nwcov),block = block_nwcov,grid = grid_nwcov)
                  nw_diag_tools = diagonalise(cat.nwcov)
                  randomvary(cat.nwsetred,cat.nwsetmodred,nw_diag_tools)
                  nwsetmodred_expanded = [0.]+list(cat.nwsetmodred)
                  for inw in range(380):
                     cat.nwsetmod[inw] = nwsetmodred_expanded[dict_nw_find_value[inw]]
                     self.set_nw_val(np.float64(cat.nwsetmod[inw]),np.int32(cat.year),np.int32(cat.trig),np.int32(inw),block = (1,1,1))

            self.nw_computed = 1

         for cat in self.cats: self.pdf(cat.data,cat.Probs,cudriver.Out(check),cat.model_options,gpuarray.to_gpu(self.re_amps_list_cu),gpuarray.to_gpu(self.dirCP_asyms_list_cu),gpuarray.to_gpu(self.im_amps_list_cu),gpuarray.to_gpu(self.weak_phases_list_cu),gpuarray.to_gpu(self.mixing_params_list_cu),gpuarray.to_gpu(self.calib_params_list_cu),gpuarray.to_gpu(self.mass_integrals_list_cu),cat.Nevts,block = cat.block_fit,grid = cat.grid_fit)

         LL = map(self.getSumLL, self.cats)
         LLsum = self.mySum(LL)
         LLsum += ctrt_fun_1(np.float64(args[N["Dp0half_SSK_cu"]]),-0.0079,0.0014)
         LLsum += ctrt_fun_1(np.float64(args[N["Dp1half_SSK_cu"]]),-0.022,0.023)
         LLsum += ctrt_fun_1(np.float64(args[N["Dp0half_OS_cu"]]),0.007,0.0006)
         LLsum += ctrt_fun_1(np.float64(args[N["Dp1half_OS_cu"]]),0.033,0.006)
         LLsum += ctrt_fun_2(np.float64(args[N["gamma_Bs_cu"]]),np.float64(args[N["delta_gamma_Bs_cu"]]),0.6643,0.083,0.0020,0.006,-0.217)
         LLsum += ctrt_fun_2(np.float64(args[N["p0metac_SSK_cu"]]),np.float64(args[N["p1_SSK_cu"]]),0.0067,0.925,0.0052,0.085,0.)
         LLsum += ctrt_fun_2(np.float64(args[N["p0metac_OS_cu"]]),np.float64(args[N["p1_OS_cu"]]),0.0062,0.982,0.0044,0.035,0.14)
         if wide_window_:
            LLsum += ctrt_fun_2(np.float64(args[N["tres_p0_2011_cu"]]),np.float64(args[N["tres_p1_2011_cu"]]),0.0347684584237,1.15385576866,0.000243952773379,0.0495706722963,0.37497)
            LLsum += ctrt_fun_2(np.float64(args[N["tres_p0_2012_cu"]]),np.float64(args[N["tres_p1_2012_cu"]]),0.0365026605725,1.26918356746,0.000250855432766,0.0528387031703,0.38357)
         else:
            LLsum += ctrt_fun_2(np.float64(args[N["tres_p0_2011_cu"]]),np.float64(args[N["tres_p1_2011_cu"]]),0.0352455552308,1.19983857817,0.000337800233389,0.0618110188611,0.39061)
            LLsum += ctrt_fun_2(np.float64(args[N["tres_p0_2012_cu"]]),np.float64(args[N["tres_p1_2012_cu"]]),0.0366294040913,1.22214099483,0.000296200532078,0.059802993325,0.39251)

         return -2*LLsum

   start = timer()

   print '\nConstructing fitting framework ...'
   manager = CUDAModel(Params, cats)

   if repeat_fit_for_nw_syst_:

      fnwsyst = open('nwsystfits.dat','w')
      fnwsyst.close()

      for iexp in range(nw_syst_N_iterations_):

         print 'Experiment #' + str(iexp)

         manager.createFit()
         manager.nw_computed = 0
         manager.fit.print_level = 0
         manager.fit.migrad()
         manager.fit.hesse()
      
         num_params = len(paramnames)
         cov_matrix = np.ones((num_params,num_params))
         central_vals = []
         for i in range(num_params):
            central_vals.append(manager.fit.values[paramnames[i]+'_cu'])
            for j in range(num_params): cov_matrix[i][j] = manager.fit.covariance[(paramnames[i]+'_cu',paramnames[j]+'_cu')]
         par_tuple = uncertainties.correlated_values(central_vals,cov_matrix)
         upar = {}
         for i in range(num_params): upar[paramnames[i]] = par_tuple[i]
         upar['reA110'] = 1.
         upar['imA110'] = 0.
         for par in max_strong_params:
            if par not in paramnames: upar[par] = 0.
         polarparamnames = []
         for par in polar_namepairs_dict.keys():
            if polar_namepairs_dict[par] in paramnames:
               par_temp = eval(polar_params_dict[par])
               if par_temp.std_dev > 1e-10:
                  polarparamnames.append(par)
                  upar[par] = par_temp

         output_string = ''
         for par in paramnames+polarparamnames: output_string += str(upar[par].nominal_value-par_result_varnw_dict[par][0]) + ' '
         output_string += '\n'
         fnwsyst = open('nwsystfits.dat','a')
         fnwsyst.write(output_string)
         fnwsyst.close()

      print '\nINFO:',int((timer() - start)/60),'min needed to do the study.'

   else:

      manager.createFit()
      manager.fit.migrad()
      manager.fit.hesse()
      if minos_: manager.fit.minos()
   
      num_params = len(paramnames)
      cov_matrix = np.ones((num_params,num_params))
      central_vals = []
      for i in range(num_params):
         central_vals.append(manager.fit.values[paramnames[i]+'_cu'])
         for j in range(num_params): cov_matrix[i][j] = manager.fit.covariance[(paramnames[i]+'_cu',paramnames[j]+'_cu')]
      par_tuple = uncertainties.correlated_values(central_vals,cov_matrix)
      upar = {}
      for i in range(num_params): upar[paramnames[i]] = par_tuple[i]
      upar['reA110'] = 1.
      upar['imA110'] = 0.
      for par in max_strong_params:
         if par not in paramnames: upar[par] = 0.
      polarparamnames = []
      for par in polar_namepairs_dict.keys():
         if polar_namepairs_dict[par] in paramnames:
            par_temp = eval(polar_params_dict[par])
            if par_temp.std_dev > 1e-10:
               polarparamnames.append(par)
               upar[par] = par_temp
   
      fitprint2LaTeX_CUDA(upar,wide_window_)
   
      for par in params_:
         if (("DCP" in par.GetName()) or ("phi" in par.GetName())) and blinding_: par.setVal(upar[par.GetName()].nominal_value-blinding_strings[par.GetName()])
         else: par.setVal(upar[par.GetName()].nominal_value)
   
      for par in params_:
         if ((not "DCP" in par.GetName()) and (not "phi" in par.GetName())): print '\t\t'+par.GetName()+'.setVal('+str(par.getVal())+')'
      print ''
   
      if output_file_name_ != "":
         par_result_dict = {}
         for par in paramnames+polarparamnames: par_result_dict[par] = (upar[par].nominal_value,upar[par].std_dev,par_name_dict[par].replace('#','\\'))
         fresult = open('_'+output_file_name_+'.py','w')
         fresult.write("par_result_dict = "+str(par_result_dict))
         fresult.close()
         print 'Fit results saved in _'+output_file_name_+'.py'
   
      print '\nINFO:',int((timer() - start)/60),'min needed to do the fit.'
   
      """c_mass_pars = ['c1_mass_swave','c2_mass_swave','c3_mass_swave','c4_mass_swave']
      c_mass_centers = np.ones(4).astype(np.float64)
      for i in range(4): c_mass_centers[i] = manager.fit.values[c_mass_pars[i]+'_cu']
      print c_mass_centers
      c_mass_cov = []
      for ipar in range(4):
         c_mass_cov.append([])
         for jpar in range(4): c_mass_cov[ipar].append(manager.fit.covariance[(c_mass_pars[ipar]+'_cu',c_mass_pars[jpar]+'_cu')])
      print c_mass_cov
      c_mass_cov_array = np.array(c_mass_cov)
      diag_tools = diagonalise(c_mass_cov_array)
      c_mass_centers_mod = np.ones(4).astype(np.float64)
      for i in range(6):
         randomvary(c_mass_centers,c_mass_centers_mod,diag_tools)
         print c_mass_centers_mod"""
   
      """h_phis = ROOT.TH1F("h_phis","h_phis",100,-5,5)
      for par in ['dphi_SS','dphi_SV','dphi_VS','dphi_ST','dphi_TS','dphi_VT','dphi_TV','dphi_TT']:
         d_phis = (upar[par].nominal_value-blinding_strings[par])/upar[par].std_dev
         print d_phis
         h_phis.Fill(d_phis)
   
      c_dCPV = ROOT.TCanvas("c_dCPV","c_dCPV")
      h_phis.Draw()
      c_dCPV.Print("dCPV.pdf")"""


def DoCUDAToy(N_exps,N_events,params_,wide_window_,output_tag,randomize_c_mass_):

   print "\n#####################################################################"
   print " P R E P A R I N G   C U D A   F R A M E W O R K"
   print "#####################################################################\n"

   import pycuda.autoinit
   import pycuda.cumath
   import pycuda.driver as cudriver
   import pycuda.gpuarray as gpuarray
   from iminuit import Minuit
   from ModelBricks import Parameter, Free, Cat, ParamBox, cuRead
   from tools import plt
   from timeit import default_timer as timer
   import uncertainties
   import uncertainties.umath as umath

   ROOT.RooRandom.randomGenerator().SetSeed(0)

   mintnpoints = 500
   mintnpoints2 = mintnpoints*mintnpoints
   if wide_window_: minthlimit = mHlimit
   else: minthlimit = 1050.
   mintarray = np.ones(mintnpoints2).astype(np.float64)

   for par in params_:
      if "DCP" in par.GetName(): par.setVal(0.)
      elif "phi" in par.GetName(): par.setVal(0.)

   block_size_mint = 510
   block_size_fit = 12*21
   THR = 1e06

   paramnames = []
   for par in params_: paramnames.append(par.GetName())

   def getGrid_mint():
      Nbunch = mintnpoints2 * 1. / block_size_mint
      if Nbunch > int(Nbunch): Nbunch = int(Nbunch) +1
      else : Nbunch = int(Nbunch)
      return  (Nbunch,1,1)

   def getGrid_fit(thiscat):
      Nbunch = thiscat.Nevts *1. / block_size_fit
      print "thiscat.Nevts, Nbunch = ", thiscat.Nevts, Nbunch
      if Nbunch > int(Nbunch): Nbunch = int(Nbunch) +1
      else : Nbunch = int(Nbunch)
      return  (Nbunch,1,1)

   block_mint = (block_size_mint,1,1)
   grid_mint = getGrid_mint()

   c_mass_centers = np.array([-0.29994255, -0.15854387, -0.12167263, -0.06586275]).astype(np.float64)
   c_mass_cov_array = np.array([[0.0003947516243460034, -7.661577933574582e-05, 0.00011979980192447234, -5.0500702593427645e-05], [-7.661577933574582e-05, 0.0003759673751610742, -7.33894853808996e-05, 0.00016748362866758049], [0.00011979980192447234, -7.33894853808996e-05, 0.00023399128961875884, -4.587884618593318e-05], [-5.0500702593427645e-05, 0.00016748362866758049, -4.587884618593318e-05, 0.000264629682495723]])
   c_mass_diag_tools = diagonalise(c_mass_cov_array)
   c_mass_centers_mod = np.ones(4).astype(np.float64)

   cats = []
   gen_data = np.ones((N_events,12)).astype(np.float64)
   thiscat = Cat("gen_cat", gen_data, getN = True)
   thiscat.block = (block_size_fit,1,1)
   thiscat.grid = getGrid_fit(thiscat)
   cats.append(thiscat)

   print '\nTranslating parameters ...'
   Params = []
   for par in params_:
      Params.append(converted_parameter(par,0))
   if wide_window_:
      Params.append(Parameter("m1_cu",1500, limits=(750,1600), constant = False, dtype = np.float64))
      Params.append(Parameter("m2_cu",896, limits=(750,1600), constant = False, dtype = np.float64))
   else:
      Params.append(Parameter("m1_cu",896, limits=(750,1050), constant = False, dtype = np.float64))
      Params.append(Parameter("m2_cu",896, limits=(750,1050), constant = False, dtype = np.float64))
   Params.append(Parameter("cos1_cu",0, limits=(-1,1), constant = False, dtype = np.float64))
   Params.append(Parameter("cos2_cu",0, limits=(-1,1), constant = False, dtype = np.float64))
   Params.append(Parameter("phi_cu",0, limits=(0,2*pi), constant = False, dtype = np.float64))
   Params.append(Parameter("t_cu",1, limits=(0,12), constant = False, dtype = np.float64))
   Params.append(Parameter("terror_cu",0.04, limits=(0,0.1), constant = False, dtype = np.float64))
   Params.append(Parameter("q_SSK_cu",0, limits=(-1,1), constant = True, dtype = np.int32))
   Params.append(Parameter("q_OS_cu",0, limits=(-1,1), constant = True, dtype = np.int32))
   Params.append(Parameter("eta_SSK_cu",0.3, limits=(0,0.5), constant = False, dtype = np.float64))
   Params.append(Parameter("eta_OS_cu",0.3, limits=(0,0.5), constant = False, dtype = np.float64))

   par_phys_names = []
   for par in paramnames: par_phys_names.append(par + "_cu")
   par_var_names = ["m1_cu","m2_cu","cos1_cu","cos2_cu","phi_cu","t_cu","terror_cu","eta_SSK_cu","eta_OS_cu"]
   par_phys_init_vals = {}
   for par in paramnames: par_phys_init_vals[par + "_cu"] = eval(par+'.getVal()')
   for par in polar_namepairs_dict.keys():
      if polar_namepairs_dict[par] in paramnames: par_phys_init_vals[par+'_cu'] = eval(init_polar_params_dict[par])
   par_ctrt_names = ["gamma_Bs_cu","delta_gamma_Bs_cu","p0metac_SSK_cu","p0metac_OS_cu","Dp0half_SSK_cu","Dp0half_OS_cu","p1_SSK_cu","p1_OS_cu","Dp1half_SSK_cu","Dp1half_OS_cu","tres_p0_2012_cu","tres_p1_2012_cu"]
   par_ctrt_init_vals = {}
   toyparamnames = []
   for par in paramnames:
      if par not in ["tres_p0_2011","tres_p1_2011"]: toyparamnames.append(par)

   print '\nCompiling CUDA PDF ...'
   mod = cuRead("../../src/TimeDependent/Bs2KpiKpiTDPDF.cu", no_extern_c = True)
   CUDA_initialize = mod.get_function("initialize")
   CUDA_set_generator = mod.get_function("set_generator")
   CUDA_max_P_eta_SSK = mod.get_function("get_max_P_eta_SSK")
   CUDA_max_P_eta_OS = mod.get_function("get_max_P_eta_OS")
   CUDA_evaluate_cond = mod.get_function("evaluate_CondPDF")
   CUDA_set_mass_params = mod.get_function("set_mass_params")
   CUDA_compute_mint_array = mod.get_function("compute_mint_array")
   CUDA_compute_acc_mint_array = mod.get_function("compute_acc_mint_array")
   CUDA_set_mass_integrals = mod.get_function("set_mass_integrals")
   CUDA_set_all_mass_integrals = mod.get_function("set_all_mass_integrals")
   CUDA_generate = mod.get_function("generateEvent")
   CUDA_evaluate_toy = mod.get_function("evaluate_toy")

   def my_getSumLL_large(cat): return gpuarray.sum(getattr(cat,"Probs"))
   def my_getSumLL_short(cat): return np.sum(getattr(cat,"Probs").get())
   def mySum1(thing): return np.float64(sum(thing))
   def mySum2(thing): return np.float64(sum(thing).get())

   def ctrt_fun_1(x,mu,sigma):
      return -(x-mu)*(x-mu)/(2.*sigma*sigma)

   def ctrt_fun_2(x_a,x_b,mu_a,mu_b,sigma_a,sigma_b,rho):
      return -1./(2.*(1-rho*rho))*((x_a-mu_a)*(x_a-mu_a)/sigma_a/sigma_a-2.*rho*(x_a-mu_a)*(x_b-mu_b)/sigma_a/sigma_b+(x_b-mu_b)*(x_b-mu_b)/sigma_b/sigma_b)

   class CUDAModel(ParamBox):

      def __init__(self, pars, cats):

         ParamBox.__init__(self, pars, cats)
         sizes = []
         for k in cats: sizes.append(k.Nevts)
         if max(sizes) > THR:
            self.getSumLL = my_getSumLL_large
            self.mySum = mySum2
         else:
            self.getSumLL = my_getSumLL_short
            self.mySum = mySum1

         self.gen_step = 0

         self.max_eta_SSK_pdf = np.ones(1).astype(np.float64)
         self.max_eta_OS_pdf = np.ones(1).astype(np.float64)
         self.get_max_SSK_eta_distr = CUDA_max_P_eta_SSK
         self.get_max_OS_eta_distr = CUDA_max_P_eta_OS

         self.max_cond_ll = gpuarray.to_gpu(np.ones(1).astype(np.float64))
         self.max_cond_pdf = 0
         self.pdf_cond = CUDA_evaluate_cond

         self.set_mass_params = CUDA_set_mass_params
         self.compute_mint_array = CUDA_compute_mint_array
         self.compute_acc_mint_array = CUDA_compute_acc_mint_array
         self.set_mass_integrals = CUDA_set_mass_integrals
         self.set_all_mass_integrals = CUDA_set_all_mass_integrals

         self.ev_gen = CUDA_generate

         self.pdf_toy = CUDA_evaluate_toy

         self.options_list_cu = create_param_list("options_list")
         self.re_amps_list_cu = create_param_list("re_amps_list")
         self.dirCP_asyms_list_cu = create_param_list("dirCP_asyms_list")
         self.im_amps_list_cu = create_param_list("im_amps_list")
         self.weak_phases_list_cu = create_param_list("weak_phases_list")
         self.mixing_params_list_cu = create_param_list("mixing_params_list")
         self.calib_params_list_cu = create_param_list("calib_params_list")
         self.cond_distr_params_list_cu = create_param_list("cond_distr_params_list")
         self.mass_integrals_list_cu = create_param_list("mass_integrals_list")
         self.ang_integrals_list_cu = create_param_list("ang_integrals_list")

         self.re_amps_list_cu_gen = create_param_list("re_amps_list")
         self.dirCP_asyms_list_cu_gen = create_param_list("dirCP_asyms_list")
         self.im_amps_list_cu_gen = create_param_list("im_amps_list")
         self.weak_phases_list_cu_gen = create_param_list("weak_phases_list")
         self.mixing_params_list_cu_gen = create_param_list("mixing_params_list")
         self.calib_params_list_cu_gen = create_param_list("calib_params_list")
         self.mass_integrals_list_cu_gen = create_param_list("mass_integrals_list")

         self.lock_to_init(["tres_p0_2011_cu","tres_p1_2011_cu"])

         CUDA_initialize(block = (1,1,1))
         CUDA_set_generator(gpuarray.to_gpu(self.options_list_cu),gpuarray.to_gpu(self.re_amps_list_cu_gen),gpuarray.to_gpu(self.dirCP_asyms_list_cu_gen),gpuarray.to_gpu(self.im_amps_list_cu_gen),gpuarray.to_gpu(self.weak_phases_list_cu_gen),gpuarray.to_gpu(self.mixing_params_list_cu_gen),gpuarray.to_gpu(self.calib_params_list_cu_gen),gpuarray.to_gpu(self.cond_distr_params_list_cu),gpuarray.to_gpu(self.mass_integrals_list_cu_gen),gpuarray.to_gpu(self.ang_integrals_list_cu),block = (1,1,1))

      def createFit(self):
         config = {}
         for par in self.params: config.update(par.getSettings())
         self.fit = Minuit(self, errordef=1, **config)

      def set_gen_step(self,num,q1_=0,q2_=0):

         for par in par_phys_names: self.Params[par].setVal(par_phys_init_vals[par])
         self.gen_step = num

         if self.gen_step == 0:

            self.calib_params_list_cu_gen[22] = c_mass_centers[0]
            self.calib_params_list_cu_gen[23] = c_mass_centers[1]
            self.calib_params_list_cu_gen[24] = c_mass_centers[2]
            self.calib_params_list_cu_gen[25] = c_mass_centers[3]
            self.calib_params_list_cu[22] = c_mass_centers[0]
            self.calib_params_list_cu[23] = c_mass_centers[1]
            self.calib_params_list_cu[24] = c_mass_centers[2]
            self.calib_params_list_cu[25] = c_mass_centers[3]
            self.set_mass_params(gpuarray.to_gpu(self.calib_params_list_cu_gen),block = (1,1,1))

            for imint in range(9):
               self.compute_mint_array(np.int32(imint),np.int32(mintnpoints),np.float64(minthlimit),cudriver.Out(mintarray),block = block_mint,grid = grid_mint)
               self.mass_integrals_list_cu_gen[imint] = sum(mintarray)
            self.set_mass_integrals(gpuarray.to_gpu(self.mass_integrals_list_cu_gen),block = (1,1,1))
            for imint in range(30):
               self.compute_acc_mint_array(np.int32(imint),np.int32(0),np.int32(mintnpoints),np.float64(minthlimit),cudriver.Out(mintarray),block = block_mint,grid = grid_mint)
               self.mass_integrals_list_cu_gen[9+imint] = sum(mintarray)
            for imint in range(21):
               self.compute_acc_mint_array(np.int32(imint),np.int32(1),np.int32(mintnpoints),np.float64(minthlimit),cudriver.Out(mintarray),block = block_mint,grid = grid_mint)
               self.mass_integrals_list_cu_gen[9+30+imint] = sum(mintarray)
            self.set_all_mass_integrals(gpuarray.to_gpu(self.mass_integrals_list_cu_gen),block = (1,1,1))

         if self.gen_step == 1:
            self.Params["q_SSK_cu"].setVal(q1_)
            self.Params["q_OS_cu"].setVal(q2_)
            self.freeThese(par_var_names)
            self.lock_to_init(par_phys_names)
            self.freeThese(par_ctrt_names)
            if q1_ == 0:
               self.Params["eta_SSK_cu"].setVal(0.5)
               self.lock_to_init(["eta_SSK_cu"])
            if q2_ == 0:
               self.Params["eta_OS_cu"].setVal(0.5)
               self.lock_to_init(["eta_OS_cu"])

         if self.gen_step == 2:

            d_temp = ctrt_gamma_Bs_delta_gamma_Bs.generate(ROOT.RooArgSet(gamma_Bs,delta_gamma_Bs),1).get(0)
            self.mixing_params_list_cu_gen[1] = d_temp.getRealValue("gamma_Bs")
            self.mixing_params_list_cu_gen[2] = d_temp.getRealValue("delta_gamma_Bs")
            self.calib_params_list_cu_gen[2] = ctrt_Dp0half_SSK.generate(ROOT.RooArgSet(Dp0half_SSK),1).get(0).getRealValue("Dp0half_SSK")
            self.calib_params_list_cu_gen[3] = ctrt_Dp0half_OS.generate(ROOT.RooArgSet(Dp0half_OS),1).get(0).getRealValue("Dp0half_OS")
            self.calib_params_list_cu_gen[6] = ctrt_Dp1half_SSK.generate(ROOT.RooArgSet(Dp1half_SSK),1).get(0).getRealValue("Dp1half_SSK")
            self.calib_params_list_cu_gen[7] = ctrt_Dp1half_OS.generate(ROOT.RooArgSet(Dp1half_OS),1).get(0).getRealValue("Dp1half_OS")
            d_temp = ctrt_p0metac_SSK_p1_SSK.generate(ROOT.RooArgSet(p0metac_SSK,p1_SSK),1).get(0)
            self.calib_params_list_cu_gen[0] = d_temp.getRealValue("p0metac_SSK")
            self.calib_params_list_cu_gen[4] = d_temp.getRealValue("p1_SSK")
            d_temp = ctrt_p0metac_OS_p1_OS.generate(ROOT.RooArgSet(p0metac_OS,p1_OS),1).get(0)
            self.calib_params_list_cu_gen[1] = d_temp.getRealValue("p0metac_OS")
            self.calib_params_list_cu_gen[5] = d_temp.getRealValue("p1_OS")
            if wide_window_: d_temp = ctrt_tres_p0_tres_p1_2012_wide.generate(ROOT.RooArgSet(tres_p0_2012,tres_p1_2012),1).get(0)
            else: d_temp = ctrt_tres_p0_tres_p1_2012_narrow.generate(ROOT.RooArgSet(tres_p0_2012,tres_p1_2012),1).get(0)
            self.calib_params_list_cu_gen[14] = d_temp.getRealValue("tres_p0_2012")
            self.calib_params_list_cu_gen[15] = d_temp.getRealValue("tres_p1_2012")

            par_ctrt_init_vals["gamma_Bs_cu"] = self.mixing_params_list_cu_gen[1]
            par_ctrt_init_vals["delta_gamma_Bs_cu"] = self.mixing_params_list_cu_gen[2]
            par_ctrt_init_vals["Dp0half_SSK_cu"] = self.calib_params_list_cu_gen[2]
            par_ctrt_init_vals["Dp0half_OS_cu"] = self.calib_params_list_cu_gen[3]
            par_ctrt_init_vals["Dp1half_SSK_cu"] = self.calib_params_list_cu_gen[6]
            par_ctrt_init_vals["Dp1half_OS_cu"] = self.calib_params_list_cu_gen[7]
            par_ctrt_init_vals["p0metac_SSK_cu"] = self.calib_params_list_cu_gen[0]
            par_ctrt_init_vals["p1_SSK_cu"] = self.calib_params_list_cu_gen[4]
            par_ctrt_init_vals["p0metac_OS_cu"] = self.calib_params_list_cu_gen[1]
            par_ctrt_init_vals["p1_OS_cu"] = self.calib_params_list_cu_gen[5]
            par_ctrt_init_vals["tres_p0_2012_cu"] = self.calib_params_list_cu_gen[14]
            par_ctrt_init_vals["tres_p1_2012_cu"] = self.calib_params_list_cu_gen[15]

            CUDA_set_generator(gpuarray.to_gpu(self.options_list_cu),gpuarray.to_gpu(self.re_amps_list_cu_gen),gpuarray.to_gpu(self.dirCP_asyms_list_cu_gen),gpuarray.to_gpu(self.im_amps_list_cu_gen),gpuarray.to_gpu(self.weak_phases_list_cu_gen),gpuarray.to_gpu(self.mixing_params_list_cu_gen),gpuarray.to_gpu(self.calib_params_list_cu_gen),gpuarray.to_gpu(self.cond_distr_params_list_cu),gpuarray.to_gpu(self.mass_integrals_list_cu_gen),gpuarray.to_gpu(self.ang_integrals_list_cu),block = (1,1,1))

         if self.gen_step == 3:
            for par in ["gamma_Bs_cu","delta_gamma_Bs_cu","Dp0half_SSK_cu","Dp0half_OS_cu","Dp1half_SSK_cu","Dp1half_OS_cu","p0metac_SSK_cu","p1_SSK_cu","p0metac_OS_cu","p1_OS_cu","tres_p0_2012_cu","tres_p1_2012_cu"]: self.Params[par].setVal(par_ctrt_init_vals[par])
            self.freeThese(par_phys_names)
            self.lock_to_init(par_var_names)
            self.lock_to_init(["tres_p0_2011_cu","tres_p1_2011_cu"])

            if randomize_c_mass_ == 1:
               randomvary(c_mass_centers,c_mass_centers_mod,c_mass_diag_tools)
               self.calib_params_list_cu[22] = c_mass_centers_mod[0]
               self.calib_params_list_cu[23] = c_mass_centers_mod[1]
               self.calib_params_list_cu[24] = c_mass_centers_mod[2]
               self.calib_params_list_cu[25] = c_mass_centers_mod[3]
            else:
               self.calib_params_list_cu[22] = c_mass_centers[0]
               self.calib_params_list_cu[23] = c_mass_centers[1]
               self.calib_params_list_cu[24] = c_mass_centers[2]
               self.calib_params_list_cu[25] = c_mass_centers[3]
            self.set_mass_params(gpuarray.to_gpu(self.calib_params_list_cu),block = (1,1,1))

            for imint in range(9):
               self.compute_mint_array(np.int32(imint),np.int32(mintnpoints),np.float64(minthlimit),cudriver.Out(mintarray),block = block_mint,grid = grid_mint)
               self.mass_integrals_list_cu[imint] = sum(mintarray)
            self.set_mass_integrals(gpuarray.to_gpu(self.mass_integrals_list_cu),block = (1,1,1))
            for imint in range(30):
               self.compute_acc_mint_array(np.int32(imint),np.int32(0),np.int32(mintnpoints),np.float64(minthlimit),cudriver.Out(mintarray),block = block_mint,grid = grid_mint)
               self.mass_integrals_list_cu[9+imint] = sum(mintarray)
            for imint in range(21):
               self.compute_acc_mint_array(np.int32(imint),np.int32(1),np.int32(mintnpoints),np.float64(minthlimit),cudriver.Out(mintarray),block = block_mint,grid = grid_mint)
               self.mass_integrals_list_cu[9+30+imint] = sum(mintarray)
            self.set_all_mass_integrals(gpuarray.to_gpu(self.mass_integrals_list_cu),block = (1,1,1))

      def generate(self):
         cat = self.cats[0]
         self.ev_gen(cat.data,np.float64(self.max_eta_SSK_pdf[0]),np.float64(self.max_eta_OS_pdf[0]),np.float64(self.max_cond_pdf),np.int32(cat.Nevts),block = cat.block,grid = cat.grid)

      def __call__(self,*args):

         chi2 = np.float64(0.)
         N = self.dc

         if self.gen_step == 1:
            m1_ran = np.float64(args[N["m1_cu"]])
            m2_ran = np.float64(args[N["m2_cu"]])
            cos1_ran = np.float64(args[N["cos1_cu"]])
            cos2_ran = np.float64(args[N["cos2_cu"]])
            phi_ran = np.float64(args[N["phi_cu"]])
            t_ran = np.float64(args[N["t_cu"]])
            terror_ran = np.float64(args[N["terror_cu"]])
            q_SSK_ran = np.int32(args[N["q_SSK_cu"]])
            q_OS_ran = np.int32(args[N["q_OS_cu"]])
            eta_SSK_ran = np.float64(args[N["eta_SSK_cu"]])
            eta_OS_ran = np.float64(args[N["eta_OS_cu"]])

            for [idx,ival] in param_list_updates("mixing_params_list",paramnames,args_ = args,N_ = N,blinding = 0): self.mixing_params_list_cu[idx] = ival
            for [idx,ival] in param_list_updates("calib_params_list",paramnames,args_ = args,N_ = N,blinding = 0): self.calib_params_list_cu[idx] = ival
            self.pdf_cond(m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran,t_ran,terror_ran,q_SSK_ran,q_OS_ran,eta_SSK_ran,eta_OS_ran,gpuarray.to_gpu(self.mixing_params_list_cu),gpuarray.to_gpu(self.calib_params_list_cu),self.max_cond_ll,block = (1,1,1))
            return -2*self.max_cond_ll[0].get()

         elif self.gen_step == 3:
            for [idx,ival] in param_list_updates("re_amps_list",paramnames,args_ = args,N_ = N,blinding = 0): self.re_amps_list_cu[idx] = ival
            for [idx,ival] in param_list_updates("dirCP_asyms_list",paramnames,args_ = args,N_ = N,blinding = 0): self.dirCP_asyms_list_cu[idx] = ival
            for [idx,ival] in param_list_updates("im_amps_list",paramnames,args_ = args,N_ = N,blinding = 0): self.im_amps_list_cu[idx] = ival
            for [idx,ival] in param_list_updates("weak_phases_list",paramnames,args_ = args,N_ = N,blinding = 0): self.weak_phases_list_cu[idx] = ival
            for [idx,ival] in param_list_updates("mixing_params_list",paramnames,args_ = args,N_ = N,blinding = 0): self.mixing_params_list_cu[idx] = ival
            for [idx,ival] in param_list_updates("calib_params_list",paramnames,args_ = args,N_ = N,blinding = 0): self.calib_params_list_cu[idx] = ival
            for cat in self.cats:
               self.pdf_toy(cat.data,cat.Probs,gpuarray.to_gpu(self.re_amps_list_cu),gpuarray.to_gpu(self.dirCP_asyms_list_cu),gpuarray.to_gpu(self.im_amps_list_cu),gpuarray.to_gpu(self.weak_phases_list_cu),gpuarray.to_gpu(self.mixing_params_list_cu),gpuarray.to_gpu(self.calib_params_list_cu),cat.Nevts,block = cat.block,grid = cat.grid)
            LL = map(self.getSumLL, self.cats)
            LLsum = self.mySum(LL)
            LLsum += ctrt_fun_1(np.float64(args[N["Dp0half_SSK_cu"]]),-0.0079,0.0014)
            LLsum += ctrt_fun_1(np.float64(args[N["Dp1half_SSK_cu"]]),-0.022,0.023)
            LLsum += ctrt_fun_1(np.float64(args[N["Dp0half_OS_cu"]]),0.007,0.0006)
            LLsum += ctrt_fun_1(np.float64(args[N["Dp1half_OS_cu"]]),0.033,0.006)
            LLsum += ctrt_fun_2(np.float64(args[N["gamma_Bs_cu"]]),np.float64(args[N["delta_gamma_Bs_cu"]]),0.6643,0.083,0.0020,0.006,-0.217)
            LLsum += ctrt_fun_2(np.float64(args[N["p0metac_SSK_cu"]]),np.float64(args[N["p1_SSK_cu"]]),0.0067,0.925,0.0052,0.085,0.)
            LLsum += ctrt_fun_2(np.float64(args[N["p0metac_OS_cu"]]),np.float64(args[N["p1_OS_cu"]]),0.0062,0.982,0.0044,0.035,0.14)
            if wide_window_:
               LLsum += ctrt_fun_2(np.float64(args[N["tres_p0_2012_cu"]]),np.float64(args[N["tres_p1_2012_cu"]]),0.0365026605725,1.26918356746,0.000250855432766,0.0528387031703,0.38357)
            else:
               LLsum += ctrt_fun_2(np.float64(args[N["tres_p0_2012_cu"]]),np.float64(args[N["tres_p1_2012_cu"]]),0.0366294040913,1.22214099483,0.000296200532078,0.059802993325,0.39251)
            return -2*LLsum

   manager = CUDAModel(Params, cats)

   print '\nComputing generation mass integrals ...'
   manager.set_gen_step(0)

   print '\nComputing conditional pdf maximum ...'
   pdf_maxima = []
   for q1_ in [-1,0,1]:
      for q2_ in [-1,0,1]:
         manager.set_gen_step(1,q1_,q2_)
         manager.createFit()
         manager.fit.print_level = 0
         manager.fit.migrad()
         pdf_maxima.append(exp(manager.max_cond_ll[0].get()))
   manager.max_cond_pdf = 1.2*max(pdf_maxima)
   manager.get_max_SSK_eta_distr(cudriver.Out(manager.max_eta_SSK_pdf),block = (1,1,1))
   manager.get_max_OS_eta_distr(cudriver.Out(manager.max_eta_OS_pdf),block = (1,1,1))

   print '\nPerforming the studies ...\n'

   fpulls_dat = open('pulls_'+output_tag+'.dat','w')
   fpulls_dat.close()

   N_submitted = 0
   N_successful = 0

   start = timer()

   while N_successful < N_exps:

      iexp = N_successful+1

      print 'MCS INFO ---> Generating sample #'+str(iexp)
      manager.set_gen_step(2)
      print manager.calib_params_list_cu_gen
      print manager.mass_integrals_list_cu_gen
      manager.createFit()
      manager.generate()
      s = ""
      for ev in range(N_events):
         for v in range(12): s += str(1*manager.cats[0].data[ev][v]) + " "
         s += "\n"
      fdata = open('tmp.dat','w')
      fdata.write(s)
      fdata.close()
      gROOT.Reset()
      fout = ROOT.TFile("tmp.root","RECREATE")
      tout = ROOT.TTree("DecayTree","DecayTree")
      tout.ReadFile("tmp.dat",dec_SSK_name+":"+dec_OS_name+":"+eta_SSK_name+":"+eta_OS_name+":"+m1_name+":"+m2_name+":"+cos1_name+":"+cos2_name+":"+phi_name+":"+t_name+":"+terror_name+":sweight")
      tout.Write()
      fout.Close()
      os.system("rm tmp.dat")

      print 'MCS INFO ---> Fitting sample #'+str(iexp)
      manager.set_gen_step(3)
      print manager.calib_params_list_cu
      print manager.mass_integrals_list_cu
      manager.createFit()
      manager.fit.print_level = 0
      manager.fit.migrad()

      N_submitted += 1
      if manager.fit.get_fmin().is_valid:
         manager.fit.hesse()
         N_successful += 1

         num_params = len(toyparamnames)
         cov_matrix = np.ones((num_params,num_params))
         central_vals = []
         for i in range(num_params):
            central_vals.append(manager.fit.values[toyparamnames[i]+'_cu'])
            for j in range(num_params): cov_matrix[i][j] = manager.fit.covariance[(toyparamnames[i]+'_cu',toyparamnames[j]+'_cu')]
         par_tuple = uncertainties.correlated_values(central_vals,cov_matrix)
         upar = {}
         for i in range(num_params): upar[toyparamnames[i]] = par_tuple[i]
         upar['reA110'] = 1.
         upar['imA110'] = 0.
         for par in max_strong_params:
            if par not in toyparamnames: upar[par] = 0.
         polarparamnames = []
         for par in polar_namepairs_dict.keys():
            if polar_namepairs_dict[par] in toyparamnames:
               par_temp = eval(polar_params_dict[par])
               if par_temp.std_dev > 1e-10:
                  polarparamnames.append(par)
                  upar[par] = par_temp

         allparamnames = []
         for par in toyparamnames: allparamnames.append(par)
         for par in polarparamnames: allparamnames.append(par)

         pull_string = ''
         for ipar in range(len(allparamnames)):
            par_name = allparamnames[ipar]
            x_par = upar[par_name].nominal_value
            if par_name+'_cu' in par_ctrt_init_vals.keys(): x0_par = par_ctrt_init_vals[par_name+'_cu']
            else: x0_par = par_phys_init_vals[par_name+'_cu']
            sigma_par = upar[par_name].std_dev*par_result_varnw_dict[par_name][1]/par_result_constnw_dict[par_name][1]
            pull_par = (x_par-x0_par)/sigma_par
            pull_string += str(pull_par)+' '
         fpulls_dat = open('pulls_'+output_tag+'.dat','a')
         fpulls_dat.write(pull_string+'\n')
         fpulls_dat.close()
      else: print 'WARNING: Fit failed. Repeating the experiment.'

   print 'INFO:',int((timer() - start)/60),'min needed to do the experiments.'
   print 'Fraction of valid fits:',float(N_successful)/float(N_submitted)

   gROOT.Reset()
   fout = ROOT.TFile("pulls_"+output_tag+".root","RECREATE")
   tout = ROOT.TTree("Pulls","Pulls")
   s = allparamnames[0]+'_pull'
   for i in range(1,len(allparamnames)): s += ':'+allparamnames[i]+'_pull'
   tout.ReadFile("pulls_"+output_tag+".dat",s)
   tout.Write()
   fout.Close()


def PDFfun(PDF_,method_,m1_,m2_,cos1_,cos2_,phi_,t_,dt_,q1_,q2_,eta1_,eta2_):

   # Function to transform the fitting PDF into an independent usable function.

   mKp1_ini = mKp1.getVal()
   mKp2_ini = mKp2.getVal()
   mKp1_narrowwin_ini = mKp1_narrowwin.getVal()
   mKp2_narrowwin_ini = mKp2_narrowwin.getVal()
   cos1_ini = cos1.getVal()
   cos2_ini = cos2.getVal()
   phi_ini = phi.getVal()
   t_ini = t.getVal()
   terror_ini = terror.getVal()
   decision_SSK_ini = decision_SSK.getIndex()
   decision_OS_ini = decision_OS.getIndex()
   etamistag_SSK_ini = etamistag_SSK.getVal()
   etamistag_OS_ini = etamistag_OS.getVal()

   mKp1.setVal(m1_)
   mKp2.setVal(m2_)
   mKp1_narrowwin.setVal(m1_)
   mKp2_narrowwin.setVal(m2_)
   cos1.setVal(cos1_)
   cos2.setVal(cos2_)
   phi.setVal(phi_)
   t.setVal(t_)
   terror.setVal(dt_)
   decision_SSK.setIndex(q1_)
   decision_OS.setIndex(q2_)
   etamistag_SSK.setVal(eta1_)
   etamistag_OS.setVal(eta2_)

   res = eval('PDF_.'+method_)

   mKp1.setVal(mKp1_ini)
   mKp2.setVal(mKp2_ini)
   mKp1_narrowwin.setVal(mKp1_narrowwin_ini)
   mKp2_narrowwin.setVal(mKp2_narrowwin_ini)
   cos1.setVal(cos1_ini)
   cos2.setVal(cos2_ini)
   phi.setVal(phi_ini)
   t.setVal(t_ini)
   terror.setVal(terror_ini)
   decision_SSK.setIndex(decision_SSK_ini)
   decision_OS.setIndex(decision_OS_ini)
   etamistag_SSK.setVal(etamistag_SSK_ini)
   etamistag_OS.setVal(etamistag_OS_ini)

   return res

def errorscan(PDF_,method_):
   n = 5
   nt = 5
   t0 = 0
   tlimit = 12
   errors_nan = 0
   errors_neg = 0
   error_list = []
   counter = 0
   total = (n+1)**8*(nt+1)*9
   for i_m1 in range(n+1):
      for i_m2 in range(n+1):
         for i_cos1 in range(n+1):
            for i_cos2 in range(n+1):
               for i_phi in range(n+1):
                  for i_t in range(nt+1):
                     for i_dt in range(n+1):
                        for i_q1 in range(-1,2):
                           for i_q2 in range(-1,2):
                              for i_eta1 in range(n+1):
                                 for i_eta2 in range(n+1):
                                    if np.isnan(PDFfun(PDF_,method_,750.+float(i_m1)/n*(1050.-750.),750.+float(i_m2)/n*(1050.-750.),-1.+float(i_cos1)/n*2.,-1.+float(i_cos2)/n*2.,float(i_phi)/n*2.*3.141593,t0+float(i_t)/nt*(tlimit-t0),float(i_dt)/n*0.08,i_q1,i_q2,float(i_eta1)/n*0.5,float(i_eta2)/n*0.5)):
                                       errors_nan += 1
                                       error_list.append([750.+float(i_m1)/n*(1050.-750.),750.+float(i_m2)/n*(1050.-750.),-1.+float(i_cos1)/n*2.,-1.+float(i_cos2)/n*2.,-3.141593+float(i_phi)/n*2.*3.141593,t0+float(i_t)/nt*(tlimit-t0),float(i_dt)/n*0.08,i_q1,i_q2,float(i_eta1)/n*0.5,float(i_eta2)/n*0.5])
                                    elif (PDFfun(PDF_,method_,750.+float(i_m1)/n*(1050.-750.),750.+float(i_m2)/n*(1050.-750.),-1.+float(i_cos1)/n*2.,-1.+float(i_cos2)/n*2.,-3.141593+float(i_phi)/n*2.*3.141593,t0+float(i_t)/nt*(tlimit-t0),float(i_dt)/n*0.08,i_q1,i_q2,float(i_eta1)/n*0.5,float(i_eta2)/n*0.5) < 0.):
                                       errors_neg += 1
                                       error_list.append([750.+float(i_m1)/n*(1050.-750.),750.+float(i_m2)/n*(1050.-750.),-1.+float(i_cos1)/n*2.,-1.+float(i_cos2)/n*2.,-3.141593+float(i_phi)/n*2.*3.141593,t0+float(i_t)/nt*(tlimit-t0),float(i_dt)/n*0.08,i_q1,i_q2,float(i_eta1)/n*0.5,float(i_eta2)/n*0.5])
                                    counter += 1.
                                    if (float(counter)%(float(total)/20.) <= 1.):
                                       print '%.1f'%(counter/total*100.)+' % scanned.'
                                       print 750.+float(i_m1)/n*(1050.-750.),750.+float(i_m2)/n*(1050.-750.),-1.+float(i_cos1)/n*2.,-1.+float(i_cos2)/n*2.,-3.141593+float(i_phi)/n*2.*3.141593,t0+float(i_t)/nt*(tlimit-t0),float(i_dt)/n*0.08,i_q1,i_q2,float(i_eta1)/n*0.5,float(i_eta2)/n*0.5
   for i in error_list: print i
   print str(errors_nan)+' NaN errors found.'
   print str(errors_neg)+' neg. PDF errors found.'
   return

def stringline(name,listpar,blinded):
   var = 0
   for par in listpar:
      if par.GetName() == name: var = [str(par.getTitle()),par.getVal(),par.getError()]
   if var != 0:
      if (("DCP" in name) or ("phi" in name)) and blinded: return '$'+var[0]+'$ & $xxx$ & %.4f'%var[2]+' \\\\\n'
      else: return '$'+var[0]+'$ & %.4f'%var[1]+' & %.4f'%var[2]+' \\\\\n'
   else: return ''

def stringline_prop(fitresult,par):
   return '$'+par.GetTitle()+'$ & %.4f'%par.getVal()+' & %.4f'%par.getPropagatedError(fitresult)+' \\\\\n'

def printresultoldformat(fitresult):

   print '************************************'
   print 'fL =',round(fL11.getVal(),3),'+-',round(fL11.getPropagatedError(fitresult),3)
   print 'fparallel =',round(fpar11.getVal(),3),'+-',round(fpar11.getPropagatedError(fitresult),3)
   print '|As-|2 =',round(sqmodAsminusnorm.getVal(),3),'+-',round(sqmodAsminusnorm.getPropagatedError(fitresult),3)
   print '|As+|2 =',round(sqmodAsplusnorm.getVal(),3),'+-',round(sqmodAsplusnorm.getPropagatedError(fitresult),3)
   print '|Ass|2 =',round(sqmodA00norm.getVal(),3),'+-',round(sqmodA00norm.getPropagatedError(fitresult),3)
   print 'deltaparallel =',round(deltaA11par.getVal(),2),'+-',round(deltaA11par.getPropagatedError(fitresult),2)
   print 'deltaperp-deltasplus =',round(deltaA11perpAsplus.getVal(),2),'+-',round(deltaA11perpAsplus.getPropagatedError(fitresult),2)
   print 'deltasminus =',round(deltaAsminus.getVal(),2),'+-',round(deltaAsminus.getPropagatedError(fitresult),2)
   print 'deltass =',round(deltaA00.getVal(),2),'+-',round(deltaA00.getPropagatedError(fitresult),2)
   print '************************************'

def fitprint2LaTeX(filename,parameters,wide_window,noCP,blinded,mixing_params_fixed,calib_params_fixed):
	partext = '\\documentclass[11pt,a4paper]{article}\n\\usepackage[left=2.5cm,top=2.5cm,right=2.5cm,bottom=2.5cm]{geometry}\n\n\\begin{document}\n\n\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|c|}\n\hline\nParameter & Value & Stat. uncertainty \\\\\n\\hline\n\\hline\n'
	if (not noCP) or (not mixing_params_fixed): partext += '\\multicolumn{3}{|c|}{Common parameters}\\\\\n\\hline\n\\hline\n'
	if not noCP:
		partext += stringline("phis",parameters,blinded)
		partext += stringline("DCP",parameters,blinded)
	if not mixing_params_fixed:
		partext += stringline("delta_m_Bs",parameters,blinded)
		partext += stringline("gamma_Bs",parameters,blinded)
		partext += stringline("delta_gamma_Bs",parameters,blinded)
	if (not noCP) or (not mixing_params_fixed): partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{3}{|c|}{$B_{s}^{0}\\to K^{*}(892)^{0}\\bar{K}^{*}(892)^{0}$ (VV)}\\\\\n\\hline\n\\hline\n'
	partext += stringline("f_VV",parameters,blinded)
	partext += stringline("fL_VV",parameters,blinded)
	partext += stringline("xpar_VV",parameters,blinded)
	partext += stringline("delta11par",parameters,blinded)
	partext += stringline("delta11perp",parameters,blinded)
	partext += stringline("DCP",parameters,blinded)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{3}{|c|}{Single $S-wave$ (SV and VS)}\\\\\n\\hline\n\\hline\n'
	partext += stringline("f_Swave",parameters,blinded)
	partext += stringline("D_SVVS",parameters,blinded)
	partext += stringline("delta01",parameters,blinded)
	partext += stringline("delta10",parameters,blinded)
	partext += stringline("DCP_SV",parameters,blinded)
	partext += stringline("DCP_VS",parameters,blinded)
	partext += stringline("dphi_SV",parameters,blinded)
	partext += stringline("dphi_VS",parameters,blinded)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{3}{|c|}{Double $S-wave$ (SS)}\\\\\n\\hline\n\\hline\n'
	partext += stringline("f_SS",parameters,blinded)
	partext += stringline("delta00",parameters,blinded)
	partext += stringline("DCP_SS",parameters,blinded)
	partext += stringline("dphi_SS",parameters,blinded)
	partext += '\\hline\n\\hline\n'
	if wide_window:
		partext += '\\multicolumn{3}{|c|}{Single $D-wave$ (VT and TV)}\\\\\n\\hline\n\\hline\n'
		partext += stringline("f_VTTV",parameters,blinded)
		partext += stringline("D_VTTV",parameters,blinded)
		partext += stringline("fL_VT",parameters,blinded)
		partext += stringline("fL_TV",parameters,blinded)
		partext += stringline("xpar_VT",parameters,blinded)
		partext += stringline("xpar_TV",parameters,blinded)
		partext += stringline("delta120",parameters,blinded)
		partext += stringline("delta210",parameters,blinded)
		partext += stringline("delta12par",parameters,blinded)
		partext += stringline("delta21par",parameters,blinded)
		partext += stringline("delta12perp",parameters,blinded)
		partext += stringline("delta21perp",parameters,blinded)
		partext += stringline("DCP_VT",parameters,blinded)
		partext += stringline("DCP_TV",parameters,blinded)
		partext += stringline("dphi_VT",parameters,blinded)
		partext += stringline("dphi_TV",parameters,blinded)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{Double $D-wave$ (TT)}\\\\\n\\hline\n\\hline\n'
		partext += stringline("f_TT",parameters,blinded)
		partext += stringline("fL_TT",parameters,blinded)
		partext += stringline("xpar1_TT",parameters,blinded)
		partext += stringline("xperp1_TT",parameters,blinded)
		partext += stringline("xpar2_TT",parameters,blinded)
		partext += stringline("delta220",parameters,blinded)
		partext += stringline("delta22par",parameters,blinded)
		partext += stringline("delta22perp",parameters,blinded)
		partext += stringline("delta22par2",parameters,blinded)
		partext += stringline("delta22perp2",parameters,blinded)
		partext += stringline("DCP_TT",parameters,blinded)
		partext += stringline("dphi_TT",parameters,blinded)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{$Scalar-Tensor$ decays (ST and TS)}\\\\\n\\hline\n\\hline\n'
		partext += stringline("D_STTS",parameters,blinded)
		partext += stringline("delta02",parameters,blinded)
		partext += stringline("delta20",parameters,blinded)
		partext += stringline("DCP_ST",parameters,blinded)
		partext += stringline("DCP_TS",parameters,blinded)
		partext += stringline("dphi_ST",parameters,blinded)
		partext += stringline("dphi_TS",parameters,blinded)
		partext += '\\hline\n\\hline\n'
	partext += '\\end{tabular}\n\\end{table}\n\n'
	if not calib_params_fixed:
		partext += '\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|c|}\n\hline\nParameter & Value & Stat. uncertainty \\\\\n\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{SSK tagger}\\\\\n\\hline\n\\hline\n'
		partext += stringline("p0metac_SSK",parameters,blinded)
		partext += stringline("Dp0half_SSK",parameters,blinded)
		partext += stringline("p1_SSK",parameters,blinded)
		partext += stringline("Dp1half_SSK",parameters,blinded)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{OS tagger}\\\\\n\\hline\n\\hline\n'
		partext += stringline("p0metac_OS",parameters,blinded)
		partext += stringline("Dp0half_OS",parameters,blinded)
		partext += stringline("p1_OS",parameters,blinded)
		partext += stringline("Dp1half_OS",parameters,blinded)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{Time resolution}\\\\\n\\hline\n\\hline\n'
		partext += stringline("tres_p0_2011",parameters,blinded)
		partext += stringline("tres_p1_2011",parameters,blinded)
		partext += stringline("tres_p0_2012",parameters,blinded)
		partext += stringline("tres_p1_2012",parameters,blinded)
		partext += '\\hline\n\\hline\n\\end{tabular}\n\\end{table}\n\n'
	partext += '\\end{document}'
	partext = partext.replace('#','\\')
	partext = partext.replace('\\hline\n\\end{tabular}','\\end{tabular}')

	texfile = open(filename+'.tex','w')
	texfile.write(partext)
	texfile.close()

def CondVarStudy(fit_bool,model_,parameters_,data_,hist_mistag_SSK_,hist_mistag_OS_,hist_deltat_):

	if fit_bool:
		hist_mistag_SSK_.plotOn(frame_eta_SSK,ROOT.RooFit.Binning(25))
		hist_mistag_OS_.plotOn(frame_eta_OS,ROOT.RooFit.Binning(25))
		hist_deltat_.plotOn(frame_terr,ROOT.RooFit.Binning(25))
		for i in observables: i.setConstant(1)
		for i in observables_narrowwin: i.setConstant(1)
		for i in parameters_: i.setConstant(1)

		# Fit of the t_err distribution.
		for i in [gamma1_dt,beta1_dt]: i.setConstant(0)
		alt_fit.setVal(1)
		model_.fitTo(hist_deltat_,ROOT.RooFit.Minos(1))
		model_.plotOn(frame_terr)
		for i in [gamma1_dt,beta1_dt]: i.setConstant(1)

		# Fit of the eta_SSK distribution.
		for i in [mu1_SSK,sigma1_SSK,c_SSK,mu2_SSK,sigma2_SSK]: i.setConstant(0)
		alt_fit.setVal(2)
		model_.fitTo(hist_mistag_SSK_,ROOT.RooFit.Minos(1))
		model_.plotOn(frame_eta_SSK)
		for i in [mu1_SSK,sigma1_SSK,c_SSK,mu2_SSK,sigma2_SSK]: i.setConstant(1)

		# Fit of the eta_OS distribution.
		for i in [mu1_OS,sigma1_OS,c_OS,mu2_OS,sigma2_OS]: i.setConstant(0)
		alt_fit.setVal(3)
		model_.fitTo(hist_mistag_OS_,ROOT.RooFit.Minos(1))
		model_.plotOn(frame_eta_OS)
		for i in [mu1_OS,sigma1_OS,c_OS,mu2_OS,sigma2_OS]: i.setConstant(1)

		alt_fit.setVal(0)
		for i in observables: i.setConstant(0)
		for i in observables_narrowwin: i.setConstant(0)
		for i in parameters_: i.setConstant(0)

		# Plot of the resulting distributions.
		c_cond = ROOT.TCanvas("c_cond","c_cond",1800,600)
		c_cond.Divide(3)
		c_cond.cd(1)
		frame_eta_SSK.Draw()
		c_cond.cd(2)
		frame_eta_OS.Draw()
		c_cond.cd(3)
		frame_terr.Draw()
		c_cond.Print("plotCondVar.root")
		c_cond.Print("plotCondVar.pdf")

def genTree(nevents,model,output_tag):
	print 'Generating events ...'
	d_ = model.generate(FullArgSet,nevents)
	print 'Events generated.'
	d_.write("tmp.dat")
	gROOT.Reset()
	fout = ROOT.TFile(output_tag + "_" + str(nevents) + "ev.root","RECREATE")
	tout = ROOT.TTree("DecayTree","DecayTree")
	tout.ReadFile("tmp.dat",m1_name+":"+m2_name+":"+cos1_name+":"+cos2_name+":"+phi_name+":"+t_name+":"+terror_name+":"+dec_SSK_name+":"+dec_OS_name+":"+eta_SSK_name+":"+eta_OS_name)
	tout.Write()
	fout.Close()
	os.system("rm tmp.dat")

def doToyMCStudy(nexp,neve,model,output_tag,job_id,GRID,num_CPU,minos_opt,strategy_option,wide_window,fix_mixing,fix_calib):

	ROOT.RooRandom.randomGenerator().SetSeed(0)

	start = time.time()

	pdf_arglist = ROOT.RooArgList(model)
	ctrtvar_argset = ROOT.RooArgSet()

	if fix_mixing:
		if fix_calib:
			MCS = ROOT.RooMCStudy(model,FullArgSet,ROOT.RooFit.Silence(),ROOT.RooFit.FitOptions(ROOT.RooFit.NumCPU(num_CPU),ROOT.RooFit.Minos(minos_opt),ROOT.RooFit.Strategy(strategy_option),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE)))
			print 'Mixing and calibration parameters fixed during the toy studies.'
		else:
			map(lambda x:pdf_arglist.add(x),[ctrt_p0metac_SSK_p1_SSK,ctrt_p0metac_OS_p1_OS,ctrt_Dp0half_SSK,ctrt_Dp1half_SSK,ctrt_Dp0half_OS,ctrt_Dp1half_OS])
			if wide_window: map(lambda x:pdf_arglist.add(x),[ctrt_tres_p0_tres_p1_2011_wide,ctrt_tres_p0_tres_p1_2012_wide])
			else: map(lambda x:pdf_arglist.add(x),[ctrt_tres_p0_tres_p1_2011_narrow,ctrt_tres_p0_tres_p1_2012_narrow])
			map(lambda x:ctrtvar_argset.add(x),[p0metac_SSK,Dp0half_SSK,p1_SSK,Dp1half_SSK,p0metac_OS,Dp0half_OS,p1_OS,Dp1half_OS,tres_p0_2011,tres_p1_2011,tres_p0_2012,tres_p1_2012])
			model_constrained = ROOT.RooProdPdf("model_constrained","model_constrained",pdf_arglist)
			MCS = ROOT.RooMCStudy(model_constrained,FullArgSet,ROOT.RooFit.Constrain(ctrtvar_argset),ROOT.RooFit.Silence(),ROOT.RooFit.FitOptions(ROOT.RooFit.NumCPU(num_CPU),ROOT.RooFit.Minos(minos_opt),ROOT.RooFit.Strategy(strategy_option),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE)))
			print 'Mixing parameters fixed during the toy studies. Calibration parameters gaussian constrained.'

	else:
		if fix_calib:
			map(lambda x:pdf_arglist.add(x),[ctrt_gamma_Bs_delta_gamma_Bs])
			map(lambda x:ctrtvar_argset.add(x),[gamma_Bs,delta_gamma_Bs])
			model_constrained = ROOT.RooProdPdf("model_constrained","model_constrained",pdf_arglist)
			MCS = ROOT.RooMCStudy(model_constrained,FullArgSet,ROOT.RooFit.Constrain(ctrtvar_argset),ROOT.RooFit.Silence(),ROOT.RooFit.FitOptions(ROOT.RooFit.NumCPU(num_CPU),ROOT.RooFit.Minos(minos_opt),ROOT.RooFit.Strategy(strategy_option),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE)))
			print 'Calibration parameters fixed during the toy studies. Mixing parameters gaussian constrained.'
		else:
			map(lambda x:pdf_arglist.add(x),[ctrt_gamma_Bs_delta_gamma_Bs,ctrt_p0metac_SSK_p1_SSK,ctrt_p0metac_OS_p1_OS,ctrt_Dp0half_SSK,ctrt_Dp1half_SSK,ctrt_Dp0half_OS,ctrt_Dp1half_OS])
			if wide_window: map(lambda x:pdf_arglist.add(x),[ctrt_tres_p0_tres_p1_2011_wide,ctrt_tres_p0_tres_p1_2012_wide])
			else: map(lambda x:pdf_arglist.add(x),[ctrt_tres_p0_tres_p1_2011_narrow,ctrt_tres_p0_tres_p1_2012_narrow])
			map(lambda x:ctrtvar_argset.add(x),[gamma_Bs,delta_gamma_Bs,p0metac_SSK,Dp0half_SSK,p1_SSK,Dp1half_SSK,p0metac_OS,Dp0half_OS,p1_OS,Dp1half_OS,tres_p0_2011,tres_p1_2011,tres_p0_2012,tres_p1_2012])
			model_constrained = ROOT.RooProdPdf("model_constrained","model_constrained",pdf_arglist)
			MCS = ROOT.RooMCStudy(model_constrained,FullArgSet,ROOT.RooFit.Constrain(ctrtvar_argset),ROOT.RooFit.Silence(),ROOT.RooFit.FitOptions(ROOT.RooFit.NumCPU(num_CPU),ROOT.RooFit.Minos(minos_opt),ROOT.RooFit.Strategy(strategy_option),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE)))
			print 'Mixing and calibration parameters gaussian constrained during the toy studies.'

	MCS.generateAndFit(nexp,neve)

	fout_MCS = ROOT.TFile("MCS.root","RECREATE")
	tout_MCS = ROOT.TTree("tree","tree")

	strl = [ "_init", "_valu", "_erro", "_errl", "_errh", "_pull" ]

	parlist = []
	fitResult = MCS.fitResult(0)
	for par in range( 0, fitResult.floatParsFinal().getSize() ):
		param = fitResult.floatParsFinal().at(par)
		for ii in range(0,len(strl)):
			parlist.append( MyStructF() )
			tout_MCS.Branch( param.GetName()+strl[ii], AddressOf(parlist[len(strl)*par+ii],'afloat'), param.GetName()+strl[ii]+"/F" )

	branches = tout_MCS.GetListOfBranches()

	for iter in range(0,nexp):
		fitResult = MCS.fitResult(iter)
		for par in range( 0, fitResult.floatParsFinal().getSize() ):
			pull = 0.
			val_ini = fitResult.floatParsInit().at(par).getVal()
			val_fit = fitResult.floatParsFinal().at(par).getVal()
			errlo	 = fitResult.floatParsFinal().at(par).getErrorLo()
			errhi	 = fitResult.floatParsFinal().at(par).getErrorHi()
			if ( abs(errlo*errhi) > 0. ):
				delta = val_fit - val_ini
				if ( delta < 0. ):
					pull =	delta / errhi
				else:
					pull = -delta / errlo
			param = fitResult.floatParsFinal().at(par)
			parlist[len(strl)*par+0].afloat = val_ini
			parlist[len(strl)*par+1].afloat = param.getVal()
			parlist[len(strl)*par+2].afloat = param.getError()
			parlist[len(strl)*par+3].afloat = param.getErrorLo() # =AsymmErrorLo if MINOS, =-Error if only HESSE
			parlist[len(strl)*par+4].afloat = param.getErrorHi() # =AsymmErrorHi if MINOS, =+Error if only HESSE
			parlist[len(strl)*par+5].afloat = pull
			
		tout_MCS.Fill()

	tout_MCS.Write()
	fout_MCS.Close()

	end = time.time()
	print 'Process finished in',(end - start)/60.,'min.'

def MCSGrid(nexp,neve,njob,output_tag,GRID):
	os.system('ganga SendExperimentsGanga.py ' + str(neve) + ' ' + str(nexp) + ' ' + str(njob) + ' ' + output_tag + ' ' + str(GRID))

def genprint2LaTeX(filename,parameters):
	partext = '\\documentclass[11pt,a4paper]{article}\n\\usepackage[left=2.5cm,top=2.5cm,right=2.5cm,bottom=2.5cm]{geometry}\n\n\\begin{document}\n\n\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|}\n\hline\nParameter & Value \\\\\n\\hline\n'
	texfile = open('latex/'+filename+'.tex','w')
	for par in parameters: partext += '$'+str(par.getTitle())+'$ & '+str(par.getVal())+' \\\\\n\\hline\n'
	partext += '\\end{tabular}\n\\end{table}\n\n\\end{document}'
	partext = partext.replace('#','\\')
	texfile.write(partext)
	texfile.close()

def printllprofile(parameter,nll):
	frame = parameter.frame(ROOT.RooFit.Title(parameter.GetName()))
	nll.plotOn(frame,ROOT.RooFit.PrintEvalErrors(0),ROOT.RooFit.ShiftToZero(),ROOT.RooFit.LineColor(kRed))
	c = ROOT.TCanvas("c_"+parameter.GetName(),"c_"+parameter.GetName())
	frame.Draw()
	c.Print("plotllprofile_" + parameter.GetName() + ".root")

def plot61Ddata(data, step, wide_window = 1, mbinning = 40, cosbinning = 40, phibinning = 40, tbinning = 40):

	if wide_window:
		data.plotOn(frame_m1,ROOT.RooFit.Name("data_"+str(step)),ROOT.RooFit.Binning(mbinning))
		data.plotOn(frame_m2,ROOT.RooFit.Name("data_"+str(step)),ROOT.RooFit.Binning(mbinning))
	else:
		data.plotOn(frame_m1_narrowwin,ROOT.RooFit.Name("data_"+str(step)),ROOT.RooFit.Binning(mbinning))
		data.plotOn(frame_m2_narrowwin,ROOT.RooFit.Name("data_"+str(step)),ROOT.RooFit.Binning(mbinning))
	data.plotOn(frame_cos1,ROOT.RooFit.Name("data_"+str(step)),ROOT.RooFit.Binning(cosbinning))
	data.plotOn(frame_cos2,ROOT.RooFit.Name("data_"+str(step)),ROOT.RooFit.Binning(cosbinning))
	data.plotOn(frame_phi,ROOT.RooFit.Name("data_"+str(step)),ROOT.RooFit.Binning(phibinning))
	data.plotOn(frame_t,ROOT.RooFit.Name("data_"+str(step)),ROOT.RooFit.Binning(tbinning))

def plot61Dmodel(model, normdata, wide_window = 1, color = kGray+2):

	if wide_window:
		model.plotOn(frame_m1,ROOT.RooFit.Name("model"),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(color),ROOT.RooFit.LineWidth(4))
		model.plotOn(frame_m2,ROOT.RooFit.Name("model"),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(color),ROOT.RooFit.LineWidth(4))
	else:
		model.plotOn(frame_m1_narrowwin,ROOT.RooFit.Name("model"),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(color),ROOT.RooFit.LineWidth(4))
		model.plotOn(frame_m2_narrowwin,ROOT.RooFit.Name("model"),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(color),ROOT.RooFit.LineWidth(4))
	model.plotOn(frame_cos1,ROOT.RooFit.Name("model"),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(color),ROOT.RooFit.LineWidth(4))
	model.plotOn(frame_cos2,ROOT.RooFit.Name("model"),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(color),ROOT.RooFit.LineWidth(4))
	model.plotOn(frame_phi,ROOT.RooFit.Name("model"),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(color),ROOT.RooFit.LineWidth(4))
	model.plotOn(frame_t,ROOT.RooFit.Name("model"),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(color),ROOT.RooFit.LineWidth(4))

def plot61Dcomponent(model, normdata, wide_window, compname, linecolor, linestyle):

	print '\nPlotting component '+compname+':\n'

	compdict = {'VV':10,'SS':11,'SV':12,'VS':13,'ST':14,'TS':15,'VT':16,'TV':17,'TT':18}
	compid = compdict[compname]

	component(compid,compid,compid,compid,compid,compid)
	if wide_window:
		model.plotOn(frame_m1,ROOT.RooFit.Name("model_comp_"+compname),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(linecolor),ROOT.RooFit.LineStyle(linestyle),ROOT.RooFit.LineWidth(2))
		model.plotOn(frame_m2,ROOT.RooFit.Name("model_comp_"+compname),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(linecolor),ROOT.RooFit.LineStyle(linestyle),ROOT.RooFit.LineWidth(2))
	else:
		model.plotOn(frame_m1_narrowwin,ROOT.RooFit.Name("model_comp_"+compname),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(linecolor),ROOT.RooFit.LineStyle(linestyle),ROOT.RooFit.LineWidth(2))
		model.plotOn(frame_m2_narrowwin,ROOT.RooFit.Name("model_comp_"+compname),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(linecolor),ROOT.RooFit.LineStyle(linestyle),ROOT.RooFit.LineWidth(2))
	model.plotOn(frame_cos1,ROOT.RooFit.Name("model_comp_"+compname),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(linecolor),ROOT.RooFit.LineStyle(linestyle),ROOT.RooFit.LineWidth(2))
	model.plotOn(frame_cos2,ROOT.RooFit.Name("model_comp_"+compname),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(linecolor),ROOT.RooFit.LineStyle(linestyle),ROOT.RooFit.LineWidth(2))
	model.plotOn(frame_phi,ROOT.RooFit.Name("model_comp_"+compname),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(linecolor),ROOT.RooFit.LineStyle(linestyle),ROOT.RooFit.LineWidth(2))
	model.plotOn(frame_t,ROOT.RooFit.Name("model_comp_"+compname),ROOT.RooFit.ProjWData(ROOT.RooArgSet(yeartrigcat),normdata),ROOT.RooFit.DrawOption("c"),ROOT.RooFit.LineColor(linecolor),ROOT.RooFit.LineStyle(linestyle),ROOT.RooFit.LineWidth(2))
	component(9,9,9,9,9,9)

def create61Dcanvas(wide_window,leg61D):

	leg61D.AddEntry(frame_t.findObject("data_0"),"Run I data","epl")
	leg61D.AddEntry(frame_t.findObject("model"),"Full model","l")
	leg61D.AddEntry(frame_t.findObject("model_comp_VV"),"B_{s}^{0} #rightarrow K^{*0}#bar{K}^{*0}","l")
	leg61D.AddEntry(frame_t.findObject("model_comp_SV"),"B_{s}^{0} #rightarrow (K^{+}#pi^{-})_{0}#bar{K}^{*0}","l")
	leg61D.AddEntry(frame_t.findObject("model_comp_VS"),"B_{s}^{0} #rightarrow K^{*0}(K^{-}#pi^{+})_{0}","l")
	leg61D.AddEntry(frame_t.findObject("model_comp_SS"),"B_{s}^{0} #rightarrow (K^{+}#pi^{-})_{0}(K^{-}#pi^{+})_{0}","l")

	if wide_window:
		leg61D.AddEntry(frame_t.findObject("model_comp_VT"),"B_{s}^{0} #rightarrow K^{*0}#bar{K}^{*}_{2}(1430)^{0}","l")
		leg61D.AddEntry(frame_t.findObject("model_comp_TV"),"B_{s}^{0} #rightarrow K^{*}_{2}(1430)^{0}#bar{K}^{*0}","l")
		leg61D.AddEntry(frame_t.findObject("model_comp_ST"),"B_{s}^{0} #rightarrow (K^{+}#pi^{-})_{0}#bar{K}^{*}_{2}(1430)^{0}","l")
		leg61D.AddEntry(frame_t.findObject("model_comp_TS"),"B_{s}^{0} #rightarrow K^{*}_{2}(1430)^{0}(K^{-}#pi^{+})_{0}","l")
		leg61D.AddEntry(frame_t.findObject("model_comp_TT"),"B_{s}^{0} #rightarrow K^{*}_{2}(1430)^{0}#bar{K}^{*}_{2}(1430)^{0}","l")
	c1 = ROOT.TCanvas("c1","c1",1000,800)
	c1.Divide(2,3)
	c1.cd(1)
	if wide_window: frame_m1.Draw()
	else: frame_m1_narrowwin.Draw()
	#c1.cd(1).SetLogy(1)
	c1.cd(2)
	if wide_window: frame_m2.Draw()
	else: frame_m2_narrowwin.Draw()
	#c1.cd(2).SetLogy(1)
	c1.cd(3)
	frame_cos1.Draw()
	c1.cd(4)
	frame_cos2.Draw()
	c1.cd(5)
	frame_phi.Draw()
	c1.cd(6)
	frame_t.Draw()
	leg61D.Draw()

	if wide_window:
		printPlot(mKp1,frame_m1)
		printPlot(mKp2,frame_m2)
	else:
		printPlot(mKp1_narrowwin,frame_m1_narrowwin)
		printPlot(mKp2_narrowwin,frame_m2_narrowwin)
	printPlot(cos1,frame_cos1)
	printPlot(cos2,frame_cos2)
	printPlot(phi,frame_phi)
	printPlot(t,frame_t)

	return c1

def fitprint2LaTeX_ReAImA(filename,parameters,wide_window,noCP,blinded,mixing_params_fixed,calib_params_fixed):
	partext = '\\documentclass[11pt,a4paper]{article}\n\\usepackage[left=2.5cm,top=2.5cm,right=2.5cm,bottom=2.5cm]{geometry}\n\n\\begin{document}\n\n\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|c|}\n\hline\nParameter & Value & Stat. uncertainty \\\\\n\\hline\n\\hline\n'
	if (not noCP) or (not mixing_params_fixed): partext += '\\multicolumn{3}{|c|}{Common parameters}\\\\\n\\hline\n\\hline\n'
	if not noCP:
		partext += stringline("phis",parameters,blinded)
		partext += stringline("DCP",parameters,blinded)
	if not mixing_params_fixed:
		partext += stringline("delta_m_Bs",parameters,blinded)
		partext += stringline("gamma_Bs",parameters,blinded)
		partext += stringline("delta_gamma_Bs",parameters,blinded)
	if (not noCP) or (not mixing_params_fixed): partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{3}{|c|}{$B_{s}^{0}\\to K^{*}(892)^{0}\\bar{K}^{*}(892)^{0}$ (VV)}\\\\\n\\hline\n\\hline\n'
	partext += stringline("reA11par",parameters,blinded)
	partext += stringline("imA11par",parameters,blinded)
	partext += stringline("reA11perp",parameters,blinded)
	partext += stringline("imA11perp",parameters,blinded)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{3}{|c|}{Single $S-wave$ (SV and VS)}\\\\\n\\hline\n\\hline\n'
	partext += stringline("reA01",parameters,blinded)
	partext += stringline("imA01",parameters,blinded)
	partext += stringline("reA10",parameters,blinded)
	partext += stringline("imA10",parameters,blinded)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{3}{|c|}{Double $S-wave$ (SS)}\\\\\n\\hline\n\\hline\n'
	partext += stringline("reA00",parameters,blinded)
	partext += stringline("imA00",parameters,blinded)
	partext += '\\hline\n\\hline\n'
	if wide_window:
		partext += '\\multicolumn{3}{|c|}{Single $D-wave$ (VT and TV)}\\\\\n\\hline\n\\hline\n'
		partext += stringline("reA120",parameters,blinded)
		partext += stringline("imA120",parameters,blinded)
		partext += stringline("reA12par",parameters,blinded)
		partext += stringline("imA12par",parameters,blinded)
		partext += stringline("reA12perp",parameters,blinded)
		partext += stringline("imA12perp",parameters,blinded)
		partext += stringline("reA210",parameters,blinded)
		partext += stringline("imA210",parameters,blinded)
		partext += stringline("reA21par",parameters,blinded)
		partext += stringline("imA21par",parameters,blinded)
		partext += stringline("reA21perp",parameters,blinded)
		partext += stringline("imA21perp",parameters,blinded)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{Double $D-wave$ (TT)}\\\\\n\\hline\n\\hline\n'
		partext += stringline("reA220",parameters,blinded)
		partext += stringline("imA220",parameters,blinded)
		partext += stringline("reA22par",parameters,blinded)
		partext += stringline("imA22par",parameters,blinded)
		partext += stringline("reA22perp",parameters,blinded)
		partext += stringline("imA22perp",parameters,blinded)
		partext += stringline("reA22par2",parameters,blinded)
		partext += stringline("imA22par2",parameters,blinded)
		partext += stringline("reA22perp2",parameters,blinded)
		partext += stringline("imA22perp2",parameters,blinded)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{$Scalar-Tensor$ decays (ST and TS)}\\\\\n\\hline\n\\hline\n'
		partext += stringline("reA02",parameters,blinded)
		partext += stringline("imA02",parameters,blinded)
		partext += stringline("reA20",parameters,blinded)
		partext += stringline("imA20",parameters,blinded)
		partext += '\\hline\n\\hline\n'
	partext += '\\end{tabular}\n\\end{table}\n\n'
	if not calib_params_fixed:
		partext += '\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|c|}\n\hline\nParameter & Value & Stat. uncertainty \\\\\n\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{SSK tagger}\\\\\n\\hline\n\\hline\n'
		partext += stringline("p0metac_SSK",parameters,blinded)
		partext += stringline("Dp0half_SSK",parameters,blinded)
		partext += stringline("p1_SSK",parameters,blinded)
		partext += stringline("Dp1half_SSK",parameters,blinded)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{OS tagger}\\\\\n\\hline\n\\hline\n'
		partext += stringline("p0metac_OS",parameters,blinded)
		partext += stringline("Dp0half_OS",parameters,blinded)
		partext += stringline("p1_OS",parameters,blinded)
		partext += stringline("Dp1half_OS",parameters,blinded)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{Time resolution}\\\\\n\\hline\n\\hline\n'
		partext += stringline("tres_p0_2011",parameters,blinded)
		partext += stringline("tres_p1_2011",parameters,blinded)
		partext += stringline("tres_p0_2012",parameters,blinded)
		partext += stringline("tres_p1_2012",parameters,blinded)
		partext += '\\hline\n\\hline\n\\end{tabular}\n\\end{table}\n\n'
	partext += '\\end{document}'
	partext = partext.replace('#','\\')
	partext = partext.replace('\\hline\n\\end{tabular}','\\end{tabular}')

	texfile = open(filename+'_ReAImA.tex','w')
	texfile.write(partext)
	texfile.close()

def fitprint2LaTeX_Polar(fitresult,filename,parameters,wide_window,noCP,blinded,mixing_params_fixed,calib_params_fixed):
	partext = '\\documentclass[11pt,a4paper]{article}\n\\usepackage[left=2.5cm,top=2.5cm,right=2.5cm,bottom=2.5cm]{geometry}\n\n\\begin{document}\n\n\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|c|}\n\hline\nParameter & Value & Stat. uncertainty \\\\\n\\hline\n\\hline\n'
	if (not noCP) or (not mixing_params_fixed): partext += '\\multicolumn{3}{|c|}{Common parameters}\\\\\n\\hline\n\\hline\n'
	if not noCP:
		partext += stringline("phis",parameters,blinded)
		partext += stringline("DCP",parameters,blinded)
	if not mixing_params_fixed:
		partext += stringline("delta_m_Bs",parameters,blinded)
		partext += stringline("gamma_Bs",parameters,blinded)
		partext += stringline("delta_gamma_Bs",parameters,blinded)
	if (not noCP) or (not mixing_params_fixed): partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{3}{|c|}{$B_{s}^{0}\\to K^{*}(892)^{0}\\bar{K}^{*}(892)^{0}$ (VV)}\\\\\n\\hline\n\\hline\n'
	partext += stringline_prop(fitresult,sqmodA11norm)
	partext += stringline_prop(fitresult,fL11)
	partext += stringline_prop(fitresult,fpar11)
	partext += stringline_prop(fitresult,deltaA11par)
	partext += stringline_prop(fitresult,deltaA11perp)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{3}{|c|}{Single $S-wave$ (SV and VS)}\\\\\n\\hline\n\\hline\n'
	partext += stringline_prop(fitresult,sqmodA01norm)
	partext += stringline_prop(fitresult,sqmodA10norm)
	partext += stringline_prop(fitresult,deltaA01)
	partext += stringline_prop(fitresult,deltaA10)
	partext += '\\hline\n\\hline\n'
	partext += '\\multicolumn{3}{|c|}{Double $S-wave$ (SS)}\\\\\n\\hline\n\\hline\n'
	partext += stringline_prop(fitresult,sqmodA00norm)
	partext += stringline_prop(fitresult,deltaA00)
	partext += '\\hline\n\\hline\n'
	if wide_window:
		partext += '\\multicolumn{3}{|c|}{Single $D-wave$ (VT and TV)}\\\\\n\\hline\n\\hline\n'
		partext += stringline_prop(fitresult,sqmodA12norm)
		partext += stringline_prop(fitresult,fL12)
		partext += stringline_prop(fitresult,fpar12)
		partext += stringline_prop(fitresult,sqmodA21norm)
		partext += stringline_prop(fitresult,fL21)
		partext += stringline_prop(fitresult,fpar21)
		partext += stringline_prop(fitresult,deltaA120)
		partext += stringline_prop(fitresult,deltaA12par)
		partext += stringline_prop(fitresult,deltaA12perp)
		partext += stringline_prop(fitresult,deltaA210)
		partext += stringline_prop(fitresult,deltaA21par)
		partext += stringline_prop(fitresult,deltaA21perp)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{Double $D-wave$ (TT)}\\\\\n\\hline\n\\hline\n'
		partext += stringline_prop(fitresult,sqmodA22norm)
		partext += stringline_prop(fitresult,fL22)
		partext += stringline_prop(fitresult,fpar22)
		partext += stringline_prop(fitresult,fperp22)
		partext += stringline_prop(fitresult,fpar222)
		partext += stringline_prop(fitresult,deltaA220)
		partext += stringline_prop(fitresult,deltaA22par)
		partext += stringline_prop(fitresult,deltaA22perp)
		partext += stringline_prop(fitresult,deltaA22par2)
		partext += stringline_prop(fitresult,deltaA22perp2)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{$Scalar-Tensor$ decays (ST and TS)}\\\\\n\\hline\n\\hline\n'
		partext += stringline_prop(fitresult,sqmodA02norm)
		partext += stringline_prop(fitresult,sqmodA20norm)
		partext += stringline_prop(fitresult,deltaA02)
		partext += stringline_prop(fitresult,deltaA20)
		partext += '\\hline\n\\hline\n'
	partext += '\\end{tabular}\n\\end{table}\n\n'
	if not calib_params_fixed:
		partext += '\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|c|}\n\hline\nParameter & Value & Stat. uncertainty \\\\\n\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{SSK tagger}\\\\\n\\hline\n\\hline\n'
		partext += stringline("p0metac_SSK",parameters,blinded)
		partext += stringline("Dp0half_SSK",parameters,blinded)
		partext += stringline("p1_SSK",parameters,blinded)
		partext += stringline("Dp1half_SSK",parameters,blinded)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{OS tagger}\\\\\n\\hline\n\\hline\n'
		partext += stringline("p0metac_OS",parameters,blinded)
		partext += stringline("Dp0half_OS",parameters,blinded)
		partext += stringline("p1_OS",parameters,blinded)
		partext += stringline("Dp1half_OS",parameters,blinded)
		partext += '\\hline\n\\hline\n'
		partext += '\\multicolumn{3}{|c|}{Time resolution}\\\\\n\\hline\n\\hline\n'
		partext += stringline("tres_p0_2011",parameters,blinded)
		partext += stringline("tres_p1_2011",parameters,blinded)
		partext += stringline("tres_p0_2012",parameters,blinded)
		partext += stringline("tres_p1_2012",parameters,blinded)
		partext += '\\hline\n\\hline\n\\end{tabular}\n\\end{table}\n\n'
	partext += '\\end{document}'
	partext = partext.replace('#','\\')
	partext = partext.replace('\\hline\n\\end{tabular}','\\end{tabular}')

	texfile = open(filename+'_Polar.tex','w')
	texfile.write(partext)
	texfile.close()

def fitprint2LaTeX_OldStyle(fitresult,filename):
	partext = '\\documentclass[11pt,a4paper]{article}\n\\usepackage[left=2.5cm,top=2.5cm,right=2.5cm,bottom=2.5cm]{geometry}\n\n\\begin{document}\n\n\\begin{table}[h]\n\\centering\n\\begin{tabular}{|c|c|c|}\n\hline\nParameter & Value & Stat. uncertainty \\\\\n\\hline\n\\hline\n'
	partext += stringline_prop(fitresult,fL11)
	partext += stringline_prop(fitresult,fpar11)
	partext += stringline_prop(fitresult,sqmodAsminusnorm)
	partext += stringline_prop(fitresult,sqmodAsplusnorm)
	partext += stringline_prop(fitresult,sqmodA00norm)
	partext += stringline_prop(fitresult,deltaA11par)
	partext += stringline_prop(fitresult,deltaA11perpAsplus)
	partext += stringline_prop(fitresult,deltaAsminus)
	partext += stringline_prop(fitresult,deltaA00)
	partext += '\\hline\n\\hline\n'
	partext += '\\end{tabular}\n\\end{table}\n\n'
	partext += '\\end{document}'
	partext = partext.replace('#','\\')
	partext = partext.replace('\\hline\n\\end{tabular}','\\end{tabular}')

	texfile = open(filename+'_OldStyle.tex','w')
	texfile.write(partext)
	texfile.close()

def printPlot(var,fr):

	def addLines():
		xmin = var.getMin()
		xmax = var.getMax()
		midLine = ROOT.TLine(xmin,0.,xmax,0.)
		uppLine = ROOT.TLine(xmin,2.,xmax,2.)
		lowLine = ROOT.TLine(xmin,-2.,xmax,-2.)
		uppLine.SetLineColor(kRed)
		lowLine.SetLineColor(kRed)
		lines = [uppLine, midLine, lowLine]
		return lines

	var_title = fr.GetXaxis().GetTitle()
	ctemp = ROOT.TCanvas()
	ctemp.Divide(1,2)
	ctemp.cd(1)
	ROOT.gPad.SetPad(0.,0.25,1.,1.)
	ROOT.gPad.SetBottomMargin(0.025)
	frame1 = fr.Clone()
	frame1.SetTitle("")
	frame1.Draw()
	frame1.GetXaxis().SetTitle("")
	frame1.GetXaxis().SetTitleSize(0.07)
	frame1.GetYaxis().SetTitleSize(0.07)
	frame1.GetXaxis().SetLabelSize(0.0)
	frame1.GetYaxis().SetLabelSize(0.06)
	ctemp.cd(2)
	ROOT.gPad.SetPad(0.,0.,1.,0.25)
	ROOT.gPad.SetTopMargin(0.025)
	ROOT.gPad.SetBottomMargin(0.55)
	frame2 = var.frame()
	h1 = frame1.pullHist("data_0","model")
	h1.SetFillColor(16)
	frame2.addPlotable(h1,"E4")
	frame2.GetXaxis().SetLabelSize(0.2)
	frame2.GetYaxis().SetLabelSize(0.2)
	frame2.GetYaxis().SetNdivisions(5)
	frame2.SetTitle("")
	frame2.GetXaxis().SetTitle(var_title)
	frame2.GetXaxis().SetTitleSize(0.25)
	frame2.GetXaxis().SetTitleOffset(0.9)
	frame2.SetMaximum(6)
	frame2.SetMinimum(-6)
	frame2.Draw()
	lines = addLines()
	map(lambda x: x.Draw("same"), lines)
	ctemp.Print('TDFitPlot_'+var.GetName()+'.root')
	ctemp.Print('TDFitPlot_'+var.GetName()+'.pdf')

def printCorrMatrix(res):

	ROOT.gStyle.SetPalette(55)
	hcorr = res.correlationHist()
	ctemp = ROOT.TCanvas()
	hcorr.Draw("zcoltext")
	ctemp.Print("FitCorrMatrix.root")
	ctemp.Print("FitCorrMatrix.pdf")

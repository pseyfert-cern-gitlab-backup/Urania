from parameters import *
import numpy as np
from math import exp

gROOT.ProcessLine( "struct MyStructF{ Float_t afloat; };" )


# ################################################################
# F U N C T I O N S
# ################################################################


def ForceCompileLibs():

	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'KpiKpiSpectrumNW.cxx++')
	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'ComputeIntegrals.cxx++')
	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'lhcbStyle.C')
	gROOT.Reset()


def CompileLibs():

	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'KpiKpiSpectrumNW.cxx+')
	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'ComputeIntegrals.cxx+')
	gROOT.ProcessLine('.x ' + SOURCE_PATH + 'lhcbStyle.C')
	gROOT.Reset()


def CompileLibsGRID():

	gROOT.ProcessLine('.x KpiKpiSpectrumNW.cxx++')
	gROOT.ProcessLine('.x ComputeIntegrals.cxx++')
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
		reA00.setVal(0.97163994981)
		reA01.setVal(-0.307779453311)
		reA10.setVal(-0.825779978734)
		reA11par.setVal(-0.806142954203)
		reA11perp.setVal(0.13028597937)
		imA00.setVal(0.78498772682)
		imA01.setVal(-2.63286888731)
		imA10.setVal(2.07320622707)
		imA11par.setVal(1.03541700344)
		imA11perp.setVal(1.850718779)
		delta_m_Bs.setVal(17.5551050692)
		gamma_Bs.setVal(0.664714683125)
		delta_gamma_Bs.setVal(0.0849436415988)
		p0metac_SSK.setVal(0.00635590157063)
		p0metac_OS.setVal(0.00623255021164)
		Dp0half_SSK.setVal(-0.00804081446555)
		Dp0half_OS.setVal(0.00699331466117)
		p1_SSK.setVal(0.931921848337)
		p1_OS.setVal(0.985639376943)
		Dp1half_SSK.setVal(-0.0173054641083)
		Dp1half_OS.setVal(0.032943401124)
		tres_p0_2011.setVal(0.0352456006781)
		tres_p1_2011.setVal(1.19984781615)
		tres_p0_2012.setVal(0.0365982765612)
		tres_p1_2012.setVal(1.21774637388)

	else:
		reA00.setVal(0.263213091699)
		reA01.setVal(1.07653830679)
		reA10.setVal(-1.49625609054)
		reA02.setVal(1.26904336768)
		reA20.setVal(-0.974895358627)
		reA11par.setVal(-0.601174018752)
		reA11perp.setVal(-0.465295943202)
		reA120.setVal(0.602027386833)
		reA12par.setVal(-0.271829808593)
		reA12perp.setVal(0.0989766761271)
		reA210.setVal(2.10776223128)
		reA21par.setVal(0.539024552709)
		reA21perp.setVal(0.236222658219)
		reA220.setVal(0.00981334657903)
		reA22par.setVal(-0.381578372735)
		reA22perp.setVal(-0.146879290127)
		reA22par2.setVal(-0.234269594676)
		reA22perp2.setVal(-0.49213232522)
		imA00.setVal(2.05661861783)
		imA01.setVal(-2.54827686531)
		imA10.setVal(1.74387412348)
		imA02.setVal(0.167910477061)
		imA20.setVal(0.356617983551)
		imA11par.setVal(0.647365397275)
		imA11perp.setVal(1.15908031842)
		imA120.setVal(0.818587824167)
		imA12par.setVal(-0.568102894404)
		imA12perp.setVal(-0.981310365381)
		imA210.setVal(-0.196363957019)
		imA21par.setVal(0.0565340027071)
		imA21perp.setVal(0.101936877575)
		imA220.setVal(0.363806432797)
		imA22par.setVal(0.145121203089)
		imA22perp.setVal(-0.376583167345)
		imA22par2.setVal(-0.506870743142)
		imA22perp2.setVal(0.00272493632338)
		delta_m_Bs.setVal(17.564750247)
		gamma_Bs.setVal(0.666081049602)
		delta_gamma_Bs.setVal(0.0835709599753)
		p0metac_SSK.setVal(0.00819184747504)
		p0metac_OS.setVal(0.00873392093879)
		Dp0half_SSK.setVal(-0.00803923202808)
		Dp0half_OS.setVal(0.00699395305975)
		p1_SSK.setVal(0.924624591241)
		p1_OS.setVal(0.98702060421)
		Dp1half_SSK.setVal(-0.0152298955895)
		Dp1half_OS.setVal(0.0328165865918)
		tres_p0_2011.setVal(0.0347684184156)
		tres_p1_2011.setVal(1.1538488585)
		tres_p0_2012.setVal(0.0364542070585)
		tres_p1_2012.setVal(1.25984512077)


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


def converted_parameter(param,blinding,scale):
   from ModelBricks import Parameter, Free
   paramname = param.GetName()
   if ('phi' in paramname or 'DCP' in paramname) and blinding:
      blstring = np.random.uniform(-scale,scale)
      blinding_strings[paramname] = blstring
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

par_name_dict = {'reA22perp': 'Re(A^{TT}_{#perp1})', 'reA22par2': 'Re(A^{TT}_{#parallel2})', 'delta_210': '#delta^{TV}_{0}', 'tres_p1_2012': 'p_{1}^{#sigma_{t}}(2012)', 'tres_p1_2011': 'p_{1}^{#sigma_{t}}(2011)', 'delta_00': '#delta^{SS}', 'reA10': 'Re(A^{VS})', 'p0metac_OS': 'p_{0}^{OS}-<#eta^{OS}>', 'reA220': 'Re(A^{TT}_{L})', 'reA20': 'Re(A^{TS})', 'delta_10': '#delta^{VS}', 'imA21par': 'Im(A^{TV}_{#parallel})', 'reA11par': 'Re(A^{VV}_{#parallel})', 'delta_11par': '#delta^{VV}_{#parallel}', 'DCP': '#Delta^{CP}', 'imA22perp2': 'Im(A^{TT}_{#perp2})', 'delta_12par': '#delta^{VT}_{#parallel}', 'delta_01': '#delta^{SV}', 'imA22par': 'Im(A^{TT}_{#parallel1})', 'delta_02': '#delta^{ST}', 'reA22par': 'Re(A^{TT}_{#parallel1})', 'p1_SSK': 'p_{1}^{SSK}', 'delta_22perp': '#delta^{TT}_{#perp1}', 'reA21par': 'Re(A^{TV}_{#parallel})', 'delta_21par': '#delta^{TV}_{#parallel}', 'Dp1half_SSK': '1/2 #Delta p_{1}^{SSK}', 'delta_11perp': '#delta^{VV}_{#perp}', 'f_perp2_22': 'f_{#perp2}^{TT}', 'imA210': 'Im(A^{TV}_{L})', 'tres_p0_2011': 'p_{0}^{#sigma_{t}}(2011)', 'reA120': 'Re(A^{VT}_{L})', 'imA21perp': 'Im(A^{TV}_{#perp})', 'tres_p0_2012': 'p_{0}^{#sigma_{t}}(2012)', 'delta_22perp2': '#delta^{TT}_{#perp2}', 'reA22perp2': 'Re(A^{TT}_{#perp2})', 'imA10': 'Im(A^{VS})', 'delta_21perp': '#delta^{TV}_{#perp}', 'p1_OS': 'p_{1}^{OS}', 'delta_22par2': '#delta^{TT}_{#parallel2}', 'f_22': 'f_{TT}', 'f_21': 'f_{TV}', 'f_20': 'f_{TS}', 'f_L_22': 'f_L^{TT}', 'f_par_22': 'f_{#parallel1}^{TT}', 'f_par_21': 'f_{#parallel}^{TV}', 'f_L_21': 'f_L^{TV}', 'imA12perp': 'Im(A^{VT}_{#perp})', 'delta_12perp': '#delta^{VT}_{#perp}', 'imA220': 'Im(A^{TT}_{L})', 'delta_m_Bs': '#Delta m_{B_{s}^{0}}', 'reA12par': 'Re(A^{VT}_{#parallel})', 'f_par2_22': 'f_{#parallel2}^{TT}', 'Dp1half_OS': '1/2 #Delta p_{1}^{OS}', 'f_12': 'f_{VT}', 'f_10': 'f_{VS}', 'f_11': 'f_{VV}', 'imA02': 'Im(A^{ST})', 'imA00': 'Im(A^{SS})', 'imA01': 'Im(A^{SV})', 'f_par_12': 'f_{#parallel}^{VT}', 'f_par_11': 'f_{#parallel}^{VV}', 'reA01': 'Re(A^{SV})', 'Dp0half_OS': '1/2 #Delta p_{0}^{OS}', 'reA11perp': 'Re(A^{VV}_{#perp})', 'imA120': 'Im(A^{VT}_{L})', 'f_01': 'f_{SV}', 'f_00': 'f_{SS}', 'f_02': 'f_{ST}', 'gamma_Bs': '#Gamma_{B_{s}^{0}}', 'f_perp_22': 'f_{#perp1}^{TT}', 'f_perp_21': 'f_{#perp}^{TV}', 'p0metac_SSK': 'p_{0}^{SSK}-<#eta^{SSK}>', 'imA22perp': 'Im(A^{TT}_{#perp1})', 'delta_22par': '#delta^{TT}_{#parallel1}', 'imA22par2': 'Im(A^{TT}_{#parallel2})', 'reA210': 'Re(A^{TV}_{L})', 'imA20': 'Im(A^{TS})', 'imA11perp': 'Im(A^{VV}_{#perp})', 'f_L_12': 'f_L^{VT}', 'f_L_11': 'f_L^{VV}', 'f_perp_12': 'f_{#perp}^{VT}', 'f_perp_11': 'f_{#perp}^{VV}', 'delta_120': '#delta^{VT}_{0}', 'delta_220': '#delta^{TT}_{0}', 'reA21perp': 'Re(A^{TV}_{#perp})', 'imA11par': 'Im(A^{VV}_{#parallel})', 'reA12perp': 'Re(A^{VT}_{#perp})', 'Dp0half_SSK': '1/2 #Delta p_{0}^{SSK}', 'reA00': 'Re(A^{SS})', 'reA02': 'Re(A^{ST})', 'delta_gamma_Bs': '#Delta #Gamma_{B_{s}^{0}}', 'delta_20': '#delta^{TS}', 'imA12par': 'Im(A^{VT}_{#parallel})', 'phis': '#phi_{s}'}

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

def DoCUDAFit(data_,params_,blinding_,wide_window_,minos_,output_file_name_):

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

   BLOCK_SIZE = 252
   THR = 1e06
   paramnames = []
   for par in params_: paramnames.append(par.GetName())

   def getGrid(thiscat, BLOCK_SIZE):
      Nbunch = thiscat.Nevts *1. / BLOCK_SIZE
      print "thiscat.Nevts, Nbunch = ", thiscat.Nevts, Nbunch
      if Nbunch > int(Nbunch): Nbunch = int(Nbunch) +1
      else : Nbunch = int(Nbunch)
      return  (Nbunch,1,1)

   print '\nTranslating parameters ...'
   Params = []
   np.random.seed(1)
   for par in params_:
      Params.append(converted_parameter(par,blinding_,blinding_scale))

   print '\nCompiling CUDA PDF ...'
   mod = cuRead("../../src/TimeDependent/Bs2KpiKpiTDPDF.cu", no_extern_c = True)
   CUDA_pdf_initializer = mod.get_function("initialize")
   CUDA_pdf = mod.get_function("evaluate")

   print '\nConverting datasets ...'
   data_arraylist = create_data_arrays(data_)

   print '\nCreating categories ...'
   cat_name_list = ['11L0TIS','11L0noTIS','12L0TIS','12L0noTIS']
   options_arraylist = []
   options_arraylist.append(create_param_list('options_11L0TIS_list'))
   options_arraylist.append(create_param_list('options_11L0noTIS_list'))
   options_arraylist.append(create_param_list('options_12L0TIS_list'))
   options_arraylist.append(create_param_list('options_12L0noTIS_list'))
   cats = []
   for i in range(4):
      thiscat = Cat(cat_name_list[i], data_arraylist[i], getN = True)
      thiscat.model_options = gpuarray.to_gpu(options_arraylist[i])
      thiscat.block = (BLOCK_SIZE,1,1)
      thiscat.grid = getGrid(thiscat, BLOCK_SIZE)
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
         self.pdf = CUDA_pdf
         self.re_amps_list_cu = create_param_list("re_amps_list")
         self.dirCP_asyms_list_cu = create_param_list("dirCP_asyms_list")
         self.im_amps_list_cu = create_param_list("im_amps_list")
         self.weak_phases_list_cu = create_param_list("weak_phases_list")
         self.mixing_params_list_cu = create_param_list("mixing_params_list")
         self.calib_params_list_cu = create_param_list("calib_params_list")
         self.mass_integrals_list_cu = create_param_list('mass_integrals_11L0TIS_list',numparams = 9)
         CUDA_pdf_initializer(block = (1,1,1))

      def check_PDF(self):
         for [idx,ival] in param_list_updates_check("re_amps_list",paramnames,blinding = blinding_): self.re_amps_list_cu[idx] = ival
         for [idx,ival] in param_list_updates_check("dirCP_asyms_list",paramnames,blinding = blinding_): self.dirCP_asyms_list_cu[idx] = ival
         for [idx,ival] in param_list_updates_check("im_amps_list",paramnames,blinding = blinding_): self.im_amps_list_cu[idx] = ival
         for [idx,ival] in param_list_updates_check("weak_phases_list",paramnames,blinding = blinding_): self.weak_phases_list_cu[idx] = ival
         for [idx,ival] in param_list_updates_check("mixing_params_list",paramnames,blinding = blinding_): self.mixing_params_list_cu[idx] = ival
         for [idx,ival] in param_list_updates_check("calib_params_list",paramnames,blinding = blinding_): self.calib_params_list_cu[idx] = ival
         cat = self.cats[1]
         print cat.data[0]
         print ''
         self.pdf(cat.data,cat.Probs,cudriver.Out(check),cat.model_options,gpuarray.to_gpu(self.re_amps_list_cu),gpuarray.to_gpu(self.dirCP_asyms_list_cu),gpuarray.to_gpu(self.im_amps_list_cu),gpuarray.to_gpu(self.weak_phases_list_cu),gpuarray.to_gpu(self.mixing_params_list_cu),gpuarray.to_gpu(self.calib_params_list_cu),gpuarray.to_gpu(self.mass_integrals_list_cu),cat.Nevts,block = cat.block,grid = cat.grid)
         print check[0],check[1],check[2]
         print ''

      def __call__(self,*args):
         chi2 = np.float64(0.)
         N = self.dc
         for [idx,ival] in param_list_updates("re_amps_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.re_amps_list_cu[idx] = ival
         for [idx,ival] in param_list_updates("dirCP_asyms_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.dirCP_asyms_list_cu[idx] = ival
         for [idx,ival] in param_list_updates("im_amps_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.im_amps_list_cu[idx] = ival
         for [idx,ival] in param_list_updates("weak_phases_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.weak_phases_list_cu[idx] = ival
         for [idx,ival] in param_list_updates("mixing_params_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.mixing_params_list_cu[idx] = ival
         for [idx,ival] in param_list_updates("calib_params_list",paramnames,args_ = args,N_ = N,blinding = blinding_): self.calib_params_list_cu[idx] = ival
         for cat in self.cats:
            self.pdf(cat.data,cat.Probs,cudriver.Out(check),cat.model_options,gpuarray.to_gpu(self.re_amps_list_cu),gpuarray.to_gpu(self.dirCP_asyms_list_cu),gpuarray.to_gpu(self.im_amps_list_cu),gpuarray.to_gpu(self.weak_phases_list_cu),gpuarray.to_gpu(self.mixing_params_list_cu),gpuarray.to_gpu(self.calib_params_list_cu),gpuarray.to_gpu(self.mass_integrals_list_cu),cat.Nevts,block = cat.block,grid = cat.grid)
            #nan = np.nan
            #for pr in getattr(cat,"Probs"):
               #if eval(str(pr)) == nan: print check[0],check[1],check[2]
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
   manager.createFit()
   #manager.check_PDF()

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
      if (("DCP" in par.GetName()) or ("phis" in par.GetName())) and blinding_: par.setVal(upar[par.GetName()].nominal_value-blinding_strings[par.GetName()])
      else: par.setVal(upar[par.GetName()].nominal_value)

   for par in params_:
      if ((not "DCP" in par.GetName()) and (not "phis" in par.GetName())): print '\t\t'+par.GetName()+'.setVal('+str(par.getVal())+')'
   print ''

   if output_file_name_ != "":
      par_result_dict = {}
      for par in paramnames+polarparamnames: par_result_dict[par] = (upar[par].nominal_value,upar[par].std_dev,par_name_dict[par].replace('#','\\'))
      fresult = open('_'+output_file_name_+'.py','w')
      fresult.write("par_result_dict = "+str(par_result_dict))
      fresult.close()
      print 'Fit results saved in _'+output_file_name_+'.py'

   print '\nINFO:',int((timer() - start)/60),'min needed to do the fit.'


def DoCUDAToy(N_exps,N_events,params_,wide_window_,output_tag):

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

   for par in params_:
      if "DCP" in par.GetName(): par.setVal(0.)
      elif "phis" in par.GetName(): par.setVal(0.)

   BLOCK_SIZE = 252
   THR = 1e06
   paramnames = []
   for par in params_: paramnames.append(par.GetName())

   def getGrid(thiscat, BLOCK_SIZE):
      Nbunch = thiscat.Nevts *1. / BLOCK_SIZE
      print "thiscat.Nevts, Nbunch = ", thiscat.Nevts, Nbunch
      if Nbunch > int(Nbunch): Nbunch = int(Nbunch) +1
      else : Nbunch = int(Nbunch)
      return  (Nbunch,1,1)

   cats = []
   gen_data = np.ones((N_events,12)).astype(np.float64)
   thiscat = Cat("gen_cat", gen_data, getN = True)
   thiscat.block = (BLOCK_SIZE,1,1)
   thiscat.grid = getGrid(thiscat, BLOCK_SIZE)
   cats.append(thiscat)

   print '\nTranslating parameters ...'
   Params = []
   for par in params_:
      Params.append(converted_parameter(par,0,blinding_scale))
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

         self.lock_to_init(["tres_p0_2011_cu","tres_p1_2011_cu"])

         CUDA_initialize(block = (1,1,1))
         CUDA_set_generator(gpuarray.to_gpu(self.options_list_cu),gpuarray.to_gpu(self.re_amps_list_cu_gen),gpuarray.to_gpu(self.dirCP_asyms_list_cu_gen),gpuarray.to_gpu(self.im_amps_list_cu_gen),gpuarray.to_gpu(self.weak_phases_list_cu_gen),gpuarray.to_gpu(self.mixing_params_list_cu_gen),gpuarray.to_gpu(self.calib_params_list_cu_gen),gpuarray.to_gpu(self.cond_distr_params_list_cu),gpuarray.to_gpu(self.mass_integrals_list_cu),gpuarray.to_gpu(self.ang_integrals_list_cu),block = (1,1,1))

      def createFit(self):
         config = {}
         for par in self.params: config.update(par.getSettings())
         self.fit = Minuit(self, errordef=1, **config)

      def set_gen_step(self,num,q1_=0,q2_=0):

         for par in par_phys_names: self.Params[par].setVal(par_phys_init_vals[par])
         self.gen_step = num

         if self.gen_step == 0:
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

            CUDA_set_generator(gpuarray.to_gpu(self.options_list_cu),gpuarray.to_gpu(self.re_amps_list_cu_gen),gpuarray.to_gpu(self.dirCP_asyms_list_cu_gen),gpuarray.to_gpu(self.im_amps_list_cu_gen),gpuarray.to_gpu(self.weak_phases_list_cu_gen),gpuarray.to_gpu(self.mixing_params_list_cu_gen),gpuarray.to_gpu(self.calib_params_list_cu_gen),gpuarray.to_gpu(self.cond_distr_params_list_cu),gpuarray.to_gpu(self.mass_integrals_list_cu),gpuarray.to_gpu(self.ang_integrals_list_cu),block = (1,1,1))

         if self.gen_step == 3:
            for par in ["gamma_Bs_cu","delta_gamma_Bs_cu","Dp0half_SSK_cu","Dp0half_OS_cu","Dp1half_SSK_cu","Dp1half_OS_cu","p0metac_SSK_cu","p1_SSK_cu","p0metac_OS_cu","p1_OS_cu","tres_p0_2012_cu","tres_p1_2012_cu"]: self.Params[par].setVal(par_ctrt_init_vals[par])
            self.freeThese(par_phys_names)
            self.lock_to_init(par_var_names)
            self.lock_to_init(["tres_p0_2011_cu","tres_p1_2011_cu"])

      def generate(self):
         cat = self.cats[0]
         self.ev_gen(cat.data,np.float64(self.max_eta_SSK_pdf[0]),np.float64(self.max_eta_OS_pdf[0]),np.float64(self.max_cond_pdf),np.int32(cat.Nevts),block = cat.block,grid = cat.grid)

      def __call__(self,*args):

         chi2 = np.float64(0.)
         N = self.dc

         if self.gen_step == 0:
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

   print '\nComputing conditional pdf maximum ...'
   pdf_maxima = []
   for q1_ in [-1,0,1]:
      for q2_ in [-1,0,1]:
         manager.set_gen_step(0,q1_,q2_)
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
            sigma_par = upar[par_name].std_dev
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
	partext += stringline("DCP_VV",parameters,blinded)
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

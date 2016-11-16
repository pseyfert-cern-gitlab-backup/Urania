from ROOT import *
from math import *
import time
import sys
import os
import random
from parameters import *
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


def information(datatype, Blinding = 1, NOCP = 0, NODIRCP = 0, SAMECP = 1, acc_type = 0, inf_t_res = 0, wide_window = 1, fix_wave_fractions = 0,\
fix_dirCP_asyms = 0, fix_strong_phases = 0, fix_weak_phases = 0, fix_mixing_params = 0, fix_calib_params = 0, pw_alternative_model = 0):

	print "\n#####################################################################"
	print " R E L E V A N T   I N F O R M A T I O N   A B O U T   T H E   F I T"
	print "#####################################################################\n"
	if (datatype == "real"): print " - Fit to REAL DATA corresponding to 2011 and 2012."
	else: print " - Fit to MONTE CARLO DATA."
	if (wide_window): print "   (WIDE WINDOW used in the Kpi invariant mass, from 750 to 1500 MeV.)\n"
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
	if fix_wave_fractions: print "\n WARNING: wave fractions fixed."
	if fix_dirCP_asyms: print "\n WARNING: direct CP violation asymmetries fixed."
	if fix_strong_phases: print "\n WARNING: strong phases fixed."
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

	if (wide_window == 0):
		f_VV.setVal(0.342716287755)
		f_SS.setVal(0.14802490239)
		D_SVVS.setVal(0.266455913281)
		fL_VV.setVal(0.262565108374)
		xpar_VV.setVal(0.348638546428)
		DCP.setVal(0.192058518052)
		delta00.setVal(0.77600454957)
		delta01.setVal(-1.59297252737)
		delta10.setVal(2.04559453012)
		delta11par.setVal(2.30444616424)
		delta11perp.setVal(2.13826174934)
		phis.setVal(0.442679418166)
		delta_m_Bs.setVal(17.7444069773)
		gamma_Bs.setVal(0.664393076101)
		delta_gamma_Bs.setVal(0.0829276243453)
		p0metac_SSK.setVal(0.00759247495529)
		p0metac_OS.setVal(0.00614987235518)
		Dp0half_SSK.setVal(-0.00823485845485)
		Dp0half_OS.setVal(0.00699867062538)
		p1_SSK.setVal(0.93786028506)
		p1_OS.setVal(0.984781117038)
		Dp1half_SSK.setVal(-0.0171300079695)
		Dp1half_OS.setVal(0.0329770554618)

	else:
		f_VV.setVal(0.129991402282)
		f_Swave.setVal(0.779324755955)
		f_SS.setVal(0.286977922698)
		f_VTTV.setVal(0.518925757426)
		f_TT.setVal(0.154758750653)
		D_SVVS.setVal(0.169137667226)
		D_VTTV.setVal(-0.0313476251179)
		D_STTS.setVal(-0.222976597893)
		fL_VV.setVal(0.161463977977)
		xpar_VV.setVal(0.332565345953)
		fL_VT.setVal(0.583350716198)
		xpar_VT.setVal(0.347514178473)
		fL_TV.setVal(0.830914271892)
		xpar_TV.setVal(0.213283559181)
		fL_TT.setVal(0.358720771261)
		xpar1_TT.setVal(0.198398154027)
		xperp1_TT.setVal(0.614130085675)
		xpar2_TT.setVal(0.134294467118)
		DCP.setVal(0.296805555859)
		delta00.setVal(0.321531769474)
		delta01.setVal(2.17143199051)
		delta10.setVal(-1.31191429801)
		delta02.setVal(-2.40981817497)
		delta20.setVal(-2.95112344238)
		delta11par.setVal(-2.12793970368)
		delta11perp.setVal(1.66713272158)
		delta120.setVal(2.32052712532)
		delta12par.setVal(2.36842439785)
		delta12perp.setVal(-1.54878149742)
		delta210.setVal(-0.733868914478)
		delta21par.setVal(0.995718780136)
		delta21perp.setVal(1.27865056041)
		delta220.setVal(0.182855426868)
		delta22par.setVal(-4.71680417069)
		delta22perp.setVal(-2.68659464005)
		delta22par2.setVal(0.890419033669)
		delta22perp2.setVal(-0.116511351867)
		phis.setVal(0.155083183879)
		delta_m_Bs.setVal(17.7718573039)
		gamma_Bs.setVal(0.661303165428)
		delta_gamma_Bs.setVal(0.0889776418563)
		p0metac_SSK.setVal(0.00759528201497)
		p0metac_OS.setVal(0.00791318514575)
		Dp0half_SSK.setVal(-0.00805304996403)
		Dp0half_OS.setVal(0.00701362120162)
		p1_SSK.setVal(0.921571293016)
		p1_OS.setVal(0.977411164304)
		Dp1half_SSK.setVal(-0.0178515756611)
		Dp1half_OS.setVal(0.032731542716)


def aux_PDF():
	""" Used to compute some normalization integrals."""

	for argument in options: options_list_aux.add(argument)
	for argument in observables: observables_list_aux.add(argument)
	for argument in wave_fractions: wave_fractions_list_aux.add(argument)
	for argument in dirCP_asyms: dirCP_asyms_list_aux.add(argument)
	for argument in strong_phases: strong_phases_list_aux.add(argument)
	for argument in weak_phases: weak_phases_list_aux.add(argument)
	for argument in mixing_params: mixing_params_list_aux.add(argument)
	for argument in calib_params_aux: calib_params_list_aux.add(argument)
	for argument in cond_distr_params: cond_distr_params_list_aux.add(argument)
	for argument in sys_studies: sys_studies_list_aux.add(argument)
	for argument in mass_integrals: mass_integrals_list_aux.add(argument)
	for argument in ang_integrals: ang_integrals_list_aux.add(argument)
	for argument in time_integrals: time_integrals_list_aux.add(argument)

	auxiliar_PDF = KpiKpiSpectrumNW("auxiliar_PDF","auxiliar_PDF",options_list_aux,observables_list_aux,wave_fractions_list_aux,dirCP_asyms_list_aux,\
strong_phases_list_aux,weak_phases_list_aux,mixing_params_list_aux,calib_params_list_aux,cond_distr_params_list_aux,sys_studies_list_aux,\
mass_integrals_list_aux,ang_integrals_list_aux,time_integrals_list_aux)

	return auxiliar_PDF
	

def PDF_with_integrals(name,description,options_arglist,wide_window,data_file,observables_arglist,wave_fractions_arglist,dirCP_asyms_arglist,strong_phases_arglist,\
weak_phases_arglist,mixing_params_arglist,calib_params_arglist,sys_studies_arglist):

	RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)
	Integrator = ComputeIntegrals("Integrator","Integrator",options_arglist,observables_arglist,mixing_params_arglist,calib_params_arglist,mass_integrals_list)

	# Calculation of the invariant mass integrals for normalization.
	if wide_window:
		option.setVal(100)
		integral100 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Im00.setVal(integral100.getVal())
		option.setVal(101)
		integral101 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Im01.setVal(integral101.getVal())
		option.setVal(110)
		integral110 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Im10.setVal(integral110.getVal())
		option.setVal(102)
		integral102 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Im02.setVal(integral102.getVal())
		option.setVal(120)
		integral120 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Im20.setVal(integral120.getVal())
		option.setVal(111)
		integral111 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Im11.setVal(integral111.getVal())
		option.setVal(112)
		integral112 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Im12.setVal(integral112.getVal())
		option.setVal(121)
		integral121 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Im21.setVal(integral121.getVal())
		option.setVal(122)
		integral122 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Im22.setVal(integral122.getVal())
	else:
		option.setVal(100)
		integral100 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im00.setVal(integral100.getVal())
		option.setVal(101)
		integral101 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im01.setVal(integral101.getVal())
		option.setVal(110)
		integral110 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im10.setVal(integral110.getVal())
		option.setVal(102)
		integral102 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im02.setVal(integral102.getVal())
		option.setVal(120)
		integral120 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im20.setVal(integral120.getVal())
		option.setVal(111)
		integral111 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im11.setVal(integral111.getVal())
		option.setVal(112)
		integral112 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im12.setVal(integral112.getVal())
		option.setVal(121)
		integral121 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im21.setVal(integral121.getVal())
		option.setVal(122)
		integral122 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Im22.setVal(integral122.getVal())

	# Calculation of the angular integrals for visualization.
	option.setVal(21)
	integral21 = Integrator.createIntegral(RooArgSet(cos1))
	If1.setVal(integral21.getVal())
	option.setVal(22)
	integral22 = Integrator.createIntegral(RooArgSet(cos1))
	If2.setVal(integral22.getVal())
	option.setVal(23)
	integral23 = Integrator.createIntegral(RooArgSet(cos1))
	If3.setVal(integral23.getVal())
	option.setVal(24)
	integral24 = Integrator.createIntegral(RooArgSet(cos1))
	If4.setVal(integral24.getVal())
	option.setVal(25)
	integral25 = Integrator.createIntegral(RooArgSet(cos1))
	If5.setVal(integral25.getVal())
	option.setVal(26)
	integral26 = Integrator.createIntegral(RooArgSet(cos1))
	If6.setVal(integral26.getVal())
	option.setVal(27)
	integral27 = Integrator.createIntegral(RooArgSet(cos1))
	If7.setVal(integral27.getVal())
	option.setVal(28)
	integral28 = Integrator.createIntegral(RooArgSet(cos1))
	If8.setVal(integral28.getVal())
	option.setVal(29)
	integral29 = Integrator.createIntegral(RooArgSet(cos1))
	If9.setVal(integral29.getVal())
	option.setVal(210)
	integral210 = Integrator.createIntegral(RooArgSet(cos1))
	If10.setVal(integral210.getVal())
	option.setVal(211)
	integral211 = Integrator.createIntegral(RooArgSet(cos1))
	If11.setVal(integral211.getVal())
	option.setVal(212)
	integral212 = Integrator.createIntegral(RooArgSet(cos1))
	If12.setVal(integral212.getVal())
	option.setVal(213)
	integral213 = Integrator.createIntegral(RooArgSet(cos1))
	If13.setVal(integral213.getVal())
	option.setVal(214)
	integral214 = Integrator.createIntegral(RooArgSet(cos1))
	If14.setVal(integral214.getVal())
	option.setVal(215)
	integral215 = Integrator.createIntegral(RooArgSet(cos1))
	If15.setVal(integral215.getVal())
	option.setVal(216)
	integral216 = Integrator.createIntegral(RooArgSet(cos1))
	If16.setVal(integral216.getVal())
	option.setVal(217)
	integral217 = Integrator.createIntegral(RooArgSet(cos1))
	If17.setVal(integral217.getVal())
	option.setVal(218)
	integral218 = Integrator.createIntegral(RooArgSet(cos1))
	If18.setVal(integral218.getVal())

	# Calculation of the invariant mass integrals for visualization.
	if wide_window:
		option.setVal(31)
		integral31 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih1Re.setVal(integral31.getVal())
		option.setVal(32)
		integral32 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih2Re.setVal(integral32.getVal())
		option.setVal(33)
		integral33 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih3Re.setVal(integral33.getVal())
		option.setVal(34)
		integral34 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih4Re.setVal(integral34.getVal())
		option.setVal(35)
		integral35 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih5Re.setVal(integral35.getVal())
		option.setVal(36)
		integral36 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih6Re.setVal(integral36.getVal())
		option.setVal(37)
		integral37 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih7Re.setVal(integral37.getVal())
		option.setVal(38)
		integral38 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih8Re.setVal(integral38.getVal())
		option.setVal(39)
		integral39 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih9Re.setVal(integral39.getVal())
		option.setVal(310)
		integral310 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih10Re.setVal(integral310.getVal())
		option.setVal(311)
		integral311 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih11Re.setVal(integral311.getVal())
		option.setVal(312)
		integral312 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih12Re.setVal(integral312.getVal())
		option.setVal(313)
		integral313 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih13Re.setVal(integral313.getVal())
		option.setVal(314)
		integral314 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih14Re.setVal(integral314.getVal())
		option.setVal(315)
		integral315 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih15Re.setVal(integral315.getVal())
		option.setVal(316)
		integral316 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih16Re.setVal(integral316.getVal())
		option.setVal(317)
		integral317 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih17Re.setVal(integral317.getVal())
		option.setVal(318)
		integral318 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih18Re.setVal(integral318.getVal())
		option.setVal(319)
		integral319 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih19Re.setVal(integral319.getVal())
		option.setVal(320)
		integral320 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih20Re.setVal(integral320.getVal())
		option.setVal(321)
		integral321 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih21Re.setVal(integral321.getVal())
		option.setVal(322)
		integral322 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih22Re.setVal(integral322.getVal())
		option.setVal(323)
		integral323 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih23Re.setVal(integral323.getVal())
		option.setVal(324)
		integral324 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih24Re.setVal(integral324.getVal())
		option.setVal(325)
		integral325 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih25Re.setVal(integral325.getVal())
		option.setVal(326)
		integral326 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih26Re.setVal(integral326.getVal())
		option.setVal(327)
		integral327 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih27Re.setVal(integral327.getVal())
		option.setVal(328)
		integral328 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih28Re.setVal(integral328.getVal())
		option.setVal(329)
		integral329 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih29Re.setVal(integral329.getVal())
		option.setVal(330)
		integral330 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih30Re.setVal(integral330.getVal())
		option.setVal(41)
		integral41 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih1Im.setVal(integral41.getVal())
		option.setVal(42)
		integral42 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih2Im.setVal(integral42.getVal())
		option.setVal(43)
		integral43 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih3Im.setVal(integral43.getVal())
		option.setVal(44)
		integral44 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih4Im.setVal(integral44.getVal())
		option.setVal(45)
		integral45 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih5Im.setVal(integral45.getVal())
		option.setVal(46)
		integral46 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih6Im.setVal(integral46.getVal())
		option.setVal(47)
		integral47 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih7Im.setVal(integral47.getVal())
		option.setVal(48)
		integral48 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih8Im.setVal(integral48.getVal())
		option.setVal(49)
		integral49 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih9Im.setVal(integral49.getVal())
		option.setVal(410)
		integral410 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih10Im.setVal(integral410.getVal())
		option.setVal(411)
		integral411 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih11Im.setVal(integral411.getVal())
		option.setVal(412)
		integral412 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih12Im.setVal(integral412.getVal())
		option.setVal(413)
		integral413 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih13Im.setVal(integral413.getVal())
		option.setVal(414)
		integral414 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih14Im.setVal(integral414.getVal())
		option.setVal(415)
		integral415 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih15Im.setVal(integral415.getVal())
		option.setVal(416)
		integral416 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih16Im.setVal(integral416.getVal())
		option.setVal(417)
		integral417 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih17Im.setVal(integral417.getVal())
		option.setVal(418)
		integral418 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih18Im.setVal(integral418.getVal())
		option.setVal(419)
		integral419 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih19Im.setVal(integral419.getVal())
		option.setVal(420)
		integral420 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih20Im.setVal(integral420.getVal())
		option.setVal(421)
		integral421 = Integrator.createIntegral(RooArgSet(mKp1,mKp2))
		Ih21Im.setVal(integral421.getVal())
	else:
		option.setVal(31)
		integral31 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih1Re.setVal(integral31.getVal())
		option.setVal(32)
		integral32 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih2Re.setVal(integral32.getVal())
		option.setVal(33)
		integral33 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih3Re.setVal(integral33.getVal())
		option.setVal(34)
		integral34 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih4Re.setVal(integral34.getVal())
		option.setVal(35)
		integral35 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih5Re.setVal(integral35.getVal())
		option.setVal(36)
		integral36 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih6Re.setVal(integral36.getVal())
		option.setVal(37)
		integral37 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih7Re.setVal(integral37.getVal())
		option.setVal(38)
		integral38 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih8Re.setVal(integral38.getVal())
		option.setVal(39)
		integral39 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih9Re.setVal(integral39.getVal())
		option.setVal(310)
		integral310 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih10Re.setVal(integral310.getVal())
		option.setVal(311)
		integral311 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih11Re.setVal(integral311.getVal())
		option.setVal(312)
		integral312 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih12Re.setVal(integral312.getVal())
		option.setVal(313)
		integral313 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih13Re.setVal(integral313.getVal())
		option.setVal(314)
		integral314 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih14Re.setVal(integral314.getVal())
		option.setVal(315)
		integral315 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih15Re.setVal(integral315.getVal())
		option.setVal(316)
		integral316 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih16Re.setVal(integral316.getVal())
		option.setVal(317)
		integral317 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih17Re.setVal(integral317.getVal())
		option.setVal(318)
		integral318 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih18Re.setVal(integral318.getVal())
		option.setVal(319)
		integral319 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih19Re.setVal(integral319.getVal())
		option.setVal(320)
		integral320 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih20Re.setVal(integral320.getVal())
		option.setVal(321)
		integral321 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih21Re.setVal(integral321.getVal())
		option.setVal(322)
		integral322 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih22Re.setVal(integral322.getVal())
		option.setVal(323)
		integral323 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih23Re.setVal(integral323.getVal())
		option.setVal(324)
		integral324 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih24Re.setVal(integral324.getVal())
		option.setVal(325)
		integral325 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih25Re.setVal(integral325.getVal())
		option.setVal(326)
		integral326 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih26Re.setVal(integral326.getVal())
		option.setVal(327)
		integral327 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih27Re.setVal(integral327.getVal())
		option.setVal(328)
		integral328 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih28Re.setVal(integral328.getVal())
		option.setVal(329)
		integral329 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih29Re.setVal(integral329.getVal())
		option.setVal(330)
		integral330 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih30Re.setVal(integral330.getVal())
		option.setVal(41)
		integral41 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih1Im.setVal(integral41.getVal())
		option.setVal(42)
		integral42 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih2Im.setVal(integral42.getVal())
		option.setVal(43)
		integral43 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih3Im.setVal(integral43.getVal())
		option.setVal(44)
		integral44 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih4Im.setVal(integral44.getVal())
		option.setVal(45)
		integral45 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih5Im.setVal(integral45.getVal())
		option.setVal(46)
		integral46 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih6Im.setVal(integral46.getVal())
		option.setVal(47)
		integral47 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih7Im.setVal(integral47.getVal())
		option.setVal(48)
		integral48 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih8Im.setVal(integral48.getVal())
		option.setVal(49)
		integral49 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih9Im.setVal(integral49.getVal())
		option.setVal(410)
		integral410 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih10Im.setVal(integral410.getVal())
		option.setVal(411)
		integral411 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih11Im.setVal(integral411.getVal())
		option.setVal(412)
		integral412 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih12Im.setVal(integral412.getVal())
		option.setVal(413)
		integral413 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih13Im.setVal(integral413.getVal())
		option.setVal(414)
		integral414 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih14Im.setVal(integral414.getVal())
		option.setVal(415)
		integral415 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih15Im.setVal(integral415.getVal())
		option.setVal(416)
		integral416 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih16Im.setVal(integral416.getVal())
		option.setVal(417)
		integral417 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih17Im.setVal(integral417.getVal())
		option.setVal(418)
		integral418 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih18Im.setVal(integral418.getVal())
		option.setVal(419)
		integral419 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih19Im.setVal(integral419.getVal())
		option.setVal(420)
		integral420 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih20Im.setVal(integral420.getVal())
		option.setVal(421)
		integral421 = Integrator.createIntegral(RooArgSet(mKp1_narrowwin,mKp2_narrowwin))
		Ih21Im.setVal(integral421.getVal())
	
	# Calculation of the time integrals for visualization.
	option.setVal(91)
	integral91 = Integrator.createIntegral(RooArgSet(t))
	IT_cosh.setVal(integral91.getVal())
	option.setVal(92)
	integral92 = Integrator.createIntegral(RooArgSet(t))
	IT_sinh.setVal(integral92.getVal())
	option.setVal(93)
	integral93 = Integrator.createIntegral(RooArgSet(t))
	IT_cos.setVal(integral93.getVal())
	option.setVal(94)
	integral94 = Integrator.createIntegral(RooArgSet(t))
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

	RooMsgService.instance().setGlobalKillBelow(RooFit.INFO)
	option.setVal(0)

	# Construction of the PDF.
	PDF = KpiKpiSpectrumNW(name,description,options_arglist,observables_arglist,wave_fractions_arglist,dirCP_asyms_arglist,strong_phases_arglist,weak_phases_arglist,mixing_params_arglist,\
calib_params_arglist,cond_distr_params_list,sys_studies_arglist,mass_integrals_list,ang_integrals_list,time_integrals_list)

	return PDF


def PDFs_with_integrals(name,description,options_11L0TIS_arglist,options_11L0noTIS_arglist,options_12L0TIS_arglist,options_12L0noTIS_arglist,wide_window,data_file,observables_arglist,\
wave_fractions_arglist,dirCP_asyms_arglist,strong_phases_arglist,weak_phases_arglist,mixing_params_arglist,calib_params_arglist,sys_studies_arglist):

	RooMsgService.instance().setGlobalKillBelow(RooFit.WARNING)
	Integrator_11L0TIS = ComputeIntegrals("Integrator_11L0TIS","Integrator_11L0TIS",options_11L0TIS_arglist,observables_arglist,mixing_params_arglist,calib_params_arglist,mass_integrals_11L0TIS_list)
	Integrator_11L0noTIS = ComputeIntegrals("Integrator_11L0noTIS","Integrator_11L0noTIS",options_11L0noTIS_arglist,observables_arglist,mixing_params_arglist,calib_params_arglist,mass_integrals_11L0noTIS_list)
	Integrator_12L0TIS = ComputeIntegrals("Integrator_12L0TIS","Integrator_12L0TIS",options_12L0TIS_arglist,observables_arglist,mixing_params_arglist,calib_params_arglist,mass_integrals_12L0TIS_list)
	Integrator_12L0noTIS = ComputeIntegrals("Integrator_12L0noTIS","Integrator_12L0noTIS",options_12L0noTIS_arglist,observables_arglist,mixing_params_arglist,calib_params_arglist,mass_integrals_12L0noTIS_list)

	# Calculation of the invariant mass integrals for normalization.
	if wide_window: mass_argset = RooArgSet(mKp1,mKp2)
	else: mass_argset = RooArgSet(mKp1_narrowwin,mKp2_narrowwin)
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
	integral_11L0TIS_21 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_1.setVal(integral_11L0TIS_21.getVal())
	option.setVal(22)
	integral_11L0TIS_22 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_2.setVal(integral_11L0TIS_22.getVal())
	option.setVal(23)
	integral_11L0TIS_23 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_3.setVal(integral_11L0TIS_23.getVal())
	option.setVal(24)
	integral_11L0TIS_24 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_4.setVal(integral_11L0TIS_24.getVal())
	option.setVal(25)
	integral_11L0TIS_25 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_5.setVal(integral_11L0TIS_25.getVal())
	option.setVal(26)
	integral_11L0TIS_26 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_6.setVal(integral_11L0TIS_26.getVal())
	option.setVal(27)
	integral_11L0TIS_27 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_7.setVal(integral_11L0TIS_27.getVal())
	option.setVal(28)
	integral_11L0TIS_28 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_8.setVal(integral_11L0TIS_28.getVal())
	option.setVal(29)
	integral_11L0TIS_29 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_9.setVal(integral_11L0TIS_29.getVal())
	option.setVal(210)
	integral_11L0TIS_210 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_10.setVal(integral_11L0TIS_210.getVal())
	option.setVal(211)
	integral_11L0TIS_211 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_11.setVal(integral_11L0TIS_211.getVal())
	option.setVal(212)
	integral_11L0TIS_212 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_12.setVal(integral_11L0TIS_212.getVal())
	option.setVal(213)
	integral_11L0TIS_213 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_13.setVal(integral_11L0TIS_213.getVal())
	option.setVal(214)
	integral_11L0TIS_214 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_14.setVal(integral_11L0TIS_214.getVal())
	option.setVal(215)
	integral_11L0TIS_215 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_15.setVal(integral_11L0TIS_215.getVal())
	option.setVal(216)
	integral_11L0TIS_216 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_16.setVal(integral_11L0TIS_216.getVal())
	option.setVal(217)
	integral_11L0TIS_217 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_17.setVal(integral_11L0TIS_217.getVal())
	option.setVal(218)
	integral_11L0TIS_218 = Integrator_11L0TIS.createIntegral(RooArgSet(cos1))
	If_11L0TIS_18.setVal(integral_11L0TIS_218.getVal())
	option.setVal(21)
	integral_11L0noTIS_21 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_1.setVal(integral_11L0noTIS_21.getVal())
	option.setVal(22)
	integral_11L0noTIS_22 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_2.setVal(integral_11L0noTIS_22.getVal())
	option.setVal(23)
	integral_11L0noTIS_23 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_3.setVal(integral_11L0noTIS_23.getVal())
	option.setVal(24)
	integral_11L0noTIS_24 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_4.setVal(integral_11L0noTIS_24.getVal())
	option.setVal(25)
	integral_11L0noTIS_25 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_5.setVal(integral_11L0noTIS_25.getVal())
	option.setVal(26)
	integral_11L0noTIS_26 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_6.setVal(integral_11L0noTIS_26.getVal())
	option.setVal(27)
	integral_11L0noTIS_27 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_7.setVal(integral_11L0noTIS_27.getVal())
	option.setVal(28)
	integral_11L0noTIS_28 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_8.setVal(integral_11L0noTIS_28.getVal())
	option.setVal(29)
	integral_11L0noTIS_29 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_9.setVal(integral_11L0noTIS_29.getVal())
	option.setVal(210)
	integral_11L0noTIS_210 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_10.setVal(integral_11L0noTIS_210.getVal())
	option.setVal(211)
	integral_11L0noTIS_211 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_11.setVal(integral_11L0noTIS_211.getVal())
	option.setVal(212)
	integral_11L0noTIS_212 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_12.setVal(integral_11L0noTIS_212.getVal())
	option.setVal(213)
	integral_11L0noTIS_213 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_13.setVal(integral_11L0noTIS_213.getVal())
	option.setVal(214)
	integral_11L0noTIS_214 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_14.setVal(integral_11L0noTIS_214.getVal())
	option.setVal(215)
	integral_11L0noTIS_215 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_15.setVal(integral_11L0noTIS_215.getVal())
	option.setVal(216)
	integral_11L0noTIS_216 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_16.setVal(integral_11L0noTIS_216.getVal())
	option.setVal(217)
	integral_11L0noTIS_217 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_17.setVal(integral_11L0noTIS_217.getVal())
	option.setVal(218)
	integral_11L0noTIS_218 = Integrator_11L0noTIS.createIntegral(RooArgSet(cos1))
	If_11L0noTIS_18.setVal(integral_11L0noTIS_218.getVal())
	option.setVal(21)
	integral_12L0TIS_21 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_1.setVal(integral_12L0TIS_21.getVal())
	option.setVal(22)
	integral_12L0TIS_22 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_2.setVal(integral_12L0TIS_22.getVal())
	option.setVal(23)
	integral_12L0TIS_23 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_3.setVal(integral_12L0TIS_23.getVal())
	option.setVal(24)
	integral_12L0TIS_24 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_4.setVal(integral_12L0TIS_24.getVal())
	option.setVal(25)
	integral_12L0TIS_25 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_5.setVal(integral_12L0TIS_25.getVal())
	option.setVal(26)
	integral_12L0TIS_26 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_6.setVal(integral_12L0TIS_26.getVal())
	option.setVal(27)
	integral_12L0TIS_27 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_7.setVal(integral_12L0TIS_27.getVal())
	option.setVal(28)
	integral_12L0TIS_28 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_8.setVal(integral_12L0TIS_28.getVal())
	option.setVal(29)
	integral_12L0TIS_29 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_9.setVal(integral_12L0TIS_29.getVal())
	option.setVal(210)
	integral_12L0TIS_210 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_10.setVal(integral_12L0TIS_210.getVal())
	option.setVal(211)
	integral_12L0TIS_211 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_11.setVal(integral_12L0TIS_211.getVal())
	option.setVal(212)
	integral_12L0TIS_212 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_12.setVal(integral_12L0TIS_212.getVal())
	option.setVal(213)
	integral_12L0TIS_213 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_13.setVal(integral_12L0TIS_213.getVal())
	option.setVal(214)
	integral_12L0TIS_214 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_14.setVal(integral_12L0TIS_214.getVal())
	option.setVal(215)
	integral_12L0TIS_215 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_15.setVal(integral_12L0TIS_215.getVal())
	option.setVal(216)
	integral_12L0TIS_216 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_16.setVal(integral_12L0TIS_216.getVal())
	option.setVal(217)
	integral_12L0TIS_217 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_17.setVal(integral_12L0TIS_217.getVal())
	option.setVal(218)
	integral_12L0TIS_218 = Integrator_12L0TIS.createIntegral(RooArgSet(cos1))
	If_12L0TIS_18.setVal(integral_12L0TIS_218.getVal())
	option.setVal(21)
	integral_12L0noTIS_21 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_1.setVal(integral_12L0noTIS_21.getVal())
	option.setVal(22)
	integral_12L0noTIS_22 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_2.setVal(integral_12L0noTIS_22.getVal())
	option.setVal(23)
	integral_12L0noTIS_23 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_3.setVal(integral_12L0noTIS_23.getVal())
	option.setVal(24)
	integral_12L0noTIS_24 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_4.setVal(integral_12L0noTIS_24.getVal())
	option.setVal(25)
	integral_12L0noTIS_25 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_5.setVal(integral_12L0noTIS_25.getVal())
	option.setVal(26)
	integral_12L0noTIS_26 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_6.setVal(integral_12L0noTIS_26.getVal())
	option.setVal(27)
	integral_12L0noTIS_27 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_7.setVal(integral_12L0noTIS_27.getVal())
	option.setVal(28)
	integral_12L0noTIS_28 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_8.setVal(integral_12L0noTIS_28.getVal())
	option.setVal(29)
	integral_12L0noTIS_29 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_9.setVal(integral_12L0noTIS_29.getVal())
	option.setVal(210)
	integral_12L0noTIS_210 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_10.setVal(integral_12L0noTIS_210.getVal())
	option.setVal(211)
	integral_12L0noTIS_211 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_11.setVal(integral_12L0noTIS_211.getVal())
	option.setVal(212)
	integral_12L0noTIS_212 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_12.setVal(integral_12L0noTIS_212.getVal())
	option.setVal(213)
	integral_12L0noTIS_213 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_13.setVal(integral_12L0noTIS_213.getVal())
	option.setVal(214)
	integral_12L0noTIS_214 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_14.setVal(integral_12L0noTIS_214.getVal())
	option.setVal(215)
	integral_12L0noTIS_215 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_15.setVal(integral_12L0noTIS_215.getVal())
	option.setVal(216)
	integral_12L0noTIS_216 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_16.setVal(integral_12L0noTIS_216.getVal())
	option.setVal(217)
	integral_12L0noTIS_217 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
	If_12L0noTIS_17.setVal(integral_12L0noTIS_217.getVal())
	option.setVal(218)
	integral_12L0noTIS_218 = Integrator_12L0noTIS.createIntegral(RooArgSet(cos1))
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
	integral_11L0TIS_91 = Integrator_11L0TIS.createIntegral(RooArgSet(t))
	IT_11L0TIS_cosh.setVal(integral_11L0TIS_91.getVal())
	option.setVal(92)
	integral_11L0TIS_92 = Integrator_11L0TIS.createIntegral(RooArgSet(t))
	IT_11L0TIS_sinh.setVal(integral_11L0TIS_92.getVal())
	option.setVal(93)
	integral_11L0TIS_93 = Integrator_11L0TIS.createIntegral(RooArgSet(t))
	IT_11L0TIS_cos.setVal(integral_11L0TIS_93.getVal())
	option.setVal(94)
	integral_11L0TIS_94 = Integrator_11L0TIS.createIntegral(RooArgSet(t))
	IT_11L0TIS_sin.setVal(integral_11L0TIS_94.getVal())
	option.setVal(91)
	integral_11L0noTIS_91 = Integrator_11L0noTIS.createIntegral(RooArgSet(t))
	IT_11L0noTIS_cosh.setVal(integral_11L0noTIS_91.getVal())
	option.setVal(92)
	integral_11L0noTIS_92 = Integrator_11L0noTIS.createIntegral(RooArgSet(t))
	IT_11L0noTIS_sinh.setVal(integral_11L0noTIS_92.getVal())
	option.setVal(93)
	integral_11L0noTIS_93 = Integrator_11L0noTIS.createIntegral(RooArgSet(t))
	IT_11L0noTIS_cos.setVal(integral_11L0noTIS_93.getVal())
	option.setVal(94)
	integral_11L0noTIS_94 = Integrator_11L0noTIS.createIntegral(RooArgSet(t))
	IT_11L0noTIS_sin.setVal(integral_11L0noTIS_94.getVal())
	option.setVal(91)
	integral_12L0TIS_91 = Integrator_12L0TIS.createIntegral(RooArgSet(t))
	IT_12L0TIS_cosh.setVal(integral_12L0TIS_91.getVal())
	option.setVal(92)
	integral_12L0TIS_92 = Integrator_12L0TIS.createIntegral(RooArgSet(t))
	IT_12L0TIS_sinh.setVal(integral_12L0TIS_92.getVal())
	option.setVal(93)
	integral_12L0TIS_93 = Integrator_12L0TIS.createIntegral(RooArgSet(t))
	IT_12L0TIS_cos.setVal(integral_12L0TIS_93.getVal())
	option.setVal(94)
	integral_12L0TIS_94 = Integrator_12L0TIS.createIntegral(RooArgSet(t))
	IT_12L0TIS_sin.setVal(integral_12L0TIS_94.getVal())
	option.setVal(91)
	integral_12L0noTIS_91 = Integrator_12L0noTIS.createIntegral(RooArgSet(t))
	IT_12L0noTIS_cosh.setVal(integral_12L0noTIS_91.getVal())
	option.setVal(92)
	integral_12L0noTIS_92 = Integrator_12L0noTIS.createIntegral(RooArgSet(t))
	IT_12L0noTIS_sinh.setVal(integral_12L0noTIS_92.getVal())
	option.setVal(93)
	integral_12L0noTIS_93 = Integrator_12L0noTIS.createIntegral(RooArgSet(t))
	IT_12L0noTIS_cos.setVal(integral_12L0noTIS_93.getVal())
	option.setVal(94)
	integral_12L0noTIS_94 = Integrator_12L0noTIS.createIntegral(RooArgSet(t))
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

	RooMsgService.instance().setGlobalKillBelow(RooFit.INFO)
	option.setVal(0)

	# Construction of the PDFs.
	PDF_11L0TIS = KpiKpiSpectrumNW(name+'_11L0TIS',description+'_11L0TIS',options_11L0TIS_arglist,observables_arglist,wave_fractions_arglist,dirCP_asyms_arglist,\
strong_phases_arglist,weak_phases_arglist,mixing_params_arglist,calib_params_arglist,cond_distr_params_list,sys_studies_arglist,mass_integrals_11L0TIS_list,\
ang_integrals_11L0TIS_list,time_integrals_11L0TIS_list)
	PDF_11L0noTIS = KpiKpiSpectrumNW(name+'_11L0noTIS',description+'_11L0noTIS',options_11L0noTIS_arglist,observables_arglist,wave_fractions_arglist,dirCP_asyms_arglist,\
strong_phases_arglist,weak_phases_arglist,mixing_params_arglist,calib_params_arglist,cond_distr_params_list,sys_studies_arglist,mass_integrals_11L0noTIS_list,\
ang_integrals_11L0noTIS_list,time_integrals_11L0noTIS_list)
	PDF_12L0TIS = KpiKpiSpectrumNW(name+'_12L0TIS',description+'_12L0TIS',options_12L0TIS_arglist,observables_arglist,wave_fractions_arglist,dirCP_asyms_arglist,\
strong_phases_arglist,weak_phases_arglist,mixing_params_arglist,calib_params_arglist,cond_distr_params_list,sys_studies_arglist,mass_integrals_12L0TIS_list,\
ang_integrals_12L0TIS_list,time_integrals_12L0TIS_list)
	PDF_12L0noTIS = KpiKpiSpectrumNW(name+'_12L0noTIS',description+'_12L0noTIS',options_12L0noTIS_arglist,observables_arglist,wave_fractions_arglist,dirCP_asyms_arglist,\
strong_phases_arglist,weak_phases_arglist,mixing_params_arglist,calib_params_arglist,cond_distr_params_list,sys_studies_arglist,mass_integrals_12L0noTIS_list,\
ang_integrals_12L0noTIS_list,time_integrals_12L0noTIS_list)

	return PDF_11L0TIS, PDF_11L0noTIS, PDF_12L0TIS, PDF_12L0noTIS

def etacomb(q1var,eta1var,q2var,eta2var):
   p_Bs = (1.+0.5*q1var*(1.-q1var-2.*eta1var))*(1.+0.5*q2var*(1.-q2var-2.*eta2var))
   p_Bsbar = (1.-0.5*q1var*(1.+q1var-2.*eta1var))*(1.-0.5*q2var*(1.+q2var-2.*eta2var))
   return min(p_Bs,p_Bsbar)/(p_Bs+p_Bsbar)

def loadData(file_path, datatype, data_file, data_tree, MC_file, MC_tree, weighted, wide_window = 1, evnum_limit = 0, GRID = 0):

	# Information.
	print "\n#####################################################################"
	print " I N P U T   D A T A"
	print "#####################################################################\n"
	if (evnum_limit == 0): print 'All events selected.'
	else: print str(evnum_limit)+' events selected.'
	if weighted: print 'Using sWeights.'
	else: print 'Not using sWeights.'

	# Input file.
	if (GRID == 1):
		print 'Loading data from InvariantMassFitOut.dat'
		tree = TTree("DecayTree","DecayTree")
		tree.ReadFile("InvariantMassFitOut.dat",m1_name+":"+m2_name+":"+cos1_name+":"+cos2_name+":"+phi_name+":"+t_name+":"+terror_name+":"+dec_SSK_name+":"+dec_OS_name+":"+eta_SSK_name+":"+eta_OS_name+":itype:"+L0TISline_name+":"+L0TOSline_name+":"+mKpiKpi_name+":"+weight_name)
	else:
		if (datatype == "real"):
			file_in = TFile(file_path + data_file)
			tree = file_in.Get(data_tree)
			print 'Loading data from ' + data_file + ':' + data_tree
		elif (datatype == "MC"):
			file_in = TFile(file_path + MC_file)
			tree = file_in.Get(MC_tree)
			print 'Loading data from ' + MC_file + ':' + MC_tree

	# Tree with the selected events.
	file_out = TFile(file_path + "trash.root","recreate")
	if wide_window: range_cut = m1_name+"<=1500. && "+m2_name+"<=1500. && "+t_name+">=0. && "+t_name+"<=12. && "+eta_SSK_name+"<=0.5 && "+eta_OS_name+"<=0.5"
	else: range_cut = "abs("+m1_name+"-900.)<150. && abs("+m2_name+"-900.)<150. && "+t_name+">=0. && "+t_name+"<=12. && "+eta_SSK_name+"<=0.5 && "+eta_OS_name+"<=0.5"
	tree2 = tree.CopyTree(range_cut)

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
	if (wide_window):
		data_11L0TIS_ = RooDataSet("data_11L0TIS_","data_11L0TIS_",RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
		data_11L0noTIS_ = RooDataSet("data_11L0noTIS_","data_11L0noTIS_",RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
		data_12L0TIS_ = RooDataSet("data_12L0TIS_","data_12L0TIS_",RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
		data_12L0noTIS_ = RooDataSet("data_12L0noTIS_","data_12L0noTIS_",RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
	else:
		data_11L0TIS_ = RooDataSet("data_11L0TIS_","data_11L0TIS_",RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
		data_11L0noTIS_ = RooDataSet("data_11L0noTIS_","data_11L0noTIS_",RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
		data_12L0TIS_ = RooDataSet("data_12L0TIS_","data_12L0TIS_",RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
		data_12L0noTIS_ = RooDataSet("data_12L0noTIS_","data_12L0noTIS_",RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
	more_real_11L0TIS = RooDataSet("more_real_11L0TIS","more_real_11L0TIS",RooArgSet(etamistag_SSK,etamistag_OS,terror))
	more_real_11L0noTIS = RooDataSet("more_real_11L0noTIS","more_real_11L0noTIS",RooArgSet(etamistag_SSK,etamistag_OS,terror))
	more_real_12L0TIS = RooDataSet("more_real_12L0TIS","more_real_12L0TIS",RooArgSet(etamistag_SSK,etamistag_OS,terror))
	more_real_12L0noTIS = RooDataSet("more_real_12L0noTIS","more_real_12L0noTIS",RooArgSet(etamistag_SSK,etamistag_OS,terror))
	more_cat_11L0TIS = RooDataSet("more_cat_11L0TIS","more_cat_11L0TIS",RooArgSet(decision_SSK,decision_OS))
	more_cat_11L0noTIS = RooDataSet("more_cat_11L0noTIS","more_cat_11L0noTIS",RooArgSet(decision_SSK,decision_OS))
	more_cat_12L0TIS = RooDataSet("more_cat_12L0TIS","more_cat_12L0TIS",RooArgSet(decision_SSK,decision_OS))
	more_cat_12L0noTIS = RooDataSet("more_cat_12L0noTIS","more_cat_12L0noTIS",RooArgSet(decision_SSK,decision_OS))
	hist_mistag_SSK = RooDataHist("hist_mistag_SSK","hist_mistag_SSK",RooArgSet(etamistag_SSK))
	hist_mistag_OS = RooDataHist("hist_mistag_OS","hist_mistag_OS",RooArgSet(etamistag_OS))
	hist_deltat = RooDataHist("hist_deltat","hist_deltat",RooArgSet(terror))
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
					if eval("i."+L0TISline_name) == 1:
						if weighted:
							weight_fit.setVal(corrfactor[0][0]*eval("i."+weight_name))
							weight_plot.setVal(eval("i."+weight_name))
						if (wide_window): data_11L0TIS_.add(RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
						else: data_11L0TIS_.add(RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
						more_real_11L0TIS.add(RooArgSet(etamistag_SSK,etamistag_OS,terror))
						more_cat_11L0TIS.add(RooArgSet(decision_SSK,decision_OS))
						ev_counter_11L0TIS += 1
					elif (eval("i."+L0TISline_name) == 0 and eval("i."+L0TOSline_name) == 1):
						if weighted:
							weight_fit.setVal(corrfactor[0][1]*eval("i."+weight_name))
							weight_plot.setVal(eval("i."+weight_name))
						if (wide_window): data_11L0noTIS_.add(RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
						else: data_11L0noTIS_.add(RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
						more_real_11L0noTIS.add(RooArgSet(etamistag_SSK,etamistag_OS,terror))
						more_cat_11L0noTIS.add(RooArgSet(decision_SSK,decision_OS))
						ev_counter_11L0noTIS += 1
				elif i.itype == 81:
					if eval("i."+L0TISline_name) == 1:
						if weighted:
							weight_fit.setVal(corrfactor[1][0]*eval("i."+weight_name))
							weight_plot.setVal(eval("i."+weight_name))
						if (wide_window): data_12L0TIS_.add(RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
						else: data_12L0TIS_.add(RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
						more_real_12L0TIS.add(RooArgSet(etamistag_SSK,etamistag_OS,terror))
						more_cat_12L0TIS.add(RooArgSet(decision_SSK,decision_OS))
						ev_counter_12L0TIS += 1
					elif (eval("i."+L0TISline_name) == 0 and eval("i."+L0TOSline_name) == 1):
						if weighted:
							weight_fit.setVal(corrfactor[1][1]*eval("i."+weight_name))
							weight_plot.setVal(eval("i."+weight_name))
						if (wide_window): data_12L0noTIS_.add(RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
						else: data_12L0noTIS_.add(RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
						more_real_12L0noTIS.add(RooArgSet(etamistag_SSK,etamistag_OS,terror))
						more_cat_12L0noTIS.add(RooArgSet(decision_SSK,decision_OS))
						ev_counter_12L0noTIS += 1

			elif (datatype == "MC"):
				rannum = random.Random().uniform(0,1)
				if (rannum<=0.25):
					if (wide_window): data_11L0TIS_.add(RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
					else: data_11L0TIS_.add(RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
					more_real_11L0TIS.add(RooArgSet(etamistag_SSK,etamistag_OS,terror))
					more_cat_11L0TIS.add(RooArgSet(decision_SSK,decision_OS))
					ev_counter_11L0TIS += 1
				elif (rannum>0.25 and rannum<=0.5):
					if (wide_window): data_11L0noTIS_.add(RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
					else: data_11L0noTIS_.add(RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
					more_real_11L0noTIS.add(RooArgSet(etamistag_SSK,etamistag_OS,terror))
					more_cat_11L0noTIS.add(RooArgSet(decision_SSK,decision_OS))
					ev_counter_11L0noTIS += 1
				elif (rannum>0.5 and rannum<=0.75):
					if (wide_window): data_12L0TIS_.add(RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
					else: data_12L0TIS_.add(RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
					more_real_12L0TIS.add(RooArgSet(etamistag_SSK,etamistag_OS,terror))
					more_cat_12L0TIS.add(RooArgSet(decision_SSK,decision_OS))
					ev_counter_12L0TIS += 1
				else:
					if (wide_window): data_12L0noTIS_.add(RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,weight_fit,weight_plot))
					else: data_12L0noTIS_.add(RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,weight_fit,weight_plot))
					more_real_12L0noTIS.add(RooArgSet(etamistag_SSK,etamistag_OS,terror))
					more_cat_12L0noTIS.add(RooArgSet(decision_SSK,decision_OS))
					ev_counter_12L0noTIS += 1

			if (datatype == "real") and weighted:
				if (etamistag_SSK.getVal() < 0.5): hist_mistag_SSK.add(RooArgSet(etamistag_SSK),eval("i."+weight_name))
				if (etamistag_OS.getVal() < 0.5): hist_mistag_OS.add(RooArgSet(etamistag_OS),eval("i."+weight_name))
				hist_deltat.add(RooArgSet(terror),eval("i."+weight_name))
			else:
				if (etamistag_SSK.getVal() < 0.5): hist_mistag_SSK.add(RooArgSet(etamistag_SSK),1)
				if (etamistag_OS.getVal() < 0.5): hist_mistag_OS.add(RooArgSet(etamistag_OS),1)
				hist_deltat.add(RooArgSet(terror),1)
			ev_counter += 1
	data_11L0TIS_.merge(more_real_11L0TIS)
	data_11L0noTIS_.merge(more_real_11L0noTIS)
	data_12L0TIS_.merge(more_real_12L0TIS)
	data_12L0noTIS_.merge(more_real_12L0noTIS)
	data_11L0TIS_.merge(more_cat_11L0TIS)
	data_11L0noTIS_.merge(more_cat_11L0noTIS)
	data_12L0TIS_.merge(more_cat_12L0TIS)
	data_12L0noTIS_.merge(more_cat_12L0noTIS)
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
	print str(ev_counter) + ' events loaded.'
	if (datatype == "real") and weighted: print 'Eff. yield categ. distribution: cat[2011,L0TIS] = '+str(int(corrfactor[0][0]*sumw[0][0]))+ ', cat[2011,L0noTIS] = '+str(int(corrfactor[0][1]*sumw[0][1]))+', cat[2012,L0TIS] = '+str(int(corrfactor[1][0]*sumw[1][0]))+ ', cat[2012,L0noTIS] = '+str(int(corrfactor[1][1]*sumw[1][1]))
	else: print 'Yield categ. distribution: cat[2011,L0TIS] = '+str(ev_counter_11L0TIS)+ ', cat[2011,L0noTIS] = '+str(ev_counter_11L0noTIS)+', cat[2012,L0TIS] = '+str(ev_counter_12L0TIS)+ ', cat[2012,L0noTIS] = '+str(ev_counter_12L0noTIS)

	data_full_ = RooDataSet("data_full_","data_full_",data_11L0TIS_.get(),RooFit.Index(yeartrigcat),RooFit.Import("2011_L0TIS",data_11L0TIS_),RooFit.Import("2011_L0noTIS",data_11L0noTIS_),\
RooFit.Import("2012_L0TIS",data_12L0TIS_),RooFit.Import("2012_L0noTIS",data_12L0noTIS_))

	if wide_window:
		data_full_fit = RooDataSet("data_full_fit","data_full_fit",data_full_,FullArgSetFitWide,"",weight_name+"_fit")
		data_full_plot = RooDataSet("data_full_plot","data_full_plot",data_full_,FullArgSetPlotWide,"",weight_name+"_plot")
	else:
		data_full_fit = RooDataSet("data_full_fit","data_full_fit",data_full_,FullArgSetFitNarrow,"",weight_name+"_fit")
		data_full_plot = RooDataSet("data_full_plot","data_full_plot",data_full_,FullArgSetPlotNarrow,"",weight_name+"_plot")

	file_out.Close()

	return [data_full_fit,data_full_plot,data_11L0TIS_,data_11L0noTIS_,data_12L0TIS_,data_12L0noTIS_], hist_mistag_SSK, hist_mistag_OS, hist_deltat

def createPDF(Blinding, NOCP, NODIRCP, SAMECP, acc_type, inf_t_res, wide_window, data_file,\
fix_wave_fractions = 0, fix_dirCP_asyms = 0, fix_strong_phases = 0, fix_weak_phases = 0, fix_mixing_params = 0, fix_calib_params = 0,\
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
	for argument in wave_fractions: wave_fractions_list.add(argument)
	for argument in strong_phases: strong_phases_list.add(argument)
	for argument in mixing_params: mixing_params_list.add(argument)
	for argument in calib_params: calib_params_list.add(argument)
	for argument in cond_distr_params: cond_distr_params_list.add(argument)
	for argument in sys_studies: sys_studies_list.add(argument)

	# If narrow window is used: removal of the unnecesary CP conserving parameters.
	if (not wide_window):
		f_Swave.setVal(1.)
		f_Swave.setConstant(1)
		f_VTTV.setConstant(1)
		f_TT.setConstant(1)
		D_VTTV.setConstant(1)
		D_STTS.setConstant(1)
		fL_VT.setConstant(1)
		xpar_VT.setConstant(1)
		fL_TV.setConstant(1)
		xpar_TV.setConstant(1)
		fL_TT.setConstant(1)
		xpar1_TT.setConstant(1)
		xperp1_TT.setConstant(1)
		xpar2_TT.setConstant(1)
		delta02.setConstant(1)
		delta20.setConstant(1)
		delta120.setConstant(1)
		delta12par.setConstant(1)
		delta12perp.setConstant(1)
		delta210.setConstant(1)
		delta21par.setConstant(1)
		delta21perp.setConstant(1)
		delta220.setConstant(1)
		delta22par.setConstant(1)
		delta22perp.setConstant(1)
		delta22par2.setConstant(1)
		delta22perp2.setConstant(1)

	# Printing out the list with the free physical parameters in the PDF.
	parameters = []
	print "\n#####################################################################"
	print " F R E E   P H Y S I C A L   P A R A M E T E R S"
	print "#####################################################################"
	lenghts = [len(wave_fractions),len(dirCP_asyms),len(strong_phases),len(weak_phases),len(mixing_params),len(calib_params)]
	lists = [wave_fractions_list,dirCP_asyms_list,strong_phases_list,weak_phases_list,mixing_params_list,calib_params_list]
	lists_unblinded = [wave_fractions_list,dirCP_asyms_unblinded_list,strong_phases_list,weak_phases_unblinded_list,mixing_params_list,calib_params_list]
	fixed_list = [fix_wave_fractions,fix_dirCP_asyms,fix_strong_phases,fix_weak_phases,fix_mixing_params,fix_calib_params]
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

	model = PDF_with_integrals("model","model",options_list,wide_window,data_file,observables_list,wave_fractions_list,dirCP_asyms_list,\
strong_phases_list,weak_phases_list,mixing_params_list,calib_params_list,sys_studies_list)

	return model, parameters


def createSimPDF(Blinding, NOCP, NODIRCP, SAMECP, acc_type, inf_t_res, wide_window, data_file,\
fix_wave_fractions = 0, fix_dirCP_asyms = 0, fix_strong_phases = 0, fix_weak_phases = 0, fix_mixing_params = 0, fix_calib_params = 0,\
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
	for argument in options_11L0TIS: options_11L0TIS_list.add(argument)
	for argument in options_11L0noTIS: options_11L0noTIS_list.add(argument)
	for argument in options_12L0TIS: options_12L0TIS_list.add(argument)
	for argument in options_12L0noTIS: options_12L0noTIS_list.add(argument)
	for argument in wave_fractions: wave_fractions_list.add(argument)
	for argument in strong_phases: strong_phases_list.add(argument)
	for argument in mixing_params: mixing_params_list.add(argument)
	for argument in calib_params: calib_params_list.add(argument)
	for argument in cond_distr_params: cond_distr_params_list.add(argument)
	for argument in sys_studies: sys_studies_list.add(argument)

	# If narrow window is used: removal of the unnecesary CP conserving parameters.
	if (not wide_window):
		f_Swave.setVal(1.)
		f_Swave.setConstant(1)
		f_VTTV.setConstant(1)
		f_TT.setConstant(1)
		D_VTTV.setConstant(1)
		D_STTS.setConstant(1)
		fL_VT.setConstant(1)
		xpar_VT.setConstant(1)
		fL_TV.setConstant(1)
		xpar_TV.setConstant(1)
		fL_TT.setConstant(1)
		xpar1_TT.setConstant(1)
		xperp1_TT.setConstant(1)
		xpar2_TT.setConstant(1)
		delta02.setConstant(1)
		delta20.setConstant(1)
		delta120.setConstant(1)
		delta12par.setConstant(1)
		delta12perp.setConstant(1)
		delta210.setConstant(1)
		delta21par.setConstant(1)
		delta21perp.setConstant(1)
		delta220.setConstant(1)
		delta22par.setConstant(1)
		delta22perp.setConstant(1)
		delta22par2.setConstant(1)
		delta22perp2.setConstant(1)

	# Printing out the list with the free physical parameters in the PDF.
	parameters = []
	print "\n#####################################################################"
	print " F R E E   P H Y S I C A L   P A R A M E T E R S"
	print "#####################################################################"
	lenghts = [len(wave_fractions),len(dirCP_asyms),len(strong_phases),len(weak_phases),len(mixing_params),len(calib_params)]
	lists = [wave_fractions_list,dirCP_asyms_list,strong_phases_list,weak_phases_list,mixing_params_list,calib_params_list]
	lists_unblinded = [wave_fractions_list,dirCP_asyms_unblinded_list,strong_phases_list,weak_phases_unblinded_list,mixing_params_list,calib_params_list]
	fixed_list = [fix_wave_fractions,fix_dirCP_asyms,fix_strong_phases,fix_weak_phases,fix_mixing_params,fix_calib_params]
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
wide_window,data_file,observables_list,wave_fractions_list,dirCP_asyms_list,strong_phases_list,weak_phases_list,mixing_params_list,calib_params_list,sys_studies_list)

	model_full = RooSimultaneous("model_full","model_full",yeartrigcat)
	model_full.addPdf(model_11L0TIS,"2011_L0TIS")
	model_full.addPdf(model_11L0noTIS,"2011_L0noTIS")
	model_full.addPdf(model_12L0TIS,"2012_L0TIS")
	model_full.addPdf(model_12L0noTIS,"2012_L0noTIS")

	return [model_full,model_11L0TIS,model_11L0noTIS,model_12L0TIS,model_12L0noTIS], parameters

def DoFit(model_,data_,num_CPU,minos_opt,strategy_option,fix_mixing,fix_calib):

   # Function to perform the fit.

   if fix_mixing:
      if fix_calib:
         res = model_.fitTo(data_,RooFit.NumCPU(num_CPU),RooFit.Minos(minos_opt),RooFit.Strategy(strategy_option),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE))
      else:
         res = model_.fitTo(data_,RooFit.NumCPU(num_CPU),RooFit.Minos(minos_opt),RooFit.Strategy(strategy_option),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE),RooFit.ExternalConstraints(RooArgSet(ctrt_p0metac_SSK,ctrt_Dp0half_SSK,ctrt_p1_SSK,ctrt_Dp1half_SSK,ctrt_p0metac_OS,ctrt_Dp0half_OS,ctrt_p1_OS,ctrt_Dp1half_OS)))

   else:
      if fix_calib:
         res = model_.fitTo(data_,RooFit.NumCPU(num_CPU),RooFit.Minos(minos_opt),RooFit.Strategy(strategy_option),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE),RooFit.ExternalConstraints(RooArgSet(ctrt_delta_m_Bs,ctrt_gamma_Bs,ctrt_delta_gamma_Bs)))
      else:
         ctrtargset = RooArgSet(ctrt_delta_m_Bs,ctrt_gamma_Bs,ctrt_delta_gamma_Bs,ctrt_p0metac_SSK,ctrt_Dp0half_SSK,ctrt_p1_SSK,ctrt_Dp1half_SSK,ctrt_p0metac_OS,ctrt_Dp0half_OS)
         ctrtargset.add(ctrt_p1_OS)
         ctrtargset.add(ctrt_Dp1half_OS)
         res = model_.fitTo(data_,RooFit.NumCPU(num_CPU),RooFit.Minos(minos_opt),RooFit.Strategy(strategy_option),RooFit.Timer(kTRUE),RooFit.SumW2Error(kTRUE),RooFit.Save(kTRUE),RooFit.ExternalConstraints(ctrtargset))

   return res

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

def errorscan(PDF_,method_,n,nt,t0,tlimit):
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
                                    if isnan(PDFfun(PDF_,method_,750.+float(i_m1)/n*(1050.-750.),750.+float(i_m2)/n*(1050.-750.),-1.+float(i_cos1)/n*2.,-1.+float(i_cos2)/n*2.,-3.141593+float(i_phi)/n*2.*3.141593,t0+float(i_t)/nt*(tlimit-t0),float(i_dt)/n*0.08,i_q1,i_q2,float(i_eta1)/n*0.5,float(i_eta2)/n*0.5)):
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

def printresultoldformat(fitresult):

   fparallel = RooFormulaVar("fparallel","fparallel","(1.-fL_VV)*xpar_VV",RooArgList(fL_VV,xpar_VV))
   deltaperpplus = RooFormulaVar("deltaperpplus","deltaperpplus","delta11perp-deltaphaseplus_100",RooArgList(delta11perp,deltaphaseplus_100))
   modSS2 = RooFormulaVar("modSS2","modSS2","(1.-f_VV)*f_Swave*f_SS",RooArgList(f_VV,f_Swave,f_SS))

   print '************************************'
   print 'fL =',round(fL_VV.getVal(),3),'+-',round(fL_VV.getError(),3)
   print 'fparallel =',round(fparallel.getVal(),3),'+-',round(fparallel.getPropagatedError(fitresult),3)
   print '|As-|2 =',round(avsqmodminus_100.getVal(),3),'+-',round(avsqmodminus_100.getPropagatedError(fitresult),3)
   print '|As+|2 =',round(avsqmodplus_100.getVal(),3),'+-',round(avsqmodplus_100.getPropagatedError(fitresult),3)
   print '|Ass|2 =',round(modSS2.getVal(),3),'+-',round(modSS2.getPropagatedError(fitresult),3)
   print 'deltaparallel =',round(delta11par.getVal(),2),'+-',round(delta11par.getError(),2)
   print 'deltaperp-deltasplus =',round(deltaperpplus.getVal(),2),'+-',round(deltaperpplus.getPropagatedError(fitresult),2)
   print 'deltasminus =',round(deltaphaseminus_100.getVal(),2),'+-',round(deltaphaseminus_100.getPropagatedError(fitresult),2)
   print 'deltass =',round(delta00.getVal(),2),'+-',round(delta00.getError(),2)
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
		partext += '\\hline\n\\hline\n\\end{tabular}\n\\end{table}\n\n'
	partext += '\\end{document}'
	partext = partext.replace('#','\\')
	partext = partext.replace('\\hline\n\\end{tabular}','\\end{tabular}')

	texfile = open(filename+'.tex','w')
	texfile.write(partext)
	texfile.close()
	#os.system('pdflatex '+filename+'.tex')

def CondVarStudy(fit_bool,model_,parameters_,data_,hist_mistag_SSK_,hist_mistag_OS_,hist_deltat_):

	if fit_bool:
		hist_mistag_SSK_.plotOn(frame_eta_SSK,RooFit.Binning(25))
		hist_mistag_OS_.plotOn(frame_eta_OS,RooFit.Binning(25))
		hist_deltat_.plotOn(frame_terr,RooFit.Binning(25))
		for i in observables: i.setConstant(1)
		for i in observables_narrowwin: i.setConstant(1)
		for i in parameters_: i.setConstant(1)

		# Fit of the t_err distribution.
		for i in [gamma1_dt,beta1_dt,c_dt,gamma2_dt,beta2_dt]: i.setConstant(0)
		alt_fit.setVal(1)
		model_.fitTo(hist_deltat_,RooFit.SumW2Error(kTRUE))
		model_.plotOn(frame_terr)
		for i in [gamma1_dt,beta1_dt,c_dt,gamma2_dt,beta2_dt]: i.setConstant(1)

		# Fit of the eta_SSK distribution.
		for i in [mu1_SSK,sigma1_SSK,c_SSK,mu2_SSK,sigma2_SSK]: i.setConstant(0)
		alt_fit.setVal(2)
		model_.fitTo(hist_mistag_SSK_,RooFit.SumW2Error(kTRUE))
		model_.plotOn(frame_eta_SSK)
		for i in [mu1_SSK,sigma1_SSK,c_SSK,mu2_SSK,sigma2_SSK]: i.setConstant(1)

		# Fit of the eta_OS distribution.
		for i in [mu1_OS,sigma1_OS,c_OS,mu2_OS,sigma2_OS]: i.setConstant(0)
		alt_fit.setVal(3)
		model_.fitTo(hist_mistag_OS_,RooFit.SumW2Error(kTRUE))
		model_.plotOn(frame_eta_OS)
		for i in [mu1_OS,sigma1_OS,c_OS,mu2_OS,sigma2_OS]: i.setConstant(1)

		alt_fit.setVal(0)
		for i in observables: i.setConstant(0)
		for i in observables_narrowwin: i.setConstant(0)
		for i in parameters_: i.setConstant(0)

		# Plot of the resulting distributions.
		c_cond = TCanvas("c_cond","c_cond",1800,600)
		c_cond.Divide(3)
		c_cond.cd(1)
		frame_eta_SSK.Draw()
		c_cond.cd(2)
		frame_eta_OS.Draw()
		c_cond.cd(3)
		frame_terr.Draw()
		c_cond.Print("plotCondVar.pdf")

def genTree(nevents,model,output_tag):
	print 'Generating events ...'
	d_ = model.generate(FullArgSet,nevents)
	print 'Events generated.'
	d_.write("tmp.dat")
	gROOT.Reset()
	fout = TFile(output_tag + "_" + str(nevents) + "ev.root","RECREATE")
	tout = TTree("DecayTree","DecayTree")
	tout.ReadFile("tmp.dat",m1_name+":"+m2_name+":"+cos1_name+":"+cos2_name+":"+phi_name+":"+t_name+":"+terror_name+":"+dec_SSK_name+":"+dec_OS_name+":"+eta_SSK_name+":"+eta_OS_name)
	tout.Write()
	fout.Close()
	os.system("rm tmp.dat")

def doToyMCStudy(nexp,neve,model,output_tag,job_id,GRID,num_CPU,minos_opt,strategy_option,fix_mixing,fix_calib):

	RooRandom.randomGenerator().SetSeed(0)

	start = time.time()

	pdf_arglist = RooArgList(model)
	ctrtvar_argset = RooArgSet()

	if fix_mixing:
		if fix_calib:
			MCS = RooMCStudy(model,FullArgSet,RooFit.Silence(),RooFit.FitOptions(RooFit.NumCPU(num_CPU),RooFit.Minos(minos_opt),RooFit.Strategy(strategy_option),RooFit.Timer(kTRUE),RooFit.Save(kTRUE)))
			print 'Mixing and calibration parameters fixed during the toy studies.'
		else:
			map(lambda x:pdf_arglist.add(x),[ctrt_p0metac_SSK,ctrt_Dp0half_SSK,ctrt_p1_SSK,ctrt_Dp1half_SSK,ctrt_p0metac_OS,ctrt_Dp0half_OS,ctrt_p1_OS,ctrt_Dp1half_OS])
			map(lambda x:ctrtvar_argset.add(x),[p0metac_SSK,Dp0half_SSK,p1_SSK,Dp1half_SSK,p0metac_OS,Dp0half_OS,p1_OS,Dp1half_OS])
			model_constrained = RooProdPdf("model_constrained","model_constrained",pdf_arglist)
			MCS = RooMCStudy(model_constrained,FullArgSet,RooFit.Constrain(ctrtvar_argset),RooFit.Silence(),RooFit.FitOptions(RooFit.NumCPU(num_CPU),RooFit.Minos(minos_opt),RooFit.Strategy(strategy_option),RooFit.Timer(kTRUE),RooFit.Save(kTRUE)))
			print 'Mixing parameters fixed during the toy studies. Calibration parameters gaussian constrained.'

	else:
		if fix_calib:
			map(lambda x:pdf_arglist.add(x),[ctrt_delta_m_Bs,ctrt_gamma_Bs,ctrt_delta_gamma_Bs])
			map(lambda x:ctrtvar_argset.add(x),[delta_m_Bs,gamma_Bs,delta_gamma_Bs])
			model_constrained = RooProdPdf("model_constrained","model_constrained",pdf_arglist)
			MCS = RooMCStudy(model_constrained,FullArgSet,RooFit.Constrain(ctrtvar_argset),RooFit.Silence(),RooFit.FitOptions(RooFit.NumCPU(num_CPU),RooFit.Minos(minos_opt),RooFit.Strategy(strategy_option),RooFit.Timer(kTRUE),RooFit.Save(kTRUE)))
			print 'Calibration parameters fixed during the toy studies. Mixing parameters gaussian constrained.'
		else:
			map(lambda x:pdf_arglist.add(x),[ctrt_delta_m_Bs,ctrt_gamma_Bs,ctrt_delta_gamma_Bs,ctrt_p0metac_SSK,ctrt_Dp0half_SSK,ctrt_p1_SSK,ctrt_Dp1half_SSK,ctrt_p0metac_OS,ctrt_Dp0half_OS,ctrt_p1_OS,ctrt_Dp1half_OS])
			map(lambda x:ctrtvar_argset.add(x),[delta_m_Bs,gamma_Bs,delta_gamma_Bs,p0metac_SSK,Dp0half_SSK,p1_SSK,Dp1half_SSK,p0metac_OS,Dp0half_OS,p1_OS,Dp1half_OS])
			model_constrained = RooProdPdf("model_constrained","model_constrained",pdf_arglist)
			MCS = RooMCStudy(model_constrained,FullArgSet,RooFit.Constrain(ctrtvar_argset),RooFit.Silence(),RooFit.FitOptions(RooFit.NumCPU(num_CPU),RooFit.Minos(minos_opt),RooFit.Strategy(strategy_option),RooFit.Timer(kTRUE),RooFit.Save(kTRUE)))
			print 'Mixing and calibration parameters gaussian constrained during the toy studies.'

	MCS.generateAndFit(nexp,neve)

	fout_MCS = TFile("MCS.root","RECREATE")
	tout_MCS = TTree("tree","tree")

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
	frame = parameter.frame(RooFit.Title(parameter.GetName()))
	nll.plotOn(frame,RooFit.PrintEvalErrors(0),RooFit.ShiftToZero(),RooFit.LineColor(kRed))
	c = TCanvas("c_"+parameter.GetName(),"c_"+parameter.GetName())
	frame.Draw()
	c.Print("plotllprofile_" + parameter.GetName() + ".pdf")

def plot61Ddata(data, step, wide_window = 1, mbinning = 40, cosbinning = 40, phibinning = 40, tbinning = 40):

	if wide_window:
		data.plotOn(frame_m1,RooFit.Name("data_"+str(step)),RooFit.Binning(mbinning))
		data.plotOn(frame_m2,RooFit.Name("data_"+str(step)),RooFit.Binning(mbinning))
	else:
		data.plotOn(frame_m1_narrowwin,RooFit.Name("data_"+str(step)),RooFit.Binning(mbinning))
		data.plotOn(frame_m2_narrowwin,RooFit.Name("data_"+str(step)),RooFit.Binning(mbinning))
	data.plotOn(frame_cos1,RooFit.Name("data_"+str(step)),RooFit.Binning(cosbinning))
	data.plotOn(frame_cos2,RooFit.Name("data_"+str(step)),RooFit.Binning(cosbinning))
	data.plotOn(frame_phi,RooFit.Name("data_"+str(step)),RooFit.Binning(phibinning))
	data.plotOn(frame_t,RooFit.Name("data_"+str(step)),RooFit.Binning(tbinning))

def plot61Dmodel(model, normdata, wide_window = 1, color = kBlue):

	if wide_window:
		model.plotOn(frame_m1,RooFit.Name("model"),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(color))
		model.plotOn(frame_m2,RooFit.Name("model"),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(color))
	else:
		model.plotOn(frame_m1_narrowwin,RooFit.Name("model"),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(color))
		model.plotOn(frame_m2_narrowwin,RooFit.Name("model"),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(color))
	model.plotOn(frame_cos1,RooFit.Name("model"),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(color))
	model.plotOn(frame_cos2,RooFit.Name("model"),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(color))
	model.plotOn(frame_phi,RooFit.Name("model"),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(color))
	model.plotOn(frame_t,RooFit.Name("model"),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(color))

def plot61Dcomponent(model, normdata, wide_window, compname, linecolor, linestyle):

	print '\nPlotting component '+compname+':\n'

	compdict = {'VV':10,'SS':11,'SV':12,'VS':13,'ST':14,'TS':15,'VT':16,'TV':17,'TT':18}
	compid = compdict[compname]

	component(compid,compid,compid,compid,compid,compid)
	if wide_window:
		model.plotOn(frame_m1,RooFit.Name("model_comp_"+compname),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(linecolor),RooFit.LineStyle(linestyle),RooFit.LineWidth(2))
		model.plotOn(frame_m2,RooFit.Name("model_comp_"+compname),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(linecolor),RooFit.LineStyle(linestyle),RooFit.LineWidth(2))
	else:
		model.plotOn(frame_m1_narrowwin,RooFit.Name("model_comp_"+compname),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(linecolor),RooFit.LineStyle(linestyle),RooFit.LineWidth(2))
		model.plotOn(frame_m2_narrowwin,RooFit.Name("model_comp_"+compname),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(linecolor),RooFit.LineStyle(linestyle),RooFit.LineWidth(2))
	model.plotOn(frame_cos1,RooFit.Name("model_comp_"+compname),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(linecolor),RooFit.LineStyle(linestyle),RooFit.LineWidth(2))
	model.plotOn(frame_cos2,RooFit.Name("model_comp_"+compname),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(linecolor),RooFit.LineStyle(linestyle),RooFit.LineWidth(2))
	model.plotOn(frame_phi,RooFit.Name("model_comp_"+compname),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(linecolor),RooFit.LineStyle(linestyle),RooFit.LineWidth(2))
	model.plotOn(frame_t,RooFit.Name("model_comp_"+compname),RooFit.ProjWData(RooArgSet(yeartrigcat),normdata),RooFit.DrawOption("c"),RooFit.LineColor(linecolor),RooFit.LineStyle(linestyle),RooFit.LineWidth(2))
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
	c1 = TCanvas("c1","c1",1000,800)
	c1.Divide(2,3)
	c1.cd(1)
	if wide_window: frame_m1.Draw()
	else: frame_m1_narrowwin.Draw()
	c1.cd(1).SetLogy(1)
	c1.cd(2)
	if wide_window: frame_m2.Draw()
	else: frame_m2_narrowwin.Draw()
	c1.cd(2).SetLogy(1)
	c1.cd(3)
	frame_cos1.Draw()
	c1.cd(4)
	frame_cos2.Draw()
	c1.cd(5)
	frame_phi.Draw()
	c1.cd(6)
	frame_t.Draw()
	leg61D.Draw()
	#for i in [c1.cd(1),c1.cd(2),c1.cd(3),c1.cd(4),c1.cd(5),c1.cd(6)]:
	#	i.GetXaxis().SetTitleSize(0.2)
	#	i.GetYaxis().SetTitleSize(0.2)

	return c1

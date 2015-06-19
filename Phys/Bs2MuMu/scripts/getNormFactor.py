#This code will calculate the normalization factors with the errors
#given the values and errors of all the components

from valAndErr import *

# NormFactor = 	BR_cal * 
#		* Gen_effRat * MuID_effRat * Rec|Gen_effRat * Sel|Rec_effRat * TRIG|Sel_effRat 
#		* fs/fd * 1/N_cal  

def getNormFactor():

	#The Branching Ratios of the calibration channels
	#br_Bd = valAndErr(0.0000194, 0.0000006) 
	#br_Bs = valAndErr(0.000034, 0.000009) 

	#The fd/fs = fu/fs
	fdfs = valAndErr(3.745,0.295)
	
	#-----------------------------------------------------#
	#Control channel: Bu -> JpsiKplus
	#The generation efficiencies including acceptance 
	#The Reconstruction and Selection and MuID from MC
	#The fitted yields for the control channel		

	br_Bu = valAndErr(0.0000601, 0.0000021) 
	gen_eff_Bu = valAndErr(0.153,0.)
	recSel_eff_Bu = valAndErr(0.15652, 0.00051)
	N_Bu = valAndErr(255396.2, 516.39)	

	#-----------------------------------------------------#
	#The signal	
	gen_eff_sig = valAndErr(0.175,0.)
	recSel_eff_sig = valAndErr(0.31217, 0.00065)	
	
	#-----------------------------------------------------#
	#Get the ratios
	gen_eff_rat  = gen_eff_Bu.over(gen_eff_sig)	
	print 'Rec and Sel eff:'	
	recSel_eff_rat = recSel_eff_Bu.over(recSel_eff_sig)	
	trig_eff_rat = valAndErr(0.934,0.008)
	yieldInverted = valAndErr(1.,0.).over(N_Bu)
	#-----------------------------------------------------#
	#Putting it all together

	normFac = br_Bu.times(gen_eff_rat).times(recSel_eff_rat).times(trig_eff_rat).times(fdfs).times(yieldInverted)

	print '------------------------------------------------------------------------'
	print 'Control channel: Bplus2JpsiKplus'	
	print 'The normalization factor : ', normFac.getVal(), ' +- ', normFac.getErr()
	print '------------------------------------------------------------------------'



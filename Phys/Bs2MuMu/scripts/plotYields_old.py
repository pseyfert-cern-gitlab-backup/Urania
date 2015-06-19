from ROOT import *
from array import *
from valAndErr import *

#For the screen turn off the whistles 
from ROOT import gROOT
gROOT.SetBatch(True)

def plotYields(v=1,data=1):
	#The 'data' to be used - 'd' (data has to be declared below)	
	#The variable to be plotted - 'v' (variable v only picks the title for the axis and the range)
	

	dir = 'YieldPlots/'
	
	plotYieldsPerStripping=True
	useEffPerStrip=False
	
	
	if v==0: 
		var = 'raw_sig_yield'
		y_title = 'Raw signal yield / pb-1'
		if data==1: y_range = [320, 460]
		if data==3: y_range = [20, 35]
	if v==1: 
		var = 'sig_yield'
		y_title = 'Trig.Eff.corr.sig.yield / pb-1'
		if data==1: y_range = [320, 550]
		if data==3: y_range = [0, 65]
	
	if v==2: 
		var = 'sig_yield'
		if data==1: 
			#Correct the raw yields with a common efficiency per Stripping	(OK!)
			useEffPerStrip=True
			y_range = [320, 550]
			y_title = 'TrigEff per Strip. cor. sig. yield / pb-1'
		if data==3: 
			#Correct the raw yields with a common efficiency per FILE (wrong)
			y_range = [0, 65]
			y_title = 'TrigEff per File. cor. sig. yield / pb-1'
		if data==8: 
			# The yields/pb for Bd to Kpi	
			y_title = 'TrigEff per File. cor. sig. yield / pb-1'
			y_range = [200, 450]

	if v==3: 
		var = 'bkg_yield'
		y_title = 'Trig.Eff. corr. bkg. yield / pb-1'
		if data==1: y_range = [35, 70]
		if data==3: y_range = [ 0, 17]

	if v==4: 
		var = 'raw_fsOverfd'
		y_title = 'N(Bs)/N(Bd)'
		if data==4: y_range = [0.058, 0.070]

	if v==5: 
		useEffPerStrip=True
		var = 'sig_yield'
		y_title = 'DiMuonTrig & TrigeEff of B+JpsiK+ S_yield/pb-1'
		
		if data == 2: y_range = [250, 400]
		if data == 5: y_range = [0, 50]

	if v==6: 
		var = 'sig_yield'
		#Correct the raw yields with a common efficiency per Stripping	
		if data==1: 
			useEffPerStrip=True
			plotYieldsPerStripping=True
			y_range = [320, 550]
			y_title = 'TrigEff per Strip. cor. sig. yield / pb-1'


	#Trigger efficiencies per Stripping from BplusJpsiKplus fidCut sample
	trig_eff_19 = valAndErr(0.911093499007 ,0.0511791394994)
	trig_eff_19a = valAndErr(0.910791428399  ,  0.0255496518844)
	trig_eff_19b = valAndErr(0.91341733899  ,  0.0311600726266)
	trig_eff_19c = valAndErr(0.914396082856  ,  0.0316261362057)
	#REPROCSSED DATA:
	trig_eff_20r1 = valAndErr( 0.923740500919  ,  0.0749463399639)
	trig_eff_20 = valAndErr(0.916055312275  ,  0.0121825109762)
	#Filling in the data
	files = []
	benchmarks = []

	#BplusJpsiKplus Fiducial Cuts
	if data==1:
		#Benchmarks are the lines over the whole plot range	
		channel = 'Bplus 2 JpsiKplus'	
		plotName = var+'_Bplus2JpsiKplus_yieldPerPb_'+'fiducialCuts_'		
		#b = {'name':'2012_822pb-1', 'raw_sig_yield': [386.67, 2.07] , 'sig_yield': [423.62,8.87]  , 'bkg_yield': [55.00, 1.22] }	
		b = {'name':'2012_1109pb-1', 'raw_sig_yield': [382.527059495  ,  2.01406919387] , 'sig_yield': [419.11415914  ,  8.32672296677]  , 'bkg_yield': [54.7370497429  ,  1.14112216864] }	
		benchmarks.append(b)	
		b = {'name':'2012_Strip19', 'raw_sig_yield': [418.490930085  ,  3.19207802305] , 'sig_yield': [459.328192486  ,  26.0387685279]  , 'bkg_yield': [54.3022080699  ,  3.25220556923] }	
		#benchmarks.append(b)	
		b = {'name':'2012_Strip19a', 'raw_sig_yield': [395.067991867  ,  2.22296888911] , 'sig_yield': [433.763405703  ,  12.4103617693]  , 'bkg_yield': [56.2502964256  ,  1.70484486866] }	
		#benchmarks.append(b)	
		b = {'name':'2012_Strip19b', 'raw_sig_yield': [365.623363818  ,  2.14496317886] , 'sig_yield': [400.280735006  ,  13.8555168047]  , 'bkg_yield': [53.3731994703  ,  1.91637690053] }	
		#benchmarks.append(b)
		#b = {'name':'2012_Strip19c_abcd', 'raw_sig_yield': [375.494841064  ,  2.46767225822] , 'sig_yield': [415.932940157  ,  18.3731207338]  , 'bkg_yield': [56.5612787175  ,  2.65881267433] }	
		b = {'name':'2012_Strip19c', 'raw_sig_yield': [371.305826331  ,  2.23442483283] , 'sig_yield': [406.066728952  ,  14.255589599]  , 'bkg_yield': [53.9990405188  ,  2.0148121725] }	
		#benchmarks.append(b)	
		b = {'name':'2011_1020pb-1', 'raw_sig_yield': [333.33, 1.77] , 'sig_yield': [358.74,7.40]  , 'bkg_yield': [36.87,0.80] }	
		benchmarks.append(b)	
		#REPRODUCTION Rec14
		b = {'name':'2012_R14_S20_2019pb-1', 'raw_sig_yield': [375.491563758  , 1.92847583509], 'sig_yield': [409.900536274  ,  5.84359769861]  , 'bkg_yield': [54.0694359569  , 0.795427516551]}
		benchmarks.append(b)	
	

		# 'Files' mean the bins along x axis
		f = {'name':'Strip19_a', 'lumi':38.2, 'raw_sig_yield': [418.41,3.97], 'sig_yield': [469.29,38.]  , 'bkg_yield': [57.81,4.92]}
		files.append(f)	
		f = {'name':'Strip19_b', 'lumi':36.8, 'raw_sig_yield': [419.29,4.03], 'sig_yield': [447.78,35.07]  , 'bkg_yield': [49.78,4.15]} 
		files.append(f)	
		f = {'name':'Strip19a_a', 'lumi':100., 'raw_sig_yield': [393.16, 2.92], 'sig_yield': [427.37,24.5]  , 'bkg_yield': [55.61,3.39]}
		files.append(f)
		f = {'name':'Strip19a_b', 'lumi':69.0, 'raw_sig_yield': [396.92,3.99 ], 'sig_yield': [445.45,  46.231 ]  , 'bkg_yield': [54.5923633454  ,  6.387 ]}
		files.append(f)
		f = {'name':'Strip19a_c', 'lumi':67.5, 'raw_sig_yield': [398.67,3.18], 'sig_yield': [437.98,  32.7819 ]  , 'bkg_yield': [56.6057073969  ,  4.381 ]}
		files.append(f)
		f = {'name':'Strip19a_d', 'lumi':68.0, 'raw_sig_yield': [393.33,3.28], 'sig_yield': [ 425.56,30.674 ]  , 'bkg_yield': [53.5083110993,4.115808]}
		files.append(f)
		f = {'name':'Strip19a_e', 'lumi':72.0, 'raw_sig_yield': [394.18,3.15], 'sig_yield': [414.37,  28.337 ]  , 'bkg_yield': [55.0175207898  ,  3.9456 ]}
		files.append(f)
		f = {'name':'Strip19a_f', 'lumi':67.5, 'raw_sig_yield': [398.57,3.26], 'sig_yield': [439.57,  33.0115 ]  , 'bkg_yield': [ 56.0498429555  ,  4.4258 ]}
		files.append(f)
		f = {'name':'Strip19b_a', 'lumi':69.7, 'raw_sig_yield': [366.26,3.09], 'sig_yield': [ 400.28,  28.354 ]  , 'bkg_yield': [53.9153926824  ,  4.05541]}
		files.append(f)
		f = {'name':'Strip19b_b', 'lumi':63.4, 'raw_sig_yield': [369.38,3.17], 'sig_yield': [412.79,  29.4971 ]  , 'bkg_yield': [55.2246655172  ,  4.1869 ]}
		files.append(f)
		f = {'name':'Strip19b_c', 'lumi':74.0, 'raw_sig_yield': [359.60,3.05], 'sig_yield': [395.24,  27.635 ]  , 'bkg_yield': [53.7057347362  ,  3.9718 ]}
		files.append(f)
		f = {'name':'Strip19b_d', 'lumi':65.0, 'raw_sig_yield': [366.84, 3.18], 'sig_yield': [365.35,26.9025 ]  , 'bkg_yield': [46.7562788635  ,  3.6829 ]}
		files.append(f)
		f = {'name':'Strip19b_e', 'lumi':31.6, 'raw_sig_yield': [368.37, 4.12 ], 'sig_yield': [387.38,39.989 ]  , 'bkg_yield': [ 52.0303429189  ,  5.6969 ]}
		files.append(f)
		f = {'name':'Strip19c_a', 'lumi':40., 'raw_sig_yield': [369.697992993  ,  3.79074079125 ], 'sig_yield': [403.039823327  ,  38.2046160129 ]  , 'bkg_yield': [55.1141197897  ,  5.53209313177]}
		files.append(f)
		f = {'name':'Strip19c_b', 'lumi':36., 'raw_sig_yield': [380.285593493  ,  3.8320682348 ], 'sig_yield': [409.328755268  ,  38.9300440761 ]  , 'bkg_yield': [52.7391183984  ,  5.23381357592 ]}
		files.append(f)
		f = {'name':'Strip19c_c', 'lumi':58.5, 'raw_sig_yield': [377.392809708  ,  3.33986413833 ], 'sig_yield': [432.302730115  ,  33.5074257888 ]  , 'bkg_yield': [57.4466424808  ,  4.75242892581 ]}
		files.append(f)
		f = {'name':'Strip19c_d', 'lumi':42., 'raw_sig_yield': [375.456730418  ,  3.70146095719 ], 'sig_yield': [402.201928997  ,  33.9045498499 ]  , 'bkg_yield': [57.2139366244  ,  5.08444270131 ]}
		files.append(f)
		f = {'name':'Strip19c_e', 'lumi':65., 'raw_sig_yield': [ 363.859569208  ,  3.03157817769], 'sig_yield': [406.828593677  ,  30.4704592273]  , 'bkg_yield': [ 53.2948208451  ,  4.15416922538]}
		files.append(f)
		f = {'name':'Strip19c_f', 'lumi':45., 'raw_sig_yield': [365.90952652  ,  3.43995196995], 'sig_yield': [392.892388524  ,  32.9583146843]  , 'bkg_yield': [48.2787916999  ,  4.24294836755]}
		files.append(f)

		
		#Modified trigger efficiency correction (use the same eff for files in the same stripping)

		trig_eff= [	trig_eff_19, trig_eff_19, 
				trig_eff_19a, trig_eff_19a, trig_eff_19a, trig_eff_19a, trig_eff_19a, trig_eff_19a, 
				trig_eff_19b, trig_eff_19b, trig_eff_19b, trig_eff_19b, trig_eff_19b, 
				trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c,
				trig_eff_20r1, trig_eff_20] #REPROCESSED DATA

		if plotYieldsPerStripping:
			files = []	
			f = {'name':'Strip19', 'lumi':75.0 , 'raw_sig_yield': [418.490930085  ,  3.19207802305] }
			files.append(f)
			f = {'name':'Strip19a', 'lumi':444.0, 'raw_sig_yield': [395.067991867  ,  2.22296888911] }
			files.append(f)
			f = {'name':'Strip19b', 'lumi':303.7, 'raw_sig_yield': [365.623363818  ,  2.14496317886] }
			files.append(f)
			f = {'name':'Strip19c', 'lumi':176.5, 'raw_sig_yield': [371.305826331  ,  2.23442483283] }
			files.append(f)
			# REPROCESSED DATA:	
			f = {'name':'2011_R14_Strip20r1', 'lumi':71., 'raw_sig_yield': [354.925864945  ,  2.99719817127 ], 'sig_yield': [384.226808927  ,  31.3420821868 ]  , 'bkg_yield': [46.8297495423  ,  4.02581365499]}
			files.append(f)
			
			trig_eff= [	trig_eff_19, 
					trig_eff_19a, 
					trig_eff_19b,
					trig_eff_19c,
					trig_eff_20r1]

		if useEffPerStrip:
			for i,f in enumerate(files):
				rawY = valAndErr(f.get('raw_sig_yield')[0] , f.get('raw_sig_yield')[1])	
				corY = rawY.over(trig_eff[i])	
				f['sig_yield'] = [corY.getVal(),corY.getErr()] 
				print f.get('name'), ' corrected with :', trig_eff[i].getVal(), ' +- ', trig_eff[i].getErr()


	#BplusJpsiKplus , JpsiDiMuon triggers, efficiencies per Stripping and got from a fit to the fiducial cut sample
	if data==2:
		channel = 'Bplus2JpsiKplus, JPsi di-muon trigger'	
		plotName = var+'_Bplus2JpsiKplus_yieldPerPb_JpsiDiMuonTrig_'+'fiducialCuts_'		
		
		#Correct fo the trig eff from Bplus channel
		raw12 = valAndErr(306.857882491  ,  1.63678983714)
		raw11 = valAndErr(261.767803083  ,  1.41264504938)
		
		trig12 = valAndErr(0.91270373752  ,  0.0174847202545)
		trig11 = valAndErr(0.929176315886  ,  0.0185330006439)
		
		sig_y12 = raw12.over(trig12)
		sig_y11 = raw11.over(trig11)

		rat = sig_y12.over(sig_y11)
		print ' ------------------------------------------------'	
		print ' ------------------------------------------------'	
		print 'THE RATIO BETWEEN 12/11 IS :',rat.getVal(), '+-',rat.getErr()
		print ' ------------------------------------------------'	
		print ' ------------------------------------------------'	


		b = {'name':'2012_1109pb-1', 'raw_sig_yield': [] , 'sig_yield': [sig_y12.getVal(),sig_y12.getErr()]  , 'bkg_yield': [] }	
		benchmarks.append(b)	
		b = {'name':'2011_1020pb-1', 'raw_sig_yield': [] , 'sig_yield': [sig_y11.getVal(),sig_y11.getErr()]  , 'bkg_yield': [] }	
		benchmarks.append(b)	
		
		f = {'name':'Strip19_a', 'lumi':38.2, 'raw_sig_yield': [340.010259729  ,  3.48646748028], 'sig_yield':  []  , 'bkg_yield': []}
		files.append(f)	
		f = {'name':'Strip19_b', 'lumi':36.8, 'raw_sig_yield': [335.714800217  ,  3.50755900131], 'sig_yield':  []  , 'bkg_yield': []} 
		files.append(f)	
		f = {'name':'Strip19a_a', 'lumi':100., 'raw_sig_yield': [313.023438164  ,  2.47512675243], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19a_b', 'lumi':69.0, 'raw_sig_yield': [315.582484136  ,  2.69201381121], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19a_c', 'lumi':67.5, 'raw_sig_yield': [316.695405293  ,  2.82836853108], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19a_d', 'lumi':68.0, 'raw_sig_yield': [311.153478856  ,  2.68067455925], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19a_e', 'lumi':72.0, 'raw_sig_yield': [314.438499087  ,  2.80606975687], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19a_f', 'lumi':67.5, 'raw_sig_yield': [316.566857568  ,  2.71868271893], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19b_a', 'lumi':69.7, 'raw_sig_yield': [295.2976866  ,  2.56888374567], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19b_b', 'lumi':63.4, 'raw_sig_yield': [297.133330568  ,  2.66434818082], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19b_c', 'lumi':74.0, 'raw_sig_yield': [289.448041268  ,  2.48629725928], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19b_d', 'lumi':65.0, 'raw_sig_yield': [296.610031318  ,  2.63934065739], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19b_e', 'lumi':31.6, 'raw_sig_yield': [291.63972098  ,  3.67220944536], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19c_a', 'lumi':40.0, 'raw_sig_yield': [297.576459235  ,  3.16245669396], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19c_b', 'lumi':36.0, 'raw_sig_yield': [307.6413058  ,  3.5874905046], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19c_c', 'lumi':58.5, 'raw_sig_yield': [302.838261802  ,  2.77587882276], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19c_d', 'lumi':42.0, 'raw_sig_yield': [304.977474329  ,  3.14694008441], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19c_e', 'lumi':65.0, 'raw_sig_yield': [297.199855419  ,  2.64625258441], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		f = {'name':'Strip19c_f', 'lumi':45.0, 'raw_sig_yield': [297.220733198  ,  3.01458185815], 'sig_yield': []  , 'bkg_yield': []}
		files.append(f)
		
	
		#Modified trigger efficiency correction (use the same eff for files in the same stripping)
		trig_eff= [	trig_eff_19, trig_eff_19, 
				trig_eff_19a, trig_eff_19a, trig_eff_19a, trig_eff_19a, trig_eff_19a, trig_eff_19a, 
				trig_eff_19b, trig_eff_19b, trig_eff_19b, trig_eff_19b, trig_eff_19b, 
				trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c]

		for i,f in enumerate(files):
			rawY = valAndErr(f.get('raw_sig_yield')[0] , f.get('raw_sig_yield')[1])	
			corY = rawY.over(trig_eff[i])	
			f['sig_yield'] = [corY.getVal(),corY.getErr()] 
			print f.get('name'), ' corrected with :', trig_eff[i].getVal(), ' +- ', trig_eff[i].getErr()



	#BsJpsiPhi Fiducial 
	if data==3:
		channel = 'Bs 2 JpsiPhi'	
		plotName = var+'_Bs2JpsiPhi_yieldPerPb_'+'fiducialCuts_'		
		
		#b = {'name':'2012_822pb-1', 'raw_sig_yield': [24.9345  ,  0.219] , 'sig_yield': [27.1023642966  ,  2.1619905582]  , 'bkg_yield': [6.35235478387  ,  0.516178784543] }	
		b = {'name':'2012_1109pb-1', 'raw_sig_yield': [24.5611147609  ,  0.19708725314] , 'sig_yield': [27.6153071737  ,  1.94664418327]  , 'bkg_yield': [6.58746803264  ,  0.472513717408] }	
		benchmarks.append(b)	
		#b = {'name':'2012_748pb-1', 'raw_sig_yield': [25.1172343645  ,  0.227529147685] , 'sig_yield': [26.4186591243  ,  2.17206584585]  , 'bkg_yield': [6.1542241271  ,  0.515766496164] }	
		#benchmarks.append(b)	
		b = {'name':'2012_Strip19', 'raw_sig_yield': [28.5727200182  ,  0.65179125397] , 'sig_yield': [29.3141557723  ,  6.14645399716]  , 'bkg_yield': [4.24073073282  ,  0.937947442795] }	
		#benchmarks.append(b)	
		b = {'name':'2012_Strip19a', 'raw_sig_yield': [25.5235125782  ,  0.279218643432] , 'sig_yield': [29.1000709949  ,  3.09390024637]  , 'bkg_yield': [6.92704726393  ,  0.750179460898] }	
		#benchmarks.append(b)	
		b = {'name':'2012_Strip19b', 'raw_sig_yield': [23.5885684585  ,  0.311443651276] , 'sig_yield': [30.9847714654  ,  4.02877176219]  , 'bkg_yield': [7.14991833321  ,  0.94857801457] }	
		#benchmarks.append(b)	
		#b = {'name':'2012_Strip19c_abcd', 'raw_sig_yield': [23.8923872692  ,  0.39965738786] , 'sig_yield': [23.2663521545  ,  3.9491256027]  , 'bkg_yield': [5.76656261402  ,  0.996893501098] }	
		#b = {'name':'2012_Strip19c_abd', 'raw_sig_yield': [] , 'sig_yield': []  , 'bkg_yield': [] }	
		b = {'name':'2012_Strip19c', 'raw_sig_yield': [23.7053862275  ,  0.321025486339] , 'sig_yield': [27.9518794318  ,  4.05260188544]  , 'bkg_yield': [6.76784950825  ,  0.997440473644] }	
		#benchmarks.append(b)	
		b = {'name':'2011_1020pb-1', 'raw_sig_yield': [20.6251327321  ,  0.178644260296] , 'sig_yield': [21.3592985302  ,  1.60095911148]  , 'bkg_yield': [3.57384812058  ,  0.276189222415] }	
		benchmarks.append(b)	


		f = {'name':'Strip19_a', 'lumi':38.2, 'raw_sig_yield': [30.3501199634  ,  0.917856694107], 'sig_yield':  [32.4140764822  ,  11.3170418917]  , 'bkg_yield': [2.19828416497  ,  0.842850544025]}
		files.append(f)	
		f = {'name':'Strip19_b', 'lumi':36.8, 'raw_sig_yield': [27.7383903641  ,  0.907321355428], 'sig_yield':  [30.6454723681  ,  9.10417853377]  , 'bkg_yield': [5.83281156206  ,  1.79750546943]} 
		files.append(f)	
		f = {'name':'Strip19a_a', 'lumi':100., 'raw_sig_yield': [25.4349543242  ,  0.537186921917], 'sig_yield': [28.6513007332  ,  6.33519021739]  , 'bkg_yield': [6.78702827561  ,  1.52943725777]}
		files.append(f)
		f = {'name':'Strip19a_b', 'lumi':69.0, 'raw_sig_yield': [24.9935031042  ,  0.633783630541], 'sig_yield': [27.533834009  ,  6.79293575688]  , 'bkg_yield': [6.36388438913  ,  1.60600220708]}
		files.append(f)
		f = {'name':'Strip19a_c', 'lumi':67.5, 'raw_sig_yield': [25.8327748617  ,  0.654361494105], 'sig_yield': [28.4457882574  ,  9.27479183022]  , 'bkg_yield': [6.36803726052  ,  2.10663535179]}
		files.append(f)
		f = {'name':'Strip19a_d', 'lumi':68.0, 'raw_sig_yield': [25.9556499851  ,  0.651961478738], 'sig_yield': [29.998296056  ,  7.5455239424]  , 'bkg_yield': [6.56146118216  ,  1.69034755683]}
		files.append(f)
		f = {'name':'Strip19a_e', 'lumi':72.0, 'raw_sig_yield': [26.6393010014  ,  0.644427600131], 'sig_yield': [36.6884253672  ,  9.15055038989]  , 'bkg_yield': [8.22709363205  ,  2.0978813761]}
		files.append(f)
		f = {'name':'Strip19a_f', 'lumi':67.5, 'raw_sig_yield': [24.9580069295  ,  0.639691993936], 'sig_yield': [31.0230685235  ,  30.2582642258]  , 'bkg_yield': [8.16417921385  ,  7.97257079477]}
		files.append(f)
		f = {'name':'Strip19b_a', 'lumi':69.7, 'raw_sig_yield': [24.2018104916  ,  0.620230956432], 'sig_yield': [30.1919540661  ,  7.95820430347]  , 'bkg_yield': [6.55453858274  ,  1.76706634898]}
		files.append(f)
		f = {'name':'Strip19b_b', 'lumi':63.4, 'raw_sig_yield': [24.9566777611  ,  1.65202311064], 'sig_yield': [27.6918720559  ,  8.73684791655]  , 'bkg_yield': [5.21129539176  ,  2.39902112017]}
		files.append(f)
		f = {'name':'Strip19b_c', 'lumi':74.0, 'raw_sig_yield': [23.2363969271  ,  0.591378741773], 'sig_yield': [0.,0.]  , 'bkg_yield': [0.,0.]} #The trigger eff goes crazy
		files.append(f)
		f = {'name':'Strip19b_d', 'lumi':65.0, 'raw_sig_yield': [24.0598624548  ,  0.641320888727], 'sig_yield': [25.2866619148  ,  6.24619957142]  , 'bkg_yield': [5.06376004961  ,  1.29266294084]}
		files.append(f)
		f = {'name':'Strip19b_e', 'lumi':31.6, 'raw_sig_yield': [23.1549026183  ,  0.884885643684], 'sig_yield': [22.150305538  ,  9.22619956772]  , 'bkg_yield': [4.216880651  ,  1.79804310824]}
		files.append(f)
		f = {'name':'Strip19c_a', 'lumi':40., 'raw_sig_yield': [23.987651527  ,  0.806918477744], 'sig_yield': [29.1493627452  ,  10.6319956272]  , 'bkg_yield': [6.79411674364  ,  2.52326629102]}
		files.append(f)
		f = {'name':'Strip19c_b', 'lumi':36., 'raw_sig_yield': [27.3912134728  ,  0.907629034064], 'sig_yield': [ 36.5444880712  ,  13.4259979724]  , 'bkg_yield': [3.88815014757  ,  1.53012172832]}
		files.append(f)
		f = {'name':'Strip19c_c', 'lumi':58.5, 'raw_sig_yield': [23.7061605118  ,  0.673048369702], 'sig_yield': [7.3813106481  ,  4.19783243757]  , 'bkg_yield': [2.02893890647  ,  1.15899419968]}
		files.append(f)
		f = {'name':'Strip19c_d', 'lumi':42., 'raw_sig_yield': [24.0592151053  ,  0.794341876537], 'sig_yield': [27.7883865551  ,  10.8237205202]  , 'bkg_yield': [5.76237454729  ,  2.29029761895]}
		files.append(f)
		f = {'name':'Strip19c_e', 'lumi':65., 'raw_sig_yield': [23.030513848  ,  0.588197560184], 'sig_yield': [25.6045816783  ,  7.02522761394]  , 'bkg_yield': [5.33766867099  ,  1.55262166931]}
		files.append(f)
		f = {'name':'Strip19c_f', 'lumi':45., 'raw_sig_yield': [28.2002897114  ,  0.819152356652], 'sig_yield': [0.,0.]  , 'bkg_yield': [0.,0]}
		files.append(f)



	#FsOverFd
	if data==4:
		channel = 'N(Bs2JpsiPhi) / N(Bplus2JpsiKplus)'	
		plotName = var+'_fsOverFd'+'PIDK_GhostProb_'		
		
		#-------------------------------------#
	
		#PIDK>0
		#Bu/Bs	
		effPIDK_11 = valAndErr(0.987,0.02) 
		effPIDK_12 = valAndErr(0.983,0.006)

		#GhostProb cut eff ratio for 2012
		#Bu/Bs	
		effGP_12_Bs = valAndErr(0.979870331104, 0.000970518032238)	
		effGP_12_Bu = valAndErr(0.993628689109,0.000139672256966)	
		effGP_12 = effGP_12_Bu.over(effGP_12_Bs)	# 1.01404099866 , 0.00101442705623 
		
		#Tracking eff difference, from Bs2JpsiPhi -> mumuK/mumu ~ mumuKK/mumuK
		#Tracking efficiency correction in MC10 with 2010 mapping	
		#This has to be DIVIDED! 
		#trkEffC_BuBs_11 = valAndErr(1.00139 , 0.01834)
		#Tracking efficiency correction in MC12 with 2012 mapping (Reco13 Strippin19)	
		#trkEffC_BuBs_12_19 = valAndErr(0.99177 , 0.00698)
		#Tracking efficiency correction in MC12 with 2012 mapping (Reco13a Strippin19a)	
		#trkEffC_BuBs_12_19a = valAndErr(0.99477 , 0.00503)
		
		
		#Tracking eff difference, mumuKK/mumuK
		#This has to be multiplied!	
		
		#Tracking efficiency correction in MC10 with 2011 mapping	
		#trkEffC_BuBs_11 = valAndErr(0.97748 , 0.00576)
		trkEffC_BuBs_11 = valAndErr(0.97748 , 0.015) # From Francesco, 1.Oct
		#Tracking efficiency correction in MC12 with 2012 mapping (Reco13 Strippin19)	
		trkEffC_BuBs_12_19 = valAndErr(1.00833 , 0.01942)
		#Tracking efficiency correction in MC12 with 2012 mapping (Reco13a Strippin19a)	
		trkEffC_BuBs_12_19a = valAndErr(1.00008 , 0.01303)
		
		#-------------------------------------trkEffC_BuBs_12_19 = valAndErr(0.99177 , 0.00698)
		
		# Total corrections:	
		#-----------------------------------------------------------------#
		#eff_11 = effPIDK_11.over(trkEffC_BuBs_11)
		#eff_12_19 = effPIDK_12.times(effGP_12).over(trkEffC_BuBs_12_19)
		#eff_12 = effPIDK_12.times(effGP_12).over(trkEffC_BuBs_12_19a)
		#-----------------------------------------------------------------#
		eff_11 = effPIDK_11.times(trkEffC_BuBs_11)
		eff_12_19 = effPIDK_12.times(effGP_12).times(trkEffC_BuBs_12_19)
		eff_12 = effPIDK_12.times(effGP_12).times(trkEffC_BuBs_12_19a)
		#-----------------------------------------------------------------#

		#b = {'name':'2012_822pb-1', 'raw_fsOverfd': [0.0639846020125 , 0.000538689276674]} 
		#y = valAndErr(0.0639846020125 , 0.000538689276674).times(eff_11)	
		y = valAndErr(0.063637035442 , 0.000465625794291).times(eff_12)	
		y_12 = y	
		b = {'name':'2012_1109pb-1', 'raw_fsOverfd': [y.getVal(),y.getErr()]} 
		benchmarks.append(b)	
	
		y = valAndErr(0.0627002324098 , 0.000519549642609).times(eff_11)	
		y_11 = y	
		b = {'name':'2011_1020pb-1', 'raw_fsOverfd': [y.getVal(),y.getErr()] }
		benchmarks.append(b)	
	
		y = valAndErr(0.0638044441022 , 0.00187110302608).times(eff_12_19)	
		f = {'name':'Strip19', 'lumi':74., 'raw_fsOverfd': [y.getVal(),y.getErr()]}
		files.append(f)
		y = valAndErr(0.0639048202394 , 0.000800545091606).times(eff_12)	
		f = {'name':'Strip19_a', 'lumi':444., 'raw_fsOverfd': [y.getVal(),y.getErr()]}
		files.append(f)	
		y = valAndErr(0.064093145524 , 0.00100392384249).times(eff_12)	
		f = {'name':'Strip19_b', 'lumi':303.7, 'raw_fsOverfd': [y.getVal(),y.getErr()]} 
		files.append(f)	
		y = valAndErr(0.0630092752542 , 0.000919631176971).times(eff_12)	
		f = {'name':'Strip19_c', 'lumi':286.5, 'raw_fsOverfd': [y.getVal(),y.getErr()]} 
		files.append(f)	
	

		#Calculate the ratio between the years
		ratio = y_12.over(y_11)
		
		print '  ---------------------------------'
		print '   The ratio between 2012/2011 is: '	
		print '  ---------------------------------'
		print '   ', ratio.getVal(), ' +- ', ratio.getErr()	
		print '   Eff cor for 2011: ', eff_11.getVal(), ' +- ', eff_11.getErr()		
		print '   Eff cor for 2012: ', eff_12.getVal(), ' +- ', eff_12.getErr()		
		print '   Corr. fsfd for 2012: ', y_12.getVal(), ' +- ', y_12.getErr()		
		print '   Corr. fsfd for 2011: ', y_11.getVal(), ' +- ', y_11.getErr()		
				
		print '  ---------------------------------'


	#BsJpsiPhi Jpsi DiMuon Triggered events, corrected with trig eff from Bplus
	if data==5:
		channel = 'Bs 2 JpsiPhi'	
		plotName = var+'_Bs2JpsiPhi_yieldPerPb_JpsiTrig_BplusPerStripEff_'+'fiducialCuts_'		
	
		#Correct fo the trig eff from Bplus channel
		raw12 = valAndErr(19.933632752  ,  0.184465068589)
		raw11 = valAndErr(16.3828191734  ,  0.15365334248)
		
		trig12 = valAndErr(0.91270373752  ,  0.0174847202545)
		trig11 = valAndErr(0.929176315886  ,  0.0185330006439)
		
		sig_y12 = raw12.over(trig12)
		sig_y11 = raw11.over(trig11)

		b = {'name':'2012_1109pb-1', 'sig_yield': [sig_y12.getVal(),sig_y12.getErr()] } 
		benchmarks.append(b)	
		b = {'name':'2011_1020pb-1', 'sig_yield': [sig_y11.getVal(),sig_y11.getErr()] } 
		benchmarks.append(b)	

		
		f = {'name':'Strip19_a', 'lumi':38.2, 'raw_sig_yield': 	[24.6007161337  ,  0.820693798334]}
		files.append(f)	
		f = {'name':'Strip19_b', 'lumi':36.8, 'raw_sig_yield': 	[23.0992271009  ,  1.10082931691]} 
		files.append(f)	
		f = {'name':'Strip19a_a', 'lumi':100., 'raw_sig_yield': [20.4969304681  ,  0.472978876243]}
		files.append(f)
		f = {'name':'Strip19a_b', 'lumi':69.0, 'raw_sig_yield': [19.8665467814  ,  0.561317666519]}
		files.append(f)
		f = {'name':'Strip19a_c', 'lumi':67.5, 'raw_sig_yield': [21.0094792105  ,  0.586811538921]}
		files.append(f)
		f = {'name':'Strip19a_d', 'lumi':68.0, 'raw_sig_yield': [21.1668023577  ,  0.583353819331]}
		files.append(f)
		f = {'name':'Strip19a_e', 'lumi':72.0, 'raw_sig_yield': [21.0608505142  ,  0.569410839783]}
		files.append(f)
		f = {'name':'Strip19a_f', 'lumi':67.5, 'raw_sig_yield': [20.1269809539  ,  0.571109148968]}
		files.append(f)
		f = {'name':'Strip19b_a', 'lumi':69.7, 'raw_sig_yield': [19.7313212406  ,  0.595742317036]}
		files.append(f)
		f = {'name':'Strip19b_b', 'lumi':63.4, 'raw_sig_yield': [19.4768952631  ,  0.992803989603]}
		files.append(f)
		f = {'name':'Strip19b_c', 'lumi':74.0, 'raw_sig_yield': [18.8874726139  ,  0.528252436971]}
		files.append(f)
		f = {'name':'Strip19b_d', 'lumi':65.0, 'raw_sig_yield': [19.8980986947  ,  0.579270605183]}
		files.append(f)
		f = {'name':'Strip19b_e', 'lumi':31.6, 'raw_sig_yield': [18.6799819551  ,  0.789867230551]}
		files.append(f)
		f = {'name':'Strip19c_a', 'lumi':40., 'raw_sig_yield': 	[19.9541473559  ,  0.732563646086]} 
		files.append(f)
		f = {'name':'Strip19c_b', 'lumi':36., 'raw_sig_yield': 	[22.8085204595  ,  1.67922131768]}
		files.append(f)
		f = {'name':'Strip19c_c', 'lumi':58.5, 'raw_sig_yield': [19.6026475677  ,  0.608806434038]}
		files.append(f)
		f = {'name':'Strip19c_d', 'lumi':42., 'raw_sig_yield': 	[19.8759471602  ,  0.718461363618]}
		files.append(f)
		f = {'name':'Strip19c_e', 'lumi':65., 'raw_sig_yield': 	[19.0167648992  ,  1.27769638594]} 
		files.append(f)
		f = {'name':'Strip19c_f', 'lumi':45., 'raw_sig_yield': 	[22.6332308695  ,  0.73050558899]}
		files.append(f)


		#Modified trigger efficiency correction (use the same eff for files in the same stripping)

		trig_eff= [	trig_eff_19, trig_eff_19, 
				trig_eff_19a, trig_eff_19a, trig_eff_19a, trig_eff_19a, trig_eff_19a, trig_eff_19a, 
				trig_eff_19b, trig_eff_19b, trig_eff_19b, trig_eff_19b, trig_eff_19b, 
				trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c, trig_eff_19c]


		if useEffPerStrip:
			for i,f in enumerate(files):
				rawY = valAndErr(f.get('raw_sig_yield')[0] , f.get('raw_sig_yield')[1])	
				corY = rawY.over(trig_eff[i])	
				f['sig_yield'] = [corY.getVal(),corY.getErr()] 
				print f.get('name'), ' corrected with :', trig_eff[i].getVal(), ' +- ', trig_eff[i].getErr()



	#Compare the different mass fits, the MLL fit, SBsubtraction and MCToy spread in fitted Nsig	
	if data==7:
		channel = 'Bplu 2 JpsiKplus'	
		plotName = 'Bu2JpsiKplus_MassFitModelSystematics'		
	
		
		n_fit = valAndErr(0.0)	
		n_toy = valAndErr(0,0)	
		n_sb = 	valAndErr(0.0)	
		
		#b = {'name':'2012_1109pb-1', 'sig_yield': [mean.getVal(),mean.getErr()] } 
		#benchmarks.append(b)	
		
		f = {'name':'MLL_fit_2012', 'lumi':1109, 		'raw_sig_yield': [n_fit.getval(),n_fit.getErr()]}
		files.append(f)	
		f = {'name':'MCToy_N_sig_Input:MLLresult', 'lumi':'', 	'raw_sig_yield': [n_toy.getval(),n_toy.getErr()]}
		files.append(f)	
		f = {'name':'SB_subtracted_N_sig_2012', 'lumi':1109, 	'raw_sig_yield': [n_sb.getval(),n_sb.getErr()]}
		files.append(f)	
		
	#----------------------------------------#
	#Compare the different mass fits, the MLL fit, SBsubtraction and MCToy spread in fitted Nsig	
	if data==8:
		channel = 'Bd to Kpi'	
		plotName = 'Bd2Kpi_TISyieldsPerPbAndStrip_TISeffCorrected_'		
		
		tis_eff_2012 = valAndErr(0.0155542881237  ,  0.000195081459193)	
		avYield = valAndErr(4.54 , 0.48).over(tis_eff_2012)

		b = {'name':'2012_1109pb-1', 'sig_yield': [avYield.getVal(),avYield.getErr()] } 
		benchmarks.append(b)	
		
		f = {'name':'Strip19', 'lumi':75, 'raw_sig_yield': [5.97,1.77]}
		files.append(f)	
		f = {'name':'Strip19a', 'lumi':444, 'raw_sig_yield': [4.37,0.49]}
		files.append(f)	
		f = {'name':'Strip19b', 'lumi':303, 'raw_sig_yield': [5.01,0.87]}
		files.append(f)	
		f = {'name':'Strip19c', 'lumi':287, 'raw_sig_yield': [4.04,0.56]}
		files.append(f)	
	
		tis_eff_19 = valAndErr(0.0202549295306  ,  0.000814068984233)	
		tis_eff_19a = valAndErr(0.0145456501759 , 0.000293536387885)	
		tis_eff_19b = valAndErr(0.0156124844965  ,  0.000382107435609)	
		tis_eff_19c = valAndErr(0.0158759843806  ,  0.000393726034143)	
		
		trig_eff= [ tis_eff_19, tis_eff_19a, tis_eff_19b, tis_eff_19c] 

		for i,f in enumerate(files):
			rawY = valAndErr(f.get('raw_sig_yield')[0] , f.get('raw_sig_yield')[1])	
			corY = rawY.over(trig_eff[i])	
			f['sig_yield'] = [corY.getVal(),corY.getErr()] 
			print f.get('name'), ' corrected with :', trig_eff[i].getVal(), ' +- ', trig_eff[i].getErr()
	#----------------------------------------#
	
	
	#----------------------------------------#
	# END OF DECLARATION, filling in the info on the plots	
	#----------------------------------------#
	
	#Loop over the files and fill the info
	#n = len(files)
	labels = [];x = []; y = []; ex = []; ey = []
	bins = [0.]	
	for i,f in enumerate(files):
		labels.append(f.get('name','noname')+'_'+str(f.get('lumi',0))+'pb')	
		bins.append(bins[i]+f.get('lumi',0.)) 
		#Calculate x
		x_val = bins[i] + (bins[i+1]-bins[i])/2
		x.append(x_val)
		print 'x=',x[i]	
		ex.append(bins[i+1]-x_val)
		print 'ex=',ex[i]	
		y.append(f.get(var)[0])
		print 'y=',y[i]	
		ey.append(f.get(var)[1])
		print 'ey=',ey[i]	
		bins[i+1]+=50 #to separate the bins
		
	bins[0]-=20 #to separate the bins
	
	n = len(x)	


	#Build and plot the Graph
	gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
	gStyle.SetFillStyle(4000)	
	gStyle.SetLabelOffset(0.02)	
		
	#c1 = TCanvas("c1","The yields per pb",200,10,700,500)
	c1 = TCanvas("c1","The yields per pb",1200,600)
	gPad.SetRightMargin(0.2)   
	gPad.SetBottomMargin(0.2) 
	
	gr = TGraphErrors(n,array('d',x),array('d',y),array('d',ex),array('d',ey))

	#Mess around with the axis
	#Add the binning and labels
	gr.GetXaxis().Set(n,array('d',bins))
	for i,l in enumerate(labels): gr.GetXaxis().SetBinLabel(i+1,l)	
	gr.GetXaxis().LabelsOption('d')
	gr.GetXaxis().SetTickLength(0.)
	gr.GetXaxis().SetLabelSize(0.06)
	
	gr.GetYaxis().SetRangeUser(y_range[0], y_range[1])
	gr.GetYaxis().SetTitle(y_title)
	gr.GetYaxis().SetTitleSize(0.06)
	gr.GetYaxis().SetLabelSize(0.06)
	
	gr.SetMarkerColor(2)
	gr.SetMarkerStyle(20)
	
	#Draw the benchmark lines	
	leg = TLegend(0.37,0.76,0.70,0.92)
	leg.SetHeader(channel)	
	leg.SetFillStyle(0)	
	leg.SetTextSize(0.04)	
	gr.Draw('AP')
	leg.AddEntry(gr,y_title,'lep');
	
	m_store = [] #so we see everything also on the popup graph
	
	for i,b in enumerate(benchmarks):
		mean = b.get(var)[0]	
		err = b.get(var)[1]	
		m_plus = TLine(bins[0], mean+err, bins[n], mean+err)
		m = TLine(bins[0], mean, bins[n], mean)
		m_min = TLine(bins[0], mean-err, bins[n], mean-err)
		m.SetLineColor(i+2)
		m_plus.SetLineColor(i+2)
		m_min.SetLineColor(i+2)
		m.SetLineWidth(3)
		m_plus.SetLineWidth(1)
		m_min.SetLineWidth(1)
		m_plus.SetLineStyle(3)	
		#m.SetLineStyle(2)	
		m_min.SetLineStyle(3)	
		m.Draw('SAME')
		m_plus.Draw('SAME')
		m_min.Draw('SAME')
		
		leg.AddEntry(m,b.get('name'),'l');

		m_store.append(m)
		m_store.append(m_plus)
		m_store.append(m_min)
	
	#ReDraw point on the benchmark lines	
	gr.Draw('PSAME')
	leg.Draw('same')


	#Store
	#c1.Print(dir+plotName+'.ps')
	c1.SaveAs(dir+plotName+'.ps')

	return m_store,c1,gr,leg

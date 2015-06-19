from ROOT import *


# The list of different toytables:
# -rw-r--r--. 1 stolk z5  7836 Jul  6 00:55 toytable_BDTpaper_spring13_2011.py
# -rw-r--r--. 1 stolk z5  7848 Jul  6 00:55 toytable_BDTpaper_spring13_2012.py
# -rw-r--r--. 1 stolk z5  7396 Jul  6 00:55 toytable_summer13_7bins.py
# -rw-r--r--. 1 stolk z5  7779 Jul  6 00:55 toytable_summer13.py
# -rw-r--r--. 1 stolk z5  7775 Jul  6 00:55 toytable_summer13_scaled2.py

#from Bs2MuMuParams import toytable_summer13 as TheTable #Does not wok yet, needs to be compiled I guess
#import toytable_summer13 as TheTable #Copied the table
#import toytable_summer13_Ale8Jul as TheTable #Alessio's table, has proper exc. bkg shape parameters
import toytable_summer13_kmnuSys as TheTable # New rable from Ale for the combination, includes the KMuNu

from SomeMassModels import RooPhysBkg #For the exclusive backgrounds
from constrain_funcs import * #To build the Gaussian constraints in one go
from profile_import_Siim import * #Import data and other methods
import os

#####################################################################################
# --------------------------------------------------------------------------------- #
print ' o) Define the variable names, global variables tweaking the fit...'
opts = {}
# --------------------------------------------------------------------------------- #
# The output of the code goes to:
opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_CMSfitTo/'
#opts['RESULTDIR'] = 'Profile_Results/2013_StudyConstraints_v2/'
# --------------------------------------------------------------------------------- #

if not os.path.exists(opts.get('RESULTDIR')): os.makedirs(opts.get('RESULTDIR'))
#-------------#
opts['DATADIR'] = 'Profile_Datafiles/'
if not os.path.exists(opts.get('DATADIR')): os.makedirs(opts.get('DATADIR'))
#-------------#
opts['NTUPLE'] = 'UB_2013'
opts['FORCECUTDATA'] = 0 # Do not read in, but redo the cutting on original sample
#-------------#
opts['FITANDPLOT']= 1 #Perform the fit and plot the results in every bin
opts['PROFILELIKELIHOOD']= 0 #Create the likelihood and profile likelihood plots for BR_s
opts['FIXFITMODEL']= 0
opts['PRINT_MODEL']= 0
#-------------#
#####################################################################################
opts['massname']= 'B_s0_MM'
opts['bdtname'] = 'BDT12flat'

opts['FIX_BRs' ]= 0

opts['INCLUDE_BD']= 1
opts['FIX_BRd' ]= 0

opts['FIX_ALPHAS' ]= 0
opts['ADD_ALPHA_CONST']= 1
opts['FIX_FDFS']= 0
opts['ADD_FDFS_CONST']= 1

#Configure peaking background components
#RooPhysBkg shape in every bin
opts['USE_ROOKEYS_MISID']= 1

opts['ADD_B0PIMUNU']= 1
opts['FIX_B0PIMUNU']= 0
opts['ADD_B0PIMUNU_CONST']= 1

opts['ADD_B0UPIMUMU'] = 1
opts['FIX_B0UPIMUMU'] = 0
opts['ADD_B0UPIMUMU_CONST'] = 1

opts['ADD_LAPMUNU' ]= 0
opts['FIX_LAPMUNU' ]= 0
opts['ADD_LAPMUNU_CONST' ]= 0

opts['UNIFORM_KAPPA'] = 0 #same slope everywhere
opts['DOUBLE_EXPO']= 0
opts['BIND_SLOPES_IN_LAST_2_BINS']= 1 #Use the same slope in bin 8 and 7
opts['USE_7_BINS'] = 0

#BDT_DEN = 1.76201e+04
#BDT_PDF = {"2":5.33030e+02*1./BDT_DEN, "3":1.26436e+02*1./BDT_DEN, "4":4.53571e+01*1./BDT_DEN, "5":3.15557e+01*1./BDT_DEN,"6":7.38383e+00*1./BDT_DEN, "7":9.30460e+00*1./BDT_DEN, "8": 1.97407e+00*1./BDT_DEN}

if opts.get('DOUBLE_EXPO'): Mass = RooRealVar(opts.get('massname'),opts.get('massname'),4170, 6565)
#else: Mass = RooRealVar(opts.get('massname'),opts.get('massname'),5432.96 - 120,6000)#4900, 6000)
else: Mass = RooRealVar(opts.get('massname'),opts.get('massname'),4900, 6000)

# --------------------------------------------------------------------------------- #
# A)  Introducing the BDT variable and the bins, importing RooDataSets
# --------------------------------------------------------------------------------- #

print ' o) Build the BDT cuts for every bin...'
samplename = "sample"
Binning = {}
Binning[opts.get('bdtname')] = [0, .25,.4,.5,.6,.7,.8,.9,1.]
BDT = BDT_cuts(opts.get('bdtname'), Binning)

print ' o) Define the BDT categories...'
cat =  RooCategory(samplename, samplename)
for i in range(1,9): cat.defineType("mumu bin" + str(i))

print ' o) Define the fiducial cuts...'
fiducial = opts.get('bdtname') + '!= 0.' # no 0 BDT events
##Muon cuts
fiducial +=     '&& muminus_TRACK_CHI2NDOF<3. && muplus_TRACK_CHI2NDOF<3.'
fiducial +=     '&& muminus_TRACK_GhostProb<0.3&&muplus_TRACK_GhostProb<0.3'
fiducial +=     '&& muminus_IPCHI2_OWNPV>25 && muplus_IPCHI2_OWNPV>25'
fiducial +=     '&& muminus_PT>250 && muplus_PT>250'
fiducial +=     '&& muminus_PT<40e03 && muplus_PT<40e03'
fiducial +=     '&& muminus_P<500e03 && muplus_P<500e03'
fiducial +=     '&& muminus_isMuon==1 && muplus_isMuon==1'
##B meson cuts
fiducial +=     '&& B_s0_BDTS_VTXCHI2<9'
fiducial +=     '&& B_s0_BDTS_DOCA<0.3'
fiducial +=     '&& B_s0_PT>500'
fiducial +=     '&& B_s0_TAU*1000.<13.248'
fiducial +=     '&& muminus_PIDK<10 && muplus_PIDK<10'
fiducial +=     '&& muminus_PIDmu>-5 && muplus_PIDmu>-5'
fiducial +=     '&& B_s0_BDTS>0.05'

print '  ---------------------------------  '
print '  THE FIDUCIAL CUTS: '
print '     ', fiducial
print '  ---------------------------------  '

# --------------------------------------------------------------------------------- #
print ' o) Read in data with the fiducial cuts'

data = dataObj(opts.get('NTUPLE')) #Import the total 2013 3fb-1 nTuple
tree_TOT = data.tree
tree_name = data.t_name

#Fiducial cut tree
path = opts.get('DATADIR')+opts.get('NTUPLE')+'_FID.root'
cut = fiducial

tree_FID, f_fid = 0, 0

if os.path.exists(path) and not opts.get('FORCECUTDATA'):
    print '   Tree found at: ', path
    f_fid = TFile(path)
    tree_FID = f_fid.Get('DecayTree')
else:
    f_fid = TFile(path,'recreate')
    print '  applying fiducial cuts...'
    tree_FID = tree_TOT.CopyTree(cut)
    f_fid.Write()
    #file.Close()
    #file = TFile(path)
print ' FIDUCIAL TREE READ in!'
print '             entries: ', tree_FID.GetEntries()

# --------------------------------------------------------------------------------- #
print '  o) Get the datasets for every BDT bin..'

BDT_file, BDT_tree, BDT_data= {},{},{}

for i in range(1+opts.get('USE_7_BINS'),9):
    path = opts.get('DATADIR')+opts.get('NTUPLE')+'_FID_BDT_'+str(i)+'.root'
    cut = fiducial + BDT[i]
    print ' -----------------------------------------    '
    print '   BDT bin :', i
    print '   ------    '
    print '     Data ile path :', path
    print '     Cut           : ', cut
    print '   ------    '
    print ' -----------------------------------------    '
    f, tree_BDT = 0,0
    if os.path.exists(path) and not opts.get('FORCECUTDATA'):
        print '     Tree found at: ', path
        f = TFile(path)
        tree_BDT = f.Get('DecayTree')
        print '     Entries: ', tree_BDT.GetEntries()
    else:
        f = TFile(path,'recreate')
        print '     applying BDT bin cut...'
        tree_BDT = tree_FID.CopyTree(cut)
        f.Write()

    #Get results out of the scope
    BDT_file[i] = f
    BDT_tree[i] = tree_BDT
    print '     Creating a RooDataSet for BDT Bin:',i
    BDT_data[i] = RooDataSet("data_bin_"+str(i),"data_bin_"+str(i),BDT_tree[i],RooArgSet(Mass))
    print '     Events in RooDataSet :', BDT_data[i].numEntries()
    print ' -----------------------------------------  \n  '

print ' -----------------------------------------------------------------------------    '
print ' --> The datasets (BDT_data[]) have been imported and BDT categories created'
print ' -----------------------------------------------------------------------------  \n  '

# --------------------------------------------------------------------------------- #
# B) MODEL BUILDING
print ' -----------------------------------------------------------------------------  \n  '
print '  Proceeding with building the model... \n'
print ' -----------------------------------------------------------------------------  \n  '
# --------------------------------------------------------------------------------- #

print '     MODEL:   o) Import the trigger corrections for BDT bins (Justine factors)...'

justine = [TheTable.Justine1, TheTable.Justine2, TheTable.Justine3 , TheTable.Justine4, TheTable.Justine5, TheTable.Justine6 , TheTable.Justine7, TheTable.Justine8]
j1 = RooRealVar("j1","j1",justine[0])
j2 = RooRealVar("j2","j2",justine[1])
j3 = RooRealVar("j3","j3",justine[2])
j4 = RooRealVar("j4","j4",justine[3])
j5 = RooRealVar("j5","j5",justine[4])
j6 = RooRealVar("j6","j6",justine[5])
j7 = RooRealVar("j7","j7",justine[6])
j8 = RooRealVar("j8","j8",justine[7])


print '     MODEL:  -> Done! \n'
print '     MODEL:   o) Import the double MisID hh->mumu yield...'
nmis ,nmis_cons = createConst(TheTable.MisIDTotYield,TheTable.MisIDTotYieldErr, "Nmis")
print '     MODEL:  -> Done! \n'
print '     MODEL:   o) Import the misid phase space(->BDT) dependence correction factors...'

mid_idf = [TheTable.MisIDfBDTBin1,TheTable.MisIDfBDTBin2,TheTable.MisIDfBDTBin3,TheTable.MisIDfBDTBin4,TheTable.MisIDfBDTBin5,TheTable.MisIDfBDTBin6,TheTable.MisIDfBDTBin7,TheTable.MisIDfBDTBin8]
missid_corr1 = RooRealVar("missid_corr1","missid_corr1",mid_idf[0])
missid_corr2 = RooRealVar("missid_corr2","missid_corr2",mid_idf[1])
missid_corr3 = RooRealVar("missid_corr3","missid_corr3",mid_idf[2])
missid_corr4 = RooRealVar("missid_corr4","missid_corr4",mid_idf[3])

missid_corr5 = RooRealVar("missid_corr5","missid_corr5",mid_idf[4])
missid_corr6 = RooRealVar("missid_corr6","missid_corr6",mid_idf[5])
missid_corr7 = RooRealVar("missid_corr7","missid_corr7",mid_idf[6])
missid_corr8 = RooRealVar("missid_corr8","missid_corr8",mid_idf[7])

print '     MODEL:  -> Done! \n'
print '     MODEL:   o) Import the time acceptance correction in the BDT bins...'

#For correcting the normalizatio (divide alpha by this)
timeAccCorrBs ,timeAccCorrBs_cons = createConst(TheTable.TimeAcceptanceCorrBs,TheTable.TimeAcceptanceCorrBsErr, "timeAccCorrBs")
timeAccCorrBd ,timeAccCorrBd_cons = createConst(TheTable.TimeAcceptanceCorrBd,TheTable.TimeAcceptanceCorrBdErr, "timeAccCorrBd")

#For correcting the signal yields pre BDT bin (for Bs only)
timeAccN = [TheTable.TimeAcc1,TheTable.TimeAcc2,TheTable.TimeAcc3,TheTable.TimeAcc4,TheTable.TimeAcc5,TheTable.TimeAcc6,TheTable.TimeAcc7,TheTable.TimeAcc8]
timeAcc1 = RooRealVar("timeAcc1","timeAcc1",timeAccN[0])
timeAcc2 = RooRealVar("timeAcc2","timeAcc2",timeAccN[1])
timeAcc3 = RooRealVar("timeAcc3","timeAcc3",timeAccN[2])
timeAcc4 = RooRealVar("timeAcc4","timeAcc4",timeAccN[3])
timeAcc5 = RooRealVar("timeAcc5","timeAcc5",timeAccN[4])
timeAcc6 = RooRealVar("timeAcc6","timeAcc6",timeAccN[5])
timeAcc7 = RooRealVar("timeAcc7","timeAcc7",timeAccN[6])
timeAcc8 = RooRealVar("timeAcc8","timeAcc8",timeAccN[7])

print '     MODEL:  -> Done! \n'
print '     MODEL:   o) Define normalized candidate yields '
print '                 N = BR*TimeAccCorrection / alphs_s (linking to abs. BR) '


#Parameters necessary for the normalization

#Alpha for BsMuMu is fd/fs * alpha for BdMuMu
fdfs , fdfs_cons = createBifurConst(TheTable.fsfd,TheTable.fsfdErrN,TheTable.fsfdErrP,'fdfs') #Actually the value is fd/fs, do not ask why the table has fsfd
#alpha_KPi , alpha_KPi_cons = createConst(TheTable.NormKPi_fullmass,TheTable.NormKPi_fullmassErr,'alpha_KPi')
#alpha_Bu , alpha_Bu_cons = createConst(TheTable.NormBu_fullmass,TheTable.NormBu_fullmassErr,'alpha_Bu')
alpha_KPi , alpha_KPi_cons = createConst(TheTable.NormKPi_fullmass * 1.0e11,TheTable.NormKPi_fullmassErr*1.0e11,'alpha_KPi')
alpha_Bu , alpha_Bu_cons = createConst(TheTable.NormBu_fullmass * 1.0e11, TheTable.NormBu_fullmassErr * 1.0e11,'alpha_Bu')


print '     MODEL:       .. for Bd -> mumu'
alpha_Bu_err = RooRealVar('eBu','eBu',TheTable.NormBu_fullmassErr*1.e12) #for combination in weighted av
alpha_Bu_err.setConstant()
alpha_KPi_err = RooRealVar('eKPi','eKPi',TheTable.NormKPi_fullmassErr*1.e12) #for combination in weighted av
alpha_KPi_err.setConstant()

alpha_d = RooFormulaVar("alpha_d","alpha_d", "((eKPi^2)/(eKPi^2 + eBu^2))*alpha_Bu + ((eBu^2)/(eKPi^2+eBu^2))*alpha_KPi", RooArgList(alpha_Bu,alpha_Bu_err,alpha_KPi,alpha_KPi_err))
nbd = RooRealVar("NBd","NBd", 5,-20.,1000)

if opts.get('INCLUDE_BD'):
    #alpha_d_mean = 0.0238 # 2.38e-11
    #alpha_d_err = 0.0009 #0.09e-11
    #alpha_d , alpha_d_cons = createConst(alpha_d_mean,alpha_d_err,'alpha_d')

    #BR_d = RooRealVar("BRd","BRd", 1e-10,-0.1e-10,10e-10)
    BR_d = RooRealVar("BRd","BRd", 1,-0.1,10)
    nbd = RooFormulaVar("NBd","NBd", "BRd*1e-10*timeAccCorrBd/(alpha_d*1.e-11)", RooArgList(alpha_d,timeAccCorrBd,BR_d))
    print '     MODEL:       -> Fit also for BR(Bd2mumu)'
else: print '     MODEL:   Fluctuate only the NBd, do not put the BR in.'

print '     MODEL:       .. for Bs -> mumu'
#alpha_s_mean = 0.0893 # 8.93e-11
#alpha_s_err = 0.0064 #0.64e-11
#alpha_s , alpha_s_cons = createConst(alpha_s_mean,alpha_s_err,'alpha_s')
alpha_s = RooFormulaVar("alpha_s","alpha_s", "fdfs*alpha_d", RooArgList(fdfs,alpha_d))
#BR_s = RooRealVar("BRs","BRs", 1e-9,-0.1e-9,10e-9)
BR_s = RooRealVar("BRs","BRs", 1,-0.1,10)
nbs = RooFormulaVar("NBs","NBs", "BRs*1e-9*timeAccCorrBs/(alpha_s*1e-11)", RooArgList(alpha_s,timeAccCorrBs,BR_s))
print '     MODEL:  -> Done! \n'

print '     MODEL:  -> Done! \n'
print '     MODEL:   o) Define the signal mass model (Crystal Ball) for both, Bd and Bs...'

sigmaBs ,sigmaBs_cons = createConst(TheTable.MassResoBs,3*TheTable.MassResoErrBs, "sigmaBs")
sigmaBd ,sigmaBd_cons = createConst(TheTable.MassResoBd,3*TheTable.MassResoErrBd, "sigmaBd")

meanBs ,meanBs_cons = createConst(TheTable.MassMeanBs,3*TheTable.MassMeanErrBs, "MBs")
meanBd ,meanBd_cons = createConst(TheTable.MassMeanBd,3*TheTable.MassMeanErrBd, "MBd")

a , a_cons = createConst(TheTable.CBTrans,TheTable.CBTransErr,'CBTrans')
n , n_cons = createConst(TheTable.CBExpo,TheTable.CBExpoErr,'CBExpo')

print '     MODEL:  -> Done! \n'
print '     MODEL:   o) Import the signal distribution in BDT from hh (TIS) distribution in the BDT...'

BDT_f2 ,BDT_f2_cons = createConst(TheTable.BDT_sig2,TheTable.BDT_sigErr2, "BDT_f2")
BDT_f3 ,BDT_f3_cons = createConst(TheTable.BDT_sig3,TheTable.BDT_sigErr3, "BDT_f3")
BDT_f4 ,BDT_f4_cons = createConst(TheTable.BDT_sig4,TheTable.BDT_sigErr4, "BDT_f4")
BDT_f5 ,BDT_f5_cons = createConst(TheTable.BDT_sig5,TheTable.BDT_sigErr5, "BDT_f5")
BDT_f6 ,BDT_f6_cons = createConst(TheTable.BDT_sig6,TheTable.BDT_sigErr6, "BDT_f6")
BDT_f7 ,BDT_f7_cons = createConst(TheTable.BDT_sig7,TheTable.BDT_sigErr7, "BDT_f7")
BDT_f8 ,BDT_f8_cons = createConst(TheTable.BDT_sig8,TheTable.BDT_sigErr8, "BDT_f8")

BDT_f1 ,BDT_f1_cons = createConst(TheTable.BDT_sig1,TheTable.BDT_sigErr1, "BDT_f1")
#BDT_f1 = RooFormulaVar("BDT_f1", "BDT_f1", "(1-BDT_f2-BDT_f3-BDT_f4-BDT_f5-BDT_f6-BDT_f7-BDT_f8)", RooArgList(BDT_f2,BDT_f3,BDT_f4,BDT_f5,BDT_f6,BDT_f7,BDT_f8)) #wrong, the renormalization needs to be done at the end, for all the corrections together!

print '     MODEL:  -> Done! \n'
print '     MODEL:   o) Import the Double Misidentified hh->mumu background model parameters...'

print '     MODEL:    Parameters for 3 x CrystalBall from MC'
#Shift between the means in toytable_test_1fb_AleInput.py and
#toytable_summer13.py
shift_Bs = 1.11
shift_Bd = -0.27
shift = (shift_Bs + shift_Bd)/2
missid_mean1 = RooRealVar("missid_mean1","missid_mean1",5.09168e+03+100+shift)#5050, 5600)#5168.)
missid_d1= RooRealVar("missid_d1","missid_d1", 4.01034e+01)#72.4, 20., 200.)
missid_d2= RooRealVar("missid_d2","missid_d2", 4.03549e+01)#72.4, 20., 200.)
missid_mean2 = RooFormulaVar("missid_mean2","missid_mean2", "missid_mean1 + missid_d1" ,RooArgList(missid_mean1,missid_d1) )
missid_mean3 = RooFormulaVar("missid_mean3","missid_mean3", "missid_mean2 + missid_d2" ,RooArgList(missid_mean2,missid_d2) )
missid_sigma = RooRealVar("missid_sigma","missid_sigma",1.06965e+02  )# 20.,200.)
missid_sigma2 = RooRealVar("missid_sigma2","missid_sigma2",  3.17942e+01)#20.,100.)
missid_sigma3 = RooRealVar("missid_sigma3","missid_sigma3", 3.00653e+01 )#20.,100.)

missid_n = RooRealVar("missid_exponent", "missid_exponent",2.63840e+01  )#1.,  0.1, 120 )
missid_n2 = RooRealVar("missid_exponent2", "missid_exponent2",  7.65872e+00 )# 9.28 ,.1, 120)

missid_a2 = RooRealVar("missid_transition2","missid_transition2",-1.18668e+00 )#-1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3 = RooRealVar("missid_transition3","missid_transition3",2.98721e+00 )#1.38, 0.2, 3) ## Transition point, in sigmas

missid_nb = RooRealVar("missid_exponentb", "missid_exponentb",2.67165e+00)#1.,  0.1, 120 )
missid_n2b = RooRealVar("missid_exponent2b", "missid_exponent2b",  3.16407e+01   )#9.28 ,.1, 120)

missid_a2b = RooRealVar("missid_transition2b","missid_transition2b", -1.85453e+00  )#-1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3b = RooRealVar("missid_transition3b","missid_transition3b", 6.69876e-01  )#1.38, 0.2, 3) ## Transition point, in sigmas1

missid_nc = RooRealVar("missid_exponentc", "missid_exponentc",1.00041e-01  )#1.,  0.1, 12 )
missid_n2c = RooRealVar("missid_exponent2c", "missid_exponent2c",   1.85700e+00)#9.28 ,.1, 12)

missid_a2c = RooRealVar("missid_transition2c","missid_transition2c", -1.75217e+00)# -1.19, -3, -0.2) ## Transition point, in sigmas
missid_a3c = RooRealVar("missid_transition3c","missid_transition3c",1.64220e+00 )#1.38, 0.2, 3) ## Transition point, in sigmas1

missid_f1 = RooRealVar("missid_fraction","missid_fraction", 7.02356e-01 )#0.5, 0., 1.)
missid_f2 = RooRealVar("missid_fraction2","missid_fraction2",6.66982e-01)#0.5, 0., 1.)
hh_f05 = RooRealVar("0.55", "0.5", 0.5) ### This defines the ratio between Bu and Bd MisId CB when Adding together later

#The RooKeys pdf can also be used, but is called when building a model in every
#BDT bin later..see below


print '     MODEL:  -> Done! \n'



if opts.get('ADD_B0PIMUNU'):
    print '     MODEL:   o) Import the parameters needed for Bd->pi mu nu exclusive background...'
    ### B0-> Pi Mu Nu bkg RooPhysBkg model

    sigmaPiMuNu1,sigmaPiMuNu1_cons = createBifurConst(TheTable.arsiPiMuNu1,TheTable.arsiPiMuNu1ErrMinus,TheTable.arsiPiMuNu1ErrPlus, "sigmaPiMuNu1")
    meanPiMuNu1,meanPiMuNu1_cons = createBifurConst(TheTable.armePiMuNu1,TheTable.armePiMuNu1ErrMinus,TheTable.armePiMuNu1ErrPlus,  "meanPiMuNu1")
    coPiMuNu1,coPiMuNu1_cons = createBifurConst(TheTable.arcoPiMuNu1,TheTable.arcoPiMuNu1ErrMinus,TheTable.arcoPiMuNu1ErrPlus,  "coPiMuNu1")

    sigmaPiMuNu2,sigmaPiMuNu2_cons = createBifurConst(TheTable.arsiPiMuNu2,TheTable.arsiPiMuNu2ErrMinus,TheTable.arsiPiMuNu2ErrPlus, "sigmaPiMuNu2")
    meanPiMuNu2,meanPiMuNu2_cons = createBifurConst(TheTable.armePiMuNu2,TheTable.armePiMuNu2ErrMinus,TheTable.armePiMuNu2ErrPlus,  "meanPiMuNu2")
    coPiMuNu2,coPiMuNu2_cons = createBifurConst(TheTable.arcoPiMuNu2,TheTable.arcoPiMuNu2ErrMinus,TheTable.arcoPiMuNu2ErrPlus,  "coPiMuNu2")

    sigmaPiMuNu3,sigmaPiMuNu3_cons = createBifurConst(TheTable.arsiPiMuNu3,TheTable.arsiPiMuNu3ErrMinus,TheTable.arsiPiMuNu3ErrPlus, "sigmaPiMuNu3")
    meanPiMuNu3,meanPiMuNu3_cons = createBifurConst(TheTable.armePiMuNu3,TheTable.armePiMuNu3ErrMinus,TheTable.armePiMuNu3ErrPlus,  "meanPiMuNu3")
    coPiMuNu3,coPiMuNu3_cons = createBifurConst(TheTable.arcoPiMuNu3,TheTable.arcoPiMuNu3ErrMinus,TheTable.arcoPiMuNu3ErrPlus,  "coPiMuNu3")

    sigmaPiMuNu4,sigmaPiMuNu4_cons = createBifurConst(TheTable.arsiPiMuNu4,TheTable.arsiPiMuNu4ErrMinus,TheTable.arsiPiMuNu4ErrPlus, "sigmaPiMuNu4")
    meanPiMuNu4,meanPiMuNu4_cons = createBifurConst(TheTable.armePiMuNu4,TheTable.armePiMuNu4ErrMinus,TheTable.armePiMuNu4ErrPlus,  "meanPiMuNu4")
    coPiMuNu4,coPiMuNu4_cons = createBifurConst(TheTable.arcoPiMuNu4,TheTable.arcoPiMuNu4ErrMinus,TheTable.arcoPiMuNu4ErrPlus,  "coPiMuNu4")

    sigmaPiMuNu5,sigmaPiMuNu5_cons = createBifurConst(TheTable.arsiPiMuNu5,TheTable.arsiPiMuNu5ErrMinus,TheTable.arsiPiMuNu5ErrPlus, "sigmaPiMuNu5")
    meanPiMuNu5,meanPiMuNu5_cons = createBifurConst(TheTable.armePiMuNu5,TheTable.armePiMuNu5ErrMinus,TheTable.armePiMuNu5ErrPlus,  "meanPiMuNu5")
    coPiMuNu5,coPiMuNu5_cons = createBifurConst(TheTable.arcoPiMuNu5,TheTable.arcoPiMuNu5ErrMinus,TheTable.arcoPiMuNu5ErrPlus,  "coPiMuNu5")

    sigmaPiMuNu6,sigmaPiMuNu6_cons = createBifurConst(TheTable.arsiPiMuNu6,TheTable.arsiPiMuNu6ErrMinus,TheTable.arsiPiMuNu6ErrPlus, "sigmaPiMuNu6")
    meanPiMuNu6,meanPiMuNu6_cons = createBifurConst(TheTable.armePiMuNu6,TheTable.armePiMuNu6ErrMinus,TheTable.armePiMuNu6ErrPlus,  "meanPiMuNu6")
    coPiMuNu6,coPiMuNu6_cons = createBifurConst(TheTable.arcoPiMuNu6,TheTable.arcoPiMuNu6ErrMinus,TheTable.arcoPiMuNu6ErrPlus,  "coPiMuNu6")

    sigmaPiMuNu7,sigmaPiMuNu7_cons = createBifurConst(TheTable.arsiPiMuNu7,TheTable.arsiPiMuNu7ErrMinus,TheTable.arsiPiMuNu7ErrPlus, "sigmaPiMuNu7")
    meanPiMuNu7,meanPiMuNu7_cons = createBifurConst(TheTable.armePiMuNu7,TheTable.armePiMuNu7ErrMinus,TheTable.armePiMuNu7ErrPlus,  "meanPiMuNu7")
    coPiMuNu7,coPiMuNu7_cons = createBifurConst(TheTable.arcoPiMuNu7,TheTable.arcoPiMuNu7ErrMinus,TheTable.arcoPiMuNu7ErrPlus,  "coPiMuNu7")

    sigmaPiMuNu8,sigmaPiMuNu8_cons = createBifurConst(TheTable.arsiPiMuNu8,TheTable.arsiPiMuNu8ErrMinus,TheTable.arsiPiMuNu8ErrPlus, "sigmaPiMuNu8")
    meanPiMuNu8,meanPiMuNu8_cons = createBifurConst(TheTable.armePiMuNu8,TheTable.armePiMuNu8ErrMinus,TheTable.armePiMuNu8ErrPlus,  "meanPiMuNu8")
    coPiMuNu8,coPiMuNu8_cons = createBifurConst(TheTable.arcoPiMuNu8,TheTable.arcoPiMuNu8ErrMinus,TheTable.arcoPiMuNu8ErrPlus,  "coPiMuNu8")

    PiMuNu, PiMuNu_cons = createConst(TheTable.PiMuNuYield, TheTable.PiMuNuYieldErr, "PiMuNu")
    PiMuNu2, PiMuNu2_cons = createConst(TheTable.PiMuNu2, TheTable.PiMuNu2Err, "PiMuNu2")
    PiMuNu3, PiMuNu3_cons = createConst(TheTable.PiMuNu3, TheTable.PiMuNu3Err, "PiMuNu3")
    PiMuNu4, PiMuNu4_cons = createConst(TheTable.PiMuNu4, TheTable.PiMuNu4Err, "PiMuNu4")
    PiMuNu5, PiMuNu5_cons = createConst(TheTable.PiMuNu5, TheTable.PiMuNu5Err, "PiMuNu5")
    PiMuNu6, PiMuNu6_cons = createConst(TheTable.PiMuNu6, TheTable.PiMuNu6Err, "PiMuNu6")
    PiMuNu7, PiMuNu7_cons = createConst(TheTable.PiMuNu7, TheTable.PiMuNu7Err, "PiMuNu7")
    PiMuNu8, PiMuNu8_cons = createConst(TheTable.PiMuNu8, TheTable.PiMuNu8Err, "PiMuNu8")
    
    PiMuNu1, PiMuNu1_cons = createConst(TheTable.PiMuNu1, TheTable.PiMuNu1Err, "PiMuNu1")
    #PiMuNu1 = RooFormulaVar("PiMuNu1", "PiMuNu1", "(1-PiMuNu2-PiMuNu3-PiMuNu4-PiMuNu5-PiMuNu6-PiMuNu7-PiMuNu8)", RooArgList(PiMuNu2,PiMuNu3,PiMuNu4,PiMuNu5,PiMuNu6,PiMuNu7,PiMuNu8)) 
    sum_PiMuNu = RooFormulaVar('PiMuNu_sum','Sum of all the raw PiMuNu fractions','(@0+@1+@2+@3+@4+@5+@6+@7)',RooArgList(PiMuNu1,PiMuNu2,PiMuNu3,PiMuNu4,PiMuNu5,PiMuNu6,PiMuNu7,PiMuNu8))

    f_PiMuNu = []
    v = vars()
    for i in range(1,9):
	f_PiMuNu.append(RooFormulaVar("f_PiMuNu_"+str(i),"Fr. of events in PiMuNu bin "+str(i), "(@0/@1)", RooArgList(v['PiMuNu'+str(i)],sum_PiMuNu)))
	print '		 f_PiMuNu:', f_PiMuNu[i-1].getVal()
    print '     MODEL:  -> Done! \n'


if opts.get('ADD_B0UPIMUMU'):
    print '     MODEL:   o) Import the parameters needed for B(0)+->pi(0)+ mu mu exclusive background...'
    ### B(0)+-> Pi(0)+ Mu Mu bkg RooPhysBkg model

    sigmaPiMuMu1,sigmaPiMuMu1_cons = createBifurConst(TheTable.arsiPiMuMu1,TheTable.arsiPiMuMu1ErrMinus,TheTable.arsiPiMuMu1ErrPlus, "sigmaPiMuMu1")
    meanPiMuMu1,meanPiMuMu1_cons = createBifurConst(TheTable.armePiMuMu1,TheTable.armePiMuMu1ErrMinus,TheTable.armePiMuMu1ErrPlus,  "meanPiMuMu1")
    coPiMuMu1,coPiMuMu1_cons = createBifurConst(TheTable.arcoPiMuMu1,TheTable.arcoPiMuMu1ErrMinus,TheTable.arcoPiMuMu1ErrPlus,  "coPiMuMu1")

    sigmaPiMuMu2,sigmaPiMuMu2_cons = createBifurConst(TheTable.arsiPiMuMu2,TheTable.arsiPiMuMu2ErrMinus,TheTable.arsiPiMuMu2ErrPlus, "sigmaPiMuMu2")
    meanPiMuMu2,meanPiMuMu2_cons = createBifurConst(TheTable.armePiMuMu2,TheTable.armePiMuMu2ErrMinus,TheTable.armePiMuMu2ErrPlus,  "meanPiMuMu2")
    coPiMuMu2,coPiMuMu2_cons = createBifurConst(TheTable.arcoPiMuMu2,TheTable.arcoPiMuMu2ErrMinus,TheTable.arcoPiMuMu2ErrPlus,  "coPiMuMu2")

    sigmaPiMuMu3,sigmaPiMuMu3_cons = createBifurConst(TheTable.arsiPiMuMu3,TheTable.arsiPiMuMu3ErrMinus,TheTable.arsiPiMuMu3ErrPlus, "sigmaPiMuMu3")
    meanPiMuMu3,meanPiMuMu3_cons = createBifurConst(TheTable.armePiMuMu3,TheTable.armePiMuMu3ErrMinus,TheTable.armePiMuMu3ErrPlus,  "meanPiMuMu3")
    coPiMuMu3,coPiMuMu3_cons = createBifurConst(TheTable.arcoPiMuMu3,TheTable.arcoPiMuMu3ErrMinus,TheTable.arcoPiMuMu3ErrPlus,  "coPiMuMu3")

    sigmaPiMuMu4,sigmaPiMuMu4_cons = createBifurConst(TheTable.arsiPiMuMu4,TheTable.arsiPiMuMu4ErrMinus,TheTable.arsiPiMuMu4ErrPlus, "sigmaPiMuMu4")
    meanPiMuMu4,meanPiMuMu4_cons = createBifurConst(TheTable.armePiMuMu4,TheTable.armePiMuMu4ErrMinus,TheTable.armePiMuMu4ErrPlus,  "meanPiMuMu4")
    coPiMuMu4,coPiMuMu4_cons = createBifurConst(TheTable.arcoPiMuMu4,TheTable.arcoPiMuMu4ErrMinus,TheTable.arcoPiMuMu4ErrPlus,  "coPiMuMu4")

    sigmaPiMuMu5,sigmaPiMuMu5_cons = createBifurConst(TheTable.arsiPiMuMu5,TheTable.arsiPiMuMu5ErrMinus,TheTable.arsiPiMuMu5ErrPlus, "sigmaPiMuMu5")
    meanPiMuMu5,meanPiMuMu5_cons = createBifurConst(TheTable.armePiMuMu5,TheTable.armePiMuMu5ErrMinus,TheTable.armePiMuMu5ErrPlus,  "meanPiMuMu5")
    coPiMuMu5,coPiMuMu5_cons = createBifurConst(TheTable.arcoPiMuMu5,TheTable.arcoPiMuMu5ErrMinus,TheTable.arcoPiMuMu5ErrPlus,  "coPiMuMu5")

    sigmaPiMuMu6,sigmaPiMuMu6_cons = createBifurConst(TheTable.arsiPiMuMu6,TheTable.arsiPiMuMu6ErrMinus,TheTable.arsiPiMuMu6ErrPlus, "sigmaPiMuMu6")
    meanPiMuMu6,meanPiMuMu6_cons = createBifurConst(TheTable.armePiMuMu6,TheTable.armePiMuMu6ErrMinus,TheTable.armePiMuMu6ErrPlus,  "meanPiMuMu6")
    coPiMuMu6,coPiMuMu6_cons = createBifurConst(TheTable.arcoPiMuMu6,TheTable.arcoPiMuMu6ErrMinus,TheTable.arcoPiMuMu6ErrPlus,  "coPiMuMu6")

    sigmaPiMuMu7,sigmaPiMuMu7_cons = createBifurConst(TheTable.arsiPiMuMu7,TheTable.arsiPiMuMu7ErrMinus,TheTable.arsiPiMuMu7ErrPlus, "sigmaPiMuMu7")
    meanPiMuMu7,meanPiMuMu7_cons = createBifurConst(TheTable.armePiMuMu7,TheTable.armePiMuMu7ErrMinus,TheTable.armePiMuMu7ErrPlus,  "meanPiMuMu7")
    coPiMuMu7,coPiMuMu7_cons = createBifurConst(TheTable.arcoPiMuMu7,TheTable.arcoPiMuMu7ErrMinus,TheTable.arcoPiMuMu7ErrPlus,  "coPiMuMu7")

    sigmaPiMuMu8,sigmaPiMuMu8_cons = createBifurConst(TheTable.arsiPiMuMu8,TheTable.arsiPiMuMu8ErrMinus,TheTable.arsiPiMuMu8ErrPlus, "sigmaPiMuMu8")
    meanPiMuMu8,meanPiMuMu8_cons = createBifurConst(TheTable.armePiMuMu8,TheTable.armePiMuMu8ErrMinus,TheTable.armePiMuMu8ErrPlus,  "meanPiMuMu8")
    coPiMuMu8,coPiMuMu8_cons = createBifurConst(TheTable.arcoPiMuMu8,TheTable.arcoPiMuMu8ErrMinus,TheTable.arcoPiMuMu8ErrPlus,  "coPiMuMu8")

    PiMuMu, PiMuMu_cons = createConst(TheTable.PiMuMuYield, TheTable.PiMuMuYieldErr, "PiMuMu")
    PiMuMu2, PiMuMu2_cons = createConst(TheTable.PiMuMu2, TheTable.PiMuMu2Err, "PiMuMu2")
    PiMuMu3, PiMuMu3_cons = createConst(TheTable.PiMuMu3, TheTable.PiMuMu3Err, "PiMuMu3")
    PiMuMu4, PiMuMu4_cons = createConst(TheTable.PiMuMu4, TheTable.PiMuMu4Err, "PiMuMu4")
    PiMuMu5, PiMuMu5_cons = createConst(TheTable.PiMuMu5, TheTable.PiMuMu5Err, "PiMuMu5")
    PiMuMu6, PiMuMu6_cons = createConst(TheTable.PiMuMu6, TheTable.PiMuMu6Err, "PiMuMu6")
    PiMuMu7, PiMuMu7_cons = createConst(TheTable.PiMuMu7, TheTable.PiMuMu7Err, "PiMuMu7")
    PiMuMu8, PiMuMu8_cons = createConst(TheTable.PiMuMu8, TheTable.PiMuMu8Err, "PiMuMu8")
    
    PiMuMu1, PiMuMu1_cons = createConst(TheTable.PiMuMu1, TheTable.PiMuMu1Err, "PiMuMu1")
    #PiMuMu1 = RooFormulaVar("PiMuMu1", "PiMuMu1", "(1-PiMuMu2-PiMuMu3-PiMuMu4-PiMuMu5-PiMuMu6-PiMuMu7-PiMuMu8)", RooArgList(PiMuMu2,PiMuMu3,PiMuMu4,PiMuMu5,PiMuMu6,PiMuMu7,PiMuMu8)) 
    sum_PiMuMu = RooFormulaVar('PiMuMu_sum','Sum of all the raw PiMuMu fractions','(@0+@1+@2+@3+@4+@5+@6+@7)',RooArgList(PiMuMu1,PiMuMu2,PiMuMu3,PiMuMu4,PiMuMu5,PiMuMu6,PiMuMu7,PiMuMu8))

    f_PiMuMu = []
    v = vars() 
    for i in range(1,9):
        f_PiMuMu.append(RooFormulaVar("f_PiMuMu_"+str(i),"Fr. of events in PiMuMut bin "+str(i), "(@0/@1)", RooArgList(v["PiMuMu"+str(i)],sum_PiMuMu)))
	print '		 f_PiMuMu:', f_PiMuMu[i-1].getVal()
	
    print '     MODEL:  -> Done! \n'

if opts.get('ADD_LAPMUNU'):
    print '     MODEL:   o) Import the parameters needed for Bs -> K mu nu exclusive background...'
    ### Lambda_b --> proton mu nu

    sigmaLaPMuNu1,sigmaLaPMuNu1_cons = createBifurConst(TheTable.arsiLaPMuNu1,TheTable.arsiLaPMuNu1ErrMinus,TheTable.arsiLaPMuNu1ErrPlus, "sigmaLaPMuNu1")
    meanLaPMuNu1,meanLaPMuNu1_cons = createBifurConst(TheTable.armeLaPMuNu1,TheTable.armeLaPMuNu1ErrMinus,TheTable.armeLaPMuNu1ErrPlus,  "meanLaPMuNu1")
    coLaPMuNu1,coLaPMuNu1_cons = createBifurConst(TheTable.arcoLaPMuNu1,TheTable.arcoLaPMuNu1ErrMinus,TheTable.arcoLaPMuNu1ErrPlus,  "coLaPMuNu1")

    sigmaLaPMuNu2,sigmaLaPMuNu2_cons = createBifurConst(TheTable.arsiLaPMuNu2,TheTable.arsiLaPMuNu2ErrMinus,TheTable.arsiLaPMuNu2ErrPlus, "sigmaLaPMuNu2")
    meanLaPMuNu2,meanLaPMuNu2_cons = createBifurConst(TheTable.armeLaPMuNu2,TheTable.armeLaPMuNu2ErrMinus,TheTable.armeLaPMuNu2ErrPlus,  "meanLaPMuNu2")
    coLaPMuNu2,coLaPMuNu2_cons = createBifurConst(TheTable.arcoLaPMuNu2,TheTable.arcoLaPMuNu2ErrMinus,TheTable.arcoLaPMuNu2ErrPlus,  "coLaPMuNu2")

    sigmaLaPMuNu3,sigmaLaPMuNu3_cons = createBifurConst(TheTable.arsiLaPMuNu3,TheTable.arsiLaPMuNu3ErrMinus,TheTable.arsiLaPMuNu3ErrPlus, "sigmaLaPMuNu3")
    meanLaPMuNu3,meanLaPMuNu3_cons = createBifurConst(TheTable.armeLaPMuNu3,TheTable.armeLaPMuNu3ErrMinus,TheTable.armeLaPMuNu3ErrPlus,  "meanLaPMuNu3")
    coLaPMuNu3,coLaPMuNu3_cons = createBifurConst(TheTable.arcoLaPMuNu3,TheTable.arcoLaPMuNu3ErrMinus,TheTable.arcoLaPMuNu3ErrPlus,  "coLaPMuNu3")

    sigmaLaPMuNu4,sigmaLaPMuNu4_cons = createBifurConst(TheTable.arsiLaPMuNu4,TheTable.arsiLaPMuNu4ErrMinus,TheTable.arsiLaPMuNu4ErrPlus, "sigmaLaPMuNu4")
    meanLaPMuNu4,meanLaPMuNu4_cons = createBifurConst(TheTable.armeLaPMuNu4,TheTable.armeLaPMuNu4ErrMinus,TheTable.armeLaPMuNu4ErrPlus,  "meanLaPMuNu4")
    coLaPMuNu4,coLaPMuNu4_cons = createBifurConst(TheTable.arcoLaPMuNu4,TheTable.arcoLaPMuNu4ErrMinus,TheTable.arcoLaPMuNu4ErrPlus,  "coLaPMuNu4")

    sigmaLaPMuNu5,sigmaLaPMuNu5_cons = createBifurConst(TheTable.arsiLaPMuNu5,TheTable.arsiLaPMuNu5ErrMinus,TheTable.arsiLaPMuNu5ErrPlus, "sigmaLaPMuNu5")
    meanLaPMuNu5,meanLaPMuNu5_cons = createBifurConst(TheTable.armeLaPMuNu5,TheTable.armeLaPMuNu5ErrMinus,TheTable.armeLaPMuNu5ErrPlus,  "meanLaPMuNu5")
    coLaPMuNu5,coLaPMuNu5_cons = createBifurConst(TheTable.arcoLaPMuNu5,TheTable.arcoLaPMuNu5ErrMinus,TheTable.arcoLaPMuNu5ErrPlus,  "coLaPMuNu5")

    sigmaLaPMuNu6,sigmaLaPMuNu6_cons = createBifurConst(TheTable.arsiLaPMuNu6,TheTable.arsiLaPMuNu6ErrMinus,TheTable.arsiLaPMuNu6ErrPlus, "sigmaLaPMuNu6")
    meanLaPMuNu6,meanLaPMuNu6_cons = createBifurConst(TheTable.armeLaPMuNu6,TheTable.armeLaPMuNu6ErrMinus,TheTable.armeLaPMuNu6ErrPlus,  "meanLaPMuNu6")
    coLaPMuNu6,coLaPMuNu6_cons = createBifurConst(TheTable.arcoLaPMuNu6,TheTable.arcoLaPMuNu6ErrMinus,TheTable.arcoLaPMuNu6ErrPlus,  "coLaPMuNu6")

    sigmaLaPMuNu7,sigmaLaPMuNu7_cons = createBifurConst(TheTable.arsiLaPMuNu7,TheTable.arsiLaPMuNu7ErrMinus,TheTable.arsiLaPMuNu7ErrPlus, "sigmaLaPMuNu7")
    meanLaPMuNu7,meanLaPMuNu7_cons = createBifurConst(TheTable.armeLaPMuNu7,TheTable.armeLaPMuNu7ErrMinus,TheTable.armeLaPMuNu7ErrPlus,  "meanLaPMuNu7")
    coLaPMuNu7,coLaPMuNu7_cons = createBifurConst(TheTable.arcoLaPMuNu7,TheTable.arcoLaPMuNu7ErrMinus,TheTable.arcoLaPMuNu7ErrPlus,  "coLaPMuNu7")

    sigmaLaPMuNu8,sigmaLaPMuNu8_cons = createBifurConst(TheTable.arsiLaPMuNu8,TheTable.arsiLaPMuNu8ErrMinus,TheTable.arsiLaPMuNu8ErrPlus, "sigmaLaPMuNu8")
    meanLaPMuNu8,meanLaPMuNu8_cons = createBifurConst(TheTable.armeLaPMuNu8,TheTable.armeLaPMuNu8ErrMinus,TheTable.armeLaPMuNu8ErrPlus,  "meanLaPMuNu8")
    coLaPMuNu8,coLaPMuNu8_cons = createBifurConst(TheTable.arcoLaPMuNu8,TheTable.arcoLaPMuNu8ErrMinus,TheTable.arcoLaPMuNu8ErrPlus,  "coLaPMuNu8")

    LaPMuNu, LaPMuNu_cons = createConst(TheTable.LaPMuNuYield, TheTable.LaPMuNuYieldErr, "LaPMuNu")
    LaPMuNu2, LaPMuNu2_cons = createConst(TheTable.LaPMuNu2, TheTable.LaPMuNu2Err, "LaPMuNu2")
    LaPMuNu3, LaPMuNu3_cons = createConst(TheTable.LaPMuNu3, TheTable.LaPMuNu3Err, "LaPMuNu3")
    LaPMuNu4, LaPMuNu4_cons = createConst(TheTable.LaPMuNu4, TheTable.LaPMuNu4Err, "LaPMuNu4")
    LaPMuNu5, LaPMuNu5_cons = createConst(TheTable.LaPMuNu5, TheTable.LaPMuNu5Err, "LaPMuNu5")
    LaPMuNu6, LaPMuNu6_cons = createConst(TheTable.LaPMuNu6, TheTable.LaPMuNu6Err, "LaPMuNu6")
    LaPMuNu7, LaPMuNu7_cons = createConst(TheTable.LaPMuNu7, TheTable.LaPMuNu7Err, "LaPMuNu7")
    LaPMuNu8, LaPMuNu8_cons = createConst(TheTable.LaPMuNu8, TheTable.LaPMuNu8Err, "LaPMuNu8")
    
    
    LaPMuNu1, LaPMuNu1_cons = createConst(TheTable.LaPMuNu1, TheTable.LaPMuNu1Err, "LaPMuNu1")
    #LaPMuNu1 = RooFormulaVar("LaPMuNu1", "LaPMuNu1", "(1-LaPMuNu2-LaPMuNu3-LaPMuNu4-LaPMuNu5-LaPMuNu6-LaPMuNu7-LaPMuNu8)", RooArgList(LaPMuNu2,LaPMuNu3,LaPMuNu4,LaPMuNu5,LaPMuNu6,LaPMuNu7,LaPMuNu8)) 
    sum_LaPMuNu = RooFormulaVar('LaPMuNu_sum','Sum of all the raw LaPMuNu fractions','(@0+@1+@2+@3+@4+@5+@6+@7)',RooArgList(LaPMuNu1,LaPMuNu2,LaPMuNu3,LaPMuNu4,LaPMuNu5,LaPMuNu6,LaPMuNu7,LaPMuNu8))
    f_LaPMuNu = []
    v = vars() 
    for i in range(1,9):
	f_LaPMuNu.append(RooFormulaVar("f_LaPMuNu_"+str(i),"Fr. of events in LaPMuNut bin "+str(i), "(@0/@1)", RooArgList(v["LaPMuNu"+str(i)],sum_LaPMuNu)))

	print '		 f_LaPMuNu:', f_LaPMuNu[i-1].getVal()

    print '     MODEL:  -> Done! \n'

print '     MODEL:   o) Import the collect all the variables to the v[] vector...'
v = vars()
print '     MODEL:  -> Done! \n'

####################################################
# CALCULATE THE FRACTION OF SIGNL EVENTS PER BDT BIN
####################################################

print ' ---------------------------------------------------------'
print '     MODEL:   o) Calculate the correction fraction per bin: '
print ' 			f_bs_raw_i = BDT_f_i * timeAcc_i / justine'
print ' 			f_bd_raw_i = BDT_f_i / justine'

f_bs_raw = []
f_bd_raw = []
f_missid_raw = []
for i in range(1,9):
	print '   --> Calculate raw fraction for bin:', i
	f_bs_raw.append(RooFormulaVar("f_bs_raw_"+str(i),"Unnormalized fr. of events in bdt bin "+str(i), "(@0*(1/@1)*@2)", RooArgList(v['BDT_f'+str(i)],v['j'+str(i)],v['timeAcc'+str(i)])))
	f_bd_raw.append(RooFormulaVar("f_bd_raw_"+str(i),"Unnormalized fr. of events in bdt bin "+str(i), "(@0*(1/@1))", RooArgList(v['BDT_f'+str(i)],v['j'+str(i)])))
	f_missid_raw.append(RooFormulaVar("f_missid_raw_"+str(i),"Unnormalized fr. of misID events in bdt bin "+str(i), "(@0/@1)", RooArgList(v['BDT_f'+str(i)],v['missid_corr'+str(i)])))

	print '		 f_bs_raw:', f_bs_raw[i-1].getVal()
	print '		 f_bd_raw:', f_bd_raw[i-1].getVal()


#Sums
sum_bs = RooFormulaVar('f_bs_raw_sum','Sum of all the raw bs fractions','(@0+@1+@2+@3+@4+@5+@6+@7)',RooArgList(f_bs_raw[0],f_bs_raw[1],f_bs_raw[2],f_bs_raw[3],f_bs_raw[4],f_bs_raw[5],f_bs_raw[6],f_bs_raw[7]))
sum_bd = RooFormulaVar('f_bd_raw_sum','Sum of all the raw bd fractions','(@0+@1+@2+@3+@4+@5+@6+@7)',RooArgList(f_bd_raw[0],f_bd_raw[1],f_bd_raw[2],f_bd_raw[3],f_bd_raw[4],f_bd_raw[5],f_bd_raw[6],f_bd_raw[7]))
sum_missid = RooFormulaVar('f_missid_raw_sum','Sum of all the raw missid fractions','(@0+@1+@2+@3+@4+@5+@6+@7)',RooArgList(f_missid_raw[0],f_missid_raw[1],f_missid_raw[2],f_missid_raw[3],f_missid_raw[4],f_missid_raw[5],f_missid_raw[6],f_missid_raw[7]))


print ' sum_f_bs = ', sum_bs.getVal()
print ' sum_f_bd = ', sum_bd.getVal()
print ' sum_f_missid = ', sum_missid.getVal()
print ' ---------------------------------------------------------'

#Renormalize the fractions
f_bs = []
f_bd = []
f_missid = []
for i in range(1,9):
	print '   --> Calculate final re-normalized fraction for bin:', i
	f_bs.append(RooFormulaVar("f_bs_"+str(i),"Fr. of events in bdt bin "+str(i), "(@0/@1)", RooArgList(f_bs_raw[i-1],sum_bs)))
	f_bd.append(RooFormulaVar("f_bd_"+str(i),"Fr. of events in bdt bin "+str(i), "(@0/@1)", RooArgList(f_bd_raw[i-1],sum_bd)))
	f_missid.append(RooFormulaVar("f_missid_"+str(i),"Fr. of events in missidt bin "+str(i), "(@0/@1)", RooArgList(f_missid_raw[i-1],sum_missid)))
	
	print '		 f_bs:', f_bs[i-1].getVal()
	print '		 f_bd:', f_bd[i-1].getVal()
	print '		 f_missid:', f_missid[i-1].getVal()
print ' ---------------------------------------------------------'

####################################################
v = vars()
class BsMuMuModel:

    def __init__(self, glbin):
        self.i = str(glbin)
        i = self.i
        prefix = '      MODEL BDT BIN ' + str(i)
        print ' ------------------------------------'
        print prefix
        print ' ------------------------------------'

        print '     o) Link the yields per bin to the total yield :'
	print '         -> N_Bs_bin = N_Bs_i * f_bs_i'
	self.nbs = RooFormulaVar("NBs" + i ,"NBs" + i, "(@0*@1)", RooArgList(v["nbs"],f_bs[glbin-1]))

	print '         -> N_Bd_bin = N_Bs * f_bd_i'
        self.nbd = RooFormulaVar("NBd" + i ,"NBd" + i, "(@0*@1)", RooArgList(v["nbd"],f_bd[glbin-1]))

        print  '    o) Define the signal shape..'
        self.Bs = RooCBShape("model Bs" + i, "model Bs"+ i, Mass, meanBs,sigmaBs,a,n)
        self.Bd = RooCBShape("model Bd" + i, "model Bd"+ i, Mass, meanBd,sigmaBd,a,n)

        print  '    o) Define the combinatorial bkg shape..'
        self.nbkg = RooRealVar("MuMuBkg"+i,"MuMuBkg"+i, 0,70000)

        if opts.get('UNIFORM_KAPPA') and i!= "1":
            print prefix + ' NB! Using the same slope for all the bins.'
            self.k = mm[1].k
            self.dk = mm[1].dk
            self.kb = mm[1].kb
            self.fb = mm[1].fb
        elif opts.get('BIND_SLOPES_IN_LAST_2_BINS') and i=="8":
            print prefix + ' NB! Use the same slope as in bin 7'
            self.k = mm[7].k
            self.dk = mm[7].dk
            self.kb = mm[7].kb
            self.fb = mm[7].fb
        else:
            self.k = RooRealVar("MuMu_k_"+i,"MuMu_k_" + i, -7e-04, -1e-02,1e-02)
            self.dk = RooRealVar("MuMu_dk_"+i,"MuMu_dk_" + i,-7e-04, -1e-02,0)#1e-02)
            self.kb = RooFormulaVar("MuMu_kb_"+i,"MuMu_kb_" + i,"MuMu_k_"+i + " + MuMu_dk_" + i, RooArgList(self.k,self.dk))
            self.fb = RooRealVar("MuMu_f_"+i,"MuMu_f_" + i,0.5,0.,1.)
            self.fb.setConstant()

        self.bkg1 = RooExponential("bkg1 MuMu model" + i , "bkg1 MuMu model" + i, Mass,self.k)
        self.bkg2 = RooExponential("bkg2 MuMu model" + i , "bkg2 MuMu model" + i, Mass,self.kb)

        if opts.get('DOUBLE_EXPO'): self.bkg = RooAddPdf("bkg MuMu model" + i, "bkg MuMu model" + i, self.bkg1,self.bkg2, self.fb)
        else: self.bkg = self.bkg1

        #Base model without the peaking background components
        model_components = RooArgList(self.bkg,self.Bs,self.Bd)
        model_yields = RooArgList(self.nbkg,self.nbs,self.nbd)

        print  prefix +'    o) Propagate the total number of MisID events to the BDT bins'
        print  prefix +'        nmis_bin = nmis_TOT*BDTsig/misIDCorr'
        #self.nmis = RooFormulaVar("Nmis" + i ,"Nmis" + i, "Nmis*BDT_f"+i+ "*1./missid_corr"+i, RooArgList(v["BDT_f"+i],v["nmis"],v["j"+i],v["missid_corr"+i]))
        self.nmis = RooFormulaVar("Nmis" + i ,"Nmis" + i, "(@0*@1)", RooArgList(v["nmis"],f_missid[glbin-1]))
        model_yields.add(self.nmis)

        if opts.get('USE_ROOKEYS_MISID'): #From Alessio, 9 Jul 2013
            self.f_roomisid = TFile("rookeys_misID_shift.root","READ")
            self.f_roomisid.cd()
            self.aw = self.f_roomisid.Get("new")
            #aw.Print()
            self.aw.var('m_{#mu#mu}').SetNameTitle(opts.get('massname'),opts.get('massname'))
            self.missid = self.aw.pdf("misIDKernelPDF")
            #self.missid.SetNameTitle('misIDKernelPDF_'+i,'misIDKernelPDF_')
            self.missid.SetNameTitle('missid'+i,'missid'+i)
            model_components.add(self.missid)

        else:
            self.missid_MSu1 = RooCBShape("missid_MSu" + "_"+ i,"missid_MSu"+ "_"+ i, Mass, missid_mean1, missid_sigma, missid_a2, missid_n2)
            self.missid_MSd1 = RooCBShape("missid_MSd"+ "_"+ i,"missid_MSd"+ "_"+ i, Mass, missid_mean1, missid_sigma, missid_a3, missid_n)
            self.missid_MSu2 = RooCBShape("missid_MSu2"+ "_"+ i,"missid_MSu2"+ "_"+ i, Mass, missid_mean2, missid_sigma2, missid_a2b, missid_n2b)
            self.missid_MSd2 = RooCBShape("missid_MSd2"+ "_"+ i,"missid_MSd2"+ "_"+ i, Mass, missid_mean2, missid_sigma2, missid_a3b, missid_nb)

            self.missid_MSu3 = RooCBShape("missid_MSu3"+ "_"+ i,"missid_MSu3"+ "_"+ i, Mass, missid_mean3, missid_sigma3, missid_a2c, missid_n2c)
            self.missid_MSd3 = RooCBShape("missid_MSd3"+ "_"+ i,"missid_MSd3"+ "_"+ i, Mass, missid_mean3, missid_sigma3, missid_a3c, missid_nc)
            self.missid_MS1 = RooAddPdf("missid_MS1"+ "_"+ i,"missid_MS1"+ "_"+ i,self.missid_MSu1,self.missid_MSd1,hh_f05)
            self.missid_MS2 = RooAddPdf("missid_MS2"+ "_"+ i,"missid_MS2"+ "_"+ i,self.missid_MSu2,self.missid_MSd2,hh_f05)
            self.missid_MS3 = RooAddPdf("missid_MS3"+ "_"+ i,"missid_MS3"+ "_"+ i,self.missid_MSu3,self.missid_MSd3,hh_f05)

            self.missid_sig0  = RooAddPdf("missid_Sigmodel0" + i,"missid_Sigmodel0"+i, self.missid_MS1, self.missid_MS2, missid_f1)
            self.missid_peak  = RooAddPdf("missid" + i ,"missid"+i, self.missid_sig0, self.missid_MS3, missid_f2)
            model_components.add(self.missid_peak)


        if opts.get('ADD_B0PIMUNU'):
            print  prefix + '    o) Define the exclusive background: PiMuNu'
            #self.nPiMuNu = RooFormulaVar("N_B0pimunu" + i, "N_B0pimunu" + i,"PiMuNu"+i + "*PiMuNu",RooArgList(v["PiMuNu"+i],v["PiMuNu"]))
            self.nPiMuNu = RooFormulaVar("N_B0pimunu" + i, "N_B0pimunu" + i,"(@0*@1)",RooArgList(f_PiMuNu[glbin-1],v["PiMuNu"]))
            self.PiMuNu = RooPhysBkg("B0pimunu" + i, "pdf B0pimunu "+ i, Mass, v["meanPiMuNu"+i],v["coPiMuNu"+i],v["sigmaPiMuNu"+i])
            model_yields.add(self.nPiMuNu)
            model_components.add(self.PiMuNu)

        if opts.get('ADD_B0UPIMUMU'):
            print  prefix + '    o) Define the exclusive background: PiMuMu'
	    #self.nPiMuMu = RooFormulaVar("N_B0upimumu" + i, "N_B0upimumu" + i,"PiMuMu"+i + "*PiMuMu",RooArgList(v["PiMuMu"+i],v["PiMuMu"]))
            self.nPiMuMu = RooFormulaVar("N_B0upimumu" + i, "N_B0upimumu" + i,"(@0*@1)",RooArgList(f_PiMuMu[glbin-1],v["PiMuMu"]))
	    self.PiMuMu = RooPhysBkg("B0upimumu" + i, "pdf B0upimumu "+ i, Mass, v["meanPiMuMu"+i],v["coPiMuMu"+i],v["sigmaPiMuMu"+i])
            model_yields.add(self.nPiMuMu)
            model_components.add(self.PiMuMu)

        if opts.get('ADD_LAPMUNU'):
            print  prefix + '    o) Define the exclusive background: LaPMuNu'
            #self.nLaPMuNu = RooFormulaVar("N_Lapmunu" + i, "N_Lapmunu" + i,"LaPMuNu"+i + "*LaPMuNu",RooArgList(v["LaPMuNu"+i],v["LaPMuNu"]))
            self.nLaPMuNu = RooFormulaVar("N_Lapmunu" + i, "N_Lapmunu" + i,"(@0*@1)",RooArgList(f_LaPMuNu[glbin-1],v["LaPMuNu"]))
            self.LaPMuNu = RooPhysBkg("Lapmunu" + i, "pdf Lapmunu "+ i, Mass, v["meanLaPMuNu"+i],v["coLaPMuNu"+i],v["sigmaLaPMuNu"+i])
            model_yields.add(self.nLaPMuNu)
            model_components.add(self.LaPMuNu)

        print prefix + ' o) Put everything together..'
        self.model = RooAddPdf("mumu model " + i, "mumu model " + i, model_components, model_yields)
        self.model.Print('v')
        self.model.Print()
        print prefix + '  Model built! '

############################################
print '     MODEL:  -> Done! \n'
print '     MODEL:  o) Building models for every BDT bin... \n'
fiter = RooSimultaneous("fitter", "fitter", cat)
mm = {}
for i in range(1+opts.get('USE_7_BINS'),9):
    mm[i] = BsMuMuModel(i)
    fiter.addPdf(mm[i].model,"mumu bin" + str(i))

############################################ Bs --> mm
print ' -----------------------------------------------------------------------------  \n  '
print '     MODEL has been built \n'
fiter.Print('v')
fiter.Print()
print ' -----------------------------------------------------------------------------  \n  '
print '     o) Link the BDT Bin models to the BDT categories...\n'

if not opts.get('USE_7_BINS'): mumuDataLG = RooDataSet("mumu data Low GL", "mumu data Low GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin1", BDT_data[1]), RooFit.Import("mumu bin2", BDT_data[2]), RooFit.Import("mumu bin3", BDT_data[3]),RooFit.Import("mumu bin4", BDT_data[4]))

else: mumuDataLG = RooDataSet("mumu data Low GL", "mumu data Low GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin2", BDT_data[2]), RooFit.Import("mumu bin3", BDT_data[3]),RooFit.Import("mumu bin4", BDT_data[4]))
mumuDataHG = RooDataSet("mumu data High GL", "mumu data High GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin5", BDT_data[5]), RooFit.Import("mumu bin6", BDT_data[6]), RooFit.Import("mumu bin7", BDT_data[7]),RooFit.Import("mumu bin8", BDT_data[8]))

allData = mumuDataLG.Clone() #RooDataSet("all data","all data", RooArgSet(Mass,cat), RooFit.Import(hhData), RooFit.Import(mumuData))
allData.append(mumuDataHG)

print '  -> Done! \n'
print '     o) Add the onstraints to the model...\n'

print '         Constrain: Total MisID Yield'
summaryConstraints = RooArgSet(nmis_cons)

print '         Constrain: Time Acceptance Corrections'
summaryConstraints.add(RooArgSet(timeAccCorrBs_cons, timeAccCorrBd_cons))

print '         Constrain: Normalization parameters'
if opts.get('ADD_ALPHA_CONST'):
    summaryConstraints.add(RooArgSet(alpha_Bu_cons, alpha_KPi_cons))

if opts.get('ADD_FDFS_CONST'):
    summaryConstraints.add(RooArgSet(fdfs_cons))

print '         Constrain: Signal mass shape parameters'
summaryConstraints.add(RooArgSet(sigmaBs_cons ,sigmaBd_cons,meanBd_cons,meanBs_cons, a_cons, n_cons))

print '         Constrain: Signal BDT fractions'
#summaryConstraints.add(RooArgSet(BDT_f2_cons, BDT_f3_cons, BDT_f4_cons, BDT_f5_cons, BDT_f6_cons, BDT_f7_cons, BDT_f8_cons))
summaryConstraints.add(RooArgSet(BDT_f1_cons, BDT_f2_cons, BDT_f3_cons, BDT_f4_cons, BDT_f5_cons, BDT_f6_cons, BDT_f7_cons, BDT_f8_cons))


if opts.get('ADD_B0PIMUNU_CONST'):
    print '         Constrain: PiMuNu shape parameters'
    summaryConstraints.add(RooArgSet(sigmaPiMuNu1_cons,sigmaPiMuNu2_cons,sigmaPiMuNu3_cons,sigmaPiMuNu4_cons,sigmaPiMuNu5_cons,sigmaPiMuNu6_cons,sigmaPiMuNu7_cons, sigmaPiMuNu8_cons))
    summaryConstraints.add(RooArgSet(meanPiMuNu1_cons,meanPiMuNu2_cons,meanPiMuNu3_cons,meanPiMuNu4_cons,meanPiMuNu5_cons,meanPiMuNu6_cons,meanPiMuNu7_cons, meanPiMuNu8_cons))
    summaryConstraints.add(RooArgSet(coPiMuNu1_cons,coPiMuNu2_cons,coPiMuNu3_cons,coPiMuNu4_cons,coPiMuNu5_cons,coPiMuNu6_cons,coPiMuNu7_cons, coPiMuNu8_cons))
    summaryConstraints.add(RooArgSet(PiMuNu1_cons,PiMuNu2_cons,PiMuNu3_cons,PiMuNu4_cons,PiMuNu5_cons,PiMuNu6_cons,PiMuNu7_cons, PiMuNu8_cons, PiMuNu_cons))
    #summaryConstraints.add(RooArgSet(PiMuNu2_cons,PiMuNu3_cons,PiMuNu4_cons,PiMuNu5_cons,PiMuNu6_cons,PiMuNu7_cons, PiMuNu8_cons, PiMuNu_cons))

if opts.get('ADD_B0UPIMUMU_CONST'):
    print '         Constrain: PiMuMu shape parameters'
    summaryConstraints.add(RooArgSet(sigmaPiMuMu1_cons,sigmaPiMuMu2_cons,sigmaPiMuMu3_cons,sigmaPiMuMu4_cons,sigmaPiMuMu5_cons,sigmaPiMuMu6_cons,sigmaPiMuMu7_cons, sigmaPiMuMu8_cons))
    summaryConstraints.add(RooArgSet(meanPiMuMu1_cons,meanPiMuMu2_cons,meanPiMuMu3_cons,meanPiMuMu4_cons,meanPiMuMu5_cons,meanPiMuMu6_cons,meanPiMuMu7_cons, meanPiMuMu8_cons))
    summaryConstraints.add(RooArgSet(coPiMuMu1_cons,coPiMuMu2_cons,coPiMuMu3_cons,coPiMuMu4_cons,coPiMuMu5_cons,coPiMuMu6_cons,coPiMuMu7_cons, coPiMuMu8_cons))
    summaryConstraints.add(RooArgSet(PiMuMu1_cons,PiMuMu2_cons,PiMuMu3_cons,PiMuMu4_cons,PiMuMu5_cons,PiMuMu6_cons,PiMuMu7_cons, PiMuMu8_cons, PiMuMu_cons))
    #summaryConstraints.add(RooArgSet(PiMuMu2_cons,PiMuMu3_cons,PiMuMu4_cons,PiMuMu5_cons,PiMuMu6_cons,PiMuMu7_cons, PiMuMu8_cons, PiMuMu_cons))

if opts.get('ADD_LAPMUNU_CONST'):
    print '         Constrain: LaPMuNu shape parameters'
    summaryConstraints.add(RooArgSet(sigmaLaPMuNu1_cons,sigmaLaPMuNu2_cons,sigmaLaPMuNu3_cons,sigmaLaPMuNu4_cons,sigmaLaPMuNu5_cons,sigmaLaPMuNu6_cons,sigmaLaPMuNu7_cons, sigmaLaPMuNu8_cons))
    summaryConstraints.add(RooArgSet(meanLaPMuNu1_cons,meanLaPMuNu2_cons,meanLaPMuNu3_cons,meanLaPMuNu4_cons,meanLaPMuNu5_cons,meanLaPMuNu6_cons,meanLaPMuNu7_cons, meanLaPMuNu8_cons))
    summaryConstraints.add(RooArgSet(coLaPMuNu1_cons,coLaPMuNu2_cons,coLaPMuNu3_cons,coLaPMuNu4_cons,coLaPMuNu5_cons,coLaPMuNu6_cons,coLaPMuNu7_cons, coLaPMuNu8_cons))
    summaryConstraints.add(RooArgSet(LaPMuNu1_cons,LaPMuNu2_cons,LaPMuNu3_cons,LaPMuNu4_cons,LaPMuNu5_cons,LaPMuNu6_cons,LaPMuNu7_cons, LaPMuNu8_cons, LaPMuNu_cons))
    #summaryConstraints.add(RooArgSet(LaPMuNu2_cons,LaPMuNu3_cons,LaPMuNu4_cons,LaPMuNu5_cons,LaPMuNu6_cons,LaPMuNu7_cons, LaPMuNu8_cons, LaPMuNu_cons))

print '  -> Done! \n'

print '     o) Fix the following parameters......\n'

#Get all the parameters
params = fiter.getParameters(allData)

#Fix everything
if opts.get('FIXFITMODEL'):
    print '  --------------------------------'
    print '     Fix the fit parameters ......\n'
    paramsIT = params.createIterator()
    p = paramsIT.Next()
    while p:
        p.setConstant()
        print '     Fixed:', p.GetName()
        print '     @ ', p.getVal()
        p = paramsIT.Next()
    print '  --------------------------------'


#Fix only specific parameters
fixParams = []

if opts.get('FIX_B0PIMUNU'):
    print '        Fix: PiMuNu shape parameters'
    fixParams += ['sigmaPiMuNu1','sigmaPiMuNu2','sigmaPiMuNu3','sigmaPiMuNu4','sigmaPiMuNu5','sigmaPiMuNu6','sigmaPiMuNu7', 'sigmaPiMuNu8']
    fixParams += ['meanPiMuNu1','meanPiMuNu2','meanPiMuNu3','meanPiMuNu4','meanPiMuNu5','meanPiMuNu6','meanPiMuNu7','meanPiMuNu8']
    fixParams += ['coPiMuNu1','coPiMuNu2','coPiMuNu3','coPiMuNu4','coPiMuNu5','coPiMuNu6','coPiMuNu7','coPiMuNu8']
    #fixParams += ['PiMuNu1','PiMuNu2','PiMuNu3','PiMuNu4','PiMuNu5','PiMuNu6','PiMuNu7','PiMuNu8','PiMuNu']
    fixParams += ['PiMuNu2','PiMuNu3','PiMuNu4','PiMuNu5','PiMuNu6','PiMuNu7','PiMuNu8','PiMuNu']

if opts.get('FIX_B0UPIMUMU'):
    print '        Fix: PiMuMu shape parameters'
    fixParams += ['sigmaPiMuMu1','sigmaPiMuMu2','sigmaPiMuMu3','sigmaPiMuMu4','sigmaPiMuMu5','sigmaPiMuMu6','sigmaPiMuMu7', 'sigmaPiMuMu8']
    fixParams += ['meanPiMuMu1','meanPiMuMu2','meanPiMuMu3','meanPiMuMu4','meanPiMuMu5','meanPiMuMu6','meanPiMuMu7','meanPiMuMu8']
    fixParams += ['coPiMuMu1','coPiMuMu2','coPiMuMu3','coPiMuMu4','coPiMuMu5','coPiMuMu6','coPiMuMu7','coPiMuMu8']
    #fixParams += ['PiMuMu1','PiMuMu2','PiMuMu3','PiMuMu4','PiMuMu5','PiMuMu6','PiMuMu7','PiMuMu8','PiMuMu']
    fixParams += ['PiMuMu2','PiMuMu3','PiMuMu4','PiMuMu5','PiMuMu6','PiMuMu7','PiMuMu8','PiMuMu']

if opts.get('FIX_LAPMUNU'):
    print '        Fix: LaPMuNu shape parameters'
    fixParams += ['sigmaLaPMuNu1','sigmaLaPMuNu2','sigmaLaPMuNu3','sigmaLaPMuNu4','sigmaLaPMuNu5','sigmaLaPMuNu6','sigmaLaPMuNu7', 'sigmaLaPMuNu8']
    fixParams += ['meanLaPMuNu1','meanLaPMuNu2','meanLaPMuNu3','meanLaPMuNu4','meanLaPMuNu5','meanLaPMuNu6','meanLaPMuNu7','meanLaPMuNu8']
    fixParams += ['coLaPMuNu1','coLaPMuNu2','coLaPMuNu3','coLaPMuNu4','coLaPMuNu5','coLaPMuNu6','coLaPMuNu7','coLaPMuNu8']
    #fixParams += ['LaPMuNu1','LaPMuNu2','LaPMuNu3','LaPMuNu4','LaPMuNu5','LaPMuNu6','LaPMuNu7','LaPMuNu8','LaPMuNu']
    fixParams += ['LaPMuNu2','LaPMuNu3','LaPMuNu4','LaPMuNu5','LaPMuNu6','LaPMuNu7','LaPMuNu8','LaPMuNu']

if opts.get('FIX_ALPHAS'):
    fixParams += ['alpha_Bu','alpha_KPi']

if opts.get('FIX_FDFS'):
    fixParams += ['fdfs']

if opts.get('FIX_BRs'):
    BR_s.setVal(0.)
    fixParams += ['BRs']

if opts.get('FIX_BRd'):
    BR_d.setVal(0.)
    fixParams += ['BRd']


    print '  --------------------------------'
for pname in fixParams:
    p = params[pname]
    p.setConstant()
    print '     Fixed:', p.GetName()
    print '     @ ', p.getVal()
    print '  --------------------------------'


print '     o) Call the fit function......\n'

if opts.get('PRINT_MODEL'):
	fiter.printCompactTree('v')
	raw_input('Continue...?')

#Do the fitting
if not opts.get('FIXFITMODEL'):

    #fiter.fitTo(allData,RooFit.Minos(kTRUE), RooFit.ExternalConstraints(RooArgSet(summaryConstraints)),RooFit.Strategy(2), RooFit.NumCPU(8), RooFit.Verbose(kTRUE), RooFit.Offset(True))
    #fiter.fitTo(allData,RooFit.Minos(kTRUE), RooFit.ExternalConstraints(RooArgSet(summaryConstraints)),RooFit.Strategy(2), RooFit.NumCPU(8), RooFit.Verbose(kTRUE), RooFit.Offset(False)) # ok!
    fiter.fitTo(allData,RooFit.Minos(kTRUE), RooFit.ExternalConstraints(RooArgSet(summaryConstraints)),RooFit.Strategy(2), RooFit.NumCPU(8), RooFit.Verbose(kTRUE), RooFit.Offset(False), RooFit.Hesse(1), RooFit.Minos(RooArgSet(BR_s,BR_d))) #Like CMS

print '  -> FIT HAS CONVERGED! \n'

#####################################################################################
# Write a summary of the fit configuration to a file
fileName = opts.get('RESULTDIR')+'FitSummary.txt'
f = open(fileName,'w')
print >> f, '#----------------------------------------#'
print >> f, '  This is the configuration for the fit:'

for name, val in opts.items():
    print >> f, '  o) '+str(name)+' : '+str(val)
print >> f, '#----------------------------------------#'
print >> f, ' BRs = ', BR_s.getVal(), ' +- ', BR_s.getError()
print >> f, ' BRd = ', BR_d.getVal(), ' +- ', BR_d.getError()
print >> f, ' alpha_d = ', alpha_d.getVal()#, ' +- ', alpha_d.getError()
print >> f, ' alpha_s = ', alpha_s.getVal()#, ' +- ', alpha_s.getError()
print >> f, '#----------------------------------------#'


f.close()
content =  open(fileName).read()
print content
#####################################################################################


if opts.get('FITANDPLOT'):
    print ' o) Save the fitted parameters to a file..'
    fiter.getParameters(allData).writeToFile(opts.get('RESULTDIR')+'FitModel_PARAMETERS.txt')

    print '  -> Done! \n'
    print '     o) Plot the fit in evety BDT bin...\n'

    c = TCanvas()
    c.Divide(4,2)
    fr = {}
    binning = 10
    size = (Mass.getMax()-Mass.getMin())*1./binning
    for i in range(1+opts.get('USE_7_BINS'),9):
     print ' -------------------- '
     print '  Plotting BDT bin:',i
     print ' -------------------- '

     c.cd(i)
     fr[i] = Mass.frame()
     BDT_data[i].plotOn(fr[i], RooFit.Binning(binning))
     mm[i].model.plotOn(fr[i])#
     mm[i].model.plotOn(fr[i])#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
     mm[i].model.plotOn(fr[i], RooFit.Components("model Bs"+str(i)),RooFit.LineColor(kRed),RooFit.LineStyle(9))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
     mm[i].model.plotOn(fr[i], RooFit.Components("model Bd"+str(i)),RooFit.LineColor(kGreen),RooFit.LineStyle(7))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
     mm[i].model.plotOn(fr[i], RooFit.Components("missid"+str(i)),RooFit.LineColor(kMagenta),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
     if opts.get('ADD_B0PIMUNU'):
        mm[i].model.plotOn(fr[i], RooFit.Components("B0pimunu"+str(i)),RooFit.LineColor(kBlack),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
     if opts.get('ADD_B0UPIMUMU'):
        mm[i].model.plotOn(fr[i], RooFit.Components("B0upimumu"+str(i)),RooFit.LineColor(kCyan),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
     if opts.get('ADD_LAPMUNU'):
        mm[i].model.plotOn(fr[i], RooFit.Components("Lapmunu"+str(i)),RooFit.LineColor(kOrange),RooFit.LineStyle(kDotted))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))

     fr[i].GetXaxis().SetTitle("m_{#mu#mu} ( MeV/c^{2} )")
     fr[i].SetTitle("B_{s}^{0}#rightarrow#mu^{+}#mu^{-} candidates, BIN [" + str(Binning[opts.get('bdtname')][i-1]) + ", " +str(Binning[opts.get('bdtname')][i])+"]" )

     fr[i].GetYaxis().SetTitle("Events /( "+str(int(size))+" MeV/c^{2} )")
     fr[i].GetYaxis().SetTitleOffset(1.4)
     #else: fr[i].GetYaxis().SetTitleOffset(1.6)
     fr[i].Draw()

    c.SaveAs(opts.get('RESULTDIR')+'MassFitInBDTBins.ps')
    c.SaveAs(opts.get('RESULTDIR')+'MassFitInBDTBins.root')

    print '  -> Done! \n'


if opts.get('PROFILELIKELIHOOD'):
    c = TCanvas()

    print '  ----------------------------------------------'
    print '  Create a profile likelihood scan plot for BRs'
    print '  ----------------------------------------------'

    print ' o) Construct unbinned likelihood'
    nll = fiter.createNLL(allData,RooFit.NumCPU(8),RooFit.ExternalConstraints(RooArgSet(summaryConstraints)))

    print ' o)  Minimize likelihood wrt all parameters'
    #nll.migrad()
    #nll.hesse()
    #nll.minos()
    RooMinuit(nll).minos()

    print ' o)  Plot likelihood scan of BR_s'
    fr = BR_s.frame(RooFit.Title("LL of BR(B_{s}^{0}#rightarrow #mu^{+}#mu^{-})"),RooFit.Range(-0.5,10))
    nll.plotOn(fr,RooFit.ShiftToZero())
    fr.Draw()
    c.SaveAs(opts.get('RESULTDIR')+'LikelihoodScan_BRs.ps')
    c.SaveAs(opts.get('RESULTDIR')+'LikelihoodScan_BRs.root')

    print ' o)  Construct profile likelihood for BR_s'
    pl_Bs = nll.createProfile(RooArgSet(BR_s))

    print ' o)  Plot profile likelihood in BR_s'
    fr = BR_s.frame(RooFit.Title("Profile LL of BR(B_{s}^{0}#rightarrow #mu^{+}#mu^{-})"),RooFit.Range(-0.5,10))
    pl_Bs.plotOn(fr,RooFit.ShiftToZero())
    fr.Draw()
    c.SaveAs(opts.get('RESULTDIR')+'ProfileLikelihood_BRs.ps')
    c.SaveAs(opts.get('RESULTDIR')+'ProfileLikelihood_BRs.root')

print ' The fractions oer bin:'
for i in range(0,8):
	print ' o) Bin:',i+1	
	print '		f_bs:', f_bs[i].getVal()
	print '		f_bd:', f_bd[i].getVal()


## c.cd(4)
## fr4 = Mass.frame()
## BDT_data[4].plotOn(fr4, RooFit.Binning(10))#, RooFit.Cut("Bmass<4"))
## mm4.model.plotOn(fr4)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## mm4.model.plotOn(fr4, RooFit.Components("model Bs4"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## mm4.model.plotOn(fr4, RooFit.Components("model Bd4"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## mm4.model.plotOn(fr4, RooFit.Components("missid4"),RooFit.LineColor(kMagenta))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## fr4.Draw()

##############################


## c2.cd(4)
## hfr4 = Mass.frame()
## datahh4.plotOn(hfr4)#, RooFit.Cut("Bmass<4"))
## hh4.model.plotOn(hfr4)#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## hh4.model.plotOn(hfr4, RooFit.Components("Sigmodel4"),RooFit.LineColor(kRed))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## hh4.model.plotOn(hfr3, RooFit.Components("shoulder4"),RooFit.LineColor(kGreen))#, RooFit.Slice(cat, "mumu bin1"), RooFit.ProjWData(allData))
## hfr4.Draw()


## #### inspired on Francesco code
## wsp = RooWorkspace("workspace","workspace")
## modelConfig = RooStats.ModelConfig("my_problem",wsp)
## modelConfig.SetPdf(fiter)
## modelConfig.SetParametersOfInterest(RooArgSet(BR_s))
## modelConfig.SetObservables(RooArgSet(Mass,cat))
## #modelConfig.SetObservables(RooArgSet(opts.get('massname'),samplename))#
## modelConfig.SetConstraintParameters(summaryConstraints)

## fc = RooStats.FeldmanCousins(allData,modelConfig)


## fc.SetTestSize(0.31731050786291404)#0.05)
## fc.UseAdaptiveSampling(kTRUE)
## fc.SetNBins(100)
## #fc.GetInterval()

## ## wsp = RooWorkspace("workspace","workspace")
## ## modelConfig = RooStats.ModelConfig("my_problem",wsp)
## ## modelConfig.SetPdf(mm[8].model)
## ## modelConfig.SetParametersOfInterest(RooArgSet(nbs))
## ## modelConfig.SetObservables(RooArgSet(opts.get('massname')))
## ## modelConfig.SetConstraintParameters(summaryConstraints)

## ## fc = RooStats.FeldmanCousins(BDT_data[8],modelConfig)
## #interval = fc.GetInterval()

## mcstudy = RooMCStudy(fiter,RooArgSet(Mass,cat),RooFit.Silence(), RooFit.FitOptions(RooFit.Save(kTRUE),RooFit.PrintEvalErrors(0), RooFit.ExternalConstraints(RooArgSet(summaryConstraints)),RooFit.Minos(kTRUE)),RooFit.Extended())

## mcstudy = RooMCStudy(fiter,RooArgSet(Mass,cat),RooFit.Silence(), RooFit.FitOptions(RooFit.Save(kTRUE),RooFit.PrintEvalErrors(0),RooFit.Minos(kTRUE)),RooFit.Extended())
## #mcstudy.generateAndFit(1000)





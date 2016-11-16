from ROOT import *

# The list of different toytables:
#n -rw-r--r--. 1 stolk z5  7836 Jul  6 00:55 toytable_BDTpaper_spring13_2011.py
# -rw-r--r--. 1 stolk z5  7848 Jul  6 00:55 toytable_BDTpaper_spring13_2012.py
# -rw-r--r--. 1 stolk z5  7396 Jul  6 00:55 toytable_summer13_7bins.py
# -rw-r--r--. 1 stolk z5  7779 Jul  6 00:55 toytable_summer13.py
# -rw-r--r--. 1 stolk z5  7775 Jul  6 00:55 toytable_summer13_scaled2.py

#from Bs2MuMuParams import toytable_summer13 as TheTable #Does not wok yet, needs to be compiled I guess
#import toytable_summer13 as TheTable #Copied the table
#import toytable_summer13_Ale8Jul as TheTable #Alessio's table, has proper exc. bkg shape parameters
#import toytable_summer13_kmnuSys as TheTable # New rable from Ale for the combination, includes the KMuNu
#import toytable_autumn13 as TheTable # New rable from Marco and Francesco 15 Nov 2013
#import toytable_autumn13_DecFra as TheTable # New new table with fixxes from Fra 11. Dec
#import toytable_autumn13_161213 as TheTable # New new table with fixxes from Fra 16 Dec
import toytable_autumn13 as TheTable # New new table with fixxes from Fra 16 Dec


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

#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_Plot_GCC48_WithOffset_FULL_KMUNUFracFree/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_Plot_GCC48_NoOffset_FULL_AllConstrained/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_Plot_GCC48_R53410_NoOffset/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_Plot_GCC48_R53414_NoOffset/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_Plot_GCC48_R53410_NoOffset_CPU1/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_Plot_GCC48_R53410_CPU1/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_Plot_GCC48_R53410_NoOffset_Optimize0/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_Plot_GCC48_R53410_NoOffset_Optimize0_CPU8/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_Plot_GCC48_R53410_WithOffset_Optimize0_CPU8/'

#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_Plot_GCC48_WithOffset_FULL_NoOffset/'

#The significance fits

#With offset
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_GCC48_ROOR53410_WithOffset_BRs_free_BRd_free/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_GCC48_ROOR53410_WithOffset_BRs_FIXto0_BRd_free/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_GCC48_ROOR53410_WithOffset_BRs_free_BRd_FIXto0/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_GCC48_ROOR53410_WithOffset_BRs_FIXto0_BRd_FIXto0/'


#Without offset
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_GCC48_ROOR53410_NoOffset_BRs_free_BRd_free/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_GCC48_ROOR53410_NoOffset_BRs_FIXto0_BRd_free/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_GCC48_ROOR53410_NoOffset_BRs_free_BRd_FIXto0/'
#opts['RESULTDIR'] = 'Profile_Results/2013_LHCb_Final_GCC48_ROOR53410_NoOffset_BRs_FIXto0_BRd_FIXto0/'

#Save the workspace
opts['RESULTDIR'] = 'Profile_Results/2014_LHCb_Workspace/'


#Turns out Ale+Fla fix the RooPhysBkg shape parameters(mean,sigma,shc) in their fit
#Let's try what I get with that
#opts['RESULTDIR'] = 'Profile_Results/2014_LHCb_Workspace_RooPhysBkgShapesFixed/'
#opts['RESULTDIR'] = 'Profile_Results/2014_LHCb_Workspace_RooPhysBkgShapesFixed_BRs_Free_BRd_Free_R53414/'
#opts['RESULTDIR'] = 'Profile_Results/2014_LHCb_Workspace_RooPhysBkgShapesFixed_BRs_Free_BRd_Free/'
#opts['RESULTDIR'] = 'Profile_Results/2014_LHCb_Workspace_RooPhysBkgShapesFixed_BRs_FIXto0_BRd_Free/'
#opts['RESULTDIR'] = 'Profile_Results/2014_LHCb_Workspace_RooPhysBkgShapesFixed_BRs_Free_BRd_FIXto0/'
#opts['RESULTDIR'] = 'Profile_Results/2014_LHCb_Workspace_RooPhysBkgShapesFixed_BRs_FIXto0_BRd_FIXto0/'

#####################################################################################
# Helper function for the configuration part
# Let user define some of the variables interactively
def askUser(optionName):
    #Ask a user for 1 or 0 and return it
    answer = -1
    askUser = True
    while askUser:
        try:
                answer = int(raw_input( '  o) Set '+optionName+' 1 or 0?'))
        except ValueError:
                print "...give a number (1 or 0), please."
                continue
        if answer == 1 or answer ==0: askUser = False
        else: print "...give 1 or 0, please."

    print ' => '+optionName+' is set to : ', answer

    return answer
#####################################################################################
#Test which fit are you running and were are you saving the results
print 'Saving the results to:'
print opts.get('RESULTDIR')

if 'REDEFINE' in raw_input('All good? (To redefine the dir type REDEFINE)'):
    opts['RESULTDIR'] = raw_input('dirname = ')

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
opts['FIT_MODEL']= 0
opts['PRINT_MODEL']= 0
opts['PLOT_HIGH_BDT_BINS'] = 0
opts['PLOT_ALL_BDT_BINS'] = 0
#-------------#

#####################################################################################
RooFit.gErrorIgnoreLevel = kError
RooMsgService.instance().setGlobalKillBelow(RooFit.ERROR)
opts['massname']= 'B_s0_MM'
opts['bdtname'] = 'BDT12flat'

opts['SAVE_WORKSPACE'] = 0#askUser('SAVE_WORKSPACE')
opts['LOAD_PARAMS_FROM'] = 0 #Set the starting parameters from this file
#opts['LOAD_PARAMS_FROM'] = opts.get('RESULTDIR')+str('loadParams.txt')

opts['SAVE_FIT_PARAMS'] = 1
opts['SAVE_START_PARAMS'] = 1

opts['FIT_WITH_OFFSET'] = 1#askUser('FIT_WITH_OFFSET')
opts['FIT_WITH_CPU_8'] = 0#askUser('FIT_WITH_CPU_8')
opts['FIT_WITH_OPTIMIZE'] = 1#askUser('FIT_WITH_OPTIMIZE')

opts['ADD_SIGSHAPE_CONST'] = 1
opts['ADD_TIMEACCCORR_CONST'] = 1
opts['ADD_BDT_FRAC_CONST'] = 1

opts['INCLUDE_BD']= 1
opts['FIX_BRd' ]= 0#askUser('FIX_BRd')
opts['FIX_BRs' ]= 0#askUser('FIX_BRs')

opts['FIX_ALPHAS' ]= 0  ### Normalization factor 
opts['ADD_ALPHA_CONST']= 1 ### set the constraint

opts['FIX_FDFS']= 0
opts['ADD_FDFS_CONST']= 1

opts['FIX_BDKPI_BF'] = 0
opts['ADD_BDKPI_BF_CONST'] = 1

opts['FIX_BUJPSIK_BF'] = 0
opts['ADD_BUJPSIK_BF_CONST'] = 1

opts['FIX_BKGNORM'] = 0
opts['ADD_BKGNORM_CONST'] = 1 ## This refers to nromalization of the pp bb
#Configure peaking background components
#RooPhysBkg shape in every bin
opts['USE_ROOKEYS_MISID']= 1
opts['ADD_MISID_NTOT_CONST'] = 1 ## NTOT : number of total B->hh

#B->Pi/K MuNu
opts['ADD_B2XMUNU']= 1
opts['FIX_B2XMUNU']= 0 #all

opts['FIX_PIMUNU_EFF_BR'] = 0
opts['FIX_PIMUNU_FRAC'] = 0

opts['FIX_PIMUNU_MEAN'] = 1
opts['FIX_PIMUNU_SIGMA'] = 1
opts['FIX_PIMUNU_SHC'] = 1
opts['ADD_B2XMUNU_SHAPE_CONST']= 0

#same shape as PiMuNu opts['FIX_KMUNU_EFF_BR'] = 0
opts['FIX_KMUNU_FRAC'] = 0
# KMUNUFRAC# need to be fixed, as the KMUNU does not have a separate pdf,
#but is added to PIMUNU. Othervise ambiguity rises int he TOT XMUNU yeid.
opts['ADD_B2XMUNU_YIELD_CONST']= 1

#B0->PiMuMu
opts['ADD_B0UPIMUMU'] = 1 ### wtf?
opts['FIX_B0UPIMUMU'] = 0 #all

opts['FIX_B0UPIMUMU_EFF_BR'] = 0
opts['FIX_B0UPIMUMU_FRAC'] = 0

opts['FIX_B0UPIMUMU_MEAN'] = 1
opts['FIX_B0UPIMUMU_SIGMA'] = 1
opts['FIX_B0UPIMUMU_SHC'] = 1
opts['ADD_B0UPIMUMU_SHAPE_CONST' ]= 0

opts['ADD_B0UPIMUMU_YIELD_CONST' ]= 1

#La->pMuNU
opts['ADD_LAPMUNU' ]= 1
opts['FIX_LAPMUNU' ]= 0 #all

opts['FIX_LAPMUNU_EFF_BR'] = 0
opts['FIX_LAPMUNU_FRAC'] = 0

opts['FIX_LAPMUNU_MEAN'] = 1
opts['FIX_LAPMUNU_SIGMA'] = 1
opts['FIX_LAPMUNU_SHC'] = 1
opts['ADD_LAPMUNU_SHAPE_CONST' ]= 0

opts['ADD_LAPMUNU_YIELD_CONST' ]= 1

opts['UNIFORM_KAPPA'] = 0 #same slope everywhere
opts['DOUBLE_EXPO']= 0
opts['BIND_SLOPES_IN_LAST_2_BINS']= 1 #Use the same slope in bin 8 and 7
opts['USE_7_BINS'] = 0  ## Get rid of the 1st BDT bin bcs has no sensitivity.

#BDT_DEN = 1.76201e+04
#BDT_PDF = {"2":5.33030e+02*1./BDT_DEN, "3":1.26436e+02*1./BDT_DEN, "4":4.53571e+01*1./BDT_DEN, "5":3.15557e+01*1./BDT_DEN,"6":7.38383e+00*1./BDT_DEN, "7":9.30460e+00*1./BDT_DEN, "8": 1.97407e+00*1./BDT_DEN}

if opts.get('DOUBLE_EXPO'): Mass = RooRealVar(opts.get('massname'),opts.get('massname'),4170, 6565)
#else: Mass = RooRealVar(opts.get('massname'),opts.get('massname'),5432.96 - 120,6000)#4900, 6000)
else: Mass = RooRealVar(opts.get('massname'),opts.get('massname'),4900, 6000)

# --------------------------------------------------------------------------------- #
# A)  Introducing the BDT variable and the bins, importing RooDataSets
# --------------------------------------------------------------------------------- #

print ' o) Build the BDT cuts for every bin...'
samplename = opts.get('bdtname')+'_cat'
Binning = {}
Binning[opts.get('bdtname')] = [0, .25,.4,.5,.6,.7,.8,.9,1.]
BDT = BDT_cuts(opts.get('bdtname'), Binning)

print ' o) Define the BDT categories...'
cat =  RooCategory(samplename, samplename)
for i in range(1,9): cat.defineType("mumu bin" + str(i))

print ' o) Define the fiducial cuts...'
fiducial = opts.get('bdtname') + '!= 0.' # no 0 BDT events  ### Separate file, or in the parameters Table
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
print ' -. The datasets (BDT_data[]) have been imported and BDT categories created'
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


print '     MODEL:  . Done! \n'
print '     MODEL:   o) Import the double MisID hh.mumu yield...'
nmis,nmis_m,nmis_s, nmis_cons = createConst(TheTable.MisIDTotYield,TheTable.MisIDTotYieldErr, "Nmis")
print '     MODEL:  . Done! \n'
print '     MODEL:   o) Import the misid phase space(.BDT) dependence correction factors...'

mid_idf = [TheTable.MisIDfBDTBin1,TheTable.MisIDfBDTBin2,TheTable.MisIDfBDTBin3,TheTable.MisIDfBDTBin4,TheTable.MisIDfBDTBin5,TheTable.MisIDfBDTBin6,TheTable.MisIDfBDTBin7,TheTable.MisIDfBDTBin8]
missid_corr1 = RooRealVar("missid_corr1","missid_corr1",mid_idf[0])
missid_corr2 = RooRealVar("missid_corr2","missid_corr2",mid_idf[1])
missid_corr3 = RooRealVar("missid_corr3","missid_corr3",mid_idf[2])
missid_corr4 = RooRealVar("missid_corr4","missid_corr4",mid_idf[3])

missid_corr5 = RooRealVar("missid_corr5","missid_corr5",mid_idf[4])
missid_corr6 = RooRealVar("missid_corr6","missid_corr6",mid_idf[5])
missid_corr7 = RooRealVar("missid_corr7","missid_corr7",mid_idf[6])
missid_corr8 = RooRealVar("missid_corr8","missid_corr8",mid_idf[7])

print '     MODEL:  . Done! \n'
print '     MODEL:   o) Import the time acceptance correction in the BDT bins...'

#For correcting the normalizatio (divide alpha by this)
timeAccCorrBs, timeAccCorrBs_m, timeAccCorrBs_s, timeAccCorrBs_cons = createConst(TheTable.TimeAcceptanceCorrBs,TheTable.TimeAcceptanceCorrBsErr, "timeAccCorrBs")
timeAccCorrBd,timeAccCorrBd_m,timeAccCorrBd_s, timeAccCorrBd_cons = createConst(TheTable.TimeAcceptanceCorrBd,TheTable.TimeAcceptanceCorrBdErr, "timeAccCorrBd")

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

print '     MODEL:  . Done! \n'
print '     MODEL:   o) Define normalized candidate yields '
print '                 N = BR*TimeAccCorrection / alphs_s (linking to abs. BR) '


#Parameters necessary for the normalization

print '     MODEL:       .. for Bd . mumu'
#New parameterization from Marco 15.Nov 2013
fdfs , fdfs_cons = createBifurConst(TheTable.fd_over_fs,TheTable.fd_over_fsErrN,TheTable.fd_over_fsErrP,'fdfs') #the 'fsfd' in TheTable =3...., sa actually fdfs
alpha_KPi , alpha_KPi_m,alpha_KPi_s, alpha_KPi_cons = createConst(TheTable.NormKPi_fullmass_noBF * 1.0e7,TheTable.NormKPi_fullmass_noBFErr*1.0e7,'alpha_KPi') # NormKPi_fullmass_noBF
alpha_KPi_Err = RooRealVar('alpha_KPi_Err','alpha_KPi_Err',TheTable.NormKPi_fullmass_noBFErr*1.e7)
alpha_Bu , alpha_Bu_m ,alpha_Bu_s , alpha_Bu_cons = createConst(TheTable.NormBu_fullmass_noBF * 1.0e7, TheTable.NormBu_fullmass_noBFErr * 1.0e7,'alpha_Bu') # NormBu_fullmass_noBF
alpha_Bu_Err = RooRealVar('alpha_Bu_Err','alpha_Bu_Err',TheTable.NormBu_fullmass_noBFErr*1.e7)  ### Redundant ?

BdKpi_BF ,BdKpi_BF_m ,BdKpi_BF_s , BdKpi_BF_cons = createConst(TheTable.BdKpi_BF*1.e05, TheTable.BdKpi_BFErr*1.e05,'BdKpi_BF')
BdKpi_BFErr = RooRealVar('BdKpi_BF_Err','BdKpi_BF_Err',TheTable.BdKpi_BFErr*1.e05) # BdKpi_BF_Err ## Redundant ??
BdKpi_BFErr.setConstant()

BuJpsiK_BF , BuJpsiK_BF_m ,BuJpsiK_BF_s , BuJpsiK_BF_cons = createConst(TheTable.BuJpsiK_BF*1.e05, TheTable.BuJpsiK_BFErr*1.e05,'BuJpsiK_BF')
BuJpsiK_BFErr = RooRealVar('BuJpsiK_BF_Err','BuJpsiK_BF_Err',TheTable.BuJpsiK_BFErr*1.e05) # BuJpsiK_BF_Err
BuJpsiK_BFErr.setConstant()

alpha_d = RooFormulaVar('alpha_d','alpha_d', '((@4*(@0*1.e-5)*((@2*1.e-5)*(@2*1.e-5)*@7*@7+@6*@6*(@3*1.e-5)*(@3*1.e-5))+@6*(@2*1.e-5)*((@0*1.e-5)*(@0*1.e-5)*@5*@5+@4*@4*(@1*1.e-5)*(@1*1.e-5)))/((@0*1.e-5)*(@0*1.e-5)*@5*@5+@4*@4*(@1*1.e-5)*(@1*1.e-5)+(@2*1.e-5)*(@2*1.e-5)*@7*@7+@6*@6*(@3*1.e-5)*(@3*1.e-5)))', RooArgList(BdKpi_BF,BdKpi_BFErr,BuJpsiK_BF,BuJpsiK_BFErr,alpha_KPi,alpha_KPi_Err,alpha_Bu,alpha_Bu_Err))
#Formula from Marco

#Original magnitudes
#alpha_KPi , alpha_KPi_cons = createConst(TheTable.NormKPi_fullmass_noBF,TheTable.NormKPi_fullmass_noBFErr,'alpha_KPi') # NormKPi_fullmass_noBF
#alpha_KPi_Err = RooRealVar('alpha_KPi_Err','alpha_KPi_Err',TheTable.NormKPi_fullmass_noBFErr)
#alpha_Bu , alpha_Bu_cons = createConst(TheTable.NormBu_fullmass_noBF, TheTable.NormBu_fullmass_noBFErr,'alpha_Bu') # NormBu_fullmass_noBF
#alpha_Bu_Err = RooRealVar('alpha_Bu_Err','alpha_Bu_Err',TheTable.NormBu_fullmass_noBFErr)
#BdKpi_BF , BdKpi_BF_cons = createConst(TheTable.BdKpi_BF, TheTable.BdKpi_BFErr,'BdKpi_BF')
#BdKpi_BFErr = RooRealVar('BdKpi_BF_Err','BdKpi_BF_Err',TheTable.BdKpi_BFErr) # BdKpi_BF_Err
#BuJpsiK_BF , BuJpsiK_BF_cons = createConst(TheTable.BuJpsiK_BF, TheTable.BuJpsiK_BFErr,'BuJpsiK_BF')
#BuJpsiK_BFErr = RooRealVar('BuJpsiK_BF_Err','BuJpsiK_BF_Err',TheTable.BuJpsiK_BFErr) # BuJpsiK_BF_Err
#alpha_d = RooFormulaVar('alpha_d','alpha_d', '((@4*@0*(@2*@2*@7*@7+@6*@6*@3*@3)+@6*@2*(@0*@0*@5*@5+@4*@4*@1*@1))/(@0*@0*@5*@5+@4*@4*@1*@1+@2*@2*@7*@7+@6*@6*@3*@3))', RooArgList(BdKpi_BF,BdKpi_BFErr,BuJpsiK_BF,BuJpsiK_BFErr,alpha_KPi,alpha_KPi_Err,alpha_Bu,alpha_Bu_Err))

#@0 : BdKpi_BF
#@1 : BdKpi_BF_Err
#@2 : BuJpsiK_BF
#@3 : BuJpsiK_BFErr
#@4 : NormKPi_fullmass_noBF
#@5 : NormKPi_fullmass_noBFErr
#@6 : NormBu_fullmass_noBF
#@7 : NormBu_fullmass_noBFErr

print 'Alpha_d = ', alpha_d.getVal()
#raw_input('Check alpha_d: 2.43016613172e-11 * 1.01504863807 = 2.4667368222862261e-11')

nbd = RooRealVar("NBd","NBd", 5,-20.,1000)
if opts.get('INCLUDE_BD'):
    #BR_d = RooRealVar("BRd","BRd", 1e-10,-0.1e-10,10e-10)
    BR_d = RooRealVar("BRd","BRd", 1,-0.1,10)
    nbd = RooFormulaVar("NBd","NBd", "@0*1e-10*@1/(@2*1.e-7)", RooArgList(BR_d,timeAccCorrBd,alpha_d)) ### Is the timeAcc needed?
    #nbd = RooFormulaVar("NBd","NBd", "BRd*1e-10*timeAccCorrBd/(alpha_d)", RooArgList(alpha_d,timeAccCorrBd,BR_d))
    print '     MODEL:       . Fit also for BR(Bd2mumu)'
else: print '     MODEL:   Fluctuate only the NBd, do not put the BR in.'

print '     MODEL:       .. for Bs . mumu'
alpha_s = RooFormulaVar("alpha_s","alpha_s", "@0*@1", RooArgList(fdfs,alpha_d))
BR_s = RooRealVar("BRs","BRs", 1,-0.1,10)
nbs = RooFormulaVar("NBs","NBs", "@0*1e-9*@1/(@2*1.e-7)", RooArgList(BR_s,timeAccCorrBs,alpha_s))
#nbs = RooFormulaVar("NBs","NBs", "BRs*1e-9*timeAccCorrBs/(alpha_s)", RooArgList(alpha_s,timeAccCorrBs,BR_s))
print '     MODEL:  . Done! \n'
print '     MODEL:  . Done! \n'
print '     MODEL:   o) Define the signal mass model (Crystal Ball) for both, Bd and Bs...'

sigmaBs ,sigmaBs_m ,sigmaBs_s ,sigmaBs_cons = createConst(TheTable.MassResoBs,TheTable.MassResoErrBs, "sigmaBs")  ## Mass peak lineshape parameters
sigmaBd ,sigmaBd_m ,sigmaBd_s ,sigmaBd_cons = createConst(TheTable.MassResoBd,TheTable.MassResoErrBd, "sigmaBd")

meanBs , meanBs_m ,meanBs_s ,meanBs_cons = createConst(TheTable.MassMeanBs,TheTable.MassMeanErrBs, "MBs")
meanBd , meanBd_m ,meanBd_s ,meanBd_cons = createConst(TheTable.MassMeanBd,TheTable.MassMeanErrBd, "MBd")

a, a_m, a_s, a_cons = createConst(TheTable.CBTrans,TheTable.CBTransErr,'CBTrans')
n, n_m, n_s, n_cons = createConst(TheTable.CBExpo,TheTable.CBExpoErr,'CBExpo')

print '     MODEL:  . Done! \n'
print '     MODEL:   o) Import the signal distribution in BDT from hh (TIS) distribution in the BDT...'

BDT_f2 ,BDT_f2_m ,BDT_f2_s ,BDT_f2_cons = createConst(TheTable.BDT_sig2,TheTable.BDT_sigErr2, "BDT_f2")
BDT_f3 ,BDT_f3_m ,BDT_f3_s ,BDT_f3_cons = createConst(TheTable.BDT_sig3,TheTable.BDT_sigErr3, "BDT_f3")
BDT_f4 ,BDT_f4_m ,BDT_f4_s ,BDT_f4_cons = createConst(TheTable.BDT_sig4,TheTable.BDT_sigErr4, "BDT_f4")
BDT_f5 ,BDT_f5_m ,BDT_f5_s ,BDT_f5_cons = createConst(TheTable.BDT_sig5,TheTable.BDT_sigErr5, "BDT_f5")
BDT_f6 ,BDT_f6_m ,BDT_f6_s ,BDT_f6_cons = createConst(TheTable.BDT_sig6,TheTable.BDT_sigErr6, "BDT_f6")
BDT_f7 ,BDT_f7_m ,BDT_f7_s ,BDT_f7_cons = createConst(TheTable.BDT_sig7,TheTable.BDT_sigErr7, "BDT_f7")
BDT_f8 ,BDT_f8_m ,BDT_f8_s ,BDT_f8_cons = createConst(TheTable.BDT_sig8,TheTable.BDT_sigErr8, "BDT_f8")

BDT_f1 ,BDT_f1_m ,BDT_f1_s ,BDT_f1_cons = createConst(TheTable.BDT_sig1,TheTable.BDT_sigErr1, "BDT_f1")
#BDT_f1 = RooFormulaVar("BDT_f1", "BDT_f1", "(1-BDT_f2-BDT_f3-BDT_f4-BDT_f5-BDT_f6-BDT_f7-BDT_f8)", RooArgList(BDT_f2,BDT_f3,BDT_f4,BDT_f5,BDT_f6,BDT_f7,BDT_f8)) #wrong, the renormalization needs to be done at the end, for all the corrections together!

print '     MODEL:  . Done! \n'
print '     MODEL:   o) Import the Double Misidentified hh.mumu background model parameters...'

print '     MODEL:    Parameters for 3 x CrystalBall from MC'
#Shift between the means in toytable_test_1fb_AleInput.py and
#toytable_summer13.py
shift_Bs = 1.11
shift_Bd = -0.27
shift = (shift_Bs + shift_Bd)/2   ### wtf?
missid_mean1 = RooRealVar("missid_mean1","missid_mean1",5.09168e+03+100+shift)#5050, 5600)#5168.)
missid_d1= RooRealVar("missid_d1","missid_d1", 4.01034e+01)#72.4, 20., 200.)
missid_d2= RooRealVar("missid_d2","missid_d2", 4.03549e+01)#72.4, 20., 200.)
missid_mean2 = RooFormulaVar("missid_mean2","missid_mean2", "@0+@1" ,RooArgList(missid_mean1,missid_d1) )
missid_mean3 = RooFormulaVar("missid_mean3","missid_mean3", "@0+@1" ,RooArgList(missid_mean2,missid_d2) )
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


print '     MODEL:  . Done! \n'


#Variables needed for peaking bkg. normalization
BkgNorm, BkgNorm_m, BkgNorm_s, BkgNorm_cons = createConst(TheTable.BkgNorm, TheTable.BkgNormErr, "BkgNorm")


if opts.get('ADD_B2XMUNU'):
    print '     MODEL:   o) Import the parameters needed for Bd.pi mu nu exclusive background...'
    ### B0. Pi Mu Nu bkg
    #SHAPE parameters:

    PiMuNuMean1,PiMuNuMean1_m,PiMuNuMean1_s,PiMuNuMean1_cons, = createConst(TheTable.PiMuNuMean1,TheTable.PiMuNuMean1Err, "PiMuNuMean1")
    PiMuNuSigma1,PiMuNuSigma1_m,PiMuNuSigma1_s,PiMuNuSigma1_cons = createConst(TheTable.PiMuNuSigma1,TheTable.PiMuNuSigma1Err, "PiMuNuSigma1")
    PiMuNuShc1, PiMuNuShc1_m,PiMuNuShc1_s, PiMuNuShc1_cons = createConst(TheTable.PiMuNuShc1,TheTable.PiMuNuShc1Err, "PiMuNuShc1")

    PiMuNuMean2,PiMuNuMean2_m,PiMuNuMean2_s,PiMuNuMean2_cons, = createConst(TheTable.PiMuNuMean2,TheTable.PiMuNuMean2Err, "PiMuNuMean2")
    PiMuNuSigma2,PiMuNuSigma2_m,PiMuNuSigma2_s,PiMuNuSigma2_cons = createConst(TheTable.PiMuNuSigma2,TheTable.PiMuNuSigma2Err, "PiMuNuSigma2")
    PiMuNuShc2, PiMuNuShc2_m,PiMuNuShc2_s, PiMuNuShc2_cons = createConst(TheTable.PiMuNuShc2,TheTable.PiMuNuShc2Err, "PiMuNuShc2")

    PiMuNuMean3,PiMuNuMean3_m,PiMuNuMean3_s,PiMuNuMean3_cons, = createConst(TheTable.PiMuNuMean3,TheTable.PiMuNuMean3Err, "PiMuNuMean3")
    PiMuNuSigma3,PiMuNuSigma3_m,PiMuNuSigma3_s,PiMuNuSigma3_cons = createConst(TheTable.PiMuNuSigma3,TheTable.PiMuNuSigma3Err, "PiMuNuSigma3")
    PiMuNuShc3, PiMuNuShc3_m,PiMuNuShc3_s, PiMuNuShc3_cons = createConst(TheTable.PiMuNuShc3,TheTable.PiMuNuShc3Err, "PiMuNuShc3")


    PiMuNuMean4, PiMuNuMean4_m, PiMuNuMean4_s, PiMuNuMean4_cons = createConst(TheTable.PiMuNuMean4,TheTable.PiMuNuMean4Err, "PiMuNuMean4")
    PiMuNuSigma4, PiMuNuSigma4_m, PiMuNuSigma4_s, PiMuNuSigma4_cons = createConst(TheTable.PiMuNuSigma4,TheTable.PiMuNuSigma4Err, "PiMuNuSigma4")
    PiMuNuShc4, PiMuNuShc4_m, PiMuNuShc4_s, PiMuNuShc4_cons = createConst(TheTable.PiMuNuShc4,TheTable.PiMuNuShc4Err, "PiMuNuShc4")

    #As PiMuNuShc is very small in this bin, I shift it by 10^5 (and multiply by 10-5 later again)
    #PiMuNuShc4shift,PiMuNuShc4_cons = createConst(TheTable.PiMuNuShc4*1.e8,TheTable.PiMuNuShc4Err*1.e8, "PiMuNuShc4shift")
    #PiMuNuShc4 = RooFormulaVar('PiMuNuShc4','PiMuNuShc4','(@0*1.e-8)',RooArgList(PiMuNuShc4shift))

    PiMuNuMean5,PiMuNuMean5_m,PiMuNuMean5_s,PiMuNuMean5_cons, = createConst(TheTable.PiMuNuMean5,TheTable.PiMuNuMean5Err, "PiMuNuMean5")
    PiMuNuSigma5,PiMuNuSigma5_m,PiMuNuSigma5_s,PiMuNuSigma5_cons = createConst(TheTable.PiMuNuSigma5,TheTable.PiMuNuSigma5Err, "PiMuNuSigma5")
    PiMuNuShc5, PiMuNuShc5_m,PiMuNuShc5_s, PiMuNuShc5_cons = createConst(TheTable.PiMuNuShc5,TheTable.PiMuNuShc5Err, "PiMuNuShc5")

    PiMuNuMean6,PiMuNuMean6_m,PiMuNuMean6_s,PiMuNuMean6_cons, = createConst(TheTable.PiMuNuMean6,TheTable.PiMuNuMean6Err, "PiMuNuMean6")
    PiMuNuSigma6,PiMuNuSigma6_m,PiMuNuSigma6_s,PiMuNuSigma6_cons = createConst(TheTable.PiMuNuSigma6,TheTable.PiMuNuSigma6Err, "PiMuNuSigma6")
    PiMuNuShc6, PiMuNuShc6_m,PiMuNuShc6_s, PiMuNuShc6_cons = createConst(TheTable.PiMuNuShc6,TheTable.PiMuNuShc6Err, "PiMuNuShc6")


    PiMuNuMean7,PiMuNuMean7_m,PiMuNuMean7_s,PiMuNuMean7_cons, = createConst(TheTable.PiMuNuMean7,TheTable.PiMuNuMean7Err, "PiMuNuMean7")
    PiMuNuSigma7,PiMuNuSigma7_m,PiMuNuSigma7_s,PiMuNuSigma7_cons = createConst(TheTable.PiMuNuSigma7,TheTable.PiMuNuSigma7Err, "PiMuNuSigma7")
    PiMuNuShc7, PiMuNuShc7_m,PiMuNuShc7_s, PiMuNuShc7_cons = createConst(TheTable.PiMuNuShc7,TheTable.PiMuNuShc7Err, "PiMuNuShc7")


    PiMuNuMean8,PiMuNuMean8_m,PiMuNuMean8_s,PiMuNuMean8_cons, = createConst(TheTable.PiMuNuMean8,TheTable.PiMuNuMean8Err, "PiMuNuMean8")
    PiMuNuSigma8,PiMuNuSigma8_m,PiMuNuSigma8_s,PiMuNuSigma8_cons = createConst(TheTable.PiMuNuSigma8,TheTable.PiMuNuSigma8Err, "PiMuNuSigma8")
    PiMuNuShc8, PiMuNuShc8_m,PiMuNuShc8_s, PiMuNuShc8_cons = createConst(TheTable.PiMuNuShc8,TheTable.PiMuNuShc8Err, "PiMuNuShc8")




    #B0 . PiMuNu and Bs . KMuNu yields (treated ass same shape)

    #NBdPiMuNu = BkgNorm * PiMuNuEff *PiMuNuBR / BuJpsiK_BF
    #Change magnitude
    PiMuNuEff, PiMuNuEff_m, PiMuNuEff_s, PiMuNuEff_cons = createConst(TheTable.PiMuNuEff*1.e7, TheTable.PiMuNuEffErr*1.e7, "PiMuNuEff")
    PiMuNuBR, PiMuNuBR_m, PiMuNuBR_s, PiMuNuBR_cons = createConst(TheTable.PiMuNuBR*1.e4, TheTable.PiMuNuBRErr*1.e4, "PiMuNuBR")
    PiMuNuTot = RooFormulaVar('PiMuNuTot','Total PiMuNu yield','(@0*@1*1.e-7*@2*1.e-4)/(@3*1.e-5)',RooArgList(BkgNorm,PiMuNuEff,PiMuNuBR,BuJpsiK_BF))
    #PiMuNuTot = RooFormulaVar('PiMuNuTot','Total PiMuNu yield','(@0*@1*1.e-7*@2*1.e-4)/(@3)',RooArgList(BkgNorm,PiMuNuEff,PiMuNuBR,BuJpsiK_BF))

    #Original magnitude
    #PiMuNuEff, PiMuNuEff_m, PiMuNuEff_s, PiMuNuEff_cons = createConst(TheTable.PiMuNuEff, TheTable.PiMuNuEffErr, "PiMuNuEff")
    #PiMuNuBR, PiMuNuBR_m, PiMuNuBR_s, PiMuNuBR_cons = createConst(TheTable.PiMuNuBR, TheTable.PiMuNuBRErr, "PiMuNuBR")
    #PiMuNuTot = RooFormulaVar('PiMuNuTot','Total PiMuNu yield','(@0*@1*@2)/@3',RooArgList(BkgNorm,PiMuNuEff,PiMuNuBR,BuJpsiK_BF))

    #NBsKMuNu = BkgNorm * KMuNuEff *KMuNuBR /BuJpsiK_BF * fs/fd
    KMuNuEff, KMuNuEff_m, KMuNuEff_s, KMuNuEff_cons = createConst(TheTable.KMuNuEff*1.e7, TheTable.KMuNuEffErr*1.e7, "KMuNuEff")
    KMuNuBR, KMuNuBR_m, KMuNuBR_s, KMuNuBR_cons = createConst(TheTable.KMuNuBR*1.e4, TheTable.KMuNuBRErr*1.e4, "KMuNuBR")
    KMuNuTot = RooFormulaVar('KMuNuTot','Total KMuNu yield','(@0*@1*1.e-7*@2*1.e-4)/(@3*1.e-5*@4)',RooArgList(BkgNorm,KMuNuEff,KMuNuBR,BuJpsiK_BF,fdfs))
    #KMuNuTot = RooFormulaVar('KMuNuTot','Total KMuNu yield','((@0*@1*1.e-7*@2*1.e-4)/(@3))*(1/@4) ',RooArgList(BkgNorm,KMuNuEff,KMuNuBR,BuJpsiK_BF,fdfs))

    #KMuNuEff, KMuNuEff_m, KMuNuEff_s, KMuNuEff_cons = createConst(TheTable.KMuNuEff, TheTable.KMuNuEffErr, "KMuNuEff")
    #KMuNuBR, KMuNuBR_m, KMuNuBR_s, KMuNuBR_cons = createConst(TheTable.KMuNuBR, TheTable.KMuNuBRErr, "KMuNuBR")
    #KMuNuTot = RooFormulaVar('KMuNuTot','Total KMuNu yield','((@0*@1*@2)/@3)*(1/@4) ',RooArgList(BkgNorm,KMuNuEff,KMuNuBR,BuJpsiK_BF,fdfs))

    print ' BdPiMuNu yield:', PiMuNuTot.getVal()
    print ' BsKMuNu yield:', KMuNuTot.getVal()
    #raw_input('Check BdPiMuNu, BsKMuNu yields: ~115,~10 per 3fb-1')

    #Fractions per BDT bins

    PiMuNuFrac2, PiMuNuFrac2_m, PiMuNuFrac2_s, PiMuNuFrac2_cons = createConst(TheTable.PiMuNuFrac2, TheTable.PiMuNuFrac2Err, "PiMuNuFrac2")
    PiMuNuFrac3, PiMuNuFrac3_m, PiMuNuFrac3_s, PiMuNuFrac3_cons = createConst(TheTable.PiMuNuFrac3, TheTable.PiMuNuFrac3Err, "PiMuNuFrac3")
    PiMuNuFrac4, PiMuNuFrac4_m, PiMuNuFrac4_s, PiMuNuFrac4_cons = createConst(TheTable.PiMuNuFrac4, TheTable.PiMuNuFrac4Err, "PiMuNuFrac4")
    PiMuNuFrac5, PiMuNuFrac5_m, PiMuNuFrac5_s, PiMuNuFrac5_cons = createConst(TheTable.PiMuNuFrac5, TheTable.PiMuNuFrac5Err, "PiMuNuFrac5")
    PiMuNuFrac6, PiMuNuFrac6_m, PiMuNuFrac6_s, PiMuNuFrac6_cons = createConst(TheTable.PiMuNuFrac6, TheTable.PiMuNuFrac6Err, "PiMuNuFrac6")
    PiMuNuFrac7, PiMuNuFrac7_m, PiMuNuFrac7_s, PiMuNuFrac7_cons = createConst(TheTable.PiMuNuFrac7, TheTable.PiMuNuFrac7Err, "PiMuNuFrac7")
    PiMuNuFrac8, PiMuNuFrac8_m, PiMuNuFrac8_s, PiMuNuFrac8_cons = createConst(TheTable.PiMuNuFrac8, TheTable.PiMuNuFrac8Err, "PiMuNuFrac8")
    #PiMuNuFrac1, PiMuNuFrac1_m, PiMuNuFrac1_s, PiMuNuFrac1_cons = createConst(TheTable.PiMuNuFrac1, TheTable.PiMuNuFrac1Err, "PiMuNuFrac1")
    PiMuNuFrac1 = RooFormulaVar("PiMuNuFrac1", "PiMuNuFrac1", "(1.-@0-@1-@2-@3-@4-@5-@6)", RooArgList(PiMuNuFrac2,PiMuNuFrac3,PiMuNuFrac4,PiMuNuFrac5,PiMuNuFrac6,PiMuNuFrac7,PiMuNuFrac8))

    KMuNuFrac2, KMuNuFrac2_m, KMuNuFrac2_s, KMuNuFrac2_cons = createConst(TheTable.KMuNuFrac2, TheTable.KMuNuFrac2Err, "KMuNuFrac2")
    KMuNuFrac3, KMuNuFrac3_m, KMuNuFrac3_s, KMuNuFrac3_cons = createConst(TheTable.KMuNuFrac3, TheTable.KMuNuFrac3Err, "KMuNuFrac3")
    KMuNuFrac4, KMuNuFrac4_m, KMuNuFrac4_s, KMuNuFrac4_cons = createConst(TheTable.KMuNuFrac4, TheTable.KMuNuFrac4Err, "KMuNuFrac4")
    KMuNuFrac5, KMuNuFrac5_m, KMuNuFrac5_s, KMuNuFrac5_cons = createConst(TheTable.KMuNuFrac5, TheTable.KMuNuFrac5Err, "KMuNuFrac5")
    KMuNuFrac6, KMuNuFrac6_m, KMuNuFrac6_s, KMuNuFrac6_cons = createConst(TheTable.KMuNuFrac6, TheTable.KMuNuFrac6Err, "KMuNuFrac6")
    KMuNuFrac7, KMuNuFrac7_m, KMuNuFrac7_s, KMuNuFrac7_cons = createConst(TheTable.KMuNuFrac7, TheTable.KMuNuFrac7Err, "KMuNuFrac7")
    KMuNuFrac8, KMuNuFrac8_m, KMuNuFrac8_s, KMuNuFrac8_cons = createConst(TheTable.KMuNuFrac8, TheTable.KMuNuFrac8Err, "KMuNuFrac8")
    #KMuNuFrac1, KMuNuFrac1_m, KMuNuFrac1_s, KMuNuFrac1_cons = createConst(TheTable.KMuNuFrac1, TheTable.KMuNuFrac1Err, "KMuNuFrac1")
    KMuNuFrac1 = RooFormulaVar("KMuNuFrac1", "KMuNuFrac1", "(1.-@0-@1-@2-@3-@4-@5-@6)", RooArgList(KMuNuFrac2,KMuNuFrac3,KMuNuFrac4,KMuNuFrac5,KMuNuFrac6,KMuNuFrac7,KMuNuFrac8))

    #Normalize the fractions
    #sum_PiMuNuFrac = RooFormulaVar('PiMuNuFrac_sum','Sum of all the raw PiMuNuFrac fractions','(@0+@1+@2+@3+@4+@5+@6+@7)',RooArgList(PiMuNuFrac1,PiMuNuFrac2,PiMuNuFrac3,PiMuNuFrac4,PiMuNuFrac5,PiMuNuFrac6,PiMuNuFrac7,PiMuNuFrac8))
    #sum_KMuNuFrac = RooFormulaVar('KMuNuFrac_sum','Sum of all the raw KMuNuFrac fractions','(@0+@1+@2+@3+@4+@5+@6+@7)',RooArgList(KMuNuFrac1,KMuNuFrac2,KMuNuFrac3,KMuNuFrac4,KMuNuFrac5,KMuNuFrac6,KMuNuFrac7,KMuNuFrac8))
    #f_PiMuNu = []
    #f_KMuNu = []
    #v = vars()
    #for i in range(1,9):
    #    f_PiMuNu.append(RooFormulaVar("f_PiMuNu_"+str(i),"Fr. of events in PiMuNu bin "+str(i), "(@0/@1)", RooArgList(v['PiMuNuFrac'+str(i)],sum_PiMuNuFrac)))
    #    f_KMuNu.append(RooFormulaVar("f_KMuNu_"+str(i),"Fr. of events in KMuNu bin "+str(i), "(@0/@1)", RooArgList(v['KMuNuFrac'+str(i)],sum_KMuNuFrac)))
    #    print '		 f_PiMuNu:', f_PiMuNu[i-1].getVal()
    #    print '		 f_KMuNu:', f_KMuNu[i-1].getVal()
    #print '     MODEL:  . Done! \n'

    #raw_input('Check BdPiMuNu, BsKMuNu fractions...')

if opts.get('ADD_B0UPIMUMU'):
    print '     MODEL:   o) Import the parameters needed for B(0)+.pi(0)+ mu mu exclusive background...'
    ### B(0)+. Pi(0)+ Mu Mu bkg RooPhysBkg model
    #SHAPE parameters:
    PiMuMuMean1, PiMuMuMean1_m, PiMuMuMean1_s, PiMuMuMean1_cons = createConst(TheTable.PiMuMuMean1,TheTable.PiMuMuMean1Err, "PiMuMuMean1")
    PiMuMuSigma1, PiMuMuSigma1_m, PiMuMuSigma1_s, PiMuMuSigma1_cons = createConst(TheTable.PiMuMuSigma1,TheTable.PiMuMuSigma1Err, "PiMuMuSigma1")
    PiMuMuShc1, PiMuMuShc1_m, PiMuMuShc1_s, PiMuMuShc1_cons = createConst(TheTable.PiMuMuShc1,TheTable.PiMuMuShc1Err, "PiMuMuShc1")

    PiMuMuMean2, PiMuMuMean2_m, PiMuMuMean2_s, PiMuMuMean2_cons = createConst(TheTable.PiMuMuMean2,TheTable.PiMuMuMean2Err, "PiMuMuMean2")
    PiMuMuSigma2, PiMuMuSigma2_m, PiMuMuSigma2_s, PiMuMuSigma2_cons = createConst(TheTable.PiMuMuSigma2,TheTable.PiMuMuSigma2Err, "PiMuMuSigma2")
    PiMuMuShc2, PiMuMuShc2_m, PiMuMuShc2_s, PiMuMuShc2_cons = createConst(TheTable.PiMuMuShc2,TheTable.PiMuMuShc2Err, "PiMuMuShc2")

    PiMuMuMean3, PiMuMuMean3_m, PiMuMuMean3_s, PiMuMuMean3_cons = createConst(TheTable.PiMuMuMean3,TheTable.PiMuMuMean3Err, "PiMuMuMean3")
    PiMuMuSigma3, PiMuMuSigma3_m, PiMuMuSigma3_s, PiMuMuSigma3_cons = createConst(TheTable.PiMuMuSigma3,TheTable.PiMuMuSigma3Err, "PiMuMuSigma3")
    PiMuMuShc3, PiMuMuShc3_m, PiMuMuShc3_s, PiMuMuShc3_cons = createConst(TheTable.PiMuMuShc3,TheTable.PiMuMuShc3Err, "PiMuMuShc3")

    PiMuMuMean4, PiMuMuMean4_m, PiMuMuMean4_s, PiMuMuMean4_cons = createConst(TheTable.PiMuMuMean4,TheTable.PiMuMuMean4Err, "PiMuMuMean4")
    PiMuMuSigma4, PiMuMuSigma4_m, PiMuMuSigma4_s, PiMuMuSigma4_cons = createConst(TheTable.PiMuMuSigma4,TheTable.PiMuMuSigma4Err, "PiMuMuSigma4")
    PiMuMuShc4, PiMuMuShc4_m, PiMuMuShc4_s, PiMuMuShc4_cons = createConst(TheTable.PiMuMuShc4,TheTable.PiMuMuShc4Err, "PiMuMuShc4")

    PiMuMuMean5, PiMuMuMean5_m, PiMuMuMean5_s, PiMuMuMean5_cons = createConst(TheTable.PiMuMuMean5,TheTable.PiMuMuMean5Err, "PiMuMuMean5")
    PiMuMuSigma5, PiMuMuSigma5_m, PiMuMuSigma5_s, PiMuMuSigma5_cons = createConst(TheTable.PiMuMuSigma5,TheTable.PiMuMuSigma5Err, "PiMuMuSigma5")
    PiMuMuShc5, PiMuMuShc5_m, PiMuMuShc5_s, PiMuMuShc5_cons = createConst(TheTable.PiMuMuShc5,TheTable.PiMuMuShc5Err, "PiMuMuShc5")

    PiMuMuMean6, PiMuMuMean6_m, PiMuMuMean6_s, PiMuMuMean6_cons = createConst(TheTable.PiMuMuMean6,TheTable.PiMuMuMean6Err, "PiMuMuMean6")
    PiMuMuSigma6, PiMuMuSigma6_m, PiMuMuSigma6_s, PiMuMuSigma6_cons = createConst(TheTable.PiMuMuSigma6,TheTable.PiMuMuSigma6Err, "PiMuMuSigma6")
    PiMuMuShc6, PiMuMuShc6_m, PiMuMuShc6_s, PiMuMuShc6_cons = createConst(TheTable.PiMuMuShc6,TheTable.PiMuMuShc6Err, "PiMuMuShc6")

    PiMuMuMean7, PiMuMuMean7_m, PiMuMuMean7_s, PiMuMuMean7_cons = createConst(TheTable.PiMuMuMean7,TheTable.PiMuMuMean7Err, "PiMuMuMean7")
    PiMuMuSigma7, PiMuMuSigma7_m, PiMuMuSigma7_s, PiMuMuSigma7_cons = createConst(TheTable.PiMuMuSigma7,TheTable.PiMuMuSigma7Err, "PiMuMuSigma7")
    PiMuMuShc7, PiMuMuShc7_m, PiMuMuShc7_s, PiMuMuShc7_cons = createConst(TheTable.PiMuMuShc7,TheTable.PiMuMuShc7Err, "PiMuMuShc7")

    PiMuMuMean8, PiMuMuMean8_m, PiMuMuMean8_s, PiMuMuMean8_cons = createConst(TheTable.PiMuMuMean8,TheTable.PiMuMuMean8Err, "PiMuMuMean8")
    PiMuMuSigma8, PiMuMuSigma8_m, PiMuMuSigma8_s, PiMuMuSigma8_cons = createConst(TheTable.PiMuMuSigma8,TheTable.PiMuMuSigma8Err, "PiMuMuSigma8")
    PiMuMuShc8, PiMuMuShc8_m, PiMuMuShc8_s, PiMuMuShc8_cons = createConst(TheTable.PiMuMuShc8,TheTable.PiMuMuShc8Err, "PiMuMuShc8")

    #B0 . PiMuMu

    #NBdPiMuNu = BkgNorm * PiMuNuEff *PiMuNuBR /BuJpsiK_BF
    PiMuMuEff, PiMuMuEff_m, PiMuMuEff_s, PiMuMuEff_cons = createConst(TheTable.PiMuMuEff*1.e3, TheTable.PiMuMuEffErr*1.e3, "PiMuMuEff")
    PiMuMuBR, PiMuMuBR_m, PiMuMuBR_s, PiMuMuBR_cons = createConst(TheTable.PiMuMuBR*1.e8, TheTable.PiMuMuBRErr*1.e8, "PiMuMuBR")
    PiMuMuTot = RooFormulaVar('PiMuMuTot','Total PiMuMu yield','(@0*(@1*1.e-3)*(@2*1.e-8))/(@3*1.e-5)',RooArgList(BkgNorm,PiMuMuEff,PiMuMuBR,BuJpsiK_BF))
    #PiMuMuTot = RooFormulaVar('PiMuMuTot','Total PiMuMu yield','(@0*@1*1.e-3*@2*1.e-8)/(@3)',RooArgList(BkgNorm,PiMuMuEff,PiMuMuBR,BuJpsiK_BF))

    #Original magnitudes
    #PiMuMuEff, PiMuMuEff_m, PiMuMuEff_s, PiMuMuEff_cons = createConst(TheTable.PiMuMuEff, TheTable.PiMuMuEffErr, "PiMuMuEff")
    #PiMuMuBR, PiMuMuBR_m, PiMuMuBR_s, PiMuMuBR_cons = createConst(TheTable.PiMuMuBR, TheTable.PiMuMuBRErr, "PiMuMuBR")
    #PiMuMuTot = RooFormulaVar('PiMuMuTot','Total PiMuMu yield','(@0*@1*@2)/@3',RooArgList(BkgNorm,PiMuMuEff,PiMuMuBR,BuJpsiK_BF))

    print ' BdPiMuMu yield:', PiMuMuTot.getVal()
    #raw_input('Check BdPiMuMu, BsKMuMu yields:  ~28 per 3fb-1')

    #Fractions per BDT bins

    PiMuMuFrac2, PiMuMuFrac2_m, PiMuMuFrac2_s, PiMuMuFrac2_cons = createConst(TheTable.PiMuMuFrac2, TheTable.PiMuMuFrac2Err, "PiMuMuFrac2")
    PiMuMuFrac3, PiMuMuFrac3_m, PiMuMuFrac3_s, PiMuMuFrac3_cons = createConst(TheTable.PiMuMuFrac3, TheTable.PiMuMuFrac3Err, "PiMuMuFrac3")
    PiMuMuFrac4, PiMuMuFrac4_m, PiMuMuFrac4_s, PiMuMuFrac4_cons = createConst(TheTable.PiMuMuFrac4, TheTable.PiMuMuFrac4Err, "PiMuMuFrac4")
    PiMuMuFrac5, PiMuMuFrac5_m, PiMuMuFrac5_s, PiMuMuFrac5_cons = createConst(TheTable.PiMuMuFrac5, TheTable.PiMuMuFrac5Err, "PiMuMuFrac5")
    PiMuMuFrac6, PiMuMuFrac6_m, PiMuMuFrac6_s, PiMuMuFrac6_cons = createConst(TheTable.PiMuMuFrac6, TheTable.PiMuMuFrac6Err, "PiMuMuFrac6")
    PiMuMuFrac7, PiMuMuFrac7_m, PiMuMuFrac7_s, PiMuMuFrac7_cons = createConst(TheTable.PiMuMuFrac7, TheTable.PiMuMuFrac7Err, "PiMuMuFrac7")
    PiMuMuFrac8, PiMuMuFrac8_m, PiMuMuFrac8_s, PiMuMuFrac8_cons = createConst(TheTable.PiMuMuFrac8, TheTable.PiMuMuFrac8Err, "PiMuMuFrac8")
    #PiMuMuFrac1, PiMuMuFrac1_m, PiMuMuFrac1_s, PiMuMuFrac1_cons = createConst(TheTable.PiMuMuFrac1, TheTable.PiMuMuFrac1Err, "PiMuMuFrac1")
    PiMuMuFrac1 = RooFormulaVar("PiMuMuFrac1", "PiMuMuFrac1", "(1.-@0-@1-@2-@3-@4-@5-@6)", RooArgList(PiMuMuFrac2,PiMuMuFrac3,PiMuMuFrac4,PiMuMuFrac5,PiMuMuFrac6,PiMuMuFrac7,PiMuMuFrac8))

    #Normalize the fractions
    #sum_PiMuMuFrac = RooFormulaVar('PiMuMuFrac_sum','Sum of all the raw PiMuMuFrac fractions','(@0+@1+@2+@3+@4+@5+@6+@7)',RooArgList(PiMuMuFrac1,PiMuMuFrac2,PiMuMuFrac3,PiMuMuFrac4,PiMuMuFrac5,PiMuMuFrac6,PiMuMuFrac7,PiMuMuFrac8))
    #f_PiMuMu = []
    #v = vars()
    #for i in range(1,9):
    #    f_PiMuMu.append(RooFormulaVar("f_PiMuMu_"+str(i),"Fr. of events in PiMuMut bin "+str(i), "(@0/@1)", RooArgList(v["PiMuMuFrac"+str(i)],sum_PiMuMuFrac)))
    #    print '		 f_PiMuMu:', f_PiMuMu[i-1].getVal()
    #print '     MODEL:  . Done! \n'

if opts.get('ADD_LAPMUNU'):
    print '     MODEL:   o) Import the parameters needed for Bs . K mu nu exclusive background...'
    ### Lambda_b -. proton mu nu

    #SHAPE parameters:
    LaPMuNuMean1, LaPMuNuMean1_m, LaPMuNuMean1_s, LaPMuNuMean1_cons = createConst(TheTable.LbPMuNuMean1,TheTable.LbPMuNuMean1Err, "LaPMuNuMean1")
    LaPMuNuSigma1, LaPMuNuSigma1_m, LaPMuNuSigma1_s, LaPMuNuSigma1_cons = createConst(TheTable.LbPMuNuSigma1,TheTable.LbPMuNuSigma1Err, "LaPMuNuSigma1")
    LaPMuNuShc1, LaPMuNuShc1_m, LaPMuNuShc1_s, LaPMuNuShc1_cons = createConst(TheTable.LbPMuNuShc1,TheTable.LbPMuNuShc1Err, "LaPMuNuShc1")

    LaPMuNuMean2, LaPMuNuMean2_m, LaPMuNuMean2_s, LaPMuNuMean2_cons = createConst(TheTable.LbPMuNuMean2,TheTable.LbPMuNuMean2Err, "LaPMuNuMean2")
    LaPMuNuSigma2, LaPMuNuSigma2_m, LaPMuNuSigma2_s, LaPMuNuSigma2_cons = createConst(TheTable.LbPMuNuSigma2,TheTable.LbPMuNuSigma2Err, "LaPMuNuSigma2")
    LaPMuNuShc2, LaPMuNuShc2_m, LaPMuNuShc2_s, LaPMuNuShc2_cons = createConst(TheTable.LbPMuNuShc2,TheTable.LbPMuNuShc2Err, "LaPMuNuShc2")

    LaPMuNuMean3, LaPMuNuMean3_m, LaPMuNuMean3_s, LaPMuNuMean3_cons = createConst(TheTable.LbPMuNuMean3,TheTable.LbPMuNuMean3Err, "LaPMuNuMean3")
    LaPMuNuSigma3, LaPMuNuSigma3_m, LaPMuNuSigma3_s, LaPMuNuSigma3_cons = createConst(TheTable.LbPMuNuSigma3,TheTable.LbPMuNuSigma3Err, "LaPMuNuSigma3")
    LaPMuNuShc3, LaPMuNuShc3_m, LaPMuNuShc3_s, LaPMuNuShc3_cons = createConst(TheTable.LbPMuNuShc3,TheTable.LbPMuNuShc3Err, "LaPMuNuShc3")

    LaPMuNuMean4, LaPMuNuMean4_m, LaPMuNuMean4_s, LaPMuNuMean4_cons = createConst(TheTable.LbPMuNuMean4,TheTable.LbPMuNuMean4Err, "LaPMuNuMean4")
    LaPMuNuSigma4, LaPMuNuSigma4_m, LaPMuNuSigma4_s, LaPMuNuSigma4_cons = createConst(TheTable.LbPMuNuSigma4,TheTable.LbPMuNuSigma4Err, "LaPMuNuSigma4")
    LaPMuNuShc4, LaPMuNuShc4_m, LaPMuNuShc4_s, LaPMuNuShc4_cons = createConst(TheTable.LbPMuNuShc4,TheTable.LbPMuNuShc4Err, "LaPMuNuShc4")

    LaPMuNuMean5, LaPMuNuMean5_m, LaPMuNuMean5_s, LaPMuNuMean5_cons = createConst(TheTable.LbPMuNuMean5,TheTable.LbPMuNuMean5Err, "LaPMuNuMean5")
    LaPMuNuSigma5, LaPMuNuSigma5_m, LaPMuNuSigma5_s, LaPMuNuSigma5_cons = createConst(TheTable.LbPMuNuSigma5,TheTable.LbPMuNuSigma5Err, "LaPMuNuSigma5")
    LaPMuNuShc5, LaPMuNuShc5_m, LaPMuNuShc5_s, LaPMuNuShc5_cons = createConst(TheTable.LbPMuNuShc5,TheTable.LbPMuNuShc5Err, "LaPMuNuShc5")

    LaPMuNuMean6, LaPMuNuMean6_m, LaPMuNuMean6_s, LaPMuNuMean6_cons = createConst(TheTable.LbPMuNuMean6,TheTable.LbPMuNuMean6Err, "LaPMuNuMean6")
    LaPMuNuSigma6, LaPMuNuSigma6_m, LaPMuNuSigma6_s, LaPMuNuSigma6_cons = createConst(TheTable.LbPMuNuSigma6,TheTable.LbPMuNuSigma6Err, "LaPMuNuSigma6")
    LaPMuNuShc6, LaPMuNuShc6_m, LaPMuNuShc6_s, LaPMuNuShc6_cons = createConst(TheTable.LbPMuNuShc6,TheTable.LbPMuNuShc6Err, "LaPMuNuShc6")

    LaPMuNuMean7, LaPMuNuMean7_m, LaPMuNuMean7_s, LaPMuNuMean7_cons = createConst(TheTable.LbPMuNuMean7,TheTable.LbPMuNuMean7Err, "LaPMuNuMean7")
    LaPMuNuSigma7, LaPMuNuSigma7_m, LaPMuNuSigma7_s, LaPMuNuSigma7_cons = createConst(TheTable.LbPMuNuSigma7,TheTable.LbPMuNuSigma7Err, "LaPMuNuSigma7")
    LaPMuNuShc7, LaPMuNuShc7_m, LaPMuNuShc7_s, LaPMuNuShc7_cons = createConst(TheTable.LbPMuNuShc7,TheTable.LbPMuNuShc7Err, "LaPMuNuShc7")

    LaPMuNuMean8, LaPMuNuMean8_m, LaPMuNuMean8_s, LaPMuNuMean8_cons = createConst(TheTable.LbPMuNuMean8,TheTable.LbPMuNuMean8Err, "LaPMuNuMean8")
    LaPMuNuSigma8, LaPMuNuSigma8_m, LaPMuNuSigma8_s, LaPMuNuSigma8_cons = createConst(TheTable.LbPMuNuSigma8,TheTable.LbPMuNuSigma8Err, "LaPMuNuSigma8")
    LaPMuNuShc8, LaPMuNuShc8_m, LaPMuNuShc8_s, LaPMuNuShc8_cons = createConst(TheTable.LbPMuNuShc8,TheTable.LbPMuNuShc8Err, "LaPMuNuShc8")

    #B0 . LaPMuNu
    #NBdPiMuNu = BkgNorm * PiMuNuEff *PiMuNuBR /BuJpsiK_BF
    LaPMuNuEff, LaPMuNuEff_m, LaPMuNuEff_s, LaPMuNuEff_cons = createConst(TheTable.LbPMuNuEff*1.e7, TheTable.LbPMuNuEffErr*1.e7, "LaPMuNuEff")
    LaPMuNuBR, LaPMuNuBR_m, LaPMuNuBR_s, LaPMuNuBR_cons = createConst(TheTable.LbPMuNuBR*1.e4, TheTable.LbPMuNuBRErr*1.e4, "LaPMuNuBR")
    LaPMuNuTot = RooFormulaVar('LaPMuNuTot','Total LaPMuNu yield','(@0*(@1*1.e-7)*(@2*1e-4))/(@3*1.e-5)',RooArgList(BkgNorm,LaPMuNuEff,LaPMuNuBR,BuJpsiK_BF))

    print ' LaPMuNu yield:', LaPMuNuTot.getVal()
    #raw_input('Check LaPMuNu, yields: ~70 per 3fb-1')

    #Fractions per BDT bins
    LaPMuNuFrac2, LaPMuNuFrac2_m, LaPMuNuFrac2_s, LaPMuNuFrac2_cons = createConst(TheTable.LbPMuNuFrac2, TheTable.LbPMuNuFrac2Err, "LaPMuNuFrac2")
    LaPMuNuFrac3, LaPMuNuFrac3_m, LaPMuNuFrac3_s, LaPMuNuFrac3_cons = createConst(TheTable.LbPMuNuFrac3, TheTable.LbPMuNuFrac3Err, "LaPMuNuFrac3")
    LaPMuNuFrac4, LaPMuNuFrac4_m, LaPMuNuFrac4_s, LaPMuNuFrac4_cons = createConst(TheTable.LbPMuNuFrac4, TheTable.LbPMuNuFrac4Err, "LaPMuNuFrac4")
    LaPMuNuFrac5, LaPMuNuFrac5_m, LaPMuNuFrac5_s, LaPMuNuFrac5_cons = createConst(TheTable.LbPMuNuFrac5, TheTable.LbPMuNuFrac5Err, "LaPMuNuFrac5")
    LaPMuNuFrac6, LaPMuNuFrac6_m, LaPMuNuFrac6_s, LaPMuNuFrac6_cons = createConst(TheTable.LbPMuNuFrac6, TheTable.LbPMuNuFrac6Err, "LaPMuNuFrac6")
    LaPMuNuFrac7, LaPMuNuFrac7_m, LaPMuNuFrac7_s, LaPMuNuFrac7_cons = createConst(TheTable.LbPMuNuFrac7, TheTable.LbPMuNuFrac7Err, "LaPMuNuFrac7")
    LaPMuNuFrac8, LaPMuNuFrac8_m, LaPMuNuFrac8_s, LaPMuNuFrac8_cons = createConst(TheTable.LbPMuNuFrac8, TheTable.LbPMuNuFrac8Err, "LaPMuNuFrac8")
    #LaPMuNuFrac1, LaPMuNuFrac1_m, LaPMuNuFrac1_s, LaPMuNuFrac1_cons = createConst(TheTable.LbPMuNuFrac1, TheTable.LbPMuNuFrac1Err, "LaPMuNuFrac1")
    LaPMuNuFrac1 = RooFormulaVar("LaPMuNuFrac1", "LaPMuNuFrac1", "(1.-@0-@1-@2-@3-@4-@5-@6)", RooArgList(LaPMuNuFrac2,LaPMuNuFrac3,LaPMuNuFrac4,LaPMuNuFrac5,LaPMuNuFrac6,LaPMuNuFrac7,LaPMuNuFrac8))

    ##Normalize the fractions
    #sum_LaPMuNuFrac = RooFormulaVar('LaPMuNuFrac_sum','Sum of all the raw LaPMuNuFrac fractions','(@0+@1+@2+@3+@4+@5+@6+@7)',RooArgList(LaPMuNuFrac1,LaPMuNuFrac2,LaPMuNuFrac3,LaPMuNuFrac4,LaPMuNuFrac5,LaPMuNuFrac6,LaPMuNuFrac7,LaPMuNuFrac8))

    #f_LaPMuNu = []
    #v = vars()
    #for i in range(1,9):
    #    f_LaPMuNu.append(RooFormulaVar("f_LaPMuNu_"+str(i),"Fr. of events in LaPMuNut bin "+str(i), "(@0/@1)", RooArgList(v["LaPMuNuFrac"+str(i)],sum_LaPMuNuFrac)))
	#print '		 f_LaPMuNu:', f_LaPMuNu[i-1].getVal()

    print '     MODEL:  . Done! \n'


print '     MODEL:   o) Import the collect all the variables to the v[] vector...'
v = vars()
print '     MODEL:  . Done! \n'

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
	print '   -. Calculate raw fraction for bin:', i
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
	print '   -. Calculate final re-normalized fraction for bin:', i
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
        print '         . N_Bs_bin = N_Bs * f_bs_i'
        self.nbs = RooFormulaVar("NBs" + i ,"NBs" + i, "(@0*@1)", RooArgList(v["nbs"],f_bs[glbin-1]))
        print '         . N_Bd_bin = N_Bs * f_bd_i'
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
            #self.kb = RooFormulaVar("MuMu_kb_"+i,"MuMu_kb_" + i,"MuMu_k_"+i + " + MuMu_dk_" + i, RooArgList(self.k,self.dk))
            self.kb = RooFormulaVar("MuMu_kb_"+i,"MuMu_kb_" + i,"@0+@1", RooArgList(self.k,self.dk))
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


        if opts.get('ADD_B2XMUNU'):
            print  prefix + '    o) Define the exclusive background: PiMuNu + KMuNu'

            #Separate yields:
            #self.nPiMuNu = RooFormulaVar("N_B0pimunu" + i, "N_B0pimunu" + i,"(@0*@1)",RooArgList(f_PiMuNu[glbin-1],v["PiMuNuTot"]))
            #self.nKMuNu = RooFormulaVar("N_B0Kmunu" + i, "N_B0Kmunu" + i,"(@0*@1)",RooArgList(f_KMuNu[glbin-1],v["KMuNuTot"]))
            #Combined yield KiMuNu + PiMuNu
            #self.nXMuNu = RooFormulaVar("N_B2Xmunu" + i, "N_B2Xmunu" + i,"(@0*@1)+(@2*@3)",RooArgList(f_PiMuNu[glbin-1],v["PiMuNuTot"],f_KMuNu[glbin-1],v["KMuNuTot"])) #Re-Normalized
            self.nXMuNu = RooFormulaVar("N_B2Xmunu" + i, "N_B2Xmunu" + i,"(@0*@1)+(@2*@3)",RooArgList(v["PiMuNuFrac"+str(glbin)],v["PiMuNuTot"],v["KMuNuFrac"+str(glbin)],v["KMuNuTot"]))

            #print ' frac of PiMuNu and KMiNu frim the Ntot:'
            #print ' = ', self.nXMuNu.getVal()
            #raw_input('OK?')

            self.XMuNu = RooPhysBkg("B2Xmunu" + i, "pdf for B0pimunu and BsKmunu "+ i, Mass, v["PiMuNuMean"+i],v["PiMuNuShc"+i],v["PiMuNuSigma"+i])

            model_yields.add(self.nXMuNu)
            model_components.add(self.XMuNu)


        if opts.get('ADD_B0UPIMUMU'):
            print  prefix + '    o) Define the exclusive background: PiMuMu'
            #self.nPiMuMu = RooFormulaVar("N_B0pimumu" + i, "N_B0pimumu" + i,"(@0*@1)",RooArgList(f_PiMuMu[glbin-1],v["PiMuMuTot"])) #ReNormalized
            self.nPiMuMu = RooFormulaVar("N_B0pimumu" + i, "N_B0pimumu" + i,"(@0*@1)",RooArgList(v["PiMuMuFrac"+str(glbin)],v["PiMuMuTot"]))
            self.PiMuMu = RooPhysBkg("B0upimumu" + i, "pdf B0upimumu "+ i, Mass, v["PiMuMuMean"+i],v["PiMuMuShc"+i],v["PiMuMuSigma"+i])
            model_yields.add(self.nPiMuMu)
            model_components.add(self.PiMuMu)
            #print ' frac of PiMuMu:', f_PiMuMu[glbin-1].getVal(), '  times the yield:',v["PiMuMuTot"].getVal()
            #print ' = ', self.nPiMuMu.getVal()
            #raw_input('OK?')


        if opts.get('ADD_LAPMUNU'):
            print  prefix + '    o) Define the exclusive background: LaPMuNu'
            #self.nLaPMuNu = RooFormulaVar("N_LaPmunu" + i, "N_LaPmunu" + i,"(@0*@1)",RooArgList(f_LaPMuNu[glbin-1],v["LaPMuNuTot"]))
            self.nLaPMuNu = RooFormulaVar("N_LaPmunu" + i, "N_LaPmunu" + i,"(@0*@1)",RooArgList(v["LaPMuNuFrac"+str(glbin)],v["LaPMuNuTot"]))
            self.LaPMuNu = RooPhysBkg("LaPmunu" + i, "pdf LaPmumu "+ i, Mass, v["LaPMuNuMean"+i],v["LaPMuNuShc"+i],v["LaPMuNuSigma"+i])
            model_yields.add(self.nLaPMuNu)
            model_components.add(self.LaPMuNu)
            #print ' frac of LaPMuNu:', f_LaPMuNu[glbin-1].getVal(), '  times the yield:',v["LaPMuNuTot"].getVal()
            #print ' = ', self.nLaPMuNu.getVal()
            #raw_input('OK?')


        print prefix + ' o) Put everything together..'
        self.model = RooAddPdf("mumu model " + i, "mumu model " + i, model_components, model_yields)
        self.model.Print('v')
        self.model.Print()
        print prefix + '  Model built! '

############################################
print '     MODEL:  . Done! \n'
print '     MODEL:  o) Building models for every BDT bin... \n'
fiter = RooSimultaneous("lhcb_pdf", "lhcb_pdf", cat)
mm = {}
for i in range(1+opts.get('USE_7_BINS'),9):
    mm[i] = BsMuMuModel(i)
    fiter.addPdf(mm[i].model,"mumu bin" + str(i))

############################################ Bs -. mm
print ' -----------------------------------------------------------------------------  \n  '
print '     MODEL has been built \n'
fiter.Print('v')
fiter.Print()
print ' -----------------------------------------------------------------------------  \n  '
print '     o) Link the BDT Bin models to the BDT categories...\n'

if not opts.get('USE_7_BINS'): mumuDataLG = RooDataSet("mumu data Low GL", "mumu data Low GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin1", BDT_data[1]), RooFit.Import("mumu bin2", BDT_data[2]), RooFit.Import("mumu bin3", BDT_data[3]),RooFit.Import("mumu bin4", BDT_data[4]))

else: mumuDataLG = RooDataSet("mumu data Low GL", "mumu data Low GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin2", BDT_data[2]), RooFit.Import("mumu bin3", BDT_data[3]),RooFit.Import("mumu bin4", BDT_data[4]))

mumuDataHG_4 = RooDataSet("mumu data High GL", "mumu data High GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin5", BDT_data[5]), RooFit.Import("mumu bin6", BDT_data[6]), RooFit.Import("mumu bin7", BDT_data[7]),RooFit.Import("mumu bin8", BDT_data[8]))
mumuDataHG_3 = RooDataSet("mumu data High GL", "mumu data High GL", RooArgSet(Mass), RooFit.Index(cat), RooFit.Import("mumu bin6", BDT_data[6]), RooFit.Import("mumu bin7", BDT_data[7]),RooFit.Import("mumu bin8", BDT_data[8]))

allData = mumuDataLG.Clone() #RooDataSet("all data","all data", RooArgSet(Mass,cat), RooFit.Import(hhData), RooFit.Import(mumuData))
allData.append(mumuDataHG_4)
allData.SetNameTitle('lhcb_data','lhcb_data')

print '  . Done! \n'
print '     o) Add the onstraints to the model...\n'

summaryConstraints = RooArgSet()

if opts.get('ADD_MISID_NTOT_CONST'):
    print '         Constrain: Total MisID Yield'
    #summaryConstraints = RooArgSet(nmis_cons)
    summaryConstraints.add(RooArgSet(nmis_cons))

if opts.get('ADD_TIMEACCCORR_CONST'):
    print '         Constrain: Time Acceptance Corrections'
    summaryConstraints.add(RooArgSet(timeAccCorrBs_cons, timeAccCorrBd_cons))

print '         Constrain: Normalization parameters'
if opts.get('ADD_ALPHA_CONST'):
    summaryConstraints.add(RooArgSet(alpha_Bu_cons, alpha_KPi_cons))

if opts.get('ADD_BDKPI_BF_CONST'):
    summaryConstraints.add(RooArgSet(BdKpi_BF_cons))

if opts.get('ADD_BUJPSIK_BF_CONST'):
    summaryConstraints.add(RooArgSet(BuJpsiK_BF_cons))

if opts.get('ADD_FDFS_CONST'):
    summaryConstraints.add(RooArgSet(fdfs_cons))

if opts.get('ADD_SIGSHAPE_CONST'):
    print '         Constrain: Signal mass shape parameters'
    summaryConstraints.add(RooArgSet(sigmaBs_cons ,sigmaBd_cons,meanBd_cons,meanBs_cons, a_cons, n_cons))

if opts.get('ADD_BDT_FRAC_CONST'):
    print '         Constrain: Signal BDT fractions'
    #summaryConstraints.add(RooArgSet(BDT_f2_cons, BDT_f3_cons, BDT_f4_cons, BDT_f5_cons, BDT_f6_cons, BDT_f7_cons, BDT_f8_cons))
    summaryConstraints.add(RooArgSet(BDT_f1_cons, BDT_f2_cons, BDT_f3_cons, BDT_f4_cons, BDT_f5_cons, BDT_f6_cons, BDT_f7_cons, BDT_f8_cons))

if opts.get('ADD_BKGNORM_CONST'):
    summaryConstraints.add(RooArgSet(BkgNorm_cons))

if opts.get('ADD_BUJPSIK_BF_CONST'):
    summaryConstraints.add(RooArgSet(BuJpsiK_BF_cons))

if opts.get('ADD_B2XMUNU_SHAPE_CONST'):
    print '         Constrain: PiMuNu shape parameters'
    summaryConstraints.add(RooArgSet(PiMuNuSigma1_cons,PiMuNuSigma2_cons,PiMuNuSigma3_cons,PiMuNuSigma4_cons,PiMuNuSigma5_cons,PiMuNuSigma6_cons,PiMuNuSigma7_cons, PiMuNuSigma8_cons))
    summaryConstraints.add(RooArgSet(PiMuNuMean1_cons,PiMuNuMean2_cons,PiMuNuMean3_cons,PiMuNuMean4_cons,PiMuNuMean5_cons,PiMuNuMean6_cons,PiMuNuMean7_cons, PiMuNuMean8_cons))
    summaryConstraints.add(RooArgSet(PiMuNuShc1_cons,PiMuNuShc2_cons,PiMuNuShc3_cons,PiMuNuShc4_cons,PiMuNuShc5_cons,PiMuNuShc6_cons,PiMuNuShc7_cons, PiMuNuShc8_cons))

if opts.get('ADD_B2XMUNU_YIELD_CONST'):
    print '         Constrain: PiMuNu yield parameters'
    #summaryConstraints.add(RooArgSet(PiMuNuFrac1_cons,PiMuNuFrac2_cons,PiMuNuFrac3_cons,PiMuNuFrac4_cons,PiMuNuFrac5_cons,PiMuNuFrac6_cons,PiMuNuFrac7_cons, PiMuNuFrac8_cons))
    summaryConstraints.add(RooArgSet(PiMuNuFrac2_cons,PiMuNuFrac3_cons,PiMuNuFrac4_cons,PiMuNuFrac5_cons,PiMuNuFrac6_cons,PiMuNuFrac7_cons, PiMuNuFrac8_cons))
    summaryConstraints.add(RooArgSet(PiMuNuEff_cons,PiMuNuBR_cons))

    print '         Constrain: KMuNu yield parameters'
    #summaryConstraints.add(RooArgSet(KMuNuFrac1_cons,KMuNuFrac2_cons,KMuNuFrac3_cons,KMuNuFrac4_cons,KMuNuFrac5_cons,KMuNuFrac6_cons,KMuNuFrac7_cons, KMuNuFrac8_cons)) #Fixed! (Ambiguous otherwise)
    summaryConstraints.add(RooArgSet(KMuNuFrac2_cons,KMuNuFrac3_cons,KMuNuFrac4_cons,KMuNuFrac5_cons,KMuNuFrac6_cons,KMuNuFrac7_cons, KMuNuFrac8_cons)) #Fixed! (Ambiguous otherwise)
    summaryConstraints.add(RooArgSet(KMuNuEff_cons,KMuNuBR_cons))


if opts.get('ADD_B0UPIMUMU_SHAPE_CONST'):

    print '         Constrain: PiMuMu shape parameters'
    summaryConstraints.add(RooArgSet(PiMuMuSigma1_cons,PiMuMuSigma2_cons,PiMuMuSigma3_cons,PiMuMuSigma4_cons,PiMuMuSigma5_cons,PiMuMuSigma6_cons,PiMuMuSigma7_cons, PiMuMuSigma8_cons))
    summaryConstraints.add(RooArgSet(PiMuMuMean1_cons,PiMuMuMean2_cons,PiMuMuMean3_cons,PiMuMuMean4_cons,PiMuMuMean5_cons,PiMuMuMean6_cons,PiMuMuMean7_cons, PiMuMuMean8_cons))
    summaryConstraints.add(RooArgSet(PiMuMuShc1_cons,PiMuMuShc2_cons,PiMuMuShc3_cons,PiMuMuShc4_cons,PiMuMuShc5_cons,PiMuMuShc6_cons,PiMuMuShc7_cons, PiMuMuShc8_cons))

if opts.get('ADD_B0UPIMUMU_YIELD_CONST'):
    print '         Constrain: PiMuMu yield parameters'
    summaryConstraints.add(RooArgSet(PiMuMuEff_cons,PiMuMuBR_cons))
    #summaryConstraints.add(RooArgSet(PiMuMuFrac1_cons,PiMuMuFrac2_cons,PiMuMuFrac3_cons,PiMuMuFrac4_cons,PiMuMuFrac5_cons,PiMuMuFrac6_cons,PiMuMuFrac7_cons, PiMuMuFrac8_cons))
    summaryConstraints.add(RooArgSet(PiMuMuFrac2_cons,PiMuMuFrac3_cons,PiMuMuFrac4_cons,PiMuMuFrac5_cons,PiMuMuFrac6_cons,PiMuMuFrac7_cons, PiMuMuFrac8_cons))

if opts.get('ADD_LAPMUNU_SHAPE_CONST'):
    print '         Constrain: LaPMuNu shape parameters'
    summaryConstraints.add(RooArgSet(LaPMuNuSigma1_cons,LaPMuNuSigma2_cons,LaPMuNuSigma3_cons,LaPMuNuSigma4_cons,LaPMuNuSigma5_cons,LaPMuNuSigma6_cons,LaPMuNuSigma7_cons, LaPMuNuSigma8_cons))
    summaryConstraints.add(RooArgSet(LaPMuNuMean1_cons,LaPMuNuMean2_cons,LaPMuNuMean3_cons,LaPMuNuMean4_cons,LaPMuNuMean5_cons,LaPMuNuMean6_cons,LaPMuNuMean7_cons, LaPMuNuMean8_cons))
    summaryConstraints.add(RooArgSet(LaPMuNuShc1_cons,LaPMuNuShc2_cons,LaPMuNuShc3_cons,LaPMuNuShc4_cons,LaPMuNuShc5_cons,LaPMuNuShc6_cons,LaPMuNuShc7_cons, LaPMuNuShc8_cons))

if opts.get('ADD_LAPMUNU_YIELD_CONST'):
    print '         Constrain: LaPMuNu yield parameters'
    #summaryConstraints.add(RooArgSet(LaPMuNuFrac1_cons,LaPMuNuFrac2_cons,LaPMuNuFrac3_cons,LaPMuNuFrac4_cons,LaPMuNuFrac5_cons,LaPMuNuFrac6_cons,LaPMuNuFrac7_cons, LaPMuNuFrac8_cons))
    summaryConstraints.add(RooArgSet(LaPMuNuFrac2_cons,LaPMuNuFrac3_cons,LaPMuNuFrac4_cons,LaPMuNuFrac5_cons,LaPMuNuFrac6_cons,LaPMuNuFrac7_cons, LaPMuNuFrac8_cons))
    summaryConstraints.add(RooArgSet(LaPMuNuEff_cons,LaPMuNuBR_cons))

print '  . Done! \n'

#Get all the parameters
params = fiter.getParameters(allData)

print '     o) Read the parameters from file......\n'  #### ??
if not opts.get('LOAD_PARAMS_FROM')==0:
    params.readFromFile(opts.get('LOAD_PARAMS_FROM'))
    print ' Load params from : ', opts.get('LOAD_PARAMS_FROM')
    raw_input('Parameters read from file...')


print '     o) Fix the following parameters......\n'

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



if opts.get('FIX_BKGNORM'):
    fixParams += ['BkgNorm']

if opts.get('FIX_BUJPSIK_BF'):
    fixParams += ['BuJpsiK_BF']

if opts.get('FIX_BDKPI_BF'):
    fixParams += ['BdKpi_BF']

if opts.get('FIX_B2XMUNU'):
    print '        Fix: PiMuNu shape parameters'
    fixParams += ['PiMuNuSigma1','PiMuNuSigma2','PiMuNuSigma3','PiMuNuSigma4','PiMuNuSigma5','PiMuNuSigma6','PiMuNuSigma7', 'PiMuNuSigma8']
    fixParams += ['PiMuNuMean1','PiMuNuMean2','PiMuNuMean3','PiMuNuMean4','PiMuNuMean5','PiMuNuMean6','PiMuNuMean7','PiMuNuMean8']
    fixParams += ['PiMuNuShc1','PiMuNuShc2','PiMuNuShc3','PiMuNuShc4','PiMuNuShc5','PiMuNuShc6','PiMuNuShc7','PiMuNuShc8']
    #fixParams += ['PiMuNuShc1','PiMuNuShc2','PiMuNuShc3','PiMuNuShc4shift','PiMuNuShc5','PiMuNuShc6','PiMuNuShc7','PiMuNuShc8']
    #fixParams += ['PiMuNuFrac1','PiMuNuFrac2','PiMuNuFrac3','PiMuNuFrac4','PiMuNuFrac5','PiMuNuFrac6','PiMuNuFrac7','PiMuNuFrac8']
    fixParams += ['PiMuNuFrac2','PiMuNuFrac3','PiMuNuFrac4','PiMuNuFrac5','PiMuNuFrac6','PiMuNuFrac7','PiMuNuFrac8']
    fixParams += ['PiMuNuEff','PiMuNuBR']
    fixParams += ['KMuNuFrac2','KMuNuFrac3','KMuNuFrac4','KMuNuFrac5','KMuNuFrac6','KMuNuFrac7','KMuNuFrac8']
    fixParams += ['KMuNuEff','KMuNuBR']

if opts.get('FIX_PIMUNU_SIGMA'):
    fixParams += ['PiMuNuSigma1','PiMuNuSigma2','PiMuNuSigma3','PiMuNuSigma4','PiMuNuSigma5','PiMuNuSigma6','PiMuNuSigma7', 'PiMuNuSigma8']
if opts.get('FIX_PIMUNU_MEAN'):
    fixParams += ['PiMuNuMean1','PiMuNuMean2','PiMuNuMean3','PiMuNuMean4','PiMuNuMean5','PiMuNuMean6','PiMuNuMean7','PiMuNuMean8']
if opts.get('FIX_PIMUNU_SHC'):
    fixParams += ['PiMuNuShc1','PiMuNuShc2','PiMuNuShc3','PiMuNuShc4','PiMuNuShc5','PiMuNuShc6','PiMuNuShc7','PiMuNuShc8']
if opts.get('FIX_PIMUNU_EFF_BR'):
    fixParams += ['PiMuNuEff','PiMuNuBR']
if opts.get('FIX_PIMUNU_FRAC'):
    fixParams += ['PiMuNuFrac2','PiMuNuFrac3','PiMuNuFrac4','PiMuNuFrac5','PiMuNuFrac6','PiMuNuFrac7','PiMuNuFrac8']

if opts.get('FIX_KMUNU_EFF_BR'):
    fixParams += ['KMuNuEff','KMuNuBR']
if opts.get('FIX_KMUNU_FRAC'):
    fixParams += ['KMuNuFrac2','KMuNuFrac3','KMuNuFrac4','KMuNuFrac5','KMuNuFrac6','KMuNuFrac7','KMuNuFrac8']


if opts.get('FIX_B0UPIMUMU'):
    print '        Fix: PiMuMu shape parameters'
    fixParams += ['PiMuMuSigma1','PiMuMuSigma2','PiMuMuSigma3','PiMuMuSigma4','PiMuMuSigma5','PiMuMuSigma6','PiMuMuSigma7', 'PiMuMuSigma8']
    fixParams += ['PiMuMuMean1','PiMuMuMean2','PiMuMuMean3','PiMuMuMean4','PiMuMuMean5','PiMuMuMean6','PiMuMuMean7','PiMuMuMean8']
    fixParams += ['PiMuMuShc1','PiMuMuShc2','PiMuMuShc3','PiMuMuShc4','PiMuMuShc5','PiMuMuShc6','PiMuMuShc7','PiMuMuShc8']
    #fixParams += ['PiMuMuFrac1','PiMuMuFrac2','PiMuMuFrac3','PiMuMuFrac4','PiMuMuFrac5','PiMuMuFrac6','PiMuMuFrac7','PiMuMuFrac8']
    fixParams += ['PiMuMuFrac2','PiMuMuFrac3','PiMuMuFrac4','PiMuMuFrac5','PiMuMuFrac6','PiMuMuFrac7','PiMuMuFrac8']
    fixParams += ['PiMuMuEff','PiMuMuBR']

if opts.get('FIX_B0UPIMUMU_SIGMA'):
    fixParams += ['PiMuMuSigma1','PiMuMuSigma2','PiMuMuSigma3','PiMuMuSigma4','PiMuMuSigma5','PiMuMuSigma6','PiMuMuSigma7', 'PiMuMuSigma8']
if opts.get('FIX_B0UPIMUMU_MEAN'):
    fixParams += ['PiMuMuMean1','PiMuMuMean2','PiMuMuMean3','PiMuMuMean4','PiMuMuMean5','PiMuMuMean6','PiMuMuMean7','PiMuMuMean8']
if opts.get('FIX_B0UPIMUMU_SHC'):
    fixParams += ['PiMuMuShc1','PiMuMuShc2','PiMuMuShc3','PiMuMuShc4','PiMuMuShc5','PiMuMuShc6','PiMuMuShc7','PiMuMuShc8']
if opts.get('FIX_B0UPIMUMU_EFF_BR'):
    fixParams += ['PiMuMuEff','PiMuMuBR']
if opts.get('FIX_B0UPIMUMU_FRAC'):
    fixParams += ['PiMuMuFrac2','PiMuMuFrac3','PiMuMuFrac4','PiMuMuFrac5','PiMuMuFrac6','PiMuMuFrac7','PiMuMuFrac8']

if opts.get('FIX_LAPMUNU'):
    print '        Fix: LaPMuNu shape parameters'
    fixParams += ['LaPMuNuSigma1','LaPMuNuSigma2','LaPMuNuSigma3','LaPMuNuSigma4','LaPMuNuSigma5','LaPMuNuSigma6','LaPMuNuSigma7', 'LaPMuNuSigma8']
    fixParams += ['LaPMuNuMean1','LaPMuNuMean2','LaPMuNuMean3','LaPMuNuMean4','LaPMuNuMean5','LaPMuNuMean6','LaPMuNuMean7','LaPMuNuMean8']
    fixParams += ['LaPMuNuShc1','LaPMuNuShc2','LaPMuNuShc3','LaPMuNuShc4','LaPMuNuShc5','LaPMuNuShc6','LaPMuNuShc7','LaPMuNuShc8']
    #fixParams += ['LaPMuNuFrac1','LaPMuNuFrac2','LaPMuNuFrac3','LaPMuNuFrac4','LaPMuNuFrac5','LaPMuNuFrac6','LaPMuNuFrac7','LaPMuNuFrac8']
    fixParams += ['LaPMuNuFrac2','LaPMuNuFrac3','LaPMuNuFrac4','LaPMuNuFrac5','LaPMuNuFrac6','LaPMuNuFrac7','LaPMuNuFrac8']
    fixParams += ['LaPMuNuEff','LaPMuNuBR']

if opts.get('FIX_LAPMUNU_SIGMA'):
    fixParams += ['LaPMuNuSigma1','LaPMuNuSigma2','LaPMuNuSigma3','LaPMuNuSigma4','LaPMuNuSigma5','LaPMuNuSigma6','LaPMuNuSigma7', 'LaPMuNuSigma8']
if opts.get('FIX_LAPMUNU_MEAN'):
    fixParams += ['LaPMuNuMean1','LaPMuNuMean2','LaPMuNuMean3','LaPMuNuMean4','LaPMuNuMean5','LaPMuNuMean6','LaPMuNuMean7','LaPMuNuMean8']
if opts.get('FIX_LAPMUNU_SHC'):
    fixParams += ['LaPMuNuShc1','LaPMuNuShc2','LaPMuNuShc3','LaPMuNuShc4','LaPMuNuShc5','LaPMuNuShc6','LaPMuNuShc7','LaPMuNuShc8']
if opts.get('FIX_LAPMUNU_EFF_BR'):
    fixParams += ['LaPMuNuEff','LaPMuNuBR']
if opts.get('FIX_LAPMUNU_FRAC'):
    fixParams += ['LaPMuNuFrac2','LaPMuNuFrac3','LaPMuNuFrac4','LaPMuNuFrac5','LaPMuNuFrac6','LaPMuNuFrac7','LaPMuNuFrac8']


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
    print '   -------      '
    print '   ------------      '
    print '   --------------------      '
    print '   ExternalConstraints:'
    summaryConstraints.Print()
    print '   -------      '
    print '   ------------      '
    print '   --------------------      '
    print '   FixTerms:'
    for pname in fixParams:
        p = params[pname]
        p.setConstant()
        print '     Fixed:', p.GetName()
        print '     @ ', p.getVal()
        print '  --------------------------------'

    if opts.get('FIXFITMODEL'):
        print '  --------------------------------'
        print '   Fixed all the fit parameters!\n'
        print '  --------------------------------'
    raw_input('Continue...?')


wsp = 0
if opts.get('SAVE_WORKSPACE'):

    print '     o) Save a workspace ...\n'
    wsp = RooWorkspace("lhcb_ws","lhcb_ws")

    print '     ... import pdf\n'
    fiter.SetNameTitle('lhcb_pdf','lhcb_pdf')
    getattr(wsp,'import')(fiter) #lhcb_pdf

    print '     ... import data\n'
    #allData.SetNameTitle('lhcb_data','lhcb_data') #Set before, matters also in createNLL part when you want to get the model component.
    getattr(wsp,'import')(allData) #lhcb_data

    print '     ... import constraints\n'
    summaryConstraints.Print("v")
    summaryConstraints.setName('lhcb_cons')
    getattr(wsp,'import')(summaryConstraints) #summaryConstraints
    getattr(wsp,'defineSet')('lhcb_cons',summaryConstraints) #summaryConstraints

    print 'Print the problematic observables:'
    wsp.Print()

    wsp.var(opts.get('massname')).Print('v')
    wsp.cat(samplename).Print('v')


    #Make a default model config object
    #modelConfig = RooStats.ModelConfig("ModelConfig",wsp)
    #modelConfig.SetPdf(fiter)
    #modelConfig.SetConstraintParameters(summaryConstraints)
    #modelConfig.SetObservables(RooArgSet(wsp.var(opts.get('massname')) , wsp.cat(samplename)))
    #modelConfig_BRs.SetParametersOfInterest(RooArgSet(wsp.var('BRs'),wsp.var('BRd')))
    #getattr(wsp,'import')(modelConfig)

    name = opts.get('RESULTDIR')+'lhcb_ws.root'
    wsp.writeToFile(name)



if opts.get('SAVE_START_PARAMS'):
    name = opts.get('RESULTDIR')+'LHCB_START_PARAMS.txt'
    params.writeToFile(name)

#Do the fitting
if opts.get('FIT_MODEL'):

    #List of arguments
    arg_list = RooLinkedList()
    arg_list.Add(RooFit.ExternalConstraints(RooArgSet(summaryConstraints)))

    if opts.get('FIT_WITH_OFFSET'):
        #Fit withOffset
        arg_list.Add(RooFit.Offset(True))
    else:
        raw_input('Fit without Offset() ?')
        arg_list.Add(RooFit.Offset(False))


    if opts.get('FIT_WITH_OPTIMIZE'):
        arg_list.Add(RooFit.Optimize(1))
    else:
        raw_input('Fit without Optimize() ?')
        arg_list.Add(RooFit.Optimize(0))


    #arg_list.Add(RooFit.Minos(kTRUE)) #Gets MINOS errors for every param
    arg_list.Add(RooFit.Minos(RooArgSet(BR_s,BR_d)))
    arg_list.Add(RooFit.Strategy(2))

    #arg_list.Add(RooFit.Verbose(kTRUE))
    #arg_list.Add(RooFit.PrintLevel(3))
    arg_list.Add(RooFit.Hesse(1))

    if opts.get('FIT_WITH_CPU_8'):
        arg_list.Add(RooFit.NumCPU(8))
    else:
        raw_input('Fit with CPU=1 ?')
        arg_list.Add(RooFit.NumCPU(1))


    #fiter.fitTo(allData,RooFit.Minos(kTRUE), RooFit.ExternalConstraints(RooArgSet(summaryConstraints)),RooFit.Strategy(2), RooFit.NumCPU(8), RooFit.Verbose(kTRUE), RooFit.Offset(True), RooFit.Hesse(1), RooFit.Minos(RooArgSet(BR_s,BR_d))) #Like CMS

    arg_list.Add(RooFit.Save()) #Save result

    #Store the NLL result before the fit
    nll = fiter.createNLL(allData, arg_list)

    nll.Print()
    nll_val_bef = nll.getVal()
    nll_model = nll.getComponents()['nll_lhcb_pdf_lhcb_data'] #the part without constraints
    #nll_model.Print() #RooAddition::nll_lhcb_pdf__with_constr[ nll_lhcb_pdf_ + nll_lhcb_pdf__constr ] = 201650
    #model_comp = nll_model.getComponents()
    #model_comp.Print()
    #raw_input('model_comp.Print()')

    nll_model_val_bef = nll_model.getVal()
    isOff = nll_model.isOffsetting()
    nll_offset_bef = nll_model.offset()
    nll_offCarry_bef = nll_model.offsetCarry()

    #Do the fit
    fitResult =  fiter.fitTo(allData, arg_list)

    # Open new ROOT file save save result
    name = opts.get('RESULTDIR')+'fitResult.root'
    fRes = TFile(name,"RECREATE")
    fitResult.Write("fitResult")
    fRes.Close()

    #In a clean ROOT session retrieve the persisted fit result as follows:
    #RooFitResult* r = gDirectory->Get("rf607") ;

    print '  . FIT HAS CONVERGED! \n'


    nll_val = nll.getVal()
    nll_model_val = nll_model.getVal()
    nll_offset = nll_model.offset()
    nll_offCarry= nll_model.offsetCarry()
    minFCN = fitResult.minNll() #Get the minimum from the fit
    fitEDM = fitResult.edm() #Get the minimum from the fit

    fileName = opts.get('RESULTDIR')+'logLikelihoodValues.txt'
    f = open(fileName,'w')
    print >> f, '#----------------------------------------#'
    print >> f, '  This is the -log(L) before the fit:'
    print >> f, '   nll = pdf.createNLL(..ExternalConstraints()..)'
    print >> f, '   -log(L) = nll.getVal()      = ', nll_val_bef
    print >> f, '   -log(L) = nll_model.getVal()      = ', nll_model_val_bef
    print >> f, '             nll_model.isOffsettinf()= ', isOff
    print >> f, '             nll_model.offset()      = ', nll_offset_bef
    print >> f, '             nll_model.offsetCarry() = ', nll_offCarry_bef
    print >> f, '#----------------------------------------#'
    print >> f, '  This is the -log(L) of the fitted model:'
    print >> f, '   nll = pdf.createNLL(..ExternalConstraints()..)'
    print >> f, '   -log(L) = nll.getVal()      = ', nll_val
    print >> f, '   -log(L) = nll_model.getVal()      = ', nll_model_val
    print >> f, '             nll_model.offset()      = ', nll_offset
    print >> f, '             nll_model.offsetCarry() = ', nll_offCarry
    print >> f, '   fitResult.minNll()          = ', minFCN
    print >> f, '   fitResult.edm()          = ', fitEDM
    print >> f, '#----------------------------------------#'
    print >> f, ' BRs = ', BR_s.getVal(), ' +- ', BR_s.getError()
    print >> f, ' BRd = ', BR_d.getVal(), ' +- ', BR_d.getError()
    print >> f, '#----------------------------------------#'
    print >> f, '  This is the configuration for the fit:'
    for name, val in opts.items():
        print >> f, '  o) '+str(name)+' : '+str(val)
    print >> f, '#----------------------------------------#'
    f.close()
    content =  open(fileName).read()
    print content
    #raw_input('ok?')

if opts.get('SAVE_FIT_PARAMS'):
    #Write parameters to file
    params.writeToFile("LHCB_FIT_PARAMS.txt")

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

for i in range(1+opts.get('USE_7_BINS'),9):
       print >> f, ' N_Bs'+str(i), mm[i].nbs.getVal()#, ' +- ', mm[i].nXMuNu.getError()

for i in range(1+opts.get('USE_7_BINS'),9):
       print >> f, ' N_Bd'+str(i), mm[i].nbd.getVal()#, ' +- ', mm[i].nXMuNu.getError()

for i in range(1+opts.get('USE_7_BINS'),9):
       print >> f, ' N_misID'+str(i), mm[i].nmis.getVal()#, ' +- ', mm[i].nXMuNu.getError()

if opts.get('ADD_B2XMUNU'):
    for i in range(1+opts.get('USE_7_BINS'),9):
       print >> f, ' N_B2XMuNu'+str(i), mm[i].nXMuNu.getVal()#, ' +- ', mm[i].nXMuNu.getError()
#       print >> f, ' f_PiMuNu'+str(i), f_PiMuNu[i-1].getVal()
#       print >> f, ' f_KMuNu'+str(i), f_KMuNu[i-1].getVal()

if opts.get('ADD_B0UPIMUMU'):
    for i in range(1+opts.get('USE_7_BINS'),9):
       print >> f, ' N_PiMuMu'+str(i), mm[i].nPiMuMu.getVal()#, ' +- ', mm[i].nPiMuMu.getError()
#       print >> f, ' f_PiMuMu'+str(i), f_PiMuMu[i-1].getVal()

if opts.get('ADD_LAPMUNU'):
    for i in range(1+opts.get('USE_7_BINS'),9):
       print >> f, ' N_LaPmunu '+str(i), mm[i].nLaPMuNu.getVal()#, ' +- ', mm[i].nPiMuMu.getError()

print >> f, '#----------------------------------------#'


f.close()
content =  open(fileName).read()
print content
#####################################################################################


if opts.get('FITANDPLOT'):
    print ' o) Save the fitted parameters to a file..'
    fiter.getParameters(allData).writeToFile(opts.get('RESULTDIR')+'FitModel_PARAMETERS.txt')

    print '  . Done! \n'
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
     gPad.SetLeftMargin(0.3)

     fr[i] = Mass.frame()
     BDT_data[i].plotOn(fr[i], RooFit.Binning(binning), RooFit.Invisible())
     mm[i].model.plotOn(fr[i])
     mm[i].model.plotOn(fr[i], RooFit.Components("model Bs"+str(i)),RooFit.LineColor(kRed),RooFit.LineStyle(9), RooFit.FillColor(kRed), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))
     mm[i].model.plotOn(fr[i], RooFit.Components("model Bd"+str(i)),RooFit.LineColor(kGreen),RooFit.LineStyle(7), RooFit.FillColor(kGreen), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))
     mm[i].model.plotOn(fr[i], RooFit.Components("missid"+str(i)),RooFit.LineColor(kMagenta),RooFit.LineStyle(kDotted), RooFit.FillColor(kMagenta), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))
     if opts.get('ADD_B2XMUNU'):
        mm[i].model.plotOn(fr[i], RooFit.Components("B2Xmunu"+str(i)),RooFit.LineColor(kBlack),RooFit.LineStyle(kDotted), RooFit.FillColor(kBlack), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))
     if opts.get('ADD_LAPMUNU'):
        mm[i].model.plotOn(fr[i], RooFit.Components("LaPmunu"+str(i)),RooFit.LineColor(kOrange),RooFit.LineStyle(kDotted), RooFit.FillColor(kOrange), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))
     if opts.get('ADD_B0UPIMUMU'):
        mm[i].model.plotOn(fr[i], RooFit.Components("B0upimumu"+str(i)),RooFit.LineColor(kCyan),RooFit.LineStyle(kDotted), RooFit.FillColor(kCyan), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

     BDT_data[i].plotOn(fr[i], RooFit.Binning(binning))

     fr[i].GetXaxis().SetTitle("m_{#mu#mu} ( MeV/c^{2} )")
     fr[i].SetTitle("B_{s}^{0}#rightarrow#mu^{+}#mu^{-} candidates, BIN [" + str(Binning[opts.get('bdtname')][i-1]) + ", " +str(Binning[opts.get('bdtname')][i])+"]" )

     fr[i].GetYaxis().SetTitleOffset(1.1)
     fr[i].GetYaxis().SetTitle("Events /( "+str(int(size))+" MeV/c^{2} )")
     #else: fr[i].GetYaxis().SetTitleOffset(1.6)
     fr[i].Draw()

    c.SaveAs(opts.get('RESULTDIR')+'MassFitInBDTBins.ps')
    c.SaveAs(opts.get('RESULTDIR')+'MassFitInBDTBins.root')

    print '  . Done! \n'


if opts.get('PLOT_HIGH_BDT_BINS'):

    print '  . Done! \n'
    print '     o) Plot the fit in evety BDT bin...\n'

    c = TCanvas()
    binning = 24
    size = (Mass.getMax()-Mass.getMin())*1./binning

    #Build component name
    def getComp(name): return str(name)+"5," + str(name) + "6," + str(name) + "7," + str(name) + "8"

    print ' -------------------------- '
    print '  Plotting HIGH BDT bins:'
    print ' -------------------------- '

    fr = Mass.frame()
    bdtBinData = mumuDataHG_3
    bdtBinData.plotOn(fr, RooFit.Binning(binning), RooFit.Invisible())

    #fiter.plotOn(fr)
    #fiter.plotOn(fr, RooFit.Slice(cat, "mumu bin1", RooFit.ProjWData(bdtBinData))
    fiter.plotOn(fr, RooFit.ProjWData(bdtBinData))
    #Combinatorial bkg, dotted
    #fiter.plotOn(fr, RooFit.Components(getComp("bkg1 MuMu model")),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted), RooFit.FillColor(9), RooFit.FillStyle(1001), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))

    #Signal, filled
    fiter.plotOn(fr, RooFit.Components(getComp("model Bs")),RooFit.LineColor(kRed),RooFit.LineStyle(1), RooFit.FillColor(kRed), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))
    fiter.plotOn(fr, RooFit.Components(getComp("model Bd")),RooFit.LineColor(kGreen),RooFit.LineStyle(7), RooFit.FillColor(kGreen), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))

    if opts.get('ADD_B2XMUNU'):
       fiter.plotOn(fr, RooFit.Components(getComp("B2Xmunu")),RooFit.LineColor(kBlack),RooFit.LineStyle(kDotted), RooFit.FillColor(kBlack), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))
    if opts.get('ADD_LAPMUNU'):
       fiter.plotOn(fr, RooFit.Components(getComp("LaPmunu")),RooFit.LineColor(kOrange),RooFit.LineStyle(kDotted), RooFit.FillColor(kOrange), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))
    if opts.get('ADD_B0UPIMUMU'):
       fiter.plotOn(fr, RooFit.Components(getComp("B0upimumu")),RooFit.LineColor(kCyan),RooFit.LineStyle(kDotted), RooFit.FillColor(kCyan), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))

    fiter.plotOn(fr, RooFit.Components(getComp("missid")),RooFit.LineColor(kMagenta),RooFit.LineStyle(kDotted), RooFit.FillColor(kMagenta), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))

    bdtBinData.plotOn(fr, RooFit.Binning(binning))

    fr.GetXaxis().SetTitle("m_{#mu#mu} ( MeV/c^{2} )")
    fr.SetTitle("B_{s}^{0}#rightarrow#mu^{+}#mu^{-} candidates BDT>0.?")

    gPad.SetLeftMargin(0.16)
    fr.GetYaxis().SetTitleOffset(1.1)
    fr.GetYaxis().SetTitle("Events /( "+str(int(size))+" MeV/c^{2} )")
    #else: fr[i].GetYaxis().SetTitleOffset(1.6)
    fr.Draw()

    c.SaveAs(opts.get('RESULTDIR')+'MassFitIn_High_BDTBins.ps')
    c.SaveAs(opts.get('RESULTDIR')+'MassFitIn_High_BDTBins.root')

    print '  . Done! \n'

if opts.get('PLOT_ALL_BDT_BINS'):

    print '  . Done! \n'
    print '     o) Plot the fit in evety BDT bin...\n'

    c = TCanvas()
    binning = 24
    size = (Mass.getMax()-Mass.getMin())*1./binning

    #Build component name
    #def getComp(name): return str(name)+"5," + str(name) + "6," + str(name) + "7," + str(name) + "8"
    def getComp(name): return str(name)+"1," +str(name)+"2," +str(name)+"3," +str(name)+"4," +    str(name)+"5," + str(name) + "6," + str(name) + "7," + str(name) + "8"

    print ' -------------------------- '
    print '  Plotting ALL BDT bins:'
    print ' -------------------------- '

    fr1 = Mass.frame()
    bdtBinData = allData

    # Save one without the fit
    bdtBinData.plotOn(fr1, RooFit.Binning(binning))
    fr1.GetXaxis().SetTitle("m_{#mu#mu} ( MeV/c^{2} )")
    fr1.SetTitle("B_{s}^{0}#rightarrow#mu^{+}#mu^{-} candidates BDT>0.?")
    gPad.SetLeftMargin(0.16)
    fr1.GetYaxis().SetTitleOffset(1.1)
    fr1.GetYaxis().SetTitle("Events /( "+str(int(size))+" MeV/c^{2} )")
    fr1.Draw()
    c.SaveAs(opts.get('RESULTDIR')+'MassFitIn_AllBDTBins_OnlyData.ps')
    c.SaveAs(opts.get('RESULTDIR')+'MassFitIn_AllBDTBins_OnlyData.root')

    # Plot the data with the fit
    fr = Mass.frame()
    bdtBinData.plotOn(fr, RooFit.Binning(binning), RooFit.Invisible())

    fiter.plotOn(fr, RooFit.ProjWData(bdtBinData))
    #Combinatorial bkg, dotted
    #fiter.plotOn(fr, RooFit.Components(getComp("bkg1 MuMu model")),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted), RooFit.FillColor(9), RooFit.FillStyle(1001), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))

    #Signal, filled
    fiter.plotOn(fr, RooFit.Components(getComp("model Bs")),RooFit.LineColor(kRed),RooFit.LineStyle(1), RooFit.FillColor(kRed), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))
    fiter.plotOn(fr, RooFit.Components(getComp("model Bd")),RooFit.LineColor(kGreen),RooFit.LineStyle(7), RooFit.FillColor(kGreen), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))

    if opts.get('ADD_B2XMUNU'):
       fiter.plotOn(fr, RooFit.Components(getComp("B2Xmunu")),RooFit.LineColor(kBlack),RooFit.LineStyle(kDotted), RooFit.FillColor(kBlack), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))
    if opts.get('ADD_LAPMUNU'):
       fiter.plotOn(fr, RooFit.Components(getComp("LaPmunu")),RooFit.LineColor(kOrange),RooFit.LineStyle(kDotted), RooFit.FillColor(kOrange), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))
    if opts.get('ADD_B0UPIMUMU'):
       fiter.plotOn(fr, RooFit.Components(getComp("B0upimumu")),RooFit.LineColor(kCyan),RooFit.LineStyle(kDotted), RooFit.FillColor(kCyan), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))

    fiter.plotOn(fr, RooFit.Components(getComp("missid")),RooFit.LineColor(kMagenta),RooFit.LineStyle(kDotted), RooFit.FillColor(kMagenta), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F") , RooFit.ProjWData(bdtBinData))

    bdtBinData.plotOn(fr, RooFit.Binning(binning))

    fr.GetXaxis().SetTitle("m_{#mu#mu} ( MeV/c^{2} )")
    fr.SetTitle("B_{s}^{0}#rightarrow#mu^{+}#mu^{-} candidates BDT>0.?")

    fr.GetYaxis().SetTitle("Events /( "+str(int(size))+" MeV/c^{2} )")
    gPad.SetLeftMargin(0.16)
    fr.GetYaxis().SetTitleOffset(1.1)
    #else: fr[i].GetYaxis().SetTitleOffset(1.6)
    fr.Draw()

    c.SaveAs(opts.get('RESULTDIR')+'MassFitIn_AllBDTBins.ps')
    c.SaveAs(opts.get('RESULTDIR')+'MassFitIn_AllBDTBins.root')
    print '  . Done! \n'

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
    b_Final_Plot_GCC48_R53410_NoOffseR
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





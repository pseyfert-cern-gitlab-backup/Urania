
####################################
# Combine the CMS and LHCb models  #
####################################


from ROOT import *
from ROOT import RooFit
from ROOT import RooStats
from SomeMassModels import RooPhysBkg #Run on LxPlus
#from SomeMassModels_this import RooPhysBkg #Run on LxPlus
from valAndErr import*

RooFit.gErrorIgnoreLevel = kError
RooMsgService.instance().setGlobalKillBelow(RooFit.ERROR)

import os

class Combination():
    """ Read in LHCb and CMS workspaces. Combine parameters/constraints, perform a fit."""

    def __init__(self, combName, autoConf = 1):
        """Star a combination. LHCb and CMS need to be read in, paramters bound and
        shared constraints defines. Or you can directly read in a saved combined Ws."""
        self.modelBuilt = False
        self.combName = combName
        self.resDir = 'Results/'+self.combName+'/'
        if not os.path.exists(self.resDir): os.makedirs(self.resDir)

        print ' <<  Starting a COMBINATION : ' + combName + ' >>'
        print '    o) Creating a combined WS(comb_ws)..'
        self.comb_f = TFile('combTemp.root','RECREATE')
        self.comb_ws = RooWorkspace('comb')
        print '                         Done!'

#        self.readLHCb()
#        self.readLHCb('lhcb_ws_fixRooPhysBkg_07032014.root')
        #self.readLHCb('lhcb_ws_28032014.root')
        self.readLHCb('lhcb_ws_20140403.root') #fdfs constraint parameters revealed, nuisances given as a set
        print '                         Done!'

        print '     o) Reading in, '
        #self.readCMS()
        self.readCMS('ws_revised_20140327_realvarnuisance.root')
        #self.readCMS('ws_revised_20140504_expcomb.root') #CMS with Exponents from Jack

        print '                         Done!'
        print '  Call -> self.fitCombinedModel() to fit!'

        #Example:
        #self.fitLHCb()
        #self.importLHCb()
        #self.importCMS_shareSomeParams(0,0,0)
        #self.buildCombModel()
        #self.combineData()
        #self.fitComb_LHCb(offset,nCPU)
        #self.fitComb_CMS(offset,nCPU,1)
        #self.fitComb_separateConstr(offset,nCPU)
        #self.combName = 'Comb_Unbound_fit2'


    ###################################
    # Helper function
    ###################################
    def modifySet(self, argSet , keepNames, suffix, removePars = ''):
        """ Add a suffix to al the variable names except the ones in keepNames set.
            Return a modified copy of argSet."""

        #newSet = argSet.Clone('clone')
        #it = newSet.createIterator()

        newSet = RooArgSet()
        it = argSet.createIterator()
        obj = it.Next()
        while obj:
            shared = False
            name = obj.GetName()
            for s in keepNames.split(','):
                if name in s: shared = True
            if not shared:
                name = obj.GetName() + suffix  #only the independent parameters get the suffix
                obj.SetName(name)

            obselete = False
            for s in removePars.split(','):  #do not add those parameters
                if name in s: obselete = True
            if not obselete:
                newSet.add(obj)
            obj = it.Next()

        return newSet


    ####################################
    # Read in LHCb model               #
    ####################################
    def readLHCb(self, fileName = 'lhcb_ws_26022014.root'):
        """Read in the LHCb workspace, pdf, data, constraints"""

        lhcb_f = TFile(fileName)
        self.lhcb_ws = lhcb_f.Get('lhcb_ws')
        self.lhcb_pdf = lhcb_ws.pdf('lhcb_pdf') # final simultaneous PDF
        self.lhcb_cat = lhcb_ws.cat('BDT12flat_cat')
        self.lhcb_mass = self.lhcb_ws.obj('B_s0_MM')
        self.lhcb_data = lhcb_ws.data('lhcb_data') # final data set
        #In LHCb fit all constraints are external
        self.lhcb_cons = lhcb_ws.set('lhcb_cons')

        testset = lhcb_ws.set('lhcb_obs')
        if testset: self.lhcb_obs = testset
        else:
            getattr(self.lhcb_ws,'defineSet')('lhcb_obs',RooArgSet(self.lhcb_ws.var('B_s0_MM'),self.lhcb_ws.cat('BDT12flat_cat')))
            self.lhcb_obs = self.lhcb_ws.set('lhcb_obs')

        testset = lhcb_ws.set('lhcb_constrained_nuisances')
        if testset: self.lhcb_nuis_cons = testset
        testset = lhcb_ws.set('lhcb_global_observables')
        if testset: self.lhcb_globobs = testset
        testset = lhcb_ws.set('lhcb_poi')
        if testset: self.lhcb_poi = testset
        testset = lhcb_ws.set('lhcb_unconstrained_nuisances')
        if testset: self.lhcb_nuis_uncons = testset


        lhcb_f.Close()
        return


    def importLHCb(self, fixBRs = 0, fixBRd = 0, fitRatio = False):
        """ Import LHCb pdf and constraint pdf's to the comb_ws. Add suffix _LHCb to all variables
            and constraints, except to the variables to be shared with CMS. Fix BRs and BRd by substituting
            them with constants, if required."""


        #Define a RooCustomizer object. This will perform the necessary subtitutions defined in the for loop.
        cust = RooCustomizer(self.lhcb_pdf,'') #The _LHCb is added to all nodes anyway

        #While fixing, create a constant, but leave the name same
        pois = self.lhcb_poi
        if fixBRs:
            name = 'BRs'
            getattr(self.comb_ws,'import')(RooRealVar(name,name,0.), RooFit.RecycleConflictNodes())
            cust.replaceArg(self.lhcb_ws.obj(name),self.comb_ws.var(name))
            pois = RooArgSet(self.lhcb_ws.var(name))

        if fixBRd:
            name = 'BRd'
            getattr(self.comb_ws,'import')(RooRealVar(name,name,0.))
            cust.replaceArg(self.lhcb_ws.obj(name),self.comb_ws.var(name))
            pois = RooArgSet(self.lhcb_ws.var(name))


        # Leave the shared variables BRs, BRd, fsfd, BuJpsiK_BF and observables untouched,
        # add '_LHCb' to the rest of the parameters
        #Define the shared parameters in string format
        self.sharedParams = 'BRs,BRd,fdfs,BuJpsiK_BF' # We'll leave those names the same when importing
        observables = ',B_s0_MM,'+self.lhcb_cat.GetName() # and those as well, but they are just not sharedParams
        #self.sharedConstraints = 'fdfs,BuJpsiK_BF' #and those are the shared constraints. only renam the constraint funtions not params

        #Replace the normalization part with just a yield variable
        formula = 0
        ratio = 0
        Nbd = 0
        if fitRatio:
            name = 'NBs'
            Nbs = RooRealVar(name,name,self.lhcb_ws.obj(name).getVal(),0.,100)
            cust.replaceArg(self.lhcb_ws.obj(name),Nbs)
            pois = RooArgSet(self.comb_ws.var(name))

            name = 'NBd'
            #ratio = RooRealVar('BRsOverBRd','BRs / BRd',1.,0,20)  #9.09638e+00   1.63282e+00
            #ratio = RooRealVar('BRsOverBRd','BRs / BRd',6.,0.,100.)
            #formula = RooFormulaVar(name+'_Form',name+'_Form','(@0*@1)/@2',RooArgList(Nbs,self.lhcb_ws.obj('fdfs'),ratio)) # Nd = fd/fs * BRd/BRs

            ratio = RooRealVar('BRdOverBRs','BRd / BRs',0.1,0.,1.)
            formula = RooFormulaVar(name+'_Form',name+'_Form','@0*@1*@2',RooArgList(Nbs,self.lhcb_ws.obj('fdfs'),ratio)) # Nd = fd/fs * BRd/BRs

            cust.replaceArg(self.lhcb_ws.obj(name),formula)
            pois = RooArgSet(ratio)
            #self.sharedParams+=',BRsOverBRd' #So the name stays the same
            self.sharedParams+=',BRdOverBRs' #So the name stays the same

        #Build the new lhcb_pdf and import it to the comb_ws
        self.lhcb_pdf_cust= cust.build(kTRUE)

        #try:
        if 1:

            getattr(self.comb_ws,'import')(self.lhcb_pdf_cust,RooFit.RenameAllVariablesExcept('LHCb',self.sharedParams+observables), RooFit.RenameAllNodes('LHCb'))
            self.comb_lhcb_pdf = self.comb_ws.pdf(self.lhcb_pdf.GetName()+'_LHCb')

            # Leave the shared constrained VARIABLES fsfd, BuJpsiK_BF untouched,
            # but rename the constraints{fsfd_const,BuJpsiK_BF_const} to 'name'+_LHCb
            getattr(self.comb_ws,'import')(self.lhcb_cons,RooFit.RenameAllVariablesExcept('LHCb',self.sharedParams) , RooFit.RenameAllNodes('LHCb'))

            #######################
            # IMPORT THE VAR SETS #
            #######################
            #Import the set of observables
            getattr(self.comb_ws,'defineSet')('comb_lhcb_obs',self.lhcb_obs)
            #getattr(self.comb_ws,'defineSet')('comb_lhcb_obs',self.lhcb_ws.set('lhcb_obs'))

            #################
            #Import the parameters of interest. As they are always shared, they LHCb ones = CMS ones => comb_poi
            getattr(self.comb_ws,'defineSet')('comb_poi',pois)

            #################
            #Those are the parameter names to be left without suffix
            self.doNotTouch = self.sharedParams + observables
            print self.doNotTouch
            # We need to redefine the RooArgSet in the new ws where the variables now have _LHCb at the end
            # The shared constraint function names get '_LHCB' (but not the shared parameters)
            comb_lhcb_cons = self.modifySet(argSet = self.lhcb_cons, keepNames = self.doNotTouch, suffix='_LHCb')
            getattr(self.comb_ws,'defineSet')('comb_lhcb_cons',comb_lhcb_cons)

            #################
            # The nuisances and global observables get a suffix, except sharedParams, observables and poi's
            comb_lhcb_nuis_cons = self.modifySet(argSet = self.lhcb_nuis_cons, keepNames = self.doNotTouch, suffix='_LHCb')
            getattr(self.comb_ws,'defineSet')('comb_lhcb_nuis_cons',comb_lhcb_nuis_cons)

            #################
            # All unconstrained LHCb parameters get a suffix
            comb_lhcb_nuis_uncons = self.modifySet(argSet = self.lhcb_nuis_uncons, keepNames = self.doNotTouch, suffix='_LHCb')

            getattr(self.comb_ws,'defineSet')('comb_lhcb_nuis_uncons',comb_lhcb_nuis_uncons, True) #import missing = True
            print 'DEBUG-5'
            #################
            # All global observables get the suffix (the shared parameters also get _LHCb constraints)
            comb_lhcb_globobs = self.modifySet(argSet = self.lhcb_globobs, keepNames = self.doNotTouch, suffix='_LHCb')
            getattr(self.comb_ws,'defineSet')('comb_lhcb_globobs',comb_lhcb_globobs)

            self.comb_ws.Print()
            self.comb_lhcb_pdf = self.comb_ws.pdf(self.lhcb_pdf.GetName()+'_LHCb')

        #except:
        #    raw_input ( ' FAILED TO IMPORT LHCb model! ' )


    ####################################
    # Read in CMS model                #
    ####################################
    def readCMS(self, fileName = 'ws_revised_20140104.root'):
        """Read in the CMS workspace, pdf, data, constraints"""

        cms_f = TFile(fileName)
        self.cms_ws = cms_f.Get('ws')
        self.cms_pdf = self.cms_ws.pdf('pdf_ext_simul') # final simultaneous PDF
        self.cms_cat = self.cms_ws.cat('allcat')
        #RooRealVar::Mass "M_{#mu#mu}"
        self.cms_mass = self.cms_ws.obj('Mass')
        self.cms_data = self.cms_ws.data('global_data') # final data set
        self.cms_ext_const = RooArgSet(self.cms_ws.pdf('fs_over_fu_gau'),self.cms_ws.pdf('one_over_BRBR_gau')) # external Gaussian constraints

        testset = self.cms_ws.set('constrained_nuisances')
        if testset: self.cms_nuis_cons = testset
        testset = self.cms_ws.set('constraint_means')
        if testset: self.cms_globobs = testset
        testset = self.cms_ws.set('obs')
        if testset: self.cms_obs = testset
        testset = self.cms_ws.set('poi')
        if testset: self.cms_poi = testset
        testset = self.cms_ws.set('unconstrained_nuisances')
        if testset: self.cms_nuis_uncons = testset
        cms_f.Close()


    def readCMS_exp(self, fileName = 'ws_revised_20140104.root'):
        """Read in the CMS workspace, pdf, data, constraints"""

        cms_f = TFile(fileName)
        self.cms_ws = cms_f.Get('ws')
        self.cms_cat = self.cms_ws.cat('allcat')
        self.cms_mass = self.cms_ws.obj('Mass')
        self.cms_data = self.cms_ws.data('global_data') # final data set
        self.cms_ext_const = RooArgSet(self.cms_ws.pdf('fs_over_fu_gau'),self.cms_ws.pdf('one_over_BRBR_gau')) # external Gaussian constraints

        testset = self.cms_ws.set('constrained_nuisances')
        if testset: self.cms_nuis_cons = testset
        testset = self.cms_ws.set('constraint_means')
        if testset: self.cms_globobs = testset
        testset = self.cms_ws.set('obs')
        if testset: self.cms_obs = testset
        testset = self.cms_ws.set('poi')
        if testset: self.cms_poi = testset
        testset = self.cms_ws.set('unconstrained_nuisances')
        if testset: self.cms_nuis_uncons = testset


        self.cms_pdf = self.cms_ws.pdf('pdf_ext_simul') # final simultaneous PDF
        #cust = RooCustomizer(self.cms_pdf,'CMS')
        cust = RooCustomizer(self.cms_pdf,'')

        cms_channels = 4
        cms_index_max = [2,2,4,4]
        for i in range(0,cms_channels):
            for j in range(0,cms_index_max[i]):

                #N_bu = BF_b * N_bu * effRat / (fdfs * BF_Bu)
                b = '_'+str(i)+'_'+str(j)
                #pdf_1comb_.. is using polynomials
                #pdf_comb_.. is using exponents
                cust.replaceArg(self.cms_ws.obj('pdf_1comb'+b),self.cms_ws.obj('pdf_comb'+b))

        custPdf = cust.build(kTRUE)
        self.cms_pdf = custPdf

        cms_f.Close()


    ####################################
    # Define the shared params         #
    ####################################

    def importCMS_combined(self, change2MeV = False):
        """(Share BRs, BRd, fdfs, BuJpsiK_BF) Make a copy of CMS model with modified variables and constraints
            to match lhcb variable and constraint names. Import the configured
            and linked CMS pdf to the combined ws """
        self.independent = False
        print "importing CMS workspace, with parameters shared for combination "
        # IDEA: Copy cms pdf with changes, and import to the comb_ws

        # We need to redefine the yield calculation formulas for N_bs and N_bd
        # in all the CMS bins

        #Define a RooCustomizer object. This will perform the necessary subtitutions defined in the for loop.
        cust = RooCustomizer(self.cms_pdf,'CMS')

        #Get the BRs from LHCb pdf in combined workspace, shift by 10e-9 to match CMS value
        BRs = self.comb_ws.obj('BRs')

        #Get the BRd from LHCb pdf in combined workspace, shift by 10e-10 to match CMS value
        BRd = self.comb_ws.obj('BRd')

        #Get the fdfs from LHCb pdf in combined workspace
        fdfs = self.comb_ws.var('fdfs')

        #Get the BuJpsiK_BF from LHCb pdf in comb ws (the value is shifted by 10e-5 in LHCb ws)
        BRbu = self.comb_ws.obj('BuJpsiK_BF')

        #Loop over the CMS bins and customize the yield calculation by using LHCb fdfs, BRs, BRd and BF_BuJpsiK
        N_bs_formula = []
        N_bd_formula = []
        cms_channels = 4
        cms_index_max = [2,2,4,4]

        # Here I define a fdfs variable for CMS in order to add a gaussian for the 5% error
        fdfs_cms_scale = RooRealVar("fdfs_cms_scale","fdfs_cms_scale",1.0,0.5,1.5)
        fdfs_cms_scale_mean  = RooRealVar("fdfs_cms_scale_mean","fdfs_cms_scale_mean",1.00)
        fdfs_cms_scale_mean.setConstant(True)
        fdfs_cms_scale_sigma = RooRealVar("fdfs_cms_scale_sigma","fdfs_cms_scale_sigma",0.05)
        fdfs_cms_scale_sigma.setConstant(True)
        fdfs_cms   = RooFormulaVar("fdfs_cms","fdfs_cms","@0*@1",RooArgList(fdfs_cms_scale,fdfs))
        fdfs_cms_scale_const = RooGaussian("fdfs_cms_scale_const","fdfs_cms_scale_const",fdfs_cms_scale,fdfs_cms_scale_mean, fdfs_cms_scale_sigma)
        fdfs_cms_scale_const.Print("v")
        print "importing stuff" ,
        getattr(self.comb_ws,'import')(fdfs_cms_scale_const, RooFit.RecycleConflictNodes())
        getattr(self.comb_ws,'import')(fdfs_cms, RooFit.RecycleConflictNodes())

        #Get the fdfs_cms from the Ws to be sure we use the same var
        fdfs_cms = self.comb_ws.obj('fdfs_cms')

        #Replace the old yield formulas by new ones in every bin
        for i in range(0,cms_channels):
            for j in range(0,cms_index_max[i]):

                #N_bu = BF_b * N_bu * effRat / (fdfs * BF_Bu)
                b = '_'+str(i)+'_'+str(j)
                effratio_bs = self.cms_ws.var('effratio_bs'+b)
                effratio_bd = self.cms_ws.var('effratio_bd'+b)
                N_bu = self.cms_ws.var('N_bu'+b)

                N_bs_formula.append(RooFormulaVar('N_bs_CombFormula'+b, 'N_bs', '@0*1.e-9*@1*@2/(@3*@4*1.e-5)',\
                                                  RooArgList(BRs,N_bu,effratio_bs,fdfs_cms,BRbu)))
                N_bd_formula.append(RooFormulaVar('N_bd_CombFormula'+b, 'N_bd', '@0*1.e-10*@1*@2/(@3*1.e-5)',\
                                                  RooArgList(BRd,N_bu,effratio_bd,BRbu)))

                #Change the old yield formula for the new one
                cust.replaceArg(self.cms_ws.obj('N_bs_formula'+b),N_bs_formula[-1])
                cust.replaceArg(self.cms_ws.obj('N_bd_formula'+b),N_bd_formula[-1])


        ################################################################
        ### THIS IS NEEDED FOR THE COMBINED ILLUSTRATIVE MASS PLOT  ###
        ################################################################
        # IDEA:
        # Change all the mass related variables from GeV to MeV
        # Leave the ReducedMass observable the same, but change the PeeK_0_0 variables
        # In each bin to PeeK / 10e3
        ################################################################
        #Containers for the formulas that relate the variables in MeV's to the original variables in GeV's
        comb_MeV = []
        keys_MeV = []
        keys_mass = []

        PeeK_bs_MeV = []
        PeeK_bd_MeV = []
        Mean_bs_MeV = []
        Mean_bd_MeV = []
        Mean_peak_MeV = []
        Sigma_peak_MeV = []
        Sigma2_peak_MeV = []

        if change2MeV:

            #Combine the mass variables (Put B_s0_MM in CMS Dataset, redefine the Mass as B_s0_MM/10e3, for the RooKeysPdf)
            mass = self.comb_ws.obj('B_s0_MM')
            # Replace GeV mass with MeV mass varible, and change the model to fit the MeV scale
            cust.replaceArg(self.cms_ws.obj('Mass'),mass)
            getattr(self.comb_ws,'import')(self.cms_ws.obj('Mass')) #Otherwise the old Mass variable will not be imported

            for i in range(0,cms_channels):
                for j in range(0,cms_index_max[i]):

                    #N_bu = BF_b * N_bu * effRat / (fdfs * BF_Bu)
                    b = '_'+str(i)+'_'+str(j)

                    ##Divide by 10e3
                    #PeeK_bs = self.cms_ws.var('PeeK_bs'+b)
                    #PeeK_bd = self.cms_ws.var('PeeK_bd'+b)

                    #PeeK_bs_MeV.append(RooFormulaVar('PeeK_bs_MeV'+b+'_CMS', 'PeeK_bs', '@0/(1.e3)',RooArgList(PeeK_bs)))
                    #PeeK_bd_MeV.append(RooFormulaVar('PeeK_bd_MeV'+b+'_CMS', 'PeeK_bd', '@0/(1.e3)',RooArgList(PeeK_bd)))

                    #cust.replaceArg(self.cms_ws.obj('PeeK_bs'+b),PeeK_bs_MeV[-1])
                    #cust.replaceArg(self.cms_ws.obj('PeeK_bd'+b),PeeK_bd_MeV[-1])

                    #Multiply by 10e3
                    Mean_bs = self.cms_ws.var('Mean_bs'+b)
                    Mean_bd = self.cms_ws.var('Mean_bd'+b)
                    Mean_peak = self.cms_ws.var('Mean_peak'+b)
                    Sigma_peak = self.cms_ws.var('Sigma_peak'+b)
                    Sigma2_peak = self.cms_ws.var('Sigma2_peak'+b)

                    Mean_bs_MeV.append(RooFormulaVar('Mean_bs_MeV'+b+'_CMS', 'Mean_bs', '@0*(1.e3)',RooArgList(Mean_bs)))
                    Mean_bd_MeV.append(RooFormulaVar('Mean_bd_MeV'+b+'_CMS', 'Mean_bd', '@0*(1.e3)',RooArgList(Mean_bd)))
                    Mean_peak_MeV.append(RooFormulaVar('Mean_peak_MeV'+b+'_CMS', 'Mean_peak', '@0*(1.e3)',RooArgList(Mean_peak)))
                    Sigma_peak_MeV.append(RooFormulaVar('Sigma_peak_MeV'+b+'_CMS', 'Sigma_peak', '@0*(1.e3)',RooArgList(Sigma_peak)))
                    Sigma2_peak_MeV.append(RooFormulaVar('Sigma2_peak_MeV'+b+'_CMS', 'Sigma2_peak', '@0*(1.e3)',RooArgList(Sigma2_peak)))

                    cust.replaceArg(self.cms_ws.obj('Mean_bs'+b),Mean_bs_MeV[-1])
                    cust.replaceArg(self.cms_ws.obj('Mean_bd'+b),Mean_bd_MeV[-1])
                    cust.replaceArg(self.cms_ws.obj('Mean_peak'+b),Mean_peak_MeV[-1])
                    cust.replaceArg(self.cms_ws.obj('Sigma_peak'+b),Sigma_peak_MeV[-1])
                    cust.replaceArg(self.cms_ws.obj('Sigma2_peak'+b),Sigma2_peak_MeV[-1])

                    #Substitute the semileptonic RooKeysPdf with a new one that describes B_s0_MM
                    # m = B_s0_MM/1000
                    cust_semi = RooCustomizer(self.cms_pdf.getComponents()['keys_semi'+b],'CMS')
                    #For RooKeys we still need to give the mass in GeV's
                    keys_mass.append(RooFormulaVar('keys_mass'+b, 'keys_mass', '@0/(1.e3)',RooArgList(mass)))
                    #cust_semi.replaceArg(self.cms_ws.obj('Mass'),keys_mass)
                    cust_semi.replaceArg(self.cms_ws.obj('Mass'),keys_mass[-1])
                    keys_MeV.append(cust_semi.build(kTRUE)) #Build new keys with the mass = B_s0_MM/1000
                    cust.replaceArg(self.cms_ws.obj('keys_semi'+b),keys_MeV[-1])

                    # Substitute the mass in Bernstein polynomial with mass/1000
                    #Does not work.
                    #cust_comb= RooCustomizer(self.cms_pdf.getComponents()['mass_1comb'+b],'CMS')
                    #cust_comb.replaceArg(self.cms_ws.obj('Mass'),keys_mass)
                    #comb_MeV.append(cust_comb.build(kTRUE)) #Build new keys with the mass = B_s0_MM/1000
                    #or..
                    #Does not work.
                    #comb_MeV.append(RooBernstein('mass_1comb'+b+'_CMS','mass_1comb'+b+'_CMS',mass,RooArgList(self.cms_ws.obj('Btrans_1comb'+b),self.cms_ws.obj('Btrans_2comb'+b))))
                    #comb_MeV.append(RooBernstein('mass_1comb'+b+'_CMS','mass_1comb'+b+'_CMS',keys_mass,RooArgList(self.cms_ws.obj('Btrans_1comb'+b),self.cms_ws.obj('Btrans_2comb'+b))))
                    #cust.replaceArg(self.cms_ws.obj('mass_1comb'+b),comb_MeV[-1])



        ################################################################
        #Build the new cms_pdf and import it to the comb_ws
        self.cms_pdf_cust= cust.build(kTRUE)

        #Import CMS customized pdf. Needs to be done here, where the newly define RooFormulas are still alive
        getattr(self.comb_ws,'import')(self.cms_pdf_cust , RooFit.RenameAllVariablesExcept('CMS','BRs,BRd,fdfs,fdfs_scale,BuJpsiK_BF,Mass,B_s0_MM,ReducedMassRes,etacat,bdtcat,bdt_0,bdt_1,bdt_2,bdt_3,'+self.cms_cat.GetName()),RooFit.RecycleConflictNodes())

        #getattr(self.comb_ws,'import')(self.cms_pdf_cust , RooFit.RenameAllNodes('CMS') , RooFit.RenameAllVariablesExcept('CMS','BRs,BRd,fdfs,fdfs_scale,BuJpsiK_BF,Mass,ReducedMassRes,etacat,bdtcat,bdt_0,bdt_1,bdt_2,bdt_3,'+self.cms_cat.GetName()),RooFit.RecycleConflictNodes())

        self.comb_cms_pdf = self.comb_ws.pdf(self.cms_pdf_cust.GetName())
        print 'CMS pdf name:', self.cms_pdf.GetName()
        print 'CMS cust pdf name:', self.comb_cms_pdf.GetName()

        #######################
        # Import also all the cms observables, poi, nuis, glob obs, unconstr_nuis
        # NB! Remember the shared parameters ('fdfs, etc')
        # NB! All internal constraints get _CMS
        # NB! And the constraints on the shared params ('..._const_LHCb')
        # NB! And the global observables (mean) on the shared param constraint ('..._mean_LHCb')

        #################

        #######################
        # IMPORT THE VAR SETS #
        #######################
        #Import the set of observables
        getattr(self.comb_ws,'defineSet')('comb_cms_obs',self.cms_obs)
        getattr(self.comb_ws,'defineSet')('comb_cms_nuis_cons',RooArgSet(self.comb_ws.var((fdfs_cms_scale.GetName()))))
        getattr(self.comb_ws,'defineSet')('comb_cms_globobs',RooArgSet(self.comb_ws.var((fdfs_cms_scale_mean.GetName()))))


        #################
        #The parameters of interest. As they are always shared, the LHCb ones = CMS ones => comb_poi

        #################
        #Adding the constraint to the ws (the fdfs_scale constr will be the only one, the rest come from LHCb)
        # Adding this constraint to the cms external constraint
        print "Creating set of cms constraints"
        cmsConstr = RooArgSet(self.comb_ws.pdf('fdfs_cms_scale_const'))
        getattr(self.comb_ws,'defineSet')('comb_cms_cons', cmsConstr) # we might want to add here the other ones..."internal"

        self.removePars = 'BF_bs,BF_bd,fs_over_fu,one_over_BRBR' #those are obselete old CSM parameters, they are shared and taken from LHCb now

        #################
        comb_cms_nuis_uncons = self.modifySet(argSet = self.cms_nuis_uncons, keepNames = self.doNotTouch, suffix='_CMS', removePars = self.removePars)
        getattr(self.comb_ws,'defineSet')('comb_cms_nuis_uncons',comb_cms_nuis_uncons)

        #################
        self.comb_ws.Print()

        #################
        #setName = 'lhcb_globobs'
        #newConst = self.lhcb_globobs.Clone(setName)
        #it = newConst.createIterator()
        #obj = it.Next()
        #while obj:
        #    name = obj.GetName() + '_LHCb'
        #    obj.SetName(name)
        #    obj = it.Next()
        #getattr(self.comb_ws,'defineSet')(setName,newConst)
        #testset = lhcb_ws.set('lhcb_constrained_nuisances')
        #################

    def importCMS_fitRatio(self):
        """ Remove the normalisation and fit only the NBs and NBd yields. Later those can be used to calculate the ratio"""

        self.independent = False
        print "importing CMS workspace, with parameters shared for combination "

        #Define a RooCustomizer object. This will perform the necessary subtitutions defined in the for loop.
        cust = RooCustomizer(self.cms_pdf,'CMS')

        #Loop over the CMS bins and customize the yield calculation by using LHCb fdfs, BRs, BRd and BF_BuJpsiK
        N_bs_var= []
        N_bd_var= []
        cms_channels = 4
        cms_index_max = [2,2,4,4]

        # Here I define a fdfs variable for CMS in order to add a gaussian for the 5% error
        fdfs = self.comb_ws.var('fdfs')
        fdfs_cms_scale = RooRealVar("fdfs_cms_scale","fdfs_cms_scale",1.0,0.5,1.5)
        fdfs_cms_scale_mean  = RooRealVar("fdfs_cms_scale_mean","fdfs_cms_scale_mean",1.00)
        fdfs_cms_scale_mean.setConstant(True)
        fdfs_cms_scale_sigma = RooRealVar("fdfs_cms_scale_sigma","fdfs_cms_scale_sigma",0.05)
        fdfs_cms_scale_sigma.setConstant(True)
        fdfs_cms = RooFormulaVar("fdfs_cms","fdfs_cms","@0*@1",RooArgList(fdfs_cms_scale,fdfs))
        fdfs_cms_scale_const = RooGaussian("fdfs_cms_scale_const","fdfs_cms_scale_const",fdfs_cms_scale,fdfs_cms_scale_mean, fdfs_cms_scale_sigma)
        fdfs_cms_scale_const.Print("v")
        print "importing stuff" ,
        getattr(self.comb_ws,'import')(fdfs_cms_scale_const, RooFit.RecycleConflictNodes())
        getattr(self.comb_ws,'import')(fdfs_cms, RooFit.RecycleConflictNodes())

        #Get the fdfs_cms from the Ws to be sure we use the same var
        fdfs_cms = self.comb_ws.obj('fdfs_cms')

        #Replace the old yield formulas by new yield variables
        #Total yields
        #NBs = fit
        #NBd = NBs * (BRd/BRs) * (fd/fs)
        getattr(self.comb_ws,'import')(RooRealVar('NBs_CMS', 'N_Bs CMS total', 42.,0.,100.)) #Variables get the CMS in the end anyhow

        #getattr(self.comb_ws,'import')(RooFormulaVar('NBd_CMS', 'N_Bd CMS total', "@0*(1./@1)*@2",RooArgList(self.comb_ws.obj('NBs_CMS'),self.comb_ws.obj('BRsOverBRd'),fdfs_cms))) #Increases error, so must not take the correlations properly into account :S 1 BRd/BRs = 0.1400 +- 0.0673
        #getattr(self.comb_ws,'import')(RooFormulaVar('NBd_CMS', 'N_Bd CMS total', "(@0/@1)*@2",RooArgList(self.comb_ws.obj('NBs_CMS'),self.comb_ws.obj('BRsOverBRd'),fdfs_cms))) #ok! 2 BRd/BRs = 0.1400 +- 0.0670

        #It does not matter which one
        #getattr(self.comb_ws,'import')(RooFormulaVar('NBd_CMS', 'N_Bd CMS total', "(@0*@1)/@2",RooArgList(self.comb_ws.obj('NBs_CMS'),fdfs_cms,self.comb_ws.obj('BRsOverBRd')))) # 3  BRd/BRs = 0.1400 +- 0.0672
        getattr(self.comb_ws,'import')(RooFormulaVar('NBd_CMS', 'N_Bd CMS total', "@0*@1*@2",RooArgList(self.comb_ws.obj('NBs_CMS'),fdfs_cms,self.comb_ws.obj('BRdOverBRs')))) # 3  BRd/BRs = 0.1400 +- 0.0672

        #-----------------#
        #Create fractions that define how NBs and NBd total divide between the categories
        f_bs_raw_CMS = []
        f_bd_raw_CMS = []
        f_bs_argList = RooArgList()
        f_bd_argList = RooArgList()

        N_bu_bins = RooArgList()
        #Define the total BuJpsiKplus yield, so we can use it in calculating the ratios per categories
        for i in range(0,cms_channels):
            for j in range(0,cms_index_max[i]):

                b = '_'+str(i)+'_'+str(j)
                N_bu = self.cms_ws.var('N_bu'+b)
                N_bu_bins.add(N_bu)

        N_bu_tot = RooFormulaVar('N_bu_tot_CMS', 'N_bu_tot', "@0+@1+@2+@3+@4+@5+@6+@7+@8+@9+@10+@11",N_bu_bins)

        for i in range(0,cms_channels):
            for j in range(0,cms_index_max[i]):
                b = '_'+str(i)+'_'+str(j)

                eff_bs = self.cms_ws.obj('effratio_bs'+b)
                eff_bd = self.cms_ws.obj('effratio_bd'+b)

                f_bs_raw_CMS.append(RooFormulaVar('f_bs_raw'+b+'_CMS', 'Bs fraction in cat', '(@0/@1)*@2',RooArgList(self.cms_ws.obj('N_bu'+b),N_bu_tot,eff_bs)))
                f_bd_raw_CMS.append(RooFormulaVar('f_bd_raw'+b+'_CMS', 'Bd fraction in cat', '(@0/@1)*@2',RooArgList(self.cms_ws.obj('N_bu'+b),N_bu_tot,eff_bd)))

                f_bs_argList.add(f_bs_raw_CMS[-1])
                f_bd_argList.add(f_bd_raw_CMS[-1])

        #effNames = effNames[:-1]

        #Raw (unnormalized) fraction sum
        f_bs_sum_CMS = RooFormulaVar('f_bs_sum_CMS', 'f_bs_sum', "@0+@1+@2+@3+@4+@5+@6+@7+@8+@9+@10+@11",f_bs_argList)
        f_bd_sum_CMS = RooFormulaVar('f_bd_sum_CMS', 'f_bd_sum', "@0+@1+@2+@3+@4+@5+@6+@7+@8+@9+@10+@11",f_bd_argList)

        #Normalize fractions to 1
        f_bs_CMS = []
        f_bd_CMS = []
        cms_bins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3']
        for i in range(0,12):
            b = '_'+cms_bins[i]+'_CMS'
            f_bs_CMS.append(RooFormulaVar('f_bs'+b,'Nbs fraction in cat','@0/@1',RooArgList(f_bs_raw_CMS[i],f_bs_sum_CMS)))
            f_bd_CMS.append(RooFormulaVar('f_bd'+b,'Nbd fraction in cat','@0/@1',RooArgList(f_bd_raw_CMS[i],f_bd_sum_CMS)))
            #getattr(self.comb_ws,'import')(f_bs_CMS[-1],RooFit.RecycleConflictNodes())
            #getattr(self.comb_ws,'import')(f_bd_CMS[-1],RooFit.RecycleConflictNodes())
        #-----------------#

        #Project the yields to the bins
        ratio_scale = []
        nr = -1
        for i in range(0,cms_channels):
            for j in range(0,cms_index_max[i]):
                nr+=1
                b = '_'+str(i)+'_'+str(j)

                # This is for replacin with the raw fractions
                #N_bs_var.append(RooFormulaVar('N_bs_bin'+b+'_CMS', 'N_bs', "@0*@1",RooArgList(self.comb_ws.obj('NBs_CMS'),f_bs_raw_CMS[nr])))
                #N_bd_var.append(RooFormulaVar('N_bd_bin'+b+'_CMS', 'N_bd', "@0*@1",RooArgList(self.comb_ws.obj('NBd_CMS'),f_bd_raw_CMS[nr])))

                # This is for replacin with the normalized fractions  Brd/Brs = 0.1399+-0.0658
                N_bs_var.append(RooFormulaVar('N_bs_bin'+b+'_CMS', 'N_bs', "@0*@1",RooArgList(self.comb_ws.obj('NBs_CMS'),f_bs_CMS[nr])))
                N_bd_var.append(RooFormulaVar('N_bd_bin'+b+'_CMS', 'N_bd', "@0*@1",RooArgList(self.comb_ws.obj('NBd_CMS'),f_bd_CMS[nr])))

                # This is for replacin with the fractions
                #N_bs_var.append(RooFormulaVar('N_bs_bin'+b+'_CMS', 'N_bs', "@0*@1",RooArgList(self.comb_ws.obj('NBs_CMS'),self.comb_ws.obj('f_bs'+b+'_CMS'))))
                #N_bd_var.append(RooFormulaVar('N_bd_bin'+b+'_CMS', 'N_bd', "@0*@1",RooArgList(self.comb_ws.obj('NBd_CMS'),self.comb_ws.obj('f_bd'+b+'_CMS')))) #Variables get the CMS in the end anyhow

                #N_bs_var.append(RooRealVar('N_bs_bin'+b, 'N_bs', 1.,0.,30))
                #ratio_scale.append(RooRealVar('ratio_scale_bin'+b, 'N_Bs = ratio_scale * BRs\BRd * NBd * fsfd', 1.,0.5,1.5)) #In case the Brs/BRd differes in the categories
                #N_bd_var.append(RooFormulaVar('N_bd_bin'+b+'_CMS', 'N_bd', "@0*@1*@2/@3", RooArgList(ratio_scale[-1], N_bs_var[-1],fdfs_cms, self.comb_ws.obj('BRsOverBRd'))))

                #Incorporate also effratio
                #N_bd_var.append(RooFormulaVar('N_bd_bin'+b+'_CMS', 'N_bd', "@0*@1*(1./@2)*(@3/@4)", RooArgList(N_bs_var[-1],fdfs_cms, self.comb_ws.obj('BRsOverBRd'),self.cms_ws.obj('effratio_bd'+b),self.cms_ws.obj('effratio_bs'+b))))

                #Incorporate also effratio and the NBu yield fraction per BDT bin #Wrong! Camcels out!
                #N_bu = self.cms_ws.var('N_bu'+b)
                #N_bd_var.append(RooFormulaVar('N_bd_bin'+b+'_CMS', 'N_bd', "@0*@1*(1./@2)*(@3/@4)*(@5/@6)", RooArgList(N_bs_var[-1],fdfs_cms, self.comb_ws.obj('BRsOverBRd'),self.cms_ws.obj('effratio_bd'+b),self.cms_ws.obj('effratio_bs'+b),N_bu,N_bu_tot)))

                #Change the old yield formula for the new variables
                cust.replaceArg(self.cms_ws.obj('N_bs_formula'+b),N_bs_var[-1])
                cust.replaceArg(self.cms_ws.obj('N_bd_formula'+b),N_bd_var[-1])

        ################################################################
        #Build the new cms_pdf and import it to the comb_ws
        self.cms_pdf_cust= cust.build(kTRUE)

        #Import CMS customized pdf. Needs to be done here, where the newly define RooFormulas are still alive
        getattr(self.comb_ws,'import')(self.cms_pdf_cust , RooFit.RenameAllVariablesExcept('CMS','BRs,BRd,BRdOverBRs,NBd_CMS,NBs_CMS,fdfs,fdfs_scale,BuJpsiK_BF,Mass,B_s0_MM,ReducedMassRes,etacat,bdtcat,bdt_0,bdt_1,bdt_2,bdt_3,'+self.cms_cat.GetName()),RooFit.RecycleConflictNodes())

        self.comb_cms_pdf = self.comb_ws.pdf(self.cms_pdf_cust.GetName())
        print 'CMS pdf name:', self.cms_pdf.GetName()
        print 'CMS cust pdf name:', self.comb_cms_pdf.GetName()

        #######################
        # IMPORT THE VAR SETS #
        #######################
        #Import the set of observables
        getattr(self.comb_ws,'defineSet')('comb_cms_obs',self.cms_obs)
        getattr(self.comb_ws,'defineSet')('comb_cms_nuis_cons',RooArgSet(self.comb_ws.var((fdfs_cms_scale.GetName()))))
        getattr(self.comb_ws,'defineSet')('comb_cms_globobs',RooArgSet(self.comb_ws.var((fdfs_cms_scale_mean.GetName()))))

        #################
        #The parameters of interest. As they are always shared, the LHCb ones = CMS ones => comb_poi
        print "Creating set of cms constraints"
        cmsConstr = RooArgSet(self.comb_ws.pdf('fdfs_cms_scale_const'))
        getattr(self.comb_ws,'defineSet')('comb_cms_cons', cmsConstr) # we might want to add here the other ones..."internal"
        self.removePars = 'BF_bs,BF_bd,fs_over_fu,one_over_BRBR' #those are obselete old CSM parameters, they are shared and taken from LHCb now
        comb_cms_nuis_uncons = self.modifySet(argSet = self.cms_nuis_uncons, keepNames = self.doNotTouch, suffix='_CMS', removePars = self.removePars)
        getattr(self.comb_ws,'defineSet')('comb_cms_nuis_uncons',comb_cms_nuis_uncons)
        #################
        self.comb_ws.Print()


    ####################################
    # Create Combined MODEL            #
    ####################################
    def combineParSets(self, suffix):
        comb_set = self.comb_ws.set('comb_lhcb_'+suffix)
        if self.comb_ws.set('comb_cms_'+suffix):
            comb_set.add(self.comb_ws.set('comb_cms_'+suffix))
        getattr(self.comb_ws,'defineSet')('comb_'+suffix,comb_set)

    def combineAllSets(self):
        self.combineParSets('obs')
        self.combineParSets('globobs')
        self.combineParSets('cons')
        self.combineParSets('nuis_uncons')
        self.combineParSets('nuis_cons')
        self.comb_ws.Print()

    def buildCombModel(self):

        self.combineAllSets()
        ##############################################################
        # o) First, get the component pdfs in lhcb and cms
        # o) and build a combined category, that makes the experiments and categories linear
        #self.comb_cat = RooCategory("comb_cat","Category of {CMS,LHCb} and their subcats")
        self.comb_cat_name = 'comb_cat'
        self.catTypes = []
        catTypes_str = ''
        typeAndPdf = ''  #typeName=pdfName pair
        self.bdt_bins = 8

        #LHCb bin pdfs
        for i in range(1,self.bdt_bins+1):
            pdfNameOld = 'mumu model '+str(i)+'_LHCb'  #Name of the component in the WS
            pdfName = 'mumu_model_'+str(i)+'_LHCb'  #Name of the component in the WS
            self.comb_ws.pdf(pdfNameOld).SetName(pdfName)
            catType = 'LHCb_bin_'+str(i)
            self.catTypes.append(catType)
            catTypes_str += catType+','
            typeAndPdf += catType +'='+pdfName +','

        #CMS bin pdfs
        cmsBins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3',]
        suffix = '_CMS'
        if self.independent: suffix = ''
        for i in range(1,13):
            pdfName = 'pdf_ext_total_'+cmsBins[i-1]+suffix #Name of the component in the WS
            catType = 'CMS_bin_'+str(i)
            self.catTypes.append(catType)
            catTypes_str += catType+','
            typeAndPdf += catType +'='+pdfName +','

        #Remove the coma at the end
        catTypes_str = catTypes_str[:len(catTypes_str)-1]
        typeAndPdf = typeAndPdf[:len(typeAndPdf)-1]

        print ' catTypes_str =', catTypes_str
        print ' typeAndPdf =', typeAndPdf
        print ' catTypes[] = ', self.catTypes
#        raw_input('ok?')
        ##############################################################

        #Build the model in the combined WS
        self.comb_ws.factory('SIMUL::comb_pdf('+self.comb_cat_name+'['+catTypes_str+'],'+typeAndPdf+')') #comb_component_cms gives the CMS pdf name
        self.comb_pdf = self.comb_ws.pdf('comb_pdf')
        self.comb_pdf.graphVizTree(self.resDir+"comb_model.dot")

        self.comb_cat = self.comb_ws.cat(self.comb_cat_name)

        #This is obselete now..
        ## Defining set of all the constraints
        #_lhcbc = self.comb_ws.set('lhcb_cons')
        #_cmsc = self.comb_ws.set('cms_cons')

        #if _lhcbc and _cmsc :
        #    getattr(self.comb_ws,'defineSet')('comb_cons', RooArgSet(_lhcbc, _cmsc))
        #else:
        #    print "ERROR one of the two constraint sets not found "
        #    raw_input()

#        print 'SIMUL::comb_pdf('+self.comb_cat_name+'['+catTypes_str+'],'+typeAndPdf+')'
        print ' o) Joint model pdf in self.comb_ws built! --> self.comb_pdf'
#        raw_input('ok?')
    ####################################
    # Combine the CMS and LHCb data    #
    ####################################
    def combineData(self):
        """ The LHCbs BDT and CMS allcat need to be linear in the combined data.
            Here, we define a combined category of them both, and import."""

        #List all the variables in the combined data
        comb_data_vars = RooArgSet( self.comb_ws.var('B_s0_MM'), \
                                    self.comb_ws.cat(self.comb_cat_name), \
                                    self.comb_ws.var('Mass'), \
                                    self.comb_ws.var('ReducedMassRes'))

        print ' o) Creating a category for the combination experiment'

        #self.comb_cms_data = RooDataSet('comb_cms_data', 'CMS data', RooArgSet(self.comb_ws.var('B_s0_MM'),self.cms_cat,self.comb_ws.var('Mass'),self.cms_cat), RooFit.Index(self.comb_ws.cat(self.comb_cat_name)), RooFit.Import('CMS', self.cms_data))
        #self.comb_lhcb_data = RooDataSet('comb_lhcb_data', 'lhcb data', RooArgSet(self.comb_ws.var('B_s0_MM'),self.lhcb_cat,self.comb_ws.var('Mass'),self.lhcb_cat), RooFit.Index(self.comb_ws.cat(self.comb_cat_name)), RooFit.Import('lhcb', self.lhcb_data))
        #self.comb_cms_data = RooDataSet('comb_cms_data', 'Combined cms+CMS data', RooArgSet(self.comb_ws.var('B_s0_MM'),self.cms_cat,self.comb_ws.var('Mass'),self.cms_cat), RooFit.Index(self.comb_ws.cat(self.comb_cat_name)), RooFit.Import('CMS', self.cms_data), RooFit.Import('cms', self.cms_data))

        lhcb_cat = self.lhcb_cat.GetName()
        cms_cat = self.cms_cat.GetName()

        #Take the category, set a state, pick the data, add it
        #Append data
        #To append the data, we need all the variables in the setw
        print " o) add column to CMS data "
#        lhcb_mass =  self.comb_ws.var('B_s0_MM')
#        lhcb_mass.setVal(42)
        mass_MeV = RooFormulaVar("B_s0_MM","@0*(1.e3)",RooArgList(self.comb_ws.var("Mass")))
        self.cms_data.addColumn(mass_MeV)
        lhcb_mass = self.comb_ws.var('B_s0_MM')

        self.cms_data.Print('v')
        #raw_input('ok?')

        print " o) add columns to LHCb data "
        cms_mass =  self.comb_ws.var('Mass')
        cms_mass.setVal(-42)
        self.lhcb_data.addColumn(cms_mass)
        cms_red = self.comb_ws.var("ReducedMassRes")
        cms_red.setVal(-42)
        self.lhcb_data.addColumn(cms_red)
        self.lhcb_data.Print('v')



        print ' o) add a category for the experiment' #for plotting
        expcat = RooCategory("expcat","expcat")
        expcat.defineType("dataLHCb")
        expcat.defineType("dataCMS")
        self.comb_expcat = expcat


        print " o) setup the comb data with first category"
        i = 0 #The first one to set the comb_data
        comb_data = RooDataSet("comb_data","comb_data",RooArgSet(lhcb_mass, cms_mass, cms_red, self.comb_cat, self.comb_expcat))

        data = getattr(self.lhcb_data,'reduce')(lhcb_cat+'=='+lhcb_cat+"::"+str(i))

        #Category for the fit
        self.comb_cat.setLabel(self.catTypes[i])
        data.addColumn(self.comb_cat)
        #Experiment category (used for plotting)
        expcat.setLabel("dataLHCb")
        data.addColumn(expcat)

        comb_data.append(data)
        comb_data.Print("v")
        #raw_input('ok?')

        print ' LHCB, ADDED: ' , lhcb_cat+'=='+str(i), '  catType = ', self.catTypes[i]

        comb_data.Print('v')

        for i in range(1,8):
            data = getattr(self.lhcb_data,'reduce')(lhcb_cat+'=='+lhcb_cat+"::"+str(i))

            self.comb_cat.setLabel(self.catTypes[i])
            data.addColumn(self.comb_cat)

            #Add experiment category
            expcat.setLabel("dataLHCb")
            data.addColumn(expcat)

            comb_data.append(data)
            print ' LHCB, ADDED: ' , lhcb_cat+'=='+str(i), '  catType = ', self.catTypes[i]

            comb_data.Print('v')
            #raw_input('ok?')

        for x in range(8,len(self.catTypes)):
            i = x-8
            data = getattr(self.cms_data,'reduce')(cms_cat+'=='+str(i))

            self.comb_cat.setLabel(self.catTypes[x])
            data.addColumn(self.comb_cat)

            #Add CMS category
            expcat.setLabel("dataCMS")
            data.addColumn(expcat)

            comb_data.append(data)
            print ' CMS, ADDED: ' , cms_cat+'=='+str(i), '  catType = ', self.catTypes[x], " with entries ", data.numEntries(), " sum = ", data.sumEntries()

            comb_data.Print('v')
            #raw_input('ok?')


        comb_data.SetNameTitle('comb_data','The combined dataset for LHCb and CMS')
        comb_data.Print('v')
        getattr(self.comb_ws,'import')(comb_data,'comb_data')
        self.comb_data = self.comb_ws.obj('comb_data')
        self.comb_data.Print('v')
        mydata =  getattr(self.comb_data,'reduce')("comb_cat==comb_cat::CMS_bin_1")
        mydata.Print("v")
        print "proviamo: ", mydata.numEntries()


    ## RooDataSet* mydata[nBinning] = {data1,data2,data3,data4,
    ##     			    data5,data6,data7,data8};
    ## map<string,RooDataSet*> data_map;
    ## for (Int_t b = 0; b< nBinning; b++){
    ##   TString _bin="bin" ;  _bin += b+1;
    ##   data_map[string(_bin)] = mydata[b];
    ## }
    ## RooDataSet *combData =
    ##   new RooDataSet("combData", "combined data",
    ##     	     RooArgSet(*mass), Index(binning), Import(data_map));


    #############################################
    # Functions necessary for different fit cases#
    #############################################
    def getFitArgs(self, offset = 1, nCPU = 8):
        """ Build the default fitTo arguments. """

        def_arg_list = RooLinkedList()
        def_arg_list.Add(RooFit.Minimizer('OldMinuit','minimize')) #Default
        #def_arg_list.Add(RooFit.Minimizer('OldMinuit','migrad'))
        #def_arg_list.Add(RooFit.Minimizer('Minuit2','migrad'))

        #def_arg_list.Add(RooFit.Minimizer('Minuit2','minimize'))
        #def_arg_list.Add(RooFit.Minimizer('Minuit2','scan'))
        #def_arg_list.Add(RooFit.Minimizer('Minuit','migrad'))

        #def_arg_list.Add(RooFit.Minos(kTRUE))
        def_arg_list.Add(RooFit.Strategy(2))
        def_arg_list.Add(RooFit.Save()) #Save result
        def_arg_list.Add(RooFit.Hesse(1))
        def_arg_list.Add(RooFit.NumCPU(nCPU))
        def_arg_list.Add(RooFit.Optimize(1))
        def_arg_list.Add(RooFit.Offset(offset))
        #def_arg_list.Add(RooFit.Verbose(1))
        def_arg_list.Add(RooFit.Extended())
        #def_arg_list.Add(RooFit.Timer(1)) #Times the CPU and wall clock consumption
        #def_arg_list.Add(RooFit.PrintLevel(3))

        return def_arg_list

    def writeNLLtoFile(self, suffix, nll,fitResult):
        nll_val = nll.getVal()
        #nll_offset = nll.offset()
        #nll_offCarry= nll.offsetCarry()
        minFCN = fitResult.minNll() #Get the minimum from the fit
        fitEDM = fitResult.edm() #Get the distance from minimum (estimate!!)

        nllFile = self.resDir + 'fitNLL_'+suffix+'_'+self.combName+'.txt'
        f = open(nllFile,'w')
        print >> f, '#----------------------------------------#'
        print >> f, '  This is the -log(L) of the fitted model:', self.combName
        print >> f, '   nll = pdf.createNLL(..ExternalConstraints()..)'
        print >> f, '   -log(L) = nll.getVal()      = ', nll_val
        #print >> f, '             nll.offset()      = ', nll_offset
        #print >> f, '             nll.offsetCarry() = ', nll_offCarry
        print >> f, '   fitResult.minNll()          = ', minFCN
        print >> f, '   fitResult.edm()          = ', fitEDM
        print >> f, '#----------------------------------------#'
        f.close()
        content =  open(nllFile).read()
        print '  --> NLL value saved to:', nllFile
        print content

    def fitModel(self, suffix, model, constraints, data, minosVars, offset,  nCPU = 8., reFit = False, range = None):
        """ Fit a given model, with given constraints on a given dataset,
            with given configuration."""

        paramFile = self.resDir + 'fitPARAMETERS_'+suffix+'_'+self.combName+'.txt'
        resultFile = self.resDir + 'fitResult_'+suffix+'_'+self.combName+'.root'

        fit_arg_list = self.getFitArgs(offset, nCPU)
        fit_arg_list.Add(RooFit.ExternalConstraints(constraints))
        fit_arg_list.Add(RooFit.Minos(minosVars))
        if range != None :
            fit_arg_list.Add(range)
        #Create the NLL object
        nll = model.createNLL(data, fit_arg_list)
        pll = nll.createProfile(minosVars)
        fitResult = 0

        if os.path.exists(paramFile) and os.path.exists(resultFile) and  not reFit:
           # \
          # and '1' in raw_input('Read the '+suffix+' fit parameters from the file (1) or perform the fit again (0)?'):

                params = model.getParameters(data)
                params.readFromFile(paramFile)
                fRes = TFile(resultFile,'READ')
                if fRes:
                    fitResult = fRes.Get('fitResult')
                    fRes.Close()
                else: raw_input(' Reading fitResult failed!')

        else:
            #Fit and save the fitResult

            fitResult = model.fitTo(data, fit_arg_list)

            ##Fit to should to exactly this (with OldMinuit), but the result is slightly different
            #m = RooMinimizer(nll)
            #m.optimizeConst(kTRUE) #Optimize
            #m.setProfile(kTRUE) #Time
            #m.setStrategy(2)
            ##m.minimize('Minuit','minuit')
            #m.setMinimizerType('OldMinuit')
            ##m.migrad() #OldMinuit calls just this
            #m.hesse()
            #m.minos(minosVars)
            #fitResult = m.save()


            #Write the fitResult
            model.getParameters(data).writeToFile(paramFile)
            fRes = TFile(resultFile,'RECREATE')
            fitResult.Write('fitResult')
            fRes.Close()
            #Write the log likelihood
            print '  --> Fitted parameters saved to:', paramFile
            print '  --> FitResult saved to:', resultFile
            self.writeNLLtoFile(suffix, nll,fitResult)

        return nll, fitResult, pll

    #######################
    # Different fit cases #
    #######################
    def fitCMS(self, offset = 1, nCPU = 8, reFit = False):
        """ Fit the CMS model in CMS WS. """
        suffix = 'CMS'
        model = self.cms_pdf
        constraints = self.cms_ext_const
        data = self.cms_data
        minosVars = RooArgSet(self.cms_ws.var('BF_bs'), self.cms_ws.var('BF_bd'))
        self.cms_nll, self.cms_fitRes, self.cms_pll = self.fitModel(suffix, model, constraints, data, minosVars,  offset , nCPU, reFit)
        print ' ==> CMS fitted! (cms_nll, cms_fitRes, cms_pll)'


    def fitComb_CMS(self, offset = 1, nCPU = 8, useCMSconstraints = 0):
        """ Fit the CMS model in Combined WS with LHCb constraints """
        model = self.comb_cms_pdf
        constraints = self.comb_ws.set('lhcb_cons')
        if useCMSconstraints:
            constraints = self.comb_ws.set('cms_cons')
        data = self.cms_data #Use the data from the individual Ws
        minosVars = RooArgSet(self.comb_ws.var('BF_bs'), self.comb_ws.var('BF_bd'))
        self.comb_cms_nll, self.comb_cms_fitRes, self.comb_cms_pll = self.fitModel('Comb_CMS', model, constraints, data, minosVars,  offset , nCPU)
        print ' ==> CMS in Combined WS fitted! (cms_nll, cms_fitRes, cms_pll)'


    def fitLHCb(self, offset = 1,  nCPU = 8):
        """ Fit the LHCbmodel in LHCb WS. """
        model = self.lhcb_pdf
        constraints = self.lhcb_cons
        data = self.lhcb_data
        minosVars = RooArgSet(self.lhcb_ws.var('BRs'), self.lhcb_ws.var('BRd'))
        #minosVars = RooArgSet()
        self.lhcb_nll, self.lhcb_fitRes, self.lhcb_pll = self.fitModel('LHCb', model, constraints, data, minosVars,  offset , nCPU)
        print ' ==> LHCb fitted! (lhcb_nll, lhcb_fitRes)'

    def fitLHCbCustom(self, offset = 1,  nCPU = 8, fixBs = False, fixBd = False):
        """ Fit the LHCbmodel in LHCb WS: Bs only (Bd constant to 0) """
        model = self.lhcb_pdf
        constraints = self.lhcb_cons
        data = self.lhcb_data
        minosVars = RooArgSet(self.lhcb_ws.var('BRs'),self.lhcb_ws.var('BRd'))

        if fixBd :
            minosVars = RooArgSet(self.lhcb_ws.var('BRs'))
            model.getVariables()['BRd'].setConstant(True)
            model.getVariables()['BRd'].setVal(0)
            model.getVariables()['MBd'].setConstant(True)
            model.getVariables()['sigmaBd'].setConstant(True)
            model.getVariables()['timeAccCorrBd'].setConstant(True)
        if fixBs :
            minosVars = RooArgSet(self.lhcb_ws.var('BRd'))
            model.getVariables()['BRs'].setConstant(True)
            model.getVariables()['BRs'].setVal(0)
            model.getVariables()['MBs'].setConstant(True)
            model.getVariables()['sigmaBs'].setConstant(True)
            model.getVariables()['timeAccCorrBs'].setConstant(True)

        #minosVars = RooArgSet()
        self.lhcb_nll, self.lhcb_fitRes, self.lhcb_pll = self.fitModel('LHCb', model, constraints, data, minosVars,  offset , nCPU)
        print ' ==> LHCb fitted! (lhcb_nll, lhcb_fitRes)'



    def fitComb_LHCb(self, offset = 1,  nCPU = 8):
        """ Fit the LHCb model in Combined WS with LHCb constraints """

        model = self.comb_lhcb_pdf
        constraints = self.comb_ws.set('lhcb_cons')
        data = self.lhcb_data #Use the individual Ws data
        minosVars = RooArgSet(self.comb_ws.var('BRs'), self.comb_ws.var('BRd'))
        #minosVars = RooArgSet()
        self.comb_lhcb_nll, self.comb_lhcb_fitRes, self.comb_lhcb_pll = self.fitModel('Comb_LHCb', model, constraints, data, minosVars,  offset , nCPU)
        print ' ==> LHCb in Combined Ws fitted! (comb_lhcb_nll, comb_lhcb_fitRes)'


    def fitComb_separateConstr(self, offset = 1,  nCPU = 8):
        """ Fit the combined model on the combined data. """
        model = self.comb_pdf
        constraints = self.comb_ws.set('lhcb_cons')
        constraints.add(self.comb_ws.set('cms_cons'))

        data = self.comb_data #Use the individual Ws data
        #minosVars = RooArgSet(self.comb_ws.var('BRs'), self.comb_ws.var('BRd'))
        minosVars = RooArgSet()
        self.comb_nll, self.comb_fitRes, self.comb_pll = self.fitModel('Comb_LHCbCMS_sepConstr', model, constraints, data, minosVars,  offset , nCPU)
        print ' ==> Full combined WS model fitted with separate constraints! (comb_nll, comb_fitRes)'

    def fitCombinedModel(self, offset = 1,  nCPU = 8, reFit = True, fixBs = False, fixBd = False, BsZero =True, fitRatio = False):
        """ Fit the combined model on the combined data. """

        model = self.comb_pdf
#        constraints = self.comb_ws.set('lhcb_cons')
        constraints = self.comb_ws.set('comb_cons')
        constraints.Print("v")

        data = self.comb_data #Use the individual Ws data
        minosVars = RooArgSet(self.comb_ws.var('BRs'), self.comb_ws.var('BRd'))
        if fitRatio: minosVars = RooArgSet(self.comb_ws.var('BRdOverBRs'))

        addName =""

        if fixBd :
            minosVars = RooArgSet(self.lhcb_ws.var('BRs'))
            model.getVariables()['BRd'].setConstant(True)
            model.getVariables()['BRd'].setVal(0)
            model.getVariables()['MBd_LHCb'].setConstant(True)
            model.getVariables()['sigmaBd_LHCb'].setConstant(True)
            model.getVariables()['timeAccCorrBd_LHCb'].setConstant(True)
            addName += "FBd"
        if fixBs :
            minosVars = RooArgSet(self.lhcb_ws.var('BRd'))
            if BsZero :
                model.getVariables()['BRs'].setVal(0)
            model.getVariables()['BRs'].setConstant(True)
            model.getVariables()['MBs_LHCb'].setConstant(True)
            model.getVariables()['sigmaBs_LHCb'].setConstant(True)
            model.getVariables()['timeAccCorrBs_LHCb'].setConstant(True)
            model.getVariables()['fdfs'].setConstant(True)
            addName += "FBs"

        self.comb_nll, self.comb_fitRes, self.comb_pll = self.fitModel('Comb_LHCbCMS'+addName, model, constraints, data, minosVars,  offset , nCPU, reFit)
        print ' ==> Full combined WS model fitted! (comb_nll, comb_fitRes)'

    def fitCombinedModeltoLHCb(self, offset = 1,  nCPU = 8, reFit = True, fixBd = False, fixBs = False):
        """ Fit the combined model on the combined data. """

        model = self.comb_pdf
        constraints = self.comb_ws.set('lhcb_cons')
        cut = "comb_cat==comb_cat::LHCb_bin_1 || comb_cat==comb_cat::LHCb_bin_2 ||"+\
              "comb_cat==comb_cat::LHCb_bin_3 || comb_cat==comb_cat::LHCb_bin_4 ||"+\
              "comb_cat==comb_cat::LHCb_bin_5 || comb_cat==comb_cat::LHCb_bin_6 ||"+\
              "comb_cat==comb_cat::LHCb_bin_7 || comb_cat==comb_cat::LHCb_bin_8"
        print " Cut is ", cut
        lhcb_range = "LHCb_bin_1,LHCb_bin_2,LHCb_bin_3,LHCb_bin_4,LHCb_bin_5,LHCb_bin_6,LHCb_bin_7,LHCb_bin_8"
        self.comb_cat.setRange("lhcb_range",lhcb_range)
        data = getattr(self.comb_data,'reduce')(cut)
        data.Print("v")
        print " Fittin to lhcb data only, entries are ", data.numEntries()
#        minosVars = RooArgSet(self.comb_ws.var('BRs'), self.comb_ws.var('BRd'))
        minosVars = RooArgSet()
        if fixBd :
            minosVars = RooArgSet(self.lhcb_ws.var('BRs'))
            model.getVariables()['BRd'].setConstant(True)
            model.getVariables()['BRd'].setVal(0)
            model.getVariables()['MBd_LHCb'].setConstant(True)
            model.getVariables()['sigmaBd_LHCb'].setConstant(True)
            model.getVariables()['timeAccCorrBd_LHCb'].setConstant(True)
        if fixBs :
            minosVars = RooArgSet(self.lhcb_ws.var('BRd'))
            if BsZero :
                model.getVariables()['BRs'].setVal(0)
            model.getVariables()['BRs'].setConstant(True)
            model.getVariables()['MBs_LHCb'].setConstant(True)
            model.getVariables()['sigmaBs_LHCb'].setConstant(True)
            model.getVariables()['timeAccCorrBs_LHCb'].setConstant(True)
            model.getVariables()['fdfs'].setConstant(True)

        self.comb_nll, self.comb_fitRes, self.comb_pll = self.fitModel('Comb_LHCbCMS', model, constraints, data, minosVars,  offset , nCPU, RooFit.Range("lhcb_range") )
        print ' ==> Full combined WS model fitted! (comb_nll, comb_fitRes)'

    def fitCombinedModeltoCMS(self, offset = 1,  nCPU = 8, reFit = True):
        """ Fit the combined model on the combined data. """

        model = self.comb_pdf
        constraints = self.comb_ws.set('lhcb_cons')
        cut = "comb_cat==comb_cat::CMS_bin_1 || comb_cat==comb_cat::CMS_bin_2 ||"+\
              "comb_cat==comb_cat::CMS_bin_3 || comb_cat==comb_cat::CMS_bin_4 ||"+\
              "comb_cat==comb_cat::CMS_bin_5 || comb_cat==comb_cat::CMS_bin_6 ||"+\
              "comb_cat==comb_cat::CMS_bin_7 || comb_cat==comb_cat::CMS_bin_8 ||"+\
              "comb_cat==comb_cat::CMS_bin_9 || comb_cat==comb_cat::CMS_bin_10 ||"+\
              "comb_cat==comb_cat::CMS_bin_11 || comb_cat==comb_cat::CMS_bin_12"

        print " Cut is ", cut
        cms_range = "CMS_bin_1,CMS_bin_2,CMS_bin_3,CMS_bin_4,CMS_bin_5,CMS_bin_6,CMS_bin_7,CMS_bin_8,CMS_bin_9,CMS_bin_10,CMS_bin_11,CMS_bin_12"
        self.comb_cat.setRange("cms_range",cms_range)
        data = getattr(self.comb_data,'reduce')(cut)
        data.Print("v")
        print " Fittin to cms data only, entries are ", data.numEntries()
#        minosVars = RooArgSet(self.comb_ws.var('BRs'), self.comb_ws.var('BRd'))
        minosVars = RooArgSet()
        self.comb_nll, self.comb_fitRes, self.comb_pll = self.fitModel('Comb_LHCbCMS', model, constraints, data, minosVars,  offset , nCPU, RooFit.Range("cms_range") )
        print ' ==> Full combined WS model fitted! (comb_nll, comb_fitRes)'

#################################################
# Compare the mean mass values for LHCb and CMS
#################################################


    def getCMSMassMean(self, ch='bs', suf = '_CMS'):

        ws=self.comb_ws
        cms_channels = 4
        cms_index_max = [2,2,4,4]
        means = []
        sigmas = []

        sumOfWVals = 0
        sumOfWeights = 0

        for i in range(0,cms_channels):
            for j in range(0,cms_index_max[i]):

                b = '_'+str(i)+'_'+str(j) + suf
                mean = ws.var('Mean_'+ch+b).getVal()
                error = ws.var('Mean_'+ch+b).getError()
                weight = (1./(error*error))

                sumOfWVals+=weight*mean
                sumOfWeights+=weight

        average = sumOfWVals/sumOfWeights

        print ' CMS Mass average for ',ch,' = ', average
        return average

#################################################
# Get the yields from the combined LHCb and CMS
# with normalisatio included
#################################################

    def getOneOverBR(self):
        rat = self.comb_ws.obj('BRsOverBRd')
        a = valAndErr(rat.getVal(),rat.getError())
        b = valAndErr(1.,0.).over(a)
        print '  BRd/BRs = %.4f +- %.4f' % (b.getVal(),b.getErr())
        return b

    def getBRRatio(self, fitRatio = False):
        """ Calculate the BR(Bs)/BR(Bd) ratio from the NBs/NBd * fd/fs"""
        print '----------------------------------------------------'

        ws = self.comb_ws
        #LHCb yields
        print ' LHCb yields:'
        NBs_tot_LHCb = valAndErr(0,0)
        NBd_tot_LHCb = valAndErr(0,0)

        for i in range(1,9):
            suf = '_LHCb'

            NBs_val = ws.obj('NBs'+str(i)+suf).getVal()
            NBs_err = 'P'
            NBs = valAndErr(NBs_val,NBs_err)

            NBd_val = ws.obj('NBd'+str(i)+suf).getVal()
            NBd_err = 'P'
            NBd = valAndErr(NBd_val,NBd_err)

            NBs_tot_LHCb = NBs_tot_LHCb.plus(NBs)
            NBd_tot_LHCb = NBd_tot_LHCb.plus(NBd)

            print '  Bin :',i
            print '     NBs = %.2f +- %.2f' % (NBs.getVal(),NBs.getErr())
            print '     NBd = %.2f +- %.2f' % (NBd.getVal(),NBd.getErr())

       #Total (the total yields from the fit, use those)
        NBs_LHCb_val = ws.obj('NBs_LHCb').getVal()
        NBd_LHCb_val = ws.obj('NBd_LHCb').getVal()
        NBs_LHCb_err = 'P' #RooFormula var has no getError()
        NBd_LHCb_err = 'P' #RooFormula var has no getError()
        if fitRatio:
            NBs_LHCb_err = ws.obj('NBs_LHCb').getError()
            NBs_LHCb_err = ws.obj('NBd_LHCb').getError()
        NBs_LHCb = valAndErr(NBs_LHCb_val,NBs_LHCb_err)
        NBd_LHCb = valAndErr(NBd_LHCb_val,NBd_LHCb_err)

        #Calculate the ratio for LHCb:
        #RooBifurGauss::fdfs_const_LHCb[ x=fdfs mean=fdfs_mean_LHCb sigmaL=fdfs_sigmaL_LHCb sigmaR=fdfs_sigmaR_LHCb ] = 0.999986
        sigmaL = ws.obj('fdfs_sigmaL_LHCb').getVal()
        sigmaR = ws.obj('fdfs_sigmaR_LHCb').getVal()
        fdfsErr =  (sigmaL+sigmaR)/2.
        print ' Calculating fdfs unc:'
        print '     sigma L =' , sigmaL
        print '     sigma R =' , sigmaR
        print '     Average =' , fdfsErr
        fdfs_lhcb = valAndErr(ws.obj('fdfs_mean_LHCb').getVal(), fdfsErr)
        brrat_LHCb = NBs_LHCb.over(NBd_LHCb).times(fdfs_lhcb)

        print '----------------------------------------------------'

        #CMS yields
        cms_channels = 4
        cms_index_max = [2,2,4,4]
        suf = '_CMS'
        print ' CMS yields:'
        NBs_tot_CMS = valAndErr(0.,0.)
        NBd_tot_CMS = valAndErr(0.,0.)

        for i in range(0,cms_channels):
            for j in range(0,cms_index_max[i]):
                b = '_CombFormula_'+str(i)+'_'+str(j)
                if fitRatio:
                    b = '_Var_'+str(i)+'_'+str(j) + suf

                print '  Bin :'+b
                NBs_val = ws.obj('N_bs'+str(b)).getVal()
                NBd_val = ws.obj('N_bd'+str(b)).getVal()
                NBs_err = 'P'
                NBd_err = 'P'
                if fitRatio:
                    NBs_err = ws.obj('N_bs'+str(b)).getError()
                    NBd_err = ws.obj('N_bd'+str(b)).getError()

                NBs = valAndErr(NBs_val,NBs_err)
                NBd = valAndErr(NBd_val,NBd_err)
                print '     NBs = %.2f +- %.2f' % (NBs.getVal(), NBs.getErr())
                print '     NBd = %.2f +- %.2f' % (NBd.getVal(), NBd.getErr())
                NBs_tot_CMS = NBs_tot_CMS.plus(NBs)
                NBd_tot_CMS = NBd_tot_CMS.plus(NBd)

        #Calculate the ratio for CMS:
        fdfs_cms = valAndErr(1.,0.05).times(fdfs_lhcb) #Scale the fdfs with 5% additional unc.
        brrat_CMS = NBs_tot_CMS.over(NBd_tot_CMS).times(fdfs_cms)

        #####################
        # Combined BRs/BRd
        #####################
        #Average:
        NBs_tot = NBs_LHCb.plus(NBs_tot_CMS)
        NBd_tot = NBd_LHCb.plus(NBd_tot_CMS)
        brsbrd= NBs_tot.over(NBd_tot).times(fdfs_lhcb) #BRs/BRd
        brrat = valAndErr(1.,0.).over(brsbrd) #BRd/BRs

        brrat_CMS = valAndErr(1.,0.).over(brrat_CMS) #BRd/BRs
        brrat_LHCb = valAndErr(1.,0.).over(brrat_LHCb) #BRd/BRs

        print '----------------------------------'
        print ' Total LHCb yields by adding up the yields with Poissonian errors:'
        print ' NBs = %.2f +- %.2f' % (NBs_tot_LHCb.getVal(),NBs_tot_LHCb.getErr())
        print ' NBd = %.2f +- %.2f' % (NBd_tot_LHCb.getVal(),NBd_tot_LHCb.getErr())
        print '----------------------------------'
        print ' Total LHCb yields from the fit:'
        print ' NBs = %.2f +- %.2f' % (NBs_LHCb.getVal(),NBs_LHCb.getErr())
        print ' NBd = %.2f +- %.2f' % (NBd_LHCb.getVal(),NBd_LHCb.getErr())
        print ' fdfs = %.5f +- %.5f ' % (fdfs_lhcb.getVal(),fdfs_lhcb.getErr())
        print ' BRs/BRd = NBd/NBs * fd/fs = %.6f +- %.6f' % (brrat_LHCb.getVal(),brrat_LHCb.getErr())
        print ' LHCb: BRd/BRs = NBd/NBs * fs/fd  = %.6f +- %.6f' % (brrat_LHCb.getVal(),brrat_LHCb.getErr())
        print ' ------------------------- '
        print ' Total CMS yields from the fit (summed over categories):'
        print ' NBs = %.2f +- %.2f' % (NBs_tot_CMS.getVal(),NBs_tot_CMS.getErr())
        print ' NBd = %.2f +- %.2f' % (NBd_tot_CMS.getVal(),NBd_tot_CMS.getErr())
        print ' fdfs_cms = %.6f +- %.6f ' % (fdfs_cms.getVal(),fdfs_cms.getErr())
        print ' CMS : BRd/BRs = NBd/NBs * fs/fd* = %.6f +- %.6f' % (brrat_CMS.getVal(),brrat_CMS.getErr())
        print '----------------------------------'
        print ' Combined (NBd_tot / NBd_tot)*(fs/fd) assuming LHCb fsfd for CMS:'
        print '       BRd/BRs =  %.6f +- %.6f' % (brrat.getVal(),brrat.getErr())
        print '----------------------------------'


##########################################
# Plotting functions
##########################################


    def plot2DContour(self, res, var1, var2):
        canva = TCanvas("contour","contour")
        f = RooPlot(-5,10,-5,10)
        f.GetXaxis().SetLabelSize(0.)
        f.GetYaxis().SetLabelSize(0.)

        res.plotOn(f,var1,var2,'ME12VHB')

        f.GetXaxis().SetRange(0,10)
        f.GetYaxis().SetRange(0,10)

        f.Draw()
        canva.SaveAs(self.resDir+'Plot_'+self.combName+'_Contour.pdf')

        return canva

    def plotLHCb(self):
        """ Plot LHCb mass fit in bins for LHCb only WS."""

        canva = TCanvas("lhcb","lhcb")
        canva.Divide(4,2)
        mass = self.lhcb_mass
        model = self.lhcb_pdf
        data = self.lhcb_data
        category = self.lhcb_cat

        lhcb_channels = 8
        frames = []
        for i in range(0,lhcb_channels):

            canva.cd(i+1)
            cat = str(i)
            b = str(i+1)
            frame = mass.frame(RooFit.Bins(25), RooFit.Title('LHCb Bin: '+b))
            frames.append(frame)

            data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.Invisible())
            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack))

            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                            RooFit.Components('model Bs'+b),RooFit.LineColor(kRed),RooFit.LineStyle(9),
                            RooFit.FillColor(kRed), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                            RooFit.Components('model Bd'+b),RooFit.LineColor(kGreen),RooFit.LineStyle(9),
                            RooFit.FillColor(kGreen), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                            RooFit.Components('B2Xmunu'+b),RooFit.LineColor(kBlack),RooFit.LineStyle(9),
                            RooFit.FillColor(kBlack), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                            RooFit.Components('LaPmunu'+b),RooFit.LineColor(kOrange),RooFit.LineStyle(9),
                            RooFit.FillColor(kOrange), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                            RooFit.Components('B0upimumu'+b),RooFit.LineColor(kCyan),RooFit.LineStyle(9),
                            RooFit.FillColor(kCyan), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                            RooFit.Components('missid'+b),RooFit.LineColor(kMagenta),RooFit.LineStyle(9),
                            RooFit.FillColor(kMagenta), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))


            data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.MarkerSize(0.6))
            frame.Draw()

        canva.SaveAs(self.resDir+'Plot_'+self.combName+'_LHCb_massFitInBins.pdf')

        return canva


    def plotCMS(self):
        """ Plot CMS mass fit in bins for CMS only WS."""

        canva = TCanvas("cms","cms")
        canva.Divide(4,3)
        mass = self.cms_mass
        model = self.cms_pdf
        data = self.cms_data
        category = self.cms_cat

        catNr = 0
        cms_channels = 4
        cms_index_max = [2,2,4,4]
        frames = []
        for i in range(0,cms_channels):
            for j in range(0,cms_index_max[i]):

                canva.cd(catNr+1)
                b = '_'+str(i)+'_'+str(j)
                cat = 'allcat_'+str(catNr)

                frame = mass.frame(RooFit.Bins(25), RooFit.Title('CMS Bin: '+b))
                frames.append(frame)
                data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.Invisible())
                model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack))

                #"pdf_bs"
                model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                RooFit.Components("pdf_bs"+b),RooFit.LineColor(kRed),RooFit.LineStyle(9),
                                RooFit.FillColor(kRed), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))
                #"pdf_bd"
                model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                RooFit.Components("pdf_bd"+b),RooFit.LineColor(kGreen),RooFit.LineStyle(7),
                                RooFit.FillColor(kGreen), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

                #"pdf_semi"
                model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                RooFit.Components("pdf_semi"+b),RooFit.LineColor(kBlack),RooFit.LineStyle(kDotted),
                                RooFit.FillColor(kBlack), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

                #"pdf_peak"
                model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                RooFit.Components("pdf_peak"+b),RooFit.LineColor(kMagenta),RooFit.LineStyle(kDotted),
                                RooFit.FillColor(kMagenta), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

                #"pdf_comb" the Exponent
                model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                RooFit.Components("pdf_comb"+b),RooFit.LineColor(kBlue),RooFit.LineStyle(kDotted))
                                #,RooFit.FillColor(kRed), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

                #"pdf_1comb" the Poly
                model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                RooFit.Components("pdf_1comb"+b),RooFit.LineColor(kCyan),RooFit.LineStyle(kDotted))
                                #,RooFit.FillColor(kRed), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

                data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.MarkerSize(0.6))
                frame.Draw()
                catNr+=1


        canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CMS_massFitInBins.pdf')

        return canva


    def plotComb(self,separateLHCbSemiLep = False, cmsInMeV = False, lhcbMax = 6000, sigFillStyle = 1001, bkgFillStyle = 3003, printWeights = False, separateLHCbbkg = False, separateCMSbkg=False,linew = 1):
        """ Plot LHCb and CMS mass fit in bins for combined WS."""

        canva = TCanvas("comb","comb",1200,800)
        canva.Divide(5,4)

        mass_lhcb = self.lhcb_mass
        self.lhcb_mass.setRange('LHCbrange',4900,6000)

        mass_cms = self.cms_mass
        self.cms_mass.setRange('CMSrange',4.900,5.9)

        if cmsInMeV:
            #Change to the same mass variable and range
            self.lhcb_mass.setRange(4900,lhcbMax)
            self.lhcb_mass.setRange('LHCbrange',4900,lhcbMax)
            self.lhcb_mass.setRange('CMSrange',4900,5900)
            mass_cms = self.lhcb_mass

        model= self.comb_pdf
        data = self.comb_data
        category = self.comb_cat
        cms_bins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3']

        frames = []
        wtxt=[]
        for i in range(0,20):

                canva.cd(i+1)
                cat = str(i)
                #LHCb
                if i < 8:
                    frame = mass_lhcb.frame(RooFit.Bins(25), RooFit.Title('LHCb Bin: '+str(i+1)))
                    frames.append(frame)
                    b = str(i+1)+'_LHCb'

                    data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.Invisible(),RooFit.CutRange('LHCbrange'))
                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),RooFit.Range('LHCbrange'),RooFit.LineWidth(linew))

                    if not separateLHCbbkg:
                        #Background combined to one component
                        lhcb_components = 'bkg1 MuMu model'+b+',missid'+b+',B2Xmunu'+b+',LaPmunu'+b+',B0upimumu'+b
                        model.plotOn(frame,RooFit.Components(lhcb_components),
                                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
                                    RooFit.LineStyle(9),RooFit.FillColor(kBlack),
                                    RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('LHCbrange'))

                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                    RooFit.Components('model Bs'+b),RooFit.LineColor(kRed),RooFit.LineStyle(9),
                                    RooFit.FillColor(kRed), RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('LHCbrange'))

                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                    RooFit.Components('model Bd'+b),RooFit.LineColor(kGreen),RooFit.LineStyle(9),
                                    RooFit.FillColor(kGreen), RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('LHCbrange'))

                    if separateLHCbbkg:
                        if separateLHCbSemiLep:
                            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                            RooFit.Components('B2Xmunu'+b),RooFit.LineColor(kBlack),RooFit.LineStyle(9),
                                            RooFit.FillColor(kBlack), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('LHCbrange'))

                            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                            RooFit.Components('LaPmunu'+b),RooFit.LineColor(kOrange),RooFit.LineStyle(9),
                                            RooFit.FillColor(kOrange), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('LHCbrange'))

                            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                            RooFit.Components('B0upimumu'+b),RooFit.LineColor(kCyan),RooFit.LineStyle(9),
                                            RooFit.FillColor(kCyan), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('LHCbrange'))
                        else:
                            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                            RooFit.Components('B2Xmunu'+b+',LaPmunu'+b+',B0upimumu'+b),RooFit.LineColor(kBlack),RooFit.LineStyle(9),
                                            RooFit.FillColor(kBlack), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('LHCbrange'))

                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components('missid'+b),RooFit.LineColor(kMagenta),RooFit.LineStyle(9),
                                        RooFit.FillColor(kMagenta), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('LHCbrange'))

                        #bkg1 MuMu model
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components('bkg1 MuMu model'+b),RooFit.LineColor(kBlue),RooFit.LineStyle(kDotted),RooFit.Range('LHCbrange'))

                    data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.MarkerSize(0.4),RooFit.MarkerColor(kBlue),RooFit.CutRange('LHCbrange'))


                else: #CMS
                    b = cms_bins[i-8]
                    if cmsInMeV:
                        b = b+'_CMS'
                        mass_cms.setRange(4900,5900) #Set to CMS range

                    frame = mass_cms.frame(RooFit.Bins(25), RooFit.Title('CMS Bin: '+str(i-7)))
                    frames.append(frame)

                    data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.Invisible(),RooFit.CutRange('CMSrange'))
                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),RooFit.Range('CMSrange'),RooFit.LineWidth(linew))

                    if not separateCMSbkg:
                        #Background combined to one component
                        cms_components = 'pdf_semi_'+b+',pdf_peak_'+b+',pdf_1comb_'+b
                        model.plotOn(frame,RooFit.Components(cms_components),
                                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
                                    RooFit.LineStyle(9),RooFit.FillColor(kBlack),
                                    RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

                    #"pdf_bs"
                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                    RooFit.Components("pdf_bs_"+b),RooFit.LineColor(kRed),RooFit.LineStyle(9),
                                    RooFit.FillColor(kRed), RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))
                    #"pdf_bd"
                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                    RooFit.Components("pdf_bd_"+b),RooFit.LineColor(kGreen),RooFit.LineStyle(9),
                                    RooFit.FillColor(kGreen), RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

                    if separateCMSbkg:
                        #"pdf_semi"
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components("pdf_semi_"+b),RooFit.LineColor(kBlack),RooFit.LineStyle(9),
                                        RooFit.FillColor(kBlack), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

                        #"pdf_peak"
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components("pdf_peak_"+b),RooFit.LineColor(kMagenta),RooFit.LineStyle(9),
                                        RooFit.FillColor(kMagenta), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))


                        #One of those (Exp, or Poly) will not be in the pdf
                        #"pdf_comb" the Exponent
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components("pdf_comb_"+b),RooFit.LineColor(kBlue),RooFit.LineStyle(kDotted),RooFit.Range('CMSrange'))
                                        #,RooFit.FillColor(kRed), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

                        #"pdf_1comb" the Poly
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components("pdf_1comb_"+b),RooFit.LineColor(kCyan),RooFit.LineStyle(kDotted),RooFit.Range('CMSrange'))
                                    #,RooFit.FillColor(kRed), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))


                    data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlue),RooFit.CutRange('CMSrange'))


                #Add the normalized S/S+B weight, if it has been calculated
                if printWeights:
                    print 'Add weight info..'
                    txt = TText(0.355,0.8,"S/(S+B)=%1.4f" % self.normWeights[i])
                    txt.SetNDC()
                    txt.SetTextSize(0.1)
                    txt.SetTextColor(kRed)
                    wtxt.append(txt)
                    frame.addObject(wtxt[-1])

                frame.Draw()

        canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CMS_massFitInBins.pdf')

        return canva



    #Plot the CMS and LHCb data on one plot
    def plotCombinedMassAllBins(self, bins = 25):
        """ Plot LHCb and CMS data in best bin on same scale 4900-5900
            Works only with the same mass scale and variable."""

        print ' Plotting LHCb and CMS together on one mass plot...'

        canva = TCanvas("cmslhcbMeV","cmslhcbMeV")

        #Change to the same mass variable and range
        mass = self.comb_ws.obj('B_s0_MM')
        mass.setRange(4900,5900)
        mass.setRange('CMSrange',4900,5900)

        model = self.comb_pdf
        data = self.comb_data
        category = self.comb_cat

        #All LHCb+CMS bins
        frame = mass.frame(RooFit.Bins(bins), RooFit.Title('LHCb+CMS All data in 4900-5900MeV range'))
        data.plotOn(frame, RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlack))
        model.plotOn(frame,RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),RooFit.Range('CMSrange'))
        frame.Draw()

        canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_AllBins.pdf')
        return canva

    def plotCombinedMassBestBins8(self, bins = 25, separateSignal = False,rangeMax = 5900, sigFillStyle = 1001, bkgFillStyle = 3003):
        """ Plot LHCb and CMS data stacked on top of eachother
            Works only with the same mass scale and variable. Best bins!"""

        print ' Plotting LHCb and CMS together on one mass plot for the best bins only...'

        canva = TCanvas("cmslhcbMeV_best","cmslhcbMeV_best")

        #Change to the same mass variable and range
        mass = self.comb_ws.obj('B_s0_MM')
        mass.setRange(4900,rangeMax)
        mass.setRange('CMSrange',4900,rangeMax)

        model = self.comb_pdf
        data = self.comb_data
        category = self.comb_cat
        cms_bins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3']


        #Best LHCb+CMS bins
        cut_cms_B =     "comb_cat==comb_cat::CMS_bin_2 ||"+\
                        "comb_cat==comb_cat::CMS_bin_8 ||"+\
                        "comb_cat==comb_cat::CMS_bin_12||"+\
                        "comb_cat==comb_cat::CMS_bin_7 "

        cut_lhcb_B=     "comb_cat==comb_cat::LHCb_bin_5 ||"+\
                        "comb_cat==comb_cat::LHCb_bin_6 ||"+\
                        "comb_cat==comb_cat::LHCb_bin_7 || comb_cat==comb_cat::LHCb_bin_8 "

        frame = mass.frame(RooFit.Bins(bins), RooFit.Title('LHCb(5,6,7,8)+CMS(2,7,8,12) ; m_{#mu#mu} (MeV)'))

        data.plotOn(frame, RooFit.Cut(cut_lhcb_B+'||'+cut_cms_B),RooFit.Invisible())

        #Total pdf
        cms_components = "pdf_ext_total_0_1*,pdf_ext_total_2_3*,pdf_ext_total_3_3*,pdf_ext_total_2_2*,"
        lhcb_components = "mumu_model_5*,mumu_model_6*,mumu_model_7*,mumu_model_8*"
        model.plotOn(frame,RooFit.Components(cms_components+lhcb_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),RooFit.Range('CMSrange'))

        #Background
        cms_components = "pdf_semi_0_1*,pdf_semi_2_3*,pdf_semi_3_3*,pdf_semi_2_2*,"+\
                        "pdf_peak_0_1*,pdf_peak_2_3*,pdf_peak_3_3*,pdf_peak_2_2*,"+\
                        "pdf_1comb_0_1*,pdf_1comb_2_3*,pdf_1comb_3_3*,pdf_1comb_2_2*"

        lhcb_components = 'bkg1 MuMu model5*,bkg1 MuMu model6*,bkg1 MuMu model7*,bkg1 MuMu model8*,'+\
                            'missid5*,missid6*,missid7*,missid8*,'+\
                            'B2Xmunu5*,B2Xmunu6*,B2Xmunu7*,B2Xmunu8*,'+\
                            'LaPmunu5*,LaPmunu6*,LaPmunu7*,LaPmunu8*,'+\
                            'B0upimumu5*,B0upimumu6*,B0upimumu7*,B0upimumu8*'
        model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
                    RooFit.LineStyle(9),RooFit.FillColor(kBlack),
                    RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        if separateSignal:
            data.plotOn(frame, RooFit.Cut(cut_cms_B),RooFit.Invisible())
            #CMS Bs
            cms_components = "pdf_bs_0_1*,pdf_bs_2_3*,pdf_bs_3_3*,pdf_bs_2_2*"
            model.plotOn(frame,RooFit.Components(cms_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kRed),
                        RooFit.LineStyle(9),RooFit.FillColor(kRed),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))
            #CMS Bd
            cms_components = "pdf_bd_0_1*,pdf_bd_2_3*,pdf_bd_3_3*,pdf_bd_2_2*"
            model.plotOn(frame,RooFit.Components(cms_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kGreen),
                        RooFit.LineStyle(9),RooFit.FillColor(kGreen),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

            data.plotOn(frame, RooFit.Cut(cut_lhcb_B),RooFit.Invisible())
            #LHCb Bs
            lhcb_components = "model Bs5*,model Bs6*,model Bs7*,model Bs8*"
            model.plotOn(frame,RooFit.Components(lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kMagenta),
                        RooFit.LineStyle(9),RooFit.FillColor(kMagenta),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))
            #LHCb Bd
            lhcb_components = "model Bd5*,model Bd6*,model Bd7*,model Bd8*"
            model.plotOn(frame,RooFit.Components(lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),
                        RooFit.LineStyle(9),RooFit.FillColor(kBlue),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        else:
            #Bs
            cms_components = "pdf_bs_0_1*,pdf_bs_2_3*,pdf_bs_3_3*,pdf_bs_2_2*"
            lhcb_components = "model Bs5*,model Bs6*,model Bs7*,model Bs8*"
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kRed),
                        RooFit.LineStyle(9),RooFit.FillColor(kRed),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

            #Bd
            cms_components = "pdf_bd_0_1*,pdf_bd_2_3*,pdf_bd_3_3*,pdf_bd_2_2*"
            lhcb_components = "model Bd5*,model Bd6*,model Bd7*,model Bd8*"
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kGreen),
                        RooFit.LineStyle(9),RooFit.FillColor(kGreen),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        data.plotOn(frame, RooFit.Cut(cut_lhcb_B+'||'+cut_cms_B),RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlue))

        frame.Draw()
        if separateSignal:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_Best8Bins_SepSign.pdf')
        else:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_Best8Bins.pdf')

        return canva



    def plotCombinedMassBestBins(self, bins = 25, separateSignal = False,rangeMax = 5900, sigFillStyle = 1001, bkgFillStyle = 3003):
        """ Plot LHCb and CMS data stacked on top of eachother
            Works only with the same mass scale and variable. Best bins!"""

        print ' Plotting LHCb and CMS together on one mass plot for the best bins only...'

        canva = TCanvas("cmslhcbMeV_best","cmslhcbMeV_best")

        #Change to the same mass variable and range
        mass = self.comb_ws.obj('B_s0_MM')
        mass.setRange(4900,rangeMax)
        mass.setRange('CMSrange',4900,rangeMax)

        model = self.comb_pdf
        data = self.comb_data
        category = self.comb_cat
        cms_bins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3']


        #Best LHCb+CMS bins
        cut_cms_B =     "comb_cat==comb_cat::CMS_bin_2 ||"+\
                        "comb_cat==comb_cat::CMS_bin_8 ||"+\
                        "comb_cat==comb_cat::CMS_bin_12 "

        cut_lhcb_B=     "comb_cat==comb_cat::LHCb_bin_6 ||"+\
                        "comb_cat==comb_cat::LHCb_bin_7 || comb_cat==comb_cat::LHCb_bin_8 "

        frame = mass.frame(RooFit.Bins(bins), RooFit.Title('LHCb(6,7,8)+CMS(2,8,12) ; m_{#mu#mu} (MeV)'))

        data.plotOn(frame, RooFit.Cut(cut_lhcb_B+'||'+cut_cms_B),RooFit.Invisible())


        #Total pdf
        cms_components = "pdf_ext_total_0_1*,pdf_ext_total_2_3*,pdf_ext_total_3_3*,"
        lhcb_components = "mumu_model_6*,mumu_model_7*,mumu_model_8*"
        model.plotOn(frame,RooFit.Components(cms_components+lhcb_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),RooFit.Range('CMSrange'))

        #Background
        cms_components = "pdf_semi_0_1*,pdf_semi_2_3*,pdf_semi_3_3*,"+\
                        "pdf_peak_0_1*,pdf_peak_2_3*,pdf_peak_3_3*,"+\
                        "pdf_1comb_0_1*,pdf_1comb_2_3*,pdf_1comb_3_3*"

        lhcb_components = 'bkg1 MuMu model6*,bkg1 MuMu model7*,bkg1 MuMu model8*,'+\
                            'missid6*,missid7*,missid8*,'+\
                            'B2Xmunu6*,B2Xmunu7*,B2Xmunu8*,'+\
                            'LaPmunu6*,LaPmunu7*,LaPmunu8*,'+\
                            'B0upimumu6*,B0upimumu7*,B0upimumu8*'
        model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
                    RooFit.LineStyle(9),RooFit.FillColor(kBlack),
                    RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        if separateSignal:
            data.plotOn(frame, RooFit.Cut(cut_cms_B),RooFit.Invisible())
            #CMS Bs
            cms_components = "pdf_bs_0_1*,pdf_bs_2_3*,pdf_bs_3_3*"
            model.plotOn(frame,RooFit.Components(cms_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kRed),
                        RooFit.LineStyle(9),RooFit.FillColor(kRed),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))
            #CMS Bd
            cms_components = "pdf_bd_0_1*,pdf_bd_2_3*,pdf_bd_3_3*"
            model.plotOn(frame,RooFit.Components(cms_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kGreen),
                        RooFit.LineStyle(9),RooFit.FillColor(kGreen),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

            data.plotOn(frame, RooFit.Cut(cut_lhcb_B),RooFit.Invisible())
            #LHCb Bs
            lhcb_components = "model Bs6*,model Bs7*,model Bs8*"
            model.plotOn(frame,RooFit.Components(lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kMagenta),
                        RooFit.LineStyle(9),RooFit.FillColor(kMagenta),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))
            #LHCb Bd
            lhcb_components = "model Bd6*,model Bd7*,model Bd8*"
            model.plotOn(frame,RooFit.Components(lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),
                        RooFit.LineStyle(9),RooFit.FillColor(kBlue),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        else:
            #Bs
            cms_components = "pdf_bs_0_1*,pdf_bs_2_3*,pdf_bs_3_3*"
            lhcb_components = "model Bs6*,model Bs7*,model Bs8*"
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kRed),
                        RooFit.LineStyle(9),RooFit.FillColor(kRed),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

            #Bd
            cms_components = "pdf_bd_0_1*,pdf_bd_2_3*,pdf_bd_3_3*"
            lhcb_components = "model Bd6*,model Bd7*,model Bd8*"
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kGreen),
                        RooFit.LineStyle(9),RooFit.FillColor(kGreen),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        data.plotOn(frame, RooFit.Cut(cut_lhcb_B+'||'+cut_cms_B),RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlue))

        frame.Draw()
        if separateSignal:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins_SepSign.pdf')
        else:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins.pdf')

        return canva

    #Plot the LHCb data on one plot, for the best bins
    def plotLHCbMassBestBins(self, bins = 25,rangeMax = 5900, sigFillStyle = 1001, bkgFillStyle = 3003):
        """ Plot LHCb data for best bins in 4900-5900 range """

        print ' Plotting LHCb on one mass plot for the best bins only...'

        canva = TCanvas("lhcbMeV_best","lhcbMeV_best")

        #Change to the same mass variable and range
        mass = self.comb_ws.obj('B_s0_MM')
        mass.setRange(4900,rangeMax)
        mass.setRange('NewRange',4900,rangeMax)

        model = self.comb_pdf
        data = self.comb_data
        category = self.comb_cat
        cms_bins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3']

        #FllStyle
        #style = 3008
        #style = 1001

        #Best LHCb bins
        cut_lhcb_B=     "comb_cat==comb_cat::LHCb_bin_6 ||"+\
                        "comb_cat==comb_cat::LHCb_bin_7 || comb_cat==comb_cat::LHCb_bin_8 "

        frame = mass.frame(RooFit.Bins(bins), RooFit.Title('LHCb(6,7,8) ; m_{#mu#mu} (MeV)'))

        data.plotOn(frame, RooFit.Cut(cut_lhcb_B),RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlue),RooFit.Invisible())

        #Total pdf
        lhcb_components = "mumu_model_6*,mumu_model_7*,mumu_model_8*"
        model.plotOn(frame,RooFit.Components(lhcb_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),RooFit.Range('NewRange'))

        #Background
        lhcb_components = 'bkg1 MuMu model6*,bkg1 MuMu model7*,bkg1 MuMu model8*,'+\
                            'missid6*,missid7*,missid8*,'+\
                            'B2Xmunu6*,B2Xmunu7*,B2Xmunu8*,'+\
                            'LaPmunu6*,LaPmunu7*,LaPmunu8*,'+\
                            'B0upimumu6*,B0upimumu7*,B0upimumu8*'
        model.plotOn(frame,RooFit.Components(lhcb_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
                    RooFit.LineStyle(9),RooFit.FillColor(kBlack),
                    RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('NewRange'))

        #Bs
        lhcb_components = "model Bs6*,model Bs7*,model Bs8*"
        model.plotOn(frame,RooFit.Components(lhcb_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kRed),
                    RooFit.LineStyle(9),RooFit.FillColor(kRed),
                    RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('NewRange'))

        #Bd
        lhcb_components = "model Bd6*,model Bd7*,model Bd8*"
        model.plotOn(frame,RooFit.Components(lhcb_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kGreen),
                    RooFit.LineStyle(9),RooFit.FillColor(kGreen),
                    RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('NewRange'))

        data.plotOn(frame, RooFit.Cut(cut_lhcb_B),RooFit.MarkerSize(0.7),RooFit.MarkerColor(kBlue))

        frame.Draw()
        canva.SaveAs(self.resDir+'Plot_'+self.combName+'_LHCbMass_BestBins.pdf')
        return canva, frame


    #Plot the CMSdata on one plot, for the best bins
    def plotCMSMassBestBins(self, bins = 25,change2MeV = False, sigFillStyle = 1001, bkgFillStyle = 3003):
        """ Plot CMSdata for best bins in 4900-5900 range """

        print ' Plotting CMS on one mass plot for the best bins only...'

        canva = TCanvas("cmsMeV_best","cmsMeV_best")

        #Change to the same mass variable and range
        mass = self.comb_ws.obj('Mass')
        #mass.setRange(4.9,5.9)
        mass.setRange('CMSrange',4.9,5.9)

        if change2MeV:
            mass = self.comb_ws.obj('B_s0_MM')
            mass.setRange(4900,5900)
            mass.setRange('CMSrange',4900,5900)

        model = self.comb_pdf
        data = self.comb_data
        category = self.comb_cat

        #Best LHCb+CMS bins
        cut_cms_B =  "comb_cat==comb_cat::CMS_bin_2 || "+\
                        "comb_cat==comb_cat::CMS_bin_8 ||"+\
                        "comb_cat==comb_cat::CMS_bin_12"

        #frame = mass.frame(RooFit.Bins(bins), RooFit.Title('CMS(2,4,8,11,12) ; m_{#mu#mu} (GeV)'))
        frame = mass.frame(RooFit.Bins(bins), RooFit.Title('CMS(2,8,12) ; m_{#mu#mu} (GeV)'))
        if change2MeV:
            frame = mass.frame(RooFit.Bins(bins), RooFit.Title('CMS(2,8,12) ; m_{#mu#mu} (MeV)'))

        data.plotOn(frame, RooFit.Cut(cut_cms_B),RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlue),RooFit.Invisible())

        #Total pdf
        cms_components = "pdf_ext_total_0_1*,pdf_ext_total_2_3*,pdf_ext_total_3_3*,"
        model.plotOn(frame,RooFit.Components(cms_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),RooFit.Range('CMSrange'))

        #Background
        cms_components = "pdf_semi_0_1*,pdf_semi_2_3*,pdf_semi_3_3*,"+\
                        "pdf_peak_0_1*,pdf_peak_2_3*,pdf_peak_3_3*,"+\
                        "pdf_1comb_0_1*,pdf_1comb_2_3*,pdf_1comb_3_3*"

        model.plotOn(frame,RooFit.Components(cms_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
                    RooFit.LineStyle(9),RooFit.FillColor(kBlack),
                    RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        #Bs
        cms_components = "pdf_bs_0_1*,pdf_bs_2_3*,pdf_bs_3_3*"
        model.plotOn(frame,RooFit.Components(cms_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kRed),
                    RooFit.LineStyle(9),RooFit.FillColor(kRed),
                    RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))
        #Bd
        cms_components = "pdf_bd_0_1*,pdf_bd_2_3*,pdf_bd_3_3*"
        model.plotOn(frame,RooFit.Components(cms_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kGreen),
                    RooFit.LineStyle(9),RooFit.FillColor(kGreen),
                    RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        data.plotOn(frame, RooFit.Cut(cut_cms_B),RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlue))

        frame.Draw()
        canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CMSMass_BestBins.pdf')
        return canva

    #Plot the CMSdata on one plot, for a single bin
    def plotCMSMassInOneBin(self, binNr=1, bins = 25,change2MeV = False, sigFillStyle = 1001, bkgFillStyle = 3003, CMSonlyWS = False):
        """ Plot CMSdata for a single bin in 4900-5900 range """

        print ' Plotting CMS on one mass plot for on bin only. Bin:',binNr
        canva = TCanvas("cmsMeV_bin","cmsMeV_bin")

        #Change to the same mass variable and range
        mass = self.comb_ws.obj('Mass')
        #mass.setRange(4.9,5.9)
        mass.setRange('CMSrange',4.9,5.9)
        model = self.comb_pdf
        data = self.comb_data
        category = self.comb_cat
        cms_bins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3']

        mass = self.comb_ws.obj('Mass')
        #mass.setRange(4.9,5.9)
        mass.setRange('CMSrange',4.9,5.9)

        model = self.comb_pdf
        data = self.comb_data
        category = self.comb_cat
        #CMS bin
        cut_cms_B =  category.GetName()+"=="+category.GetName()+"::CMS_bin_"+str(binNr)

        if CMSonlyWS:
            #Plot from CMS ws
            #Change to the same mass variable and range
            mass = self.cms_ws.obj('Mass')
            #mass.setRange(4.9,5.9)
            mass.setRange('CMSrange',4.9,5.9)
            model = self.cms_pdf
            data = self.cms_data
            category = self.cms_cat
            mass = self.cms_ws.obj('Mass')
            #mass.setRange(4.9,5.9)
            mass.setRange('CMSrange',4.9,5.9)
            model = self.cms_pdf
            data = self.cms_data
            category = self.cms_cat
             #CMS bin
            cut_cms_B =  category.GetName()+"=="+category.GetName()+"::allcat_"+str(binNr-1)

        if change2MeV:
            mass = self.comb_ws.obj('B_s0_MM')
            mass.setRange(4900,5900)
            mass.setRange('CMSrange',4900,5900)
        frame = mass.frame(RooFit.Bins(bins), RooFit.Title('CMS('+str(binNr)+') ; m_{#mu#mu} (GeV)'))

        if change2MeV:
            frame = mass.frame(RooFit.Bins(bins), RooFit.Title('CMS('+str(binNr)+') ; m_{#mu#mu} (MeV)'))

        data.plotOn(frame, RooFit.Cut(cut_cms_B),RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlue),RooFit.Invisible())

        #Total pdf
        cms_components = "pdf_ext_total_"+cms_bins[binNr-1]+"*"
        model.plotOn(frame,RooFit.Components(cms_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),RooFit.Range('CMSrange'))

       # #Background
       # cms_components = "pdf_semi_0_1*,pdf_semi_1_1*,pdf_semi_2_3*,pdf_semi_3_2*,pdf_semi_3_3*,"+\
       #                 "pdf_peak_0_1*,pdf_peak_1_1*,pdf_peak_2_3*,pdf_peak_3_2*,pdf_peak_3_3*,"+\
       #                 "pdf_1comb_0_1*,pdf_1comb_1_1*,pdf_1comb_2_3*,pdf_1comb_3_2*,pdf_1comb_3_3*"

       # model.plotOn(frame,RooFit.Components(cms_components),
       #             RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
       #             RooFit.LineStyle(9),RooFit.FillColor(kBlack),
       #             RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        #Bs
        cms_components = "pdf_bs_"+cms_bins[binNr-1]+"*"
        model.plotOn(frame,RooFit.Components(cms_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kRed),
                    RooFit.LineStyle(9),RooFit.FillColor(kRed),
                    RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))
        #Bd
        cms_components = "pdf_bd_"+cms_bins[binNr-1]+"*"
        model.plotOn(frame,RooFit.Components(cms_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kGreen),
                    RooFit.LineStyle(9),RooFit.FillColor(kGreen),
                    RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        data.plotOn(frame, RooFit.Cut(cut_cms_B),RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlue))

        frame.Draw()
        canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CMSMass_Bin_'+str(binNr)+'.pdf')
        return canva


###############################################################################
# Make S/S+B weighted combined mass plot
###############################################################################


    def getSBweights(self):

        cms_bins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3']
        weights =[]
        sumOfWeights = 0.

        #Loop over all the bins
        for i in range(0,20):

            pdfTot = 0
            pdfBs = 0
            Ntot = 0
            Nbs = 0
            mass = self.comb_ws.obj('B_s0_MM')
            #LHCb
            if i < 8:
                b = str(i+1)+'_LHCb'
                #mumu_model_1_LHCb[ MuMuBkg1_LHCb * bkg1 MuMu model1_LHCb +
                #                   NBs1_LHCb * model Bs1_LHCb +
                #                   NBd1_LHCb * model Bd1_LHCb +
                #                   Nmis1_LHCb * missid1_LHCb +
                #                   N_B2Xmunu1_LHCb * B2Xmunu1_LHCb +
                #                   N_B0pimumu1_LHCb * B0upimumu1_LHCb +
                #                   N_LaPmunu1_LHCb * LaPmunu1_LHCb ] = 2.57575e+08

                #Set the mass to the Bs mean
                #LHCb fits a single shared mean in every category
                bsMean = self.comb_ws.obj('MBs_LHCb').getVal()
                mass.setVal(bsMean)
                print ' Mass value set to : ', bsMean

                #Yields
                Nbs = self.comb_ws.obj('NBs'+b).getVal()
                Nbd = self.comb_ws.obj('NBd'+b).getVal()
                Ncomb = self.comb_ws.obj('MuMuBkg'+b).getVal()
                Nmis= self.comb_ws.obj('Nmis'+b).getVal()
                Nbmn= self.comb_ws.obj('N_B2Xmunu'+b).getVal()
                Nbmm= self.comb_ws.obj('N_B0pimumu'+b).getVal()
                Nlmn= self.comb_ws.obj('N_LaPmunu'+b).getVal()
                Ntot = Nbs+Nbd+Ncomb+Nmis+Nbmn+Nbmm+Nlmn

                #Pdf values
                pdfTot = self.comb_pdf.getComponents()['mumu_model_'+b]
                pdfBs  = self.comb_pdf.getComponents()['model Bs'+b]


            else: #CMS
                b = cms_bins[i-8]
                #pdf_ext_sum_0_0_CMS[   N_bs_CombFormula_0_0 * pdf_bs_0_0_CMS +
                #                       N_bd_CombFormula_0_0 * pdf_bd_0_0_CMS +
                #                       N_comb_formula_0_0 * pdf_1comb_0_0_CMS +
                #                       N_semi_0_0_CMS * pdf_semi_0_0_CMS +
                #                       N_peak_0_0_CMS * pdf_peak_0_0_CMS ] = 4.42573e-06/1

                #Set the mass to the Bs mean
                #CMS uses a fixed mean in every category
                bsMean = self.comb_ws.obj('Mean_bs_'+b+'_CMS').getVal()
                mass.setVal(bsMean*1000.)
                print ' Mass value set to : ', bsMean*1000.

                #Yields
                Nbs = self.comb_ws.obj('N_bs_CombFormula_'+b).getVal()
                Nbd = self.comb_ws.obj('N_bd_CombFormula_'+b).getVal()
                Ncomb = self.comb_ws.obj('N_comb_formula_'+b).getVal()
                Nsemi= self.comb_ws.obj('N_semi_'+b+'_CMS').getVal()
                Npeak= self.comb_ws.obj('N_peak_'+b+'_CMS').getVal()
                Ntot = Nbs+Nbd+Ncomb+Nsemi+Npeak
                #Pdf values
                res = self.comb_ws.var('ReducedMassRes')
                pdfBs =  self.comb_pdf.getComponents()['pdf_bs_'+b+'_CMS'].createProjection(RooArgSet(res))
                pdfTot = self.comb_pdf.getComponents()['pdf_ext_sum_'+b+'_CMS'].createProjection(RooArgSet(res))


            pdfBsVal = pdfBs.getVal(RooArgSet(mass))
            S = Nbs * pdfBsVal

            pdfTotVal = pdfTot.getVal(RooArgSet(mass))
            T = Ntot * pdfTotVal
            w = S/T
            weights.append(w)
            sumOfWeights += w
            #Build a new weighted Bs,Bd and background pdf
            print '======================================='
            print ' BIN: ', i
            print ' b = ',b
            print ' Total   pdf value:' , pdfTotVal
            print ' Bs      pdf value:' , pdfBsVal
            print ' Total  bin yield :' , Ntot
            print ' Bs     bin yield :' , Nbs
            print ' S=               :', S
            print ' T=S+B=           :', T
            print ' S/S+B+           :', w
            print '======================================='

        #Print unnormalized bin weights
        print '======================================='
        print ' Raw mass bin weights:'
        print '======================================='
        for i in range(0,20):
            print ' Bin %2.0f w = %1.5f' % (i,weights[i])
        self.rawSBWeights = weights
        self.normWeights = []
        #Normalize weights
        print '======================================='
        print ' Normalized mass bin weights:'
        print '======================================='
        print 'LHCb:'
        lhcbSum = 0
        cmsSum = 0
        for i in range(0,8):
            nw =  weights[i]/sumOfWeights
            lhcbSum+= nw
            self.normWeights.append(nw)
            print '  Bin ',i,' W(S/S+B) at Bs peak =', nw
        print '                                         LHCb contribution:', lhcbSum
        print 'CMS:'
        for i in range(8,20):
            nw =  weights[i]/sumOfWeights
            cmsSum+= nw
            self.normWeights.append(nw)
            print '  Bin ',i-8,' W(S/S+B) at Bs peak =', nw
        print '                                         CMS  contribution:', cmsSum
        print '======================================='
        return self.normWeights


    def plotBinWeights(self,weights,maxX=1,suf=''):
        """Plot the bins agains their weights in increasing order"""

        #Sort the bins according to the weights
        d = {}
        for i in range(0,20):
            if i<8: d['LHCb_Bin_'+str(i+1)] = weights[i]
            else: d['CMS_Bin_'+str(i+1-8)] = weights[i]

        #Sort the bin according to the weights
        import operator
        sorted_d = sorted(d.iteritems(), key=operator.itemgetter(1))
        binNames, binWeights = [],[]
        for i in range(0,20):
            binNames.append(sorted_d[i][0])
            binWeights.append(sorted_d[i][1])

        #Plot the sorted bin weights

        hist = TH1F("hist","S/S+B weights per categories ; ; w = S/S+B",20,0,20)
        hist.SetFillColor(1)
        hist.SetBarWidth(0.4)
        #hist.SetBarOffset(0.1)
        hist.SetStats(0)
        hist.SetMinimum(0)
        hist.SetMaximum(maxX)


        for i in range(0,20):
            hist.Fill(binNames[i],binWeights[i])
            hist.GetXaxis().SetBinLabel(i+1,binNames[i])

        c = TCanvas('wHist','wHist')
        hist.Draw('hbar')

        c.SaveAs(self.resDir+'Plot_'+self.combName+'_SBbinWeights_'+suf+'.pdf')
        return c,hist


    def buildWeightedPdf(self):

        #Build a new total pdf = w1*lhcb_bin1+...+wi*CMS_bin1

        #RooSimultaneous::comb_pdf[ indexCat=comb_cat
        #CMS_bin_1=pdf_ext_total_0_0_CMS CMS_bin_10=pdf_ext_total_3_1_CMS CMS_bin_11=pdf_ext_total_3_2_CMS
        #CMS_bin_12=pdf_ext_total_3_3_CMS CMS_bin_2=pdf_ext_total_0_1_CMS CMS_bin_3=pdf_ext_total_1_0_CMS
        #CMS_bin_4=pdf_ext_total_1_1_CMS CMS_bin_5=pdf_ext_total_2_0_CMS CMS_bin_6=pdf_ext_total_2_1_CMS
        #CMS_bin_7=pdf_ext_total_2_2_CMS CMS_bin_8=pdf_ext_total_2_3_CMS CMS_bin_9=pdf_ext_total_3_0_CMS
        #LHCb_bin_1=mumu_model_1_LHCb LHCb_bin_2=mumu_model_2_LHCb LHCb_bin_3=mumu_model_3_LHCb LHCb_bin_4=mumu_model_4_LHCb
        #LHCb_bin_5=mumu_model_5_LHCb LHCb_bin_6=mumu_model_6_LHCb LHCb_bin_7=mumu_model_7_LHCb LHCb_bin_8=mumu_model_8_LHCb ] = 3.08585e-08

        cms_bins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3']
        pdfList = RooArgList()
        weights = []
        wList = RooArgList()

        for i in range(0,20):

            #Get LHCb bin pdf's
            binPdf = 0
            if i < 8:
                b = str(i+1)+'_LHCb'
                binPdf = self.comb_pdf.getComponents()['mumu_model_'+b]

            else: #CMS
                b = cms_bins[i-8]
                binPdf = self.comb_pdf.getComponents()['pdf_ext_total_'+b+'_CMS']

            #Add the pdf and a bin weight to the list
            pdfList.add(binPdf)
            weights.append(RooRealVar('w'+str(i+1),'S/S+B bin weight for bin '+str(i+1),self.normWeights[i]))
            wList.add(weights[-1])
            print ' ============================  '
            print ' BIN:', i
            print ' ============================  '
            print ' Added pdf   :', binPdf.GetName()
            print ' Added weight:', self.normWeights[i]

        print ' ============================  '
        pdfList.Print()
        wList.Print()
        comb_wpdf = RooAddPdf('comb_wpdf','Weighted combined LHCb+CMS pdf',pdfList,wList)
        print ' Combined and weighted pdf built! (self.comb_wpdf)'
        comb_wpdf.Print()
        getattr(self.comb_ws,'import')(comb_wpdf, RooFit.RecycleConflictNodes())
        print ' ============================  '
        self.comb_wpdf = self.comb_ws.obj('comb_wpdf')

        #Calculate the int over Bs projection w.r.t the integral over the total pdf
        #This will give a normalization of the data as normData2 = 1/(intBs / intTotal) * N_Bs(fitted)



        return self.comb_wpdf


    def buildWeightedData(self):

        #Start the weighted dataset from bin 1, then loop and append other bins

        cat = self.comb_cat
        catN = cat.GetName()
        Ntot = self.comb_data.numEntries()
        #LHCb bin 1
        i = 0
        data_bin = getattr(self.comb_data,'reduce')(catN+'=='+catN+"::"+str(i))
        w = RooRealVar('w','Weight = (S/S+B) / N_cat',self.normWeights[i]*Ntot/data_bin.numEntries())
        data_bin.addColumn(w)
        data_sum = data_bin.Clone()

        for i in range(1,20):
            data_bin = getattr(self.comb_data,'reduce')(catN+'=='+catN+"::"+str(i))
            w.setVal(self.normWeights[i]*Ntot/data_bin.numEntries())
            data_bin.addColumn(w)
            data_sum.append(data_bin)


        #Now interpret the 'w' as a weight of the event
        wdata = RooDataSet(data_sum.GetName(),data_sum.GetTitle(),data_sum,data_sum.get(),'',w.GetName())

        getattr(self.comb_ws,'import')(wdata,'comb_wdata')
        self.comb_wdata = self.comb_ws.obj('comb_wdata')
        return self.comb_wdata



    def plotWeightedMass(self, bins = 25, separateSignal = False,rangeMax = 5900, sigFillStyle = 1001, bkgFillStyle = 3003):
        """ Plot a combined mass plot, where the bins (pdf,data) are weighted by S/S+B. The S, and B are gotten from pdf values
        at the Bs peak. This is equivalent to integratins around the Bs peak+-sigma range."""

        print '  Plotting the combined weighted mass plot...'

        #Tp plot the weighted mass plot, you need to call before:
        #self.getSBweights()
        #self.buildWeightedPdf()
        #self.buildWeightedData()


        canva = TCanvas("wMass","wMass")

        mass = self.comb_ws.var('B_s0_MM')
        mass.setRange(4900,5900)
        mass.setRange('CMSrange',4900,5900)

        model= self.comb_wpdf
        data = self.comb_wdata
        category = self.comb_cat
        cms_bins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3']

        frame = mass.frame(RooFit.Bins(bins), RooFit.Title('S/(S+B) weighted LHCb and CMS ; m_{#mu#mu} (MeV) '))
        data.plotOn(frame, RooFit.Invisible())

        #Total pdf
        model.plotOn(frame, RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),RooFit.Range('CMSrange'))

        #Background
        cms_components = 'pdf_semi_*,pdf_peak_*,pdf_1comb_*'
        lhcb_components = 'bkg1 MuMu model*,missid*,B2Xmunu*,LaPmunu*,B0upimumu*'

        model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
                    RooFit.LineStyle(9),RooFit.FillColor(kBlack),
                    RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        if separateSignal:

            #CMS part
            cut_cms =   "comb_cat==comb_cat::CMS_bin_1 || comb_cat==comb_cat::CMS_bin_2 ||"+\
                        "comb_cat==comb_cat::CMS_bin_3 || comb_cat==comb_cat::CMS_bin_4 ||"+\
                        "comb_cat==comb_cat::CMS_bin_5 || comb_cat==comb_cat::CMS_bin_6 ||"+\
                        "comb_cat==comb_cat::CMS_bin_7 || comb_cat==comb_cat::CMS_bin_8 ||"+\
                        "comb_cat==comb_cat::CMS_bin_9 || comb_cat==comb_cat::CMS_bin_10 ||"+\
                        "comb_cat==comb_cat::CMS_bin_11 || comb_cat==comb_cat::CMS_bin_12"

            data.plotOn(frame, RooFit.Cut(cut_cms),RooFit.Invisible())
            #CMS Bs
            cms_components = "pdf_bs_*"
            model.plotOn(frame,RooFit.Components(cms_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kRed),
                        RooFit.LineStyle(9),RooFit.FillColor(kRed),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))
            #CMS Bd
            cms_components = "pdf_bd_*"
            model.plotOn(frame,RooFit.Components(cms_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kGreen),
                        RooFit.LineStyle(9),RooFit.FillColor(kGreen),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

            #LHCb part
            cut_lhcb=   "comb_cat==comb_cat::LHCb_bin_1 || comb_cat==comb_cat::LHCb_bin_2 || "+\
                        "comb_cat==comb_cat::LHCb_bin_3 || comb_cat==comb_cat::LHCb_bin_4 || "+\
                        "comb_cat==comb_cat::LHCb_bin_5 || comb_cat==comb_cat::LHCb_bin_6 || "+\
                        "comb_cat==comb_cat::LHCb_bin_7 || comb_cat==comb_cat::LHCb_bin_8 "

            data.plotOn(frame, RooFit.Cut(cut_lhcb),RooFit.Invisible())
            #LHCb Bs
            lhcb_components = "model Bs*"
            model.plotOn(frame,RooFit.Components(lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kMagenta),
                        RooFit.LineStyle(9),RooFit.FillColor(kMagenta),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))
            #LHCb Bd
            lhcb_components = "model Bd*"
            model.plotOn(frame,RooFit.Components(lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue),
                        RooFit.LineStyle(9),RooFit.FillColor(kBlue),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        else:
            #Bs
            cms_components = "pdf_bs_*"
            lhcb_components = "model Bs*"
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kRed),
                        RooFit.LineStyle(9),RooFit.FillColor(kRed),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

            #Bd
            cms_components = "pdf_bd_*"
            lhcb_components = "model Bd*"
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kGreen),
                        RooFit.LineStyle(9),RooFit.FillColor(kGreen),
                        RooFit.FillStyle(sigFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

        data.plotOn(frame, RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlue),RooFit.DataError(RooAbsData.SumW2))

        frame.Draw()
        if separateSignal:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeigtedMass_bins_'+str(bins)+'_SignSep.pdf')
        else:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeightedMass_bins_'+str(bins)+'.pdf')

        return canva


#Servers:
#(0x7f999a220200,V-) RooCategory::allcat "channels"
#(0x7f999a641800,V-) RooProdPdf::pdf_ext_total_0_0 "pdf_ext_total"
#(0x7f999a644800,V-) RooProdPdf::pdf_ext_total_0_1 "pdf_ext_total"
#(0x7f999a271200,V-) RooProdPdf::pdf_ext_total_1_0 "pdf_ext_total"
#(0x7f999a302800,V-) RooProdPdf::pdf_ext_total_1_1 "pdf_ext_total"
#(0x7f999a21dc00,V-) RooProdPdf::pdf_ext_total_2_0 "pdf_ext_total"
#(0x7f999a321200,V-) RooProdPdf::pdf_ext_total_2_1 "pdf_ext_total"
#(0x7f999a392000,V-) RooProdPdf::pdf_ext_total_2_2 "pdf_ext_total"
#(0x7f999a403400,V-) RooProdPdf::pdf_ext_total_2_3 "pdf_ext_total"
#(0x7f999a48f600,V-) RooProdPdf::pdf_ext_total_3_0 "pdf_ext_total"
#(0x7f999a500a00,V-) RooProdPdf::pdf_ext_total_3_1 "pdf_ext_total"
#(0x7f999a571e00,V-) RooProdPdf::pdf_ext_total_3_2 "pdf_ext_total"
#(0x7f999a5e3200,V-) RooProdPdf::pdf_ext_total_3_3 "pdf_ext_total"
#Proxies:
#!plotCoefNormSet ->
#indexCat -> allcat
#allcat_0 -> pdf_ext_total_0_0
#allcat_1 -> pdf_ext_total_0_1
#allcat_2 -> pdf_ext_total_1_0
#allcat_3 -> pdf_ext_total_1_1
#allcat_4 -> pdf_ext_total_2_0
#allcat_5 -> pdf_ext_total_2_1
#allcat_6 -> pdf_ext_total_2_2
#allcat_7 -> pdf_ext_total_2_3
#allcat_8 -> pdf_ext_total_3_0
#allcat_9 -> pdf_ext_total_3_1
#allcat_10 -> pdf_ext_total_3_2
#allcat_11 -> pdf_ext_total_3_3

    #def prepareCombWorkspace(self):
    #    """This is not needes if, the nuisances and glob,obs are already defined
    #    in single WS. But if not, it will find the constraints, the means, and the unconstrained nuisances"""


    #    ws = self.comb_ws
    #    constraints = self.comb_ws.set('comb_cons')
    #    # I define another one for conveninence in case we forgot to add something
    #    ws.defineSet("constraints",constraints)
    #    #get all variables
    #    variables = ws.allVars()
    #    # get the observables

    #    # get all the constrained nuisance parameters
    #    it = constraints.createIterator()
    #    obj = it.Next()
    #    const_nuisances = RooArgSet("constrained_nuisances")
    #    globobs   = RooArgSet("global_observables")
    #    # a bit of a hack....
    #    while obj :
    #        name = obj.GetName()
    #        nameglob = ""
    #        print "Found constraint with name ", name
    #        if name[-6:]  == "_const" :
    #            name = name.replace("_const","")
    #            nameglob = name +"_mean"
    #        elif name[-11:] == "_const_LHCb" :
    #            name = name.replace("_const","")
    #            nameglob = name.replace("_LHCb" ,"_mean_LHCb")
    #        else :
    #            raw_input(' NB! Constraint name is different from expected!')
 #  #          print "Going to search var name as: ", name
    #        var = ws.var(name)
    #        if var :
#   #            print "Found var with name ",name
    #            const_nuisances.add(var)
    #        else :
    #            #The shared variables do not have _LHCb suffix
    #            name = name.replace("_LHCb","")
    #            var = ws.var(name)
    #            if var:
    #                const_nuisances.add(var)
    #            else:
    #                print "Var with name %s not found"%(name)
    #                raw_input('....')
#   #         print "Trying to find the glob obs as ", nameglob
    #        glob = ws.var(nameglob)
    #        if glob:
    #            print "Found global observable with name ", nameglob
    #            globobs.add(glob)
    #        else:
    #            nameglob = nameglob.replace("_LHCb" ,"")
    #            glob = ws.var(nameglob)
    #            if glob:
    #                print "Found global observable with name ", nameglob
    #                globobs.add(glob)
    #            else:
    #                print "Not fond glob obs with name ", nameglob
    #                raw_input('...')

    #        obj = it.Next()

    #    const_nuisances.Print("v")
    #    #raw_input('ok?')

    #    #all the parameters
    #    all_pars = self.comb_pdf.getParameters(self.comb_data)

    #    # define parameters of interest
    #    poi = RooArgSet(ws.var('BF_bs'), ws.var('BF_bd'))

    #    # Get unconstrained nuisances

    #    # Define remaining (unconstrained nuisances) as All -observables - cons-nuisances - poi
    #    # Make a subset of those that are not constrained
    #    it = all_pars.createIterator()
    #    par = it.Next()
    #    free_nuisances = RooArgSet("unconstrained_nuisances")
    #    # a bit of a hack....
    #    while par :
    #        par_name = par.GetName()

    #        #See if it is constrained
    #        itr = const_nuisances.createIterator()
    #        const_nuis = itr.Next()
    #        veto = False
    #        while const_nuis:
    #            if par_name in const_nuis.GetName(): veto = True
    #            const_nuis = it.Next()


    #        #See if it is a poi
    #        itr = poi.createIterator()
    #        poi = itr.Next()
    #        veto = False
    #        while poi:
    #            if par_name in poi.GetName(): veto = True
    #            poi = it.Next()

    #        #See if it is an observable
    #        itr = poi.createIterator()
    #        poi = itr.Next()
    #        veto = False
    #        while poi:
    #            if par_name in poi.GetName(): veto = True
    #            poi = it.Next()



    #        #If not constrained, add to the free par list
    #        if not isConstrained:
    #            print ' + Added paramater to the unconstrained nuisance list:', par_name
    #            free_nuisances.add(par)
    #        else:
    #            print ' - parameter not added because it is constrained:', par_name

    #        par = it.Next()

    #    free_nuisances.Print('v')


    def saveCombWorkspace(self):
        ''' Saves the combined worskspace to file '''
        wsFile = self.resDir + 'combinedWorkspace_'+self.combName+'.root'
        print "Going to save the combined workspace to ", wsFile
        self.comb_ws.SaveAs(wsFile)


##     def changeConstraints(self):
##         ''' changing the constraints'''
##         constraints = self.comb_ws.set('comb_cons')
##         it = constraints.createIterator()
##         obj = it.Next()
##         print " before operation "
##         obj.Print("v")
##         servers = obj.serverMIterator()
##         _mean = servers.next()
##         _sigma = servers.next()
##         _name = obj.GetName()
##         _mean_var = RooRealVar(_name+"_mean",_name+"_mean", _mean.getVal())
## #        obj.replaceServer(_mean, _mean_var, 1,1)

##         cust = RooCustomizer(obj,'')
##         cust.replaceArg(_mean, _mean_var)
##         cust.Print("v")
## #        obj = cust.build(kTRUE)
##         miao= cust.build(kTRUE)
##         print " after operation "
##         obj.Print('v')
##         miao.Print("v")


#        while obj:
            #name = obj.GetName() + '_LHCb'
            #obj.SetName(name)
#            obj.Print("v")
#            obj = it.Next()


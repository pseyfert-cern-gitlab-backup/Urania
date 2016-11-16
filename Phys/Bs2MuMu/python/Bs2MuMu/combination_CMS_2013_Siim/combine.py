#############################
# Credits                   #
# Author: Siim Tolk         #
# Date: Autumn 2014         #
# Mail: siim.tolk@cern.ch   #
#############################

####################################
# Combine the CMS and LHCb models  #
####################################
from ROOT import *
from ROOT import RooFit
from ROOT import RooStats
from ROOT import TFeldmanCousins
from SomeMassModels import RooPhysBkg #Run on LxPlus
#from SomeMassModels_this import RooPhysBkg #Run on LxPlus

RooFit.gErrorIgnoreLevel = kError
RooMsgService.instance().setGlobalKillBelow(RooFit.ERROR)

import os
from valAndErr import *

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


    def importLHCb(self, fixBRs = 0, fixBRd = 0):
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

        #Build the new lhcb_pdf and import it to the comb_ws
        self.lhcb_pdf_cust= cust.build(kTRUE)

        #try:
        if 1:
        # Leave the shared variables BRs, BRd, fsfd, BuJpsiK_BF and observables untouched,
            # add '_LHCb' to the rest of the parameters
            #Define the shared parameters in string format
            self.sharedParams = 'BRs,BRd,fdfs,BuJpsiK_BF' # We'll leave those names the same when importing
            observables = ',B_s0_MM,'+self.lhcb_cat.GetName() # and those as well, but they are just not sharedParams
            #self.sharedConstraints = 'fdfs,BuJpsiK_BF' #and those are the shared constraints. only renam the constraint funtions not params
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
            getattr(self.comb_ws,'defineSet')('comb_lhcb_nuis_uncons',comb_lhcb_nuis_uncons)
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
    # Calculate expected SM yield      #
    ####################################

    def getExpSMYieldLHCb(self):


        print 'SM Expectation for LHCb'
        ws = self.lhcb_ws
        #The yield is equal to
        #N_SM_Bs = BF_Bs_SM * fsfd * 1/alpha_d
        #N_SM_Bd = BF_Bd_SM / alpha_d



        #RooFormulaVar::alpha_d[ actualVars=(BdKpi_BF,BdKpi_BF_Err,BuJpsiK_BF,BuJpsiK_BF_Err,alpha_KPi,alpha_KPi_Err,alpha_Bu,alpha_Bu_Err) formula=" ((@4*(@0*1.e-5)*((@2*1.e-5)*(@2*1.e-5)*@7*@7+@6*@6*(@3*1.e-5)*(@3*1.e-5))+@6*(@2*1.e-5)*((@0*1.e-5)*(@0*1.e-5)*@5*@5+@4*@4*(@1*1.e-5)*(@1*1.e-5)))/((@0*1.e-5)*(@0*1.e-5)*@5*@5+@4*@4*(@1*1.e-5)*(@1*1.e-5)+(@2*1.e-5)*(@2*1.e-5)*@7*@7+@6*@6*(@3*1.e-5)*(@3*1.e-5)))" ] = 0.000246674

        print ' o) Calculate alpha_d '
        #Edit the RooFormula in the Ws, in order to evaluate the uncertainty
        e5 = valAndErr(1.e-5,0.)
        e7 = valAndErr(1.e-7,0.)
        # @0 = Bd.getVal()
        # @1 = Bd.getErr()
        Bd = valAndErr(ws.obj('BdKpi_BF').getVal(),ws.obj('BdKpi_BF_Err').getVal()).times(e5)
        print ' Bd_BF = ' , Bd.info()
        # @2 = Bu.getVal()
        # @3 = Bu.getErr()
        Bu = valAndErr(ws.obj('BuJpsiK_BF').getVal(),ws.obj('BuJpsiK_BF_Err').getVal()).times(e5)
        print ' Bu_BF = ' , Bu.info()
        # @4 = a_bd.getVal()
        # @5 = a_bd.getErr()
        a_bd = valAndErr(ws.obj('alpha_KPi').getVal(),ws.obj('alpha_KPi_Err').getVal()).times(e7)
        print ' a_bd = ' , a_bd.info()
        # @6 = a_bu.getVal()
        # @7 = a_bu.getErr()
        a_bu = valAndErr(ws.obj('alpha_Bu').getVal(),ws.obj('alpha_Bu_Err').getVal()).times(e7)
        print ' a_bu = ' , a_bu.info()
        # * -> .times
        # + -> .times
        # / -> .over


        #The weighting
        a_bd_tot = a_bd.times(Bd)
        a_bu_tot = a_bu.times(Bu)

        sumSig = (a_bd_tot.getErr())**2 + (a_bu_tot.getErr())**2
        fBd = (a_bu_tot.getErr())**2 / sumSig
        fBu = (a_bd_tot.getErr())**2 / sumSig

        alpha_d = (valAndErr(fBd,0.).times(a_bd_tot)).plus(valAndErr(fBu,0.).times(a_bu_tot))
        print ' ---------------------------------------- '
        print ' Alpha_d = ', alpha_d.getVal(),' +- ', alpha_d.getErr()
        print ' ---------------------------------------- '

        # X-checking...
        #v0 = Bd.getVal()
        #v1 = Bd.getErr()
        #v2 = Bu.getVal()
        #v3 = Bu.getErr()
        #v4 = a_bd.getVal()
        #v5 = a_bd.getErr()
        #v6 = a_bu.getVal()
        #v7 = a_bu.getErr()
        #alpha_d_v =((v4*(v0)*((v2)*(v2)*v7*v7+v6*v6*(v3)*(v3))+v6*(v2)*((v0)*(v0)*v5*v5+v4*v4*(v1)*(v1)))/((v0)*(v0)*v5*v5+v4*v4*(v1)*(v1)+(v2)*(v2)*v7*v7+v6*v6*(v3)*(v3)))
        #alpha_d = valAndErr(alpha_d_v,0.)
        #print ' ---------------------------------------- '
        #print ' Alpha_d = ', alpha_d.getVal(),' +- ', alpha_d.getErr()
        #print ' ---------------------------------------- '


        # Standard Model predictions
        BF_SM_s = valAndErr(3.66e-9,0.23e-9)
        print ' BF(Bsmm) = ', BF_SM_s.info()
        BF_SM_d = valAndErr(1.06e-10,0.09e-10)
        print ' BF(Bdmm) = ', BF_SM_d.info()

        # Fsfd from the ws
        errR = ws.obj('fdfs_sigmaR').getVal()
        errL = ws.obj('fdfs_sigmaL').getVal()
        fdfs = valAndErr(lhcb_ws.obj('fdfs').getVal(), (errR+errL)/2.)
        print ' fd/fs = ', fdfs.info()

        # Expected yields for the SM BF's
        one = valAndErr(1.,0.)
        N_bs = BF_SM_s.times(one.over(fdfs)).times( one.over(alpha_d) )
        N_bd = BF_SM_d.times( one.over(alpha_d) )

        print ' ------------------  '
        print ' SM Expected yields for LHCb'
        print ' N(Bdsmm) = ', N_bd.info()
        print ' N(Bsmm) = ', N_bs.info()
        print ' ------------------  '



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
        #def_arg_list.Add(RooFit.Minimizer('OldMinuit','minimize')) #Default
        #def_arg_list.Add(RooFit.Minimizer('OldMinuit','migrad'))

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

    def fitCombinedModel(self, offset = 1,  nCPU = 8, reFit = True, fixBs = False, fixBd = False, BsZero =True):
        """ Fit the combined model on the combined data. """

        model = self.comb_pdf
#        constraints = self.comb_ws.set('lhcb_cons')
        constraints = self.comb_ws.set('comb_cons')
        constraints.Print("v")

        data = self.comb_data #Use the individual Ws data
        minosVars = RooArgSet(self.comb_ws.var('BRs'), self.comb_ws.var('BRd'))
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


########################################
# Print the fit output
########################################

    def getYields(self):

        yieldFile = self.resDir + 'fitYields_CMSLHCb_'+self.combName+'.txt'
        f = open(yieldFile,'w')

        #Yields
        Nbs,Nbd,Ncomb,Nmis,Nbmn,Nbmm,Nlmn,Ntot = 0,0,0,0,0,0,0,0

        #Loop over all the LHCb bins
        for i in range(0,8):
                b = str(i+1)+'_LHCb'
                print >> f , ' =================================================='
                print >> f , ' LHCb BDT Cat: ', b

                #Yields
                Nbs_bin = self.comb_ws.obj('NBs'+b).getVal()
                Nbd_bin = self.comb_ws.obj('NBd'+b).getVal()
                Ncomb_bin = self.comb_ws.obj('MuMuBkg'+b).getVal()
                Nmis_bin= self.comb_ws.obj('Nmis'+b).getVal()
                Nbmn_bin= self.comb_ws.obj('N_B2Xmunu'+b).getVal()
                Nbmm_bin= self.comb_ws.obj('N_B0pimumu'+b).getVal()
                Nlmn_bin= self.comb_ws.obj('N_LaPmunu'+b).getVal()
                Ntot_bin = Nbs_bin+Nbd_bin+Ncomb_bin+Nmis_bin+Nbmn_bin+Nbmm_bin+Nlmn_bin

                Nbs += Nbs_bin
                Nbd += Nbd_bin
                Ncomb += Ncomb_bin
                Nmis += Nmis_bin
                Nbmn += Nbmn_bin
                Nbmm += Nbmm_bin
                Nlmn += Nlmn_bin
                Ntot += Ntot_bin

                print >> f , '     N_{Bs}              = ' , Nbs_bin
                print >> f , '     N_{Bd}              = ' , Nbd_bin
                print >> f , '     N_{Comb#mu#mu}      = ' , Ncomb_bin
                print >> f , '     N_{MisIDhh}         = ' , Nmis_bin
                print >> f , '     N_{h#mu#nu}         = ' , Nbmn_bin
                print >> f , '     N_{#pi#mu#mu}       = ' , Nbmm_bin
                print >> f , '     N_{#Lambda p#mu#nu} = ' , Nlmn_bin
                print >> f , '     -------------------------'
                print >> f , '     N_{CatTot}          = ' , Ntot_bin

            ####################

        print >> f , ' =================================================='
        print >> f , ' =================================================='
        print >> f , ' LHCb Summary '
        print >> f , '     N_{Bs}              = ' , Nbs
        print >> f , '     N_{Bd}              = ' , Nbd
        print >> f , '     N_{Comb#mu#mu}      = ' , Ncomb
        print >> f , '     N_{MisIDhh}         = ' , Nmis
        print >> f , '     N_{h#mu#nu}         = ' , Nbmn
        print >> f , '     N_{#pi#mu#mu}       = ' , Nbmm
        print >> f , ' =================================================='


        cms_bins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3']
        NbsC,NbdC,NcombC,Nsemi,Npeak = 0,0,0,0,0

        print >> f , ' '
        print >> f , ' '
        print >> f , ' '

        for i in range(8,20):

            b = cms_bins[i-8]
            print >> f , ' =================================================='
            print >> f , ' CMS BDT Cat: ', b

            #Yields
            Nbs_bin = self.comb_ws.obj('N_bs_CombFormula_'+b).getVal()
            Nbd_bin = self.comb_ws.obj('N_bd_CombFormula_'+b).getVal()
            Ncomb_bin = self.comb_ws.obj('N_comb_formula_'+b).getVal()
            Npeak_bin= self.comb_ws.obj('N_peak_'+b+'_CMS').getVal()
            Nsemi_bin= self.comb_ws.obj('N_semi_'+b+'_CMS').getVal()
            Ntot_bin = Nbs_bin+Nbd_bin+Ncomb_bin+Nsemi_bin+Npeak_bin

            NbsC += Nbs_bin
            NbdC += Nbd_bin
            NcombC += Ncomb_bin
            Npeak += Npeak_bin
            Nsemi += Nsemi_bin
            Ntot += Ntot_bin

            print >> f , '     N_{Bs}              = ' , Nbs_bin
            print >> f , '     N_{Bd}              = ' , Nbd_bin
            print >> f , '     N_{Comb#mu#mu}      = ' , Ncomb_bin
            print >> f , '     N_{MisIDhh}         = ' , Npeak_bin
            print >> f , '     N_{h#mu#nu h#mu#mu} = ' , Nsemi_bin
            print >> f , '     -------------------------'
            print >> f , '     N_{CatTot}          = ' , Ntot_bin

            ####################

        print >> f , ' =================================================='
        print >> f , ' =================================================='
        print >> f , ' CMS Summary '
        print >> f , '     N_{Bs}              = ' , NbsC
        print >> f , '     N_{Bd}              = ' , NbdC
        print >> f , '     N_{Comb#mu#mu}      = ' , NcombC
        print >> f , '     N_{MisIDhh}         = ' , Npeak
        print >> f , '     N_{h#mu#nu h#mu#mu} = ' , Nsemi
        print >> f , ' =================================================='
        print >> f , ' =================================================='

        f.close()
        content =  open(yieldFile).read()
        print content


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

##########################################
# Plotting functions
##########################################

    def adjustPlot(self,frame,xTitle = 0, yTitle = 0,lMarg = 0.12, bMarg=0.16, yTitleSize = 0.05, yOffset = 0, rMarg = 0):

        #----------------------------------#
        #Beautification of the plots
        #----------------------------------#
        #No title
        gStyle.SetOptTitle(0)

        #Set font to Arial(or Helvetica)  fontnr = 7, and 2 is the precision
        #gStyle.SetTextFont(72)  #bold
        #gStyle.SetTextFont(62)
        gStyle.SetTextFont(42) #medium


        #Margins
        #gPad.SetTopMargin(0.18)
        if rMarg:
            gPad.SetRightMargin(rMarg)

        if bMarg:
            gPad.SetBottomMargin(0.16)
            frame.GetXaxis().SetTitleOffset(1.3)

        if lMarg:
            gPad.SetLeftMargin(lMarg)
            frame.GetYaxis().SetTitleOffset(1.1)

        if yOffset:
            frame.GetYaxis().SetTitleOffset(yOffset)

        #Labels
        frame.GetYaxis().SetTitle('Candidates / (40 MeV/#font[12]{c}^{2})')
        #frame.GetYaxis().SetTitle('Candidates per 40 MeV/#font[12]{c}^{2}')
        if yTitle: frame.GetYaxis().SetTitle(yTitle)
        frame.GetYaxis().SetTitleSize(yTitleSize)
        frame.GetYaxis().SetLabelSize(0.04)
        frame.GetYaxis().SetLabelOffset(0.01)

        frame.GetXaxis().SetTitle('#font[12]{m}_{#mu^{+}#mu^{#font[122]{-}}} [MeV/#font[12]{c}^{2}]')
        if xTitle: frame.GetXaxis().SetTitle(xTitle)
        frame.GetXaxis().SetTitleSize(0.05)
        frame.GetXaxis().SetLabelSize(0.04)
        frame.GetXaxis().SetLabelOffset(0.02)



    def addCustomYtitle(self,frame):
        #Special title for the weighted graph


        frame.GetYaxis().SetTitleSize(0.)
        # Best is to make titles ourselves:
        tya = TLatex()
        tya.SetTextAlign(11)
        tya.SetTextSize(0.05)
        tya.SetTextAngle(90.)
        tya.DrawLatexNDC(0.034, 0.23, "S/(S+B) weighted candidates")
        tya.DrawLatexNDC(0.075, 0.405, "per 40 MeV/#font[12]{c}^{2}")
        tya.Draw()

        #txax = TLatex( 0.68, 0.03, "#font[12]{m}(#font[12]{D}^{+}#pi^{#font[122]{-}}) [GeV/#font[12]{c}^{2}]")
        #txax.SetNDC(kTRUE)
        #txax.SetTextSize(0.05)
        #txax.Draw()

        return tya


    def drawCMSLHCb(self,x=0.11,y=0.91,title = '',size=0.05):
        #Add the LHCb and CMS and luminosity text
        t1 = TLatex()
        t1.SetTextAlign(11)
        t1.SetTextSize(size)
        if title:
            t1.DrawLatexNDC(x,y,title)
        else:
            t1.DrawLatexNDC(x,y,'CMS and LHCb')
        t1.Draw()
        return t1

    def drawLumiInfo(self,x=0.395,y=0.912, info = 0, size = 0.037):
        #Add the LHCb and CMS and luminosity text
        t1 = TLatex()
        t1.SetTextAlign(11)
        t1.SetTextSize(size)
        #t1.DrawLatexNDC(x,y,'#bf{#sqrt{#font[12]{s}}=7 TeV (L=5+1 fb^{-1}), #sqrt{#font[12]{s}}=8 TeV (L=20+2 fb^{#font[122]{-}1}})')
        if info:
            t1.DrawLatexNDC(x,y,info)
        else:
            t1.DrawLatexNDC(x,y,'L(#sqrt{#font[12]{s}} = 7 TeV) = 5+1 fb^{-1},L(#sqrt{#font[12]{s}} = 8 TeV) = 20+2 fb^{#font[122]{-}1}')
        t1.Draw()
        return t1

    def increaseY(self,frame,f=1.5):
        #Shift y range
        ymax = frame.GetMaximum()
        print ' Old: ymax = ', ymax
        print ' New: ymax = ', ymax*f
        frame.SetMaximum(f*ymax)


    def drawLegend(self,frame,x1=0.55,y1=0.57,x2=0.83,y2=0.86, liteVer = 0,sepBkg = 0, sepLHCbAllBkg = 0, noSig = 0, SM = 0):
        #Use:
        #MyHist->plotOn(MyFrame,RooFit::Name("some name")

        leg = TLegend(x1,y1,x2,y2)
        leg.SetFillColor(4000)
        leg.SetLineColor(4000)
        leg.SetTextSize(0.04)
        leg.AddEntry(frame.findObject("datapoints"),"Data","lep")

        if liteVer:
            leg.AddEntry(frame.findObject("total_pdf"),"Sig. and bkg.","l")

        elif noSig and not SM:
            leg.AddEntry(frame.findObject("total_pdf"),"Background only model","l")

        elif SM:
            leg.AddEntry(frame.findObject("total_pdf"),"SM sig. and meas. bkg.","l")
        else:
            leg.AddEntry(frame.findObject("total_pdf"),"Signal and background","l")

        if SM:
            leg.AddEntry(frame.findObject("bs_pdf"),"SM #font[12]{B}^{0}_{s}#rightarrow #mu^{+}#mu^{#font[122]{-}}","l")
            leg.AddEntry(frame.findObject("bd_pdf"),"SM #font[12]{B}^{0}#rightarrow #mu^{+}#mu^{#font[122]{-}}","l")


        elif not sepLHCbAllBkg and not noSig:
            leg.AddEntry(frame.findObject("bs_pdf"),"#font[12]{B}^{0}_{s}#rightarrow #mu^{+}#mu^{#font[122]{-}}","l")
            leg.AddEntry(frame.findObject("bd_pdf"),"#font[12]{B}^{0}#rightarrow #mu^{+}#mu^{#font[122]{-}}","l")


        if sepBkg:
            leg.AddEntry(frame.findObject("comb_bkg_pdf"),"Comb. bkg.","l")
            leg.AddEntry(frame.findObject("semi_bkg_pdf"),"Semi. bkg.","l")
            leg.AddEntry(frame.findObject("misid_bkg_pdf"),"Peak. bkg.","l")

        elif sepLHCbAllBkg:
            leg.AddEntry(frame.findObject("bs_pdf"),"#font[12]{B}^{0}_{s}#rightarrow #mu^{+}#mu^{#font[122]{-}}","f")
            leg.AddEntry(frame.findObject("bd_pdf"),"#font[12]{B}^{0}#rightarrow #mu^{+}#mu^{#font[122]{-}}","f")
            leg.AddEntry(frame.findObject("comb_bkg_pdf"),"Comb. bkg.","l")
            leg.AddEntry(frame.findObject("munu_bkg_pdf"),"#font[12]{B}#rightarrow h#mu#nu","l")
            leg.AddEntry(frame.findObject("mumu_bkg_pdf"),"#font[12]{B}^{0}#rightarrow #pi#mu^{+}#mu^{#font[122]{-}}","l")
            leg.AddEntry(frame.findObject("lapmunu_bkg_pdf"),"#font[12]{#Lambda}_{b}#rightarrow p#mu^{-}#nu^{#font[122]{-}}","l")
            leg.AddEntry(frame.findObject("misid_bkg_pdf"),"#font[12]{B}#rightarrow hh","l")

        else:
            leg.AddEntry(frame.findObject("bkg_pdf"),"Background","l")

        leg.Draw()

        return leg


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


    def plotComb(self,separateLHCbSemiLep = False, cmsInMeV = False, lhcbMax = 6000, sigFillStyle = 1001, bkgFillStyle = 3003, printWeights = False, separateLHCbbkg = False, separateCMSbkg=False,linew = 1, addLegend = True, onlyLHCb = False, onlyCMS = False, lowerYmax = False, addLegBinOne = False, fcErr = True):
        """ Plot LHCb and CMS mass fit in bins for combined WS."""

        xb,yb = 5,4
        resx,resy = 1350,1200
        if onlyLHCb: xb, yb, resx, resy = 2,4,1100,1200
        if onlyCMS: xb, yb,resx,resy = 3,4,1200,1200

        if separateLHCbbkg and separateCMSbkg:
            resx,resy = 1800,1200

        canva = TCanvas("combAll","combAll",resx,resy)
        canva.Divide(xb,yb)

        mass_lhcb = self.lhcb_mass
        self.lhcb_mass.setRange('LHCbrange',4900,6000)

        mass_cms = self.cms_mass
        self.cms_mass.setRange('CMSrange',4.900,5.9)

        if cmsInMeV and not onlyLHCb:
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
        legs = []
        t1 = []
        t2 = []
        wtxt=[]
        s,f = 0,20
        if onlyLHCb:f = 8
        if onlyCMS: s = 8

        for i in range(s,f):

                c = i
                if onlyCMS: c = i-8

                canva.cd(c+1)
                cat = str(i)
                #LHCb
                if i < 8:
                    print '     o) Drawing LHCb bin: ',i
                    frame = mass_lhcb.frame(RooFit.Bins(25), RooFit.Title('LHCb Bin: '+str(i+1)))
                    space = 0
                    if separateLHCbbkg and addLegend: space = 0.3
                    if i < 1: self.adjustPlot(frame,lMarg = 0.138,rMarg=space, yOffset=1.45)
                    else: self.adjustPlot(frame,rMarg = space )


                    frames.append(frame)
                    b = str(i+1)+'_LHCb'

                    data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.Invisible(),RooFit.CutRange('LHCbrange'))

                    #Make space for the legend
                    if not onlyLHCb or not separateLHCbbkg: self.increaseY(frame,f=1.4)
                    if lowerYmax: self.increaseY(frame,f=0.75)

                    if not separateLHCbbkg:
                        #Background combined to one component
                        lhcb_components = 'bkg1 MuMu model'+b+',missid'+b+',B2Xmunu'+b+',LaPmunu'+b+',B0upimumu'+b
                        model.plotOn(frame,RooFit.Components(lhcb_components),
                                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),RooFit.LineStyle(2),
                                    #RooFit.FillColor(kBlack),RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                                    RooFit.LineWidth(linew),
                                    RooFit.Range('LHCbrange'),RooFit.Name('bkg_pdf'))

                    if not separateLHCbbkg:
                        #Bs filled..
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components('model Bs'+b), RooFit.FillColor(kRed-3), RooFit.FillStyle(3004), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('LHCbrange'))
                        #Bs line
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components('model Bs'+b),RooFit.LineColor(kRed-3),RooFit.LineStyle(3),RooFit.Range('LHCbrange'),RooFit.Name('bs_pdf'),RooFit.LineWidth(linew))

                        #Bd filled..
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components('model Bd'+b), RooFit.FillColor(kGreen-3), RooFit.FillStyle(3005), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('LHCbrange'))
                        #Bd line
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components('model Bd'+b),RooFit.LineColor(kGreen-3),RooFit.LineStyle(6),RooFit.Range('LHCbrange'),RooFit.Name('bd_pdf'),RooFit.LineWidth(linew))

                    if separateLHCbbkg:
                        if separateLHCbSemiLep:
                            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                            RooFit.Components('B2Xmunu'+b),RooFit.LineColor(kBlack),RooFit.LineStyle(6),
                                            #RooFit.FillColor(kBlack), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                                            RooFit.Range('LHCbrange'),RooFit.Name('munu_bkg_pdf'),RooFit.LineWidth(linew))

                            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                            RooFit.Components('LaPmunu'+b),RooFit.LineColor(kOrange-3),RooFit.LineStyle(4),
                                            #RooFit.FillColor(kOrange), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                                            RooFit.Range('LHCbrange'),RooFit.Name('lapmunu_bkg_pdf'),RooFit.LineWidth(linew))

                            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                            RooFit.Components('B0upimumu'+b),RooFit.LineColor(kCyan-3),RooFit.LineStyle(7),
                                            #RooFit.FillColor(kCyan), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                                            RooFit.Range('LHCbrange'),RooFit.Name('mumu_bkg_pdf'),RooFit.LineWidth(linew))
                        else:
                            model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                            RooFit.Components('B2Xmunu'+b+',LaPmunu'+b+',B0upimumu'+b),RooFit.LineColor(kBlack),RooFit.LineStyle(7),
                                            #RooFit.FillColor(kBlack), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                                            RooFit.Range('LHCbrange'),
                                            RooFit.Name('semi_bkg_pdf'),RooFit.LineWidth(linew))

                        #bkg1 MuMu model
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components('bkg1 MuMu model'+b),RooFit.LineColor(28),RooFit.LineStyle(5),RooFit.Range('LHCbrange'),
                                        RooFit.Name('comb_bkg_pdf'),RooFit.LineWidth(linew))

                        #Bs filled..
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),RooFit.Components('model Bs'+b),
                                        RooFit.FillColor(kRed-3),RooFit.FillStyle(3004),RooFit.DrawOption("F"),
                                        RooFit.LineWidth(linew),RooFit.LineColor(kRed-3),RooFit.LineStyle(3),
                                        RooFit.Name('bs_pdf'))
                                        #RooFit.Range('LHCbrange'))
                        #Bs line
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components('model Bs'+b),RooFit.LineColor(kRed-3),RooFit.LineStyle(3),RooFit.Range('LHCbrange'),RooFit.LineWidth(linew))

                        #Bd filled..
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components('model Bd'+b),
                                        RooFit.FillColor(kGreen-3), RooFit.FillStyle(3005), RooFit.DrawOption("F"),
                                        RooFit.LineWidth(linew),RooFit.LineColor(kGreen-3),RooFit.LineStyle(3),
                                        RooFit.Name('bd_pdf'))
                        #Bd line
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components('model Bd'+b),RooFit.LineColor(kGreen-3),RooFit.LineStyle(3),RooFit.Range('LHCbrange'),RooFit.LineWidth(linew))


                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components('missid'+b),RooFit.LineColor(kMagenta-3),RooFit.LineStyle(2),
                                        #RooFit.FillColor(kMagenta), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                                        RooFit.Range('LHCbrange'),RooFit.Name('misid_bkg_pdf'),RooFit.LineWidth(linew))



                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue-6),
                            #RooFit.NormRange('LHCbrange'),
                            RooFit.Range('LHCbrange'),RooFit.LineWidth(linew),RooFit.Name('total_pdf'))

                    data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.MarkerSize(0.4),RooFit.LineWidth(linew),RooFit.MarkerColor(kBlack),RooFit.CutRange('LHCbrange'),RooFit.Name('datapoints'))
                    if fcErr: self.addFeldmanCousinsErrors(frame,25)


                else:
                    #CMS
                    b = cms_bins[i-8]
                    if cmsInMeV:
                        b = b+'_CMS'
                        mass_cms.setRange(4900,5900) #Set to CMS range

                    print '     o) Drawing CMS bin: ',b

                    frame = mass_cms.frame(RooFit.Bins(25), RooFit.Title('CMS Bin: '+str(i-7)))
                    space = 0
                    if separateCMSbkg and addLegend: space = 0.3
                    self.adjustPlot(frame,xTitle='#font[12]{m}_{#mu^{+}#mu^{#font[122]{-}}} [GeV/#font[12]{c}^{2}]',rMarg = space)
                    frames.append(frame)

                    data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.Invisible())

                    #Make space for the legend
                    if not onlyCMS or not separateCMSbkg: self.increaseY(frame,f=1.585)
                    if lowerYmax: self.increaseY(frame,f=0.8)

                    if not separateCMSbkg:
                        #Background combined to one component
                        cms_components = 'pdf_semi_'+b+',pdf_peak_'+b+',pdf_1comb_'+b
                        model.plotOn(frame,RooFit.Components(cms_components),
                                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
                                    RooFit.LineStyle(2),
                                    RooFit.LineWidth(linew),
                                    #RooFit.FillColor(kBlack),RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                                    RooFit.Range('CMSrange'),RooFit.Name('bkg_pdf'))


                    #"pdf_bs" filled
                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                    RooFit.Components("pdf_bs_"+b),RooFit.FillColor(kRed-3), RooFit.FillStyle(3004), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

                    #"pdf_bs" line
                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),RooFit.LineWidth(linew),
                                    RooFit.Components("pdf_bs_"+b),RooFit.LineColor(kRed),RooFit.LineStyle(3),RooFit.Range('CMSrange'),RooFit.Name('bs_pdf'))

                    #"pdf_bd" filled
                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                    RooFit.Components("pdf_bd_"+b),RooFit.FillColor(kGreen-3), RooFit.FillStyle(3005), RooFit.VLines(), RooFit.DrawOption("F"),RooFit.Range('CMSrange'))

                    #"pdf_bd" line
                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),RooFit.LineWidth(linew),
                                    RooFit.Components("pdf_bd_"+b),RooFit.LineColor(kGreen),RooFit.LineStyle(6),RooFit.Range('CMSrange'),RooFit.Name('bd_pdf'))

                    if separateCMSbkg:
                        #"pdf_semi"
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components("pdf_semi_"+b),RooFit.LineColor(kBlack),RooFit.LineStyle(7),RooFit.LineWidth(linew),
                                        #RooFit.FillColor(kBlack), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                                        RooFit.Range('CMSrange'),
                                        RooFit.Name('semi_bkg_pdf'))
                        #"pdf_peak"
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),
                                        RooFit.Components("pdf_peak_"+b),RooFit.LineColor(kMagenta),RooFit.LineStyle(2),RooFit.LineWidth(linew),
                                        #RooFit.FillColor(kMagenta), RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                                        RooFit.Range('CMSrange'),
                                        RooFit.Name('misid_bkg_pdf'))

                        #One of those (Exp, or Poly) will not be in the pdf
                        #"pdf_comb" the Exponent
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),RooFit.LineWidth(linew),
                                        RooFit.Components("pdf_comb_"+b),RooFit.LineColor(28),RooFit.LineStyle(5),RooFit.Range('CMSrange'),RooFit.Name('comb_bkg_pdf'))
                                        #,RooFit.FillColor(kRed), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

                        #"pdf_1comb" the Poly
                        model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),RooFit.LineWidth(linew),
                                        RooFit.Components("pdf_1comb_"+b),RooFit.LineColor(kCyan-3),RooFit.LineStyle(kDotted),RooFit.Range('CMSrange'),RooFit.Name('comb_bkg_pdf'))
                                    #,RooFit.FillColor(kRed), RooFit.FillStyle(3008), RooFit.VLines(), RooFit.DrawOption("F"))

                    model.plotOn(frame,RooFit.Slice(category,cat),RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue-6),
                            #RooFit.Range('CMSrange'),RooFit.NormRange('CMSrange'), #no help
                            RooFit.LineWidth(linew),RooFit.Name('total_pdf'))


                    data.plotOn(frame, RooFit.Cut(category.GetName()+'=='+category.GetName()+'::'+cat),RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlack),RooFit.CutRange('CMSrange'),RooFit.Name('datapoints'),RooFit.LineWidth(linew))
                    if fcErr: self.addFeldmanCousinsErrors(frame,25)

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

                #Add LHCb to the plot
                if i<8:t1.append(self.drawCMSLHCb(x=0.12,title='LHCb (BDT category '+str(i+1)+')',size = 0.055))
                else: t1.append(self.drawCMSLHCb(x=0.12,title='CMS (BDT category '+str(i-7)+')', size = 0.055))

                #Legend
                if not separateCMSbkg and not separateLHCbbkg and addLegend:
                    legs.append(self.drawLegend(frame,liteVer = True,x1=0.63,y1=0.593,y2=0.88))
                elif separateCMSbkg and separateLHCbbkg and addLegend:
                    legs.append(self.drawLegend(frame,liteVer = True,x1=0.71,y1=0.2,x2=1.,y2=0.88, sepBkg = True))
                elif onlyCMS and separateCMSbkg:
                    legs.append(self.drawLegend(frame,liteVer = True,x1=0.71,y1=0.2,x2=1.,y2=0.88, sepBkg = True))
                elif onlyLHCb and separateLHCbbkg and not separateLHCbSemiLep:
                    legs.append(self.drawLegend(frame,liteVer = True,x1=0.71,y1=0.2,x2=1.,y2=0.88, sepBkg = True))
                elif onlyLHCb and separateLHCbbkg and separateLHCbSemiLep:
                    legs.append(self.drawLegend(frame,liteVer = True,x1=0.71,y1=0.2,x2=1.,y2=0.88, sepLHCbAllBkg = True))
                elif addLegBinOne and i < 1:
                    print 'Adding legend to bin 1 only...'
                    legs.append(self.drawLegend(frame,liteVer = True,x1=0.165,y1=0.195,x2=0.46,y2=0.6, sepBkg = True))


                #Add CMS+LHCb and luminosity info
                #Every plot is a subselection!! not total lumi...
                #t2.append(self.drawLumiInfo(x=0.69,info='L = 25+3 fb^{#font[122]{-}1}',size=0.05))

        suf = ''
        if onlyLHCb: suf = '_onlyLHCbcats_'
        if onlyCMS: suf = '_onlyCMScats_'
        if separateCMSbkg and separateLHCbbkg: suf+='_separateBkg_'
        if fcErr: suf+= '_FCErr_'

        canva.SaveAs(self.resDir+'Plot_'+self.combName+suf+'_massFitInBins.pdf')
        canva.SaveAs(self.resDir+'Plot_'+self.combName+suf+'_massFitInBins.root')
        canva.SaveAs(self.resDir+'Plot_'+self.combName+suf+'_massFitInBins.eps')
        canva.SaveAs(self.resDir+'Plot_'+self.combName+suf+'_massFitInBins.C')

        return canva,legs


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

    def plotCombinedMassBestBins8(self, bins = 25, separateSignal = False,rangeMax = 5900, sigFillStyle = 1001, bkgFillStyle = 3003, noSignal = False):
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

        if separateSignal and not noSignal:
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

        elif not noSignal:
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


    def addFeldmanCousinsErrors(self, frame,bins):
        frame.Print()
        hist = frame.getHist('datapoints')
        hist.Print('v')

        fc = TFeldmanCousins(0.6827)

        for b in range(0,bins):
            #n = thf.GetBinContent(b)

            m, n = Double(0), Double(0)
            hist.GetPoint(b,m,n)

            if n < 35:
                ul = fc.CalculateUpperLimit(n,0.)
                ll = fc.CalculateLowerLimit(n,0.)

                hist.SetPointEYhigh(b,ul-n)
                hist.SetPointEYlow(b,n-ll)
                print ' Setting 68% FC limits for point ',b,' wirh ',n,' events to [',ll,',',ul,']'
            else: print ' n>50, using Poisson errors'
        hist.Print('v')

        return 0


    def plotCombinedMassBestBins(self, bins = 25, separateSignal = False,rangeMax = 5900, sigFillStyle = 1001, bkgFillStyle = 4000, addLegend = True, sepBkg = False, noSignal = False, fcErr = True, noXErr = False):
        """ Plot LHCb and CMS data stacked on top of eachother
            Works only with the same mass scale and variable. Best bins!"""

        print ' Plotting LHCb and CMS together on one mass plot for the best bins only...'

        canva = TCanvas("cmslhcbMeV_best","cmslhcbMeV_best")

        #Change to the same mass variable and range
        mass = self.comb_ws.obj('B_s0_MM')
        mass.setRange(4900,rangeMax)
        mass.setRange('CMSrange',4900,rangeMax)
        mass.setRange('fullrange',4900,6000)

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


        frame = mass.frame(RooFit.Bins(bins), RooFit.Title(''))

        #Set the margins,titles, axis parameters
        self.adjustPlot(frame)
        data.plotOn(frame, RooFit.Cut(cut_lhcb_B+'||'+cut_cms_B),RooFit.Invisible())

        #Background
        if sepBkg:
           #Semileptonic misID bkg
            comp = 'pdf_semi_0_1*,pdf_semi_2_3*,pdf_semi_3_3*,'+\
                                'B2Xmunu6*,B2Xmunu7*,B2Xmunu8*,'+\
                                'LaPmunu6*,LaPmunu7*,LaPmunu8*,'+\
                                'B0upimumu6*,B0upimumu7*,B0upimumu8*'
            model.plotOn(frame,RooFit.Components(comp),
            RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
            RooFit.LineStyle(2),
            #RooFit.FillColor(kBlack),RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
            RooFit.Range('CMSrange'),RooFit.Name("semi_bkg_pdf"))

            #Combinatorial bkg
            comp = "pdf_1comb_0_1*,pdf_1comb_2_3*,pdf_1comb_3_3*,bkg1 MuMu model6*,bkg1 MuMu model7*,bkg1 MuMu model8*"
            model.plotOn(frame,RooFit.Components(comp),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kCyan-3),
                        RooFit.LineStyle(3),
                        #RooFit.FillColor(kBlack),RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                        RooFit.Range('CMSrange'),RooFit.Name("comb_bkg_pdf"))

            #B2hh misID bkg
            comp = "pdf_peak_0_1*,pdf_peak_2_3*,pdf_peak_3_3*,missid6*,missid7*,missid8*"
            model.plotOn(frame,RooFit.Components(comp),
            RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kMagenta-3),
            RooFit.LineStyle(9),
            #RooFit.FillColor(kBlack),RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
            RooFit.Range('CMSrange'),RooFit.Name("misid_bkg_pdf"))


        else:
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
                        RooFit.LineStyle(2),
                        #RooFit.FillColor(kBlack),RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                        RooFit.Range('CMSrange'),RooFit.Name("bkg_pdf"))



        #Total pdf
        cms_components = "pdf_ext_total_0_1*,pdf_ext_total_2_3*,pdf_ext_total_3_3*,"
        lhcb_components = "mumu_model_6*,mumu_model_7*,mumu_model_8*"
        model.plotOn(frame,RooFit.Components(cms_components+lhcb_components),
                    RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue-6),RooFit.Range('CMSrange'),RooFit.NormRange('fullrange'),RooFit.Name("total_pdf"))


        if separateSignal and not noSignal:
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

        elif not noSignal:
            #Bs
            cms_components = "pdf_bs_0_1*,pdf_bs_2_3*,pdf_bs_3_3*"
            lhcb_components = "model Bs6*,model Bs7*,model Bs8*"
            #filled..
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),
                        RooFit.FillColor(kRed-3),RooFit.FillStyle(3004),
                        RooFit.VLines(),
                        RooFit.DrawOption("F"),
                        RooFit.Range('CMSrange'))

            #line..
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),
                        RooFit.LineColor(kRed-3),RooFit.LineStyle(7),
                        RooFit.Range('CMSrange'),RooFit.Name("bs_pdf"))

            #Bd
            cms_components = "pdf_bd_0_1*,pdf_bd_2_3*,pdf_bd_3_3*"
            lhcb_components = "model Bd6*,model Bd7*,model Bd8*"
            #filled..
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),
                        RooFit.FillColor(kGreen-3),RooFit.FillStyle(3005),
                        RooFit.VLines(), RooFit.DrawOption("F"),
                        RooFit.Range('CMSrange'))
            #lines...
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),
                        RooFit.LineColor(kGreen-3),RooFit.LineStyle(5),
                        RooFit.Range('CMSrange'),RooFit.Name("bd_pdf"))


        if noXErr:
            data.plotOn(frame, RooFit.Cut(cut_lhcb_B+'||'+cut_cms_B),
                         RooFit.MarkerSize(1.),
                         RooFit.XErrorSize(0),
                         RooFit.MarkerColor(kBlack),
                         RooFit.LineWidth(2),
                         RooFit.Name("datapoints"))

        else:
            data.plotOn(frame, RooFit.Cut(cut_lhcb_B+'||'+cut_cms_B),
                         RooFit.MarkerSize(0.8),
                         RooFit.MarkerColor(kBlack),
                         RooFit.LineWidth(2),
                         RooFit.Name("datapoints"))

        if fcErr :self.addFeldmanCousinsErrors(frame,bins)

        frame.Draw()

        #Legend
        leg = 0
        if not separateSignal and addLegend and not noSignal:
            leg = self.drawLegend(frame,y1=0.48,sepBkg=sepBkg)
        elif noSignal:
            leg = self.drawLegend(frame,y1=0.48,sepBkg=sepBkg,noSig = True)

        #Add CMS+LHCb and luminosity info
        t1 = self.drawCMSLHCb(x=0.12)
        t2 = self.drawLumiInfo(x=0.4)

        suf = ''
        if fcErr: suf = '_fcErr'
        if noXErr: suf += '_noXErr'

        if sepBkg:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins_SepBkg'+suf+'.pdf')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins_SepBkg'+suf+'.root')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins_SepBkg'+suf+'.eps')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins_SepBkg'+suf+'.C')

        elif separateSignal:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins_SepSign'+suf+'.pdf')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins_SepSign'+suf+'.root')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins_SepSign'+suf+'.eps')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins_SepSign'+suf+'.C')

        else:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins'+suf+'.root')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins'+suf+'.eps')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins'+suf+'.pdf')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedMass_BestBins'+suf+'.C')

        return canva,leg,t1,t2

    #Plot the LHCb data on one plot, for the best bins
    def plotLHCbMassBestBins(self, bins = 25,rangeMax = 5900, sigFillStyle = 4000, bkgFillStyle = 4000):
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

        data.plotOn(frame, RooFit.Cut(cut_lhcb_B),RooFit.MarkerSize(0.6),RooFit.MarkerColor(kBlack),RooFit.Invisible())

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

        #Fix the BR of the fit to the SM expectation values to calculate the expected S/S+B weights
        #Note that the measured background is the expected one (the signal BR was free to fit the signal comp.)
        #\newcommand{\BRBsmm}{\ensuremath{3.66\pm0.23}\xspace}
        #\newcommand{\BRBdmm}{\ensuremath{1.06\pm0.09}\xspace}

        #Make a copy, to still have the fitted BR
        #smWS = RooWorkspace(self.comb_ws)

        self.comb_ws.obj('BRs').setVal(3.66)
        self.comb_ws.obj('BRs').setError(0.23)
        self.comb_ws.obj('BRd').setVal(1.06)
        self.comb_ws.obj('BRd').setError(0.09)

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
        Bs_pdfList = RooArgList()
        weights = []
        wList = RooArgList()

        for i in range(0,20):

            #Get LHCb bin pdf's
            binPdf = 0
            if i < 8:
                b = str(i+1)+'_LHCb'
                binPdf = self.comb_pdf.getComponents()['mumu_model_'+b]
                binBsPdf = self.comb_pdf.getComponents()['model Bs'+b]

            else: #CMS
                b = cms_bins[i-8]
                binPdf = self.comb_pdf.getComponents()['pdf_ext_total_'+b+'_CMS']
                binBsPdf = self.comb_pdf.getComponents()['pdf_bs_'+b+'_CMS']

            #Add the pdf and a bin weight to the list
            pdfList.add(binPdf)
            Bs_pdfList.add(binBsPdf)
            weights.append(RooRealVar('w'+str(i+1),'S/S+B bin weight for bin '+str(i+1),self.normWeights[i]))
            wList.add(weights[-1])
            print ' ============================  '
            print ' BIN:', i
            print ' ============================  '
            print ' Added pdf   :', binPdf.GetName()
            print ' Added Bs pdf   :', binBsPdf.GetName()
            print ' Added weight:', self.normWeights[i]

        print ' ============================  '
        pdfList.Print()
        Bs_pdfList.Print()
        wList.Print()
        comb_wpdf = RooAddPdf('comb_wpdf','Weighted combined LHCb+CMS pdf',pdfList,wList)
        comb_wBspdf = RooAddPdf('comb_wBspdf','Weighted combined LHCb+CMS Bs pdf',Bs_pdfList,wList)
        print ' Combined and weighted pdf built! (self.comb_wpdf)'
        comb_wpdf.Print()
        getattr(self.comb_ws,'import')(comb_wpdf, RooFit.RecycleConflictNodes())
        print ' Combined and weighted Bs pdf built! (self.comb_wBspdf)'
        comb_wBspdf.Print()
        getattr(self.comb_ws,'import')(comb_wBspdf, RooFit.RecycleConflictNodes())
        print ' ============================  '
        self.comb_wpdf = self.comb_ws.obj('comb_wpdf')
        self.comb_wBspdf = self.comb_ws.obj('comb_wBspdf')

        return self.comb_wpdf

    def calcWBsFrac(self):
        """Calculates the fraction of total Bs yields w.r.t to the total yield."""


        cms_bins = ['0_0','0_1','1_0','1_1','2_0','2_1','2_2','2_3','3_0','3_1','3_2','3_3']
        lhcb_comp = ['NBs','MuMuBkg','NBd','Nmis','N_B2Xmunu','N_B0pimumu','N_LaPmunu']
        cms_comp = [ 'N_bs_CombFormula_','N_bd_CombFormula_','N_comb_formula_','N_semi_','N_peak_']
        cms_suf = [ '','','','_CMS','_CMS']

        N_Bs, N_tot = [],[]
        N_Bs_tot, N_tot_tot = 0,0
        N_frac = []
        #Calculate SumOverCats( w_cat * (N_Bs)) / SumOverCats(w_cat*(N_Bs + ...))
        for i in range(0,20):
            #LHCb components
            if i < 8:
                b = str(i+1)+'_LHCb'
                N_Bs.append(self.comb_ws.obj(lhcb_comp[0]+b).getVal())
                print ' N_Bs in cat '+b+' :',N_Bs[-1]
                print ' N_Bs in cat '+b+' :',N_Bs[-1]
                N_Bs_tot+=N_Bs[-1]

                N_tot_cat = 0
                for comp in lhcb_comp: N_tot_cat+=self.comb_ws.obj(comp+b).getVal()
                N_tot.append(N_tot_cat)
                print ' N_tot in cat '+b+' :',N_tot[-1]
                N_tot_tot += N_tot[-1]


            else: #CMS
                b = cms_bins[i-8]
                N_Bs.append(self.comb_ws.obj(cms_comp[0]+b+cms_suf[0]).getVal())
                print ' N_Bs in cat '+b+' :',N_Bs[-1]
                N_Bs_tot+=N_Bs[-1]

                N_tot_cat = 0
                for a in range(0,5): N_tot_cat+=self.comb_ws.obj(cms_comp[a]+b+cms_suf[a]).getVal()
                N_tot.append(N_tot_cat)
                print ' N_tot in cat '+b+' :',N_tot[-1]
                N_tot_tot += N_tot[-1]

            #ractions per bin
            N_frac.append(N_Bs[-1]/N_tot[-1])
            print ' NBs / Ntot = ', N_frac[-1]


        #Get the weighted sums
        wN_Bs,wN_tot = [],[]
        wN_Bs_tot,wN_tot_tot = 0,0
        totFrac, wtotFrac = 0,0
        for i in range(0,20):
            print ' o) Cat : ',i
            w = self.normWeights[i]
            print '     w = ' ,w

            wN_Bs.append(w*N_Bs_tot)
            print '     w*NBs = ' ,wN_Bs[-1]
            wN_Bs_tot+=wN_Bs[-1]

            wN_tot.append(w*N_tot_tot)
            print '     w*Ntot = ' ,wN_tot[-1]
            wN_tot_tot+=wN_tot[-1]

            totFrac += N_frac[i]
            wtotFrac += w*N_frac[i]

        print '-------------------'
        print ' SumOverCats(NBs) = ', N_Bs_tot
        print ' SumOverCats(w*NBs) = ', wN_Bs_tot
        print ' SumOverCats(Ntot) = ', N_tot_tot
        print ' SumOverCats(w*Ntot) = ', wN_tot_tot
        self.fracBs = N_Bs_tot/N_tot_tot
        print ' Bs fraction in the nominal pdf:', self.fracBs
        print ' SumOverCats( N_frac)', totFrac
        print ' SumOverCats( w*N_frac)', wtotFrac
        self.wFracBs = wtotFrac #~0.17
        print '-------------------'

        return [N_Bs_tot,self.wFracBs]

    def buildWeightedData(self):

        #Start the weighted dataset from bin 1, then loop and append other bins

        cat = self.comb_cat
        catN = cat.GetName()
        Ntot = self.comb_data.numEntries()

        #Normalize to the Bs yields
        res = self.calcWBsFrac() #[Bs yield~72,bsFracAfterWeighting~0.17]
        #Nnorm = (30.54+42.01)*(1/0.17)
        Nnorm = res[0]*(1/res[1])
        print ' plotting...'
        #~0.17 is the contribution of Bs pdf to the total S/S+B weighted pdf
        # The NNorm is the total weighted data, so 17% is Bs (72.55)


        self.dataWeights = []

        #LHCb bin 1
        i = 0
        data_bin = getattr(self.comb_data,'reduce')(catN+'=='+catN+"::"+str(i))

        dataWeight = self.normWeights[i]*Nnorm/data_bin.numEntries()
        w = RooRealVar('w','Weight = (S/S+B)^norm * N_tot / N_cat',dataWeight)
        self.dataWeights.append(dataWeight)
        data_bin.addColumn(w)
        data_sum = data_bin.Clone()

        for i in range(1,20):
            data_bin = getattr(self.comb_data,'reduce')(catN+'=='+catN+"::"+str(i))
            #w.setVal(self.normWeights[i]*Nnorm/data_bin.numEntries())
            dataWeight = self.normWeights[i]*Nnorm/data_bin.numEntries()
            w.setVal(dataWeight)
            self.dataWeights.append(dataWeight)
            data_bin.addColumn(w)
            data_sum.append(data_bin)


        #Now interpret the 'w' as a weight of the event
        wdata = RooDataSet(data_sum.GetName(),data_sum.GetTitle(),data_sum,data_sum.get(),'',w.GetName())

        getattr(self.comb_ws,'import')(wdata,'comb_wdata')
        self.comb_wdata = self.comb_ws.obj('comb_wdata')
        return self.comb_wdata


    def addWeightedFCErr(self,frame,bins):
        """Add FC Asymmetrical errors to the weighted plot"""

        #Symmetric errors are err = sqrt( w1^2*N1 + w2^2*N2 + ...)
        #Asymmetric errors
        #   err_up = sqrt( w1^2*err_up_1^2 + w2^2*err_up_2^2 + ...)  and same for err_lo
        # err_up_# and low come from the TFeldmanCousins(N_#,0) routine

        fc = TFeldmanCousins(0.68)

        err_up_cat_bin = [[0 for x in xrange(bins)] for x in xrange(20)]
        err_lo_cat_bin = [[0 for x in xrange(bins)] for x in xrange(20)]
        N_cat_bin = [[0 for x in xrange(bins)] for x in xrange(20)]

        #We need category yields in every mass bin separately
        #Generate histograms for every category and go through the bins to get yields and asym FC errors
        frame2 = frame.Clone('copy')

        for cat in range(1,21):

            cut = 'comb_cat==comb_cat::LHCb_bin_'+str(cat)
            if cat > 8: cut = 'comb_cat==comb_cat::CMS_bin_'+str(cat-8)

            histName = 'hist_cat_'+str(cat)
            self.comb_data.plotOn(frame2, RooFit.Cut(cut),RooFit.Invisible(),RooFit.Name(histName))

            print 'o) Category = ', cut
            for b in range(0,bins):
                #Get the yields, upper, and lower errors from FC for this category for every mass bin
                hist_cat = frame2.getHist(histName)
                m, n = Double(0), Double(0)
                hist_cat.GetPoint(b,m,n)
                N_cat_bin[cat-1][b] = n

                # This is what the default option in RooFitErrors Sumw2 would be:
                #ul = sqrt(n)
                #lo = sqrt(n)

                #if n < 50: #Use the FC
                ul = fc.CalculateUpperLimit(n,0.)-n
                lo = n-fc.CalculateLowerLimit(n,0.)


                err_up_cat_bin[cat-1][b] = ul
                err_lo_cat_bin[cat-1][b] = lo
                print '     68% FC limits for bin ',b,' wirh ',n,' events to [-',lo,',+',ul,']'

        #Get the total upper and lover errors for a combine weighted mass bin
        hist = frame.getHist('datapoints')
        hist.Print('v')

        for b in range(0,bins):
            err_up_sq, err_lo_sq = 0,0
            for c in range(0,20):
                err_up_sq += (self.dataWeights[c]**2) * (err_up_cat_bin[c][b]**2)
                err_lo_sq += (self.dataWeights[c]**2) * (err_lo_cat_bin[c][b]**2)


            #Errors
            ul = sqrt(err_up_sq)
            ll = sqrt(err_lo_sq)

            hist.SetPointEYhigh(b,ul)
            hist.SetPointEYlow(b,ll)

        hist.Print('v')
        raw_input('ok?')
        return 0



    def plotWeightedMass(self, bins = 25, separateSignal = False,rangeMax = 5900, sigFillStyle = 1001, bkgFillStyle = 3003, addLegend = True, SMexpected = False, offset = 1, CPU=8, separateBkg = False, fcErr = True):
        """ Plot a combined mass plot, where the bins (pdf,data) are weighted by S/S+B. The S, and B are gotten from pdf values
        at the Bs peak. This is equivalent to integratins around the Bs peak+-sigma range."""

        print '  Plotting the combined weighted mass plot...'

        #Tp plot the weighted mass plot, you need to call before:
        self.getSBweights()

        if not SMexpected:
            self.fitCombinedModel(offset,CPU,reFit = False, fixBs = False, fixBd = False)

        self.buildWeightedPdf()
        self.buildWeightedData()


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

        #Set the margins,titles, axis parameters
        self.adjustPlot(frame,yTitle = 'S/(S+B) weighted cand. / (40 MeV/#font[12]{c}^{2})')

        #Background
        if separateBkg:
           #Semileptonic misID bkg
            comp = 'pdf_semi_*,B2Xmunu*,LaPmunu*,B0upimumu*'
            model.plotOn(frame,RooFit.Components(comp),
            RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
            RooFit.LineStyle(2),
            #RooFit.FillColor(kBlack),RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
            RooFit.Range('CMSrange'),RooFit.Name("semi_bkg_pdf"))

            #Combinatorial bkg
            comp = "pdf_1comb_*,bkg1 MuMu model*"
            model.plotOn(frame,RooFit.Components(comp),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kCyan-3),
                        RooFit.LineStyle(3),
                        #RooFit.FillColor(kBlack),RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
                        RooFit.Range('CMSrange'),RooFit.Name("comb_bkg_pdf"))

            #B2hh misID bkg
            comp = "pdf_peak_*,missid*"
            model.plotOn(frame,RooFit.Components(comp),
            RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kMagenta-3),
            RooFit.LineStyle(9),
            #RooFit.FillColor(kBlack),RooFit.FillStyle(bkgFillStyle), RooFit.VLines(), RooFit.DrawOption("F"),
            RooFit.Range('CMSrange'),RooFit.Name("misid_bkg_pdf"))

        else:
            cms_components = 'pdf_semi_*,pdf_peak_*,pdf_1comb_*'
            lhcb_components = 'bkg1 MuMu model*,missid*,B2Xmunu*,LaPmunu*,B0upimumu*'

            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlack),
                        RooFit.LineStyle(2),RooFit.Range('CMSrange'),RooFit.Name('bkg_pdf'))

        #Total pdf
        model.plotOn(frame, RooFit.ProjWData(RooArgSet(category),data),RooFit.LineColor(kBlue-6),RooFit.Range('CMSrange'),RooFit.Name('total_pdf'))


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
            #filled..
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),
                        RooFit.FillColor(kRed-3),RooFit.FillStyle(3004),
                        RooFit.VLines(),
                        RooFit.DrawOption("F"),
                        RooFit.Range('CMSrange'))
            #line..
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),
                        RooFit.LineColor(kRed-3),RooFit.LineStyle(7),
                        RooFit.Range('CMSrange'),RooFit.Name("bs_pdf"))

            #Bd
            cms_components = "pdf_bd_*"
            lhcb_components = "model Bd*"
            #filled..
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),
                        RooFit.FillColor(kGreen-3),RooFit.FillStyle(3005),
                        RooFit.VLines(),
                        RooFit.DrawOption("F"),
                        RooFit.Range('CMSrange'))
            #line..
            model.plotOn(frame,RooFit.Components(cms_components+','+lhcb_components),
                        RooFit.ProjWData(RooArgSet(category),data),
                        RooFit.LineColor(kGreen-3),RooFit.LineStyle(5),
                        RooFit.Range('CMSrange'),RooFit.Name("bd_pdf"))

        data.plotOn(frame,
                         RooFit.DataError(RooAbsData.SumW2),
                         #RooFit.DataError(RooAbsData.Poisson),
                         RooFit.MarkerSize(0.8),
                         #RooFit.XErrorSize(0),
                         RooFit.MarkerColor(kBlack),
                         RooFit.LineWidth(2),
                         RooFit.Name("datapoints"))

        if fcErr: self.addWeightedFCErr(frame,bins)

        frame.Draw()

        #Add a custom 2 line tutle, as it's loooooong
        yTitle = 0
        #yTitle = self.addCustomYtitle(frame)


        #Legend
        leg = 0
        if SMexpected:
            leg = self.drawLegend(frame,SM=1,sepBkg=separateBkg, y1 = 0.5)
        elif not separateSignal and addLegend:
            leg = self.drawLegend(frame,sepBkg=separateBkg, y1 = 0.5)


        #Add CMS+LHCb and luminosity info
        t1 = self.drawCMSLHCb(x=0.12)
        t2 = self.drawLumiInfo()

        suf = ''
        if separateBkg: suf = '_sepBkg_'
        if fcErr: suf += '_FCErrors_'

        if SMexpected:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeigtedMass_bins_'+str(bins)+suf+'_SMexpected.pdf')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeigtedMass_bins_'+str(bins)+suf+'_SMexpected.C')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeigtedMass_bins_'+str(bins)+suf+'_SMexpected.root')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeigtedMass_bins_'+str(bins)+suf+'_SMexpected.eps')
        elif separateSignal:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeigtedMass_bins_'+str(bins)+suf+'_SignSep.pdf')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeigtedMass_bins_'+str(bins)+suf+'_SignSep.C')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeigtedMass_bins_'+str(bins)+suf+'_SignSep.root')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeigtedMass_bins_'+str(bins)+suf+'_SignSep.eps')
        else:
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeightedMass_bins_'+str(bins)+suf+'.root')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeightedMass_bins_'+str(bins)+suf+'.eps')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeightedMass_bins_'+str(bins)+suf+'.pdf')
            canva.SaveAs(self.resDir+'Plot_'+self.combName+'_CombinedWeightedMass_bins_'+str(bins)+suf+'.C')

        return canva,t1,t2, leg, yTitle

    def saveCombWorkspace(self):
        ''' Saves the combined worskspace to file '''
        wsFile = self.resDir + 'combinedWorkspace_'+self.combName+'.root'
        print "Going to save the combined workspace to ", wsFile
        self.comb_ws.SaveAs(wsFile)



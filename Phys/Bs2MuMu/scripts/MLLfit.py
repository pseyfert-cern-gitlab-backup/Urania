from ROOT import *
from valAndErr import *
#Mass model for the fit
from SomeMassModels import B2JpsiModels as B
import os

def oldConf(fit):
			print '    configuring fitter..'
			fit.fsh.setVal(0)
			fit.fsh.setConstant(kTRUE)
			fit.sh_mean.setConstant(kTRUE)
			fit.sh_sigma.setConstant(kTRUE)
			fit.delta_m.setRange(0.,200.) #Let the resolution addition of the second Gaussian go to zero if needed.


def fitBu2JpsiKplus(data, massVar, cutName, cut):
        print ' o) Perform the mass fit on Bu2JpsiKplus... \n '

        tree = data.get('tree')
	print '    The tree I am fitting:'
	print '    Entries: ',tree.GetEntries()

        #asd = raw_input('...')

        # ------------------------------------#
        # The form of initialization function:
	#__init__(tree, var,cuts="", shorTime = True, weight_var=0, fit1peak = True, fixBs = True, single = 0,fit_in_init = False):
        #FiterBasis. __init__(tree, var,cuts, shorTime, weight_var, sigf = double_gaussian, bkgf = bujpsik_bkg, fit_in_init=fit_in_init)
        # ------------------------------------#

        #sh_mean.setRange(5000.,5250.)
	fitBu = B.BuJPsiK(tree,massVar, cut)
	#fitBu = B.BuJPsiK(tree,massVar, cut, True, 0., True, True, 0, 0.)

        print ' o) Configuring fitter..'
        fitBu.fsh.setVal(0)
        fitBu.fsh.setConstant(kTRUE)
        fitBu.sh_mean.setConstant(kTRUE)
        fitBu.sh_sigma.setConstant(kTRUE)
        fitBu.delta_m.setRange(0.,200.) #Let the resolution addition of the second Gaussian go to zero if needed.


	print ' o) FIT:'
	fitBu.fit({},8)
        print ' FIT has converged!'

        print ' o) Save the plot in root file, and ps...'
        rootName = data.get('name')+'_'+massVar+'_Fit_'+cutName
        directory = 'MassFitResults/Bu2JpsiKplus/Plots/'
        if not os.path.exists(directory): os.makedirs(directory)
        plotName = massVar+'_Fit_'+cutName+'_LogScale_'+str(log)
        canvas = TCanvas(massVar+'_canv',massVar+'_canv', 800,600)
        fr = fitBu.plot(100)
        file = TFile(directory+rootName+'.root','RECREATE')
        fr.Write()
        file.Close()
        canvas.SaveAs(directory+rootName+'.ps')

        print ' o) Save the fitted parameters to a file..'
        directory = 'MassFitResults/Bu2JpsiKplus/'
        fitBu.model.getParameters(fitBu.data).writeToFile(directory+rootName+'_PARAMETERS.txt')

        print ' o) Save the fit info to a file..'
        directory = 'MassFitResults/Bu2JpsiKplus/'

        #Calculate the B mass resolution (weighted average of the double gaussian sigmas)
        fr = valAndErr(fitBu.f1.getVal(), fitBu.f1.getError())
        oneMinFr = valAndErr(1.,0.).minus(fr)
        B_mass_mean = valAndErr(fitBu.mean1.getVal(), fitBu.mean1.getError())
        sigma1 = valAndErr(fitBu.sigma1.getVal(), fitBu.sigma1.getError())
        delta_s = valAndErr(fitBu.delta_s.getVal(), fitBu.delta_s.getError())
        sigma2 = sigma1.plus( delta_s )

        # res = sqrt(  f^2 * sig1^2 + (1-f)^2*sig2^2 )
        #B_mass_sigma =  ( ((fr.times(fr)).times(sigma1.times(sigma1))).plus((oneMinFr.times(oneMinFr)).times(sigma2.times(sigma2)))  ).sqrt()

        # res = sqrt(  f * sig1^2 + (1-f)*sig2^2 ) CORRECT!!!
	B_mass_sigma =  ( (fr.times(sigma1.times(sigma1))).plus(oneMinFr.times(sigma2.times(sigma2)))  ).sqrt()

	# Simple f_s1 + (1-f)s2
        #B_mass_sigma =  (fr.times(sigma1)).plus(oneMinFr.times(sigma2))

	f = open(directory+rootName+'_FitInfo.txt','w')
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        print >> f, ' # FIT INFO FOR: ', data.get('name')
        print >> f, ' # CHANNEL : Bu2JpsiKplus'
        print >> f, ' # Luminosity in pb : ',data.get('lumi').getVal()," +- ",data.get('lumi').getErr()
	print >> f, ' # Entries before the cut: ',tree.GetEntries()
        print >> f, ' # MassVar: ', massVar
        print >> f, ' # cut :', cut
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        print >> f, ' # N_sig : ',fitBu.nsig.getVal(),' +- ',fitBu.nsig.getError()
        print >> f, ' # B mass mean : ',B_mass_mean.getVal(),' +- ',B_mass_mean.getErr()
        print >> f, ' # B mass reso : ',B_mass_sigma.getVal(),' +- ',B_mass_sigma.getErr()
        print >> f, ' # reso = sqrt(  f * sig1^2 + (1-f) * sig2^2 )'
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        f.close()


        # Print the file content in terminal:
        content =  open(directory+rootName+'_FitInfo.txt').read()
        print content
        return valAndErr(fitBu.nsig.getVal(),fitBu.nsig.getError())



def fitBs2JpsiPhi(data, massVar, cutName, cut):
        print ' o) Perform the mass fit on Bs2JpsiPhi... \n '

        tree = data.get('tree')
	print '    The tree I am fitting:'
	print '    Entries: ',tree.GetEntries()

        #asd = raw_input('...')
        # ------------------------------------#
        # The form of initialization function:
	#__init__(tree, var,cuts="", shorTime = True, weight_var=0, fit1peak = True, fixBs = True, single = 0,fit_in_init = False):
        #FiterBasis. __init__(tree, var,cuts, shorTime, weight_var, sigf = double_gaussian, bkgf = bujpsik_bkg, fit_in_init=fit_in_init)
        # ------------------------------------#

        fitBs = B.DoubleGaussian(self.tree,massVar,cut)
        #fitBs.fitIfNotSaved({'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8, 'fitAnyhow':fitAnyhow})

        print ' o) Configuring fitter..'

	print ' o) FIT:'
        fitBs.fit({},8)
        print ' FIT has converged!'

        print ' o) Save the plot in root file, and ps...'
        rootName = data.get('name')+'_'+massVar+'_Fit_'+cutName
        directory = 'MassFitResults/Bs2JpsiPhi/Plots/'
        if not os.path.exists(directory): os.makedirs(directory)
        plotName = massVar+'_Fit_'+cutName+'_LogScale_'+str(log)
        canvas = TCanvas(massVar+'_canv',massVar+'_canv', 800,600)
        fr = fitBu.plot(100)
        file = TFile(directory+rootName+'.root','RECREATE')
        fr.Write()
        file.Close()
        canvas.SaveAs(directory+rootName+'.ps')

        print ' o) Save the fitted parameters to a file..'
        directory = 'MassFitResults/Bs2JpsiPhi/'
        fitBu.model.getParameters(fitBu.data).writeToFile(directory+rootName+'_PARAMETERS.txt')

        print ' o) Save the fit info to a file..'

        #Calculate the B mass resolution (weighted average of the double gaussian sigmas)
        fr = valAndErr(fitBu.f1.getVal(), fitBu.f1.getError())
        oneMinFr = valAndErr(1.,0.).minus(fr)
        B_mass_mean = valAndErr(fitBu.mean1.getVal(), fitBu.mean1.getError())
        sigma1 = valAndErr(fitBu.sigma1.getVal(), fitBu.sigma1.getError())
        delta_s = valAndErr(fitBu.delta_s.getVal(), fitBu.delta_s.getError())
        sigma2 = sigma1.plus( delta_s )

        #res = sqrt(  f^2 * sig1^2 + (1-f)^2*sig2^2 )
        #B_mass_sigma =  ( ((fr.times(fr)).times(sigma1.times(sigma1))).plus((oneMinFr.times(oneMinFr)).times(sigma2.times(sigma2)))  ).sqrt()

        # res = sqrt(  f * sig1^2 + (1-f)*sig2^2 ) CORRECT!!!
	B_mass_sigma =  ( (fr.times(sigma1.times(sigma1))).plus(oneMinFr.times(sigma2.times(sigma2)))  ).sqrt()

	# Simple f_s1 + (1-f)s2
        #B_mass_sigma =  (fr.times(sigma1)).plus(oneMinFr.times(sigma2))

	f = open(directory+rootName+'_FitInfo.txt','w')
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        print >> f, ' # FIT INFO FOR: ', data.get('name')
        print >> f, ' # CHANNEL : Bs2JpsiPhi'
        print >> f, ' # Luminosity in pb : ',data.get('lumi').getVal()," +- ",data.get('lumi').getErr()
	print >> f, ' # Entries before the cut: ',tree.GetEntries()
        print >> f, ' # MassVar: ', massVar
        print >> f, ' # cut :', cut
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        print >> f, ' # N_sig : ',fitBu.nsig.getVal(),' +- ',fitBu.nsig.getError()
        print >> f, ' # B mass mean : ',B_mass_mean.getVal(),' +- ',B_mass_mean.getErr()
        print >> f, ' # B mass reso : ',B_mass_sigma.getVal(),' +- ',B_mass_sigma.getErr()
        print >> f, ' # reso = sqrt(  f * sig1^2 + (1-f) * sig2^2 )'
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        f.close()

        # Print the file content in terminal:
        content =  open(directory+rootName+'_FitInfo.txt').read()
        print content
        return valAndErr(fitBs.nsig.getVal(),fitBu.nsig.getError())


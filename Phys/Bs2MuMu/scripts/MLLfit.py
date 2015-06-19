from ROOT import *
gROOT.SetBatch()
from valAndErr import *
#Mass model for the fit
#from SomeMassModels import B2JpsiModels as B
import os


def plotMassFit(w,dataName,massVar,opts={}):

        #Build and plot the Graph
        gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
        gStyle.SetFillStyle(4000)
        gStyle.SetLabelOffset(0.02)


        m = w.var(massVar)
        pdf = w.pdf('model')
        data = w.data(dataName)

        # Plot mass distribution
        fr = m.frame(RooFit.Title('B_{u}^{+} to J/#psiK^{+} mass fit on '+ opts.get('nTupleName')), RooFit.Bins(opts.get('binning',100)))
        if opts.get('channel',0) is 'Bs': fr = m.frame(RooFit.Title('B_{s} to J/#psi#phi mass fit on ' + opts.get('nTupleName')), RooFit.Bins(opts.get('binning',100)))

        data.plotOn(fr)
        pdf.plotOn(fr)

        # Plot residual OR pull distribution
        # Has to be here, after plotting pdf and data
        # hpull = fr.pullHist()
        # h = fr.residHist() #Residual histogram
        h = fr.pullHist() #Pull histogram

        #Plot all the bkg components
        pdf.plotOn(fr,RooFit.Components('exp'),RooFit.LineStyle(kDashed),RooFit.LineColor(kGray))
        pdf.plotOn(fr,RooFit.Components('pi_CB'),RooFit.LineStyle(kDashed),RooFit.LineColor(kMagenta))
        pdf.plotOn(fr,RooFit.Components('bkg'),RooFit.LineStyle(kDashed),RooFit.LineColor(kGreen))
        pdf.plotOn(fr,RooFit.Components('sig'),RooFit.LineStyle(kDashed),RooFit.LineColor(kRed))

        param = opts.get('param',False) #Draw parameters to the right hand side?
        if param:
            pdf.paramOn(fr,RooFit.Layout(0.67,1.,0.97),RooFit.LineColor(4000))
            #pdf.paramOn(fr,RooFit.Layout(0.67,1.,0.9),RooFit.LineColor(4000), RooFit.ShowConstants(kTRUE))
            fr.getAttText().SetTextSize(0.03)


        fr_h = m.frame(RooFit.Title(' '))
        fr_h.SetLineColor(1)
        fr_h.SetFillColor(2)
        fr_h.addPlotable(h,'E3')

        #Draw canvas
        canv = TCanvas('MassFit','MassFit',1000, 600)
        canv.Divide(1,2)

        canv.cd(1)
        if opts.get('log',0): gPad.SetLogy()

        gPad.SetPad(0.,0.25,1,1)
        gPad.SetBottomMargin(0.022)

        if param:
            gPad.SetLeftMargin(0.15)
            gPad.SetRightMargin(0.35)

        fr.GetYaxis().SetTitleOffset(0.8)
       #fr.GetYaxis().SetTitleSize(0.15)
        fr.GetXaxis().SetTitleSize(0)
        fr.GetXaxis().SetLabelSize(0)
        fr.Draw()

        canv.cd(2)
        gPad.SetPad(0.,0.,1,0.25)
        gPad.SetTopMargin(0.035)
        if param:
            gPad.SetLeftMargin(0.15)
            gPad.SetRightMargin(0.35)
        gPad.SetBottomMargin(0.35)
        fr_h.GetYaxis().SetTitleOffset(0.28)
        #fr_h.GetYaxis().SetTitle('Residuals')
        fr_h.GetYaxis().SetTitle('Pull')
        fr_h.GetYaxis().SetTitleSize(0.2)
        fr_h.GetYaxis().SetLabelSize(0.15)
        fr_h.GetYaxis().SetNdivisions(5)

        fr_h.GetXaxis().SetTitleOffset(0.7)
        fr_h.GetXaxis().SetTitleSize(0.2)
        fr_h.GetXaxis().SetLabelSize(0.1)

        fr_h.Draw('hist')

        directory = opts.get('directory','')+'Plots/'
        if not os.path.exists(directory):
                os.makedirs(directory)
        canv.SaveAs(directory+opts.get('plotName','MassFit')+'_param_'+str(param)+'.ps')
        canv.SaveAs(directory+opts.get('plotName','MassFit')+'_param_'+str(param)+'.root')

        w.Print()
        print '  THE MODEL:'
        pdf.Print()

        return fr

def fitBu2JpsiKplus(data, massVar, cutName, cut, log = True, dirName = False, param = False):
        print ' o) Perform the mass fit on Bu2JpsiKplus... \n '

        tree = data.get('tree')
        print '    The tree I am fitting:'
        entries = tree.GetEntries()
        print '    Entries: ',entries

        print ' o) Use the cutsstring...'
        #Add fiducial cuts
        #cuts = cs.minimalNormBu_lnf
        print cut

        #In SomeMassModels:
        #f = TFile("borrame_ho.root","recreate")
        #t = tree.CopyTree(cuts)

        f = TFile("temporaryData_"+data.get('name')+".root","recreate")
        tree_JK_cut = tree
        if len(cut)>0: tree_JK_cut = tree.CopyTree(cut)
        entries = tree_JK_cut.GetEntries()
        print 'Tree has after cuts: '+str(entries)
        #raw_input('Continue?')

        # ------------------------------------- #
        # Build a model for Bu2JpsiKplus
        # ------------------------------------- #
        print ' o) Define the mass variable:'
        Bu_pdg = 5279.17 #MeV/c^2
        mass = RooRealVar(massVar,'J/#psi constrained B^{+}_{u} mass',Bu_pdg-100.,Bu_pdg+100.,'MeV/c^{2}')
        obs = RooArgList(mass)

        print ' o) Create a RooDataSet:'
        dataName = 'data_Jpsi'
        dataSet= RooDataSet(dataName,'Dataset with Bu2JpsiKplus',tree_JK_cut,RooArgSet(obs))
        print dataSet
        print ' DataSet has: ' + str(dataSet.numEntries())

        print ' o) Create JpsiK workspace...'
        w= RooWorkspace('w')
        getattr(w,'import')(obs)
        getattr(w,'import')(dataSet)
        w.Print()

        # ---------------------------- #
        # The signal model definition:
        # ---------------------------- #
        print ' o)Build the mass signal model (Double CrystalBall):'
        w.factory('m_mean[5278,5230,5300]')
        #w.factory("CBShape::cb_1("+massVar+",m_mean,m_sigma[10.,0.,200.],alpha_left[1, 0,10],n_1[7,0,25])") # CB with tail on the left
        w.factory("CBShape::cb_1("+massVar+",m_mean,m_sigma[10.,0.,200.],alpha_left[4, 3,5],n_1[20,7,50])") # 2011_S20r1_July setings

        #For sigma_2 = sigma + sigma_del
        w.factory("m_sigma_del[5.,0.,100.]")
        m_sigma_2 = RooFormulaVar('m_sigma_2','@0+@1',RooArgList(w.var('m_sigma'),w.var('m_sigma_del')))
        getattr(w,'import')(m_sigma_2)
        #w.factory("CBShape::cb_2("+massVar+",m_mean,m_sigma_2,alpha_right[1.6, 0,100],n_2[9,0,50])") #CB with tail on the right
        #w.factory("CBShape::cb_2("+massVar+",m_mean,m_sigma_2,alpha_right[10, 0,100],n_2[25,0,50])") #CB with tail on the right
        #w.factory("CBShape::cb_2("+massVar+",m_mean,m_sigma_2,alpha_right[-1, -10,0],n_2[7,0,35])") #CB with tail on the right
        #w.factory("CBShape::cb_2("+massVar+",m_mean,m_sigma_2,alpha_right[-6, -10,-3],n_2[20,0,50])") #CB with tail on the right, but do not let to extend under the misID peak, tweaking for 2011_s20r1_July
        w.factory("CBShape::cb_2("+massVar+",m_mean,m_sigma_2,alpha_right[-6, -8,-6],n_2[16,13,16])") #CB with tail on the right, but do not let to extend under the misID peak, tweaking for 2011_s20r1_July

        #Sum 2 CB's
        w.factory("SUM::sig( f_cb1[0.4,0.,1.]*cb_1, cb_2 )")


        #Try double gaussian
        #w.factory("Gaussian::g_1("+massVar+",m_mean,m_sigma)")
        #w.factory("Gaussian::g_2("+massVar+",m_mean,m_sigma_2)")
        #w.factory("SUM::sig( f_g1[0.5,0.,1.]*g_1, g_2 )")

        # -------------------------------- #
        # The background model definition:
        # -------------------------------- #
        print ' o) Build the mass background model: Exp + CB for pion misID peak'
        w.factory("Exponential::exp("+massVar+",m_bkg_slope[-0.0015,-10,0])")

        #Letting the m_mean be fitted in peak+[+45..+55MeV] range
        #Decreases the signal yield and reduces the mass resolution (error grows though on reso)! <<<<-WRONG! FIX IT as it behaves funny otherwise.
        #massMean = w.var('m_mean').getVal()+44. S17 sucks a bit
        #massMean = Bu_pdg+43.
        #massMean = 5328 # Taken from the 2012 S20 fit (most stat) #the Strip19abc does not function without fixing the mean
        massMean = 5324 # Taken from the 2011 S20r1 fit

        # For the reast of the data, leave the mean floating
        w.factory("CBShape::pi_CB("+massVar+",pi_mean["+str(massMean)+","+str(massMean-5)+","+str(massMean+10)+"],pi_sigma[13.,9.,23.],pi_alpha[-0.5,-0.6,-0.1],pi_n[3.,2.5,5.5])") # tweak the CB tail for 2011 S20r1, not used yet
        #w.factory("CBShape::pi_CB("+massVar+",pi_mean["+str(massMean)+","+str(massMean-5)+","+str(massMean+10)+"],pi_sigma[13.,9.,23.],pi_alpha[-0.5,-0.6,-0.3],pi_n[3.,2.5,5.5])") #Nsig err = 319
        #w.factory("CBShape::pi_CB("+massVar+",pi_mean["+str(massMean)+","+str(massMean-10)+","+str(massMean+15)+"],pi_sigma[13.,9.,23.],pi_alpha[-0.5,-0.6,-0.3],pi_n[3.,2.5,5.5])") # Freed boundary for the left massMean for the 2012 S20 TIS fit

        #Only fix for the Strip19abc!!
        #w.factory("CBShape::pi_CB("+massVar+",pi_mean["+str(massMean)+"],pi_sigma[13.,9.,23.],pi_alpha[-0.5,-0.6,-0.3],pi_n[3.,2.5,5.5])") #Nsig err = 319   #With FidCuts WITHOUT constraints

        #w.factory("SUM::bkg( f_pi[0.1,0.01,0.4]*pi_CB, exp)")
        w.factory("SUM::bkg( f_pi[0.06,0.01,0.4]*pi_CB, exp)")

        #Fix the mean of the misID CB on the right for the TIS, TISTOS and TOS fits to the TRIG value
        if 'TOS' in cut or 'TIS' in cut:
                meanVal = 0.
                if data.get('name') is '2011_Strip17': meanVal = 5332.0 #from the TRIG fit
                if data.get('name') is '2011_Strip20r1_excl5': meanVal = 5324.2 #at right bound
                if data.get('name') is '2011_Strip20r1': meanVal = 5324.2 #at right bound
                if data.get('name') is '2012_Strip19abc': meanVal = 5328.8 # fixed also for TRIG from 2012 S20
                if data.get('name') is '2012_Strip20': meanVal = 5328.8
                if meanVal is 0: raw_input('CB mean not set! Abort..')
                w.var('pi_mean').setVal(meanVal)
                #w.var('pi_mean').setConstant(True)


        # -------------------------------- #
        # Put the model all together:
        # -------------------------------- #
        print ' o) Combine and the mass model...'
        w.factory("SUM::model( Nsig[1000,0.,100000000]*sig, Nbkg[1000,0.,1000000000]*bkg )")

        # -------------------------------- #
        # FIT THE MODEL:
        # -------------------------------- #
        print ' o) FIT:'
        pdf = w.pdf('model')
        pdf.fitTo(w.data(dataName), RooFit.NumCPU(8))
        print ' FIT has converged!'

        print ' o) Save the plot in root file, and ps...'
        rootName = data.get('name')+'_'+massVar+'_Fit_'+cutName

        directory = 'MassFitResults/Bu2JpsiKplus/'
        if dirName: directory = 'MassFitResults/'+str(dirName)
        plotName = massVar+'_Fit_'+cutName+'_LogScale_'+str(log)
        frame_log = plotMassFit(w,dataName,massVar,{'log':True, 'directory':directory,'plotName':rootName+plotName, 'channel':'Bu', 'nTupleName':data.get('name'),'param':True})
        frame = plotMassFit(w,dataName,massVar,{'log':False, 'directory':directory,'plotName':rootName+plotName, 'channel':'Bu', 'nTupleName':data.get('name'),'param':False})

        print ' o) Save the fitted parameters to a file..'
        pdf.getParameters(w.data(dataName)).writeToFile(directory+rootName+'_PARAMETERS.txt')

        print ' o) Save the fit info to a file..'

        #Calculate the B mass resolution (weighted average of the double gaussian sigmas)
        fr = valAndErr(w.var('f_cb1').getVal(), w.var('f_cb1').getError())
        oneMinFr = valAndErr(1.,0.).minus(fr)
        B_mass_mean = valAndErr(w.var('m_mean').getVal(), w.var('m_mean').getError())
        sigma1 = valAndErr(w.var('m_sigma').getVal(), w.var('m_sigma').getError())
        sigma_del = valAndErr(w.var('m_sigma_del').getVal(), w.var('m_sigma_del').getError())
        sigma2 = sigma1.plus(sigma_del)

        # res = sqrt(  f * sig1^2 + (1-f)*sig2^2 ) CORRECT!!!
	B_mass_sigma =  ( (fr.times(sigma1.times(sigma1))).plus(oneMinFr.times(sigma2.times(sigma2)))  ).sqrt()

	f = open(directory+rootName+'_FitInfo.txt','w')
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        print >> f, ' # FIT INFO FOR: ', data.get('name')
        print >> f, ' # CHANNEL : Bu2JpsiKplus'
        print >> f, ' # Luminosity in pb : ',data.get('lumi').getVal()," +- ",data.get('lumi').getErr()
        print >> f, ' # Entries before the cut: ',tree.GetEntries()
        print >> f, ' # Entries after the cut: ', w.data(dataName).numEntries()
        print >> f, ' # MassVar: ', massVar
        print >> f, ' # cut :', cut
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        print >> f, ' # N_sig : ',w.var('Nsig').getVal(),' +- ', w.var('Nsig').getError()
        print >> f, ' # B mass mean : ',B_mass_mean.getVal(),' +- ',B_mass_mean.getErr()
        print >> f, ' # B mass reso : ',B_mass_sigma.getVal(),' +- ',B_mass_sigma.getErr()
        print >> f, ' # reso = sqrt(  f * sig1^2 + (1-f) * sig2^2 )'
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        f.close()

        # Print the file content in terminal:
        content =  open(directory+rootName+'_FitInfo.txt').read()
        print content
        return valAndErr(w.var('Nsig').getVal(),w.var('Nsig').getError())


def fitBs2JpsiPhi(data, massVar, cutName, cut, log = True, dirName = False, param = False):
        print ' o) Perform the mass fit on Bs2JpsiPhi... \n '

        tree = data.get('tree')
        print '    The tree I am fitting:'
        entries = tree.GetEntries()
        print '    Entries: ',entries

        print ' o) Use the cutsstring...'
        #Add fiducial cuts
        #cuts = cs.minimalNormBu_lnf
        print cut
        tree_cut= tree.CopyTree(cut)
        entries = tree_cut.GetEntries()
        print 'Tree has after cuts: '+str(entries)
        #raw_input('Continue?')

        # ------------------------------------- #
        # Build a model for Bs2JpsiPhi
        # ------------------------------------- #
        print ' o) Define the mass variable:'
        Bs_pdg = 5366.3 #MeV/c^2
        mass = RooRealVar(massVar,'J/#psi constrained B^{0}_{s} mass',Bs_pdg-100.,Bs_pdg+100.,'MeV/c^{2}')
        obs = RooArgList(mass)

        print ' o) Create a RooDataSet:'
        dataName = 'data_Jpsi'
        dataSet= RooDataSet(dataName,'Dataset with Bs2JpsiPhi',tree_cut,RooArgSet(obs))
        print dataSet
        print ' DataSet has: ' + str(dataSet.numEntries())

        print ' o) Create JpsiK workspace...'
        w= RooWorkspace('w')
        getattr(w,'import')(obs)
        getattr(w,'import')(dataSet)
        w.Print()

        # ---------------------------- #
        # The signal model definition:
        # ---------------------------- #
        print ' o)Build the mass signal model (Double CrystalBall):'
        w.factory('m_mean[5360,0,10000]')
        #w.factory("CBShape::cb_1("+massVar+",m_mean,m_sigma[10.,0.,200.],alpha_left[-60, -100,0],n_1[1,0,100])") # CB with tail on the left
        w.factory("CBShape::cb_1("+massVar+",m_mean,m_sigma[10.,0.,200.],alpha_left[1, 0,100],n_1[1,0,30])") # CB with tail on the left
        #For sigma_2 = sigma + sigma_del
        w.factory("m_sigma_del[3.,1.,100.]")
        m_sigma_2 = RooFormulaVar('m_sigma_2','@0+@1',RooArgList(w.var('m_sigma'),w.var('m_sigma_del')))
        getattr(w,'import')(m_sigma_2)

        #Sum 2 CB's
        #w.factory("CBShape::cb_2("+massVar+",m_mean,m_sigma_2,alpha_right[10, 0,100],n_2[7,0,100])") #CB with tail on the right
        #w.factory("SUM::sig( f_cb1[0.5,0.,1.]*cb_1, cb_2 )")

        #Sum CB and a Gauss
        w.factory("Gaussian::g_2("+massVar+",m_mean,m_sigma_2)")
        w.factory("SUM::sig( f_cb1[0.8]*cb_1, g_2 )")

        # -------------------------------- #
        # The background model definition:
        # -------------------------------- #
        print ' o) Build the mass background model: Exp + CB for pion misID peak'

        w.factory("Exponential::exp("+massVar+",m_bkg_slope[-0.001,-10,0])")
        w.factory("CBShape::pi_CB("+massVar+",pi_mean["+str(w.var('m_mean').getVal()+50.)+",5400,5425],pi_sigma[10.,10.,23.],pi_alpha[-0.5,-0.6,-0.3],pi_n[3.,2.,10])") # the best

        w.factory("SUM::bkg( f_pi[0.01,0.01,0.3]*pi_CB, exp)")

        # -------------------------------- #
        # Put the model all together:
        # -------------------------------- #
        print ' o) Combine and the mass model...'
        w.factory("SUM::model( Nsig[1000,0.,100000000]*sig, Nbkg[1000,0.,1000000000]*bkg )")

        #Fix the mean of the misID CB on the right for the TIS, TISTOS and TOS fits to the TRIG value
        if 'TOS' in cut or 'TIS' in cut:
                meanVal = 0.
                if data.get('name') is '2011_Strip17': meanVal = 5413.4 #from the TRIG fit
                if data.get('name') is '2011_Strip20r1': meanVal = 5414.0
                if data.get('name') is '2012_Strip19abc': meanVal = 5413.1
                if data.get('name') is '2012_Strip20': meanVal = 5411.7

                if meanVal is 0: raw_input('CB mean not set! Abort..')

                w.var('pi_mean').setVal(meanVal)
                #w.var('pi_mean').setConstant(True)

        # -------------------------------- #
        # FIT THE MODEL:
        # -------------------------------- #
        print ' o) FIT:'
        pdf = w.pdf('model')
        pdf.fitTo(w.data(dataName), RooFit.NumCPU(8))
        print ' FIT has converged!'

        print ' o) Save the plot in root file, and ps...'
        rootName = data.get('name')+'_'+massVar+'_Fit_'+cutName

        directory = 'MassFitResults/Bs2JpsiPhi/'
        if dirName: directory = 'MassFitResults/'+str(dirName)
        plotName = massVar+'_Fit_'+cutName+'_LogScale_'+str(log)
        frame_log = plotMassFit(w,dataName,massVar,{'log':True, 'directory':directory,'plotName':rootName+plotName, 'channel':'Bs', 'nTupleName':data.get('name'),'param':True})
        frame = plotMassFit(w,dataName,massVar,{'log':False, 'directory':directory,'plotName':rootName+plotName, 'channel':'Bs', 'nTupleName':data.get('name'),'param':False})


        print ' o) Save the fitted parameters to a file..'
        pdf.getParameters(w.data(dataName)).writeToFile(directory+rootName+'_PARAMETERS.txt')

        print ' o) Save the fit info to a file..'

        #Calculate the B mass resolution (weighted average of the double gaussian sigmas)
        fr = valAndErr(w.var('f_cb1').getVal(), w.var('f_cb1').getError())
        oneMinFr = valAndErr(1.,0.).minus(fr)
        B_mass_mean = valAndErr(w.var('m_mean').getVal(), w.var('m_mean').getError())
        sigma1 = valAndErr(w.var('m_sigma').getVal(), w.var('m_sigma').getError())
        sigma_del = valAndErr(w.var('m_sigma_del').getVal(), w.var('m_sigma_del').getError())
        sigma2 = sigma1.plus(sigma_del)

        # res = sqrt(  f * sig1^2 + (1-f)*sig2^2 ) CORRECT!!!
	B_mass_sigma =  ( (fr.times(sigma1.times(sigma1))).plus(oneMinFr.times(sigma2.times(sigma2)))  ).sqrt()

        f = open(directory+rootName+'_FitInfo.txt','w')
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        print >> f, ' # FIT INFO FOR: ', data.get('name')
        print >> f, ' # CHANNEL : Bs2JpsiPhi'
        print >> f, ' # Luminosity in pb : ',data.get('lumi').getVal()," +- ",data.get('lumi').getErr()
	print >> f, ' # Entries before the cut: ',tree.GetEntries()
	print >> f, ' # Entries after the cut: ', w.data(dataName).numEntries()
        print >> f, ' # MassVar: ', massVar
        print >> f, ' # cut :', cut
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        print >> f, ' # N_sig : ',w.var('Nsig').getVal(),' +- ', w.var('Nsig').getError()
        print >> f, ' # B mass mean : ',B_mass_mean.getVal(),' +- ',B_mass_mean.getErr()
        print >> f, ' # B mass reso : ',B_mass_sigma.getVal(),' +- ',B_mass_sigma.getErr()
        print >> f, ' # reso = sqrt(  f * sig1^2 + (1-f) * sig2^2 )'
        print >> f, ' #--------------------------------------------------------------------------------------------------#	'
        f.close()


        # Print the file content in terminal:
        content =  open(directory+rootName+'_FitInfo.txt').read()
        print content
        return valAndErr(w.var('Nsig').getVal(),w.var('Nsig').getError())




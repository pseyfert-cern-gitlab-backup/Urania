from ROOT import *
from array import *
from valAndErr import *
import os
from plotYields import *
from getTrigEff import *

#For the screen turn off the whistles
gROOT.SetBatch(True)

def plotFsFd2013(y_range = [0,0.16]):
        """ Get the yields from the result files,correct for the trigger efficiency and plot them """

        #For the files:
        directory = 'MassFitResults/'
        #channel_Bu =  'Bu2JpsiKplus/'
        channel_Bu =  'JpsiTrig'

        tr_level = 'JpsiTrig__TRIG' #Identifier for the JpsiTrigger required fit result files
        lumi_unc_comp = 0.005 #An uncorrelated uncertainty for comparing the yields to eachother

        mass_var_Bu = 'Bplus_JCMass'
        B_name_Bu = 'Bplus'
        #channel_Bs =  'Bs2JpsiPhi/'
        channel_Bs =  'JpsiTrig'
        mass_var_Bs = 'B_s0_JCMass'
        B_name_Bs = 'B_s0_'

       # y_range = [-1,1] # y range of the plot
        y_title = 'N(B_{s}#rightarrowJ/#psi#phi) / N(B^{+}#rightarrowJ/#psiK^{+})'


        #-----------------------------------------#
        #-- Define the efficiencie corrections  --#
        #-----------------------------------------#
        # No need, as the triggers are the same for both Bu and Bs channel

        # Efficiency corrections for BuJpsiKplus
        Bu_eff_cor_2011_Strip20r1 = valAndErr(1,0)
        Bu_eff_cor_2011_Strip17 = valAndErr(1,0)
        Bu_eff_cor_2012_Strip19 = valAndErr(1,0)
        Bu_eff_cor_2012_Strip20 = valAndErr(1,0)

        # Efficiency corrections for BsJpsiPhi
        Bs_eff_cor_2011_Strip20r1 = valAndErr(1,0)
        Bs_eff_cor_2011_Strip17 = valAndErr(1,0)
        Bs_eff_cor_2012_Strip19 = valAndErr(1,0)
        Bs_eff_cor_2012_Strip20 = valAndErr(1,0)

        #-----------------------------------------#
        #-- Define the points to be read in-------#
        #-----------------------------------------#
        # Array of dictionaries containing all the
        # information about the entries (points/lines)
        entries_fsfd = []
        entries_Bu = []
        entries_Bs = []

        #plotOpts = {'yTitle':y_title, 'yRange':y_range}

        # Define the colors   NB only applies for line, points have all black color..
        color_2011 = 2 #red
        color_2011_S17 = 3 #green
        color_2012 = 4 #
        color_2012_S19 = 5 #

        # Add lines for BuJpsiKplus

        # 2011
        line  = {'type':'line' , 'nTupleName':'2011_Strip17_'+B_name_Bu, 'lumiUnc':lumi_unc_comp, 'eff_cor':Bu_eff_cor_2011_Strip17, 'color':color_2011_S17}
        entries_Bu.append(line)
        line  = {'type':'line' , 'nTupleName':'2011_Strip20r1_'+B_name_Bu, 'lumiUnc':lumi_unc_comp, 'eff_cor':Bu_eff_cor_2011_Strip20r1, 'color':color_2011}
        entries_Bu.append(line)
        # 2012
        line  = {'type':'line' , 'nTupleName':'2012_Strip19abc_'+B_name_Bu, 'lumiUnc':lumi_unc_comp, 'eff_cor':Bu_eff_cor_2012_Strip19, 'color':color_2012_S19}
        entries_Bu.append(line)
        line  = {'type':'line' , 'nTupleName':'2012_Strip20_'+B_name_Bu, 'lumiUnc':lumi_unc_comp, 'eff_cor':Bu_eff_cor_2012_Strip20, 'color':color_2012}
        entries_Bu.append(line)

        # Find the file names, read in the yields and write them to the dictionary
        entries_Bu = addFiles(directory, channel_Bu, entries_Bu, tr_level, mass_var_Bu) #Add 'file' to the dictionary with the filename
        entries_Bu = readVars(directory, channel_Bu, entries_Bu) #Add 'n_sig' etc..


        # Add lines for BsJpsiPhi
        # 2011
        line  = {'type':'line' , 'nTupleName':'2011_Strip17_'+B_name_Bs, 'lumiUnc':lumi_unc_comp, 'eff_cor':Bs_eff_cor_2011_Strip17, 'color':color_2011_S17}
        entries_Bs.append(line)
        line  = {'type':'line' , 'nTupleName':'2011_Strip20r1_'+B_name_Bs, 'lumiUnc':lumi_unc_comp, 'eff_cor':Bs_eff_cor_2011_Strip20r1, 'color':color_2011}
        entries_Bs.append(line)
        # 2012
        line  = {'type':'line' , 'nTupleName':'2012_Strip19abc_'+B_name_Bs, 'lumiUnc':lumi_unc_comp, 'eff_cor':Bs_eff_cor_2012_Strip19, 'color':color_2012_S19}
        entries_Bs.append(line)
        line  = {'type':'line' , 'nTupleName':'2012_Strip20_'+B_name_Bs, 'lumiUnc':lumi_unc_comp, 'eff_cor':Bs_eff_cor_2012_Strip20, 'color':color_2012}
        entries_Bs.append(line)

        # Find the file names, read in the yields and write them to the dictionary
        entries_Bs = addFiles(directory, channel_Bs, entries_Bs, tr_level, mass_var_Bs) #Add 'file'
        entries_Bs = readVars(directory, channel_Bs, entries_Bs) #Add 'n_sig' etc..


        #------------------------#
        # Calculate the fs/fd    #
        #------------------------#

        entries_fsfd = entries_Bu  #Does not matter which one you use for template

        for i,e_bu in enumerate(entries_Bu):
                print ' o) Calculating fsfd:'
                print '    nTuple_Bu' , e_bu.get('nTupleName',0)
                print '    nTuple_Bs' , entries_Bs[i].get('nTupleName',1)

                #fd = e_bu.get('n_sig_raw',0) #both are valAndErr obj
                #fs = entries_Bs[i].get('n_sig_raw',0)

                # Yields corrected with the eff_cor
                fd = e_bu.get('n_sig_cor',0) #both are valAndErr obj
                fs = entries_Bs[i].get('n_sig_cor',0)

                fsfd = fs.over(fd)
                entries_fsfd[i]['fsfd'] = fsfd
                print '     n_sig Bs = %i (%i)' % (fs.getVal(),fs.getErr())
                print '     n_sig Bu = %i (%i)' % (fd.getVal(),fd.getErr())
                print '     fsfd = %f (%f)' % (fsfd.getVal(),fsfd.getErr())

                #Remove the Bu or Bs from the name
                split_name =  e_bu.get('nTupleName').split('_')
                entries_fsfd[i]['nTupleName'] = split_name[0] +'_'+split_name[1]+'_'

                #Change from 'line' to 'point'
                entries_fsfd[i]['type'] = 'point'


        # Plot the fsfd in the entries_fsfd:
        plotVarInEntries('fsfd', entries_fsfd , {'yTitle':y_title, 'yRange':y_range, 'channel':'JpsiTrigger for both, no eff. cor.', 'plotName':'fsfd2013_raw'})

        print 'Efficiencie corrections BuJpsiKplus:'
        print ' 2011 Strip17 :', Bu_eff_cor_2011_Strip17.getVal(), '+-', Bu_eff_cor_2011_Strip17.getErr()
        print ' 2011 Strip20r1 :', Bu_eff_cor_2011_Strip20r1.getVal(), '+-', Bu_eff_cor_2011_Strip20r1.getErr()
        print ' 2012 Strip19abc :', Bu_eff_cor_2012_Strip19.getVal(), '+-', Bu_eff_cor_2012_Strip19.getErr()
        print ' 2012 Strip20 :', Bu_eff_cor_2012_Strip20.getVal(), '+-', Bu_eff_cor_2012_Strip20.getErr()
        print 'Efficiencie corrections BsJpsiPhi:'
        print ' 2011 Strip17 :', Bs_eff_cor_2011_Strip17.getVal(), '+-', Bs_eff_cor_2011_Strip17.getErr()
        print ' 2011 Strip20r1 :', Bs_eff_cor_2011_Strip20r1.getVal(), '+-', Bs_eff_cor_2011_Strip20r1.getErr()
        print ' 2012 Strip19abc :', Bs_eff_cor_2012_Strip19.getVal(), '+-', Bs_eff_cor_2012_Strip19.getErr()
        print ' 2012 Strip20 :', Bs_eff_cor_2012_Strip20.getVal(), '+-', Bs_eff_cor_2012_Strip20.getErr()

        print 'fsfd for the samples:'
        for e in entries_fsfd:
                if e.get('type') is 'line':
                        print ' For: ',e.get('nTupleName'), ' the fsfd:',e.get('fsfd').getVal(), ' +- ', e.get('fsfd').getErr()



from ROOT import *
from array import *
from valAndErr import *
import os
from plotYields import *
from getTrigEff import *

#For the screen turn off the whistles
gROOT.SetBatch(True)

def plotYields2013(ch = 'Bu'):
        """ Get the yields from the result files,correct for the trigger efficiency and plot them """

        #For the files:
        directory = 'MassFitResults/'
        channel =  'Bu2JpsiKplus/'
        mass_var = 'Bplus_JCMass'
        B_name = 'Bplus'
        y_range = [320,520]

        if ch is 'Bs' :
                channel =  'Bs2JpsiPhi/'
                mass_var = 'B_s0_JCMass'
                #B_name = 'B_s0_'
                B_name = 'B_s0'
                y_range = [20,37]

        tr_level = 'TRIG' #For the plot

        #-----------------------------------------#
        #-- Get the trigger efficiencies  --------#
        #-----------------------------------------#
        #def getTrigEff(nTupleName, directory, channel, massVar):

        # Reprocessed 2012 data
        # add _Bplus to separate from the _B_ files
        trig_eff_2011_Strip17 = getTrigEff('2011_Strip17_'+B_name,directory, channel, mass_var).getEff()
        trig_eff_2011_Strip20r1 = getTrigEff('2011_Strip20r1_'+B_name,directory, channel, mass_var).getEff()
        #trig_eff_2011_Strip20r1 = getTrigEff('2011_Strip20r1_excl5_'+B_name,directory, channel, mass_var).getEff()

        trig_eff_2012_Strip19 = getTrigEff('2012_Strip19abc_'+B_name,directory, channel, mass_var).getEff()
        trig_eff_2012_Strip20 = getTrigEff('2012_Strip20_'+B_name,directory, channel, mass_var).getEff()

        #-----------------------------------------#
        #-- Define the points to be read in-------#
        #-----------------------------------------#
        entries = []    # Array of dictionaries containing all the
                        # information about the entries (points/lines)
        y_title = 'Trigger eff. corrected yields / pb^{-1}'
        plotOpts = {'yTitle':y_title, 'yRange':y_range}

        lumi_unc_comp = 0.005 #An uncorrelated uncertainty for comparing the yields to eachother

        #Define the colors
        color_2011 = 2 #red
        color_2011_S17 = 3 #green
        color_2012 = 4 #
        color_2012_S19 = 5 #


        if ch in 'Bs':
            point = {'type':'point' , 'nTupleName':'2011_Strip20r1_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2011_Strip20r1}
            entries.append(point)

            point = {'type':'point' , 'nTupleName':'2012_Strip20_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20}
            entries.append(point)

        if ch in 'Bu':
            #Add points
            #2011
            point = {'type':'point' , 'nTupleName':'2011_Strip20r1_A_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2011_Strip20r1}
            entries.append(point)
            point = {'type':'point' , 'nTupleName':'2011_Strip20r1_B_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2011_Strip20r1}
            entries.append(point)
            point = {'type':'point', 'nTupleName':'2011_Strip20r1_C_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2011_Strip20r1}
            entries.append(point)
            point = {'type':'point', 'nTupleName':'2011_Strip20r1_D_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2011_Strip20r1}
            entries.append(point)


            #2012
            point = {'type':'point' , 'nTupleName':'2012_Strip20_MagDown_A_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20}
            entries.append(point)
            point = {'type':'point' , 'nTupleName':'2012_Strip20_MagDown_B_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20}
            entries.append(point)
            point = {'type':'point', 'nTupleName':'2012_Strip20_MagDown_C_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20}
            entries.append(point)
            point = {'type':'point', 'nTupleName':'2012_Strip20_MagDown_D_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20}
            entries.append(point)

            point = {'type':'point', 'nTupleName':'2012_Strip20_MagUp_A_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20}
            entries.append(point)
            point = {'type':'point', 'nTupleName':'2012_Strip20_MagUp_B_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20}
            entries.append(point)
            point = {'type':'point', 'nTupleName':'2012_Strip20_MagUp_C_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20}
            entries.append(point)
            point = {'type':'point', 'nTupleName':'2012_Strip20_MagUp_D_','lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20}
            entries.append(point)

        #Add lines
        #2011
        line  = {'type':'line' , 'nTupleName':'2011_Strip20r1_'+B_name, 'lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2011_Strip20r1, 'color':color_2011}
        entries.append(line)
        line  = {'type':'line' , 'nTupleName':'2011_Strip17_'+B_name, 'lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2011_Strip17, 'color':color_2011_S17}
        entries.append(line)

        #2012
        line  = {'type':'line' , 'nTupleName':'2012_Strip20_'+B_name, 'lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20, 'color':color_2012}
        entries.append(line)
        line  = {'type':'line' , 'nTupleName':'2012_Strip19abc_'+B_name, 'lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip19, 'color':color_2012_S19}
        entries.append(line)
        #line  = {'type':'line' , 'nTupleName':'2012_Strip20_GoodITRuns', 'lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20, 'color':color_2012}
        #entries.append(line)
        #line  = {'type':'line' , 'nTupleName':'2012_Strip20_BadITRuns', 'lumiUnc':lumi_unc_comp, 'eff_cor':trig_eff_2012_Strip20, 'color':color_2012}
        #entries.append(line)

        #Get the entries from files and plot
        entries_with_files = addFiles(directory, channel, entries, tr_level, mass_var)
        entries_with_vars = readVars(directory, channel, entries)

        #plotVarInEntries('n_sig_raw', entries_with_vars , {'yTitle':' Raw signal yields per pb', 'yRange':[320,520], 'channel':channel, 'plotName':'BuJpsiKplus_YieldsPerPb_n_sig_raw_All2013'})
        plotVarInEntries('n_sig', entries_with_vars , {'yTitle':y_title, 'yRange':y_range, 'channel':channel, 'plotName':'BuJpsiKplus_YieldsPerPb_n_sig_corrected_All2013'})

        print 'Trigger efficiencies:'
        print ' 2011 Strip17 :', trig_eff_2011_Strip17.getVal(), '+-', trig_eff_2011_Strip17.getErr()
        print ' 2011 Strip20r1 :', trig_eff_2011_Strip20r1.getVal(), '+-', trig_eff_2011_Strip20r1.getErr()
        print ' 2012 Strip19abc :', trig_eff_2012_Strip19.getVal(), '+-', trig_eff_2012_Strip19.getErr()
        print ' 2012 Strip20 :', trig_eff_2012_Strip20.getVal(), '+-', trig_eff_2012_Strip20.getErr()
        #print ' 2012 Strip20 Excl5 :', trig_eff_2012_Strip20.getVal(), '+-', trig_eff_2012_Strip20.getErr()
        print ' Yields in numbers for lines:'
        yields = {}
        for e in entries_with_vars:
                if e.get('type') is 'line':
                        print ' For: ',e.get('nTupleName'), ' the n_sig:',e.get('n_sig').getVal(), ' +- ', e.get('n_sig').getErr()
                        yields[e.get('nTupleName')] = e.get('n_sig')

        #Calculate the change between the 1-2 adn 3-4 elements
        # order is new20111, old2011, new2012, old2012
        print ' Yields:', yields
        new = yields.get('2011_Strip20r1_'+B_name,0)
        old = yields.get('2011_Strip17_'+B_name,0)
        change_2011 = new.minus(old).over(old)

        new = yields.get('2012_Strip20_'+B_name)
        old = yields.get('2012_Strip19abc_'+B_name)
        change_2012 = new.minus(old).over(old)

        print ' THE CHANGE in YIELDS:'
        print ' ---------------------'
        print '  In 2011 change: %.4f +- %.4f' % (change_2011.getVal(),change_2011.getErr())
        print '  In 2012 change: %.4f +- %.4f' % (change_2012.getVal(),change_2012.getErr())
        print ' ---------------------'

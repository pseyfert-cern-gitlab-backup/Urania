from ROOT import *
from array import *
from valAndErr import *
import os
from plotYields import *
from getTrigEff import *

#For the screen turn off the whistles
gROOT.SetBatch(True)

def showTrigEff(ch = 'Bu'):
        """ Get the trigger efficiencies from the result files"""

        #For the files:
        directory = 'MassFitResults/'
        channel =  'Bu2JpsiKplus/' #means the sub_directory
        mass_var = 'Bplus_JCMass'
        B_name = 'Bplus'

        if ch is 'Bs' :
                channel =  'Bs2JpsiPhi/'
                mass_var = 'B_s0_JCMass'
                B_name = 'B_s0_'

        #-----------------------------------------#
        #-- Get the trigger efficiencies  --------#
        #-----------------------------------------#
        #def getTrigEff(nTupleName, directory, channel, massVar):

        # Reprocessed 2012 data
        # add _Bplus to separate from the _B_ files
        trig_ch = channel
        #trig_ch = 'Bu2JpsiKplus/'
        trig_eff_2011_Strip17 = getTrigEff('2011_Strip17_'+B_name,directory, trig_ch, mass_var).getEff()
        trig_eff_2011_Strip20r1 = getTrigEff('2011_Strip20r1_'+B_name,directory, trig_ch, mass_var).getEff()
        trig_eff_2012_Strip19 = getTrigEff('2012_Strip19abc_'+B_name,directory, trig_ch, mass_var).getEff()
        trig_eff_2012_Strip20 = getTrigEff('2012_Strip20_'+B_name,directory, trig_ch, mass_var).getEff()

        tis_eff_2011_Strip17 = getTrigEff('2011_Strip17_'+B_name,directory, trig_ch, mass_var).getTisEff()
        tis_eff_2011_Strip20r1 = getTrigEff('2011_Strip20r1_'+B_name,directory, trig_ch, mass_var).getTisEff()
        tis_eff_2012_Strip19 = getTrigEff('2012_Strip19abc_'+B_name,directory, trig_ch, mass_var).getTisEff()
        tis_eff_2012_Strip20 = getTrigEff('2012_Strip20_'+B_name,directory, trig_ch, mass_var).getTisEff()


        #Trig eff

        #-----------------------------------------#
        #-- Print the efficiencies to terminal -------#
        #-----------------------------------------#

        print 'From yields in:', directory + channel
        print '  -------'
        print 'Trigger efficiencies:'
        print ' 2011 Strip17 :', trig_eff_2011_Strip17.getVal(), '+-', trig_eff_2011_Strip17.getErr()
        print ' 2011 Strip20r1 :', trig_eff_2011_Strip20r1.getVal(), '+-', trig_eff_2011_Strip20r1.getErr()
        print ' 2012 Strip19abc :', trig_eff_2012_Strip19.getVal(), '+-', trig_eff_2012_Strip19.getErr()
        print ' 2012 Strip20 :', trig_eff_2012_Strip20.getVal(), '+-', trig_eff_2012_Strip20.getErr()
        print '  -------'
        print 'Tis efficiencies:'
        print ' 2011 Strip17 :', tis_eff_2011_Strip17.getVal(), '+-', tis_eff_2011_Strip17.getErr()
        print ' 2011 Strip20r1 :', tis_eff_2011_Strip20r1.getVal(), '+-', tis_eff_2011_Strip20r1.getErr()
        print ' 2012 Strip19abc :', tis_eff_2012_Strip19.getVal(), '+-', tis_eff_2012_Strip19.getErr()
        print ' 2012 Strip20 :', tis_eff_2012_Strip20.getVal(), '+-', tis_eff_2012_Strip20.getErr()
        print '  -------'



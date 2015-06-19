#---------------------------------------------------
# script to write the table with the parameters 
# for the toys
#
#  Summer 13 analysis
#  2011+2012 dataset
#  with BDT12
#  
#---------------------------------------------------

from errors import *
import alphaparam_autumn13 as alpha_comb
import alphaparam_summer13_2011 as alpha11
import alphaparam_spring13_2012 as alpha12
from BRparams import *
from BDTparam_summer13 import *
from PeakingParam_autumn13 import *
from odict import ODict

print 'run toytable() to produce the table.'
print 'toytable()'

bins = range(1,9)

def setBkg(operator, name):
    ''' Sets given background values for toytable '''
    operator[name+'_comment']    = "\n## "+name+" parameters" 
    operator[name+'BR']    = val(eval(name+"BR"))
    operator[name+'BRErr'] = err(eval(name+"BR"))
    operator[name+'Eff']    = val(eval(name+"Eff"))
    operator[name+'EffErr'] = err(eval(name+"Eff"))
    variables = ['Frac','Mean','Sigma','Shc']
    for i in range(1,9):
        for v in variables : 
            operator[name+v+str(i)] =        val(eval(name+v+str(i)))
            operator[name+v+str(i)+'Err'] =  err(eval(name+v+str(i)))
        
    

def toytable():

    
    operator= ODict()

    operator['BR_comment'     ] = '\n## Branching Fraction'
    
    operator['Bsmumu_BR']    = val(alpha12.Bsmumu_BR)
    operator['Bsmumu_BRErr'] = err(alpha12.Bsmumu_BR)
    operator['Bdmumu_BR']    = val(alpha12.Bdmumu_BR)
    operator['Bdmumu_BRErr'] = err(alpha12.Bdmumu_BR)

    operator['Norm_comment'   ] = '\n## Normalisation'

    
    operator['BuJpsiK_BF']   = val(BuBR)
    operator['BuJpsiK_BFErr']= err(BuBR)
    operator['BdKpi_BF']     = val(BdBR)
    operator['BdKpi_BFErr']  = err(BdBR)

    operator['TimeAcceptanceCorrBs']     = val(alpha12.TimeAcceptanceCorrBs)
    operator['TimeAcceptanceCorrBsErr']  = err(alpha12.TimeAcceptanceCorrBs)
    operator['TimeAcceptanceCorrBd']     = val(alpha12.TimeAcceptanceCorrBd)
    operator['TimeAcceptanceCorrBdErr']  = err(alpha12.TimeAcceptanceCorrBd)
    
    operator['NormBu_noBF']     = val(alpha_comb.BuComb_mw_noBF)
    operator['NormBu_noBFErr']  = err(alpha_comb.BuComb_mw_noBF)
    operator['NormKPi_noBF']    = val(alpha_comb.BdComb_mw_noBF)
    operator['NormKPi_noBFErr'] = err(alpha_comb.BdComb_mw_noBF) 
    operator['NormBu_fullmass_noBF']     = val(alpha_comb.BuComb_fit_noBF)
    operator['NormBu_fullmass_noBFErr']  = err(alpha_comb.BuComb_fit_noBF)
    operator['NormKPi_fullmass_noBF']    = val(alpha_comb.BdComb_fit_noBF)
    operator['NormKPi_fullmass_noBFErr'] = err(alpha_comb.BdComb_fit_noBF)
    
    operator['fd_over_fs']     = val(alpha12.fdfs)
    operator['fd_over_fsErrP'] = err(alpha12.fdfs)
    operator['fd_over_fsErrN'] =-err(alpha12.fdfs)

    operator['BDTSig_comment' ] = '\n## BDT Signal'

    operator['BDT_sig1'] = val(ZFrac1)
    operator['BDT_sig2'] = val(ZFrac2)
    operator['BDT_sig3'] = val(ZFrac3)
    operator['BDT_sig4'] = val(ZFrac4)
    operator['BDT_sig5'] = val(ZFrac5)
    operator['BDT_sig6'] = val(ZFrac6)
    operator['BDT_sig7'] = val(ZFrac7)
    operator['BDT_sig8'] = val(ZFrac8)
    operator['BDT_sigErr1'] = err(ZFrac1)
    operator['BDT_sigErr2'] = err(ZFrac2)
    operator['BDT_sigErr3'] = err(ZFrac3)
    operator['BDT_sigErr4'] = err(ZFrac4)
    operator['BDT_sigErr5'] = err(ZFrac5)
    operator['BDT_sigErr6'] = err(ZFrac6)
    operator['BDT_sigErr7'] = err(ZFrac7)
    operator['BDT_sigErr8'] = err(ZFrac8)

    operator['TimeAcc1'] = val(TimeAcc1)
    operator['TimeAcc2'] = val(TimeAcc2)
    operator['TimeAcc3'] = val(TimeAcc3)
    operator['TimeAcc4'] = val(TimeAcc4)
    operator['TimeAcc5'] = val(TimeAcc5)
    operator['TimeAcc6'] = val(TimeAcc6)
    operator['TimeAcc7'] = val(TimeAcc7)
    operator['TimeAcc8'] = val(TimeAcc8)

    operator['Justine1'] = val(J_ave1)
    operator['Justine2'] = val(J_ave2)
    operator['Justine3'] = val(J_ave3)
    operator['Justine4'] = val(J_ave4)
    operator['Justine5'] = val(J_ave5)
    operator['Justine6'] = val(J_ave6)
    operator['Justine7'] = val(J_ave7)
    operator['Justine8'] = val(J_ave8)

    operator['MassSig_comment'] = '\n## Mass Signal'

    operator['MassMeanBs'] = val(MassMeanBs)
    operator['MassMeanBd'] = val(MassMeanBd)
    operator['MassResoBs'] = val(MassResoBs)
    operator['MassResoBd'] = val(MassResoBd)
    
    operator['CBTrans']   = val(CBTrans)
    operator['CBExpo']    = val(CBExpo)
    operator['CBTransErr']= err(CBTrans)
    operator['CBExpoErr'] = err(CBExpo)
    
    operator['MassMeanErrBs'] = err(MassMeanBs)
    operator['MassMeanErrBd'] = err(MassMeanBd)
    operator['MassResoErrBs'] = err(MassResoBs)
    operator['MassResoErrBd'] = err(MassResoBd)

    operator['BKG_comment'    ] = '\n## Background'
    
    operator['BkgMassk1'] = val(BkgMassk1)
    operator['BkgMassk2'] = val(BkgMassk2)
    operator['BkgMassk3'] = val(BkgMassk3)
    operator['BkgMassk4'] = val(BkgMassk4)
    operator['BkgMassk5'] = val(BkgMassk5)
    operator['BkgMassk6'] = val(BkgMassk6)
    operator['BkgMassk7'] = val(BkgMassk7)
    operator['BkgMassk8'] = val(BkgMassk8)
    operator['BkgMasskErrP1'] = errpos(BkgMassk1)
    operator['BkgMasskErrP2'] = errpos(BkgMassk2)
    operator['BkgMasskErrP3'] = errpos(BkgMassk3)
    operator['BkgMasskErrP4'] = errpos(BkgMassk4)
    operator['BkgMasskErrP5'] = errpos(BkgMassk5)
    operator['BkgMasskErrP6'] = errpos(BkgMassk6)
    operator['BkgMasskErrP7'] = errpos(BkgMassk7)
    operator['BkgMasskErrP8'] = errpos(BkgMassk8)
    operator['BkgMasskErrN1'] = -errneg(BkgMassk1)
    operator['BkgMasskErrN2'] = -errneg(BkgMassk2)
    operator['BkgMasskErrN3'] = -errneg(BkgMassk3)
    operator['BkgMasskErrN4'] = -errneg(BkgMassk4)
    operator['BkgMasskErrN5'] = -errneg(BkgMassk5)
    operator['BkgMasskErrN6'] = -errneg(BkgMassk6)
    operator['BkgMasskErrN7'] = -errneg(BkgMassk7)
    operator['BkgMasskErrN8'] = -errneg(BkgMassk8)
    operator['FracCombBin1'] = val(FracCombBin1)
    operator['FracCombBin2'] = val(FracCombBin2)
    operator['FracCombBin3'] = val(FracCombBin3)
    operator['FracCombBin4'] = val(FracCombBin4)
    operator['FracCombBin5'] = val(FracCombBin5)
    operator['FracCombBin6'] = val(FracCombBin6)
    operator['FracCombBin7'] = val(FracCombBin7)
    operator['FracCombBin8'] = val(FracCombBin8)
    operator['FracCombErrP1'] = errpos(FracCombBin1)
    operator['FracCombErrP2'] = errpos(FracCombBin2)
    operator['FracCombErrP3'] = errpos(FracCombBin3)
    operator['FracCombErrP4'] = errpos(FracCombBin4)
    operator['FracCombErrP5'] = errpos(FracCombBin5)
    operator['FracCombErrP6'] = errpos(FracCombBin6)
    operator['FracCombErrP7'] = errpos(FracCombBin7)
    operator['FracCombErrP8'] = errpos(FracCombBin8)
    operator['FracCombErrN1'] = -errneg(FracCombBin1)
    operator['FracCombErrN2'] = -errneg(FracCombBin2)
    operator['FracCombErrN3'] = -errneg(FracCombBin3)
    operator['FracCombErrN4'] = -errneg(FracCombBin4)
    operator['FracCombErrN5'] = -errneg(FracCombBin5)
    operator['FracCombErrN6'] = -errneg(FracCombBin6)
    operator['FracCombErrN7'] = -errneg(FracCombBin7)
    operator['FracCombErrN8'] = -errneg(FracCombBin8)

    

    operator['SbGL1'] = SbGL1
    operator['SbGL2'] = SbGL2
    operator['SbGL3'] = SbGL3
    operator['SbGL4'] = SbGL4
    operator['SbGL5'] = SbGL5
    operator['SbGL6'] = SbGL6
    operator['SbGL7'] = SbGL7
    operator['SbGL8'] = SbGL8
    operator['GL1MassSb1'] = GL1MassSb1 
    operator['GL1MassSb2'] = GL1MassSb2 
    operator['GL1MassSb3'] = GL1MassSb3 
    operator['GL1MassSb4'] = GL1MassSb4 
    operator['GL2MassSb1'] = GL2MassSb1 
    operator['GL2MassSb2'] = GL2MassSb2 
    operator['GL2MassSb3'] = GL2MassSb3 
    operator['GL2MassSb4'] = GL2MassSb4 
    operator['GL3MassSb1'] = GL3MassSb1 
    operator['GL3MassSb2'] = GL3MassSb2 
    operator['GL3MassSb3'] = GL3MassSb3 
    operator['GL3MassSb4'] = GL3MassSb4 
    operator['GL4MassSb1'] = GL4MassSb1 
    operator['GL4MassSb2'] = GL4MassSb2 
    operator['GL4MassSb3'] = GL4MassSb3 
    operator['GL4MassSb4'] = GL4MassSb4
    operator['GL5MassSb1'] = GL5MassSb1 
    operator['GL5MassSb2'] = GL5MassSb2 
    operator['GL5MassSb3'] = GL5MassSb3 
    operator['GL5MassSb4'] = GL5MassSb4 
    operator['GL6MassSb1'] = GL6MassSb1 
    operator['GL6MassSb2'] = GL6MassSb2 
    operator['GL6MassSb3'] = GL6MassSb3 
    operator['GL6MassSb4'] = GL6MassSb4 
    operator['GL7MassSb1'] = GL7MassSb1 
    operator['GL7MassSb2'] = GL7MassSb2 
    operator['GL7MassSb3'] = GL7MassSb3 
    operator['GL7MassSb4'] = GL7MassSb4 
    operator['GL8MassSb1'] = GL8MassSb1 
    operator['GL8MassSb2'] = GL8MassSb2 
    operator['GL8MassSb3'] = GL8MassSb3 
    operator['GL8MassSb4'] = GL8MassSb4
    
##     operator['TisTot']    = val(BhhYield)#BhhNcanTis)
##     operator['TisErrTot'] = err(BhhYield)#BhhNcanTis)
##     operator['MisIDGlobalFactor']    = val(MisIDGlobalFactor)
##     operator['MisIDGlobalFactorErr'] = err(MisIDGlobalFactor)
    operator['MisID_comment'  ] = '\n## Mis-identification'

    operator['MisIDTotYield']    = val(MisIDTotalYield)
    operator['MisIDTotYieldErr'] = err(MisIDTotalYield)
    
    operator['MisIDfBs']     = val    (fpeakBs)
    operator['MisIDfErrPBs'] = errpos (fpeakBs)
    operator['MisIDfErrNBs'] = -errneg(fpeakBs)
    operator['MisIDfBd']     = val    (fpeakBd)
    operator['MisIDfErrPBd'] = errpos (fpeakBd)
    operator['MisIDfErrNBd'] = -errneg(fpeakBd)
    
    operator['MisIDfBDTBin1'] = val(MisIDfBDTBin1)
    operator['MisIDfBDTBin2'] = val(MisIDfBDTBin2)
    operator['MisIDfBDTBin3'] = val(MisIDfBDTBin3)
    operator['MisIDfBDTBin4'] = val(MisIDfBDTBin4)          
    operator['MisIDfBDTBin5'] = val(MisIDfBDTBin5)
    operator['MisIDfBDTBin6'] = val(MisIDfBDTBin6)
    operator['MisIDfBDTBin7'] = val(MisIDfBDTBin7)
    operator['MisIDfBDTBin8'] = val(MisIDfBDTBin8)
    
    operator['SystBkgBin1'] = SystBkgBin1
    operator['SystBkgBin2'] = SystBkgBin2
    operator['SystBkgBin3'] = SystBkgBin3
    operator['SystBkgBin4'] = SystBkgBin4
    operator['SystBkgBin5'] = SystBkgBin5
    operator['SystBkgBin6'] = SystBkgBin6
    operator['SystBkgBin7'] = SystBkgBin7
    operator['SystBkgBin8'] = SystBkgBin8

    operator['ExclBkg_comment'    ] = '\n## Exclusive Backgrounds'
    operator['BRMeasured_Bs']     = val   (BRMeasuredBs)
    operator['BRMeasured_BsErrP'] = errpos(BRMeasuredBs)
    operator['BRMeasured_BsErrN'] = -errneg(BRMeasuredBs)

    operator["BkgNorm"] = val(BkgNorm)
    operator["BkgNormErr"] = err(BkgNorm)

    # Bd -> pi mu nu 
    setBkg(operator, "PiMuNu")

    # B+(0) -> pi+(0) mu mu 
    setBkg(operator, "PiMuMu")

    # Bs -> K mu nu  
    setBkg(operator, "KMuNu")

    # Lb-> p mu nu
    setBkg(operator, "LbPMuNu")

    
    f = open('toytable_autumn13.py','w')
    for key in operator.keys:
        if key.count('comment') != 0:
            f.write(str(operator[key])+'\n')
        else:
            f.write(key+' = '+str(operator[key])+'\n')
    f.close()
    

    
    
     
    
 

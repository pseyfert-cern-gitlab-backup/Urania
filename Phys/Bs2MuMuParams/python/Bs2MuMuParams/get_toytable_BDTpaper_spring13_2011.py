#---------------------------------------------------
# script to write the table with the parameters 
# for the toys
#
#  Spring 13 analysis
#  full 2011 dataset
#
#  paper BDT (1+1fb paper)
#
#---------------------------------------------------

from errors import *
from alphaparam_spring13_2011 import *
from PeakingParam_BDTpaper_spring13_2011 import *
from BDTparam_BDTpaper_spring13_2011 import * 

print 'run toytable() to produce the table.'
print 'toytable()'

def toytable():
    keys = [
            #'Norm_comment'
            'BuJpsiK_BF','BuJpsiK_BFErr'
            ,'BdKpi_BF','BdKpi_BFErr'
            ,'TimeAcceptanceCorrBs', 'TimeAcceptanceCorrBsErr', 'TimeAcceptanceCorrBd', 'TimeAcceptanceCorrBdErr'
            ,'NormBu_fullmass','NormBu_fullmassErr','NormKPi_fullmass','NormKPi_fullmassErr'
            ,'NormBu','NormBuErr','NormKPi','NormKPiErr'
            ,'fsfd','fsfdErrP','fsfdErrN'
            #,'MassSig_comment'
            ,'CBTrans','CBTransErr'
            ,'CBExpo','CBExpoErr'
            ,'MassMeanBs',   'MassMeanBd',   'MassResoBs',   'MassResoBd'
            ,'MassMeanErrBs','MassMeanErrBd','MassResoErrBs','MassResoErrBd'
            #,'BDTSig_comment'
            ,'TisTot', 'TisErrTot'
            ,'BDT_sig1','BDT_sig2','BDT_sig3','BDT_sig4','BDT_sig5','BDT_sig6','BDT_sig7','BDT_sig8' 
            ,'BDT_sigErr1','BDT_sigErr2','BDT_sigErr3','BDT_sigErr4','BDT_sigErr5','BDT_sigErr6','BDT_sigErr7','BDT_sigErr8'
            ,'Justine1','Justine2','Justine3','Justine4','Justine5','Justine6','Justine7','Justine8'
            ,'TimeAcc1', 'TimeAcc2', 'TimeAcc3', 'TimeAcc4', 'TimeAcc5', 'TimeAcc6', 'TimeAcc7', 'TimeAcc8'
            #,'BKG_comment'
            ,'BkgMassk1','BkgMasskErrP1','BkgMasskErrN1'
            ,'BkgMassk2','BkgMasskErrP2','BkgMasskErrN2'
            ,'BkgMassk3','BkgMasskErrP3','BkgMasskErrN3'
            ,'BkgMassk4','BkgMasskErrP4','BkgMasskErrN4'
            ,'BkgMassk5','BkgMasskErrP5','BkgMasskErrN5'
            ,'BkgMassk6','BkgMasskErrP6','BkgMasskErrN6'
            ,'BkgMassk7','BkgMasskErrP7','BkgMasskErrN7'
            ,'BkgMassk8','BkgMasskErrP8','BkgMasskErrN8'
            ,'FracCombBin1','FracCombBin2','FracCombBin3','FracCombBin4','FracCombBin5','FracCombBin6','FracCombBin7','FracCombBin8'
            ,'FracCombErrP1','FracCombErrP2','FracCombErrP3','FracCombErrP4','FracCombErrP5','FracCombErrP6','FracCombErrP7','FracCombErrP8'
            ,'FracCombErrN1','FracCombErrN2','FracCombErrN3','FracCombErrN4','FracCombErrN5','FracCombErrN6','FracCombErrN7','FracCombErrN8'
            ,'SbGL1','GL1MassSb1','GL1MassSb2','GL1MassSb3','GL1MassSb4','SystBkgBin1'
            ,'SbGL2','GL2MassSb1','GL2MassSb2','GL2MassSb3','GL2MassSb4','SystBkgBin2'
            ,'SbGL3','GL3MassSb1','GL3MassSb2','GL3MassSb3','GL3MassSb4','SystBkgBin3'
            ,'SbGL4','GL4MassSb1','GL4MassSb2','GL4MassSb3','GL4MassSb4','SystBkgBin4'
            ,'SbGL5','GL5MassSb1','GL5MassSb2','GL5MassSb3','GL5MassSb4','SystBkgBin5'
            ,'SbGL6','GL6MassSb1','GL6MassSb2','GL6MassSb3','GL6MassSb4','SystBkgBin6'
            ,'SbGL7','GL7MassSb1','GL7MassSb2','GL7MassSb3','GL7MassSb4','SystBkgBin7'
            ,'SbGL8','GL8MassSb1','GL8MassSb2','GL8MassSb3','GL8MassSb4','SystBkgBin8'
            #,'MisID_comment'
            ,'MisIDfBs','MisIDfBd','MisIDfErrPBs','MisIDfErrPBd','MisIDfErrNBs','MisIDfErrNBd'
            ,'MisIDGlobalFactor', 'MisIDGlobalFactorErr'
            ,'MisIDfBDTBin1','MisIDfBDTBin2','MisIDfBDTBin3','MisIDfBDTBin4'
            ,'MisIDfBDTBin5','MisIDfBDTBin6','MisIDfBDTBin7','MisIDfBDTBin8'
            #,'BR_comment'
            ,'Bsmumu_BR','Bsmumu_BRErr','Bdmumu_BR','Bdmumu_BRErr'
            ,'BRMeasured_Bs','BRMeasured_BsErrP','BRMeasured_BsErrN'
            # PiMuNu
            ,'PiMuNuYield','PiMuNuYieldErr'
            ,'PiMuNu1','PiMuNu2','PiMuNu3','PiMuNu4','PiMuNu5','PiMuNu6','PiMuNu7','PiMuNu8'
            ,'PiMuNu1Err','PiMuNu2Err','PiMuNu3Err','PiMuNu4Err','PiMuNu5Err','PiMuNu6Err','PiMuNu7Err','PiMuNu8Err'
             #
             ,'sigmaPiMuNu1', 'sigmaPiMuNu2', 'sigmaPiMuNu3', 'sigmaPiMuNu4', 'sigmaPiMuNu5', 'sigmaPiMuNu6', 'sigmaPiMuNu7', 'sigmaPiMuNu8'
, 'sigmaPiMuNu1ErrPlus', 'sigmaPiMuNu2ErrPlus', 'sigmaPiMuNu3ErrPlus', 'sigmaPiMuNu4ErrPlus', 'sigmaPiMuNu5ErrPlus', 'sigmaPiMuNu6ErrPlus', 'sigmaPiMuNu7ErrPlus', 'sigmaPiMuNu8ErrPlus'                  
,'sigmaPiMuNu1ErrMinus', 'sigmaPiMuNu2ErrMinus', 'sigmaPiMuNu3ErrMinus', 'sigmaPiMuNu4ErrMinus', 'sigmaPiMuNu5ErrMinus', 'sigmaPiMuNu6ErrMinus', 'sigmaPiMuNu7ErrMinus', 'sigmaPiMuNu8ErrMinus'     
,'meanPiMuNu1', 'meanPiMuNu2', 'meanPiMuNu3', 'meanPiMuNu4', 'meanPiMuNu5', 'meanPiMuNu6', 'meanPiMuNu7', 'meanPiMuNu8'
, 'meanPiMuNu1ErrPlus', 'meanPiMuNu2ErrPlus', 'meanPiMuNu3ErrPlus', 'meanPiMuNu4ErrPlus', 'meanPiMuNu5ErrPlus', 'meanPiMuNu6ErrPlus', 'meanPiMuNu7ErrPlus', 'meanPiMuNu8ErrPlus'
, 'meanPiMuNu1ErrMinus', 'meanPiMuNu2ErrMinus', 'meanPiMuNu3ErrMinus', 'meanPiMuNu4ErrMinus', 'meanPiMuNu5ErrMinus', 'meanPiMuNu6ErrMinus', 'meanPiMuNu7ErrMinus', 'meanPiMuNu8ErrMinus'
            
            # PiMuMu
            ,'PiMuMuYield','PiMuMuYieldErr'
            ,'PiMuMu1','PiMuMu2','PiMuMu3','PiMuMu4','PiMuMu5','PiMuMu6','PiMuMu7','PiMuMu8'
            ,'PiMuMu1Err','PiMuMu2Err','PiMuMu3Err','PiMuMu4Err','PiMuMu5Err','PiMuMu6Err','PiMuMu7Err','PiMuMu8Err'
             #
             ,'sigmaPiMuMu1', 'sigmaPiMuMu2', 'sigmaPiMuMu3', 'sigmaPiMuMu4', 'sigmaPiMuMu5', 'sigmaPiMuMu6', 'sigmaPiMuMu7', 'sigmaPiMuMu8'
, 'sigmaPiMuMu1ErrPlus', 'sigmaPiMuMu2ErrPlus', 'sigmaPiMuMu3ErrPlus', 'sigmaPiMuMu4ErrPlus', 'sigmaPiMuMu5ErrPlus', 'sigmaPiMuMu6ErrPlus', 'sigmaPiMuMu7ErrPlus', 'sigmaPiMuMu8ErrPlus'                  
,'sigmaPiMuMu1ErrMinus', 'sigmaPiMuMu2ErrMinus', 'sigmaPiMuMu3ErrMinus', 'sigmaPiMuMu4ErrMinus', 'sigmaPiMuMu5ErrMinus', 'sigmaPiMuMu6ErrMinus', 'sigmaPiMuMu7ErrMinus', 'sigmaPiMuMu8ErrMinus'     
,'meanPiMuMu1', 'meanPiMuMu2', 'meanPiMuMu3', 'meanPiMuMu4', 'meanPiMuMu5', 'meanPiMuMu6', 'meanPiMuMu7', 'meanPiMuMu8'
, 'meanPiMuMu1ErrPlus', 'meanPiMuMu2ErrPlus', 'meanPiMuMu3ErrPlus', 'meanPiMuMu4ErrPlus', 'meanPiMuMu5ErrPlus', 'meanPiMuMu6ErrPlus', 'meanPiMuMu7ErrPlus', 'meanPiMuMu8ErrPlus'
, 'meanPiMuMu1ErrMinus', 'meanPiMuMu2ErrMinus', 'meanPiMuMu3ErrMinus', 'meanPiMuMu4ErrMinus', 'meanPiMuMu5ErrMinus', 'meanPiMuMu6ErrMinus', 'meanPiMuMu7ErrMinus', 'meanPiMuMu8ErrMinus'

             ]
    
    operator= {}
    operator['Norm_comment'   ] = '\n## Normalisation'
    operator['MassSig_comment'] = '\n## Mass Signal'
    operator['BDTSig_comment' ] = '\n## BDT Signal'
    operator['BKG_comment'    ] = '\n## Background'
    operator['MisID_comment'  ] = '\n## Mis-identification'
    operator['BR_comment'     ] = '\n## Branching Fraction'
    operator['Bsmumu_BR']    = val(Bsmumu_BR)
    operator['Bsmumu_BRErr'] = err(Bsmumu_BR)
    operator['Bdmumu_BR']    = val(Bdmumu_BR)
    operator['Bdmumu_BRErr'] = err(Bdmumu_BR)
    
    operator['BuJpsiK_BF']     = val(BuBR)
    operator['BuJpsiK_BFErr']  = err(BuBR)
    operator['BdKpi_BF']     = val(BdBR)
    operator['BdKpi_BFErr']  = err(BdBR)

    operator['TimeAcceptanceCorrBs']     = val(TimeAcceptanceCorrBs)
    operator['TimeAcceptanceCorrBsErr']  = err(TimeAcceptanceCorrBs)
    operator['TimeAcceptanceCorrBd']     = val(TimeAcceptanceCorrBd)
    operator['TimeAcceptanceCorrBdErr']  = err(TimeAcceptanceCorrBd)
    
    operator['NormBu']     = val(Bub)
    operator['NormBuErr']  = err(Bub)
    operator['NormKPi']    = val(Bdb)
    operator['NormKPiErr'] = err(Bdb)
    operator['NormBu_fullmass']     = val(Bu_fit)
    operator['NormBu_fullmassErr']  = err(Bu_fit)
    operator['NormKPi_fullmass']    = val(Bd_fit)
    operator['NormKPi_fullmassErr'] = err(Bd_fit) 
    
##     operator['NormBu']     = val(Bub_noBF)
##     operator['NormBuErr']  = err(Bub_noBF)
##     operator['NormKPi']    = val(Bdb_noBF)
##     operator['NormKPiErr'] = err(Bdb_noBF) 
##     operator['NormBu_fullmass']     = val(Bu_fit_noBF)
##     operator['NormBu_fullmassErr']  = err(Bu_fit_noBF)
##     operator['NormKPi_fullmass']    = val(Bd_fit_noBF)
##     operator['NormKPi_fullmassErr'] = err(Bd_fit_noBF)
    
    operator['fsfd']    = val(fdfs)
    operator['fsfdErrP'] =  err(fdfs)
    operator['fsfdErrN'] = -err(fdfs)
    operator['TisTot']    = val(BhhYield)#BhhNcanTis)
    operator['TisErrTot'] = err(BhhYield)#BhhNcanTis)

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
    operator['MassMeanBs'] = val(MassMeanBs)
    operator['MassMeanBd'] = val(MassMeanBd)
    operator['MassResoBs'] = val(MassResoBs)
    operator['MassResoBd'] = val(MassResoBd)
    operator['CBTrans'] = val(CBTrans)
    operator['CBExpo'] = val(CBExpo)
    operator['MassMeanErrBs'] = err(MassMeanBs)
    operator['MassMeanErrBd'] = err(MassMeanBd)
    operator['MassResoErrBs'] = err(MassResoBs)
    operator['MassResoErrBd'] = err(MassResoBd)
    operator['CBTransErr'] = err(CBTrans)
    operator['CBExpoErr'] = err(CBExpo)
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
    
    operator['MisIDfBs']     = val    (fpeakBs)
    operator['MisIDfErrPBs'] = errpos (fpeakBs)
    operator['MisIDfErrNBs'] = -errneg(fpeakBs)
    operator['MisIDfBd']     = val    (fpeakBd)
    operator['MisIDfErrPBd'] = errpos (fpeakBd)
    operator['MisIDfErrNBd'] = -errneg(fpeakBd)
    operator['MisIDGlobalFactor']    = val(MisIDGlobalFactor)
    operator['MisIDGlobalFactorErr'] = err(MisIDGlobalFactor)
    
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

    operator['BRMeasured_Bs']     = val   (BRMeasuredBs)
    operator['BRMeasured_BsErrP'] = errpos(BRMeasuredBs)
    operator['BRMeasured_BsErrN'] = -errneg(BRMeasuredBs)
#
    operator['PiMuNuYield']    = val(PiMuNuTot)
    operator['PiMuNuYieldErr'] = err(PiMuNuTot)
      
    operator['PiMuNu1'] =    val(PiMuNuFrac1)
    operator['PiMuNu2'] =    val(PiMuNuFrac2)
    operator['PiMuNu3'] =    val(PiMuNuFrac3)
    operator['PiMuNu4'] =    val(PiMuNuFrac4)
    operator['PiMuNu5'] =    val(PiMuNuFrac5)
    operator['PiMuNu6'] =    val(PiMuNuFrac6)
    operator['PiMuNu7'] =    val(PiMuNuFrac7)
    operator['PiMuNu8'] =    val(PiMuNuFrac8)
    operator['PiMuNu1Err'] = err(PiMuNuFrac1)
    operator['PiMuNu2Err'] = err(PiMuNuFrac2)
    operator['PiMuNu3Err'] = err(PiMuNuFrac3)
    operator['PiMuNu4Err'] = err(PiMuNuFrac4)
    operator['PiMuNu5Err'] = err(PiMuNuFrac5)
    operator['PiMuNu6Err'] = err(PiMuNuFrac6)
    operator['PiMuNu7Err'] = err(PiMuNuFrac7)
    operator['PiMuNu8Err'] = err(PiMuNuFrac8)
   
    operator['sigmaPiMuNu1'] =         val(PiMuNuSigma1)
    operator['sigmaPiMuNu2'] =         val(PiMuNuSigma2)
    operator['sigmaPiMuNu3'] =         val(PiMuNuSigma3)
    operator['sigmaPiMuNu4'] =         val(PiMuNuSigma4)
    operator['sigmaPiMuNu5'] =         val(PiMuNuSigma5)
    operator['sigmaPiMuNu6'] =         val(PiMuNuSigma6)
    operator['sigmaPiMuNu7'] =         val(PiMuNuSigma7)
    operator['sigmaPiMuNu8'] =         val(PiMuNuSigma8)
    operator['sigmaPiMuNu1ErrPlus'] =   err(PiMuNuSigma1)   #      errpos(PiMuNuSigma1)    
    operator['sigmaPiMuNu2ErrPlus'] =   err(PiMuNuSigma2)   #      errpos(PiMuNuSigma2)    
    operator['sigmaPiMuNu3ErrPlus'] =   err(PiMuNuSigma3)   #      errpos(PiMuNuSigma3)    
    operator['sigmaPiMuNu4ErrPlus'] =   err(PiMuNuSigma4)   #      errpos(PiMuNuSigma4)    
    operator['sigmaPiMuNu5ErrPlus'] =   err(PiMuNuSigma5)   #      errpos(PiMuNuSigma5)    
    operator['sigmaPiMuNu6ErrPlus'] =   err(PiMuNuSigma6)   #      errpos(PiMuNuSigma6)    
    operator['sigmaPiMuNu7ErrPlus'] =   err(PiMuNuSigma7)   #      errpos(PiMuNuSigma7)    
    operator['sigmaPiMuNu8ErrPlus'] =   err(PiMuNuSigma8)   #      errpos(PiMuNuSigma8)
    operator['sigmaPiMuNu1ErrMinus'] = -err(PiMuNuSigma1)   #     -errneg(PiMuNuSigma1)    
    operator['sigmaPiMuNu2ErrMinus'] = -err(PiMuNuSigma2)   #     -errneg(PiMuNuSigma2)    
    operator['sigmaPiMuNu3ErrMinus'] = -err(PiMuNuSigma3)   #     -errneg(PiMuNuSigma3)    
    operator['sigmaPiMuNu4ErrMinus'] = -err(PiMuNuSigma4)   #     -errneg(PiMuNuSigma4)    
    operator['sigmaPiMuNu5ErrMinus'] = -err(PiMuNuSigma5)   #     -errneg(PiMuNuSigma5)    
    operator['sigmaPiMuNu6ErrMinus'] = -err(PiMuNuSigma6)   #     -errneg(PiMuNuSigma6)    
    operator['sigmaPiMuNu7ErrMinus'] = -err(PiMuNuSigma7)   #     -errneg(PiMuNuSigma7)    
    operator['sigmaPiMuNu8ErrMinus'] = -err(PiMuNuSigma8)   #     -errneg(PiMuNuSigma8)    
    
    operator['meanPiMuNu1'] =         val(PiMuNuMean1)
    operator['meanPiMuNu2'] =         val(PiMuNuMean2)
    operator['meanPiMuNu3'] =         val(PiMuNuMean3)
    operator['meanPiMuNu4'] =         val(PiMuNuMean4)
    operator['meanPiMuNu5'] =         val(PiMuNuMean5)
    operator['meanPiMuNu6'] =         val(PiMuNuMean6)
    operator['meanPiMuNu7'] =         val(PiMuNuMean7)
    operator['meanPiMuNu8'] =         val(PiMuNuMean8)
    operator['meanPiMuNu1ErrPlus'] =   err(PiMuNuMean1) #   errpos(PiMuNuMean1)   
    operator['meanPiMuNu2ErrPlus'] =   err(PiMuNuMean2) #   errpos(PiMuNuMean2)   
    operator['meanPiMuNu3ErrPlus'] =   err(PiMuNuMean3) #   errpos(PiMuNuMean3)   
    operator['meanPiMuNu4ErrPlus'] =   err(PiMuNuMean4) #   errpos(PiMuNuMean4)   
    operator['meanPiMuNu5ErrPlus'] =   err(PiMuNuMean5) #   errpos(PiMuNuMean5)   
    operator['meanPiMuNu6ErrPlus'] =   err(PiMuNuMean6) #   errpos(PiMuNuMean6)   
    operator['meanPiMuNu7ErrPlus'] =   err(PiMuNuMean7) #   errpos(PiMuNuMean7)   
    operator['meanPiMuNu8ErrPlus'] =   err(PiMuNuMean8) #   errpos(PiMuNuMean8)   
    operator['meanPiMuNu1ErrMinus'] = -err(PiMuNuMean1) #  -errneg(PiMuNuMean1)   
    operator['meanPiMuNu2ErrMinus'] = -err(PiMuNuMean2) #  -errneg(PiMuNuMean2)   
    operator['meanPiMuNu3ErrMinus'] = -err(PiMuNuMean3) #  -errneg(PiMuNuMean3)   
    operator['meanPiMuNu4ErrMinus'] = -err(PiMuNuMean4) #  -errneg(PiMuNuMean4)   
    operator['meanPiMuNu5ErrMinus'] = -err(PiMuNuMean5) #  -errneg(PiMuNuMean5)   
    operator['meanPiMuNu6ErrMinus'] = -err(PiMuNuMean6) #  -errneg(PiMuNuMean6)   
    operator['meanPiMuNu7ErrMinus'] = -err(PiMuNuMean7) #  -errneg(PiMuNuMean7)   
    operator['meanPiMuNu8ErrMinus'] = -err(PiMuNuMean8) #  -errneg(PiMuNuMean8)   


#
    operator['PiMuMuYield']    = val(PiMuMuTot)
    operator['PiMuMuYieldErr'] = err(PiMuMuTot)
      
    operator['PiMuMu1'] =    val(PiMuMuFrac1)
    operator['PiMuMu2'] =    val(PiMuMuFrac2)
    operator['PiMuMu3'] =    val(PiMuMuFrac3)
    operator['PiMuMu4'] =    val(PiMuMuFrac4)
    operator['PiMuMu5'] =    val(PiMuMuFrac5)
    operator['PiMuMu6'] =    val(PiMuMuFrac6)
    operator['PiMuMu7'] =    val(PiMuMuFrac7)
    operator['PiMuMu8'] =    val(PiMuMuFrac8)
    operator['PiMuMu1Err'] = err(PiMuMuFrac1)
    operator['PiMuMu2Err'] = err(PiMuMuFrac2)
    operator['PiMuMu3Err'] = err(PiMuMuFrac3)
    operator['PiMuMu4Err'] = err(PiMuMuFrac4)
    operator['PiMuMu5Err'] = err(PiMuMuFrac5)
    operator['PiMuMu6Err'] = err(PiMuMuFrac6)
    operator['PiMuMu7Err'] = err(PiMuMuFrac7)
    operator['PiMuMu8Err'] = err(PiMuMuFrac8)
   
    operator['sigmaPiMuMu1'] =         val(PiMuMuSigma1)
    operator['sigmaPiMuMu2'] =         val(PiMuMuSigma2)
    operator['sigmaPiMuMu3'] =         val(PiMuMuSigma3)
    operator['sigmaPiMuMu4'] =         val(PiMuMuSigma4)
    operator['sigmaPiMuMu5'] =         val(PiMuMuSigma5)
    operator['sigmaPiMuMu6'] =         val(PiMuMuSigma6)
    operator['sigmaPiMuMu7'] =         val(PiMuMuSigma7)
    operator['sigmaPiMuMu8'] =         val(PiMuMuSigma8)
    operator['sigmaPiMuMu1ErrPlus'] =  err(PiMuMuSigma1)
    operator['sigmaPiMuMu2ErrPlus'] =  err(PiMuMuSigma2)
    operator['sigmaPiMuMu3ErrPlus'] =  err(PiMuMuSigma3)
    operator['sigmaPiMuMu4ErrPlus'] =  err(PiMuMuSigma4)
    operator['sigmaPiMuMu5ErrPlus'] =  err(PiMuMuSigma5)
    operator['sigmaPiMuMu6ErrPlus'] =  err(PiMuMuSigma6)
    operator['sigmaPiMuMu7ErrPlus'] =  err(PiMuMuSigma7)
    operator['sigmaPiMuMu8ErrPlus'] =  err(PiMuMuSigma8)                   
    operator['sigmaPiMuMu1ErrMinus'] = -err(PiMuMuSigma1)
    operator['sigmaPiMuMu2ErrMinus'] = -err(PiMuMuSigma2)
    operator['sigmaPiMuMu3ErrMinus'] = -err(PiMuMuSigma3)
    operator['sigmaPiMuMu4ErrMinus'] = -err(PiMuMuSigma4)
    operator['sigmaPiMuMu5ErrMinus'] = -err(PiMuMuSigma5)
    operator['sigmaPiMuMu6ErrMinus'] = -err(PiMuMuSigma6)
    operator['sigmaPiMuMu7ErrMinus'] = -err(PiMuMuSigma7)
    operator['sigmaPiMuMu8ErrMinus'] = -err(PiMuMuSigma8)

    operator['meanPiMuMu1'] =         val(PiMuMuMean1)
    operator['meanPiMuMu2'] =         val(PiMuMuMean2)
    operator['meanPiMuMu3'] =         val(PiMuMuMean3)
    operator['meanPiMuMu4'] =         val(PiMuMuMean4)
    operator['meanPiMuMu5'] =         val(PiMuMuMean5)
    operator['meanPiMuMu6'] =         val(PiMuMuMean6)
    operator['meanPiMuMu7'] =         val(PiMuMuMean7)
    operator['meanPiMuMu8'] =         val(PiMuMuMean8)
    operator['meanPiMuMu1ErrPlus'] =  err(PiMuMuMean1)
    operator['meanPiMuMu2ErrPlus'] =  err(PiMuMuMean2)
    operator['meanPiMuMu3ErrPlus'] =  err(PiMuMuMean3)
    operator['meanPiMuMu4ErrPlus'] =  err(PiMuMuMean4)
    operator['meanPiMuMu5ErrPlus'] =  err(PiMuMuMean5)
    operator['meanPiMuMu6ErrPlus'] =  err(PiMuMuMean6)
    operator['meanPiMuMu7ErrPlus'] =  err(PiMuMuMean7)
    operator['meanPiMuMu8ErrPlus'] =  err(PiMuMuMean8)
    operator['meanPiMuMu1ErrMinus'] = -err(PiMuMuMean1)
    operator['meanPiMuMu2ErrMinus'] = -err(PiMuMuMean2)
    operator['meanPiMuMu3ErrMinus'] = -err(PiMuMuMean3)
    operator['meanPiMuMu4ErrMinus'] = -err(PiMuMuMean4)
    operator['meanPiMuMu5ErrMinus'] = -err(PiMuMuMean5)
    operator['meanPiMuMu6ErrMinus'] = -err(PiMuMuMean6)
    operator['meanPiMuMu7ErrMinus'] = -err(PiMuMuMean7)
    operator['meanPiMuMu8ErrMinus'] = -err(PiMuMuMean8)



    
        
    out_name = 'toytable_BDTpaper_spring13_2011.py'
    
    f = open(out_name,'w')
    for key in keys:
        if key.count('comment') != 0:
            f.write(str(operator[key])+'\n')
        else:
            f.write(key+' = '+str(operator[key])+'\n')
    f.close()


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

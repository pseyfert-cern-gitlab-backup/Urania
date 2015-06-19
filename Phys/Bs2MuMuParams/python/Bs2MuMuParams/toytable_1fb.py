#---------------------------------------------------
# script to write the table with the parameters 
# for the toys
#
#  2012 -- Analysis 1fb
#
#---------------------------------------------------

from errors import *
from alphaparam_1fb import *
from BDTparam_1fb import * 

def toytable():
    keys = [
            #'Norm_comment'
             'NormPhi','NormPhiErr','NormBu','NormBuErr','NormKPi','NormKPiErr'
            ,'fsfd','fsfdErrP','fsfdErrN'
            #,'MassSig_comment'
            ,'CBTrans','CBTransErr'
            ,'MassMeanBs',   'MassMeanBd',   'MassResoBs',   'MassResoBd'
            ,'MassMeanErrBs','MassMeanErrBd','MassResoErrBs','MassResoErrBd'
            #,'BDTSig_comment'
            ,'TisTot','Tis2','Tis3','Tis4','Tis5','Tis6','Tis7','Tis8'
            ,'TisErrTot','TisErr2','TisErr3','TisErr4','TisErr5','TisErr6','TisErr7','TisErr8'
            ,'Justine1','Justine2','Justine3','Justine4','Justine5','Justine6','Justine7','Justine8'
            #,'BKG_comment'
            ,'BkgMassk1','BkgMasskErrP1','BkgMasskErrN1'
            ,'BkgMassk2','BkgMasskErrP2','BkgMasskErrN2'
            ,'BkgMassk3','BkgMasskErrP3','BkgMasskErrN3'
            ,'BkgMassk4','BkgMasskErrP4','BkgMasskErrN4'
            ,'BkgMassk5','BkgMasskErrP5','BkgMasskErrN5'
            ,'BkgMassk6','BkgMasskErrP6','BkgMasskErrN6'
            ,'BkgMassk7','BkgMasskErrP7','BkgMasskErrN7'
            ,'BkgMassk8','BkgMasskErrP8','BkgMasskErrN8'
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
            ,'BRMeasured_Bs','BRMeasured_BsErrP','BRMeasured_BsErrN']
    
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
    operator['NormPhi']    = val(Bsb)
    operator['NormPhiErr'] = err(Bsb)
    operator['NormBu']     = val(Bub)
    operator['NormBuErr']  = err(Bub)
    operator['NormKPi']    = val(Bdb)
    operator['NormKPiErr'] = err(Bdb) 
    operator['fsfd']    = val(fdfs)
    operator['fsfdErrP'] =  errpos(fdfs)
    operator['fsfdErrN'] = -errneg(fdfs)
    operator['TisTot']    = val(TisTot)
    operator['TisErrTot'] = err(TisTot)
    operator['Tis2'] = val(Tis2)
    operator['Tis3'] = val(Tis3)
    operator['Tis4'] = val(Tis4)
    operator['Tis5'] = val(Tis5)
    operator['Tis6'] = val(Tis6)
    operator['Tis7'] = val(Tis7)
    operator['Tis8'] = val(Tis8)
    operator['TisErr2'] = err(Tis2)
    operator['TisErr3'] = err(Tis3)
    operator['TisErr4'] = err(Tis4)
    operator['TisErr5'] = err(Tis5)
    operator['TisErr6'] = err(Tis6)
    operator['TisErr7'] = err(Tis7)
    operator['TisErr8'] = err(Tis8)
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
    operator['MassMeanErrBs'] = err(MassMeanBs)
    operator['MassMeanErrBd'] = err(MassMeanBd)
    operator['MassResoErrBs'] = err(MassResoBs)
    operator['MassResoErrBd'] = err(MassResoBd)
    operator['CBTransErr'] = err(CBTrans)
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
  
    f = open('toytable.txt','w')
    for key in keys:
        if key.count('comment') != 0:
            f.write(str(operator[key])+'\n')
        else:
            f.write(key+' = '+str(operator[key])+'\n')
    f.close()


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

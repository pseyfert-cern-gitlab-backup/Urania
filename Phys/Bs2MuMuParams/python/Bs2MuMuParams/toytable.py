#---------------------------------------------------
# script to write the table with the parameters 
# for the toys 
#---------------------------------------------------

from errors import *
from alphaparam import *
from BDTparam import * #BDTparam import *

def toytable():
    keys = ['NormPhi','NormPhiErr','NormBu','NormBuErr','NormKPi',
            'NormKPiErr','fsfd','fsfdErr','TisTot','Tis2','Tis3','Tis4',
            'TisErrTot','TisErr2','TisErr3','TisErr4',
            'Justine1','Justine2','Justine3','Justine4',
            'MassMeanBs','MassMeanBd','MassReso',
            'CBTrans','MassMeanErrBs','MassMeanErrBd',
            'MassResoErr','CBTransErr',
            'BkgMassk1','BkgMassk2','BkgMassk3','BkgMassk4',
            'BkgMasskErrP1','BkgMasskErrP2','BkgMasskErrP3','BkgMasskErrP4',
            'BkgMasskErrN1','BkgMasskErrN2','BkgMasskErrN3','BkgMasskErrN4',
            'SbGL1','SbGL2','SbGL3','SbGL4',
            'GL1MassSb1','GL1MassSb2','GL1MassSb3','GL1MassSb4',
            'GL2MassSb1','GL2MassSb2','GL2MassSb3','GL2MassSb4',
            'GL3MassSb1','GL3MassSb2','GL3MassSb3','GL3MassSb4',
            'GL4MassSb1','GL4MassSb2','GL4MassSb3','GL4MassSb4',
            'MisIDfBs','MisIDfBd','MisIDfErrBs','MisIDfErrBd',
            'MisIDN','MisIDNErr',
            'SystBkgBin1','SystBkgBin2','SystBkgBin3','SystBkgBin4',
            'Bsmumu_BR', 'Bsmumu_BRErr', 'Bdmumu_BR', 'Bdmumu_BRErr',
            'BRMeasured_Bs', 'BRMeasured_BsErrP', 'BRMeasured_BsErrN']
    
    operator= {}
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
    operator['fsfdErr'] = err(fdfs)
    operator['TisTot']    = val(TisTot)
    operator['TisErrTot'] = err(TisTot)
    operator['Tis2'] = val(Tis2)
    operator['Tis3'] = val(Tis3)
    operator['Tis4'] = val(Tis4)
    operator['TisErr2'] = err(Tis2)
    operator['TisErr3'] = err(Tis3)
    operator['TisErr4'] = err(Tis4)
    operator['Justine1'] = val(Justine1)
    operator['Justine2'] = val(Justine2)
    operator['Justine3'] = val(Justine3)
    operator['Justine4'] = val(Justine4)
    operator['MassMeanBs'] = val(MassMeanBs)
    operator['MassMeanBd'] = val(MassMeanBd)
    operator['MassReso'] = val(MassReso)
    operator['CBTrans'] = val(CBTrans)
    operator['MassMeanErrBs'] = err(MassMeanBs)
    operator['MassMeanErrBd'] = err(MassMeanBd)
    operator['MassResoErr'] = err(MassReso)
    operator['CBTransErr'] = err(CBTrans)
    operator['BkgMassk1'] = val(BkgMassk1)
    operator['BkgMassk2'] = val(BkgMassk2)
    operator['BkgMassk3'] = val(BkgMassk3)
    operator['BkgMassk4'] = val(BkgMassk4)
    operator['BkgMasskErrP1'] = err(BkgMassk1)
    operator['BkgMasskErrP2'] = err(BkgMassk2)
    operator['BkgMasskErrP3'] = errpos(BkgMassk3)
    operator['BkgMasskErrP4'] = errpos(BkgMassk4)
    operator['BkgMasskErrN1'] = -1.*err(BkgMassk1)
    operator['BkgMasskErrN2'] = -1.*err(BkgMassk2)
    operator['BkgMasskErrN3'] = errneg(BkgMassk3)
    operator['BkgMasskErrN4'] = errneg(BkgMassk4)
    operator['SbGL1'] = val(SbGL1)
    operator['SbGL2'] = val(SbGL2)
    operator['SbGL3'] = val(SbGL3)
    operator['SbGL4'] = val(SbGL4)
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
    
     
    operator['MisIDfBs']    = val(fpeakBs)
    operator['MisIDfErrBs'] = err(fpeakBs)
    operator['MisIDfBd']    = val(fpeakBd)
    operator['MisIDfErrBd'] = err(fpeakBd)
    operator['MisIDN']    = val(BkgPeakNcan)
    operator['MisIDNErr'] = err(BkgPeakNcan)
    operator['SystBkgBin1'] = SystBkgBin1
    operator['SystBkgBin2'] = SystBkgBin2
    operator['SystBkgBin3'] = SystBkgBin3
    operator['SystBkgBin4'] = SystBkgBin4

    operator['BRMeasured_Bs']     = val   (BRMeasuredBs)
    operator['BRMeasured_BsErrP'] = errpos(BRMeasuredBs)
    operator['BRMeasured_BsErrN'] = errneg(BRMeasuredBs)
  
    f = open('toytable.txt','w')
    for key in keys:
        f.write(key+' = '+str(operator[key])+'\n')
    f.close()

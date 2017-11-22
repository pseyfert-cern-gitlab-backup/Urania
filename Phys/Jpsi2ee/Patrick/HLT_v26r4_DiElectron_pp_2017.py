# =============================================================================
# @file   DiElectron_pp_2017.py
# @author Jessica Prisciandaro (jessica.prisciandaro@cern.ch)
# @date   12.02.2016
# =============================================================================
"""Threshold settings for Hlt2 DiElectron lines for 2016.
WARNING :: DO NOT EDIT WITHOUT PERMISSION OF THE AUTHORS 
"""

from GaudiKernel.SystemOfUnits import GeV, mm, MeV 

class DiElectron_pp_2017(object) :
    
    __all__ = ( 'ActiveHlt2Lines' )
    
    
    def ActiveHlt2Lines(self) :
        """
        Returns a list of active lines
        """

        lines = [
            
            'Hlt2DiElectronElSoft',
            'Hlt2DiElectronJPsiEETurbo',
            ]
            
        return lines

   
    def Thresholds(self) :
        """
        Returns a dictionary of cuts
        """
        
        # keep pass through thresholds
        d = { }

        from Hlt2Lines.DiElectron.Lines     import DiElectronLines            
        d.update({DiElectronLines :
                      {'ElSoft' :          {'VDZ'       :        0,
                                            'CosAngle'  : 0.999997,
                                            'IpDzRatio' :     0.02,
                                            'IpProd'    :       0.8 * mm * mm,
                                            'SumGP'     :      0.2,
                                            'MinIpChi2' :       6,
                                            'IpChi2Prod':     2000,
                                            'Rho2'      :      36 * mm * mm,
                                            'DOCA'      :      0.3 * mm,
                                            'MaxIpChi2' :     1000000000000,
                                            'MinProbNNe' :      0.1,                                                                                                           
                                            'SVZ'       :      600 * mm,
                                            'Mass'      :     1000 * MeV,
                                            'Dira'      :        0
                                            
                                            },
                       # Turbo lines
                       'JPsiEETurbo' :  {'MassWindow' :   1100 * MeV,
                                         'Pt'         :   2500 * MeV,
                                         'ePt'       :    500 * MeV,
                                         'VertexChi2' :   25, 
                                         'TrChi2'     :   10, 
                                         'TrChi2Tight':   5,  
                                         'TRACK_TRGHOSTPROB_MAX': 0.4,
                                         'PIDCut'     : "(MINTREE('e-' == ABSID, PROBNNe)>0.4)" 
                                         },  
                       'L0Req'       : {'ElSoft'    : "L0_DECISION_PHYSICS",
                                        'JPsiEETurbo' : "L0_CHANNEL('Electron')" },
                       'Hlt1Req'     : {'ElSoft'    : None,
                                        'JPsiEETurbo' : "HLT_PASS_RE('Hlt1(?!Lumi)(?!Velo)(?!BeamGas)(?!NoPV).*Decision')" }                    
                       }
                  })
        
        return d
    


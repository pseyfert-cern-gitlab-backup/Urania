# =============================================================================
# @file:   Definition of the lines devoted to the study of DiElectron decays
# @author: Miguel Ramos Pernas miguel.ramos.pernas@cern.ch
# @author: Jessica Prisciandaro jessica.prisciandaro@cern.ch
# @date:   2016-02-12
# =============================================================================

from GaudiKernel.SystemOfUnits import GeV, MeV, mm
from Hlt2Lines.Utilities.Hlt2LinesConfigurableUser import Hlt2LinesConfigurableUser

class DiElectronLines(Hlt2LinesConfigurableUser) :
    __slots__ = {'Prescale' : { },

                 'Common'   : { },

                 'ElSoft'   : { 'VDZ'       :        0,
                                'CosAngle'  : 0.999997,
                                'IpDzRatio' :     0.01,
                                'IpProd'    :      0.8 * mm * mm,
                                'SumGP'     :      0.1,
                                'MinProbNNe':      0.1,
                                'MinIpChi2' :        16,
                                'IpChi2Prod':     2000,
                                'Rho2'      :       64 * mm * mm,
                                'DOCA'      :      0.2 * mm,
                                'MaxIpChi2' :     1000,
                                'SVZ'       :      600 * mm,
                                'Mass'      :     1000 * MeV,
                                'Dira'      :        0
                                },
                 # Turbo lines
                 'JPsiEETurbo' :  {'MassWindow' :   1100 * MeV,
                                 'Pt'         :   0 * MeV,
                                 'ePt'       :    500 * MeV,
                                 'VertexChi2' :   25, 
                                 'TrChi2'     :   10, 
                                 'TrChi2Tight':   5,
                                 'TRACK_TRGHOSTPROB_MAX': 0.4,
                                 'PIDCut'     : "(MINTREE('e-' == ABSID, PROBNNe)>0.4)" 
                                         },  
                 'L0Req'                : {'ElSoft'    : "L0_DECISION_PHYSICS",
                                           'JPsiEETurbo' : "L0_CHANNEL('Electron')" },
                 'Hlt1Req'              : {'ElSoft'    : "HLT_PASS_RE('.*Decision')",
                                           'JPsiEETurbo' : "HLT_PASS_RE('.*Decision')" }
                 }
    
    def stages(self, nickname = "" ):
        from Stages import DiElectronFromKS0,JpsiPIDFilter
        self._stages = { 'ElSoft'    : [DiElectronFromKS0],
                         'JPsiEETurbo' : [JpsiPIDFilter('JPsiEETurbo')], }
        if nickname:
            return self._stages[nickname]
        else:
            return self._stages

    def __apply_configuration__(self) :
        from HltLine.HltLine import Hlt2Line
        for nickname, algos in self.algorithms(self.stages()):
            linename = 'DiElectron' + nickname if nickname != 'DiElectron' else nickname
            if nickname.find('Turbo') > -1 :
              Hlt2Line(linename, prescale = self.prescale,
                       algos = algos, postscale = self.postscale,
                       L0DU = self.L0Req[nickname],
                       HLT1 = self.Hlt1Req[nickname],
                       Turbo=True)  
            else :
              Hlt2Line(linename, prescale = self.prescale,
                       algos = algos, postscale = self.postscale,
                       L0DU = self.L0Req[nickname],
                       HLT1 = self.Hlt1Req[nickname])

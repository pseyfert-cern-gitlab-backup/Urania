###########################################################################################################################################
## P2VVParameterizations.CPVParams: CP and CPT violation parameterizations                                                               ##
##                                                                                                                                       ##
## authors:                                                                                                                              ##
##   GR,  Gerhard Raven,      Nikhef & VU, Gerhard.Raven@nikhef.nl                                                                       ##
##   JvL, Jeroen van Leerdam, Nikhef,      j.van.leerdam@nikhef.nl                                                                       ##
##   GC , Georgios Chatzikonstantinidis ,Nikhef, georgm@nikhef.nl                                                                        ##
###########################################################################################################################################

from P2VV.Parameterizations.GeneralUtils import _util_parse_mixin, _util_conditionalObs_mixin
from P2VV.RooFitWrappers import Pdf
###########################################################################################################################################
## follow HFAG conventions:                                                                                                              ##
## lambda_f = q/p * A_f^bar / A_f                                                                                                        ##
##          = eta_f * |lambda_f| * e^(-i * phi_s^f)                                                                                      ##
##          = eta_f * |lambda_f| * [cos(-phi_s^f) + i * sin(-phi_s^f)]                                                                   ##
##          = eta_f * |lambda_f| * [cos(phi_s^f)  - i * sin(phi_s^f) ]                                                                   ##
## C_f = (1 - |lambda_f|^2) / (1 + |lambda_f|^2)                                                                                         ##
## D_f = - Re(lambda_f) / (1 + |lambda_f|^2)                                                                                             ##
##     = -eta_f * |lambda_f| / (1 + |lambda_f|^2) * cos(-phi_s^f)                                                                        ##
##     = -eta_f * |lambda_f| / (1 + |lambda_f|^2) * cos(phi_s^f)                                                                         ##
## S_f = + Im(lambda_f) / (1 + |lambda_f|^2)                                                                                             ##
##     = +eta_f * |lambda_f| / (1 + |lambda_f|^2) * sin(-phi_s^f)                                                                        ##
##     = -eta_f * |lambda_f| / (1 + |lambda_f|^2) * sin(phi_s^f)                                                                         ##
###########################################################################################################################################
from math import sqrt, cos, sin, pi
from ROOT import RooNumber
RooInf = RooNumber.infinity()
phiVal    = 0.
lambSqVal = 1.
lambVal   = sqrt(lambSqVal)
ReLambVal = lambVal * cos(-phiVal)
ImLambVal = lambVal * sin(-phiVal)
CVal      = ( 1. - lambSqVal ) / ( 1. + lambSqVal )
DVal      = -2. * ReLambVal / ( 1. + lambSqVal )
SVal      = +2. * ImLambVal / ( 1. + lambSqVal )

phiErr    = 0.1
lambSqErr = 0.08
lambErr   = lambSqErr / 2.
ReLambErr = lambSqErr / 2.
ImLambErr = phiErr
CErr      = lambSqErr / 2.
DErr      = lambSqErr / sqrt(2.)
SErr      = phiErr

#Parameters for CPT for Sidereal Modulations
CPTs         = { 'Da0'        : {'Val':0.,'Max':+RooInf,'Min':-RooInf},
                 'DaZ'        : {'Val':0.,'Max':+RooInf,'Min':-RooInf},
                 'DaX'        : {'Val':0.,'Max':+RooInf,'Min':-RooInf},
                 'DaY'        : {'Val':0.,'Max':+RooInf,'Min':-RooInf},
                 'Da0-0.38DaZ': {'Val':0.,'Max':+RooInf,'Min':-RooInf},
                 'Da1'        : {'Val':0.,'Max':+RooInf,'Min':-RooInf},
                 'Da2'        : {'Val':0.,'Max':+RooInf,'Min':-RooInf}
                 }
ParCPT       = { 'CosX': -0.38118, 'SinX':0.92450, 'Phi0':0.89905}

#Parameters for CPT without Sidereal Modulations
CPTc         = {'Re_Z': {'Val':0.,'Max':+RooInf,'Min':-RooInf},
                'Im_Z': {'Val':0.,'Max':+RooInf,'Min':-RooInf}
                }


class CPTPar_c ( _util_parse_mixin, _util_conditionalObs_mixin ):
    def __init__( self, **kwargs ):
        # class for CPT constant with and without the SME condition( Im_Z == 0 )
        for i in kwargs.keys()    : assert i in ['Re_Z','Im_Z']
        for coef in kwargs.keys() : setattr(self, '_' + coef,kwargs.pop(coef) )

    def __getitem__(self, kw): return getattr( self, '_' + kw)
    def Re_Z(self): return self._Re_Z
    def Im_Z(self): return self._Im_Z


class CPTPar_s ( _util_parse_mixin, _util_conditionalObs_mixin ):
    def __init__( self, **kwargs ):
        # class for CPT with Sidereal modulations, with the SME condition( Im_Z ==0 )
        for i in kwargs.keys()    : assert i in ['Re_Z']
        for coef in kwargs.keys() : setattr(self, '_' + coef,kwargs.pop(coef) )

    def __getitem__(self, kw): return getattr( self, '_' + kw)
    def Re_Z(self): return self._Re_Z


class _CPTConstant_( CPTPar_c ) :
    def __init__( self, **kwargs) :
        kw = kwargs.pop('CPTConstant')
        CPTPar_c.__init__(self,Re_Z = self._parseArg( kw.pop('Name_Re') , {}, Title = 'Re(Z) param. CPT parameter without Sidreal Variations'
                                                    ,Value  = CPTc['Re_Z']['Val'] ,MinMax = (CPTc['Re_Z']['Min'],CPTc['Re_Z']['Max'] ) )
                            ,Im_Z = self._parseArg( kw.pop('Name_Im') , {}, Title = 'Im(Z) param. CPT parameter without Sidreal Variations'
                                                    ,Value  = CPTc['Im_Z']['Val'] ,MinMax = (CPTc['Im_Z']['Min'],CPTc['Im_Z']['Max'] ) )
                        )

        self._check_extraneous_kw( kwargs )

class _CPTSiderealVariations_c ( CPTPar_s , _util_conditionalObs_mixin, Pdf ):
    def __init__(self, **kwargs ):

        self._parseArg('SiderealPhase',kwargs, Title = 'SiderealPhase', Observable = True, Unit = 'rad', Value =0., MinMax = (0., +1e+30))
        self._parseArg('B_Pz'    ,kwargs, Title = 'B_Pz'    , Observable = True, Unit = 'MeV', Value =0., MinMax = (0.,+1e+30))

        _util_conditionalObs_mixin.__init__(self,{'ConditionalObservables':set([self._SiderealPhase, self._B_Pz])})

        o = {'SiderealPhase': self._SiderealPhase
             ,'B_Pz'        : self._B_Pz
             ,'SinX'        : self._parseArg('SinX', kwargs, Title = 'SinX', Value = ParCPT.pop('SinX'), ObjectType = 'ConstVar')
             ,'DaY'         : self._parseArg('DaY' , kwargs, Title = 'CPT Component - Y', Value = CPTs['DaY']['Val'], MinMax = (CPTs['DaY']['Min'],CPTs['DaY']['Max']) )
             ,'DaX'         : self._parseArg('DaX' , kwargs, Title = 'CPT Component - X', Value = CPTs['DaX']['Val'], MinMax = (CPTs['DaX']['Min'],CPTs['DaX']['Max']) )
             ,'Da0-0.38DaZ' : self._parseArg('Da0-0.38DaZ',kwargs,Title = 'CPT Da0-0.38DaZ',Value = CPTs['Da0-0.38DaZ']['Val'], MinMax = (CPTs['Da0-0.38DaZ']['Min'],CPTs['Da0-0.38DaZ']['Max']) )
             ,'dM'          : kwargs.pop('dM')
             ,'dGamma'      : kwargs.pop('dGamma')
             }
        self._dict = dict()
        for var in o.keys(): self._dict[var] = o[var]

        #\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
        #                                                                                                                                                 #
        #                                                  Formula for the Z(CPT Parameter)                                                               #
        # Z =(dM / (dM^{2} + 0.25*dGamma^{2}) * Pz/m0 * ( Da0 + DaZ*CosX + DaY*SinX*sin(SiderealPhase) +  DaX*SinX*cos(SiderealPhase) )                   #
        #                                                                                                                                                 #
        # COMMENTS:                                                                                                                                       #
        # For Colimated Analysis                                                                                                                          #
        # Where in this case: beta == 1 with very good approximation                                                                                      #
        # And for gamma = sqrt( 1 + (P/m)^2 ) == P/m again it is a very valid approximation                                                               #
        #                                                                                                                                                 #
        #\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

        # The mass of B_{s} is taken 5366.77 PDG 2012

        formula  = '@0  / ( @0**2 + 0.25*@1**2 ) * @2*1./5366.77 * ( @3 + @4*@5*sin(@6) + @7*@5*cos(@6))'
        arg      = [o.pop(i) for i in ('dM','dGamma','B_Pz','Da0-0.38DaZ','DaY','SinX','SiderealPhase','DaX')]

        self._parseArg('CPTSiderealVariations', kwargs, Title = 'Re(Z) param. CPT parameter with Sidereal Variations'
                       ,Formula = formula, Arguments = arg, ObjectType = 'FormulaVar')

        CPTPar_s.__init__(self, Re_Z = self._CPTSiderealVariations)
        self._check_extraneous_kw( kwargs )

    def cptParameters(self,par):
        assert par in self._dict.keys()
        return self._dict[par]


class _CPTSiderealVariations_f ( CPTPar_s , _util_conditionalObs_mixin, Pdf ):
    def __init__(self, **kwargs ):

        self._parseArg('SiderealPhase',kwargs, Title = 'SiderealPhase', Observable = True, Unit = 'rad', Value =0., MinMax = (0., 1e+30 ))
        self._parseArg('B_P'    ,kwargs, Title = 'B_P'    , Observable = True, Unit = 'MeV', Value =0., MinMax = (0.,1e+30 ))
        self._parseArg('B_theta',kwargs, Title = 'B_theta', Observable = True, Unit = 'rad', Value =0., MinMax = (0.,1e+30))
        self._parseArg('B_phi'  ,kwargs, Title = 'B_phi'  , Observable = True, Unit = 'rad', Value =0., MinMax = (-1e+30,1e+30 ))

        _util_conditionalObs_mixin.__init__(self,{'ConditionalObservables':set([self._SiderealPhase, self._B_P,self._B_theta,self._B_phi])})

        o = {'SiderealPhase': self._SiderealPhase
             ,'B_P'        : self._B_P
             ,'B_theta'    : self._B_theta
             ,'B_phi'      : self._B_phi
             ,'Phi0'       : self._parseArg('phi0', kwargs, Title = 'Phi0', Value = ParCPT.pop('Phi0'), ObjectType = 'ConstVar')
             ,'CosX'       : self._parseArg('CosX', kwargs, Title = 'CosX', Value = ParCPT.pop('CosX'), ObjectType = 'ConstVar')
             ,'SinX'       : self._parseArg('SinX', kwargs, Title = 'SinX', Value = ParCPT.pop('SinX'), ObjectType = 'ConstVar')
             ,'Da1'        : self._parseArg('Da1' , kwargs, Title = 'CPT Component Da0-0.38DaZ', Value = CPTs['Da1']['Val'], MinMax = (CPTs['Da1']['Min'],CPTs['Da1']['Max']) )
             ,'Da2'        : self._parseArg('Da2' , kwargs, Title = 'CPT Component 0.38Da0+DaZ', Value = CPTs['Da2']['Val'], MinMax = (CPTs['Da2']['Min'],CPTs['Da2']['Max']) )
             ,'DaY'        : self._parseArg('DaY' , kwargs, Title = 'CPT Component - Y', Value = CPTs['DaY']['Val'], MinMax = (CPTs['DaY']['Min'],CPTs['DaY']['Max']) )
             ,'DaX'        : self._parseArg('DaX' , kwargs, Title = 'CPT Component - X', Value = CPTs['DaX']['Val'], MinMax = (CPTs['DaX']['Min'],CPTs['DaX']['Max']) )
             ,'dM'         : kwargs.pop('dM')
             ,'dGamma'     : kwargs.pop('dGamma')
             }
        self._parseArg( 'phi_Plus_Phi_0', { }, Arguments = [o.pop('B_phi'),o.pop('Phi0')], ObjectType = 'Addition' )
        o['phi_Plus_Phi_0'] = self._phi_Plus_Phi_0


        self._dict = dict()
        for var in o.keys(): self._dict[var] = o[var]

        ##########################################################################################################################################################################
        #                                                   Formula for Z(CPT Parameter )                                                                                        #
        #                                                                                                                                                                        #
        #  Z =     (dM / (dM^{2} + 0.25*dGamma^{2}) * P/m0 *(                                                                                                                    #
        #          +Da1/(1+CosX**2) *{ (1 + CosX**2*cos(theta) - sin(theta)*cos(phi_Plus_Phi_0)*CosX*SinX) }                                                                     #
        #          +Da2/(1+CosX**2) *{ (-CosX + cos(theta)*CosX - sin(theta)*cos(phi_Plus_Phi_0)*SinX) }                                                                         # 
        #          +DaX *{ cos(SiderealPhase)*( cos(theta)*SinX + sin(theta)*cos(phi_Plus_Phi_0)*CosX ) - sin(SiderealPhase)*sin(phi + phi_0)*sin(theta) }                       #
        #          +DaY *{ sin(SiderealPhase)*( cos(theta)*SinX + sin(theta)*cos(phi_Plus_Phi_0)*CosX ) + cos(SiderealPhase)*sin(phi + phi_0)*sin(theta) } )                     #
        #                                                                                                                                                                        # 
        # COMMENTS:                                                                                                                                                              #
        # Parameters Da1 and Da2 refer to a new parametrization of the CPT violation coefsm in order to eliminate correlations.                                                  #
        # For not Colimated Analysis                                                                                                                                             #
        # For the beta and gamma the same approximations as in the previous formula are made                                                                                     #
        # phi and theta represent the angles of the B mesons in the X-Y plane and Z axis respectively                                                                            #
        # For Ph_0 is analysis note                                                                                                                                              #
        ##########################################################################################################################################################################

        # The mass of B_{s} is taken 5366.77 PDG 2012

        fac = '@0 / ( @0**2 + 0.25*@1**2 ) * @2*1./5366.77 *('
        par1= '     @3*1./(1+@4**2)    * (  1    + @4**2 * cos(@5) - sin(@5)*cos(@6)*@4*@7  )'
        par2= '+    @8*1./(1+@4**2)    * ( -1*@4 + cos(@5)*@4      - sin(@5)*cos(@6)*@7     ) '
        par3= '+ (  @9                 * (  cos(@10)*( cos(@5)*@7  + sin(@5)*cos(@6)*@4     ) - sin(@10)*sin(@6)*sin(@5) ) )'
        par4= '+ (  @11                * (  sin(@10)*( cos(@5)*@7  + sin(@5)*cos(@6)*@4     ) + cos(@10)*sin(@6)*sin(@5) ) ) )' 
        
        formula = fac + par1 + par2 + par3 + par4

        arg    = [o.pop(i) for i in ('dM','dGamma','B_P','Da1','CosX','B_theta','phi_Plus_Phi_0','SinX','Da2','DaX','SiderealPhase','DaY')]

        self._parseArg('CPTSiderealVariations', kwargs, Title = 'Re(Z) param. CPT parameter with Sidereal Variations'
                       ,Formula = formula, Arguments = arg, ObjectType = 'FormulaVar')


        CPTPar_s.__init__(self, Re_Z = self._CPTSiderealVariations)

    def cptParameters(self,par):
        assert par in self._dict.keys()
        return self._dict[par]


class CPParam ( _util_parse_mixin ):
    def __init__( self, **kwargs ) :
        for coef in 'CDS' : setattr( self, '_' + coef, kwargs.pop(coef) )
        self._ampNames = kwargs.pop( 'AmplitudeNames', None )

        if self._ampNames :
            for coefDict in [ 'RPlusDict', 'RMinDict', 'RReDict', 'RImDict' ] : setattr( self, '_' + coefDict, kwargs.pop(coefDict) )

    def __getitem__( self, kw ) : return getattr( self, '_' + kw )

    def CPVInDecay(self) : return True if self._ampNames else False
    def AmplitudeNames(self) : return self._ampNames

    def C(self) : return self._C
    def D(self) : return self._D
    def S(self) : return self._S
    def R( self, CPVDecInd, amp0Ind, amp1Ind ) :
        if not self.CPVInDecay() : return None

        assert CPVDecInd in ( 'plus', 'min', 'Re', 'Im' )\
            , 'P2VV - ERROR: CPParam.R(): valid CP violation in decay parameter indices are "plus", "min", "Re" or "Im" (got "%s")'\
              % CPVDecInd
        assert amp0Ind in self._ampNames and amp1Ind in self._ampNames\
            , 'P2VV - ERROR: CPParam.R(): valid amplitude indices are "%s" (got "%s" and "%s")'\
              % ( '", "'.join( amp for amp in self._ampNames ), amp0Ind, amp1Ind )

        return self._RPlusDict[ ( amp0Ind, amp1Ind ) ] if CPVDecInd == 'plus'\
          else self._RMinDict[  ( amp0Ind, amp1Ind ) ] if CPVDecInd == 'min'\
          else self._RReDict[   ( amp0Ind, amp1Ind ) ] if CPVDecInd == 'Re'\
          else self._RImDict[   ( amp0Ind, amp1Ind ) ]

class CDS_CPParam( CPParam ) :
    def __init__( self, **kwargs ) :
        self._parseArg('C', kwargs,  Title = 'CPV param. C', Value = CVal, Error = CErr, MinMax = ( -1., 1. ) )
        self._parseArg('D', kwargs,  Title = 'CPV param. D', Value = DVal, Error = DErr, MinMax = ( -2., 2. ) )
        self._parseArg('S', kwargs,  Title = 'CPV param. S', Value = SVal, Error = SErr, MinMax = ( -2., 2. ) )
        self._check_extraneous_kw( kwargs )

class LambdaCarth_CPParam( CPParam ) :
    def __init__( self, **kwargs ) :
        self._parseArg( 'ReLambdaCP', kwargs,  Title = 'CPV param. Re(lambda)', Value = ReLambVal, Error = ReLambErr
                       , MinMax = ( -RooInf, +RooInf ) )
        self._parseArg( 'ImLambdaCP', kwargs,  Title = 'CPV param. Im(lambda)', Value = ImLambVal, Error = ImLambErr
                       , MinMax = ( -RooInf, +RooInf ) )

        CPParam.__init__(self, C = self._parseArg( 'C', kwargs, Formula = '(1. - @0*@0 - @1*@1) / (1. + @0*@0 + @1*@1)'
                                                  , Arguments = [ self._ReLambdaCP, self._ImLambdaCP ], ObjectType = 'FormulaVar' )
                             , D = self._parseArg( 'D', kwargs, Formula = '-2. * @0 / (1. + @0*@0 + @1*@1)'
                                                  , Arguments = [ self._ReLambdaCP, self._ImLambdaCP ], ObjectType = 'FormulaVar' )
                             , S = self._parseArg( 'S', kwargs, Formula = '2. * @1 / (1. + @0*@0 + @1*@1)'
                                                  , Arguments = [ self._ReLambdaCP, self._ImLambdaCP ], ObjectType = 'FormulaVar' )
                        )

        self._check_extraneous_kw( kwargs )

class LambdaAbsArg_CPParam( CPParam ) :
    def __init__( self, **kwargs ) :
        self._parseArg( 'lambdaCP', kwargs,  Title = 'CPV param. |lambda|', Value = lambVal, Error = lambErr, MinMax = ( 0.,      5.    ) )
        self._parseArg( 'phiCP',    kwargs,  Title = 'CPV param. phi',      Value = phiVal,  Error = phiErr,  MinMax = (-RooInf, +RooInf) )
        CPParam.__init__(self, C = self._parseArg( 'C', kwargs, Formula = '(1. - @0*@0) / (1. + @0*@0)'
                                                   , Arguments = [ self._lambdaCP ], ObjectType = 'FormulaVar' )
                         , D = self._parseArg( 'D', kwargs, Formula = '-2. * @0 * cos(@1) / (1. + @0*@0)'
                                               , Arguments = [ self._lambdaCP, self._phiCP ], ObjectType = 'FormulaVar' )
                         , S = self._parseArg( 'S', kwargs, Formula = '-2. * @0 * sin(@1) / (1. + @0*@0)'
                                               , Arguments = [ self._lambdaCP, self._phiCP ], ObjectType = 'FormulaVar' )
                         )

        self._check_extraneous_kw( kwargs )

class LambdaSqArg_CPParam( CPParam ) :
    def __init__( self, **kwargs ) :
        self._parseArg( 'lambdaCPSq', kwargs,  Title = 'CPV param. |lambda|^2', Value = lambSqVal, Error = lambSqErr
                       , MinMax = ( 0., 25. ) )
        self._parseArg( 'phiCP',      kwargs,  Title = 'CPV param. phi',        Value = phiVal,    Error = phiErr
                       , MinMax = ( -RooInf, +RooInf ) )

        CPParam.__init__(self, C = self._parseArg( 'C', kwargs, Formula = '(1. - @0) / (1. + @0)'
                                                  , Arguments = [ self._lambdaCPSq ], ObjectType = 'FormulaVar' )
                             , D = self._parseArg( 'D', kwargs, Formula = '-2. * sqrt(@0) * cos(@1) / (1. + @0)'
                                                  , Arguments = [ self._lambdaCPSq, self._phiCP ], ObjectType = 'FormulaVar' )
                             , S = self._parseArg( 'S', kwargs, Formula = '-2. * sqrt(@0) * sin(@1) / (1. + @0)'
                                                  , Arguments = [ self._lambdaCPSq, self._phiCP ], ObjectType = 'FormulaVar' )
                        )
        self._check_extraneous_kw( kwargs )

class LambdaArg_CPParam( CPParam ) :
    def __init__( self, **kwargs ) :
        self._parseArg( 'phiCP', kwargs, Title = 'CPV param. phi', Value = phiVal, Error = phiErr, MinMax = ( -RooInf, +RooInf ) )
        CPParam.__init__(self, C = self._parseArg( 'C', kwargs, Value = 0., ObjectType = 'ConstVar' )
                             , D = self._parseArg( 'D', kwargs, Formula = '-cos(@0)', Arguments = [self._phiCP], ObjectType = 'FormulaVar')
                             , S = self._parseArg( 'S', kwargs, Formula = '-sin(@0)', Arguments = [self._phiCP], ObjectType = 'FormulaVar')
                        )
        self._check_extraneous_kw( kwargs )

class CPVDecay_CPParam( CPParam ) :
    def __init__( self, **kwargs ) :
        ampNames   = kwargs.pop('AmplitudeNames')
        amps       = kwargs.pop('Amplitudes')
        magNames   = kwargs.pop('MagnitudeNames')
        phaseNames = kwargs.pop('PhaseNames')

        RPlusDict = { }
        RMinDict  = { }
        RReDict   = { }
        RImDict   = { }
        try :   from itertools import combinations_with_replacement as cwr  # this requires python 2.7 or later
        except: from P2VV.Compatibility import cwr
        for ampComb in cwr( ampNames, 2 ) :
            eta0 = amps[ ampComb[0] ].CP
            eta1 = amps[ ampComb[1] ].CP

            RPlusDict[ampComb] = tuple( [ self._parseArg(  '%sRPlus_%s_%s' % ( comp, ampComb[0], ampComb[1] ), kwargs
                                                         , Formula = '(%s@0*@1*%s(@2-@3)) / 2.'\
                                                                     % ( '1. + ' if comp == 'Re' and eta0 == eta1\
                                                                         else '1. - ' if comp == 'Re' and eta0 != eta1\
                                                                         else '' if eta0 == eta1 else '-'
                                                                        , func
                                                                       )
                                                         , Arguments = [  getattr( self, '_%s' % magNames[   ampComb[0] ] )
                                                                        , getattr( self, '_%s' % magNames[   ampComb[1] ] )
                                                                        , getattr( self, '_%s' % phaseNames[ ampComb[0] ] )
                                                                        , getattr( self, '_%s' % phaseNames[ ampComb[1] ] )
                                                                       ]
                                                         , ObjectType = 'FormulaVar'
                                                        ) for ( comp, func ) in [ ( 'Re', 'cos' ), ( 'Im', 'sin' ) ]
                                      ] )
            RMinDict[ampComb]  = tuple( [ self._parseArg(  '%sRMin_%s_%s' % ( comp, ampComb[0], ampComb[1] ), kwargs
                                                         , Formula = '(%s@0*@1*%s(@2-@3)) / 2.'\
                                                                     % ( '1. - ' if comp == 'Re' and eta0 == eta1\
                                                                         else '1. + ' if comp == 'Re' and eta0 != eta1\
                                                                         else '-' if eta0 == eta1 else ''
                                                                        , func
                                                                       )
                                                         , Arguments = [  getattr( self, '_%s' % magNames[   ampComb[0] ] )
                                                                        , getattr( self, '_%s' % magNames[   ampComb[1] ] )
                                                                        , getattr( self, '_%s' % phaseNames[ ampComb[0] ] )
                                                                        , getattr( self, '_%s' % phaseNames[ ampComb[1] ] )
                                                                       ]
                                                         , ObjectType = 'FormulaVar'
                                                        ) for ( comp, func ) in [ ( 'Re', 'cos' ), ( 'Im', 'sin' ) ]
                                      ] )
            RReDict[ampComb]   = tuple( [ self._parseArg(  '%sRRe_%s_%s' % ( comp, ampComb[0], ampComb[1] ), kwargs
                                                         , Formula = '(%s@0*%s(@2) %s @1*%s(-@3)) / 2.'\
                                                                     % ( '' if eta0 > 0 else '-', func, '+' if eta1 > 0 else '-', func )
                                                         , Arguments = [  getattr( self, '_%s' % magNames[   ampComb[0] ] )
                                                                        , getattr( self, '_%s' % magNames[   ampComb[1] ] )
                                                                        , getattr( self, '_%s' % phaseNames[ ampComb[0] ] )
                                                                        , getattr( self, '_%s' % phaseNames[ ampComb[1] ] )
                                                                       ]
                                                         , ObjectType = 'FormulaVar'
                                                        ) for ( comp, func ) in [ ( 'Re', 'cos' ), ( 'Im', 'sin' ) ]
                                      ] )
            RImDict[ampComb]   = tuple( [ self._parseArg(  '%sRIm_%s_%s' % ( comp, ampComb[0], ampComb[1] ), kwargs
                                                         , Formula = '(%s@0*%s(@2) %s @1*%s(-@3)) / 2.'\
                                                                     % (  '-' if ( eta0 > 0 and comp == 'Re' )\
                                                                              or ( eta0 < 0 and comp == 'Im' ) else ''
                                                                        , func
                                                                        , '+' if ( eta1 > 0 and comp == 'Re' )\
                                                                              or ( eta1 < 0 and comp == 'Im' ) else '-'
                                                                        , func
                                                                       )
                                                         , Arguments = [  getattr( self, '_%s' % magNames[   ampComb[0] ] )
                                                                        , getattr( self, '_%s' % magNames[   ampComb[1] ] )
                                                                        , getattr( self, '_%s' % phaseNames[ ampComb[0] ] )
                                                                        , getattr( self, '_%s' % phaseNames[ ampComb[1] ] )
                                                                       ]
                                                         , ObjectType = 'FormulaVar'
                                                        ) for ( comp, func ) in [ ( 'Re', 'sin' ), ( 'Im', 'cos' ) ]
                                      ] )

        self._check_extraneous_kw( kwargs )
        CPParam.__init__(  self, AmplitudeNames = ampNames
                         , C = self._parseArg(  'C', kwargs
                                              , Formula = '(1. - @0*@0) / (1. + @0*@0)'
                                              , Arguments = [  getattr( self, '_%s' % magNames['mix'] ) ]
                                              , ObjectType = 'FormulaVar'
                                             )
                         , D = self._parseArg(  'D', kwargs
                                              , Formula = '-2. * @0 * cos(@1) / (1. + @0*@0)'
                                              , Arguments = [ getattr( self, '_%s' % magNames['mix'] )
                                                             , getattr( self, '_%s' % phaseNames['mix'] ) ]
                                              , ObjectType = 'FormulaVar'
                                             )
                         , S = self._parseArg(  'S', kwargs
                                              , Formula = '-2. * @0 * sin(@1) / (1. + @0*@0)'
                                              , Arguments = [ getattr( self, '_%s' % magNames['mix'] )
                                                             , getattr( self, '_%s' % phaseNames['mix'] ) ]
                                              , ObjectType = 'FormulaVar'
                                             )
                         , RPlusDict = RPlusDict
                         , RMinDict  = RMinDict
                         , RReDict   = RReDict
                         , RImDict   = RImDict
                        )

class LambdaAbsArg_CPVDecay_CPParam( CPVDecay_CPParam ) :
    def __init__( self, **kwargs ) :
        ampNames   = kwargs.pop('AmplitudeNames')
        amps       = kwargs.pop('Amplitudes')
        magNames   = dict( mix = 'rhoCP_m'    )
        phaseNames = dict( mix = 'phiCPRel_m' )
        self._parseArg( 'rhoCP_m', kwargs, Title = 'CPV in mixing param. |rho_m|', Value = 1., Error = lambErr, MinMax = ( 0., 5. )
                       , Constant = True )
        self._parseArg( 'phiCPRel_m', kwargs, Title = 'CPV in mixing param. phi_m - phi_m', Value = 0., ObjectType = 'ConstVar' )

        for amp in ampNames :
            magNames[amp]   = 'rhoCP_%s' % amp
            phaseNames[amp] = 'phiCP_%s' % amp
            self._parseArg( 'rhoCP_%s' % amp, kwargs, Title = 'CPV in decay param. |rho_%s|' % amp, Value = lambVal, Error = lambErr
                           , MinMax = ( 0., 5. ) )
            self._parseArg( 'phiCP_%s' % amp, kwargs, Title = 'CPV in decay param. phi_%s + phi_m' % amp, Value = 0., Error = phiErr
                           , MinMax = ( -RooInf, +RooInf ) )

        self._check_extraneous_kw( kwargs )
        CPVDecay_CPParam.__init__( self, AmplitudeNames = ampNames, Amplitudes = amps, MagnitudeNames = magNames, PhaseNames = phaseNames )

class LambdaAbsArgRel_CPVDecay_CPParam( CPVDecay_CPParam ) :
    def __init__( self, **kwargs ) :
        ampNames   = kwargs.pop('AmplitudeNames')
        amps       = kwargs.pop('Amplitudes')
        magNames   = dict( mix = 'rhoCP_m' )
        phaseNames = dict( mix = 'phiCP_m' )
        self._parseArg( 'rhoCP_m', kwargs, Title = 'CPV in mixing param. |rho_m|', Value = 1., Error = lambErr, MinMax = ( 0., 5. )
                       , Constant = True )
        self._parseArg( 'phiCP_m', kwargs, Title = 'CPV in mixing param. phi_m + phi_0', Value = phiVal,  Error = phiErr
                       , MinMax = ( -RooInf, +RooInf ) )

        for ind, amp in enumerate(ampNames) :
            magNames[amp]   = 'rhoCP_%s'    % amp
            phaseNames[amp] = 'phiCPRel_%s' % amp
            self._parseArg( 'rhoCP_%s' % amp, kwargs, Title = 'CPV in decay param. |rho_%s|' % amp, Value = 1., Error = lambErr
                           , MinMax = ( 0., 5. ) )
            if ind == 0 :
                self._parseArg( 'phiCPRel_%s' % amp, kwargs, Title = 'CPV in decay param. phi_%s - phi_0' % amp, Value = 0.
                               , ObjectType = 'ConstVar' )
            else :
                self._parseArg( 'phiCPRel_%s' % amp, kwargs, Title = 'CPV in decay param. phi_%s - phi_0' % amp, Value = 0., Error = phiErr
                               , MinMax = ( -RooInf, +RooInf ) )

        self._check_extraneous_kw( kwargs )
        CPVDecay_CPParam.__init__( self, AmplitudeNames = ampNames, Amplitudes = amps, MagnitudeNames = magNames, PhaseNames = phaseNames )


class ACP_AssymetryParametrization( _util_parse_mixin ):
    # Implimentation based on LHCb-ANA-2015-013-v6
    def __init__( self, **kwargs ) :
        amps    = kwargs.pop('Amplitudes')

        ACP0    = self._parseArg( 'ACP0',    kwargs, Title = 'CP assymetry zero',          Value = 0., Error = 0.06, MinMax = ( -1, 1 ) , Constant = False )
        ACPpar  = self._parseArg( 'ACPpar',  kwargs, Title = 'CP assymetry parallel',      Value = 0., Error = 0.15, MinMax = ( -1, 1 ) , Constant = False )
        ACPperp = self._parseArg( 'ACPperp', kwargs, Title = 'CP assymetry perpendicular', Value = 0., Error = 0.10, MinMax = ( -1, 1 ) , Constant = False )
        ACPS    = self._parseArg( 'ACPS',    kwargs, Title = 'CP assymetry s-wave',        Value = 0., Error = 0.10, MinMax = ( -1, 1 ) , Constant = False )

        # p-wave Acp fraction
        fACP_Pwave = self._parseArg( 'fACP_Pwave', kwargs , Title = 'Acp fraction for p-wave'
                                    , Formula = '@0*@3 + @1*@4 + @2*@5'
                                    , Arguments = [ amps['A0'], amps['Aperp'], amps['Apar'], ACP0, ACPperp, ACPpar ]
                                    , ObjectType = 'FormulaVar'
                                )

        # s + p wave Acp fraction
        fACP =  self._parseArg( 'fACP', kwargs , Title = 'Acp fraction for s + pwave'
                                       , Formula = '@0*@1 + (1. - @0)*@2'
                                       , Arguments = [ amps['AS'], ACPS, fACP_Pwave ]
                                       , ObjectType = 'FormulaVar'
                                   )

        # floating yield
        Yield_2011 = self._parseArg('Yield_2011',  kwargs, Title = '2011 yield ', MinMax = ( 0, +RooInf ) , Constant = False )
        Yield_2012 = self._parseArg('Yield_2012',  kwargs, Title = '2012 yield ', MinMax = ( 0, +RooInf ) , Constant = False )

        # expected yields from cp assymymetry
        Yield_CP_2011_pos = self._parseArg( 'Yield_CP_2011_pos', kwargs , Title = 'cp assymymetry induced yield 2011 pos'
                                            , Formula = '@0 * 0.5 * (1. + @1)'
                                            , Arguments = [ Yield_2011, fACP ]
                                            , ObjectType = 'FormulaVar'
                                        )

        Yield_CP_2012_pos = self._parseArg( 'Yield_CP_2012_pos', kwargs , Title = 'cp assymymetry induced yield 2012 pos'
                                            , Formula = '@0 * 0.5 * (1. + @1)'
                                            , Arguments = [ Yield_2012, fACP ]
                                            , ObjectType = 'FormulaVar'
                                        )

        Yield_CP_2011_neg = self._parseArg( 'Yield_CP_2011_neg', kwargs , Title = 'cp assymymetry induced yield 2011 neg'
                                            , Formula = '@0 - @1'
                                            , Arguments = [ Yield_2011, Yield_CP_2011_pos ]
                                            , ObjectType = 'FormulaVar'
                                        )

        Yield_CP_2012_neg = self._parseArg( 'Yield_CP_2012_neg', kwargs , Title = 'cp assymymetry induced yield 2012 neg'
                                            , Formula = '@0 - @1'
                                            , Arguments = [ Yield_2012, Yield_CP_2012_pos ]
                                            , ObjectType = 'FormulaVar'
                                        )

        # expected yields from cp + production + detection assymetry
        A_D = self._parseArg('A_D',  kwargs, Title = 'detection assymetry',  Value = 0 , Constant = True )
        A_P = self._parseArg('A_P',  kwargs, Title = 'production assymetry', Value = 0 , Constant = True )

        Yield_tot_2011_pos = self._parseArg('Yield_tot_2011_pos',  kwargs, Title = 'total expected yield 2011 pos'
                                            , Formula = '@0*(1 + @1 - @2)'
                                            , Arguments = [ Yield_CP_2011_pos, A_D, A_P ]
                                            , ObjectType = 'FormulaVar'
                                        )

        Yield_tot_2012_pos = self._parseArg('Yield_tot_2012_pos',  kwargs, Title = 'total expected yield 2012 pos'
                                            , Formula = '@0*(1 + @1 - @2)'
                                            , Arguments = [ Yield_CP_2012_pos, A_D, A_P ]
                                            , ObjectType = 'FormulaVar'
                                        )

        Yield_tot_2011_neg = self._parseArg('Yield_tot_2011_neg',  kwargs, Title = 'total expected yield 2011 neg'
                                            , Formula = '@0*(1 - @1 + @2)'
                                            , Arguments = [ Yield_CP_2011_neg, A_D, A_P ]
                                            , ObjectType = 'FormulaVar'
                                        )

        Yield_tot_2012_neg = self._parseArg('Yield_tot_2012_neg',  kwargs, Title = 'total expected yield 2012 neg'
                                            , Formula = '@0*(1 - @1 + @2)'
                                            , Arguments = [ Yield_CP_2012_neg, A_D, A_P ]
                                            , ObjectType = 'FormulaVar'
                                        )

        self._ExpYields = dict(pos2011=Yield_tot_2011_pos, pos2012=Yield_tot_2012_pos, neg2011=Yield_tot_2011_neg, neg2012=Yield_tot_2012_neg )

    def __getitem__( self, kw ) : return getattr( self, '_' + kw )

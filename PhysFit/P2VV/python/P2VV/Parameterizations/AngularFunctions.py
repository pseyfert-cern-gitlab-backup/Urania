###########################################################################################################################################
## P2VVParameterizations.AngularFunctions: Decay angles and functions of decay angles                                                    ##
##                                                                                                                                       ##
## authors:                                                                                                                              ##
##   GR,  Gerhard Raven,      Nikhef & VU, Gerhard.Raven@nikhef.nl                                                                       ##
##   JvL, Jeroen van Leerdam, Nikhef,      j.van.leerdam@nikhef.nl                                                                       ##
##                                                                                                                                       ##
###########################################################################################################################################

#TODO: inherit from UserDict mixin instead of wrapping & forwarding...
class AngularFunctions :
    def __init__(self) :         self._d = dict()
    def __getitem__(self,k) :    return self._d[k]
    def __setitem__(self,k,v) :  self._d[k] = v
    def __contains__(self,k) :   return k in self._d
    def keys(self) :             return self._d.keys()
    def iterkeys(self) :         return self._d.iterkeys()
    def items(self) :            return self._d.items()
    def iteritems(self) :        return self._d.iteritems()
    def values(self) :           return self._d.values()
    def itervalues(self) :       return self._d.itervalues()

from collections import OrderedDict
from P2VV.Parameterizations.GeneralUtils import _util_parse_mixin
# SB: This class has been modified to make it non "mu mu h h" specific
# This needed an OrderedDict since the P2VV basis PDF takes the angles dictionary
# and loops over the keys to determine build the "build string"
class AngleDefinitions( _util_parse_mixin ) :
    def __init__( self , **kwargs ) :
        self.angles = dict( (i,kwargs.pop(i)) for i in kwargs.keys() if i!="functions" )
        self.functions = kwargs.pop('functions')


class JpsiphiHelicityAngles( AngleDefinitions ) :
    def __init__( self, **kwargs ) :
        from math import pi
        d = OrderedDict(  [('cpsi'   , self._parseArg( 'cpsi',   kwargs, SingleArgKey = 'Name', Name = 'helcosthetaK'
                                         , Title = 'cos(#theta_{K})',   MinMax = ( -1,  1 ),  Observable = True ))
             , ('ctheta' , self._parseArg( 'ctheta', kwargs, SingleArgKey = 'Name', Name = 'helcosthetaL'
                                         , Title = 'cos(#theta_{#mu})', MinMax = ( -1,  1 ),  Observable = True ))
             , ('phi'    , self._parseArg( 'phi',    kwargs, SingleArgKey = 'Name', Name = 'phi'
                                         , Title = '#phi_{h}',          MinMax = ( -pi, pi ), Observable = True, Unit = 'rad' ))]
            )
        coef = kwargs.pop( 'DummyCoef', False )
        self._check_extraneous_kw(kwargs)
        d['functions'] = JpsiphiTransversityAmplitudesHelicityAngles( Angles = d, DummyCoef = coef )
        AngleDefinitions.__init__(self, **d )


class JpsiphiTransversityAngles( AngleDefinitions ) :
    def __init__( self, **kwargs ) :
        from math import pi
        d = OrderedDict(  [ ('cpsi' ,   self._parseArg( 'cpsi',   kwargs, SingleArgKey = 'Name', Name='trcospsi'
                                        , Title = 'cos(#psi_{tr})',   MinMax=( -1,  1 ),  Observable = True ))
            , ('ctheta' , self._parseArg( 'ctheta', kwargs, SingleArgKey = 'Name', Name='trcostheta'
                                        , Title = 'cos(#theta_{tr})', MinMax=( -1,  1 ),  Observable = True ))
            , ('phi'   ,  self._parseArg( 'phi',    kwargs, SingleArgKey = 'Name', Name='trphi'
                                        , Title = '#phi_{tr}',        MinMax=( -pi, pi ), Observable = True ))]
            )
        coef = kwargs.pop( 'DummyCoef', False )
        d['functions'] = JpsiphiTransversityAmplitudesTransversityAngles( Angles = d, DummyCoef = coef )
        self._check_extraneous_kw(kwargs)
        AngleDefinitions.__init__(self, **d )


class JpsiKstHelicityAngles( AngleDefinitions ) :
    def __init__( self, **kwargs ) :
        from math import pi
        d = OrderedDict(  [ (  'cpsi'   , self._parseArg( 'cpsi',   kwargs, SingleArgKey = 'Name', Name = 'helcosthetaK'
                                         , Title = 'cos(#theta_{K})',   MinMax = ( -1,  1 ),  Observable = True ))
             , ('ctheta' , self._parseArg( 'ctheta', kwargs, SingleArgKey = 'Name', Name = 'helcosthetaL'
                                         , Title = 'cos(#theta_{#mu})', MinMax = ( -1,  1 ),  Observable = True ))
             , ('phi'    , self._parseArg( 'phi',    kwargs, SingleArgKey = 'Name', Name = 'helphi'
                                         , Title = '#phi_{h}',          MinMax = ( -pi, pi ), Observable = True, Unit = 'rad' ))]
            )
        coef = kwargs.pop( 'DummyCoef', False )
        self._check_extraneous_kw(kwargs)
        d['functions'] = JpsiKstTransversityAmplitudesHelicityAngles( Angles = d, DummyCoef = coef )
        AngleDefinitions.__init__(self, **d )

class phiphiHelicityAngles( AngleDefinitions ) :
    def __init__( self, **kwargs ) :
        from math import pi
        d = OrderedDict(  [ (  'ctheta_1'   , self._parseArg( 'ctheta_1',   kwargs, SingleArgKey = 'Name', Name = 'ctheta_1'
                                         , Title = 'cos(#theta_{1})',   MinMax = ( -1,  1 ),  Observable = True ))
             , ('ctheta_2' , self._parseArg( 'ctheta_2', kwargs, SingleArgKey = 'Name', Name = 'ctheta_2'
                                         , Title = 'cos(#theta_{2})', MinMax = ( -1,  1 ),  Observable = True ))
             , ('phi'    , self._parseArg( 'phi',    kwargs, SingleArgKey = 'Name', Name = 'phi'
                                         , Title = 'phi',          MinMax = ( -3.15, 3.15 ), Observable = True ))]
            )
        coef = kwargs.pop( 'DummyCoef', False )
        raw = kwargs.pop( 'Raw', False )
        csp = kwargs.pop( 'CSP' )
        self._check_extraneous_kw(kwargs)
        if raw:
            print "With raw, no CSP has been coded up yet, be aware"
            d['functions'] = phiphiTransversityAmplitudesHelicityAnglesRaw( Angles = d, DummyCoef = coef)
        else:
            d['functions'] = phiphiTransversityAmplitudesHelicityAngles( Angles = d, DummyCoef = coef, CSP = csp )
        AngleDefinitions.__init__(self, **d )


class JpsiKstTransversityAngles( AngleDefinitions ) :
    def __init__( self, **kwargs ) :
        from math import pi
        d = OrderedDict(  [ ( 'cpsi' ,   self._parseArg( 'cpsi',   kwargs, SingleArgKey = 'Name', Name='trcospsi'
                                        , Title = 'cos(#psi_{tr})',   MinMax=( -1,  1 ),  Observable = True ))
            , ('ctheta' , self._parseArg( 'ctheta', kwargs, SingleArgKey = 'Name', Name='trcostheta'
                                        , Title = 'cos(#theta_{tr})', MinMax=( -1,  1 ),  Observable = True ))
            , ('phi'   ,  self._parseArg( 'phi',    kwargs, SingleArgKey = 'Name', Name='trphi'
                                        , Title = '#phi_{tr}',        MinMax=( -pi, pi ), Observable = True ))]
            )
        coef = kwargs.pop( 'DummyCoef', False )
        d['functions'] = JpsiKstTransversityAmplitudesTransversityAngles( Angles = d, DummyCoef = coef )
        self._check_extraneous_kw(kwargs)
        AngleDefinitions.__init__(self, **d )


class JpsiphiTransversityAmplitudesHelicityAngles( AngularFunctions ) :
    def __init__( self, **kwargs ) :
        AngularFunctions.__init__(self)
        angles = kwargs.pop('Angles')
        coef   = kwargs.pop( 'DummyCoef', False )

        from P2VV.Parameterizations.GeneralUtils import getParNamePrefix
        namePF = getParNamePrefix(True)

        # define function to build angular function; create dummy coefficient if we need to split the angular efficiency functions later
        from P2VV.RooFitWrappers import P2VVAngleBasis, Addition, RealVar
        dummy = RealVar( Name = namePF + 'angEffDummyCoef', Value = 1. ) if coef else None
        _ba = lambda name, args :\
            Addition( namePF + name, [ P2VVAngleBasis( Name = namePF + name, Angles = angles, Indices = arg[0], FixedCoef = arg[1]
                                                      , Coefficient = dummy ) for arg in args ] )

        # TODO: generate the following table straight from the physics using PS->(VV,VS) ->ffss  (V=spin 1, f=spin 1/2, PS,S,s = spin 0)
        from math import sqrt
        angFuncs = { ('A0',   'A0')    :  ( _ba('Re_ang_A0_A0',           [ ( ( 0, 0, 0,  0 ),        4.             )
                                                                          , ( ( 0, 0, 2,  0 ),       -sqrt( 16. / 5.))
                                                                          , ( ( 2, 0, 0,  0 ),        8.             )
                                                                          , ( ( 2, 0, 2,  0 ),       -sqrt( 64. / 5.))]), None)
                   , ('Apar', 'Apar')  :  ( _ba('Re_ang_Apar_Apar',       [ ( ( 2, 2, 0,  0 ),        2.             )
                                                                          , ( ( 2, 2, 2,  0 ),        sqrt(  1. / 5.))
                                                                          , ( ( 2, 2, 2,  2 ),       -sqrt(  3. / 5.))]), None)
                   , ('Aperp','Aperp') :  ( _ba('Re_ang_Aperp_Aperp',     [ ( ( 2, 2, 0,  0 ),        2.             )
                                                                          , ( ( 2, 2, 2,  0 ),        sqrt(  1. / 5.))
                                                                          , ( ( 2, 2, 2,  2 ),        sqrt(  3. / 5.))]), None)
                   , ('A0',   'Apar')  :  ( _ba('Re_ang_A0_Apar',         [ ( ( 2, 1, 2,  1 ),        sqrt( 24. / 5.))]), None)
                   , ('A0',   'Aperp') :  ( None, _ba('Im_ang_A0_Aperp',  [ ( ( 2, 1, 2, -1 ), -1. * -sqrt( 24. / 5.))]))
                   , ('Apar', 'Aperp') :  ( None, _ba('Im_ang_Apar_Aperp',[ ( ( 2, 2, 2, -2 ), -1. *  sqrt( 12. / 5.))]))
                   , ('AS',   'AS')    :  ( _ba('Re_ang_AS_AS',           [ ( ( 0, 0, 0,  0 ),        4.             )
                                                                          , ( ( 0, 0, 2,  0 ),       -sqrt( 16. / 5.))]), None)
                   , ('A0',   'AS')    :  ( _ba('Re_ang_A0_AS',           [ ( ( 1, 0, 0,  0 ),        sqrt(192.     ))
                                                                          , ( ( 1, 0, 2,  0 ),       -sqrt(192. / 5.))]), None)
                   , ('Apar', 'AS')    :  ( _ba('Re_ang_Apar_AS',         [ ( ( 1, 1, 2,  1 ),        sqrt( 72. / 5.))]), None)
                   , ('Aperp','AS')    :  ( None, _ba('Im_ang_Aperp_AS',  [ ( ( 1, 1, 2, -1 ), -1. *  sqrt( 72. / 5.))]))
                   }
        for k,v in angFuncs.iteritems() : self[k] = v


class JpsiphiTransversityAmplitudesTransversityAngles( AngularFunctions ) :
    def __init__( self, **kwargs ) :
        AngularFunctions.__init__(self)
        angles = kwargs.pop('Angles')
        coef   = kwargs.pop( 'DummyCoef', False )

        from P2VV.Parameterizations.GeneralUtils import getParNamePrefix
        namePF = getParNamePrefix(True)

        # define function to build angular function; create dummy coefficient if we need to split the angular efficiency functions later
        from P2VV.RooFitWrappers import P2VVAngleBasis, Addition, RealVar
        dummy = RealVar( Name = namePF + 'angEffDummyCoef', Value = 1. ) if coef else None
        _ba = lambda name, args :\
            Addition( namePF + name, [ P2VVAngleBasis( Name = namePF + name, Angles = angles, Indices = arg[0], FixedCoef = arg[1]
                                                      , Coefficient = dummy ) for arg in args ] )

        # TODO: generate the following table straight from the physics using PS->(VV,VS) ->ffss  (V=spin 1, f=spin 1/2, PS,S,s = spin 0)
        from math import sqrt
        angFuncs = { ('A0',   'A0')    :  ( _ba('Re_ang_A0_A0',           [ ( ( 0, 0, 0,  0 ),        4.             )
                                                                          , ( ( 0, 0, 2,  0 ),        sqrt(  4. / 5.))
                                                                          , ( ( 0, 0, 2,  2 ),       -sqrt( 12. / 5.))
                                                                          , ( ( 2, 0, 0,  0 ),        8.             )
                                                                          , ( ( 2, 0, 2,  0 ),        sqrt( 16. / 5.))
                                                                          , ( ( 2, 0, 2,  2 ),       -sqrt( 48. / 5.))]), None)
                   , ('Apar', 'Apar')  :  ( _ba('Re_ang_Apar_Apar',       [ ( ( 2, 2, 0,  0 ),        2.             )
                                                                          , ( ( 2, 2, 2,  0 ),        sqrt(  1. / 5.))
                                                                          , ( ( 2, 2, 2,  2 ),        sqrt(  3. / 5.))]), None)
                   , ('Aperp','Aperp') :  ( _ba('Re_ang_Aperp_Aperp',     [ ( ( 2, 2, 0,  0 ),        2.             )
                                                                          , ( ( 2, 2, 2,  0 ),       -sqrt(  4. / 5.))]), None)
                   , ('A0',   'Apar')  :  ( _ba('Re_ang_A0_Apar',         [ ( ( 2, 1, 2, -2 ),       -sqrt( 24. / 5.))]), None)
                   , ('A0',   'Aperp') :  ( None, _ba('Im_ang_A0_Aperp',  [ ( ( 2, 1, 2,  1 ),  -1. * sqrt( 24. / 5.))]))
                   , ('Apar', 'Aperp') :  ( None, _ba('Im_ang_Apar_Aperp',[ ( ( 2, 2, 2, -1 ),  -1. * sqrt( 12. / 5.))]))
                   , ('AS',   'AS')    :  ( _ba('Re_ang_AS_AS',           [ ( ( 0, 0, 0,  0 ),        4.             )
                                                                          , ( ( 0, 0, 2,  0 ),        sqrt(  4. / 5.))
                                                                          , ( ( 0, 0, 2,  2 ),       -sqrt( 12. / 5.))]),None)
                   , ('A0',   'AS')    :  ( _ba('Re_ang_A0_AS',           [ ( ( 1, 0, 0,  0 ),        sqrt(192.     ))
                                                                          , ( ( 1, 0, 2,  0 ),        sqrt( 48. / 5.))
                                                                          , ( ( 1, 0, 2,  2 ),       -sqrt(144. / 5.))]), None)
                   , ('Apar', 'AS')    :  ( _ba('Re_ang_Apar_AS',         [ ( ( 1, 1, 2, -2 ),       -sqrt( 72. / 5.))]), None)
                   , ('Aperp','AS')    :  ( None, _ba('Im_ang_Aperp_AS',  [ ( ( 1, 1, 2,  1 ), -1. * -sqrt( 72. / 5.))]))
                   }
        for k,v in angFuncs.iteritems() : self[k] = v


class JpsiKstTransversityAmplitudesHelicityAngles( AngularFunctions ) :
    def __init__( self, **kwargs ) :
        AngularFunctions.__init__(self)
        angles = kwargs.pop('Angles')
        coef   = kwargs.pop( 'DummyCoef', False )

        from P2VV.Parameterizations.GeneralUtils import getParNamePrefix
        namePF = getParNamePrefix(True)

        # define function to build angular function; create dummy coefficient if we need to split the angular efficiency functions later
        from P2VV.RooFitWrappers import P2VVAngleBasis, Addition, RealVar
        dummy = RealVar( Name = namePF + 'angEffDummyCoef', Value = 1. ) if coef else None
        _ba = lambda name, args :\
            Addition( namePF + name, [ P2VVAngleBasis( Name = namePF + name, Angles = angles, Indices = arg[0], FixedCoef = arg[1]
                                                      , Coefficient = dummy ) for arg in args ] )

        # TODO: generate the following table straight from the physics using PS->(VV,VS) ->ffss  (V=spin 1, f=spin 1/2, PS,S,s = spin 0)
        from math import sqrt
        angFuncs = { ('A0',   'A0')    :  ( _ba('Re_ang_A0_A0',           [ ( ( 0, 0, 0,  0 ),        4.             )
                                                                          , ( ( 0, 0, 2,  0 ),       -sqrt( 16. / 5.))
                                                                          , ( ( 2, 0, 0,  0 ),        8.             )
                                                                          , ( ( 2, 0, 2,  0 ),       -sqrt( 64. / 5.))]), None)
                   , ('Apar', 'Apar')  :  ( _ba('Re_ang_Apar_Apar',       [ ( ( 2, 2, 0,  0 ),        2.             )
                                                                          , ( ( 2, 2, 2,  0 ),        sqrt(  1. / 5.))
                                                                          , ( ( 2, 2, 2,  2 ),       -sqrt(  3. / 5.))]), None)
                   , ('Aperp','Aperp') :  ( _ba('Re_ang_Aperp_Aperp',     [ ( ( 2, 2, 0,  0 ),        2.             )
                                                                          , ( ( 2, 2, 2,  0 ),        sqrt(  1. / 5.))
                                                                          , ( ( 2, 2, 2,  2 ),        sqrt(  3. / 5.))]), None)
                   , ('A0',   'Apar')  :  ( _ba('Re_ang_A0_Apar',         [ ( ( 2, 1, 2,  1 ),        sqrt( 24. / 5.))]), None)
                   , ('A0',   'Aperp') :  ( None, _ba('Im_ang_A0_Aperp',  [ ( ( 2, 1, 2, -1 ), -1. * -sqrt( 24. / 5.))]))
                   , ('Apar', 'Aperp') :  ( None, _ba('Im_ang_Apar_Aperp',[ ( ( 2, 2, 2, -2 ), -1. *  sqrt( 12. / 5.))]))
                   , ('AS',   'AS')    :  ( _ba('Re_ang_AS_AS',           [ ( ( 0, 0, 0,  0 ),        4.             )
                                                                          , ( ( 0, 0, 2,  0 ),       -sqrt( 16. / 5.))]), None)
                   , ('A0',   'AS')    :  ( _ba('Re_ang_A0_AS',           [ ( ( 1, 0, 0,  0 ),        sqrt(192.     ))
                                                                          , ( ( 1, 0, 2,  0 ),       -sqrt(192. / 5.))]), None)
                   , ('Apar', 'AS')    :  ( _ba('Re_ang_Apar_AS',         [ ( ( 1, 1, 2,  1 ),        sqrt( 72. / 5.))]), None)
                   , ('Aperp','AS')    :  ( None, _ba('Im_ang_Aperp_AS',  [ ( ( 1, 1, 2, -1 ), -1. *  sqrt( 72. / 5.))]))
                   }
        for k,v in angFuncs.iteritems() : self[k] = v


class JpsiKstTransversityAmplitudesTransversityAngles( AngularFunctions ) :
    def __init__( self, **kwargs ) :
        AngularFunctions.__init__(self)
        angles = kwargs.pop('Angles')
        coef   = kwargs.pop( 'DummyCoef', False )

        from P2VV.Parameterizations.GeneralUtils import getParNamePrefix
        namePF = getParNamePrefix(True)

        # define function to build angular function; create dummy coefficient if we need to split the angular efficiency functions later
        from P2VV.RooFitWrappers import P2VVAngleBasis, Addition, RealVar
        dummy = RealVar( Name = namePF + 'angEffDummyCoef', Value = 1. ) if coef else None
        _ba = lambda name, args :\
            Addition( namePF + name, [ P2VVAngleBasis( Name = namePF + name, Angles = angles, Indices = arg[0], FixedCoef = arg[1]
                                                      , Coefficient = dummy ) for arg in args ] )

        # TODO: generate the following table straight from the physics using PS->(VV,VS) ->ffss  (V=spin 1, f=spin 1/2, PS,S,s = spin 0)
        from math import sqrt
        angFuncs = { ('A0',   'A0')    :  ( _ba('Re_ang_A0_A0',           [ ( ( 0, 0, 0,  0 ),        4.             )
                                                                          , ( ( 0, 0, 2,  0 ),        sqrt(  4. / 5.))
                                                                          , ( ( 0, 0, 2,  2 ),       -sqrt( 12. / 5.))
                                                                          , ( ( 2, 0, 0,  0 ),        8.             )
                                                                          , ( ( 2, 0, 2,  0 ),        sqrt( 16. / 5.))
                                                                          , ( ( 2, 0, 2,  2 ),       -sqrt( 48. / 5.))]), None)
                   , ('Apar', 'Apar')  :  ( _ba('Re_ang_Apar_Apar',       [ ( ( 2, 2, 0,  0 ),        2.             )
                                                                          , ( ( 2, 2, 2,  0 ),        sqrt(  1. / 5.))
                                                                          , ( ( 2, 2, 2,  2 ),        sqrt(  3. / 5.))]), None)
                   , ('Aperp','Aperp') :  ( _ba('Re_ang_Aperp_Aperp',     [ ( ( 2, 2, 0,  0 ),        2.             )
                                                                          , ( ( 2, 2, 2,  0 ),       -sqrt(  4. / 5.))]), None)
                   , ('A0',   'Apar')  :  ( _ba('Re_ang_A0_Apar',         [ ( ( 2, 1, 2, -2 ),       -sqrt( 24. / 5.))]), None)
                   , ('A0',   'Aperp') :  ( None, _ba('Im_ang_A0_Aperp',  [ ( ( 2, 1, 2,  1 ),  -1. * sqrt( 24. / 5.))]))
                   , ('Apar', 'Aperp') :  ( None, _ba('Im_ang_Apar_Aperp',[ ( ( 2, 2, 2, -1 ),  -1. * sqrt( 12. / 5.))]))
                   , ('AS',   'AS')    :  ( _ba('Re_ang_AS_AS',           [ ( ( 0, 0, 0,  0 ),        4.             )
                                                                          , ( ( 0, 0, 2,  0 ),        sqrt(  4. / 5.))
                                                                          , ( ( 0, 0, 2,  2 ),       -sqrt( 12. / 5.))]),None)
                   , ('A0',   'AS')    :  ( _ba('Re_ang_A0_AS',           [ ( ( 1, 0, 0,  0 ),        sqrt(192.     ))
                                                                          , ( ( 1, 0, 2,  0 ),        sqrt( 48. / 5.))
                                                                          , ( ( 1, 0, 2,  2 ),       -sqrt(144. / 5.))]), None)
                   , ('Apar', 'AS')    :  ( _ba('Re_ang_Apar_AS',         [ ( ( 1, 1, 2, -2 ),       -sqrt( 72. / 5.))]), None)
                   , ('Aperp','AS')    :  ( None, _ba('Im_ang_Aperp_AS',  [ ( ( 1, 1, 2,  1 ), -1. * -sqrt( 72. / 5.))]))
                   }
        for k,v in angFuncs.iteritems() : self[k] = v

class phiphiTransversityAmplitudesHelicityAnglesRaw( AngularFunctions ) :
    def __init__( self, **kwargs ) :
        AngularFunctions.__init__(self)
        angles = kwargs.pop('Angles')

        from P2VV.RooFitWrappers import FormulaVar
        
        _rawFns = lambda name, formula, coeff :\
             FormulaVar( Name = name[0]+"_"+name[1]+"_angularFunction", Formula = str(coeff)+"*("+formula+")", Arguments = [ angles[ang] for ang in ( 'ctheta_1', 'ctheta_2', 'phi' ) ] )

        from math import sqrt
        angFuncs = { ('A0',     'A0')       :  _rawFns( ('A0','A0'), "@0*@0*@1*@1", 4.0)
                , ('Apara',     'Apara')    :  _rawFns( ('Apara','Apara'), "sin(acos(@0))*sin(acos(@0))*sin(acos(@1))*sin(acos(@1))*(1.0+cos(2.0*@2))", 1.0)
                , ('Aperp',     'Aperp')    :  _rawFns( ('Aperp','Aperp'), "sin(acos(@0))*sin(acos(@0))*sin(acos(@1))*sin(acos(@1))*(1.0-cos(2.0*@2))", 1.0)
                , ('Apara',     'Aperp')    :  _rawFns( ('Apara','Aperp'), "sin(acos(@0))*sin(acos(@0))*sin(acos(@1))*sin(acos(@1))*sin(2.0*@2)", -2.0)
                , ('Apara',     'A0')       :  _rawFns( ('Apara','A0'), "sin(2.0*acos(@0))*sin(2.0*acos(@1))*cos(@2)", sqrt(2))
                , ('A0',        'Aperp')    :  _rawFns( ('A0','Aperp'), "sin(2.0*acos(@0))*sin(2.0*acos(@1))*sin(@2)", -1.0*sqrt(2))
                , ('Ass',       'Ass')      :  _rawFns( ('Ass','Ass'), "1.0", (4.0/9.0))
                , ('As',        'As')       :  _rawFns( ('As','As'), "(@0+@1)*(@0+@1)", (4.0/3.0))
                , ('As',        'Ass')      :  _rawFns( ('As','Ass'), "(@0+@1)", (8.0/3.0/sqrt(3)))
                , ('A0',        'Ass')      :  _rawFns( ('A0','Ass'), "@0*@1", (8.0/3.0))
                , ('Apara',     'Ass')      :  _rawFns( ('Apara','Ass'), "sin(acos(@0))*sin(acos(@1))*cos(@2)", (4.0*sqrt(2)/3.0))
                , ('Aperp',     'Ass')      :  _rawFns( ('Aperp','Ass'), "sin(acos(@0))*sin(acos(@1))*sin(@2)", (-4.0*sqrt(2)/3.0))
                , ('A0',        'As')       :  _rawFns( ('A0','As'), "@0*@1*(@0+@1)", (8.0/sqrt(3)))
                , ('Apara',     'As')       :  _rawFns( ('Apara','As'), "sin(acos(@0))*sin(acos(@1))*(@0+@1)*cos(@2)", (4.0*sqrt(2)/3))
                , ('Aperp',     'As')       :  _rawFns( ('Aperp','As'), "sin(acos(@0))*sin(acos(@1))*(@0+@1)*sin(@2)", (-4.0*sqrt(2)/3))
                }
        
        for k,v in angFuncs.iteritems() : self[k] = v

class phiphiTransversityAmplitudesHelicityAngles( AngularFunctions ) :
    def __init__( self, **kwargs ) :
        AngularFunctions.__init__(self)
        angles = kwargs.pop('Angles')
        csp    = kwargs.pop('CSP')
        coef   = kwargs.pop( 'DummyCoef', False )

        from P2VV.Parameterizations.GeneralUtils import getParNamePrefix
        namePF = getParNamePrefix(True)

        # define function to build angular function; create dummy coefficient if we need to split the angular efficiency functions later
        from P2VV.RooFitWrappers import P2VVAngleBasis, Addition, RealVar, Product
        dummy = RealVar( Name = namePF + 'angEffDummyCoef', Value = 1. ) if coef else None
        _ba = lambda name, args, coeff :\
            Addition( namePF + name, [ P2VVAngleBasis( Name = namePF + name, Angles = angles, Indices = arg[0], FixedCoef = arg[1]*coeff
                                                      , Coefficient = dummy ) for arg in args ] )
        _baCSP = lambda name, args, coeff :\
            Addition( namePF + name, [ Product(name+"_Prod_"+str(n),[P2VVAngleBasis( Name = namePF + name, Angles = angles, Indices = args[n][0], FixedCoef = args[n][1]*coeff
                                                      , Coefficient = dummy )]+args[n][2]) for n in range(len(args)) ] )

        from math import sqrt
        angFuncs = { ('A0',   'A0')      :( _ba('Re_ang_A0_A0',            [ ( ( 0, 0, 0,  0 ),        4.             )
                                                                           , ( ( 0, 0, 2,  0 ),        8./sqrt(5.)    )
                                                                           , ( ( 2, 0, 0,  0 ),        8.             )
                                                                           , ( ( 2, 0, 2,  0 ),        16.*sqrt( 1. / 5.))], (1./4.5)))###
                   , ('Apara', 'Apara')  :( _ba('Re_ang_Apara_Apara',      [ ( ( 0, 0, 0,  0 ),        4.             )
                                                                           , ( ( 2, 0, 0,  0 ),        -4.)
                                                                           , ( ( 0, 0, 2,  0 ),        -4./sqrt(5.))
                                                                           , ( ( 2, 0, 2,  0 ),        4./sqrt(5.))
                                                                           , ( ( 2, 2, 2,  2 ),        sqrt( 12. / 5.))], 2.0/9.))###
                   , ('Aperp', 'Aperp')  :( _ba('Re_ang_Aperp_Aperp',      [ ( ( 0, 0, 0,  0 ),        4.             )
                                                                           , ( ( 2, 0, 0,  0 ),        -4.)
                                                                           , ( ( 0, 0, 2,  0 ),        -4./sqrt(5.))
                                                                           , ( ( 2, 0, 2,  0 ),        4./sqrt(5.))
                                                                           , ( ( 2, 2, 2,  2 ),        -sqrt( 12. / 5.))], 2.0/9.))###
                   , ('Apara',   'A0')   :( _ba('Re_ang_Apara_A0',         [ ( ( 2, 1, 2,  1 ),        2.*sqrt( 6./ 5.))], (4./9.)))###
                   , ('Aperp',   'A0')   :( _ba('Im_ang_A0_Aperp',         [ ( ( 2, 1, 2, -1 ),        4. * sqrt( 6. / 5.))],(-2./9.)))###
                   , ('Aperp', 'Apara')  :( _ba('Im_ang_Aperp_Apara',      [ ( ( 2, 2, 2, -2 ),        -4. *  sqrt( 3. / 5.))],(8./36.)))###
                   , ('As',   'As')      :( _ba('Re_ang_AS_AS',            [ ( ( 0, 0, 0,  0 ),        8.             )
                                                                           , ( ( 2, 0, 0,  0 ),        8.)
                                                                           , ( ( 1, 0, 1,  0 ),        +8.*sqrt(3.))
                                                                           , ( ( 0, 0, 2,  0 ),        8./sqrt(5.))], (2./9.)))###
                   , ('A0',   'As')      :( _baCSP('Re_ang_A0_AS',            [ ( ( 1, 0, 0,  0 ),        8.*sqrt(3.),[csp]             )
                                                                           , ( ( 0, 0, 1,  0 ),        8.,[csp])
                                                                           , ( ( 2, 0, 1,  0 ),        16.,[csp])
                                                                           , ( ( 1, 0, 2,  0 ),        16.*sqrt(3./5.),[csp])], (2./9.)))###
                   , ('Apara',   'As')   :( _baCSP('Re_ang_Apara_AS',         [ ( ( 2, 1, 1,  1 ),        4.,[csp])
                                                                           , ( ( 1, 1, 2,  1 ),        12./sqrt(5.),[csp])], (2.0/9.0*sqrt(2./3.))))###
                   , ('Aperp',   'As')   :( _baCSP('Im_ang_Aperp_AS',         [ ( ( 2, 1, 1,  -1 ),       (4.),[csp])
                                                                           , ( ( 1, 1, 2,  -1 ),       12./sqrt(5.),[csp])], -sqrt(3.)/18.*(4.0/3.0*sqrt(2.))))###
                   , ('As',   'Ass')     :( _baCSP('Re_ang_AS_ASS',           [ ( ( 1, 0, 0,  0 ),        sqrt(3.),[csp])
                                                                           , ( ( 0, 0, 1,  0 ),        1.,[csp])], (16./9.)))###
                   , ('Ass',   'Ass')    :( _ba('Re_ang_ASS_ASS',          [ ( ( 0, 0, 0, 0 ),         (8./9.))],1.0))###
                   , ('A0',   'Ass')     :( _baCSP('Re_ang_A0_ASS',           [ ( ( 1, 0, 1, 0 ),         (16./3./sqrt(3.)),[csp,csp])],1.0))###
                   , ('Apara',   'Ass')  :( _baCSP('Re_ang_Apara_ASS',        [ ( ( 1, 1, 1, 1 ),         (8.*sqrt(2.)/3.*sqrt(3.)),[csp,csp])],3.0/9.))###
                   , ('Aperp',   'Ass')  :( _baCSP('Im_ang_Aperp_ASS',        [ ( ( 1, 1, 1, -1 ),        (16.*sqrt(2.)/9.*8.*sqrt(3.)),[csp,csp])],-1.0/16.))###
                   }
        for k,v in angFuncs.iteritems() : self[k] = v


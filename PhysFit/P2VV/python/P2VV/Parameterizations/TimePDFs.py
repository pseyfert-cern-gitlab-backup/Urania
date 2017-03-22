###########################################################################################################################################
## P2VVParameterizations.TimePDFs: Parameterizations of PDFs that depend on decay time with and whithout CPT violation                   ##
##                                                                                                                                       ##
## authors:                                                                                                                              ##
##   GR,  Gerhard Raven,                    Nikhef & VU, Gerhard.Raven@nikhef.nl                                                         ##
##   RA,  Roel Aaij,                        Nikhef, raaij@nikhef.nl                                                                      ##
##   GC,  Georgios Chatzikonstantinidis     Nikhef, georgm@nikhef.nl                                                                     ##
###########################################################################################################################################

#inspect function
import inspect
def check():
    curframe = inspect.currentframe()
    calframe = inspect.getouterframes(curframe, 2)
    print 'caller name:', calframe[1][3]

from P2VV.Parameterizations.GeneralUtils import _util_parse_mixin
class BDecayBasisCoefficients ( _util_parse_mixin ) :
    def __init__(self, **kwargs ) :
        for i in ['sin','cos','sinh','cosh' ] : setattr(self,i,kwargs.pop(i))
        if kwargs : raise KeyError('unknown keyword arguments: %s' % kwargs )
    def __getitem__(self,kw) :
        return getattr(self,kw)

#it is not used anywhere this class
class Coefficients_BDecayBasisCoefficients ( BDecayBasisCoefficients ) :
    def __init__( self, **kwargs ) :
        cCosh = self._parseArg( 'cCosh', kwargs, Title = 'cosh coefficient', Value =  1., ObjectType = 'ConstVar' )
        cCos  = self._parseArg( 'cCos',  kwargs, Title = 'cos coefficient',  Value =  0., MinMax = (-2., 2.) )
        cSinh = self._parseArg( 'cSinh', kwargs, Title = 'sinh coefficient', Value = -1., MinMax = (-2., 2.) )
        cSin  = self._parseArg( 'cSin',  kwargs, Title = 'sin coefficient',  Value =  0., MinMax = (-2., 2.) )
        BDecayBasisCoefficients.__init__( self, **dict( cosh = cCosh, cos = cCos, sinh = cSinh, sin = cSin ) )

class JpsiphiBTagDecayBasisCoefficients_CPT ( BDecayBasisCoefficients ) :
#example class with only Re(z), dont use it.

    def __init__( self, AngFuncs, Amplitudes, CPParams, Order,CPTParam) :
        from P2VV.RooFitWrappers import ConstVar,Product
        from ROOT import RooRealVar
        Re_Z = CPTParam.Re_Z()
        zero  = ConstVar( Name = 'zero',  Value =  0. )
        minuss = ConstVar( Name = 'minuss', Value = -1. )
        def combine( tCoefType, angFuncs, amplitudes, CPParams, iIndex, jIndex,trType,Tag_Type) :
            assert Tag_Type in ('Even','Odd')

            from P2VV.RooFitWrappers import ConstVar, RealVar, FormulaVar
            one   = ConstVar( Name = 'one',   Value =  1. )
            minus = ConstVar( Name = 'minus', Value = -1. )

            # test function for the content of the timeCoefficients
            def Coef_Content(Re_val,Im_val,tCType,iInd,jInd,amps,Type,Tag_Type):
                def giv_val(tC):
                    return None if tC == None else tC.getVal() if tC != None else None
                print 'Index_configurattion',':','(',iInd,',',jInd,')','==','(',amps[iInd].CP,',',amps[jInd].CP,')'
                print 'Type :', Type,'\n','Type of Tagging',Tag_Type
                print '{0:10} of {1:10}'.format('Content', 'Re_%s_%s_%s' % (tCType,iInd,jInd)) ,'==>(Name - Value)',(Re_val),':', giv_val(Re_val)
                print '{0:10} of {1:10}'.format('Content', 'Im_%s_%s_%s' % (tCType,iInd,jInd)) ,'==>(Name - Value)',(Im_val),':', giv_val(Im_val), '\n'

            # define functions which return Re(Ai* Aj), Im( Ai* Aj),
            # the name is dependent from the Tag cause the combine will be called two times for the sinh(Even,Odd)
            Re = lambda Ai, Aj : self._parseArg( 'Re_amps_%s_%s' % ( Ai, Aj ), { }, Type = 'ProdCarthCToRe', ObjectType = 'ConvertPolAmp'
                                                , Arguments = [ Ai.Re, Ai.Im, Aj.Re, Aj.Im ] )
            Im = lambda Ai, Aj : self._parseArg( 'Im_amps_%s_%s' % ( Ai, Aj), { }, Type = 'ProdCarthCToIm', ObjectType = 'ConvertPolAmp'
                                                , Arguments = [ Ai.Re, Ai.Im, Aj.Re, Aj.Im ] )
            # define functions which return the coefficients of the time dependence
            def CPVDec( termInd, iInd, jInd, amps, CPPar ) :

                # get parameters for CP violation in decay
                assert termInd in ( 'plus', 'min', 'Re', 'Im' )
                if CPPar.CPVInDecay() : return CPPar.R( termInd, iInd, jInd )

                # only CP violation in mixing (or lambdas for all polarizations identical):
                # R^+  =     ( 1 + eta_i * eta_j ) / 2
                # R^-  =     ( 1 - eta_i * eta_j ) / 2
                # R^Re =     ( eta_i + eta_j )     / 2
                # R^Im = i * ( eta_i - eta_j )     / 2

                if termInd == 'plus' : return ( None if amps[iInd].CP != amps[jInd].CP else one,                                 None )
                if termInd == 'min'  : return ( None if amps[iInd].CP == amps[jInd].CP else one,                                 None )
                if termInd == 'Re'   : return ( None if amps[iInd].CP != amps[jInd].CP else one if amps[iInd].CP > 0 else minus, None )
                if termInd == 'Im'   : return ( None, None if amps[iInd].CP == amps[jInd].CP else one if amps[iInd].CP > 0 else minus )

            def tCoefTerm_CP( name, dec, mix, sign) :
                # build one of the two terms within the time function coficient:
                # + R^+ * 1,  + R^- * C,  + R^- * 1,  + R^+ * C,  + R^Re * D,  + R^Im * S,  + R^Im * D,  - R^Re * S
                if not dec or not mix : return None
                if dec == minus : sign = -sign
                if mix == minus : sign = -sign
                sign = minus if sign < 0 else None
                if dec in [ one, minus ] : dec = None
                if mix in [ one, minus ] : mix = None

                facs = [ fac for fac in ( sign, dec, mix ) if fac ]
                return self._parseArg( name, {}, Arguments = facs, ObjectType = 'Product' ) if len(facs) > 1\
                    else facs[0] if len(facs) == 1 else one

            def tCoefTerm_CPT (name, dec, mix, sign) :
                if not dec or not mix : return None
                if dec == minus : sign = -sign
                if mix == minus : sign = -sign
                sign = minus if sign < 0 else None
                if dec in [ one, minus ] : dec = None
                if mix in [ one, minus ] : mix = None

                facs = [ fac for fac in ( sign, dec, mix ) if fac ]
                term= self._parseArg( name, { }, Arguments = facs, ObjectType = 'Product' ) if len(facs) > 1\
                    else facs[0] if len(facs) == 1 else one
                return self._parseArg(name + '_',{},Arguments =[term,Re_Z],ObjectType = 'Product')

            def tCoef_CPT ( tCType, iInd, jInd, amps, CPPar,Tag ):
                # build CPT contribution
                # cosh: qf * [     Re(z) *  (  D * R^Re  +  R^Im * S ) ] #odd term
                # cos : qf * [    -Re(z) *  (  D * R^Re  +  R^Im * S ) ] #odd term
                # sinh: qf * [     Re(z) *  (      R^+   +  R^-  * C ) ] #odd tern/even term
                # where this will be created in two steps first only the odd and second only the even
                assert tCType in ( 'cosh', 'cos','sinh')

                CPVDecInds = [ 'Re', 'Im'] if tCType in ('cosh','cos') else ['plus','min']

                CPVDecs = [ CPVDec( CPVDecInd, iInd, jInd, amps, CPPar ) for CPVDecInd in CPVDecInds ]

                CPVMixs = [ CPPar.D(), CPPar.S() ] if tCType in ('cosh','cos') else [one,CPPar.C()]
                if tCType == 'sinh' and Tag == 'Even': CPVMixs.reverse()
                signs = [ +1,+1] if tCType in ['cosh','sinh'] else [-1,-1]
                name = '%s_%s_%s_CPT' % ( iInd , jInd, tCType )

                terms = [ (  tCoefTerm_CPT( 'Re_%s%d_%s_%s_%s_CPT' % ( tCType, ind, iInd, jInd,Tag ), dec[0], mix, sign  )
                             , tCoefTerm_CPT( 'Im_%s%d_%s_%s_%s_CPT' % ( tCType, ind, iInd, jInd,Tag ), dec[1], mix, sign)
                             ) for ind, ( dec, mix, sign ) in enumerate( zip( CPVDecs, CPVMixs, signs))
                          ]

                assert any( comp for term in terms for comp in term )

                add = lambda name, args : self._parseArg( name, { }, Arguments = args, ObjectType = 'Addition' ) if len(args) > 1\
                    else args[0] if len(args) == 1 else None

                Coef_Content(add('Re_%s_%s_%s_%s' %(tCType,iInd,jInd,Tag), [term[0] for term in terms if term[0]]),\
                                 add('Im_%s_%s_%s_%s' % (tCType,iInd,jInd,Tag), [ term[1] for term in terms if term[1] ] ), tCType,iInd,jInd,amps,'CPT',Tag)

                return (  add( 'Re_%s_%s_%s_%s_CPT' % ( tCType, iInd, jInd,Tag ),  [ term[0] for term in terms if term[0] ] )
                          , add( 'Im_%s_%s_%s_%s_CPT' % ( tCType, iInd, jInd,Tag ),[ term[1] for term in terms if term[1] ] )
                          )

            def tCoef_CP( tCType, iInd, jInd, amps, CPPar,Tag) :

                # build the coefficient of the time function:
                # cosh: [ + R^+  * 1 + R^-  * C                ]      #even term
                # cos:  [ + R^-  * 1 + R^+  * C                ] * qf #odd  term
                # sinh: [ + R^Re * D + R^Im * S                ]      #even term 
                # sin:  [ + R^Im * D - R^Re * S                ] * qf #odd  term

                assert tCType in ( 'cosh', 'sinh', 'cos', 'sin' )
                CPVDecInds = [ 'plus', 'min' ] if tCType in ( 'cosh', 'cos' ) else [ 'Re', 'Im' ]
                if tCType in ( 'cos', 'sin' ) : CPVDecInds.reverse()

                CPVDecs = [ CPVDec( CPVDecInd, iInd, jInd, amps, CPPar ) for CPVDecInd in CPVDecInds ]

                CPVMixs = [ one, CPPar.C() ] if tCType in ( 'cosh', 'cos' ) else [ CPPar.D(), CPPar.S() ]
                signs = [ +1, +1 ] if tCType in ( 'cosh', 'cos', 'sinh' ) else [ +1, -1 ]

                name = '%s_%s_%s_CP' % ( iInd , jInd, tCType )

                terms = [ (  tCoefTerm_CP( 'Re_%s%d_%s_%s_%s_CP' % ( tCType, ind, iInd, jInd,Tag ), dec[0], mix, sign  )
                             , tCoefTerm_CP( 'Im_%s%d_%s_%s_%s_CP' % ( tCType, ind, iInd, jInd,Tag ), dec[1], mix, sign)
                             ) for ind, ( dec, mix, sign ) in enumerate( zip( CPVDecs, CPVMixs, signs ) )
                          ]

                assert any( comp for term in terms for comp in term )

                add = lambda name, args : self._parseArg( name, { }, Arguments = args, ObjectType = 'Addition' ) if len(args) > 1\
                    else args[0] if len(args) == 1 else None

                Coef_Content(add('Re_%s_%s_%s_%s' %(tCType,iInd,jInd,Tag), [term[0] for term in terms if term[0]]),\
                             add('Im_%s_%s_%s_%s' % (tCType,iInd,jInd,Tag), [ term[1] for term in terms if term[1] ] ), tCType,iInd,jInd,amps,'CP',Tag)

                return (  add( 'Re_%s_%s_%s_%s' % ( tCType, iInd, jInd,Tag ),  [ term[0] for term in terms if term[0] ] )
                          , add( 'Im_%s_%s_%s_%s' % ( tCType, iInd, jInd,Tag ),[ term[1] for term in terms if term[1] ] )
                          )

            # create complex amplitude, time and angular factors,
            ( reAmps, imAmps ) = ( Re( amplitudes[iIndex], amplitudes[jIndex] ), Im( amplitudes[iIndex], amplitudes[jIndex] ) )\
                             if iIndex != jIndex else ( amplitudes[iIndex].Mag2, None )

            if trType == 'CP':
                ( reTime, imTime ) = tCoef_CP( tCoefType, iIndex, jIndex, amplitudes, CPParams,Tag_Type)
            else:
                ( reTime, imTime ) = tCoef_CPT(tCoefType, iIndex, jIndex, amplitudes, CPParams,Tag_Type)
            ( reAng, imAng ) = angFuncs[ ( iIndex, jIndex ) ]

            # (real part of) product of amplitude, time and angular (complex) factors:
            # Re(abc) = Re(a)Re(b)Re(c) - Im(a)Im(b)Re(c) - Re(a)Im(b)Im(c) - Im(a)Re(b)Im(c)
            prod = lambda name, args : [ self._parseArg( name, { }, Arguments = args, ObjectType = 'Product' ) ] if all(args) else [ ]

            x1 = prod('ReReRe_%s_%s_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex],trType,Tag_Type), [        reAmps , reTime, reAng ] )
            x2 = prod( 'ImImRe_%s_%s_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex],trType,Tag_Type), [ minus, imAmps , imTime, reAng ] )
            x3 = prod( 'ReImIm_%s_%s_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex],trType,Tag_Type), [ minus, reAmps , imTime, imAng ] )
            x4 = prod( 'ImReIm_%s_%s_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex],trType,Tag_Type), [ minus, imAmps , reTime, imAng ] )

            return x1+x2+x3+x4

        try : # this requires python 2.7 or later...
            from itertools import combinations_with_replacement as cwr
        except:
            from P2VV.Compatibility import cwr
        args_CP,args_CPT,args_Combine = dict(),dict(),dict()
        for tCoefType in [ 'cosh','sinh','cos','sin' ] :
            assert tCoefType in ('cosh','sinh','cos','sin')
            Tag_Type = ['Even'] if tCoefType in ['cosh','sinh'] else ['Odd']
            coef_CP  = self._parseArg( '%s_%s_Coef_CP'    % (tCoefType,Tag_Type[0]), { }, ObjectType = 'Addition'
                                       , Arguments = [ term for ( i, j ) in cwr( Order, 2 )\
                                                           for term in combine( tCoefType, AngFuncs, Amplitudes, CPParams, i, j,'CP',Tag_Type[0])     ]
                                       )
            args_CP[tCoefType] = [coef_CP,None] if Tag_Type[0] == 'Even' else [None,coef_CP]

        for tCoefType in ['cosh','cos','sinh']:
            assert tCoefType in ('cosh','cos','sinh')
            Tag_Type = ['Odd'] if tCoefType in ['cosh','cos'] else ['Odd','Even']

            if len(Tag_Type)   == 1:#only odd terms-->(cosh,cos)
                coef_CPT = self._parseArg( '%s_%s_Coef_CPT' % (tCoefType,Tag_Type[0]), { }, ObjectType = 'Addition'
                                           , Arguments = [ term for ( i, j ) in cwr( Order , 2 )\
                                                           for term in combine( tCoefType, AngFuncs, Amplitudes, CPParams, i, j,'CPT',Tag_Type[0])    ]
                                           )
                args_CPT[tCoefType] = [None,coef_CPT]

            elif len(Tag_Type) == 2:
                args_CPT[tCoefType] = [None,None]#just Initialize
                for  Tag in Tag_Type:
                    coef_CPT = self._parseArg( '%s_%s_Coef_CPT' % (tCoefType,Tag), { }, ObjectType = 'Addition'
                                               , Arguments = [ term for ( i, j ) in cwr( Order , 2 )\
                                                                   for term in combine( tCoefType, AngFuncs, Amplitudes, CPParams, i, j,'CPT',Tag)    ]
                                               )
                    if Tag =='Odd' :args_CPT[tCoefType][1] = coef_CPT
                    if Tag =='Even':args_CPT[tCoefType][0]= coef_CPT

            else: raise Exception('You have only Even and Odd terms')

        for Coef in ['cosh','sinh','sin','cos']:
            if Coef =='cosh': args_Combine[Coef] = (args_CP[Coef][0],args_CPT[Coef][1])
            if Coef =='sinh': args_Combine[Coef] = (self._parseArg('%s_EvenCP_EvenCPT' % (Coef)
                                                                   ,{},Arguments=[args_CP[Coef][0],args_CPT[Coef][0]],ObjectType = 'Addition'),args_CPT[Coef][1])
            if Coef == 'cos': args_Combine[Coef] = (None,self._parseArg('%s_OddCP_OddCPT' % (Coef)
                                                                        ,{},Arguments = [args_CP[Coef][1],args_CPT[Coef][1]],ObjectType = 'Addition'))
            if Coef == 'sin': args_Combine[Coef] = (None,args_CP[Coef][1])

        BDecayBasisCoefficients.__init__( self, **args_Combine )

class JpsiphiBTagDecayBasisCoefficients_CPT_extension ( BDecayBasisCoefficients ) :
# this is the nominal class for the time coefs with CPT violation ...

    def __init__( self, AngFuncs, Amplitudes, CPParams, Order,CPTParam) :
        from P2VV.RooFitWrappers import ConstVar,Product
        from ROOT import RooRealVar
        zero   = ConstVar( Name = 'zero',  Value =  0. )
        minuss = ConstVar( Name = 'minuss', Value = -1. )
        Im_Z   = CPTParam.Im_Z() if 'Im_Z' in dir(CPTParam) else zero
        Re_Z   = CPTParam.Re_Z()

        def combine( tCoefType, angFuncs, amplitudes, CPParams, iIndex, jIndex,trType,Tag_Type) :
            assert Tag_Type in ('Even','Odd')

            from P2VV.RooFitWrappers import ConstVar, RealVar, FormulaVar
            one   = ConstVar( Name = 'one',   Value =  1. )
            minus = ConstVar( Name = 'minus', Value = -1. )

            # test function for the content of the timeCoefficients
            def Coef_Content(Re_val,Im_val,tCType,iInd,jInd,amps,Type,Tag_Type):
                def giv_val(tC):
                    return None if tC == None else tC.getVal() if tC != None else None
                print 'Index_configurattion',':','(',iInd,',',jInd,')','==','(',amps[iInd].CP,',',amps[jInd].CP,')'
                print 'Type :', Type,'\n','Type of Tagging',Tag_Type
                print '{0:10} of {1:10}'.format('Content', 'Re_%s_%s_%s' % (tCType,iInd,jInd)) ,'==>(Name - Value)',(Re_val),':', giv_val(Re_val)
                print '{0:10} of {1:10}'.format('Content', 'Im_%s_%s_%s' % (tCType,iInd,jInd)) ,'==>(Name - Value)',(Im_val),':', giv_val(Im_val), '\n'

            # define functions which return Re(Ai* Aj), Im( Ai* Aj),
            # the name is dependent from the Tag cause the combine will be called two times for the sinh(Even,Odd)
            Re = lambda Ai, Aj : self._parseArg( 'Re_amps_%s_%s' % ( Ai, Aj ), { }, Type = 'ProdCarthCToRe', ObjectType = 'ConvertPolAmp'
                                                , Arguments = [ Ai.Re, Ai.Im, Aj.Re, Aj.Im ] )
            Im = lambda Ai, Aj : self._parseArg( 'Im_amps_%s_%s' % ( Ai, Aj), { }, Type = 'ProdCarthCToIm', ObjectType = 'ConvertPolAmp'
                                                , Arguments = [ Ai.Re, Ai.Im, Aj.Re, Aj.Im ] )
            # define functions which return the coefficients of the time dependence
            def CPVDec( termInd, iInd, jInd, amps, CPPar ) :

                # get parameters for CP violation in decay
                assert termInd in ( 'plus', 'min', 'Re', 'Im' )
                if CPPar.CPVInDecay() : return CPPar.R( termInd, iInd, jInd )

                # only CP violation in mixing (or lambdas for all polarizations identical):
                # R^+  =     ( 1 + eta_i * eta_j ) / 2
                # R^-  =     ( 1 - eta_i * eta_j ) / 2
                # R^Re =     ( eta_i + eta_j )     / 2
                # R^Im = i * ( eta_i - eta_j )     / 2

                if termInd == 'plus' : return ( None if amps[iInd].CP != amps[jInd].CP else one,                                 None )
                if termInd == 'min'  : return ( None if amps[iInd].CP == amps[jInd].CP else one,                                 None )
                if termInd == 'Re'   : return ( None if amps[iInd].CP != amps[jInd].CP else one if amps[iInd].CP > 0 else minus, None )
                if termInd == 'Im'   : return ( None, None if amps[iInd].CP == amps[jInd].CP else one if amps[iInd].CP > 0 else minus )

            def tCoefTerm_CP( name, dec, mix, sign ) :
                # build one of the two terms within the time function coficient:
                # + R^+ * 1,  + R^- * C,  + R^- * 1,  + R^+ * C,  + R^Re * D,  + R^Im * S,  + R^Im * D,  - R^Re * S
                if not dec or not mix : return None
                if dec == minus : sign = -sign
                if mix == minus : sign = -sign
                sign = minus if sign < 0 else None
                if dec in [ one, minus ] : dec = None
                if mix in [ one, minus ] : mix = None

                facs = [ fac for fac in ( sign, dec, mix ) if fac ]
                return self._parseArg( name, {}, Arguments = facs, ObjectType = 'Product' ) if len(facs) > 1\
                    else facs[0] if len(facs) == 1 else one

            def cptPart(tType,Tag):
                if tType in ['cosh','cos']:
                    if Tag == 'Odd' : return Re_Z
                    if Tag == 'Even': return Im_Z
                elif tType == 'sinh': return Re_Z
                else                : return Im_Z

            def tCoefTerm_CPT (name, dec, mix, sign,tType,Tag) :
                if not dec or not mix : return None
                if dec == minus : sign = -sign
                if mix == minus : sign = -sign
                sign = minus if sign < 0 else None
                if dec in [ one, minus ] : dec = None
                if mix in [ one, minus ] : mix = None

                facs = [ fac for fac in ( sign, dec, mix ) if fac ]
                term= self._parseArg( name, { }, Arguments = facs, ObjectType = 'Product' ) if len(facs) > 1\
                    else facs[0] if len(facs) == 1 else one

                return self._parseArg(name + '_',{},Arguments =[term,cptPart(tType,Tag)],ObjectType = 'Product')

            def tCoef_CPT ( tCType, iInd, jInd, amps, CPPar,Tag ):
                # build CPT contribution
                # cosh: qf * [     Re(z) *  (  D * R^Re  +  R^Im * S ) ]  + Im(z) * [- R^Re * S + R^Im * D ] #odd term/ even term
                # cos : qf * [    -Re(z) *  (  D * R^Re  +  R^Im * S ) ]  - Im(z) * [- R^Re * S + R^Im * D ] #odd term/ even term
                # sinh: qf * [     Re(z) *  (      R^+   +  R^-  * C ) ]  + Re(z) * [  R^+   + C * R^-     ] #odd term/ even term
                # sin : qf * [     Im(z) *  (      R^+   +  R^-  * C ) ]  + Im(z) * [  R^+   + C * R^-     ] #ood term/ even term
                # where this will be created in two steps first only the odd and second only the even
                assert tCType in ( 'cosh', 'cos','sinh','sin')

                CPVDecInds = [ 'Re', 'Im'] if tCType in ('cosh','cos') else ['plus','min']

                CPVDecs = [ CPVDec( CPVDecInd, iInd, jInd, amps, CPPar ) for CPVDecInd in CPVDecInds ]

                CPVMixs = [ CPPar.D(), CPPar.S() ] if tCType in ('cosh','cos') else [one,CPPar.C()]

                if Tag == 'Odd':
                    if tCType in ['cosh','sinh','sin']: signs = [+1,+1]
                    else                              : signs = [-1,-1]
                if Tag == 'Even':
                    CPVMixs.reverse()
                    if tCType in ['sinh','sin']       : signs = [+1,+1]
                    if tCType == 'cosh'               : signs = [-1,+1]
                    if tCType == 'cos'                : signs = [+1,-1]

                name = '%s_%s_%s_CPT' % ( iInd , jInd, tCType )

                terms = [ (  tCoefTerm_CPT( 'Re_%s%d_%s_%s_%s_CPT' % ( tCType, ind, iInd, jInd,Tag ), dec[0], mix, sign,tCType,Tag)
                             , tCoefTerm_CPT( 'Im_%s%d_%s_%s_%s_CPT' % ( tCType, ind, iInd, jInd,Tag ), dec[1], mix, sign,tCType,Tag)
                             ) for ind, ( dec, mix, sign ) in enumerate( zip( CPVDecs, CPVMixs, signs))
                          ]


                assert any( comp for term in terms for comp in term )

                add = lambda name, args : self._parseArg( name, { }, Arguments = args, ObjectType = 'Addition' ) if len(args) > 1\
                    else args[0] if len(args) == 1 else None

                Coef_Content(add('Re_%s_%s_%s_%s' %(tCType,iInd,jInd,Tag), [term[0] for term in terms if term[0]]),\
                                 add('Im_%s_%s_%s_%s' % (tCType,iInd,jInd,Tag), [ term[1] for term in terms if term[1] ] ), tCType,iInd,jInd,amps,'CPT',Tag)

                return (  add( 'Re_%s_%s_%s_%s_CPT' % ( tCType, iInd, jInd,Tag ),  [ term[0] for term in terms if term[0] ] )
                          , add( 'Im_%s_%s_%s_%s_CPT' % ( tCType, iInd, jInd,Tag ),[ term[1] for term in terms if term[1] ] )
                          )

            def tCoef_CP( tCType, iInd, jInd, amps, CPPar,Tag) :

                # build the coefficient of the time function:
                # cosh: [ + R^+  * 1 + R^-  * C                ]      #even term
                # cos:  [ + R^-  * 1 + R^+  * C                ] * qf #odd  term
                # sinh: [ + R^Re * D + R^Im * S                ]      #even term
                # sin:  [ + R^Im * D - R^Re * S                ] * qf #odd  term

                assert tCType in ( 'cosh', 'sinh', 'cos', 'sin' )
                CPVDecInds = [ 'plus', 'min' ] if tCType in ( 'cosh', 'cos' ) else [ 'Re', 'Im' ]
                if tCType in ( 'cos', 'sin' ) : CPVDecInds.reverse()

                CPVDecs = [ CPVDec( CPVDecInd, iInd, jInd, amps, CPPar ) for CPVDecInd in CPVDecInds ]

                CPVMixs = [ one, CPPar.C() ] if tCType in ( 'cosh', 'cos' ) else [ CPPar.D(), CPPar.S() ]
                signs = [ +1, +1 ] if tCType in ( 'cosh', 'cos', 'sinh' ) else [ +1, -1 ]

                name = '%s_%s_%s_CP' % ( iInd , jInd, tCType )

                terms = [ (  tCoefTerm_CP( 'Re_%s%d_%s_%s_%s_CP' % ( tCType, ind, iInd, jInd,Tag ), dec[0], mix, sign   )
                             , tCoefTerm_CP( 'Im_%s%d_%s_%s_%s_CP' % ( tCType, ind, iInd, jInd,Tag ), dec[1], mix, sign )
                             ) for ind, ( dec, mix, sign ) in enumerate( zip( CPVDecs, CPVMixs, signs ) )
                          ]

                assert any( comp for term in terms for comp in term )

                add = lambda name, args : self._parseArg( name, { }, Arguments = args, ObjectType = 'Addition' ) if len(args) > 1\
                    else args[0] if len(args) == 1 else None

                Coef_Content(add('Re_%s_%s_%s_%s' %(tCType,iInd,jInd,Tag), [term[0] for term in terms if term[0]]),\
                                 add('Im_%s_%s_%s_%s' % (tCType,iInd,jInd,Tag), [ term[1] for term in terms if term[1] ] ), tCType,iInd,jInd,amps,'CP',Tag)

                return (  add( 'Re_%s_%s_%s_%s' % ( tCType, iInd, jInd,Tag ),  [ term[0] for term in terms if term[0] ] )
                          , add( 'Im_%s_%s_%s_%s' % ( tCType, iInd, jInd,Tag ),[ term[1] for term in terms if term[1] ] )
                          )

            # create complex amplitude, time and angular factors,
            ( reAmps, imAmps ) = ( Re( amplitudes[iIndex], amplitudes[jIndex] ), Im( amplitudes[iIndex], amplitudes[jIndex] ) )\
                             if iIndex != jIndex else ( amplitudes[iIndex].Mag2, None )

            if trType == 'CP':
                ( reTime, imTime ) = tCoef_CP( tCoefType, iIndex, jIndex, amplitudes, CPParams,Tag_Type)
            else:
                ( reTime, imTime ) = tCoef_CPT(tCoefType, iIndex, jIndex, amplitudes, CPParams,Tag_Type)

            ( reAng, imAng ) = angFuncs[ ( iIndex, jIndex ) ]

            # (real part of) product of amplitude, time and angular (complex) factors:
            # Re(abc) = Re(a)Re(b)Re(c) - Im(a)Im(b)Re(c) - Re(a)Im(b)Im(c) - Im(a)Re(b)Im(c)
            prod = lambda name, args : [ self._parseArg( name, { }, Arguments = args, ObjectType = 'Product' ) ] if all(args) else [ ]

            x1 = prod( 'ReReRe_%s_%s_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex],trType,Tag_Type), [        reAmps , reTime, reAng ] )
            x2 = prod( 'ImImRe_%s_%s_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex],trType,Tag_Type), [ minus, imAmps , imTime, reAng ] )
            x3 = prod( 'ReImIm_%s_%s_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex],trType,Tag_Type), [ minus, reAmps , imTime, imAng ] )
            x4 = prod( 'ImReIm_%s_%s_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex],trType,Tag_Type), [ minus, imAmps , reTime, imAng ] )

            return x1+x2+x3+x4

        try : # this requires python 2.7 or later...
            from itertools import combinations_with_replacement as cwr
        except:
            from P2VV.Compatibility import cwr
        args_CP,args_CPT,args_Combine = dict(),dict(),dict()
        for tCoefType in [ 'cosh','sinh','cos','sin' ] :
            assert tCoefType in ('cosh','sinh','cos','sin')
            Tag_Type = ['Even'] if tCoefType in ['cosh','sinh'] else ['Odd']
            coef_CP  = self._parseArg( '%s_%s_Coef_CP'    % (tCoefType,Tag_Type[0]), { }, ObjectType = 'Addition'
                                       , Arguments = [ term for ( i, j ) in cwr( Order, 2 )\
                                                           for term in combine( tCoefType, AngFuncs, Amplitudes, CPParams, i, j,'CP',Tag_Type[0])     ]
                                       )
            args_CP[tCoefType] = [coef_CP,None] if Tag_Type[0] == 'Even' else [None,coef_CP]

        for tCoefType in ['cosh','cos','sinh','sin'] :
            assert tCoefType in ('cosh','cos','sinh','sin')
            Tag_Type = ['Odd','Even']# all the terms contain both even and odd terms
            args_CPT[tCoefType] = [None,None]#just Initialize
            for Tag in Tag_Type:
                coef_CPT = self._parseArg( '%s_%s_Coef_CPT' % (tCoefType,Tag), { }, ObjectType = 'Addition'
                                           , Arguments = [ term for ( i, j ) in cwr( Order , 2 )\
                                                               for term in combine( tCoefType, AngFuncs, Amplitudes, CPParams, i, j,'CPT',Tag)    ]
                                           )
                if Tag =='Odd' :args_CPT[tCoefType][1] = coef_CPT
                if Tag =='Even':args_CPT[tCoefType][0] = coef_CPT

        for Coef in ['cosh','sinh','sin','cos']:
            if Coef =='cosh': args_Combine[Coef] = (self._parseArg('%s_EvenCP_EvenCPT' % (Coef)
                                                                   ,{},Arguments=[args_CP[Coef][0],args_CPT[Coef][0]],ObjectType = 'Addition'),args_CPT[Coef][1])
            if Coef =='sinh': args_Combine[Coef] = (self._parseArg('%s_EvenCP_EvenCPT' % (Coef)
                                                                   ,{},Arguments=[args_CP[Coef][0],args_CPT[Coef][0]],ObjectType = 'Addition'),args_CPT[Coef][1])

            if Coef == 'cos': args_Combine[Coef] = (args_CPT[Coef][0],self._parseArg('%s_OddCP_OddCPT' % (Coef)
                                                                                     ,{},Arguments = [args_CP[Coef][1],args_CPT[Coef][1]],ObjectType = 'Addition'))
            if Coef == 'sin': args_Combine[Coef] = (args_CPT[Coef][0],self._parseArg('%s_oddCP_oddCPT' % (Coef)
                                                                                     ,{},Arguments = [args_CP[Coef][1],args_CPT[Coef][1]],ObjectType = 'Addition'))

        BDecayBasisCoefficients.__init__( self, **args_Combine )
                                                                          
class JpsiphiBTagDecayBasisCoefficients( BDecayBasisCoefficients ) :
    def __init__( self, AngFuncs, Amplitudes, CPParams, Order ) :
        def combine( tCoefType, angFuncs, amplitudes, CPParams, iIndex, jIndex) :
            from P2VV.RooFitWrappers import ConstVar, RealVar, FormulaVar
            one   = ConstVar( Name = 'one',   Value =  1 )
            minus = ConstVar( Name = 'minus', Value = -1 )

            # define functions which return Re(Ai* Aj), Im( Ai* Aj)
            Re = lambda Ai, Aj : self._parseArg( 'Re_amps_%s_%s' % ( Ai, Aj ), { }, Type = 'ProdCarthCToRe', ObjectType = 'ConvertPolAmp'
                                                , Arguments = [ Ai.Re, Ai.Im, Aj.Re, Aj.Im ] )
            Im = lambda Ai, Aj : self._parseArg( 'Im_amps_%s_%s' % ( Ai, Aj ), { }, Type = 'ProdCarthCToIm', ObjectType = 'ConvertPolAmp'
                                                , Arguments = [ Ai.Re, Ai.Im, Aj.Re, Aj.Im ] )

            # test function for the content of the timeCoefficients
            def Coef_Content(Re_val,Im_val,tCType,iInd,jInd,amps):
                def giv_val(tC):
                    return None if tC == None else tC.getVal() if tC != None else None
                print 'Index_configurattion',':','(',iInd,',',jInd,')','==','(',amps[iInd].CP,',',amps[jInd].CP,')'
                print '{0:10} of {1:10}'.format('Content', 'Re_%s_%s_%s' % (tCType,iInd,jInd)) ,'==>(Name - Value)',(Re_val),':', giv_val(Re_val)
                print '{0:10} of {1:10}'.format('Content', 'Im_%s_%s_%s' % (tCType,iInd,jInd)) ,'==>(Name - Value)',(Im_val),':', giv_val(Im_val), '\n'

            # define functions which return the coefficients of the time dependence
            def CPVDec( termInd, iInd, jInd, amps, CPPar ) :

                # get parameters for CP violation in decay
                assert termInd in ( 'plus', 'min', 'Re', 'Im' )
                if CPPar.CPVInDecay() : return CPPar.R( termInd, iInd, jInd )

                # only CP violation in mixing (or lambdas for all polarizations identical):
                # R^+  =     ( 1 + eta_i * eta_j ) / 2
                # R^-  =     ( 1 - eta_i * eta_j ) / 2
                # R^Re =     ( eta_i + eta_j )     / 2
                # R^Im = i * ( eta_i - eta_j )     / 2

                if termInd == 'plus' : return ( None if amps[iInd].CP != amps[jInd].CP else one,                                 None )
                if termInd == 'min'  : return ( None if amps[iInd].CP == amps[jInd].CP else one,                                 None )
                if termInd == 'Re'   : return ( None if amps[iInd].CP != amps[jInd].CP else one if amps[iInd].CP > 0 else minus, None )
                if termInd == 'Im'   : return ( None, None if amps[iInd].CP == amps[jInd].CP else one if amps[iInd].CP > 0 else minus )

            def tCoefTerm( name, dec, mix, sign, tCType) :
                # build one of the two terms within the time function coficient:
                # + R^+ * 1,  + R^- * C,  + R^- * 1,  + R^+ * C,  + R^Re * D,  + R^Im * S,  + R^Im * D,  - R^Re * S

                if not dec or not mix : return None
                if dec == minus : sign = -sign
                if mix == minus : sign = -sign
                sign = minus if sign < 0 else None
                if dec in [ one, minus ] : dec = None
                if mix in [ one, minus ] : mix = None

                facs = [ fac for fac in ( sign, dec, mix ) if fac ]
                return self._parseArg( name, { }, Arguments = facs, ObjectType = 'Product' ) if len(facs) > 1\
                    else facs[0] if len(facs) == 1 else one

            def tCoef( tCType, iInd, jInd, amps, CPPar ) :

                # build the coefficient of the time function:
                # cosh: [ + R^+  * 1 + R^-  * C ]
                # cos:  [ + R^-  * 1 + R^+  * C ] * qf
                # sinh: [ + R^Re * D + R^Im * S ]
                # sin:  [ + R^Im * D - R^Re * S ] * qf

                assert tCType in ( 'cosh', 'sinh', 'cos', 'sin' )

                CPVDecInds = [ 'plus', 'min' ] if tCType in ( 'cosh', 'cos' ) else [ 'Re', 'Im' ]
                if tCType in ( 'cos', 'sin' ) : CPVDecInds = [ CPVDecInds[1], CPVDecInds[0] ]

                CPVDecs = [ CPVDec( CPVDecInd, iInd, jInd, amps, CPPar ) for CPVDecInd in CPVDecInds ]

                CPVMixs = [ one, CPPar.C() ] if tCType in ( 'cosh', 'cos' ) else [ CPPar.D(), CPPar.S() ]
                signs = [ +1, +1 ] if tCType in ( 'cosh', 'cos', 'sinh' ) else [ +1, -1 ]

                name = '%s_%s_%s' % ( iInd , jInd, tCType )

                terms = [ (  tCoefTerm( 'Re_%s%d_%s_%s' % ( tCType, ind, iInd, jInd ), dec[0], mix, sign,tCType )
                             , tCoefTerm( 'Im_%s%d_%s_%s' % ( tCType, ind, iInd, jInd ), dec[1], mix, sign,tCType )
                             ) for ind, ( dec, mix, sign ) in enumerate( zip( CPVDecs, CPVMixs, signs ) )
                          ]

                assert any( comp for term in terms for comp in term )

                add = lambda name, args : self._parseArg( name, { }, Arguments = args, ObjectType = 'Addition' ) if len(args) > 1\
                    else args[0] if len(args) == 1 else None

                # check the content of the coef
                Coef_Content(add('Re_%s_%s_%s' %(tCType,iInd,jInd), [term[0] for term in terms if term[0]]),\
                                 add('Im_%s_%s_%s' % (tCType,iInd,jInd), [ term[1] for term in terms if term[1] ] ), tCType,iInd,jInd,amps)

                #for i in range(100): print 'C :',CPPar.C().getVal(),'D :',CPPar.D().getVal(),'S :',CPPar.S().getVal()
                return (  add( 'Re_%s_%s_%s' % ( tCType, iInd, jInd ),  [ term[0] for term in terms if term[0] ] )
                          , add( 'Im_%s_%s_%s' % ( tCType, iInd, jInd ),[ term[1] for term in terms if term[1] ] )
                          )

            # create complex amplitude, time and angular factors,
            ( reAmps, imAmps ) = ( Re( amplitudes[iIndex], amplitudes[jIndex] ), Im( amplitudes[iIndex], amplitudes[jIndex] ) )\
                             if iIndex != jIndex else ( amplitudes[iIndex].Mag2, None )
            ( reTime, imTime ) = tCoef( tCoefType, iIndex, jIndex, amplitudes, CPParams)
            ( reAng, imAng ) = angFuncs[ ( iIndex, jIndex ) ]

            # (there is a minus in case there are 2 imaginary contributions)
            prod = lambda name, args : [ self._parseArg( name, { }, Arguments = args, ObjectType = 'Product' ) ] if all(args) else [ ]

            x1= prod( 'ReReRe_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex]), [        reAmps , reTime, reAng ] )
            x2= prod( 'ImImRe_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex]), [ minus, imAmps , imTime, reAng ] )
            x3= prod( 'ReImIm_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex]), [ minus, reAmps , imTime, imAng ] )
            x4= prod( 'ImReIm_%s_%s_%s' % ( tCoefType, amplitudes[iIndex], amplitudes[jIndex]), [ minus, imAmps , reTime, imAng ] )
            return x1+x2+x3+x4

        try : # this requires python 2.7 or later...
            from itertools import combinations_with_replacement as cwr
        except:
            from P2VV.Compatibility import cwr
        args = dict()
        for tCoefType in [ 'cosh', 'sinh', 'cos', 'sin' ] :
            # NOTE: 'Amplitudes' must be traversed 'in order' : A0, Apar, Aperp, AS, so we cannot use Amplitudes.keys() out of the box
            #args[ tCoefType ] = self._parseArg( '%sCoef' % tCoefType, { }, ObjectType = 'Addition'
            #                                   , Arguments = [ term for ( i, j ) in cwr( Order, 2 )\
            #                                                   for term in combine( tCoefType, AngFuncs, Amplitudes, CPParams, i, j ) ]

            coef     = self._parseArg( '%sCoef'    % tCoefType, { }, ObjectType = 'Addition'
                                       , Arguments = [ term for ( i, j ) in cwr( Order, 2 )\
                                                           for term in combine( tCoefType, AngFuncs, Amplitudes, CPParams, i, j)     ]
                                       )

            args[ tCoefType ] = ( coef, None ) if tCoefType in [ 'cosh', 'sinh' ] else ( None, coef )

        BDecayBasisCoefficients.__init__( self, **args )


class JpsiphiBDecayBasisCoefficients( BDecayBasisCoefficients ) :

    def __init__(self,  angFuncs, Amplitudes,CP, itag, dilution, order ) :
        def combine( name, afun, A, CPparams, tag, i, j) :
            # TODO: deal with tag = None: create the untagged PDF in that case!
            from P2VV.RooFitWrappers import ConstVar, Product
            plus  = ConstVar( Name = 'plus',  Value =  1 )
            minus = ConstVar( Name = 'minus', Value = -1 )
            if type(CP['C'])==ConstVar and CP['C'].getVal() == 0 : 
                Norm = [ ]
            else :
                Norm = [ self._parseArg( 'Norm', kwargs, Formula = '1.0/(1.0+sign(@0)*@1)', Arguments = [ tag, CP['C'] ]
                        , ObjectType = 'FormulaVar' ) ]
                Norm[0].setAttribute("CacheAndTrack")
            # define functions which return Re(Conj(Ai) Aj), Im( Conj(Ai) Aj)
            Re = lambda ai, aj : self._parseArg( 'Re_c_%s_%s' % ( ai, aj ), { }, Type = 'ProdCarthCToRe', ObjectType = 'ConvertPolAmp'
                                                , Arguments=[ ai.Re,ai.Im,aj.Re,aj.Im ] )
            Im = lambda ai, aj : self._parseArg( 'Im_c_%s_%s' % ( ai, aj ), { }, Type = 'ProdCarthCToIm', ObjectType = 'ConvertPolAmp'
                                                , Arguments=[ ai.Re,ai.Im,aj.Re,aj.Im ] )
            # define functions which return the coefficients that define the time-dependence...
            _minus_if = lambda b, x : [ minus ] + x if b else  x 
            coef = { 'cosh' : lambda ai,aj,CP : ( plus if ai.CP == aj.CP else  CP['C']
                                                , None )
                   , 'cos'  : lambda ai,aj,CP : ( tag  if ai.CP != aj.CP else Product('Re_%s_%s_cos' %(ai,aj),                              [ tag, CP['C'] ] ) 
                                                , None )
                   , 'sinh' : lambda ai,aj,CP : ( None if ai.CP != aj.CP else Product('Re_%s_%s_sinh'%(ai,aj),  _minus_if( ai.CP < 0     ,  [      CP['D'] ] ))
                                                , None if ai.CP == aj.CP else Product('Im_%s_%s_sinh'%(ai,aj),  _minus_if( ai.CP < aj.CP ,  [      CP['S'] ] )) )
                   , 'sin'  : lambda ai,aj,CP : ( None if ai.CP != aj.CP else Product('Re_%s_%s_sin' %(ai,aj),  _minus_if( ai.CP > 0     ,  [ tag, CP['S'] ] ))
                                                , None if ai.CP == aj.CP else Product('Im_%s_%s_sin' %(ai,aj),  _minus_if( ai.CP < aj.CP ,  [ tag, CP['D'] ] )) )
                   }
            (c_re,c_im) = coef[name](A[i],A[j],CPparams)
            (f_re,f_im) = afun[(i,j)]
            (a_re,a_im) = ( Re(A[i],A[j]),Im(A[i],A[j]) )
            # NOTE: thes sign are just the obvious Re(a b c)  = Re(a)Re(b)Re(c) - Re(a)Im(b)Im(c) - Im(a)Re(b)Im(c) - Im(a)Im(b)Re(c),
            #       i.e. there is a minus in case there are 2 imaginary contributions
            prod = lambda name, args : [ Product(name, args) ] if all(args) else []
            s  = prod('ReReRe_%s_%s_%s'%(name,A[i],A[j]), [        a_re , c_re, f_re ]+Norm ) \
               + prod('ImImRe_%s_%s_%s'%(name,A[i],A[j]), [ minus, a_im , c_im, f_re ]+Norm ) \
               + prod('ImReIm_%s_%s_%s'%(name,A[i],A[j]), [ minus, a_im , c_re, f_im ]+Norm ) \
               + prod('ReImIm_%s_%s_%s'%(name,A[i],A[j]), [ minus, a_re , c_im, f_im ]+Norm )
            assert len(s) == 1 # for now, coefficients are either real, or imaginary, but not both... (not true in general, but I'm lazy today ;-)
            return s[0]

        args = dict()
        from P2VV.RooFitWrappers import Addition,Product, RealCategory
        try : # this requires python 2.7 or later...
            from itertools import combinations_with_replacement as cwr
        except:
            from P2VV.Compatibility import cwr

        tag = Product('tag',( RealCategory('tag_real', itag ),dilution))
        for name in [ 'cosh', 'sinh', 'cos', 'sin' ] :
            # NOTE: 'Amplitudes'  must be traversed 'in order' -- so we cannot use Amplitudes.keys() out of the box, but use the
            #       specified order (which also selects which ones to include!)...
            args[ name ] = Addition( 'a_%s'% name, [ combine(name,angFuncs,Amplitudes,CP,tag,i,j) for (i,j) in cwr( order, 2 ) ] )

        BDecayBasisCoefficients.__init__( self, **args )


def JpsiphiBDecay( Name, time, tag, lifetimeParams, sigtres, tagging, basisCoefficients ) :
    from P2VV.RooFitWrappers import BDecay
    return  BDecay(  Name                   = Name
                   , time                   = time
                   , dm                     = lifetimeParams['dM']
                   , tau                    = lifetimeParams['MeanLifetime']
                   , dGamma                 = lifetimeParams['dGamma']
                   , resolutionModel        = sigtres['model']
                   , coshCoef               = basisCoefficients['cosh']
                   , cosCoef                = basisCoefficients['cos']
                   , sinhCoef               = basisCoefficients['sinh']
                   , sinCoef                = basisCoefficients['sin']
                   , ConditionalObservables = sigtres.ConditionalObservables() + tagging.ConditionalObservables()
                   , ExternalConstraints    = lifetimeParams.ExternalConstraints()\
                                              + sigtres.ExternalConstraints()\
                                              + tagging.ExternalConstraints()
                  )

def JpsiphiBTagDecay( Name, time, tag, lifetimeParams, sigtres, tagging, basisCoefficients ) :
    from P2VV.RooFitWrappers import BTagDecay
    return  BTagDecay(  Name                   = Name
                      , time                   = time
                      , iTag                   = tag
                      , dm                     = lifetimeParams['dM']
                      , tau                    = lifetimeParams['MeanLifetime']
                      , dGamma                 = lifetimeParams['dGamma']
                      , resolutionModel        = sigtres['model']
                      , coshCoef               = basisCoefficients['cosh']
                      , cosCoef                = basisCoefficients['cos']
                      , sinhCoef               = basisCoefficients['sinh']
                      , sinCoef                = basisCoefficients['sin']
                      , dilution               = tagging['dilution']
                      , ADilWTag               = tagging['ADilWTag']
                      , avgCEven               = tagging['avgCEven']
                      , avgCOdd                = tagging['avgCOdd']
                      , ConditionalObservables = sigtres.ConditionalObservables() + tagging.ConditionalObservables()
                      , ExternalConstraints    = lifetimeParams.ExternalConstraints()\
                                                 + sigtres.ExternalConstraints()\
                                                 + tagging.ExternalConstraints()
                     )


class GeneralCoefficients ( BDecayBasisCoefficients ) :
# class for determining the TD coefficients in the most general case.

    def __init__( self, Name, AngFuncs, Amplitudes, CPParams, keyDict, singleCP,ampNames) :
        from P2VV.RooFitWrappers import ConstVar,Product
        from P2VV.RooFitWrappers import ConstVar, RealVar, FormulaVar
        from ROOT import RooRealVar
        
        if singleCP:
            phii_in = CPParams[Name+'phiCPRel_0']
            constant = ConstVar( Name = 'constant' , Value = 1.0 )
            self.phis = self._parseArg('single_phis',{}, Formula = '@1 * @0', Arguments = [ phii_in, constant ], ObjectType = 'FormulaVar' )
        else:
            for key in ampNames:
                #lambdai = CPParams[Name+'rhoCP_%s' % key[ 1 : ]]
                #CPParams[Name+'Inv_rhoCP_%s' % key[1:]] = self._parseArg(Name+'Inv_rhoCP_%s' % key[1:], {}, Formula = '1.0/@0', Arguments = [ lambdai ], ObjectType = 'FormulaVar' )
                if "0" not in key:
                    phi = CPParams[Name+'phiCPRel_%s' % key[ 1 : ]]
                    CPParams[Name+'phiCPRelNonShifted_%s' % key[1:]] = self._parseArg(Name+'phiCPRelNonShifted_%s' % key[1:], {}, Formula = '@1 + @0', Arguments = [ phi, CPParams[Name+'phiCPRel_0']], ObjectType = 'FormulaVar' )

        def orthog(key0,Amplitudes,CPParams,angTerm,eta1,Coef,singleCP):
            assert Coef in ( 'cos', 'sin', 'sinh', 'cosh' )

            # Get the amplitude
            ai = Amplitudes[Name+key0]
            # mag2
            aisq = ai.Mag2
            # lambda
            lambdai = CPParams[Name+'rhoCP_%s' % key0[ 1 : ]]
            # weak phase
            phii = CPParams[Name+'phiCPRel_%s' % key0[ 1 : ]]

            # If single CP, give the 0 polarisation
            if singleCP:
                lambdai = CPParams[Name+'rhoCP_0']
                phii = self.phis
            elif "0" not in key0:
                phii = CPParams[Name+'phiCPRelNonShifted_%s' % key0[ 1 : ]]

            norm = self._parseArg(Name+'_NormOrthog_%s_%s' % (Coef,key0),{}, Formula = '0.5*@0*(1.0+@1*@1)', Arguments = [ aisq, lambdai ], ObjectType = 'FormulaVar' )
            
            if Coef=='cosh':
                return self._parseArg( Name+'_OrthogTot_cosh_%s' % (key0), {}, Arguments = [norm,angTerm], ObjectType = 'Product' )
            elif Coef=='sinh':
                sinhForm = self._parseArg(Name+'_Orthog_sinh_%s' % (key0),{}, Formula = '-2.0 * @0 * @1 * cos(@2) / (1.0+@1*@1)'
                        , Arguments = [ eta1, lambdai, phii ], ObjectType = 'FormulaVar' )
                return self._parseArg( Name+'_OrthogTot_sinh_%s' % (key0), {}, Arguments = [norm,sinhForm,angTerm], ObjectType = 'Product' )
            elif Coef=='cos':
                cosForm = self._parseArg(Name+'_Orthog_cos_%s' % (key0),{}, Formula = '(1.0-@0*@0)/(1.0+@0*@0)'
                        , Arguments = [ lambdai], ObjectType = 'FormulaVar' )
                return self._parseArg( Name+'_OrthogTot_cos_%s' % (key0), {}, Arguments = [norm,cosForm,angTerm], ObjectType = 'Product' )
            elif Coef=='sin':
                sinForm = self._parseArg(Name+'_Orthog_sin_%s' % (key0),{}, Formula = '2.0 * @0 * @1 * sin(@2) / (1.0+@1*@1)'
                        , Arguments = [ eta1, lambdai, phii ], ObjectType = 'FormulaVar' )
                return self._parseArg( Name+'_OrthogTot_sin_%s' % (key0), {}, Arguments = [norm,sinForm,angTerm], ObjectType = 'Product' )

            print 20 * "*"
            print "Misconfiguration in orthogonal definitions"
            print 20 * "*"
            return
        
        def imaginary(key0,key1,Amplitudes,CPParams,angTerm,eta1,eta2,Coef,singleCP):
            assert Coef in ( 'cos', 'sin', 'sinh', 'cosh' )

            # Get the amplitude
            ai = Amplitudes[Name+key0]
            aj = Amplitudes[Name+key1]
            # mag2
            aisq = ai.Mag2
            ajsq = aj.Mag2
            # phase
            delta_i = ai.Phase
            delta_j = aj.Phase
            # lambda
            lambdai = CPParams[Name+'rhoCP_%s' % key0[ 1 : ] ]
            lambdaj = CPParams[Name+'rhoCP_%s' % key1[ 1 : ] ]
            # weak phase
            phii = CPParams[Name+'phiCPRel_%s' % key0[ 1 : ] ]
            phij = CPParams[Name+'phiCPRel_%s' % key1[ 1 : ] ]
            
            # If single CP, give the 0 polarisation
            if singleCP:
                lambdai = CPParams[Name+'rhoCP_0']
                phii = self.phis
            elif "0" not in key0:
                phii = CPParams[Name+'phiCPRelNonShifted_%s' % key0[ 1 : ]]
            elif "0" not in key1:
                phij = CPParams[Name+'phiCPRelNonShifted_%s' % key1[ 1 : ]]

            # note minus sign or not depending on whether its there
            norm = self._parseArg(Name+'_NormIm_%s_%s_%s' % (Coef,key0,key1),{}, Formula = '0.5*sqrt(@0)*sqrt(@1)', Arguments = [ aisq, ajsq ], ObjectType = 'FormulaVar' )

            if Coef=='cosh':
                if singleCP:
                    coshForm = self._parseArg(Name+'_Im_cosh_%s_%s' % (key0,key1),{}, Formula = 'sin(@0 - @1) + @2*@3*@4*@4*sin(@0 - @1)'
                            , Arguments = [ delta_i, delta_j, eta1, eta2, lambdai], ObjectType = 'FormulaVar' )
                else:
                    coshForm = self._parseArg(Name+'_Im_cosh_%s_%s' % (key0,key1),{}, Formula = 'sin(@0 - @1) + @4*@5*@6*@7*sin(@0 - @1 - @2 + @3)'
                            , Arguments = [ delta_i, delta_j, phii, phij, eta1, eta2, lambdai, lambdaj], ObjectType = 'FormulaVar' )
                #coshForm.Print()
                return self._parseArg( Name+'_ImTot_cosh_%s_%s' % (key0,key1), {}, Arguments = [norm,coshForm,angTerm], ObjectType = 'Product' )
            elif Coef=='sinh':
                if singleCP:
                    sinhForm = self._parseArg(Name+'_Im_sinh_%s_%s' % (key0,key1),{}, Formula = '-1.0 * @3 * @5 * sin(@0 - @1 - @2) - 1.0 * @4 * @5 * sin(@0 - @1 + @2)'
                            , Arguments = [ delta_i, delta_j, phii, eta1, eta2, lambdai], ObjectType = 'FormulaVar' )
                else:
                    sinhForm = self._parseArg(Name+'_Im_sinh_%s_%s' % (key0,key1),{}, Formula = '-1.0 * @4 * @6 * sin(@0 - @1 - @2) - @5 * @7 * sin(@0 - @1 + @3)'
                            , Arguments = [ delta_i, delta_j, phii, phij, eta1, eta2, lambdai, lambdaj], ObjectType = 'FormulaVar' )
                #sinhForm.Print()
                return self._parseArg( Name+'_ImTot_sinh_%s_%s' % (key0,key1), {}, Arguments = [norm,sinhForm,angTerm], ObjectType = 'Product' )
            elif Coef=='cos':
                if singleCP:
                    cosForm = self._parseArg(Name+'_Im_cos_%s_%s' % (key0,key1),{}, Formula = 'sin(@0 - @1) - @2*@3*@4*@4*sin(@0 - @1)'
                            , Arguments = [ delta_i, delta_j, eta1, eta2, lambdai], ObjectType = 'FormulaVar' )
                else:
                    cosForm = self._parseArg(Name+'_Im_cos_%s_%s' % (key0,key1),{}, Formula = 'sin(@0 - @1) - @4*@5*@6*@7*sin(@0 - @1 - @2 + @3)'
                            , Arguments = [ delta_i, delta_j, phii, phij, eta1, eta2, lambdai, lambdaj], ObjectType = 'FormulaVar' )
                #cosForm.Print()
                return self._parseArg( Name+'_ImTot_cos_%s_%s' % (key0,key1), {}, Arguments = [norm,cosForm,angTerm], ObjectType = 'Product' )
            elif Coef=='sin':
                if singleCP:
                    sinForm = self._parseArg(Name+'_Im_sin_%s_%s' % (key0,key1),{}, Formula = '1.0 * @3 * @5 * cos(@0 - @1 - @2) - 1.0 * @4 * @5 * cos(@0 - @1 + @2)'
                            , Arguments = [ delta_i, delta_j, phii, eta1, eta2, lambdai], ObjectType = 'FormulaVar' )
                else:
                    sinForm = self._parseArg(Name+'_Im_sin_%s_%s' % (key0,key1),{}, Formula = '@4 * @6 * cos(@0 - @1 - @2) - @5 * @7 * cos(@0 - @1 + @3)'
                            , Arguments = [ delta_i, delta_j, phii, phij, eta1, eta2, lambdai, lambdaj], ObjectType = 'FormulaVar' )
                #sinForm.Print()
                return self._parseArg( Name+'_ImTot_sin_%s_%s' % (key0,key1), {}, Arguments = [norm,sinForm,angTerm], ObjectType = 'Product' )

            print 20 * "*"
            print "Misconfiguration in imaginary definitions"
            print 20 * "*"
            return
        
        def real(key0,key1,Amplitudes,CPParams,angTerm,eta1,eta2,Coef,singleCP):
            assert Coef in ( 'cos', 'sin', 'sinh', 'cosh' )

            # Get the amplitude
            ai = Amplitudes[Name+key0]
            aj = Amplitudes[Name+key1]
            # mag2
            aisq = ai.Mag2
            ajsq = aj.Mag2
            # phase
            delta_i = ai.Phase
            delta_j = aj.Phase
            # lambda
            lambdai = CPParams[Name+'rhoCP_%s' % key0[ 1 : ] ]
            lambdaj = CPParams[Name+'rhoCP_%s' % key1[ 1 : ] ]
            # weak phase
            phii = CPParams[Name+'phiCPRel_%s' % key0[ 1 : ] ]
            phij = CPParams[Name+'phiCPRel_%s' % key1[ 1 : ] ]
            
            # If single CP, give the 0 polarisation
            if singleCP:
                lambdai = CPParams[Name+'rhoCP_0']
                phii = self.phis
            elif "0" not in key0:
                phii = CPParams[Name+'phiCPRelNonShifted_%s' % key0[ 1 : ]]
            elif "0" not in key1:
                phij = CPParams[Name+'phiCPRelNonShifted_%s' % key1[ 1 : ]]

            norm = self._parseArg(Name+'_NormRe_%s_%s_%s' % (Coef,key0,key1),{}, Formula = '0.5*sqrt(@0)*sqrt(@1)', Arguments = [ aisq, ajsq ], ObjectType = 'FormulaVar' )

            if Coef=='cosh':
                if singleCP:
                    coshForm = self._parseArg(Name+'_Re_cosh_%s_%s' % (key0,key1),{}, Formula = 'cos(@0 - @1) + @2*@3*@4*@4*cos(@0 - @1)'
                            , Arguments = [ delta_i, delta_j, eta1, eta2, lambdai], ObjectType = 'FormulaVar' )
                else:
                    coshForm = self._parseArg(Name+'_Re_cosh_%s_%s' % (key0,key1),{}, Formula = 'cos(@0 - @1) + @4*@5*@6*@7*cos(@0 - @1 - @2 + @3)'
                            , Arguments = [ delta_i, delta_j, phii, phij, eta1, eta2, lambdai, lambdaj], ObjectType = 'FormulaVar' )
                #coshForm.Print()
                return self._parseArg( Name+'_ReTot_cosh_%s_%s' % (key0,key1), {}, Arguments = [norm,coshForm,angTerm], ObjectType = 'Product' )
            elif Coef=='sinh':
                if singleCP:
                    sinhForm = self._parseArg(Name+'_Re_sinh_%s_%s' % (key0,key1),{}, Formula = '-1.0 * @3 * @5 * cos(@0 - @1 - @2) - @4 * @5 * cos(@0 - @1 + @2)'
                            , Arguments = [ delta_i, delta_j, phii, eta1, eta2, lambdai], ObjectType = 'FormulaVar' )
                else:
                    sinhForm = self._parseArg(Name+'_Re_sinh_%s_%s' % (key0,key1),{}, Formula = '-1.0 * @4 * @6 * cos(@0 - @1 - @2) - @5 * @7 * cos(@0 - @1 + @3)'
                            , Arguments = [ delta_i, delta_j, phii, phij, eta1, eta2, lambdai, lambdaj], ObjectType = 'FormulaVar' )
                #sinhForm.Print()
                return self._parseArg( Name+'_ReTot_sinh_%s_%s' % (key0,key1), {}, Arguments = [norm,sinhForm,angTerm], ObjectType = 'Product' )
            elif Coef=='cos':
                if singleCP:
                    cosForm = self._parseArg(Name+'_Re_cos_%s_%s' % (key0,key1),{}, Formula = 'cos(@0 - @1) - @2*@3*@4*@4*cos(@0 - @1)'
                            , Arguments = [ delta_i, delta_j, eta1, eta2, lambdai], ObjectType = 'FormulaVar' )
                else:
                    cosForm = self._parseArg(Name+'_Re_cos_%s_%s' % (key0,key1),{}, Formula = 'cos(@0 - @1) - @4*@5*@6*@7*cos(@0 - @1 - @2 + @3)'
                            , Arguments = [ delta_i, delta_j, phii, phij, eta1, eta2, lambdai, lambdaj], ObjectType = 'FormulaVar' )
                #cosForm.Print()
                return self._parseArg( Name+'_ReTot_cos_%s_%s' % (key0,key1), {}, Arguments = [norm,cosForm,angTerm], ObjectType = 'Product' )
            elif Coef=='sin':
                if singleCP:
                    sinForm = self._parseArg(Name+'_Re_sin_%s_%s' % (key0,key1),{}, Formula = '-1.0 * @3 * @5 * sin(@0 - @1 - @2) + @4 * @5 * sin(@0 - @1 + @2)'
                            , Arguments = [ delta_i, delta_j, phii, eta1, eta2, lambdai], ObjectType = 'FormulaVar' )
                else:
                    sinForm = self._parseArg(Name+'_Re_sin_%s_%s' % (key0,key1),{}, Formula = '-1.0 * @4 * @6 * sin(@0 - @1 - @2) + @5 * @7 * sin(@0 - @1 + @3)'
                            , Arguments = [ delta_i, delta_j, phii, phij, eta1, eta2, lambdai, lambdaj], ObjectType = 'FormulaVar' )
                #sinForm.Print()
                return self._parseArg( Name+'_ReTot_sin_%s_%s' % (key0,key1), {}, Arguments = [norm,sinForm,angTerm], ObjectType = 'Product' )

            print 20 * "*"
            print "Misconfiguration in real definitions"
            print 20 * "*"
            return
        
        # initialize
        terms={}
        for Coef in ['cosh','sinh','sin','cos']:
            terms[Coef]=[]
        
        for key in keyDict:
            amp1 = Amplitudes[Name+key[0]]
            amp2 = Amplitudes[Name+key[1]]
            eta1 = ConstVar( Name = Name+'_eta_'+key[0],   Value =  amp1.CP )
            eta2 = ConstVar( Name = Name+'_eta_'+key[1],   Value =  amp2.CP )
            angTerm = AngFuncs[key]
            
            for Coef in ['cosh','sinh','sin','cos']:
                if amp1.Phase.GetName()==amp2.Phase.GetName():
                    # Return PDF for orthogonal case
                    terms[Coef].append(orthog(key[0],Amplitudes,CPParams,angTerm,eta1,Coef,singleCP))
                elif key[0]=="Aperp" or key[1]=="Aperp":
                    # Return imaginary interference term
                    terms[Coef].append(imaginary(key[0],key[1],Amplitudes,CPParams,angTerm,eta1,eta2,Coef,singleCP))
                else:
                    # Return real interference term
                    terms[Coef].append(real(key[0],key[1],Amplitudes,CPParams,angTerm,eta1,eta2,Coef,singleCP))
        
        combine = lambda name, args : self._parseArg( name, { }, Arguments = args, ObjectType = 'Addition' )

        args_Combine={}
        for Coef in ['cosh','sinh','sin','cos']:
            args_Combine[Coef] = combine(Name + "_" + Coef, terms[Coef])
        BDecayBasisCoefficients.__init__( self, **args_Combine )


class TimePdf( _util_parse_mixin ) :
    def __init__( self, **kwargs ) :
        self._pdf = kwargs.pop('pdf')
        self._efficiency = kwargs.pop( 'Efficiency', None )
        if self._efficiency : self._pdf = self._efficiency * self._pdf
        for (k,v) in kwargs.iteritems() : setattr( self, '_' + k, v )

    def pdf(self) : return self._pdf

class LP2011_Background_Time( TimePdf ) :
    def __init__(self, time, resolutionModel, **kwargs) :
        Name = kwargs.pop('Name', self.__class__.__name__)
        self._ml_tau = self._parseArg( '%s_ml_tau' % Name, kwargs, Title = 'medium lifetime background ', Unit = 'ps'
                                      , Value = 0.152, Error = 0.003, MinMax = (0.001, 10.))
        self._ll_tau = self._parseArg( '%s_ll_tau' % Name, kwargs, Title = 'long lifetime background ',   Unit = 'ps'
                                      , Value = 1.4,  Error = 0.04,  MinMax = (0.1, 10.))
        self._fml = self._parseArg(    '%s_fml' % Name,    kwargs, Title = 'fraction medium lifetime background'
                                      , Value = 0.79,  Error = 0.01,  MinMax = (0.0001, 0.999))

        from P2VV.RooFitWrappers import  SumPdf,Pdf
        from ROOT import RooDecay as Decay
        self._mlPdf = Pdf(  Name = Name + '_ml'
                          , Type = Decay
                          , Parameters = (time, self._ml_tau, resolutionModel, 'SingleSided')
                          , ConditionalObservables = resolutionModel.ConditionalObservables()
                          , ExternalConstraints = resolutionModel.ExternalConstraints()
                         )
        self._llPdf = Pdf(  Name = Name + '_ll'
                          , Type = Decay
                          , Parameters = (time, self._ll_tau, resolutionModel, 'SingleSided')
                          , ConditionalObservables = resolutionModel.ConditionalObservables()
                          , ExternalConstraints = resolutionModel.ExternalConstraints()
                         )

        efficiency = kwargs.pop( 'Efficiency', None )
        if efficiency :
            self._mlPdf = efficiency * self._mlPdf
            self._llPdf = efficiency * self._llPdf

        self._check_extraneous_kw( kwargs )
        TimePdf.__init__( self, pdf = SumPdf(  Name = Name
                                             , PDFs = ( self._mlPdf, self._llPdf)
                                             , Yields = { self._mlPdf.GetName() : self._fml }
                                            )
                        )
        self._efficiency = efficiency

class Single_Exponent_Time( TimePdf ) :
    def __init__(self,time,resolutionModel,**kwargs) :
        self._parseArg('tau', kwargs, Title = 'lifetime', Unit = 'ps', Value = 1.5, Error = 0.05, MinMax = ( 0.1, 10. ) )

        from P2VV.RooFitWrappers import Pdf
        from ROOT import RooDecay as Decay
        TimePdf.__init__(self, pdf = Pdf( Name = kwargs.pop('Name',self.__class__.__name__)
                                          , Type = Decay
                                          , Parameters = (time, self._tau,resolutionModel,'SingleSided')
                                          , ConditionalObservables = resolutionModel.ConditionalObservables()
                                          , ExternalConstraints = resolutionModel.ExternalConstraints())
                         )

class Prompt_Peak( TimePdf ) :
    def __init__(self, time, resolutionModel, **kwargs) :
        namePF = self.getNamePrefix(kwargs)
        self._parseArg( 'prompt_tau', kwargs, Title = 'lifetime', Unit = 'ps', Value = 0, Constant = True )

        from P2VV.RooFitWrappers import Pdf
        from ROOT import RooDecay as Decay
        TimePdf.__init__(self, pdf = Pdf( Name = namePF + kwargs.pop('Name', self.__class__.__name__)
                                          , Type = Decay
                                          , Parameters = (time, self._prompt_tau, resolutionModel, 'SingleSided')
                                          , ConditionalObservables = resolutionModel.ConditionalObservables()
                                          , ExternalConstraints = resolutionModel.ExternalConstraints())
                     )

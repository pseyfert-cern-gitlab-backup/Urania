###########################################################################################################################################
## Utilities.DataMoments: P2VV utilities for computing and using (efficiency) moments                                                    ##
##                                                                                                                                       ##
## authors:                                                                                                                              ##
##   GR,  Gerhard Raven,      Nikhef & VU, Gerhard.Raven@nikhef.nl                                                                       ##
##   JvL, Jeroen van Leerdam, Nikhef,      j.van.leerdam@nikhef.nl                                                                       ##
##   VS,  Vasilis Syropoulos, Nikhef,      v.syropoulos@nikhef.nl                                                                        ##
##                                                                                                                                       ##
###########################################################################################################################################

def angularMomentIndices( label, angleFuncs, p2vvDecay ) :
    if p2vvDecay == 'jpsiphi':
        from P2VV.Parameterizations.AngularFunctions import JpsiphiHelicityAngles as HelicityAngles
        from P2VV.Parameterizations.AngularFunctions import JpsiphiTransversityAngles as TransversityAngles 
    elif p2vvDecay == 'jpsiKst':
        from P2VV.Parameterizations.AngularFunctions import JpsiKstHelicityAngles as HelicityAngles
        from P2VV.Parameterizations.AngularFunctions import JpsiKstTransversityAngles as TransversityAngles 
    else: assert False, 'P2VV - ERROR: angularMomentIndices: Provided p2vv decay "%s" is unknown. Provide either jpsiphi or jpsiKst.'%p2vvDecay
    transAngles = { TransversityAngles : True, HelicityAngles : False  }[ type(angleFuncs) ]
    
    from P2VV.Utilities.General import switch
    for case in switch(label):
        if case('weights') :
            return [ ( 0, 0, 0 ), ( 0, 2, 0 ), ( 0, 2, 2 ), ( 2, 0, 0 ), ( 0, 2, 1 ), ( 0, 2, -1 ), ( 0, 2, -2 )
                   , ( 1, 0, 0 ), ( 1, 2, 1 ), ( 1, 2, -1 ) ]
        if case('weightsPlus1') :
            return [ ( 0, 0, 0 ), ( 0, 2, 0 ), ( 0, 2, 2 ), ( 2, 0, 0 ), ( 0, 2, 1 ), ( 0, 2, -1 ), ( 0, 2, -2 )
                   , ( 1, 0, 0 ), ( 1, 2, 1 ), ( 1, 2, -1 ), ( 0, 1, 0 ), ( 0, 1, 1 ) ]
        if case('basis012') :
            return [ ( PIndex, YIndex0, YIndex1 ) for PIndex in range(3) for YIndex0 in range(3)\
                         for YIndex1 in range( -YIndex0, YIndex0 + 1 ) ]
        if case('basis012Plus') :
            return [ ( PIndex, YIndex0, YIndex1 ) for PIndex in range(3) for YIndex0 in range(3)\
                          for YIndex1 in range( -YIndex0, YIndex0 + 1 ) ] + [ ( 0, 4, 0 ) ]
        if case( 'basis012Thetal' ) :
            return   [ ( PIndex, YIndex0, YIndex1 ) for PIndex in range(3) for YIndex0 in range(3)\
                           for YIndex1 in range( -YIndex0, YIndex0 + 1 ) ] \
                   + [ ( 0, YIndex0, 0 ) for YIndex0 in range( 3, 5 ) ]
        if case('basis012ThetalPhi') :
            return  [ ( PIndex, YIndex0, YIndex1 ) for PIndex in range(3) for YIndex0 in range(3)\
                           for YIndex1 in range( -YIndex0, YIndex0 + 1 ) ] \
                  + [ ( 0, YIndex0, YIndex1 ) for YIndex0 in range( 3, 5 ) for YIndex1 in range( -YIndex0, YIndex0 + 1 ) ]
        if case('basis0123') :
            return [ ( PIndex, YIndex0, YIndex1 ) for PIndex in range(4) for YIndex0 in range(4)\
                          for YIndex1 in range( -YIndex0, YIndex0 + 1 ) ]
        if case('basis01234') :
            return  [ ( PIndex, YIndex0, YIndex1 ) for PIndex in range(5) for YIndex0 in range(5)\
                          for YIndex1 in range( -YIndex0, YIndex0 + 1 ) ]
        if case('basisSig3') :
            return [ ( 0, 0, 0 ), ( 2, 0, 0 ), ( 0, 2, 0 ) ] if not transAngles\
                          else [ ( 0, 0, 0 ), ( 2, 0, 0 ), ( 0, 2, 0 ), ( 0, 2, 2 ) ]
        if case('basisSig4') :
            if transAngles :
                raise RuntimeError('P2VV - ERROR: angularMomentIndices: not a valid angular efficiency configuration with transversity angles: %s'\
                                   % multiplyByAngEff)
            return [ ( 0, 0, 0 ), ( 2, 0, 0 ), ( 0, 2, 0 ), ( 0, 4, 0 ) ]
        if case('basisSig6') :
            if transAngles :
                raise RuntimeError('P2VV - ERROR: angularMomentIndices: not a valid angular efficiency configuration with transversity angles: %s'\
                                   % multiplyByAngEff)
            return [ ( 0, 0, 0 ), ( 2, 0, 0 ), ( 0, 2, 0 ), ( 0, 2, 2 ), ( 0, 4, 0 ), ( 4, 0, 0 ) ]

        # first Kp bin
        if case('bin1_neg_2011'):
            return { 'fit':False, 'constrain':False,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (0, 1, 1), (2, 2, 0) ]}#, (2, 3, 0), (2, 4, 0) ] }
        if case('bin1_neg_2012'):
            return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (0, 1, 1), (2, 2, 0), (2, 3, 0), (2, 4, 0) ] }
        if case('bin1_pos_2011'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (0, 1, 1), (2, 2, 0) ]}#, (2, 3, 0), (2, 4, 0) ] }
        if case('bin1_pos_2012'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0), (2, 3, 0), (2, 4, 0) ] }
        # second Kp bin    
        if case('bin2_neg_2011'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (0, 1, 1), (2, 2, 0), (2, 3, 0) ]}#,(2, 4, 0) ] }
        if case('bin2_neg_2012'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (0, 1, 1),  (2, 2, 0), (2, 3, 0),]}# (2, 4, 0) ] }
        if case('bin2_pos_2011'):
                return { 'fit':False, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (0, 1, 1), (2, 2, 0),]}# (2, 3, 0),]}# (2, 4, 0) ] }
        if case('bin2_pos_2012'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (0, 1, 1), (2, 2, 0), (2, 3, 0), (2, 4, 0) ] }
        # third Kp bin
        if case('bin3_neg_2011'): # This is problematic in cosThL= +/-1
                return { 'fit':False, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 ]}#(2, 2, 0), (2, 3, 0), (2, 4, 0) ]}#(2, 4, 0) ] }
        if case('bin3_neg_2012'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]}# (2, 3, 0), (2, 4, 0) ] }
        if case('bin3_pos_2011'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                (2, 2, 0),]}# (2, 3, 0), (2, 4, 0) ] }
        if case('bin3_pos_2012'):
                return { 'fit':False, 'constrain':True, # This is problematic in cosThL= +/-1
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]}# (2, 3, 0), (2, 4, 0) ] }
        # fourth Kp bin    
        if case('bin4_neg_2011'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                  (2, 2, 0), (2, 3, 0),]}# (2, 4, 0) ] }
        if case('bin4_neg_2012'):
                return { 'fit':False, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (0, 1, 1), (2, 2, 0), (2, 3, 0), (2, 4, 0) ] }
        if case('bin4_pos_2011'):
            return { 'fit':False, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0), ]}#(2, 3, 0), (2, 4, 0) ] }
        if case('bin4_pos_2012'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (0, 1, 1), (2, 2, 0), (2, 3, 0), (2, 4, 0) ] }

        # merge periods bin1
        if case('bin1_neg'):
                return { 'fit':False, 'constrain':False,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]}# (2, 3, 0), (2, 4, 0) ]}#(2, 4, 0) ] }
        if case('bin1_pos'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]}# (2, 3, 0), (2, 4, 0) ] }
        # merge periods bin2
        if case('bin2_neg'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]} #(2, 3, 0), (2, 4, 0) ]}#(2, 4, 0) ] }
        if case('bin2_pos'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]}# (2, 3, 0), (2, 4, 0) ] }
        # merge periods bin3
        if case('bin3_neg'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]} #(2, 3, 0), (2, 4, 0) ]}#(2, 4, 0) ] }
        if case('bin3_pos'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]}# (2, 3, 0), (2, 4, 0) ] }
        # merge periods bin4
        if case('bin4_neg'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]} #(2, 3, 0), (2, 4, 0) ]}#(2, 4, 0) ] }
        if case('bin4_pos'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]}# (2, 3, 0), (2, 4, 0) ] }

        # merge KpiBins
        if case('all_pos'):
                return { 'fit':False, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]}# (2, 3, 0), (2, 4, 0) ] }
        if case('all_neg'):
                return { 'fit':True, 'constrain':True,
                     'indices':[ (0, 0, 0), (1, 0, 0), (2, 0, 0), (0, 2, 0), (0, 4, 0), (3, 0, 0), (4, 0, 0), (6, 0, 0),
                                 (2, 2, 0),]}# (2, 3, 0), (2, 4, 0) ] }

        raise RuntimeError('P2VV - ERROR: angularMomentIndices: not a valid angular efficiency configuration: %s'% label)


def getMomentFuncArgs( funcName, kwargs ) :
    # new moments or append to existing moments?
    kwargs['addFacs'] = kwargs.pop( 'AddMoments', ( ) )

    # process all moments?
    kwargs['procAll'] = kwargs.pop( 'ProcessAll', False )

    # moments and correlations
    funcNames    = kwargs.pop( 'BasisFuncNames', [ ] )
    moments      = kwargs.pop( 'Moments',        { } )
    correlations = kwargs.pop( 'Correlations',   { } )
    if ( kwargs['addFacs'] or not kwargs['procAll'] ) and not funcNames :
        print 'P2VV - ERROR: %s(): no basis function names specified' % ( funcName if funcName else 'getMomentFuncArgs' )
        return False
    for name in funcNames :
        if moments and name not in moments :
            print 'P2VV - ERROR: %s(): could not find moment of function "%s"' % ( funcName if funcName else 'getMomentFuncArgs', name )
            return False
        if correlations and name not in correlations :
            print 'P2VV - ERROR: %s(): could not find correlations for function "%s"'\
                  % ( funcName if funcName else 'getMomentFuncArgs', name )
            return False
    kwargs.update( dict( funcNames = funcNames, moments = moments, correlations = correlations ) )

    # maximum length of basis function name
    maxName = 0
    for func in funcNames : maxName = max( len(func), maxName )
    kwargs['maxLenName'] = max( 15, min( [ kwargs.pop( 'MaxLenName', 20 ), maxName ] ) )

    # name requirements
    kwargs['names'] = kwargs.pop( 'Names', None )
    import re
    kwargs['nameExpr'] = re.compile( kwargs['names'] ) if kwargs['names'] else None

    # minimum significance
    kwargs['minSignif'] = kwargs.pop( 'MinSignificance', float('-inf') )

    # scale factors
    kwargs['scale']  = kwargs.pop( 'Scale',  1. )
    kwargs['scales'] = kwargs.pop( 'Scales', ( kwargs['scale'], kwargs['scale'], 1. ) )

    return True


def printMoments( **kwargs ) :
    # parse arguments
    assert getMomentFuncArgs( 'printMoments', kwargs ), 'P2VV - ERROR: printMoments(): unable to parse function arguments'

    # print header
    print 'P2VV - INFO: printMoments():'
    print '  name requirement: \'' + ( kwargs['names'] if kwargs['names'] else '' ) + '\''
    print '  minimum significance = %.1f' % kwargs['minSignif']
    print '  scales = ({0:.5g}, {1:.5g}, {2:.5g})'.format( kwargs['scales'][0], kwargs['scales'][1], kwargs['scales'][2] )
    print '  ' + '-' * ( 45 + kwargs['maxLenName'] )
    print ( '  {0:<%d}   {1:>11}   {2:>9}   {3:>12}' % kwargs['maxLenName'] )\
            .format( 'basis function', 'coefficient', 'std. dev.', 'significance' )
    print '  ' + '-' * ( 45 + kwargs['maxLenName'] )

    # print moments
    for func in kwargs['funcNames'] :
        if ( kwargs['nameExpr'] and not kwargs['nameExpr'].match(func) )\
                or ( func in kwargs['moments'] and kwargs['moments'][func][2] < kwargs['minSignif'] ) :
            continue

        print ( '  {0:<%d}' % kwargs['maxLenName'] )\
                .format( func if len(func) <= kwargs['maxLenName'] else '...' + func[ 3 - kwargs['maxLenName'] : ] ),
        if func not in kwargs['moments'] :
            print
            continue

        coef = kwargs['moments'][func]
        print '  {0:>+11.5f}   {1:>9.5f}   {2:>12.1f}'\
              .format( coef[0] * kwargs['scales'][0], coef[1] * kwargs['scales'][1], coef[2] * kwargs['scales'][2] )

    print '  ' + '-' * ( 45 + kwargs['maxLenName'] ) + '\n'

    if not kwargs['correlations'] : return

    # print correlation matrix
    print '  correlation matrix:'
    print ' ' * ( 2 + kwargs['maxLenName'] ),
    for func2 in kwargs['funcNames'] :
        if ( kwargs['nameExpr'] and not kwargs['nameExpr'].match(func2) )\
                or ( func2 in kwargs['moments'] and kwargs['moments'][func2][2] < kwargs['minSignif'] ) :
            continue
        print ( '  {0:>11}' ).format( func2 if len(func2) <= 11 else '.' + func2[ 1 - 11 : ] ),
    print

    for it1, func1 in enumerate(kwargs['funcNames']) :
        if ( kwargs['nameExpr'] and not kwargs['nameExpr'].match(func1) )\
                or ( func1 in kwargs['moments'] and kwargs['moments'][func1][2] < kwargs['minSignif'] ) :
            continue
        print ( '  {0:<%d}' % kwargs['maxLenName'] )\
                .format( func1 if len(func1) <= kwargs['maxLenName'] else '...' + func1[ 3 - kwargs['maxLenName'] : ] ),
        if func1 not in kwargs['correlations'] :
            print
            continue

        for it2, func2 in enumerate(kwargs['funcNames']) :
            if ( kwargs['nameExpr'] and not kwargs['nameExpr'].match(func2) )\
                    or ( func2 in kwargs['moments'] and kwargs['moments'][func2][2] < kwargs['minSignif'] ) :
                continue
            if it2 >= it1 :
                print '  {0:>+11.3f}'.format( kwargs['correlations'][func1][func2] ),
            else :
                print ' ' * 13,
        print

    print


def writeMoments( filePath = 'moments', **kwargs ) :
    # parse arguments
    assert getMomentFuncArgs( 'writeMoments', kwargs ), 'P2VV - ERROR: writeMoments(): unable to parse function arguments'
    verb = kwargs.pop( 'Verbose', True )

    # get file path and name
    filePath = filePath.strip()
    fileName = filePath.split('/')[-1]

    # open file
    try :
        momFile = open( filePath, 'w' )
    except :
        raise IOError( 'P2VV - ERROR: writeMoments(): unable to open file \"%s\"' % filePath )

    # write moments to content string
    cont = '# %s: angular moments\n' % fileName\
         + '# name requirement: \'{0}\'\n'.format( kwargs['names'] if kwargs['names'] else '' )\
         + '# minimum significance = {0:.1f}\n'.format(kwargs['minSignif'])\
         + '# scales = ({0:.5g}, {1:.5g}, {2:.5g})\n'.format( kwargs['scales'][0], kwargs['scales'][1], kwargs['scales'][2] )\
         + '#\n'\
         + '# ' + '-' * ( 49 + kwargs['maxLenName'] ) + '\n'\
         + ( '# {0:<%s}   {1:<14}   {2:<13}   {3:<13}\n' % kwargs['maxLenName'] )\
               .format( 'basis function', 'coefficient', 'std. dev.', 'significance' )\
         + '# ' + '-' * ( 49 + kwargs['maxLenName'] ) + '\n'

    numMoments = 0
    for func in kwargs['funcNames'] :
        if ( kwargs['nameExpr'] and not kwargs['nameExpr'].match(func) )\
                or ( func in kwargs['moments'] and kwargs['moments'][func][2] < kwargs['minSignif'] ) :
            continue

        cont += ( '  {0:<%s}' % kwargs['maxLenName'] ).format(func)
        if func in kwargs['moments'] :
            coef = kwargs['moments'][func]
            cont += '   {0:<+14.8g}   {1:<13.8g}   {2:<13.8g}\n'\
                    .format( coef[0] * kwargs['scales'][0], coef[1] * kwargs['scales'][1], coef[2] * kwargs['scales'][2] )
            numMoments += 1

        else :
            cont += '\n'

    cont += '# ' + '-' * (49 + kwargs['maxLenName']) + '\n'

    if kwargs['correlations'] :
        # write correlation matrix to content string
        cont += '#\n# correlation matrix:\n'
        cont += ' ' * ( 2 + kwargs['maxLenName'] )
        for func2 in kwargs['funcNames'] :
            if ( kwargs['nameExpr'] and not kwargs['nameExpr'].match(func2) )\
                    or ( func2 in kwargs['moments'] and kwargs['moments'][func2][2] < kwargs['minSignif'] ) :
                continue
            cont += ( '  {0:>12}' ).format( func2 if len(func2) <= 12 else '.' + func2[ 1 - 12 : ] )
        cont += '\n'

        for it1, func1 in enumerate(kwargs['funcNames']) :
            if ( kwargs['nameExpr'] and not kwargs['nameExpr'].match(func1) )\
                    or ( func1 in kwargs['moments'] and kwargs['moments'][func1][2] < kwargs['minSignif'] ) :
                continue
            cont += ( '  {0:<%d}' % kwargs['maxLenName'] ).format(func1)
            if func1 not in kwargs['correlations'] :
                cont += '\n'
                continue

            for it2, func2 in enumerate(kwargs['funcNames']) :
                if ( kwargs['nameExpr'] and not kwargs['nameExpr'].match(func2) )\
                        or ( func2 in kwargs['moments'] and kwargs['moments'][func2][2] < kwargs['minSignif'] ) :
                    continue
                cont += '  {0:>+12.6g}'.format( kwargs['correlations'][func1][func2] )
            cont += '\n'

    # write content to file
    momFile.write(cont)
    momFile.close()

    if verb :
        print 'P2VV - INFO: writeMoments(): %d efficiency moment%s written to file \"%s\"'\
              % ( numMoments, '' if numMoments == 1 else 's', filePath )


def readMoments( filePath = 'moments', **kwargs ) :
    # parse arguments
    assert getMomentFuncArgs( 'readMoments', kwargs ), 'P2VV - ERROR: readMoments(): unable to parse function arguments'
    verb = kwargs.pop( 'Verbose', True )

    # reset moments and correlations dictionaries
    if not kwargs['addFacs'] :
        if kwargs['procAll'] : del kwargs['funcNames'][ : ]
        kwargs['moments'].clear()
        kwargs['correlations'].clear()

    # get file path
    filePath = filePath.strip()

    # open file
    try :
      momFile = open(filePath, 'r')
    except :
      raise IOError( 'P2VV - ERROR: readMoments(): unable to open file \"%s\"' % filePath )

    # loop over lines and read moments
    from math import sqrt
    numMoments = 0
    corrMatrix = False
    funcNamesMoms = [ ]
    funcNamesCorrs = [ ]
    correlations = [ ]
    while True :
        # read next line
        line = momFile.readline()
        if not line : break

        # check for empty or comment lines and start of correlation matrix
        line = line.strip()
        if 'correlation' in line : corrMatrix = True
        if not line or line[0] == '#' : continue
        line = line.split()

        if not corrMatrix :
            # check moment format
            if len(line) < 4 or ( not kwargs['addFacs'] and not kwargs['procAll'] and line[0] not in kwargs['funcNames'] ) : continue
            try :
              coef   = float(line[1])
              stdDev = float(line[2])
              signif = float(line[3])
            except :
              continue

            # check significance and name
            if ( kwargs['nameExpr'] and not kwargs['nameExpr'].match(line[0]) ) or signif < kwargs['minSignif'] : continue

            # get moment
            if kwargs['addFacs'] :
                assert line[0] in kwargs['moments'], 'P2VV - ERROR: readMoments(): moment %s does not exist yet' % line[0]
                origCoef, origStdDev = kwargs['moments'][line[0]][ : 2 ]
                totCoef = kwargs['addFacs'][0] * origCoef + kwargs['addFacs'][1] * coef
                totStdDev = sqrt( kwargs['addFacs'][0]**2 * origStdDev**2 + kwargs['addFacs'][1]**2 * stdDev**2 )
                kwargs['moments'][line[0]] = ( totCoef, totStdDev, abs(totCoef) / totStdDev )
            else :
                kwargs['moments'][line[0]] = ( coef, stdDev, signif )
            numMoments += 1
            if kwargs['procAll'] : kwargs['funcNames'].append(line[0])
            funcNamesMoms.append(line[0])

        else :
            # read correlation matrix row
            if len(line) < 1 + numMoments or type(line[0]) != str : continue
            try :
                corrs = [ float(corr) for corr in line[ 1 : ] ]
            except :
                continue
            funcNamesCorrs.append(line[0])
            correlations.append(corrs)

    momFile.close()

    # process correlation matrix
    if corrMatrix :
        # check which moments to include in correlation matrix
        skipInds = [ ]
        for it, func in enumerate(funcNamesCorrs) :
            if func not in funcNamesMoms : skipInds.append(it)
        assert len(funcNamesCorrs) - len(skipInds) == numMoments\
               , 'P2VV - ERROR: readMoments(): number of rows in correlation matrix is not consistent with number of moments read'

        if kwargs['addFacs'] :
            print 'P2VV - WARNING: readMoments(): appending correlations matrices not implemented yet'

        else :
            # construct correlation matrix
            for func1, corrs in zip( funcNamesCorrs, correlations ) :
                if func1 not in funcNamesMoms : continue
                kwargs['correlations'][func1] = { }
                for it, func2 in enumerate(funcNamesCorrs) :
                    if func2 not in funcNamesMoms : continue
                    kwargs['correlations'][func1][func2] = corrs[it]

                assert len(kwargs['correlations'][func1]) == numMoments\
                     , 'P2VV - ERROR: readMoments(): number of columns in correlation matrix is not consistent with number of moments read'

            assert len(kwargs['correlations']) == numMoments\
                   , 'P2VV - ERROR: readMoments(): number of rows in correlation matrix is not consistent with number of moments read'

    if verb :
        print 'P2VV - INFO: readMoments(): %d efficiency moment%s read from file \"%s\"'\
              % ( numMoments, '' if numMoments == 1 else 's', filePath )


def convertEffWeightsToMoments( Weights, **kwargs ) :
    verb = kwargs.pop( 'Verbose', True )
    pols = [ '0 0', 'para para', 'perp perp', '0 para', '0 perp', 'para perp', 'S S', '0 S', 'para S', 'perp S' ]
    wNames = kwargs.pop( 'WeightNames'
                        , { '0 0' : 'Re_ang_A0_A0', 'para para' : 'Re_ang_Apar_Apar', 'perp perp' : 'Re_ang_Aperp_Aperp'
                           , '0 para' : 'Re_ang_A0_Apar', '0 perp' : 'Im_ang_A0_Aperp', 'para perp' : 'Im_ang_Apar_Aperp'
                           , 'S S' : 'Re_ang_AS_AS', '0 S' : 'Re_ang_A0_AS', 'para S' : 'Re_ang_Apar_AS', 'perp S' : 'Im_ang_Aperp_AS'
                          }
                       )
    pref = kwargs.pop('WeightNamesPrefix', '')
    if pref:
        for wNam in wNames.keys(): wNames[wNam] = pref + '_' + wNames[wNam]

    for pol in pols :
        assert pol in wNames.keys()\
            , 'P2VV - ERROR: convertEffWeightsToMoments(): polarization "%s" not found in weight names dictionary' % pol
        assert wNames[pol] in Weights.keys()\
            , 'P2VV - ERROR: convertEffWeightsToMoments(): weight "%s" not found in weights dictionary' % wNames[pol]

    momNames = [  'p2vvab_0000', 'p2vvab_0020',  'p2vvab_0022'
                , 'p2vvab_0021', 'p2vvab_002m1', 'p2vvab_002m2'
                , 'p2vvab_1000', 'p2vvab_1021',  'p2vvab_102m1'
                , 'p2vvab_2000'
               ]

    # convert weights to moments
    from math import sqrt, pi
    coef = lambda name : Weights[ wNames[name] ][0]
    moms = { }
    moms['p2vvab_0000']  =   1. / 3.                        * ( coef('0 0') + coef('para para') + coef('perp perp') )
    moms['p2vvab_0020']  =   1. / 3. * sqrt(5.)             * ( coef('0 0') + coef('para para') + coef('perp perp') - 3. * coef('S S') )
    moms['p2vvab_0022']  =            -sqrt(5. / 3.)        * ( coef('para para') - coef('perp perp') )
    moms['p2vvab_2000']  =   5. / 2.                        * ( coef('0 0') - coef('S S') )
    moms['p2vvab_0021']  = - 8. / 3. * sqrt( 5. / 2. ) / pi *   coef('para S')
    moms['p2vvab_002m1'] = - 8. / 3. * sqrt( 5. / 2. ) / pi *  -coef('perp S')
    moms['p2vvab_002m2'] =             sqrt( 5. / 3. )      *  -coef('para perp')
    moms['p2vvab_1000']  =   1. / 2. * sqrt(3.)             *   coef('0 S')
    moms['p2vvab_1021']  = -32. / 3. * sqrt( 5. / 6. ) / pi *   coef('0 para')
    moms['p2vvab_102m1'] = +32. / 3. * sqrt( 5. / 6. ) / pi *  -coef('0 perp')

    # match the general moments coefficients format
    for name in momNames : moms[name] = ( moms[name], 0., 0. )

    # get scale factor for moment coefficient
    scale = kwargs.pop( 'Scale', 1. )

    if kwargs.pop( 'PrintMoments', verb ) or verb:
        # print moments to screen
        printMoments( BasisFuncNames = momNames, Moments = moms, Scale = scale )

    if kwargs.get( 'OutputFilePath', '' ) :
        # write the moments to a file
        writeMoments( kwargs.pop('OutputFilePath'), BasisFuncNames = momNames, Moments = moms, Scale = scale, Verbose = verb )

    # check if there are remaining keyword arguments
    assert len(kwargs) == 0, 'P2VV - ERROR: convertEffWeightsToMoments(): unused keyword arguments: %s' % kwargs


def multiplyP2VVAngleBases( angleBasis, **kwargs ) :
    doReset = kwargs.pop( 'DoReset', True )

    def __dref__(arg) :
        from ROOT import RooAbsArg
        if isinstance( arg, RooAbsArg ) : return arg
        return arg._var

    if 'Functions' in kwargs :
        funcs = kwargs.pop('Functions')
        if 'Coefficients' in kwargs :
            coefs = kwargs.pop('Coefficients')
            assert len(funcs) == len(coefs)\
                   , 'P2VV - ERROR: multiplyP2VVAngleBases(): numbers of functions and coefficients are different'
        else :
            coefs = [ ConstVar( Name = 'one', Value = 1. ) for it in range( len(funcs) ) ]

        from ROOT import RooArgList
        funcList = RooArgList( __dref__(func) for func in funcs )
        coefList = RooArgList( __dref__(coef) for coef in coefs )
        angleBasis.createProdSum( funcList, coefList, doReset )

    elif all( inds in kwargs for inds in ( 'iIndices', 'jIndices', 'lIndices', 'mIndices' ) ) :
        iInds = kwargs.pop('iIndices')
        jInds = kwargs.pop('jIndices')
        lInds = kwargs.pop('lIndices')
        mInds = kwargs.pop('mIndices')
        assert len(iInds) == len(jInds) == len(lInds) == len(mInds)\
               , 'P2VV - ERROR: multiplyP2VVAngleBases(): different numbers i, j, l and m indices specified'

        if 'FixedCoefs' in kwargs :
            fixCoefs = kwargs.pop('FixedCoefs')
            assert len(iInds) == len(fixCoefs)\
                   , 'P2VV - ERROR: multiplyP2VVAngleBases(): numbers of indices and fixed coefficients are different'
        else :
            fixCoefs = [ 1. for it in range( len(iInds) ) ]

        if 'Coefficients' in kwargs :
            coefs = kwargs.pop('Coefficients')
            assert len(iInds) == len(coefs)\
                   , 'P2VV - ERROR: multiplyP2VVAngleBases(): numbers of indices and coefficients are different'
        else :
            coefs = [ ConstVar( Name = 'one', Value = 1. ) for it in range( len(iInds) ) ]

        from ROOT import std
        iIndsVec    = std.vector('Int_t')()
        jIndsVec    = std.vector('Int_t')()
        lIndsVec    = std.vector('Int_t')()
        mIndsVec    = std.vector('Int_t')()
        fixCoefsVec = std.vector('Double_t')()
        for ind  in iInds    : iIndsVec.push_back(ind)
        for ind  in jInds    : jIndsVec.push_back(ind)
        for ind  in lInds    : lIndsVec.push_back(ind)
        for ind  in mInds    : mIndsVec.push_back(ind)
        for coef in fixCoefs : fixCoefsVec.push_back(coef)

        from ROOT import RooArgList
        coefList = RooArgList( __dref__(coef) for coef in coefs )

        angleBasis.createProdSum( iIndsVec, jIndsVec, lIndsVec, mIndsVec, fixCoefsVec, coefList, doReset )

    else :
        raise RuntimeError, 'P2VV - ERROR: multiplyP2VVAngleBases(): either functions or indices should be specified'


def normalizeMoments( momentsFileOrig, momentsFileNorm, normMoment = 'Re_ang_A0_A0', printMoms = True ):
    # moment containers
    funcNames = [ ]
    moments = { }
    correlations = { }
    
    # read moments
    print 'input moments:'
    from P2VV.Utilities.DataMoments import readMoments, printMoments
    readMoments( momentsFileOrig, BasisFuncNames = funcNames, Moments = moments, Correlations = correlations, ProcessAll = True )
    if printMoms: printMoments( BasisFuncNames = funcNames, Moments = moments, Correlations = correlations )
    
    # calculate moments with new normalization
    from math import sqrt
    valNorm = moments[normMoment][0]
    errNorm = moments[normMoment][1]
    momsNew  = { }
    corrsNew = { }
    # moments value and error
    for name in funcNames :
        valNew   = moments[name][0] / valNorm
        err      = moments[name][1]
        corrNorm = correlations[name][normMoment]
        varNew   = ( err**2 + valNew**2 * errNorm**2 - 2. * valNew * err * errNorm * corrNorm ) / valNorm**2
        momsNew[name] = ( valNew, sqrt(varNew), ( sqrt( valNew**2 / varNew ) ) if varNew != 0. else 0. if valNew == 0. else float('inf') )
        corrsNew[name] = { }
    
    # moments correlations
    for name0 in funcNames :
        for name1 in funcNames :
            valsNew   = ( momsNew[name0][0], momsNew[name1][0] )
            errsNew   = ( momsNew[name0][1], momsNew[name1][1] )
            errs      = ( moments[name0][1], moments[name1][1] )
            corr01    = correlations[name0][name1]
            corr0Norm = correlations[name0][normMoment]
            corr1Norm = correlations[name1][normMoment]
            corr01New = ( errs[0] * errs[1] * corr01 + valsNew[0] * valsNew[1] * errNorm**2\
                         - valsNew[1] * errs[0] * errNorm * corr0Norm - valsNew[0] * errs[1] * errNorm * corr1Norm ) / valNorm**2
            if abs( errsNew[0] ) > 1.e-10 and abs( errsNew[1] ) > 1.e-10 :
                corr01New /= errsNew[0] * errsNew[1]
            elif abs( corr01New ) < 1.e-10 and name0 == normMoment and name1 == normMoment :
                corr01New = 1.
            elif abs( corr01New ) < 1.e-10 and ( name0 == normMoment or name1 == normMoment ) :
                corr01New = 0.
            else :
                corr01New = -999.
            corrsNew[name0][name1] = corr01New
            corrsNew[name1][name0] = corr01New
    
    print 'output moments:'
    from P2VV.Utilities.DataMoments import writeMoments
    writeMoments( momentsFileNorm, BasisFuncNames = funcNames, Moments = momsNew, Correlations = corrsNew )
    if printMoms: printMoments( BasisFuncNames = funcNames, Moments = momsNew, Correlations = corrsNew )
    
def combineMoments( momentsFilesIn, momentsFileOut, prefix = '', printMoms = True):
    funcNames = [ 'Re_ang_A0_A0', 'Re_ang_Apar_Apar', 'Re_ang_Aperp_Aperp'
                 , 'Im_ang_Apar_Aperp', 'Re_ang_A0_Apar', 'Im_ang_A0_Aperp'
                 , 'Re_ang_AS_AS', 'Re_ang_Apar_AS', 'Im_ang_Aperp_AS', 'Re_ang_A0_AS' ]
    
    if prefix:
        funcNamesWPF = []
        for name in funcNames: funcNamesWPF += [prefix + '_' + name]
        funcNames =  funcNamesWPF

    # moment containers
    moments = [ ]
    correlations = [ ]
    
    # read moments
    from P2VV.Utilities.DataMoments import readMoments, printMoments
    for momsFile in momentsFilesIn :
        moments.append( { } )
        correlations.append( { } )
        readMoments( momsFile, BasisFuncNames = funcNames, Moments = moments[-1], Correlations = correlations[-1] )
        if printMoms: printMoments( BasisFuncNames = funcNames, Moments = moments[-1], Correlations = correlations[-1] )
    
    # combine moments
    from ROOT import TMatrixD
    combNames = [ name for name in funcNames if moments[0][name][1] > 0. ]
    momVec    = TMatrixD( len(combNames), 1              )
    covMat    = TMatrixD( len(combNames), len(combNames) )
    for moms, corrs in zip( moments, correlations ) :
        mom = TMatrixD( len(combNames), 1              )
        cov = TMatrixD( len(combNames), len(combNames) )
        for it1, name1 in enumerate(combNames) :
            mom[it1][0] = moms[name1][0]
            for it2, name2 in enumerate(combNames) :
                cov[it1][it2] = moms[name1][1] * moms[name2][1] * corrs[name1][name2]
        cov.Invert()
        momVec += cov * mom
        covMat += cov
    covMat.Invert()
    momVec = covMat * momVec
    
    momsNew  = { }
    corrsNew = { }
    for name in funcNames :
        if moments[0][name][1] > 0. : continue
        momsNew[name]  = moments[0][name]
        corrsNew[name] = correlations[0][name]
    
    from math import sqrt
    for it1, name1 in enumerate(combNames) :
        val = momVec[it1][0]
        err = sqrt( covMat[it1][it1] )
        momsNew[name1]  = ( val, err, abs( val / err ) )
        corrsNew[name1] = { }
        for name in funcNames :
            if moments[0][name][1] > 0. : continue
            corrsNew[name1][name] = correlations[0][name1][name]
        for it2, name2 in enumerate(combNames) :
            corrsNew[name1][name2] = covMat[it1][it2] / err / sqrt( covMat[it2][it2] )
    
    # write combined moments to file
    from P2VV.Utilities.DataMoments import writeMoments
    writeMoments( momentsFileOut, BasisFuncNames = funcNames, Moments = momsNew, Correlations = corrsNew )
    if printMoms: printMoments( BasisFuncNames = funcNames, Moments = momsNew, Correlations = corrsNew )
    

class RealMomentsBuilder ( dict ) :
    # TODO:  implement reduce: clone self, selecting a subset of available moments...
    # TODO:                    support as kw: MinSignificance, Names
    # def reduce( self, **kwargs ) :
    #
    #

    def __init__( self, **kwargs )   :
        self._basisFuncNames   = [ ]
        self._basisFuncIndices = { }
        self._basisFuncs       = { }
        self._coefficients     = { }
        self._correlations     = { }
        self._constrainAcceptance = False
        if 'Moments' in kwargs :
            for mom in kwargs.pop('Moments') : self.append( Moment = mom )
        if 'Moment' in kwargs :
            self.append( Moment = kwargs.pop(Moment) )
        self._covMatrixSize = 0
        if kwargs :
            raise RuntimeError( 'unknown keyword arguments %s' % kwargs.keys() )

    def basisFuncs(self)       : return self._basisFuncs.copy()
    def basisFuncNames(self)   : return self._basisFuncNames[ : ]
    def basisFuncIndices(self) : return self._basisFuncIndices.copy()
    def coefficients(self)     : return self._coefficients.copy()
    def correlations(self)     : return dict( [ ( key, val.copy() ) for key, val in self._correlations.iteritems() ] )

    def _iterFuncAndCoef( self, **kwargs ) :
        # get minimum significance for coefficient
        minSignif = kwargs.pop( 'MinSignificance', float('-inf') )

        # get name requirement for coefficient
        names = kwargs.pop('Names',None)
        import re
        nameExpr = re.compile(names) if names else None

        # check if there are no arguments left
        assert not kwargs, 'extraneous kw args: %s' % kwargs

        # yield name, coefficient and function for selected moments
        for funcName in self._basisFuncNames :
            if self._coefficients[funcName][2] < minSignif : continue
            if nameExpr and not nameExpr.match(funcName)   : continue
            yield ( funcName, self._coefficients[funcName], self._basisFuncs[funcName] )

    def appendPYList( self, Angles, IndicesList, PDF = None, IntSet = None, NormSet = None ) :
        # save angles to use them in the constrain.
        self._angles = Angles 
                
        # build moments from list of indices
        if not PDF and not IntSet and not NormSet :
            # build moment
            for inds in IndicesList :
                self.append(  Angles = Angles, PIndex = inds[0], YIndex0 = inds[1], YIndex1 = inds[2]
                                  , Norm = float( 2 * inds[0] + 1 ) / 2. )
        elif PDF and IntSet != None and NormSet != None :
            # TODO: default for IntSet should be an empty set and a set of angles for NormSet,
            #       but we need a dataset to determine this ;-(
            #       maybe set to 'None' , and then defer to compute???
            #       Problem is, at that point the moments have already been build...
            # build efficiency moment
            for inds in IndicesList :
                self.append(  Angles = Angles, PIndex = inds[0], YIndex0 = inds[1], YIndex1 = inds[2]
                                  , Norm = float( 2 * inds[0] + 1 ) / 2., PDF = PDF, IntSet = IntSet, NormSet = NormSet )
        else :
            print 'P2VV - ERROR: RealMomentsBuilder.appendList: a PDF, an integration set and a normalisation set are required for efficiency moments'

    def append( self, **kwargs ) :
        momIndices = None
        if 'Moment' in kwargs :
            # get moment directly from arguments
            func = None
            moment = kwargs.pop('Moment')

        elif 'Function' in kwargs or all( arg in kwargs for arg in ( 'Angles', 'PIndex', 'YIndex0', 'YIndex1' ) ):
            # build moment with function from arguments
            if 'Function' in kwargs :
                # get function from arguments
                func = kwargs.pop('Function')
            else :
                # build basis function
                from P2VV.RooFitWrappers import P2VVAngleBasis
                momIndices = ( kwargs.pop('PIndex'), kwargs.pop('YIndex0'), kwargs.pop('YIndex1') )
                func = P2VVAngleBasis( Name = 'p2vvab', Angles = kwargs.pop('Angles')
                                      , Indices = ( momIndices[0], 0, momIndices[1], momIndices[2] ), FixedCoef = 1. )

            if not 'PDF' in kwargs and not 'IntSet' in kwargs and not 'NormSet' in kwargs :
                # build moment
                from P2VV.RooFitWrappers import RealMoment
                moment = RealMoment( Name = func.GetName(), BasisFunc = func, Norm = kwargs.pop( 'Norm', 1. ) )
            elif 'PDF' in kwargs and 'IntSet' in kwargs and 'NormSet' in kwargs :
                # build efficiency moment
                from P2VV.RooFitWrappers import RealEffMoment
                pdf = kwargs.pop('PDF')
                moment = RealEffMoment( Name = func.GetName(), BasisFunc = func, Norm = kwargs.pop( 'Norm', 1. ), PDF = pdf
                                       , IntSet = kwargs.pop('IntSet'), NormSet = kwargs.pop('NormSet') )
            else :
                print 'P2VV - ERROR: RealMomentsBuilder.append: a PDF, an integration set and a normalisation set are required for an efficiency moment'
                moment = None

        else :
            print 'P2VV - ERROR: RealMomentsBuilder.append: did not find required arguments'
            moment = None

        # check for unexpected arguments
        if kwargs :
            print 'P2VV - ERROR: RealMomentsBuilder.append: unknown arguments:', kwargs
            moment = None

        if moment :
            # append moment
            momName = moment.GetName()
            self._basisFuncNames.append(momName)
            if momIndices : self._basisFuncIndices[momName] = momIndices
            else :          self._basisFuncIndices[momName] = None
            if func : assert func == moment.basisFunc()
            self._basisFuncs[momName] = moment.basisFunc()
            self[momName] = moment

    def initCovariances(self) :
        self._covMatrixSize = len(self._basisFuncNames)
        for it, name1 in enumerate(self._basisFuncNames) :
            self[name1].clearMoments()
            moments = [ self[name2] for name2 in self._basisFuncNames[ it + 1 : ] ]
            self[name1].appendMoments(moments)

    def compute( self, data, **kwargs ) :
        """computes moments of data set (wrapper for C++ computeRooRealMoments)

        Looping over data in python is quite a bit slower than in C++. Hence, we
        adapt the arguments and then defer to the C++ computeRooRealMoments.
        """
        from P2VV.Load import P2VVLibrary
        from ROOT import std, computeRooRealMoments
        momVec = std.vector('RooRealMoment*')()
        for func in self._basisFuncNames : momVec.push_back( self[func]._var )
        computeRooRealMoments( data, momVec, kwargs.pop( 'ResetFirst', False ), kwargs.pop( 'Verbose', True ) )

        for it1, func1 in enumerate(self._basisFuncNames) :
            self._coefficients[func1] = ( self[func1].coefficient(), self[func1].stdDev(), self[func1].significance() )
            if self._covMatrixSize == len(self._basisFuncNames) :
                corrs = { }
                for it2, func2 in enumerate(self._basisFuncNames) :
                    corrs[func2] = self[func2].correlation( it1 - it2 ) if it2 < it1 else self[func1].correlation( it2 - it1)
                self._correlations[func1] = corrs

    def convertEffWeightsToMoments( self, **kwargs ) :
        convertEffWeightsToMoments( Weights = self._coefficients, **kwargs )

    def Print( self, **kwargs ) :
        printMoments( BasisFuncNames = self._basisFuncNames, Moments = self._coefficients, Correlations = self._correlations, **kwargs )

    def write( self, filePath = 'moments', **kwargs ) :
        writeMoments( filePath, BasisFuncNames = self._basisFuncNames, Moments = self._coefficients, Correlations = self._correlations,
                     **kwargs )

    def read( self, filePath = 'moments', **kwargs ) :
        readMoments( filePath, BasisFuncNames = self._basisFuncNames, Moments = self._coefficients, Correlations = self._correlations,
                    **kwargs )
        self._covMatrixSize = len(self._correlations)

    def buildPDFTerms( self, **kwargs ) :
        # TODO: decide whether coefficients are ConstVar or RealVar?? (add keyword for that! -- what MinMax to give if RealVar?? x times their error??)
        # TODO: verify we've got moments, and not EffMoments???
        # TODO: verify we've either been computed or read

        # get minimum significance
        minSignif = kwargs.pop( 'MinSignificance', float('-inf') )

        # get name requirements
        import re
        names = kwargs.pop( 'Names', None )

        # get scale factors
        scale  = kwargs.pop( 'Scale',  None )
        scales = kwargs.pop( 'Scales', ( scale, scale ) if scale != None else ( None, None ) )

        # get number of standard deviations for range of the PDF coefficients
        numStdDevs = kwargs.pop( 'RangeNumStdDevs', 5. )

        # get prefix for PDF coefficient names
        namePref = kwargs.pop( 'CoefNamePrefix', 'C_' )

        # loop over PDF terms
        keys     = []
        angFuncs = {}
        angCoefs = {}
        from P2VV.RooFitWrappers import ConstVar, RealVar
        for ( name, coef, func ) in self._iterFuncAndCoef( MinSignificance = minSignif, Names = names ) :
            # construct the key and the function for the term
            if self._constrainAcceptance and name =='p2vvab_0000': continue

            keys.append( ( name, None ) )
            angFuncs[( name, None )] = ( func, None )

            # get the coefficient value and standard deviation
            coefVal = coef[0] * scales[0] if scales[0] else coef[0]
            coefErr = coef[1] * scales[1] if scales[1] else coef[1]

            # create the coefficient parameter for the PDF term
            if self._basisFuncIndices[name] == ( 0, 0, 0 ) :
                angCoefs[( name, None )] = ( ConstVar( Name = namePref + name, Value = coefVal ), None )
            else :
                coefMin = coefVal - numStdDevs * coefErr
                coefMax = coefVal + numStdDevs * coefErr
                angCoefs[( name, None )] = ( RealVar(  namePref + name, Value = coefVal, MinMax = ( coefMin, coefMax ) ), None )

        # Include constrain terms
        if self._constrainAcceptance:
            from P2VV.RooFitWrappers import FormulaVar
            for cTerm in self._constrainTerms:
                
                ckey = ( cTerm[0] + '_constr', None )
                cCoef = angCoefs[ (cTerm[0], None) ][0] 
                keys.append( ckey )
                angFuncs[ckey] = ( cTerm[1], None )
                angCoefs[ckey] = ( FormulaVar(Name = '%s_constr'%(cCoef.GetName()), Formula ='-@0', Arguments = [cCoef] ), None )

        from P2VV.Parameterizations.AngularPDFs import Coefficients_AngularPdfTerms
        return Coefficients_AngularPdfTerms( Keys = keys, AngFunctions = angFuncs, AngCoefficients = angCoefs )

    def createPDF( self, **kwargs ) :
        # TODO: decide whether coefficients are ConstVar or RealVar?? (add keyword for that! -- what MinMax to give if RealVar??)
        #        maybe take MinMax = ( -5 * c[1], 5*c[1] ) ??? and make the 5 settable??
        # TODO: verify we've got moments, and not EffMoments???
        # TODO: verify we've either been computed or read
        scale = kwargs.pop('Scale', 1. )
        name = kwargs.pop('Name')
        ( names, coefs, funs ) = zip( *self._iterFuncAndCoef( MinSignificance = kwargs.pop( 'MinSignificance', float('-inf') )
                                                         , Names           = kwargs.pop( 'Names', None)
                                                         ) )
        from P2VV.RooFitWrappers import ConstVar,RealSumPdf
        # TODO: renornmalize wrt. 0,0,0? require 0,0,0 to be present??
        return RealSumPdf( name
                         , functions = funs
                         , coefficients = ( ConstVar( Name = ('C_%3.6f'%c[0]).replace('-','m').replace('.','d')
                                                    , Value = c[0]*scale ) for c in coefs )
                         )


    def __mul__( self, pdf ) : return self.multiplyPDFWithEff(pdf)


    def multiplyPDFWithEff( self, pdf, **kwargs ) :
        # TODO: check that 'we' contain efficiency moments?
        # TODO: and that we've actually either 'read' or 'compute'-ed them??
        # TODO: do not use type to recognize, but name??
        coefs    = [ ]
        effFuncs = [ ]
        coefName        = kwargs.pop( 'CoefName',          'effC'    )
        constCoefs      = kwargs.pop( 'ConstCoefs',         True     )
        constrainAcc    = kwargs.pop( 'ConstainAcc',        False    )
        constrTermsPref = kwargs.pop( 'ConstrainTermsPref',  ''      )
        constrainType   = kwargs.pop( 'ConstainType',     'Integral' )
        verbose         = kwargs.pop( 'Verbose',           True      )
                
        from P2VV.RooFitWrappers import ConstVar, RealVar
        for funcName, coef, effFunc in self._iterFuncAndCoef( Names = 'p2vvab.*' ) :
            # this part is to constrain the angular acceptance
            if constrainAcc and funcName == 'p2vvab_0000': continue
            name = ( '%s_%d%d%d' % ( ( coefName, ) + tuple( self._basisFuncIndices[funcName] ) ) ).replace( '-', 'm' )
            coefs.append( ConstVar( Name = name, Value = coef[0] ) if constCoefs\
                          else RealVar( Name = name, Value = coef[0], Error = coef[1] if coef[1] else 0, Constant = True ) )
            effFuncs.append(effFunc)

        if constrainAcc:
            print 'P2VV - INFO: RealMomentsBuilder.multiplyPDFWithEff(): constraining acceptance with c_000 efficiency moment.'
            self._constrainAcceptance = True
            self._constrainTerms = constrainAngularAcceptance( self.basisFuncIndices(), self.coefficients(), self._angles, coefs, effFuncs, 
                                                               constVarCoefs = constCoefs,
                                                               constrainType = constrainType,
                                                               verbose = verbose,
                                                               constrainTermsPref = constrTermsPref
                                                           )
            
        bases = [ ]
        from ROOT import RooP2VVAngleBasis
        for comp in filter( lambda x : type(x) is RooP2VVAngleBasis, pdf.getComponents() ) :
            multiplyP2VVAngleBases( comp, Functions = effFuncs, Coefficients = coefs, DoReset = True )
            bases.append( comp.GetName() )
        print 'P2VV - INFO: RealMomentsBuilder.multiplyPDFWithEff(): multiplied the following %s with angular acceptance:'\
              % ( ( '%d components' % len(bases) ) if len(bases) > 1 else 'component' )
        print '             [ ' + ', '.join( name for name in bases ) + ' ]'

        return pdf


# Utility tool to constrian the acceptance at cosThK = 1 (This is for the jpsiKst analysys)
def constrainAngularAcceptance( momentsIndices, momentsCoefficiencts, angles, coefficiencts, efficiencyFuncs, **kwargs ):
    constVarCoefs      = kwargs.pop( 'constVarCoefs',      True      )
    constrainType      = kwargs.pop( 'constrainType',     'Integral' )
    constrainTermsPref = kwargs.pop( 'constrainTermsPref',   ''      )
    verbose            = kwargs.pop( 'verbose',             False    )

    cThK = angles['cpsi']._var
    cThL = angles['ctheta']._var
    phi  = angles['phi']._var

    # helping functions
    from P2VV.RooFitWrappers import ConstVar, RealVar, P2VVAngleBasis, Product, FormulaVar
    from ROOT import RooArgSet, RooSpHarmonic

    isSimul     =  all( map(lambda name: len(name.GetName().split('_')[:-1])!=1, coefficiencts) )
    simul_suf   = '_'.join(coefficiencts[0].GetName().split('_')[1:-1]).replace('p2','2')
    _i          = lambda name: momentsIndices[name]
    constr_term = lambda i,j,k: P2VVAngleBasis( Name = 'constr_ang_%s%s%s'%(i,j,k), 
                                                Angles = {'cpsi':cThK, 'ctheta':cThL, 'phi':phi },
                                                Indices = ( i, 0, j, k ))
    constr_termProd = lambda suf, term, coef: Product('constr_prod_%s_%s_%s'%( constrainTermsPref, simul_suf if isSimul else '', suf), [term,coef] )
    
    def constr_coef(mom):
        # CAREFULL!! Unless you constrain only in cThk-cThL, this is a dangerous, since mom[2] can be negative and thus missing the sign         
        coef = ''        
        for c in coefficiencts:
            ijk = '%s%s%s'%(mom[0],mom[1],mom[2])
            if c.GetName().split('_')[-1] == ijk: 
                coef = c
                assert coef, 'P2VV - ERROR: DataMoments.constrainAngularAcceptance: Cannot grab obect: %s'% c.GetName()
            if not isSimul:
                constr_name = 'constr_c_%s'%ijk
            else:
                constr_name = 'constr_c_%s_%s'%( simul_suf, ijk )
        return FormulaVar(Name = '%s_%s'%(constr_name, constrainTermsPref ), Formula ='-@0', Arguments = [coef] )
  
    # loop over given moments and build the constrian terms
    from math import sqrt, pi
    
    print 'P2VV - INFO: DataMoments.constrainAngularAcceptance: Replaced c_000 * P0Y00 with the following terms:'
    # constrainTerms = {}
    constrainTerms = []
    for name, mom in momentsIndices.iteritems():
       
        # This is the term that you are replacing
        if name == 'p2vvab_0000': continue 

        # Math: Integrals of Y_jk dphi for j!=k over [-pi,pi] are equal to zero
        if constrainType == 'Integral' and _i(name)[2] != 0: continue 

        coef = constr_coef(mom)
        term = constr_term(0,mom[1],mom[2])

        coefficiencts.append( coef )
        efficiencyFuncs.append( term )
        
        constrainTerms.append( (name, term)  )
        if verbose: print ' ', 'C_' + name, '*',term.GetName() 

    return constrainTerms

def writeConstrainedMoms( fileName, basisMoms, accFitResult, PrintMoments = False ):
    names = basisMoms.keys()
    scales = [1,1,1] 
    maxLenName = 0
    funcNames  = basisMoms.basisFuncNames()
    fitMomsSet = accFitResult.floatParsFinal()
    fitedMomVar = lambda name: accFitResult.floatParsFinal().find('effC_' + ''.join( name.split('_')[1][i] for i in [0,2,3] ))
    moments = { name : ( fitedMomVar(name).getVal(), fitedMomVar(name).getError(), 1 ) for name in basisMoms.coefficients().keys() if not name=='p2vvab_0000'  }
    moments.update( {'p2vvab_0000':(1,1,1) })
    # open file
    try :
        momFile = open( fileName, 'w' )
    except :
        raise IOError( 'P2VV - ERROR: DataMoments.writeConstrainedMoms(): unable to open file \"%s\"' % fileName )
    # write moments to content string
    cont = '# %s: angular moments\n' % fileName\
         + '# name requirement: \'{0}\'\n'.format( '' )\
         + '# minimum significance = {0:s}\n'.format('-inf')\
         + '# scales = ({0:.5g}, {1:.5g}, {2:.5g})\n'.format( scales[0], scales[1], scales[2] )\
         + '#\n'\
         + '# ' + '-' * ( 49 + maxLenName ) + '\n'\
         + ( '# {0:<%s}   {1:<14}   {2:<13}   {3:<13}\n' % maxLenName )\
               .format( 'basis function', 'coefficient', 'std. dev.', 'significance' )\
         + '# ' + '-' * ( 49 + maxLenName ) + '\n'
    numMoments = 0
    for func in funcNames :
        cont += ( '  {0:<%s}' % maxLenName ).format(func)
        if func in moments :
            coef = moments[func]
            cont += '   {0:<+14.8g}   {1:<13.8g}   {2:<13.8g}\n'\
                    .format( coef[0] * scales[0], coef[1] * scales[1], coef[2] * scales[2] )
            numMoments += 1
        else :
            cont += '\n'
    cont += '# ' + '-' * (49 + maxLenName) + '\n'
    
    # print out
    if PrintMoments: print cont

    # write content to file
    momFile.write(cont)
    momFile.close()
    print 'P2VV - INFO: DataMoments.writeConstrainedMoms(): wrote constrianed moments to file %s'%momFile.name




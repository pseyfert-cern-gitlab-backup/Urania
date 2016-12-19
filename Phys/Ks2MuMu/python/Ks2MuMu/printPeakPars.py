import KsMuMuPeakPars

for cat in ['TOS1_', 'TOS2_', 'TIS_' ]:
    print 'CATEGORY:', cat
    for i in xrange( 10 ):
        ib = str( i )
        cl = getattr( KsMuMuPeakPars, 'KsMuMuIpaPars_' + cat + ib )
        pars = [ cl.ipa_m, cl.ipa_s, cl.a, cl.n, cl.l ]
        for i, el in enumerate( pars ):
            pars[ i ] = '%.2f' % el
        out = ' & '
        out = out.join( pars )
        print out + ' \\\\'

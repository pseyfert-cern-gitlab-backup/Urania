from ROOT import *
gROOT.SetBatch(True)
from valAndErr import *
from readData import *
import cutStrings as cs
from SBsubtraction import *
import os

def getRawYields(i):

    datasets = []

    ################################################################
    if i is 1:
        filename = 'RawYieldsFor2011_D.txt'
        datasets.append('2011_Strip20r1_D')
    ################################################################
    if i is 2:
        filename = 'RawYieldsFor2011_ABCD.txt'
        datasets.append('2011_Strip20r1_A')
        datasets.append('2011_Strip20r1_B')
        datasets.append('2011_Strip20r1_C')
        datasets.append('2011_Strip20r1_D')
    ################################################################
    if i is 3:
        filename = 'RawYieldsFor2011_abcdefghijk.txt'
        datasets.append('2011_Strip20r1_a')
        datasets.append('2011_Strip20r1_b')
        datasets.append('2011_Strip20r1_c')
        datasets.append('2011_Strip20r1_d')
        datasets.append('2011_Strip20r1_e')
        datasets.append('2011_Strip20r1_f')
        datasets.append('2011_Strip20r1_g')
        datasets.append('2011_Strip20r1_h')
        datasets.append('2011_Strip20r1_i')
        datasets.append('2011_Strip20r1_j')
        datasets.append('2011_Strip20r1_k')
        datasets.append('2011_Strip20r1_l')
    ################################################################
    if i is 4:
        filename = 'RawYieldsFor2011_2012.txt'
        datasets.append('2011_Strip20r1')
        datasets.append('2012_Strip20')
        datasets.append('2011and12_SEL')
    ################################################################

    directory = 'RawYieldsPerFiles_SB'
    if not os.path.exists(directory): os.makedirs(directory)

    yields = {}
    lumi = {}
    rates = {}

    for data in datasets:
        print ' o) Read in data:', data
        dataobj = readData(data)
        tree = dataobj.get('tree')
        lumival = dataobj.get('lumi')
        cut = dataobj.get('cut')+ '&&' + cs.minimalNormBu_lnf

        #Bplus_PT
        #N_sig = getSBSubtractedYield(tree, 'Bplus_M', 100, 100, 55, cut , 'Bu', 100, True)
        N_sig = getSBSubtractedYield(tree, 'Bplus_M', 100, 100, 55, cut , 'Bu', 100, False)
        yields[data] = valAndErr(N_sig,'P')
        rates[data] = yields[data].over(lumival)
        lumi[data] = lumival

    f = open(directory+'/'+filename,'w')
    #Print results
    print >>f, '-------------------------------------------------'
    for data in datasets:
        print >>f, ' o) Data:', data
        print >>f, '     SB subtracted yield : %.1f +- %.1f'%( yields[data].getVal() , yields[data].getErr())
        print >>f, '     Luminosity/pb-1     : %.1f +- %.1f'%( lumi[data].getVal() , lumi[data].getErr())
        print >>f, '     Yields / pb-1       : %.1f +- %.1f'%( rates[data].getVal() , rates[data].getErr())
    print >>f, '-------------------------------------------------'
    f.close()


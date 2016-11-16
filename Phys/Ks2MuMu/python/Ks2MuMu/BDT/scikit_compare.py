from scikit_BDT_classes import *

bdt1 = cPickle.load(open('test1.b'))
bdt2 = cPickle.load(open('test2.b'))

#compareROCs( {'1': bdt1, '2': bdt2} )
overtrainDist(bdt1[0])

mat = makeCorrPlot( bdt1[0].train, variables = bdt1[0].bdtvars )

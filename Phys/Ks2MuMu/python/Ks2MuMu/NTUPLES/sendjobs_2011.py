# This file executes gangaScript.py for a given mode, polarity, stripping
# selection and mcMatch requirements

modes = ['MCMB08a', 'MCMB08c']
#modes = ['dataKspipi', 'dataMB']
#modes = ['dataMB']
polarities = ['Up', 'Down']

STRIPSEL = False
MCMATCH  = True

print '*** Stripping selection set to: %s ***' % str(STRIPSEL)
print '*** mcMatch requirement set to: %s ***' % str(MCMATCH)
for MODE in modes:
    for MAGNET in polarities:
        print '*** Executing mode:', MODE, 'and polarity:', MAGNET, '***'
        execfile('gangaScript_2011.py')

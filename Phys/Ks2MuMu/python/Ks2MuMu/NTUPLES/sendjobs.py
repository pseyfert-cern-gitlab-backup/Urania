# This file executes gangaScript.py for a given mode, polarity, stripping
# selection and mcMatch requirements

modes = ['dataKsmumu', 'dataKspipi', 'dataMB']
polarities = ['Up', 'Down']

STRIPSEL = True
MCMATCH  = False

print '*** Stripping selection set to: %s ***' % str(STRIPSEL)
print '*** mcMatch requirement set to: %s ***' % str(MCMATCH)
for MODE in modes:
    for MAGNET in polarities:
        print '*** Executing mode:', MODE, 'and polarity:', MAGNET, '***'
        execfile('gangaScript.py')

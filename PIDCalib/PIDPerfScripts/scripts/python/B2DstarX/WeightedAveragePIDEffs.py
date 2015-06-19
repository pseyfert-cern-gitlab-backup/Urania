import os.path
from decimal import *
from math import *
import sys

'''
A = __________1___________
    Sum_i[ 1/(sigma_i)^2 ]
'''
def A(list):
    sum = 0
    for i in list:
        sum += 1/i**2
    return 1/sum

'''
B = Sum_i[ x/y^2 ]
'''
def B(list1, list2):
    sum = 0
    for x, y in map(None, list1, list2):
        sum += x/y**2
    return sum

'''
Weighted Mean = B x A
'''
def WeightedMean(Effs, Errs):
    #getcontext().prec = 6
    #return B(Effs, Errs)*A(Errs)
    return (B(Effs, Errs)*A(Errs)).quantize(Decimal('1.000000'), rounding=ROUND_HALF_UP)

'''
Error = sqrt(A)
'''
def Error(Errs):
    #getcontext().prec = 6
    #return sqrt(A(Errs))
    return Decimal(str(sqrt(A(Errs)))).quantize(Decimal('1.000000'), rounding=ROUND_HALF_UP)


NOFILES = {'Up'   : int(sys.argv[1]),
           'Down' : int(sys.argv[2])
           }
TRKTYPES = ['k', 'pi']
MAGDIR = ['Up', 'Down']
FILES = {}
OUTFILES = {}

'''
Construct files names to process (FILES) and open files to write weighted averages to (OUTFILES)
'''
for t in TRKTYPES:
    for o in MAGDIR:
        for i in range(0,NOFILES[o]):
            FileName = o+'_'+t+'_'+str(i)+'.txt'
            #print FileName
            FILES.setdefault(t+'_'+o, []).extend([FileName])
        outFileName = o+'_'+t+'.txt'
        OUTFILES.setdefault(t+'_'+o, []).extend([open(outFileName,'w')])
print FILES

print '\n'

'''
For each DLL cut, loop over FILES and determine the weighted average. Write out results to screen and to OUTFILES.
'''
for key, l in FILES.items():
    print key
    num_lines = 17
    for i in range(0,num_lines):
        Errs = []
        Effs = []
        Dummy_Errs = []
        Dummy_Effs = []
        Els = []
        for n in l:
            with open(n) as f:
                line = f.readlines()[i]
                #print key, n, line.split()
                if not Els:
                    Els.append(line.split()[0])
                Dummy_Effs.append(line.split()[1][0:8])
                Dummy_Errs.append(line.split()[2][0:10])
        Effs = [Decimal(x) for x in Dummy_Effs]
        Errs = [Decimal(x) for x in Dummy_Errs]
        ##print Effs
        ##print Errs
        Avg_Eff = WeightedMean(Effs,Errs)
        Avg_Err = Error(Errs)
        ##print type(Avg_Eff)
        ##print type(Avg_Err)
        Els.append('\t')
        Els.append(Avg_Eff.to_eng_string())
        Els.append('\t')
        Els.append(str(Avg_Err))
        s = " ".join(Els)
        print s
        OUTFILES[key][0].writelines(s)
        OUTFILES[key][0].write('\n')
    OUTFILES[key][0].close()

'''
For each DLL cut, loop over FILES and determine the weighted average. Print results to screen in LaTeX table format.
'''
for key, l in FILES.items():
    print key
    num_lines = 17
    for i in range(0,num_lines):
        Errs = []
        Effs = []
        Dummy_Errs = []
        Dummy_Effs = []
        Els = []
        for n in l:
            with open(n) as f:
                line = f.readlines()[i]
                #print key, n, line.split()
                if not Els:
                    Els.append(line.split()[0])
                    Els.append(' & ')
                Dummy_Effs.append(line.split()[1][0:8])
                Dummy_Errs.append(line.split()[2][0:10])
        Effs = [Decimal(x) for x in Dummy_Effs]
        Errs = [Decimal(x) for x in Dummy_Errs]
        #print Effs
        #print Errs
        Avg_Eff = WeightedMean(Effs,Errs)
        Avg_Err = Error(Errs)
        #print type(Avg_Eff)
        #print type(Avg_Err)
        Els.append(Avg_Eff.to_eng_string())
        Els.append(' & ')
        Els.append(str(Avg_Err)[0:8])
        Els.append(' & ? & ? & ? & ?')
        Els.append('\\\ ')
        s = " ".join(Els)
        print s
    print '\n'

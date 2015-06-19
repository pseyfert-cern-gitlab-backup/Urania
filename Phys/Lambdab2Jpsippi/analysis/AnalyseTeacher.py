__author__ = 'P. Koppenburg'
from optparse import OptionParser
import re
import sys

#############################################################################################
class Variable:
    """Variable stats holder"""
    def __init__(self, id, name):
        self.id = id
        self.name = name
        self.corrpc =   -1
        self.corrsig =  -1
        self.relrank =  -1
        self.relcorr =  -1
        self.relsig  =  -1
        self.prec = "%.1f"
#        print "new variable ", id, name
        
    def table(self):
        p = self.prec
        print self.relrank, " & ", self.id, " & ", self.name, " & ", p % self.corrpc, "\\%", " & ", p % self.corrsig, "\\sigma", " & ", p % self.relcorr, "\\%", " & ", p % self.relsig, "\\sigma", " \\\\ \n", 

vars = []

#############################################################################################
## main

above_signif = True
significance_cut = 3
re_variable = re.compile('(Filling variable )([0-9].*)')
re_correlations = re.compile('( variable)(.*)(       %  ,  in sigma:   )([0-9].*)')
re_relevance = re.compile('(.*)(most relevant variable)(.*)')
re_global = re.compile('( global preprocessing flag:)(.*)')

f = open(sys.argv[1])
l = f.readlines()

for line in l:
    if (re_global.match(line)):
        significance_cut = int(int(line.split()[3])/100.)/2.
        print "% the significance cut is ", significance_cut
    if (re_variable.match(line)):
#        print 'variable : ', line
#        print line.split()[2], line.split("``")[1].split("''")[0].replace("_"," ")
        found = False
        for v in vars: 
            if (v.id == int(line.split()[2])): found = True
        if (not found): vars.extend([ Variable(int(line.split()[2]), line.split("``")[1].split("''")[0]) ])
    if (re_correlations.match(line)):
#        print line.split()
        for v in vars: 
            if (v.id == int(line.split()[1])):
                v.corrpc = float(line.split()[3])
                v.corrsig = float(line.split()[8])
#                v.table()
    if (re_relevance.match(line)):
#        print line.split()
        for v in vars: 
            if (v.id == int(line.split()[4])):
                v.relrank = int(line.split()[0])
                v.relcorr = float(line.split()[6])
                v.relsig  = float(line.split()[10])
                if (above_signif and v.relsig<significance_cut):
                   above_signif = False
                   print "\\hline"
                v.table()
                


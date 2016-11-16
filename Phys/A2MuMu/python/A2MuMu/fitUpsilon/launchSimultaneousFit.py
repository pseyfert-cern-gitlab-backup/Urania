from os import system as shell
import os.path
import simplejson as json


outdir = "./FIT_RESULTS/"
logdir = "./FIT_LOGS/"

def launchFitsInBins(logptBins, option, outdir, logdir):
        outfile= outdir+"fitParResults_" +'_'+ option + ".py"
        for i in range(len(logptBins)-1):
               print logptBins[i], logptBins[i+1], outfile, option
               if os.path.exists(outfile):
                   print "Outfile exists! remove it or define a new one"
               else:
                   shell("python SimultanFitYnSandA0.py {0} {1} {2} {3}".format(logptBins[i], logptBins[i+1], outfile, option) + " >& " + logdir +"fitlog_{0}_{1}_{2}.log".format(option, logptBins[i], logptBins[i+1]) +" &" )

fptbins = open('./logptBins.json','r')
logptBins = json.load(fptbins)
option = 'fitA12_YnSscaled'
launchFitsInBins(logptBins, option, outdir, logdir)

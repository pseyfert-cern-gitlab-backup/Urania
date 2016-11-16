from os import system as shell
import os.path


outdir = "./FIT_RESULTS/"
logdir = "./FIT_LOGS/"

def launchFitsInBins(logptBins, samples, option, outdir, logdir):
    for sample in samples:
        outfile= outdir+"fitParResults_"+ sample +'_'+ option + ".py"
        for i in range(len(logptBins)-1):
               print logptBins[i], logptBins[i+1], outfile, sample, option
               if os.path.exists(outfile):
                   print "Outfile exists! remove it or define a new one"
               else:
                   shell("python Y1S_fitAndSPlot.py {0} {1} {2} {3} {4}".format(logptBins[i], logptBins[i+1], outfile, sample, option) + " >& " + logdir +"fitlog_{0}_{1}_{2}_{3}.log".format(sample, option, logptBins[i], logptBins[i+1]) +" &" )


## first fit in the whole pt range to extract parameters independent of pt
allPt = [3.8, 10.0]
option = "Allpt"
samplesA1 = ['A8MC2011', 'A8MC2012', 'A10MC2011', 'A10MC2012', 'A12MC2011', 'A12MC2012']
launchFitsInBins(allPt, samplesA1, option, outdir, logdir)

#samplesY1 = ["Y1MC2012", "Y1MC2011"]
#launchFitsInBins(allPt, samplesY1, option, outdir, logdir)

#samplesY2 = ["Y2MC2012", "Y2MC2011"]
#launchFitsInBins(allPt, samplesY2, option, outdir, logdir)

#samplesY3 = ["Y3MC2012", "Y3MC2011"]
#launchFitsInBins(allPt, samplesY3, option, outdir, logdir)



## then fit in bins of pt
import simplejson as json
fptbins = open('./logptBins.json','r')
logptBins = json.load(fptbins)

#Default: fix everything but ipa_s
#samples = ["Y1MC2012", "Y1MC2011", 'Y2MC2011', 'Y2MC2012', 'Y3MC2011', 'Y3MC2012']
#option = 'lfixed'
#launchFitsInBins(logptBins, samples, option, outdir, logdir)

#Test: fix everything but ipa_s and l
#samples = ["Y1MC2012", "Y1MC2011"]
#option = 'lfree'
#launchFitsInBins(logptBins, samples, option, outdir, logdir)

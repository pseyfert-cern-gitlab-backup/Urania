from ROOT import *
import sys
sys.path.append("..")
import OurSites
import simplejson as json
import math

fptbins = open('./logptBins.json','r')
logptBins = json.load(fptbins)


inputTuples = {
        'Y1MC2011': OurSites.MY_TUPLE_PATH + "Upsilon_1S_MC_2011.root",
        'Y1MC2012': OurSites.MY_TUPLE_PATH + "Upsilon_1S_MC_2012.root",
        'Y2MC2011': OurSites.MY_TUPLE_PATH + "Upsilon_2S_MC_2011.root",
        'Y2MC2012': OurSites.MY_TUPLE_PATH + "Upsilon_2S_MC_2012.root",
        'Y3MC2011': OurSites.MY_TUPLE_PATH + "Upsilon_3S_MC_2011.root",
        'Y3MC2012': OurSites.MY_TUPLE_PATH + "Upsilon_3S_MC_2012.root",
        }

tupleName = "A1/A1"

samples = ['Y1MC2011', 'Y1MC2012']
centresDict = {}

for sample in samples:
    t1 = TChain(tupleName)
    t1.Add(inputTuples[sample])
    t2 = t1.CopyTree("!(evtNum%10)")
    print t2

    centre = []
    for i in range(len(logptBins)-1):
           h1 = TH1F('tit','',400,3.8,10)
           #h1 = TH1F('tit','',4000,6300.,10000000.)
           for index in range(t2.GetEntries("")):
                  t2.GetEntry(index)
                  logBpt = math.log10(getattr(t2, "Bpt"))
                  if (logBpt>logptBins[i] and logBpt<logptBins[i+1]):
                         h1.Fill(logBpt)
           mean = h1.GetMean()
           print mean, h1.GetEntries()
           centre.append(mean)
           h1.Delete()

    centresDict[sample] = centre

print centresDict
fptbinscentre = open('./logptBinsCentres.json','w')
fptbinscentre.write(json.dumps(centresDict))
fptbinscentre.close()



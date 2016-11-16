from ROOT import *

def getRampUpVal(tuple, percentage, cut='1'):
       rampup = 0
       step = 0.01 #MeV
       totentries = tuple.GetEntries(cut)
       for i in range(10000):
              entries = tuple.GetEntries(cut +'&&'+ 'B_MMass_Err<{0}'.format(i*step))
              if float(entries)/float(totentries)>percentage:
                     rampup = i*step
                     break
       return rampup


def PlotRampUp(tuple, massbins, percentage):
       graph = TGraph()
       for nbin in range(len(massbins)-1):
           masscut = 'Bmass > {0} && Bmass < {1}'.format(massbins[nbin]*1000., massbins[nbin+1]*1000.)
           rampup = getRampUpVal(tuple, percentage, masscut)
           massval = (massbins[nbin]+massbins[nbin+1])/2.0
           graph.SetPoint(nbin, massval*1000., rampup)

       return graph


def getRampUpValToy(tuple, percentage, cut='1'):
       rampup = 0
       step = 0.01 #MeV
       totentries = tuple.GetEntries(cut)
       for i in range(10000):
              entries = tuple.GetEntries(cut +'&&'+ 'Jpsi_MMERR<{0}'.format(i*step))
              if float(entries)/float(totentries)>percentage:
                     rampup = i*step
                     break
       return rampup



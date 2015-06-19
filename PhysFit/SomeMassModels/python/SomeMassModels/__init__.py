"""
"""
import os
print "importing from ", os.path.abspath(__path__[0])
from ROOT import *
gSystem.Load("libCint")
gSystem.Load("libRooFit")


gROOT.ProcessLine(".L $SOMEMASSMODELSROOT/src/RooExpAndGauss.cxx++")
gROOT.ProcessLine(".L $SOMEMASSMODELSROOT/src/RooExpAndGaussInv.cxx++")
gROOT.ProcessLine(".L $SOMEMASSMODELSROOT/src/RooPhysBkg.cxx++")
gROOT.ProcessLine(".L $SOMEMASSMODELSROOT/src/RooRadiativeTail.cxx++")
gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
gROOT.ProcessLine(".L $URANIAROOT/src/RooAmorosoPdf.cxx++")
gROOT.ProcessLine(".L $URANIAROOT/src/RooApollonios.cxx++")
gROOT.ProcessLine(".L $SOMEMASSMODELSROOT/src/RooJohanCruijff.cxx++")
gROOT.ProcessLine(".L $URANIAROOT/src/RooIpatia2.cxx++")

"""
"""
import os
print "importing from ", os.path.abspath(__path__[0])
from ROOT import *
gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")


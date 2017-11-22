"""
Usage:
python makeSmallTree.py <input file>

This macro takes the gigantic TTree with J/psi candidates and reduces 
it using only the variables which are needed. Some additinal variables
are computed on the fly. 
The macro does not apply any cuts, in order to be able to use
the small tree as friend of the big tree if needed.
"""

######################
def addFloat(outT,thename):
    """
    Add a float to tree. Saves one line of code per call.
    """
    from array import array
    newF = array( 'f', [ 0. ] )
    outT.Branch( thename, newF, thename+"/f" )
    return newF
    
######################
def writeTree(inT,n):
    """
    Write the tree
    https://root.cern.ch/how/how-write-ttree-python
    """
    from math import log, sqrt

    outT = TTree( 'Jpsi2ee', 'Small Tree' )
    event   = addFloat(outT,"event")     # event and run are there to test Friend
    run     = addFloat(outT,"run")
    mass    = addFloat(outT,"mass") 
    pt      = addFloat(outT,"pt")        # J/psi pt 
    y       = addFloat(outT,"y")         # J/psi rapidity
    pseudoT = addFloat(outT,"pseudoT") 
#    dtfM    = addFloat(outT,"dtfM")     # The mass from decayTreeFitter
#    dtfChi2 = addFloat(outT,"dtfChi2")  # The chi2 from decayTreeFitter
    epPT    = addFloat(outT,"epPT")       # e+ PT
    emPT    = addFloat(outT,"emPT") 
    epPe    = addFloat(outT,"epPe")      # electron PID
    emPe    = addFloat(outT,"emPe")
    epBrem  = addFloat(outT,"epBrem")    # brem categories
    emBrem  = addFloat(outT,"emBrem")
    pt_asym = addFloat(outT,"pt_asym")   # asymmetry of pt
#    p_asym  = addFloat(outT,"p_asym")
    spd     = addFloat(outT,"spd")       # number of SPD hits 
    PV      = addFloat(outT,"PV")        # number of PVs
    polarity = addFloat(outT,"polarity") # Magnet
#     = addFloat(outT,"") 

    if ((not n>0) or n>inT.GetEntries()): n = inT.GetEntries()
    
#    frac = 1000 # print frequency
    pc = 0
    for i in range(n):
        lastpc = pc
        pc = int(100.*i/n+0.5)
        inT.GetEntry(i)
        run[0]     = inT.runNumber
        event[0]   = inT.eventNumber
        mass[0]    = inT.Psi_M
        pt[0]      = inT.Psi_PT
        y[0]       = 0.5*log((inT.Psi_PE+inT.Psi_PZ)/(inT.Psi_PE-inT.Psi_PZ)) # rapidity https://en.wikipedia.org/wiki/Rapidity#In_experimental_particle_physics
        pseudoT[0] = (inT.Psi_ENDVERTEX_Z-inT.Psi_OWNPV_Z)*mass[0]/inT.Psi_PZ
#        dtfM[0]   = inT.Psi_PVFit_M[0]    # !BUGGY! This is an array (running over PVs)
#        dtfChi2[0] = inT.Psi_PVFit_chi2[0] # !BUGGY! This is an array (running over PVs)
        epPT[0]    = inT.eplus_PT
        emPT[0]    = inT.eminus_PT
        epPe[0]    = inT.eplus_MC15TuneV1_ProbNNe
        emPe[0]    = inT.eminus_MC15TuneV1_ProbNNe
        epBrem[0]  = inT.eplus_BremMultiplicity
        emBrem[0]  = inT.eminus_BremMultiplicity
        pt_asym[0] = (inT.eplus_PT-inT.eminus_PT)/(inT.eplus_PT+inT.eminus_PT)
#        p_asym[0]  = (inT.eplus_P-inT.eminus_P)/(inT.eplus_P+inT.eminus_P)
        spd[0]     = inT.nSPDHits
        PV[0]      = inT.nPVs
        polarity[0]= inT.Polarity
        if (i==0 or i==n or pc>lastpc): print "Candidate",i,"of",n,"(",pc,"%) with mass",mass[0]
        outT.Fill()
    return outT

###############################################
"""
``Main''
"""
from AllMacroes import *
from ROOT import *
import sys
import os
if ( len(sys.argv) == 2 ): 
    inFile = sys.argv[1]
    n = 0
elif ( len(sys.argv) == 3 ): 
    inFile = sys.argv[1]
    n = int(sys.argv[2])
else : 
    print "Usage: python makeSmallTree.py <input file> [ <number-of-events> ]"
    sys.exit()

f=TFile.Open(inFile) 
f.ls()
t=f.Get("Hlt2DiElectronJPsiEETurbo_Tuple/DecayTree")  # The TTree
t.Show(0) # shows all variables

fout = TFile( 'output.root', 'recreate' )
fout.cd()
newT = writeTree(t,n)
newT.Write()
fout.Close()

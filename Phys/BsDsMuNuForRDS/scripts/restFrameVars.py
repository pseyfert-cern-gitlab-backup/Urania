####################################################################
## Script to compute the discriminating kinematic variables
## in the approximate B rest frame for the Bs2DsX candidates.
####################################################################
from BsDsMuNuForRDS.DataRetrieval import getChainWithTupleName
from ROOT import *
from math import tan
import sys
gROOT.SetBatch()
gROOT.ProcessLine('.x ~/lhcbStyle.C')

# Options
debug = True
test  = True

# Variables
mB_PDG = 5366.79

print '*'*70
####################################################################
## Get the files and tuples.
####################################################################
dataTag = 'MC_AllNeutrals'
polarity = 'MagDown'
#fName = '/afs/cern.ch/work/s/sogilvy/RDs/RDS_DiMuon_%s.root' %polarity
#tName = 'B2DsMuNuTuple/DecayTree'
#f = TFile(fName)
#t = f.Get(tName)
t = getChainWithTupleName('MC_AllNeutrals', polarity, 'B2DsMuNuTuple/DecayTree')

if debug:
    pass
    #f.ls()
    t.Print()

####################################################################
# Now some containers for variables we need.
####################################################################
# First make the containers.
from numpy import zeros as z
mB  = z(1, dtype=float)
pzB = z(1, dtype=float)

pxBT = z(1, dtype=float)
px2BT = z(1, dtype=float)
pyBT = z(1, dtype=float)
pzBT = z(1, dtype=float)
peBT = z(1, dtype=float)

# The vertex quantities.
PVx = z(1, dtype=float)
PVy = z(1, dtype=float)
PVz = z(1, dtype=float)

BVx = z(1, dtype=float)
BVy = z(1, dtype=float)
BVz = z(1, dtype=float)

# ... and the truth vertex info
PVxT = z(1, dtype=float)
PVyT = z(1, dtype=float)
PVzT = z(1, dtype=float)

BVxT = z(1, dtype=float)
BVyT = z(1, dtype=float)
BVzT = z(1, dtype=float)

# The muon kinematics.
muPx = z(1, dtype=float)
muPy = z(1, dtype=float)
muPz = z(1, dtype=float)
muPe = z(1, dtype=float)

muPxT = z(1, dtype=float)
muPyT = z(1, dtype=float)
muPzT = z(1, dtype=float)
muPeT = z(1, dtype=float)

# D kinematics.
DPx = z(1, dtype=float)
DPy = z(1, dtype=float)
DPz = z(1, dtype=float)
DPe = z(1, dtype=float)

DPxT = z(1, dtype=float)
DPyT = z(1, dtype=float)
DPzT = z(1, dtype=float)
DPeT = z(1, dtype=float)

# Now set the branch addresses.
t.SetBranchAddress('Bs_0_M', mB)
t.SetBranchAddress('Bs_0_PZ', pzB)

t.SetBranchAddress('Bs_0_TRUEP_X', px2BT)
t.SetBranchAddress('Bs_0_TRUEP_Y', pyBT)
t.SetBranchAddress('Bs_0_TRUEP_Z', pzBT)
t.SetBranchAddress('Bs_0_TRUEP_E', peBT)
#print 'FUCKIN HELL LAD 2:', pxBT

t.SetBranchAddress('Bs_0_OWNPV_X', PVx)
t.SetBranchAddress('Bs_0_OWNPV_Y', PVy)
t.SetBranchAddress('Bs_0_OWNPV_Z', PVz)

t.SetBranchAddress('Bs_0_TRUEORIGINVERTEX_X', PVxT)
t.SetBranchAddress('Bs_0_TRUEORIGINVERTEX_Y', PVyT)
t.SetBranchAddress('Bs_0_TRUEORIGINVERTEX_Z', PVzT)

t.SetBranchAddress('Bs_0_ENDVERTEX_X', BVx)
t.SetBranchAddress('Bs_0_ENDVERTEX_Y', BVy)
t.SetBranchAddress('Bs_0_ENDVERTEX_Z', BVz)

t.SetBranchAddress('Bs_0_TRUEENDVERTEX_X', BVxT)
t.SetBranchAddress('Bs_0_TRUEENDVERTEX_Y', BVyT)
t.SetBranchAddress('Bs_0_TRUEENDVERTEX_Z', BVzT)

t.SetBranchAddress('mu_PX', muPx)
t.SetBranchAddress('mu_PY', muPy)
t.SetBranchAddress('mu_PZ', muPz)
t.SetBranchAddress('mu_PE', muPe)

t.SetBranchAddress('mu_TRUEP_X', muPxT)
t.SetBranchAddress('mu_TRUEP_Y', muPyT)
t.SetBranchAddress('mu_TRUEP_Z', muPzT)
t.SetBranchAddress('mu_TRUEP_E', muPeT)

t.SetBranchAddress('Ds_PX', DPx)
t.SetBranchAddress('Ds_PY', DPy)
t.SetBranchAddress('Ds_PZ', DPz)
t.SetBranchAddress('Ds_PE', DPe)

t.SetBranchAddress('Ds_TRUEP_X', DPxT)
t.SetBranchAddress('Ds_TRUEP_Y', DPyT)
t.SetBranchAddress('Ds_TRUEP_Z', DPzT)
t.SetBranchAddress('Ds_TRUEP_E', DPeT)

####################################################################
# Output file for the variables and monitoring hists.
####################################################################
outFile  = TFile('BsRestVars_%s_%s.root' %(dataTag, polarity), 'recreate')
outTuple = TTree('BsRestVars', 'BsRestVars')

# Output branches.
q2   = z(1, dtype=float) 
Emu  = z(1, dtype=float)
MM2  = z(1, dtype=float)

outTuple.Branch('q2', q2, 'q2/D')
outTuple.Branch('Emu', Emu, 'Emu/D')
outTuple.Branch('MM2', MM2, 'MM2/D')

q2True   = z(1, dtype=float)
EmuTrue  = z(1, dtype=float)
MM2True  = z(1, dtype=float)

outTuple.Branch('q2True', q2True, 'q2True/D')
outTuple.Branch('EmuTrue', EmuTrue, 'EmuTrue/D')
outTuple.Branch('MM2True', MM2True, 'MM2True/D')

# Some monitoring histograms.
h  = TH1F('Elepton', 'Elepton', 30, 0, 2.5)
h2 = TH1F('qsquared', 'qsquared', 30, 0, 12)
h3 = TH1F('missingM', 'missingM', 30, 0, 10)

#print 'FUCKIN HELL LAD 3:', pxBT

####################################################################
# Now the event loop.
####################################################################
numToProcess = t.GetEntries()
if test:
    numToProcess = int(numToProcess * 0.01)
print '-- Processing %i events...' %numToProcess    

for i in xrange(numToProcess):

    # Event counter.
    if i%1000 == 0:
        sys.stdout.write('\rProcessing event %i of %i...' %(i, numToProcess))
        sys.stdout.flush()
        
    # Set the branches.
    t.GetEntry(i)
    #print muPx[0]
    # Now construct the B momenta
    # So first we need the ratio m(B)/m(Y), where Y is the visible part
    # of the decay. We can access this easily with the PDG value of the
    # B meson mass, and the computed mass of the B candidate.
    mRatio = mB_PDG / mB[0]

    # We can then access the visible Pz with the measured Pz.
    newBPz = mRatio * pzB[0]

    # To get the remaining components of the B momentum we need the
    # B end vertex, and get the unit vector from the displacement
    # of the B meson to the PV.
    # Given we don't have the B meson decay endpoint from the lack of a slow pion
    # or otherwise I'm not sure how to do this.
    # Perhaps it all works out for the tau decays where the B and mu vertex is not reliable
    # in that the discriminating variables are different?
    # For now I'll use the computed B end vertex position.

    # So first make the displacement vector.
    dispVector = TVector3()
    dispVector.SetX(PVx[0] - BVx[0])
    dispVector.SetY(PVy[0] - BVy[0])
    dispVector.SetZ(PVz[0] - BVz[0])

    # Get the alpha angle.
    zVector = TVector3(0.0, 0.0, 1.0)
    alpha = dispVector.Angle(zVector)

    # Now calculate the magnitude of the B momentum.
    newBPMag = newBPz * (1 + (tan(alpha)**2))**0.5

    # Now get the x and y components of the B momentum.
    # We have the displacement vector and the Pz,
    # so just take the fraction of the (Px/Pz) * Pz.
    xFactor = dispVector.X() / dispVector.Z()
    yFactor = dispVector.Y() / dispVector.Z()
    newBPx = xFactor * newBPz
    newBPy = yFactor * newBPz

    # Now Calculate the B energy.
    newBE = (newBPMag**2 + mB_PDG**2)**0.5

    # Now make a 4-vector for the B.
    approxB4V = TLorentzVector(newBPx, newBPy, newBPz, newBE)

    # Now we need to boost everything into the B rest frame.
    # First make the 4-vectors for the D and mu.
    Ds4VLab = TLorentzVector(DPx[0], DPy[0], DPz[0], DPe[0])
    mu4VLab = TLorentzVector(muPx[0], muPy[0], muPz[0], muPe[0])

    # Now boost them into the B rest frame.
    approxBRestBoost = -approxB4V.BoostVector()
    Ds4VBRest = Ds4VLab.Clone()
    Ds4VBRest.Boost(approxBRestBoost)
    mu4VBRest = mu4VLab.Clone()
    mu4VBRest.Boost(approxBRestBoost)


    Emu[0] = mu4VBRest.E()/1e3
    q2[0] = (approxB4V - Ds4VLab).M2()/10e6
    MM2[0] = (approxB4V - Ds4VLab - mu4VLab).M2()/10e6
    # Now do it all again for the truth.
    # But check the B and D are real, or else it'll give errors.
    if (pzBT[0] == 0 or DPzT[0] == 0):
        q2True[0]  = -10e6
        EmuTrue[0] = -10e6
        MM2True[0] = -10e6
    else:
        # Just get the B kinematics from the truth.
        TrueB4VLab = TLorentzVector(px2BT[0], pyBT[0], pzBT[0], peBT[0])
        BRestBoost = -TrueB4VLab.BoostVector()
        TrueDs4VLab = TLorentzVector(DPxT[0], DPyT[0], DPzT[0], DPeT[0])
        Truemu4VLab = TLorentzVector(muPxT[0], muPyT[0], muPzT[0], muPeT[0])

        TrueDs4VBRest = TrueDs4VLab.Clone()
        TrueDs4VBRest.Boost(BRestBoost)

        Truemu4VBRest = Truemu4VLab.Clone()
        Truemu4VBRest.Boost(BRestBoost)

        Trueelepton = Truemu4VBRest.E()/1000.0

        Trueq24V = TrueB4VLab - TrueDs4VLab
        Trueq2value = (Trueq24V.M()/1000.0)**2

        TruemissingMsq4V = TrueB4VLab - TrueDs4VLab - Truemu4VLab
        TruemissingMsq = (TruemissingMsq4V.M()/1000.0)**2

        q2True[0]  = Trueq2value
        EmuTrue[0] = Trueelepton
        MM2True[0] = TruemissingMsq
                                
    # Now fill the output tuple.
    outTuple.Fill()

    # Some debug printouts.
    #if debug:
    #    if i%100 == 0:
            #print Emu[0], q2[0], MM2[0]
            #print mRatio, newBPz
            #dispVector.Print()
            #print alpha, newBPz, newBPMag
            #print newBPx, newBPy, newBPz, newBE
            #Ds4VBRest.Print()
            #mu4VBRest.Print()
            #h.Fill(mu4VBRest.E()/1000.0)
            #print missingMsq
            #print B4VBRest.P(), Ds4VBRest.P()

print 
# If we're testing draw the monitoring histograms.
if test:
    c = TCanvas('c', 'c', 800, 600)
    c.cd()
    h.Draw('e')
    c.SaveAs('elepton_Mag%s.png' %polarity)
    
    c.Clear()
    h2.Draw('e')
    c.SaveAs('qsq_Mag%s.png' %polarity)
    
    c.Clear()
    h3.Draw('e')
    c.SaveAs('missingMsq_Mag%s.png' %polarity)

# Now save the output tuple.
outTuple.AutoSave()
outFile.Close()

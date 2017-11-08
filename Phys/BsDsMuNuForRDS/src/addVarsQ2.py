#!/usr/bin/env python

''' This code creates a reduced ntuple without doing the photon association '''

from ROOT import *
import os,sys
from math import *

#dataTag  = sys.argv[1] #'BdDstDs'
#polarity = sys.argv[2] #'MagDown'
dataTag = "MC_Signal"
polarity = 'All'

# Resonance masses in GeV/c2 from the PDG.
BsMassPDG = 5366.82
DsstMassPDG = 2112.1

# A dict containing lists of all files to be added for each type of data and polarity.
# Also contains the tuple names for each file type to be cycled over.
dataDict = {

    'Data_PhotonEff' : { 'tNames'  : [ 'B2DsMuNuTuple/DecayTree' ]
                         ,'All'     : [ 'photonControl.root' ]
                         ,'AllOut'  : 'photonControl.root' 
                       }
    
    ,'MC_Signal'   : { 'tNames'      : [ 'B2DsMuNuTuple/DecayTree' 
                                       ,'B2DsMuNuTupleFake/DecayTree'
                                       ,'B2DsMuNuSSTuple/DecayTree' 
                                       ,'B2DsMuNuSSTupleFake/DecayTree']
                      ,'All'      : [ 'MC09b_DsMuNu.root' ]
                      ,'AllOut'   :   'MC09b_DsMuNu.root'
                    }

    ,'MC_InclDs'   : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_InclDsUp_allNeutrals_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_InclDsDown_allNeutrals_iso.root' ]
                       ,'MagUpOut'   :  'TupleRDS_InclDsUp_allNeutrals_iso.root'
                       ,'MagDownOut' :  'TupleRDS_InclDsDown_allNeutrals_iso.root'
                       }

    ,'MC_LbLcDs'   : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_LbLcDs_Up_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_LbLcDs_Down_iso.root' ]
                       ,'MagUpOut'   :  'TupleRDS_LbLcDs_Up_iso.root'
                       ,'MagDownOut' :  'TupleRDS_LbLcDs_Down_iso.root'
                       }
    ,'MC_BdDstDs'  : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_BdDstDs_Up_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_BdDstDs_Down_iso.root' ]
                       ,'MagUpOut'   :  'TupleRDS_BdDstDs_Up_iso.root'
                       ,'MagDownOut' :  'TupleRDS_BdDstDs_Down_iso.root'
                       }

    ,'MC_BsDsDs'   : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_BsDsDs_Up_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_BsDsDs_Down_iso.root' ]
                       ,'MagUpOut'   :  'TupleRDS_BsDsDs_Up_iso.root'
                       ,'MagDownOut' :  'TupleRDS_BsDsDs_Down_iso.root'
                       }

    ,'MC_BuD0Ds'   : { 'tNames'      : [ 'MB2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuTuple/DecayTree'
                                         ,'B2DsMuNuSSTuple/DecayTree' ]
                       ,'MagUp'      : [ 'TupleRDS_BuD0Ds_Up_iso.root' ]
                       ,'MagDown'    : [ 'TupleRDS_BuD0Ds_Down_iso.root' ]
                       ,'MagUpOut'   :  'TupleRDS_BuD0Ds_Up_iso.root'
                       ,'MagDownOut' :  'TupleRDS_BuD0Ds_Down_iso.root'
                       }
    ,'Data'        : { 'tNames'      : ['B2DsMuNuTuple/DecayTree'
                                        ,'B2DsMuNuTupleFake/DecayTree'
                                        ,'B2DsMuNuSSTuple/DecayTree'
                                        ,'B2DsMuNuSSTupleFake/DecayTree']
                       ,'MagUp'      : ['TupleRDS_DataUp_1_allNeutrals_iso.root'
                                        ,'TupleRDS_DataUp_2_allNeutrals_iso.root']
                       ,'MagDown'    : ['TupleRDS_DataDown_1_allNeutrals_iso.root'
                                        ,'TupleRDS_DataDown_2_allNeutrals_iso.root']
                       ,'MagUpOut'   : 'TupleRDS_DataUp_allNeutrals_iso.root'
                       ,'MagDownOut' : 'TupleRDS_DataDown_allNeutrals_iso.root'
                       }
    }

def addVars():

  # Make the new file.
  baseName = '/afs/cern.ch/user/r/rvazquez/work/'
  #baseName = '/eos/lhcb/wg/semileptonic/Bs2DsX/ProcessedTrees/'
  endName = dataDict[dataTag]['%s%s' %(polarity, 'Out')]
  outFileName = '%s%s' %(baseName, endName)
  print '-- INFO: making new file:'
  print '----', outFileName
  
  fOut = TFile(outFileName, "recreate")

  # Loop over the tuples.
  for tName in dataDict[dataTag]['tNames']:

    # Get the chain with the package functions.
    print '-- DataRetrieval.getChainWithTupleName making chain with name:'
    print '----', tName
    c = TChain(tName)
    # Now get the list of files and add them.
    # First get the list of file names within the home directory.
    inList = dataDict[dataTag][polarity]
    # Now get the data directory
    #dataDir = '/afs/cern.ch/user/r/rvazquez/work/gangadir/workspace/rvazquez/LocalXML/1448/'
    dataDir = '/eos/lhcb/wg/semileptonic/Bs2DsX/ProcessedTrees/'

    # Now populate a list of full names to be passed to the ROOT classes.
    outList = []
    for endName in inList:
      #toAdd = '%s%s%s' %('root://eoslhcb.cern.ch//', baseName, endName)
      toAdd = '%s%s%s' %('', dataDir, endName)
      print '---- ' + toAdd
      outList.append(toAdd)    
    
    for fName in outList:
      c.Add(fName)
    print '-- Retrieved TChain with %i entries.\n' %c.GetEntries() 
    
    # Make the TDirectory.
    dirName  = tName.split('/')[0]
    tNameEnd = tName.split('/')[1]

    theDir = fOut.mkdir(dirName)
    theDir.cd()

    # Make the new tuple.
    tOut = TTree('DecayTree', 'DecayTree') 

    #####################################################################################
    # Now make branches for all the q2 kinematics.
    #####################################################################################
    from numpy import zeros as z
    Bs_0_PX = z(1)
    Bs_0_PY = z(1)
    Bs_0_PZ = z(1)
    Bs_0_PE = z(1)
    Ds_0_40_nc_maxPt_PX = z(1)
    Ds_0_40_nc_maxPt_PY = z(1)
    Ds_0_40_nc_maxPt_PZ = z(1)
    Ds_0_40_nc_maxPt_PE = z(1)
    Ds_0_40_nc_mult = z(1)
    Ds_PX = z(1)
    Ds_PY = z(1)
    Ds_PZ = z(1)
    Ds_PE = z(1)
    Kpl_PIDK = z(1)
    Kmi_PIDK = z(1)
    pi_PIDK = z(1)
    Bs_0_ENDVERTEX_X = z(1)
    Bs_0_OWNPV_X = z(1)
    Bs_0_ENDVERTEX_Y = z(1)
    Bs_0_OWNPV_Y = z(1)
    Bs_0_ENDVERTEX_Z = z(1)
    Bs_0_OWNPV_Z = z(1)
    mu_PX = z(1)
    mu_PY = z(1)
    mu_PZ = z(1)
    mu_PE = z(1)


    Bs_0_MCORR = z(1)
    Ds_MM = z(1)
    nLongTracks = z(1, dtype=int)

    c.SetBranchAddress('Bs_0_PX',Bs_0_PX)
    c.SetBranchAddress('Bs_0_PY',Bs_0_PY)
    c.SetBranchAddress('Bs_0_PZ',Bs_0_PZ)
    c.SetBranchAddress('Bs_0_PE',Bs_0_PE)
    c.SetBranchAddress('Ds_0.40_nc_maxPt_PX',Ds_0_40_nc_maxPt_PX)
    c.SetBranchAddress('Ds_0.40_nc_maxPt_PY',Ds_0_40_nc_maxPt_PY)
    c.SetBranchAddress('Ds_0.40_nc_maxPt_PZ',Ds_0_40_nc_maxPt_PZ)
    c.SetBranchAddress('Ds_0.40_nc_maxPt_PE',Ds_0_40_nc_maxPt_PE)
    c.SetBranchAddress('Ds_0.40_nc_mult',Ds_0_40_nc_mult)
    c.SetBranchAddress('Ds_PX',Ds_PX)
    c.SetBranchAddress('Ds_PY',Ds_PY)
    c.SetBranchAddress('Ds_PZ',Ds_PZ)
    c.SetBranchAddress('Ds_PE',Ds_PE)
    c.SetBranchAddress('Kpl_PIDK',Kpl_PIDK)
    c.SetBranchAddress('Kmi_PIDK',Kmi_PIDK)
    c.SetBranchAddress('pi_PIDK',pi_PIDK)
    c.SetBranchAddress('Bs_0_ENDVERTEX_X',Bs_0_ENDVERTEX_X)
    c.SetBranchAddress('Bs_0_ENDVERTEX_Y',Bs_0_ENDVERTEX_Y)
    c.SetBranchAddress('Bs_0_ENDVERTEX_Z',Bs_0_ENDVERTEX_Z)
    c.SetBranchAddress('Bs_0_OWNPV_X',Bs_0_OWNPV_X)
    c.SetBranchAddress('Bs_0_OWNPV_Y',Bs_0_OWNPV_Y)
    c.SetBranchAddress('Bs_0_OWNPV_Z',Bs_0_OWNPV_Z)
    c.SetBranchAddress('mu_PX',mu_PX)
    c.SetBranchAddress('mu_PY',mu_PY)
    c.SetBranchAddress('mu_PZ',mu_PZ)
    c.SetBranchAddress('mu_PE',mu_PE)

    c.SetBranchAddress('Bs_0_MCORR',Bs_0_MCORR)
    c.SetBranchAddress('Ds_MM',Ds_MM)
    c.SetBranchAddress('nLongTracks',nLongTracks)

    ### new variables
    sq = z(1, dtype=int)
    McorrDsst = z(1)
    McorrDs = z(1)
    bSinFlightAng = z(1)
    bFlightLen = z(1)

    pBsY = z(1) 
    q2Y = z(1)
    mm2Y = z(1)
    thlY = z(1)
    elcmY = z(1)
    wY = z(1)
    
    pBsP1 = z(1)
    q2P1 = z(1)
    mm2P1 = z(1)
    thlP1 = z(1)
    elcmP1 = z(1)
    wP1 = z(1)

    pBsP2 = z(1)
    q2P2 = z(1)
    mm2P2 = z(1)
    thlP2 = z(1)
    elcmP2 = z(1)
    wP2 = z(1)

    Ds_0_40_nc_maxPt_PX = z(1)
    Ds_0_40_nc_maxPt_PY = z(1)
    Ds_0_40_nc_maxPt_PZ = z(1)
    Ds_0_40_nc_mult = z(1)

    nLT = z(1, dtype=int)

    ## new vars
    tOut.Branch('sq',sq,'sq/I')
    tOut.Branch('McorrDsst',McorrDsst,'McorrDsst/D')
    tOut.Branch('McorrDs',McorrDs,'McorrDs/D')
    tOut.Branch('bSinFlightAng',bSinFlightAng,'bSinFlightAng/D')
    tOut.Branch('bFlightLen',bFlightLen,'bFlightLen/D')

    tOut.Branch('pBsY',pBsY,'pBsY/D')
    tOut.Branch('q2Y',q2Y,'q2Y/D')
    tOut.Branch('mm2Y',mm2Y,'mm2Y/D')
    tOut.Branch('thlY',thlY,'thlY/D')
    tOut.Branch('elcmY',elcmY,'elcmY/D')
    tOut.Branch('wY',wY,'wY/D')

    tOut.Branch('pBsP1',pBsP1,'pBsP1/D')
    tOut.Branch('q2P1',q2P1,'q2P1/D')
    tOut.Branch('mm2P1',mm2P1,'mm2P1')
    tOut.Branch('thlP1',thlP1,'thlP1/D')
    tOut.Branch('elcmP1',elcmP1,'elcmP1/D')
    tOut.Branch('wP1',wP1,'wP1/D')

    tOut.Branch('pBsP2',pBsP2,'pBsP2/D')
    tOut.Branch('q2P2',q2P2,'q2P2/D')
    tOut.Branch('mm2P2',mm2P2,'mm2P2/D')
    tOut.Branch('thlP2',thlP2,'thlP2/D')
    tOut.Branch('elcmP2',elcmP2,'elcmP2/D')
    tOut.Branch('wP2',wP2,'wP2/D')

    tOut.Branch('nLT',nLT,'nLT/I')
    tOut.Branch('Ds_0.40_nc_maxPt_PX',Ds_0_40_nc_maxPt_PX,'Ds_0.40_nc_maxPt_PX/D')
    tOut.Branch('Ds_0.40_nc_maxPt_PY',Ds_0_40_nc_maxPt_PY,'Ds_0.40_nc_maxPt_PY/D')
    tOut.Branch('Ds_0.40_nc_maxPt_PZ',Ds_0_40_nc_maxPt_PZ,'Ds_0.40_nc_maxPt_PZ/D')
    tOut.Branch('Ds_0.40_nc_mult',Ds_0_40_nc_mult,'Ds_0.40_nc_mult/D')

    #####################################################################################
    # Now loop over the events and plot the Dalitz variables.
    #####################################################################################
    numToProcess = c.GetEntries()
    numPassedCounter = 0
    print '-- INFO: number of events to process:', numToProcess

    #preselectionCut = '1'
    preselectionCut = 'Ds_MM>1940 && Ds_MM<2000 && Kpl_PIDK>5 && Kmi_PIDK>5 && pi_PIDK<3'
    c.Draw('>>eList', preselectionCut)
    eList = gDirectory.Get('eList')
    print '-- INFO: number of events passing preselection:', eList.GetN()

    for i in xrange(numToProcess):

        ###################################################################
        # Some printout monitoring, and fetch the entry.
        if i%1000 == 0:
            sys.stdout.write('\rProcessing entry %i of %i...' %(i, numToProcess))
            sys.stdout.flush()
        if not eList.Contains(i): continue

        numPassedCounter += 1
        c.GetEntry(i)

        nLT[0] = nLongTracks
        Ds_0_40_nc_maxPt_PX[0] = Ds_0_40_nc_maxPt_PX
        Ds_0_40_nc_maxPt_PY[0] = Ds_0_40_nc_maxPt_PY
        Ds_0_40_nc_maxPt_PZ[0] = Ds_0_40_nc_maxPt_PZ
        Ds_0_40_nc_mult = Ds_0_40_nc_mult

        ## Compute Marcello's variables
        Bs4V = TLorentzVector(Bs_0_PX,Bs_0_PY,Bs_0_PZ,Bs_0_PE)
        Mu4V = TLorentzVector(mu_PX,mu_PY,mu_PZ,mu_PE)
        Dsst4V = TLorentzVector(Ds_PX+Ds_0_40_nc_maxPt_PX,Ds_PY+Ds_0_40_nc_maxPt_PY,Ds_PZ+Ds_0_40_nc_maxPt_PZ,Ds_PE+Ds_0_40_nc_maxPt_PE)
        Ds4V = TLorentzVector(Ds_PX,Ds_PY,Ds_PZ,Ds_PE)
        DsstMu4V = Dsst4V + Mu4V
        DsMu4V = Ds4V + Mu4V
        DsstMu3V = DsstMu4V.Vect()
        DsMu3V = DsMu4V.Vect()
        Bs4V3 = Bs4V.Vect()
        Bs_dir = TVector3(Bs_0_ENDVERTEX_X - Bs_0_OWNPV_X,
                          Bs_0_ENDVERTEX_Y - Bs_0_OWNPV_Y,
                          Bs_0_ENDVERTEX_Z - Bs_0_OWNPV_Z)
        Bs_dir_phi = Bs_dir.Phi()
        Bs_dir_eta = Bs_dir.Eta()
        Bs_dir_theta = Bs_dir.Theta()
        Bs_dir_mag = Bs_dir.Mag()
        bSinFlightAng[0] = sin(Bs_dir_theta)
        bFlightLen[0] = Bs_dir_mag
        ## ComputeBMom2Fold
        b3V = DsstMu4V.Vect() ## 3-mom of the b-hadron
        angF = Bs_dir.Angle(b3V)
        aaa = 4*(-pow(DsstMu4V.E(),2) + pow(DsstMu4V.P()*cos(angF),2))
        bbb = 4*DsstMu4V.P()*cos(angF)*( pow(BsMassPDG,2) + DsstMu4V.Mag2() )
        ccc = -4*pow(DsstMu4V.E(),2)*pow(DsstMu4V.P(),2) + pow(pow(BsMassPDG,2)-DsstMu4V.Mag2()-2*pow(DsstMu4V.P(),2),2)
        det=pow(bbb,2)-4*aaa*ccc
        pHigh = -bbb/(2*aaa)
        pLow = -bbb/(2*aaa)
        sq[0] = -1
        if( det>0 ):
          sq[0] = 1
          pLow=(-bbb+sqrt(det))/(2*aaa)
          pHigh=(-bbb-sqrt(det))/(2*aaa)
        ## end of function
        
        B3vHigh = (Bs_dir.Unit())*pHigh
        B3vLow = (Bs_dir.Unit())*pLow
        Bs4vHigh = TLorentzVector( B3vHigh,sqrt( BsMassPDG*BsMassPDG+B3vHigh.Mag2() ) )
        Bs4vLow = TLorentzVector( B3vLow,sqrt( BsMassPDG*BsMassPDG+B3vLow.Mag2() ) )
        pBsP1[0] = pHigh
        pBsP2[0] = pLow
        q2P1[0], mm2P1[0], thlP1[0], elcmP1[0], wP1[0] = SemiDec(Bs4vHigh, Dsst4V, Mu4V)
        q2P2[0], mm2P2[0], thlP2[0], elcmP2[0], wP2[0] = SemiDec(Bs4vLow, Dsst4V, Mu4V)
    
        ## ========================================================================
        ## Boost Approx. Kinematics
        ## ========================================================================
        pBsY[0] = (BsMassPDG/DsstMu4V.M())*(DsstMu4V.Pz())*sqrt(1+tan(Bs_dir_theta)*tan(Bs_dir_theta))
        BsFromY3 = (Bs_dir.Unit())*(pBsY)
        EBsFromY = sqrt(pBsY*pBsY+BsMassPDG*BsMassPDG)
        BsFromY = TLorentzVector(BsFromY3.X(),BsFromY3.Y(),BsFromY3.Z(),EBsFromY )
        q2Y[0], mm2Y[0], thlY[0], elcmY[0], wY[0] = SemiDec(BsFromY, Dsst4V, Mu4V)
    
        ## ==========================
        ## compute corrected mass
        ## ==========================
        ## Ds corrected mass
        Ds3V = Ds4V.Vect()
        pTcorrDs = DsMu3V.Perp(Bs_dir)
        McorrDs[0] = sqrt( DsMu4V.M2()+pow(pTcorrDs,2) ) + pTcorrDs
        ## Dsst corrected mass
        Dsst3V = Dsst4V.Vect()
        pTcorrDsst = DsstMu3V.Perp(Bs_dir)
        McorrDsst[0] = sqrt( DsstMu4V.M2()+pow(pTcorrDsst,2) ) + pTcorrDsst
        #Mu3V = Mu4V.Vect()
        #pTcorr = Mu3V.Perp(Bs_dir)

        ##################################################################
        # Now fill the ntuple.
        tOut.Fill()
    
    ##################################################################
    # Print some info.
    print
    print '-- Created ntuple.'
    print '-- Passed %i entries of %i.' %(numPassedCounter, numToProcess)
    # Write and change up directory.
    tOut.Write()
    fOut.cd('..')

  # Now close the file.    
  fOut.Close()

  return

def SemiDec( PB4v, PD4v, PL4v ): 

  _bmass = PB4v.M() 
  _bmass2 = PB4v.M2()
  _dmass = PD4v.M() 
  _dmass2 = PD4v.M2()

  pW = PB4v - PD4v
  pY = PD4v + PL4v
  pNu = PB4v - pY

  _q2 = pW.M2()
  _mm2 = pNu.M2()
  _wvar = -1.
  if(_bmass*_dmass != 0):
    _wvar = PB4v.Dot(PD4v)/(_bmass*_dmass)
  

  _emiss = pNu.E()
  _pmiss = pNu.Rho()

  pmu = PL4v
  pmu.Boost(-PB4v.BoostVector())
  _elcm = pmu.E()

  pWbframe = pW
  pWbframe.Boost(-PB4v.BoostVector())
  pmu1 = PL4v
  Wboost = TVector3(-pW.X()/pW.T(),-pW.Y()/pW.T(),-pW.Z()/pW.T())
  pmu1.Boost(Wboost)

  _thl = pmu1.Angle(pWbframe.Vect())
  if( isnan(_thl) ): 
    _thl=-10
  _thl = pmu1.Angle(pWbframe.Vect())

  return _q2, _mm2, _thl, _elcm, _wvar  



if __name__ == '__main__':
  addVars()

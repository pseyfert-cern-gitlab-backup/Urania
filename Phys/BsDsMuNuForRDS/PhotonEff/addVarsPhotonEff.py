#!/usr/bin/env python

''' This code creates a reduced ntuple without doing the photon association '''

from ROOT import *
import os,sys
from math import *

#dataTag  = sys.argv[1] #'BdDstDs'
#polarity = sys.argv[2] #'MagDown'
dataTag = "Data_PhotonEff"
polarity = 'AllIn'

# Resonance masses in GeV/c2 from the PDG.
BsMassPDG = 5366.82
DsMassPDG = 1968.27
DsstMassPDG = 2112.1
#BsMassPDG = 5279.32
#DsMassPDG = 1864.83
#DsstMassPDG = 2006.85

# A dict containing lists of all files to be added for each type of data and polarity.
# Also contains the tuple names for each file type to be cycled over.
dataDict = {

    'Data_PhotonEff' : { 'tNames'  : [ 'B2DsMuNuTuple/DecayTree' ,
                                       'B2DsMuNuSSTuple/DecayTree' ]
                         ,'AllIn'     : [ 'photonControl_Up_5.root' ]
                         ,'AllInOut'  : 'photonControl_Up_5_cut.root' 
                       }
}

def addVarsPhotonEff():

  # Make the new file.
  baseName = '/afs/cern.ch/user/r/rvazquez/work/'
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
    #dataDir = '/afs/cern.ch/user/r/rvazquez/work/gangadir/workspace/rvazquez/LocalXML/1467/'
    dataDir = '/eos/lhcb/user/r/rvazquez/RDS/PhotonControlTuples/'

    # Now populate a list of full names to be passed to the ROOT classes.
    outList = []
    for endName in inList:
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
    B_PX = z(1)
    B_PY = z(1)
    B_PZ = z(1)
    B_PE = z(1)
    B_MM = z(1)
    B_MMERR = z(1)
    B_P = z(1)
    B_DIRA_OWNPV = z(1)
    Ds_0_40_nc_maxPt_PX = z(1)
    Ds_0_40_nc_maxPt_PY = z(1)
    Ds_0_40_nc_maxPt_PZ = z(1)
    Ds_0_40_nc_maxPt_PE = z(1)
    Ds_0_40_nc_secPt_PX = z(1)
    Ds_0_40_nc_secPt_PY = z(1)
    Ds_0_40_nc_secPt_PZ = z(1)
    Ds_0_40_nc_secPt_PE = z(1)
    Ds_0_40_nc_thiPt_PX = z(1)
    Ds_0_40_nc_thiPt_PY = z(1)
    Ds_0_40_nc_thiPt_PZ = z(1)
    Ds_0_40_nc_thiPt_PE = z(1)
    Ds_0_40_nc_mult = z(1,dtype=int)
    Ds_0_40_nc_radius = z(1)
    Ds_0_40_nc_CL = z(1) 
    Ds_PX = z(1)
    Ds_PY = z(1)
    Ds_PZ = z(1)
    Ds_PE = z(1)
    Kpl_PX = z(1)
    Kpl_PY = z(1)
    Kpl_PZ = z(1)
    Kpl_PE = z(1)
    Kmi_PX = z(1)
    Kmi_PY = z(1)
    Kmi_PZ = z(1)
    Kmi_PE = z(1)
    Kpl_PIDK = z(1)
    Kmi_PIDK = z(1)
    Kpl_PIDp = z(1)
    Kmi_PIDp = z(1)
    pi_PIDK = z(1)
    piFromB_PIDK = z(1)
    piFromB_PX = z(1)
    piFromB_PY = z(1)
    piFromB_PZ = z(1)
    piFromB_PE = z(1)
    piFromB_MINIPCHI2 = z(1)
    B_ENDVERTEX_X = z(1)
    B_OWNPV_X = z(1)
    B_ENDVERTEX_Y = z(1)
    B_OWNPV_Y = z(1)
    B_ENDVERTEX_Z = z(1)
    B_OWNPV_Z = z(1)
    B_ENDVERTEX_CHI2 = z(1)
    Ds_ENDVERTEX_X = z(1)
    Ds_OWNPV_X = z(1)
    Ds_ENDVERTEX_Y = z(1)
    Ds_OWNPV_Y = z(1)
    Ds_ENDVERTEX_Z = z(1)
    Ds_OWNPV_Z = z(1) 
    Ds_ENDVERTEX_CHI2 = z(1)

    Ds_MM = z(1)
    nLongTracks = z(1, dtype=int)

    c.SetBranchAddress('B_PX',B_PX)
    c.SetBranchAddress('B_PY',B_PY)
    c.SetBranchAddress('B_PZ',B_PZ)
    c.SetBranchAddress('B_PE',B_PE)
    c.SetBranchAddress('B_MM',B_MM)
    c.SetBranchAddress('B_MMERR',B_MMERR)
    c.SetBranchAddress('B_P',B_P)
    c.SetBranchAddress('B_DIRA_OWNPV',B_DIRA_OWNPV)
    c.SetBranchAddress('Ds_0.40_nc_maxPt_PX',Ds_0_40_nc_maxPt_PX)
    c.SetBranchAddress('Ds_0.40_nc_maxPt_PY',Ds_0_40_nc_maxPt_PY)
    c.SetBranchAddress('Ds_0.40_nc_maxPt_PZ',Ds_0_40_nc_maxPt_PZ)
    c.SetBranchAddress('Ds_0.40_nc_maxPt_PE',Ds_0_40_nc_maxPt_PE)
    c.SetBranchAddress('Ds_0.40_nc_mult',Ds_0_40_nc_mult)
    c.SetBranchAddress('Ds_0.40_nc_radius',Ds_0_40_nc_radius)
    c.SetBranchAddress('Ds_0.40_nc_CL',Ds_0_40_nc_CL)
    c.SetBranchAddress('Ds_0.40_nc_secPt_PX',Ds_0_40_nc_secPt_PX)
    c.SetBranchAddress('Ds_0.40_nc_secPt_PY',Ds_0_40_nc_secPt_PY)
    c.SetBranchAddress('Ds_0.40_nc_secPt_PZ',Ds_0_40_nc_secPt_PZ)
    c.SetBranchAddress('Ds_0.40_nc_secPt_PE',Ds_0_40_nc_secPt_PE)
    c.SetBranchAddress('Ds_0.40_nc_thiPt_PX',Ds_0_40_nc_thiPt_PX)
    c.SetBranchAddress('Ds_0.40_nc_thiPt_PY',Ds_0_40_nc_thiPt_PY)
    c.SetBranchAddress('Ds_0.40_nc_thiPt_PZ',Ds_0_40_nc_thiPt_PZ)
    c.SetBranchAddress('Ds_0.40_nc_thiPt_PE',Ds_0_40_nc_thiPt_PE) 
    c.SetBranchAddress('Ds_PX',Ds_PX)
    c.SetBranchAddress('Ds_PY',Ds_PY)
    c.SetBranchAddress('Ds_PZ',Ds_PZ)
    c.SetBranchAddress('Ds_PE',Ds_PE)
    c.SetBranchAddress('Kpl_PX',Kpl_PX)
    c.SetBranchAddress('Kpl_PY',Kpl_PY)
    c.SetBranchAddress('Kpl_PZ',Kpl_PZ)
    c.SetBranchAddress('Kpl_PE',Kpl_PE)
    c.SetBranchAddress('Kmi_PX',Kmi_PX)
    c.SetBranchAddress('Kmi_PY',Kmi_PY)
    c.SetBranchAddress('Kmi_PZ',Kmi_PZ)
    c.SetBranchAddress('Kmi_PE',Kmi_PE)
    c.SetBranchAddress('Kpl_PIDK',Kpl_PIDK)
    c.SetBranchAddress('Kmi_PIDK',Kmi_PIDK)
    c.SetBranchAddress('Kpl_PIDp',Kpl_PIDp)
    c.SetBranchAddress('Kmi_PIDp',Kmi_PIDp)
    c.SetBranchAddress('pi_PIDK',pi_PIDK)
    c.SetBranchAddress('piFromB_PIDK',piFromB_PIDK)
    c.SetBranchAddress('piFromB_PX',piFromB_PX)
    c.SetBranchAddress('piFromB_PY',piFromB_PY)
    c.SetBranchAddress('piFromB_PZ',piFromB_PZ)
    c.SetBranchAddress('piFromB_PE',piFromB_PE) 
    c.SetBranchAddress('piFromB_MINIPCHI2',piFromB_MINIPCHI2)
    c.SetBranchAddress('B_ENDVERTEX_X',B_ENDVERTEX_X)
    c.SetBranchAddress('B_ENDVERTEX_Y',B_ENDVERTEX_Y)
    c.SetBranchAddress('B_ENDVERTEX_Z',B_ENDVERTEX_Z)
    c.SetBranchAddress('B_OWNPV_X',B_OWNPV_X)
    c.SetBranchAddress('B_OWNPV_Y',B_OWNPV_Y)
    c.SetBranchAddress('B_OWNPV_Z',B_OWNPV_Z)
    c.SetBranchAddress('B_ENDVERTEX_CHI2',B_ENDVERTEX_CHI2)
    c.SetBranchAddress('Ds_ENDVERTEX_X',Ds_ENDVERTEX_X)
    c.SetBranchAddress('Ds_ENDVERTEX_Y',Ds_ENDVERTEX_Y)
    c.SetBranchAddress('Ds_ENDVERTEX_Z',Ds_ENDVERTEX_Z)
    c.SetBranchAddress('Ds_OWNPV_X',Ds_OWNPV_X)
    c.SetBranchAddress('Ds_OWNPV_Y',Ds_OWNPV_Y)
    c.SetBranchAddress('Ds_OWNPV_Z',Ds_OWNPV_Z)
    c.SetBranchAddress('Ds_ENDVERTEX_CHI2',Ds_ENDVERTEX_CHI2)
    c.SetBranchAddress('Ds_MM',Ds_MM)
    c.SetBranchAddress('nLongTracks',nLongTracks)

    ### new variables
    sq = z(1, dtype=int)
    determinant = z(1)
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

    nLT = z(1, dtype=int)
    Bs_VCHI2 = z(1)
    Bs_DIRA = z(1)
    Ds_VCHI2 = z(1)
    DsHigh = z(1)
    DsLow = z(1)
    Bs_Mom = z(1)
    piPIDK = z(1)
    piFromBPIDK = z(1)
    piFromBMINIPCHI2 = z(1)
    pi_PT = z(1)
    piTrick_PT = z(1)
    pTPiTrickBsdir = z(1)
    mDsst = z(1)
    mDsG = z(1)
    mDsGSec = z(1)
    mDsGThi = z(1)
    m1Dsst = z(1)
    m2Dsst = z(1)
    mDsGPi = z(1)
    pDsstY = z(1)
    mBsAnother = z(1)
    mDsstAnother = z(1)
    #Bs_NewCorr = z(1)

    gamma_PX = z(1)
    gamma_PY = z(1)
    gamma_PZ = z(1)
    gamma_PE = z(1)
    gamma_mult = z(1, dtype=int)
    gamma_CL = z(1)
    gamma_rad = z(1)

    ## new vars
    tOut.Branch('sq',sq,'sq/I')
    tOut.Branch('det',determinant,'det/D')
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
    tOut.Branch('gamma_PX',gamma_PX,'gamma_PX/D')
    tOut.Branch('gamma_PY',gamma_PY,'gamma_PY/D')
    tOut.Branch('gamma_PZ',gamma_PZ,'gamma_PZ/D')
    tOut.Branch('gamma_PE',gamma_PE,'gamma_PE/D')
    tOut.Branch('gamma_mult',gamma_mult,'gamma_mult/I')
    tOut.Branch('gamma_rad',gamma_rad,'gamma_rad/D')
    tOut.Branch('gamma_CL',gamma_CL,'gamma_CL/D')

    tOut.Branch('Ds_MM',Ds_MM,'Ds_MM/D')
    tOut.Branch('Bs_MM',B_MM,'Bs_MM/D')
    tOut.Branch('Bs_MMERR',B_MMERR,'Bs_MMERR/D')
    tOut.Branch('Bs_VCHI2',Bs_VCHI2,'Bs_VCHI2/D')
    tOut.Branch('Bs_DIRA',Bs_DIRA,'Bs_DIRA/D')
    tOut.Branch('Ds_VCHI2',Ds_VCHI2,'Ds_VCHI2/D')
    tOut.Branch('DsHigh',DsHigh,'DsHigh/D')
    tOut.Branch('DsLow',DsLow,'DsLow/D')
    tOut.Branch('Bs_Mom',Bs_Mom,'Bs_Mom/D')
    tOut.Branch('piPIDK',piPIDK,'piPIDK/D')
    tOut.Branch('piFromBPIDK',piFromBPIDK,'piFromBPIDK/D')
    tOut.Branch('piFromBMINIPCHI2',piFromBMINIPCHI2,'piFromBMINIPCHI2/D')
    tOut.Branch('pi_PT',pi_PT,'pi_PT/D')
    tOut.Branch('piTrick_PT',piTrick_PT,'piTrick_PT/D')
    tOut.Branch('piTrickBsdir_PT',pTPiTrickBsdir,'piTrickBsdir_PT/D')
    tOut.Branch('massDsst',mDsst,'massDsst/D')
    tOut.Branch('massDsG',mDsG,'massDsG/D')
    tOut.Branch('massDsGSec',mDsGSec,'massDsGSec/D')
    tOut.Branch('massDsGThi',mDsGThi,'massDsGThi/D')
    tOut.Branch('m1Dsst',m1Dsst,'m1Dsst/D')
    tOut.Branch('m2Dsst',m2Dsst,'m2Dsst/D')
    tOut.Branch('mDsGPi',mDsGPi,'mDsGPi/D')
    tOut.Branch('pDsstY',pDsstY,'pDsstY/D')
    tOut.Branch('mBsAnother',mBsAnother,'mBsAnother/D')
    tOut.Branch('mDsstAnother',mDsstAnother,'mDsstAnother/D')
    #tOut.Branch('Bs_NewCorr',Bs_NewCorr,'Bs_NewCorr/D')

    #####################################################################################
    # Now loop over the events and plot the Dalitz variables.
    #####################################################################################
    numToProcess = c.GetEntries()
    numPassedCounter = 0
    print '-- INFO: number of events to process:', numToProcess

    #preselectionCut = '1'
    preselectionCut = 'Ds_MM>1940 && Ds_MM<2000 && Kpl_PIDK-Kpl_PIDp>-10 && Kmi_PIDK-Kmi_PIDp>-10 && B_MM<5600 && B_MM>4900 && B_ENDVERTEX_CHI2<6 && abs(sqrt((Kpl_PE+Kmi_PE)**2-(Kpl_PX+Kmi_PX)**2-(Kpl_PY+Kmi_PY)**2-(Kpl_PZ+Kmi_PZ)**2)-1019.46)<7'
    c.Draw('>>eList', preselectionCut)
    eList = gDirectory.Get('eList')
    print '-- INFO: number of events passing preselection:', eList.GetN()

    for i in xrange(numToProcess):

        ###################################################################
        # Some printout monitoring, and fetch the entry.
        if i%10000 == 0:
            sys.stdout.write('\rProcessing entry %i of %i...' %(i, numToProcess))
            sys.stdout.flush()
        if not eList.Contains(i): continue

        numPassedCounter += 1
        c.GetEntry(i)

        nLT[0] = nLongTracks
        Ds_MM[0] = Ds_MM
        B_MM[0] = B_MM
        B_MMERR[0] = B_MMERR
        gamma_PX[0] = Ds_0_40_nc_maxPt_PX
        gamma_PY[0] = Ds_0_40_nc_maxPt_PY
        gamma_PZ[0] = Ds_0_40_nc_maxPt_PZ
        gamma_PE[0] = Ds_0_40_nc_maxPt_PE
        gamma_mult[0] = Ds_0_40_nc_mult
        gamma_CL[0] = Ds_0_40_nc_CL
        gamma_rad[0] = Ds_0_40_nc_radius
        Bs_VCHI2[0] = B_ENDVERTEX_CHI2
        Ds_VCHI2[0] = Ds_ENDVERTEX_CHI2
        Bs_DIRA[0] = B_DIRA_OWNPV
        piPIDK[0] = pi_PIDK
        piFromBPIDK[0] = piFromB_PIDK
        piFromBMINIPCHI2[0] = piFromB_MINIPCHI2
        pi_PT[0] = sqrt(piFromB_PX**2+piFromB_PY**2)

        Dsst4V = TLorentzVector(Ds_PX+Ds_0_40_nc_maxPt_PX,Ds_PY+Ds_0_40_nc_maxPt_PY,Ds_PZ+Ds_0_40_nc_maxPt_PZ,Ds_PE+Ds_0_40_nc_maxPt_PE)
        mDsG[0] = Dsst4V.Mag()

        DsstSec4V = TLorentzVector(Ds_PX+Ds_0_40_nc_secPt_PX,Ds_PY+Ds_0_40_nc_secPt_PY,Ds_PZ+Ds_0_40_nc_secPt_PZ,Ds_PE+Ds_0_40_nc_secPt_PE)
        mDsGSec[0] = DsstSec4V.Mag()
   
        DsstThi4V = TLorentzVector(Ds_PX+Ds_0_40_nc_thiPt_PX,Ds_PY+Ds_0_40_nc_thiPt_PY,Ds_PZ+Ds_0_40_nc_thiPt_PZ,Ds_PE+Ds_0_40_nc_thiPt_PE)
        mDsGThi[0] = DsstThi4V.Mag()

        ## Compute Marcello's variables
        Bs4V = TLorentzVector(B_PX,B_PY,B_PZ,B_PE)
        PiFromB4V = TLorentzVector(piFromB_PX,piFromB_PY,piFromB_PZ,piFromB_PE)
        Ds4V = TLorentzVector(Ds_PX,Ds_PY,Ds_PZ,Ds_PE)
        DsPi4V = Ds4V + PiFromB4V
        DsstPi4V = Dsst4V + PiFromB4V
        mDsGPi[0] = DsstPi4V.Mag()
        DsstPi3V = DsstPi4V.Vect()
        DsPi3V = DsPi4V.Vect()
        Bs4V3 = Bs4V.Vect()
        Bs_dir = TVector3(B_ENDVERTEX_X - B_OWNPV_X,
                          B_ENDVERTEX_Y - B_OWNPV_Y,
                          B_ENDVERTEX_Z - B_OWNPV_Z)
        Bs_dir_phi = Bs_dir.Phi()
        Bs_dir_eta = Bs_dir.Eta()
        Bs_dir_theta = Bs_dir.Theta()
        Bs_dir_mag = Bs_dir.Mag()
        bSinFlightAng[0] = sin(Bs_dir_theta)
        bFlightLen[0] = Bs_dir_mag
        ## ComputeBMom2Fold
        ##b3V = DsstPi4V.Vect() ## 3-mom of the b-hadron
        b3V = DsPi4V.Vect()
        angF = Bs_dir.Angle(b3V)
        ##aaa = 4*(-pow(DsstPi4V.E(),2) + pow(DsstPi4V.P()*cos(angF),2))
        aaa = 4*(-pow(DsPi4V.E(),2) + pow(DsPi4V.P()*cos(angF),2))
        ##bbb = 4*DsstPi4V.P()*cos(angF)*( pow(BsMassPDG,2) + DsstPi4V.Mag2() )
        bbb = 4*DsPi4V.P()*cos(angF)*( pow(BsMassPDG,2) + DsPi4V.Mag2() )
        ##ccc = -4*pow(DsstPi4V.E(),2)*pow(DsstPi4V.P(),2) + pow(pow(BsMassPDG,2)-DsstPi4V.Mag2()-2*pow(DsstPi4V.P(),2),2)
        ccc = -4*pow(DsPi4V.E(),2)*pow(DsPi4V.P(),2) + pow(pow(BsMassPDG,2)-DsPi4V.Mag2()-2*pow(DsPi4V.P(),2),2)
        det=pow(bbb,2)-4*aaa*ccc
        pHigh = -bbb/(2*aaa)
        pLow = -bbb/(2*aaa)
        determinant[0] = det
        sq[0] = -1
        if( det>0 ):
          sq[0] = 1
          pLow=(-bbb+sqrt(det))/(2*aaa)
          pHigh=(-bbb-sqrt(det))/(2*aaa)
        ## end of function
       
        ## ricci's attempt
        Pi3V = PiFromB4V.Vect()
        pTPiBsdir = Pi3V.Perp(Bs_dir)
        angle = Pi3V.Angle(Bs_dir)
        BMom = pTPiBsdir/sin(angle)
        Bs_Mom[0] = BMom
        pTPiTrickBsdir[0] = pTPiBsdir

        #Bs_NewCorr[0] = sqrt(B_MM**2+(B_P*sqrt(1-B_DIRA_OWNPV**2))**2) + B_P*sqrt(1-B_DIRA_OWNPV**2)

        origin = TVector3(0,0,1)
        pTPiTrick = Pi3V.Perp(origin)
        piTrick_PT[0] = pTPiTrick

#        pGamma = ((2112.1**2-1968.27**2)/2)*(1/(Ds_PE-sqrt(Ds_PX**2+Ds_PY**2+Ds_PZ**2)))
        

        ## Dsstar mass
        BsE = sqrt(BMom**2+BsMassPDG**2)
        mDsst[0] = sqrt((BsE-PiFromB4V.E())**2-(BMom-Pi3V.Mag())**2)

        B3vHigh = (Bs_dir.Unit())*pHigh
        B3vLow = (Bs_dir.Unit())*pLow
        Bs4vHigh = TLorentzVector( B3vHigh,sqrt( BsMassPDG*BsMassPDG+B3vHigh.Mag2() ) )
        Bs4vLow = TLorentzVector( B3vLow,sqrt( BsMassPDG*BsMassPDG+B3vLow.Mag2() ) )
        Ds4VHigh = Bs4vHigh-PiFromB4V
        Ds4VLow = Bs4vLow-PiFromB4V
        DsMassHigh = Ds4VHigh.M()
        DsMassLow = Ds4VLow.M()
 
        P1Gamma4V = Bs4vHigh - Bs4V
        P2Gamma4V = Bs4vLow - Bs4V

        P1Dsst4V = Ds4V + P1Gamma4V
        P2Dsst4V = Ds4V + P2Gamma4V
    
        m1Dsst[0] = P1Dsst4V.M()
        m2Dsst[0] = P2Dsst4V.M()

        DsHigh[0] = DsMassHigh
        DsLow[0] = DsMassLow
        pBsP1[0] = pHigh
        pBsP2[0] = pLow
        #q2P1[0], mm2P1[0], thlP1[0], elcmP1[0], wP1[0] = SemiDec(Bs4vHigh, Dsst4V, Pi4V)
        #q2P2[0], mm2P2[0], thlP2[0], elcmP2[0], wP2[0] = SemiDec(Bs4vLow, Dsst4V, Pi4V)
        q2P1[0], mm2P1[0], thlP1[0], elcmP1[0], wP1[0] = SemiDec(Bs4vHigh, Ds4V, PiFromB4V)
        q2P2[0], mm2P2[0], thlP2[0], elcmP2[0], wP2[0] = SemiDec(Bs4vLow, Ds4V, PiFromB4V)

        ## Another boost approx
        Ds_dir = TVector3(Ds_ENDVERTEX_X - Ds_OWNPV_X,
                          Ds_ENDVERTEX_Y - Ds_OWNPV_Y,
                          Ds_ENDVERTEX_Z - Ds_OWNPV_Z)
        Ds_dir_theta = Ds_dir.Theta()
        pDsstY[0] = (DsstMassPDG/Ds4V.M())*(Ds4V.Pz())*sqrt(1+tan(Ds_dir_theta)*tan(Ds_dir_theta))
        DsstFromY3V = (Ds_dir.Unit())*(pDsstY) 
        EDsstFromY = sqrt(pDsstY*pDsstY+DsstMassPDG*DsstMassPDG)
        DsstFromY4V = TLorentzVector(DsstFromY3V.X(), DsstFromY3V.Y(), DsstFromY3V.Z(), EDsstFromY)
        mDsstAnother[0] = DsstFromY4V.M()
        BsAnother4V = DsstFromY4V + PiFromB4V
        mBsAnother[0] = BsAnother4V.M()

        ## ========================================================================
        ## Boost Approx. Kinematics
        ## ========================================================================
        ##pBsY[0] = (BsMassPDG/DsstPi4V.M())*(DsstPi4V.Pz())*sqrt(1+tan(Bs_dir_theta)*tan(Bs_dir_theta))
        pBsY[0] = (BsMassPDG/DsPi4V.M())*(DsPi4V.Pz())*sqrt(1+tan(Bs_dir_theta)*tan(Bs_dir_theta))
        BsFromY3 = (Bs_dir.Unit())*(pBsY)
        EBsFromY = sqrt(pBsY*pBsY+BsMassPDG*BsMassPDG)
        BsFromY = TLorentzVector(BsFromY3.X(),BsFromY3.Y(),BsFromY3.Z(),EBsFromY )
        #q2Y[0], mm2Y[0], thlY[0], elcmY[0], wY[0] = SemiDec(BsFromY, Dsst4V, Pi4V)
        q2Y[0], mm2Y[0], thlY[0], elcmY[0], wY[0] = SemiDec(BsFromY, Ds4V, PiFromB4V)

        ## ==========================
        ## compute corrected mass
        ## ==========================
        ## Ds corrected mass
        pTcorrDs = DsPi3V.Perp(Bs_dir)
        McorrDs[0] = sqrt( DsPi4V.M2()+pow(pTcorrDs,2) ) + pTcorrDs
        #McorrDs[0] = sqrt( DsPi4V.M2()+pow(pTcorrDs,2) )
        ## Dsst corrected mass
        pTcorrDsst = DsstPi3V.Perp(Bs_dir)
        McorrDsst[0] = sqrt( DsstPi4V.M2()+pow(pTcorrDsst,2) ) + pTcorrDsst
        #McorrDsst[0] = sqrt( DsstPi4V.M2()+pow(pTcorrDsst,2) )

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
  addVarsPhotonEff()

from ROOT import *
from math import *
from parameters import *

# ################################################################
# V A R I A B L E S
# ################################################################

# Names of the variables in the ntuples.

KpPx_name = 'B_s0_DTF_KST1_K_PX'
KpPy_name = 'B_s0_DTF_KST1_K_PY'
KpPz_name = 'B_s0_DTF_KST1_K_PZ'
KmPx_name = 'B_s0_DTF_KST2_K_PX'
KmPy_name = 'B_s0_DTF_KST2_K_PY'
KmPz_name = 'B_s0_DTF_KST2_K_PZ'
PipPx_name = 'B_s0_DTF_KST2_PI_PX'
PipPy_name = 'B_s0_DTF_KST2_PI_PY'
PipPz_name = 'B_s0_DTF_KST2_PI_PZ'
PimPx_name = 'B_s0_DTF_KST1_PI_PX'
PimPy_name = 'B_s0_DTF_KST1_PI_PY'
PimPz_name = 'B_s0_DTF_KST1_PI_PZ'

KpP_name = 'B_s0_DTF_KST1_K_P'
KmP_name = 'B_s0_DTF_KST2_K_P'
PipP_name = 'B_s0_DTF_KST2_PI_P'
PimP_name = 'B_s0_DTF_KST1_PI_P'

KpPx_TRUE_name = 'Kplus_TRUEP_X'
KpPy_TRUE_name = 'Kplus_TRUEP_Y'
KpPz_TRUE_name = 'Kplus_TRUEP_Z'
KmPx_TRUE_name = 'Kminus_TRUEP_X'
KmPy_TRUE_name = 'Kminus_TRUEP_Y'
KmPz_TRUE_name = 'Kminus_TRUEP_Z'
PipPx_TRUE_name = 'Piplus_TRUEP_X'
PipPy_TRUE_name = 'Piplus_TRUEP_Y'
PipPz_TRUE_name = 'Piplus_TRUEP_Z'
PimPx_TRUE_name = 'Piminus_TRUEP_X'
PimPy_TRUE_name = 'Piminus_TRUEP_Y'
PimPz_TRUE_name = 'Piminus_TRUEP_Z'

ctau_name = 'B_s0_DTF_CTAU'
truetau_name = 'B_s0_TRUETAU'
ctauerr_name = 'B_s0_DTF_CTAUERR'

# ################################################################
# F U N C T I O N S
# ################################################################

def deltap(p):
	x = p/1000.
	return p*0.01*(0.43309584679004054 + 0.006136502016572859*x - 0.0000215311159170714*x*x + 3.306945947698e-8*x*x*x)

gROOT.ProcessLine(\
	"struct MyStruct{\
	Float_t afloat;\
	};")
from ROOT import MyStruct

gROOT.ProcessLine(\
	"struct MyStruct2{\
	Int_t aint;\
	};")
from ROOT import MyStruct2

#Function to multiply an array by a number (NProduct = Number Product)
def NProduct(alpha, Vect):
        Vect1 = range(3)
        for i in range(0,3):
            Vect1[i] = alpha*Vect[i]
        return Vect1


#Function to multiply a TVector3 by a number (NProductV = Number Product Vector)
def NProductV(alpha, Vect):
        Vect1 = [Vect.x(),Vect.y(),Vect.z()]
        for i in range(0,3):
            Vect1[i] = alpha*Vect[i]
        return TVector3(Vect1[0],Vect1[1],Vect1[2])


#Function to sum two arrays
def ArraySum(Vect1, Vect2):
        Vect = range(3)
        for i in range(0,3):
            Vect[i] = Vect1[i] + Vect2[i]
        return Vect


#Function to calculate the vector product of two vectors
def VProduct(Vect1, Vect2):
        Product = range(3)
        Product[0] = Vect1[1]*Vect2[2] - Vect1[2]*Vect2[1]
        Product[1] = -Vect1[0]*Vect2[2] + Vect1[2]*Vect2[0]
        Product[2] = Vect1[0]*Vect2[1] - Vect1[1]*Vect2[0]
        return Product


#Function to calculate the dot product of two vectors
def DProduct(Vector1, Vector2):
        Product = Vector1[0]*Vector2[0] + Vector1[1]*Vector2[1] + Vector1[2]*Vector2[2]
        return Product


#Function to calculate the module of a vector 3D
def VectorModule(fData):
        Module = sqrt(DProduct( fData, fData)) 
        return Module


#Function to calculate the unitary vector
def VectorUnitary(fData):
        Module = VectorModule(fData)
        Aux = NProduct(1./Module, fData)
        return Aux


#Function to calculate the parameters for the Armenteros plots
def get_APvars(P11_P,P12_P):
	P1_P = P11_P + P12_P
	P1dir = VectorUnitary(P1_P) # direction of P1
	P11_L = DProduct(P11_P, P1dir) # projection of P11 over the direction of P1
	P12_L = DProduct(P12_P, P1dir) # projection of P12 over the direction of P1
	P11_T = sqrt(VectorModule(P11_P)**2. - P11_L*P11_L) # P11 transverse component
	alpha = (P11_L - P12_L) / (P11_L + P12_L) # AP parameter
	return alpha, P11_T


#function to calculate the Theta1, Theta2 and Phi angles
def get_Angles(kp,pim,km,pip):

        P11p = [kp.Px(), kp.Py(), kp.Pz()]
        P12p = [pim.Px(), pim.Py(), pim.Pz()]
        P21p = [km.Px(), km.Py(), km.Pz()]
        P22p = [pip.Px(), pip.Py(), pip.Pz()]
    
        #Get the masses
        P11mass = kp.M()
        P12mass = pim.M()
        P21mass = km.M()
        P22mass = pip.M()
        P1mass = (kp+pim).M()
        P2mass = (km+pip).M()
        Bmass = (kp+pim+km+pip).M()
    
        #Calculate the momentum of K* and anti-K* (Particle 1 and particle 2)
        P1p = ArraySum( P11p, P12p)
        P2p = ArraySum( P21p, P22p)
        Bp = ArraySum( P1p, P2p)
    
        #Calculate the energies
        BE = sqrt( Bmass*Bmass + DProduct( Bp, Bp))
        P1E = sqrt( P1mass*P1mass + DProduct( P1p, P1p))
        P2E = sqrt( P2mass*P2mass + DProduct( P2p, P2p))
        P11E = sqrt( P11mass*P11mass + DProduct( P11p, P11p))
        P12E = sqrt( P12mass*P12mass + DProduct( P12p, P12p))
        P21E = sqrt( P21mass*P21mass + DProduct( P21p, P21p))
        P22E = sqrt( P22mass*P22mass + DProduct( P22p, P22p))
    
        #Calculate beta and gamma
        BBeta = NProduct( 1./BE, Bp)
        P1Beta = NProduct( 1./P1E, P1p)
        P2Beta = NProduct( 1./P2E, P2p)
    
        BGamma = 1./sqrt( 1 - DProduct( BBeta, BBeta))
        P1Gamma = 1./sqrt( 1 - DProduct( P1Beta, P1Beta))
        P2Gamma = 1./sqrt( 1 - DProduct( P2Beta, P2Beta))
    
        #Calculate the momentum of the K*, K and pi particles on the Bd, (anti-)K* direction
        P1p_B = DProduct( P1p, VectorUnitary( Bp)) #Projection of the K* momentum over the B movement direction
        P2p_B = DProduct( P2p, VectorUnitary( Bp))
        P11p_B = DProduct( P11p, VectorUnitary( Bp))
        P12p_B = DProduct( P12p, VectorUnitary( Bp))
        P21p_B = DProduct( P21p, VectorUnitary( Bp))
        P22p_B = DProduct( P22p, VectorUnitary( Bp))
        P1p_P2 = DProduct( P1p, VectorUnitary( P2p)) #Projection of the K* momentum over the anti-K* movement direction
        P2p_P1 = DProduct( P2p, VectorUnitary( P1p))
        P11p_P1 = DProduct( P11p, VectorUnitary( P1p)) #Projection of the P11 momentum over the particle 1 movement direction
        P12p_P1 = DProduct( P12p, VectorUnitary( P1p))
        P21p_P2 = DProduct( P21p, VectorUnitary( P2p))
        P22p_P2 = DProduct( P22p, VectorUnitary( P2p))
    
        #Calculate the momentum of the K and pi particles in the (anti-)K* rest frame
        #P11p_P1RF1 = particle 11 momentum in the particle 1 rest frame step 1 (move to the P1 rest frame)
        P1p_BRF1 = ArraySum( P1p, NProduct( -1*P1p_B, VectorUnitary( Bp)))
        P2p_BRF1 = ArraySum( P2p, NProduct( -1*P2p_B, VectorUnitary( Bp)))
        P11p_BRF1 = ArraySum( P11p, NProduct( -1*P11p_B, VectorUnitary( Bp)))
        P12p_BRF1 = ArraySum( P12p, NProduct( -1*P12p_B, VectorUnitary( Bp)))
        P21p_BRF1 = ArraySum( P21p, NProduct( -1*P21p_B, VectorUnitary( Bp)))
        P22p_BRF1 = ArraySum( P22p, NProduct( -1*P22p_B, VectorUnitary( Bp)))
        P1p_P2RF1 = ArraySum( P1p, NProduct( -1*P1p_P2, VectorUnitary( P2p)))
        P2p_P1RF1 = ArraySum( P2p, NProduct( -1*P2p_P1, VectorUnitary( P1p)))
        P11p_P1RF1 = ArraySum( P11p, NProduct( -1*P11p_P1, VectorUnitary( P1p)))
        P12p_P1RF1 = ArraySum( P12p, NProduct( -1*P12p_P1, VectorUnitary( P1p)))
        P21p_P2RF1 = ArraySum( P21p, NProduct( -1*P21p_P2, VectorUnitary( P2p)))
        P22p_P2RF1 = ArraySum( P22p, NProduct( -1*P22p_P2, VectorUnitary( P2p)))
    
        #P11p_KstsRF2 = particle 1 momentum in the particle 1 rest frame step 2 (the lorentz transformation)
        P1p_BRF2 = BGamma*P1p_B - BGamma*VectorModule( BBeta)*P1E
        P2p_BRF2 = BGamma*P2p_B - BGamma*VectorModule( BBeta)*P2E
        P11p_BRF2 = BGamma*P11p_B - BGamma*VectorModule( BBeta)*P11E
        P12p_BRF2 = BGamma*P12p_B - BGamma*VectorModule( BBeta)*P12E
        P21p_BRF2 = BGamma*P21p_B - BGamma*VectorModule( BBeta)*P21E
        P22p_BRF2 = BGamma*P22p_B - BGamma*VectorModule( BBeta)*P22E
        P1p_P2RF2 = P2Gamma*P1p_P2 - P2Gamma*VectorModule( P2Beta)*P1E
        P2p_P1RF2 = P1Gamma*P2p_P1 - P1Gamma*VectorModule( P1Beta)*P2E
        P11p_P1RF2 = P1Gamma*P11p_P1 - P1Gamma*VectorModule( P1Beta)*P11E
        P12p_P1RF2 = P1Gamma*P12p_P1 - P1Gamma*VectorModule( P1Beta)*P12E
        P21p_P2RF2 = P2Gamma*P21p_P2 - P2Gamma*VectorModule( P2Beta)*P21E
        P22p_P2RF2 = P2Gamma*P22p_P2 - P2Gamma*VectorModule( P2Beta)*P22E
    
        #P11p_P1RF = particle 1 momentum in the P1 rest frame (sum of the step 1 and step 2)
        P1p_BRF = ArraySum( P1p_BRF1, NProduct( P1p_BRF2, VectorUnitary( Bp)))
        P2p_BRF = ArraySum( P2p_BRF1, NProduct( P2p_BRF2, VectorUnitary( Bp)))
        P11p_BRF = ArraySum( P11p_BRF1, NProduct( P11p_BRF2, VectorUnitary( Bp)))
        P12p_BRF = ArraySum( P12p_BRF1, NProduct( P12p_BRF2, VectorUnitary( Bp)))
        P21p_BRF = ArraySum( P21p_BRF1, NProduct( P21p_BRF2, VectorUnitary( Bp)))
        P22p_BRF = ArraySum( P22p_BRF1, NProduct( P22p_BRF2, VectorUnitary( Bp)))
        P1p_P2RF = ArraySum( P1p_P2RF1, NProduct( P1p_P2RF2, VectorUnitary( P2p)))
        P2p_P1RF = ArraySum( P2p_P1RF1, NProduct( P2p_P1RF2, VectorUnitary( P1p)))
        P11p_P1RF = ArraySum( P11p_P1RF1, NProduct( P11p_P1RF2, VectorUnitary( P1p)))
        P12p_P1RF = ArraySum( P12p_P1RF1, NProduct( P12p_P1RF2, VectorUnitary( P1p)))
        P21p_P2RF = ArraySum( P21p_P2RF1, NProduct( P21p_P2RF2, VectorUnitary( P2p)))
        P22p_P2RF = ArraySum( P22p_P2RF1, NProduct( P22p_P2RF2, VectorUnitary( P2p)))
    
        #Take de oposite of the these vectors
        P2p_P1RF = NProduct( -1., P2p_P1RF)
        P1p_P2RF = NProduct( -1., P1p_P2RF)
    
        #Calculate the cos(theta) from the dot product of the (anti-)K* -P1- and K+(-) -P11- momentums
        CosTheta1 = DProduct( P11p_P1RF, P2p_P1RF) / (VectorModule( P11p_P1RF)*VectorModule( P2p_P1RF))
        CosTheta2 = DProduct( P21p_P2RF, P1p_P2RF) / (VectorModule( P21p_P2RF)*VectorModule( P1p_P2RF))
    
    
        #Calculate the phi angle from the vector product of the (anti-)K* and K+(-) momentums
        #PlaneP1 = plane formed by the P1 and its daughters
        PlaneP1 = VectorUnitary( VProduct( P11p_BRF, P12p_BRF))
        PlaneP2 = VectorUnitary( VProduct( P21p_BRF, P22p_BRF))
    
        #Make a ortogonal base
        Vx = VectorUnitary( PlaneP1)
        Vz = VectorUnitary( P1p_BRF)
        Vy = VectorUnitary( VProduct( Vz, Vx))
    
        #Calculate Sen(Phi) and Cos(Phi)
        CosPhi = DProduct( PlaneP2, Vx)
        SenPhi = DProduct( PlaneP2, Vy)
    
        ## Calculate Phi
        Phi = atan2( SenPhi, CosPhi)
        #Phi = pi - Phi
        #if Phi < 0.: Phi = 2.*pi + Phi
    
        return CosTheta1, CosTheta2, Phi


def AddTrivialWeights(inputfilename,outputfilename):
	
	fwin = TFile(NTUPLE_PATH + inputfilename + '.root')
	twin = fwin.Get('DecayTree')
	fwout = TFile(NTUPLE_PATH + outputfilename + '.root','RECREATE')
	print "Copying the original tree ..."
	twout = twin.CopyTree("")
	print "Tree copied."

	weightvar = MyStruct()
	newBranchweight = twout.Branch('weight', AddressOf(weightvar,'afloat'), 'weight/F')

	print "Processing events ..."
	for i in twout:
		weightvar.afloat = 1.
		newBranchweight.Fill()
	print "All events processed."

	twout.Write()
	fwout.Close()


def rhoKst_PIDcuts(inputfilename,outputfilename):

	ftin = TFile(NTUPLE_PATH+inputfilename+'.root')
	ttin = ftin.Get('AnalysisTree')
	ftout = TFile(NTUPLE_PATH+outputfilename+'.root','RECREATE')
	print "Copying the original tree ..."
	ttout = ttin.CopyTree("")
	print "Tree copied."

	passpid_rhoKst = MyStruct2()
	newBranch_passpid_rhoKst = ttout.Branch('passpid_rhoKst', AddressOf(passpid_rhoKst,'aint'), 'passpid_rhoKst/I')
	Mrho_rhoKst = MyStruct()
	newBranch_Mrho_rhoKst = ttout.Branch('Mrho_rhoKst', AddressOf(Mrho_rhoKst,'afloat'), 'Mrho_rhoKst/F')
	MKst_rhoKst = MyStruct()
	newBranch_MKst_rhoKst = ttout.Branch('MKst_rhoKst', AddressOf(MKst_rhoKst,'afloat'), 'MKst_rhoKst/F')
	MB_rhoKst = MyStruct()
	newBranch_MB_rhoKst = ttout.Branch('MB_rhoKst', AddressOf(MB_rhoKst,'afloat'), 'MB_rhoKst/F')
	Kcharge_rhoKst = MyStruct2()
	newBranch_Kcharge_rhoKst = ttout.Branch('Kcharge_rhoKst', AddressOf(Kcharge_rhoKst,'aint'), 'Kcharge_rhoKst/I')
	is_rhoKst = MyStruct2()
	newBranch_is_rhoKst = ttout.Branch('is_rhoKst', AddressOf(is_rhoKst,'aint'), 'is_rhoKst/I')

	k = TLorentzVector()
	pi = TLorentzVector()
	pi1 = TLorentzVector()
	pi2 = TLorentzVector()

	print "Processing events ..."
	for i in ttout:

		passpid_rhoKst.aint = 0
		Mrho_rhoKst.afloat = -1.
		MKst_rhoKst.afloat = -1.
		MB_rhoKst.afloat = -1.
		Kcharge_rhoKst.aint = 0
		is_rhoKst.aint = 0

		pid_selected = 0
		if i.itype>0:
			kaon_probnnk = max(i.Kplus_ProbNNk,i.Kminus_ProbNNk,i.Piplus_ProbNNk,i.Piminus_ProbNNk)
			if kaon_probnnk>0.2:
				if i.Kplus_ProbNNk==kaon_probnnk and kaon_probnnk*(1.-i.Kplus_ProbNNpi)>0.3:
					if i.Piminus_ProbNNpi>0.2 and i.Kminus_ProbNNpi>0.2 and i.Piplus_ProbNNpi>0.2:
						if i.Piminus_ProbNNpi*(1.-i.Piminus_ProbNNk)>0.3 and i.Kminus_ProbNNpi*(1.-i.Kminus_ProbNNk)>0.3 and i.Piplus_ProbNNpi*(1.-i.Piplus_ProbNNk)>0.3:
							pid_selected = 1
							k.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,493.667)
							pi.SetXYZM(i.Piminus_PX,i.Piminus_PY,i.Piminus_PZ,139.570)
							pi1.SetXYZM(i.Piplus_PX,i.Piplus_PY,i.Piplus_PZ,139.570)
							pi2.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,139.570)
							Kcharge_rhoKst.aint = 1
				elif i.Piminus_ProbNNk==kaon_probnnk and kaon_probnnk*(1.-i.Piminus_ProbNNpi)>0.3:
					if i.Kplus_ProbNNpi>0.2 and i.Kminus_ProbNNpi>0.2 and i.Piplus_ProbNNpi>0.2:
						if i.Kplus_ProbNNpi*(1.-i.Kplus_ProbNNk)>0.3 and i.Kminus_ProbNNpi*(1.-i.Kminus_ProbNNk)>0.3 and i.Piplus_ProbNNpi*(1.-i.Piplus_ProbNNk)>0.3:
							pid_selected = 1
							k.SetXYZM(i.Piminus_PX,i.Piminus_PY,i.Piminus_PZ,493.667)
							pi.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,139.570)
							pi1.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,139.570)
							pi2.SetXYZM(i.Piplus_PX,i.Piplus_PY,i.Piplus_PZ,139.570)
							Kcharge_rhoKst.aint = -1
				elif i.Kminus_ProbNNk==kaon_probnnk and kaon_probnnk*(1.-i.Kminus_ProbNNpi)>0.3:
					if i.Kplus_ProbNNpi>0.2 and i.Piminus_ProbNNpi>0.2 and i.Piplus_ProbNNpi>0.2:
						if i.Kplus_ProbNNpi*(1.-i.Kplus_ProbNNk)>0.3 and i.Piminus_ProbNNpi*(1.-i.Piminus_ProbNNk)>0.3 and i.Piplus_ProbNNpi*(1.-i.Piplus_ProbNNk)>0.3:
							pid_selected = 1
							k.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,493.667)
							pi.SetXYZM(i.Piplus_PX,i.Piplus_PY,i.Piplus_PZ,139.570)
							pi1.SetXYZM(i.Piminus_PX,i.Piminus_PY,i.Piminus_PZ,139.570)
							pi2.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,139.570)
							Kcharge_rhoKst.aint = -1
				elif i.Piplus_ProbNNk==kaon_probnnk and kaon_probnnk*(1.-i.Piplus_ProbNNpi)>0.3:
					if i.Kplus_ProbNNpi>0.2 and i.Piminus_ProbNNpi>0.2 and i.Kminus_ProbNNpi>0.2:
						if i.Kplus_ProbNNpi*(1.-i.Kplus_ProbNNk)>0.3 and i.Piminus_ProbNNpi*(1.-i.Piminus_ProbNNk)>0.3 and i.Kminus_ProbNNpi*(1.-i.Kminus_ProbNNk)>0.3:
							pid_selected = 1
							k.SetXYZM(i.Piplus_PX,i.Piplus_PY,i.Piplus_PZ,493.667)
							pi.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,139.570)
							pi1.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,139.570)
							pi2.SetXYZM(i.Piminus_PX,i.Piminus_PY,i.Piminus_PZ,139.570)
							Kcharge_rhoKst.aint = 1

		else:
			kaon_probnnk = max(i.Kplus_V3ProbNNk_corr,i.Kminus_V3ProbNNk_corr,i.Piplus_V3ProbNNk_corr,i.Piminus_V3ProbNNk_corr)
			if kaon_probnnk>0.2:
				if i.Kplus_V3ProbNNk_corr==kaon_probnnk and kaon_probnnk*(1.-i.Kplus_V3ProbNNpi_corr)>0.3:
					if i.Piminus_V3ProbNNpi_corr>0.2 and i.Kminus_V3ProbNNpi_corr>0.2 and i.Piplus_V3ProbNNpi_corr>0.2:
						if i.Piminus_V3ProbNNpi_corr*(1.-i.Piminus_V3ProbNNk_corr)>0.3 and i.Kminus_V3ProbNNpi_corr*(1.-i.Kminus_V3ProbNNk_corr)>0.3 and i.Piplus_V3ProbNNpi_corr*(1.-i.Piplus_V3ProbNNk_corr)>0.3:
							pid_selected = 1
							k.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,493.667)
							pi.SetXYZM(i.Piminus_PX,i.Piminus_PY,i.Piminus_PZ,139.570)
							pi1.SetXYZM(i.Piplus_PX,i.Piplus_PY,i.Piplus_PZ,139.570)
							pi2.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,139.570)
							Kcharge_rhoKst.aint = 1
				elif i.Piminus_V3ProbNNk_corr==kaon_probnnk and kaon_probnnk*(1.-i.Piminus_V3ProbNNpi_corr)>0.3:
					if i.Kplus_V3ProbNNpi_corr>0.2 and i.Kminus_V3ProbNNpi_corr>0.2 and i.Piplus_V3ProbNNpi_corr>0.2:
						if i.Kplus_V3ProbNNpi_corr*(1.-i.Kplus_V3ProbNNk_corr)>0.3 and i.Kminus_V3ProbNNpi_corr*(1.-i.Kminus_V3ProbNNk_corr)>0.3 and i.Piplus_V3ProbNNpi_corr*(1.-i.Piplus_V3ProbNNk_corr)>0.3:
							pid_selected = 1
							k.SetXYZM(i.Piminus_PX,i.Piminus_PY,i.Piminus_PZ,493.667)
							pi.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,139.570)
							pi1.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,139.570)
							pi2.SetXYZM(i.Piplus_PX,i.Piplus_PY,i.Piplus_PZ,139.570)
							Kcharge_rhoKst.aint = -1
				elif i.Kminus_V3ProbNNk_corr==kaon_probnnk and kaon_probnnk*(1.-i.Kminus_V3ProbNNpi_corr)>0.3:
					if i.Kplus_V3ProbNNpi_corr>0.2 and i.Piminus_V3ProbNNpi_corr>0.2 and i.Piplus_V3ProbNNpi_corr>0.2:
						if i.Kplus_V3ProbNNpi_corr*(1.-i.Kplus_V3ProbNNk_corr)>0.3 and i.Piminus_V3ProbNNpi_corr*(1.-i.Piminus_V3ProbNNk_corr)>0.3 and i.Piplus_V3ProbNNpi_corr*(1.-i.Piplus_V3ProbNNk_corr)>0.3:
							pid_selected = 1
							k.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,493.667)
							pi.SetXYZM(i.Piplus_PX,i.Piplus_PY,i.Piplus_PZ,139.570)
							pi1.SetXYZM(i.Piminus_PX,i.Piminus_PY,i.Piminus_PZ,139.570)
							pi2.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,139.570)
							Kcharge_rhoKst.aint = -1
				elif i.Piplus_V3ProbNNk_corr==kaon_probnnk and kaon_probnnk*(1.-i.Piplus_V3ProbNNpi_corr)>0.3:
					if i.Kplus_V3ProbNNpi_corr>0.2 and i.Piminus_V3ProbNNpi_corr>0.2 and i.Kminus_V3ProbNNpi_corr>0.2:
						if i.Kplus_V3ProbNNpi_corr*(1.-i.Kplus_V3ProbNNk_corr)>0.3 and i.Piminus_V3ProbNNpi_corr*(1.-i.Piminus_V3ProbNNk_corr)>0.3 and i.Kminus_V3ProbNNpi_corr*(1.-i.Kminus_V3ProbNNk_corr)>0.3:
							pid_selected = 1
							k.SetXYZM(i.Piplus_PX,i.Piplus_PY,i.Piplus_PZ,493.667)
							pi.SetXYZM(i.Kminus_PX,i.Kminus_PY,i.Kminus_PZ,139.570)
							pi1.SetXYZM(i.Kplus_PX,i.Kplus_PY,i.Kplus_PZ,139.570)
							pi2.SetXYZM(i.Piminus_PX,i.Piminus_PY,i.Piminus_PZ,139.570)
							Kcharge_rhoKst.aint = 1

		if pid_selected:
			passpid_rhoKst.aint = 1
			Mrho_rhoKst.afloat = (pi1+pi2).M()
			MKst_rhoKst.afloat = (k+pi).M()
			MB_rhoKst.afloat = (k+pi+pi1+pi2).M()
			if abs(MB_rhoKst.afloat-5280.)<30.: is_rhoKst.aint = 1

		newBranch_passpid_rhoKst.Fill()
		newBranch_Mrho_rhoKst.Fill()
		newBranch_MKst_rhoKst.Fill()
		newBranch_MB_rhoKst.Fill()
		newBranch_Kcharge_rhoKst.Fill()
		newBranch_is_rhoKst.Fill()
	print "All events processed."

	ttout.Write()
	ftout.Close()


def AddAngles(inputfilename,inputfileextradir,inputfileextradirname,outputfilename):
	
	fcosin = TFile(NTUPLE_PATH + inputfilename + '.root')
	if inputfileextradir: tcosin = fcosin.Get(inputfileextradirname).Get('AnalysisTree')
	else: tcosin = fcosin.Get('AnalysisTree')
	fcosout = TFile(NTUPLE_PATH + outputfilename + '.root','RECREATE')
	print "Copying the original tree ..."
	tcosout = tcosin.CopyTree("pass_all")#pass_bdt && pass_pid && pass_rhokst==0 && pass_multcand")
	print "Tree copied."

	#cos1 = MyStruct()
	#newBranchcos1 = tcosout.Branch('B_s0_DTF_KST1_COSTHETA', AddressOf(cos1,'afloat'), 'B_s0_DTF_KST1_COSTHETA/F')
	#cos2 = MyStruct()
	#newBranchcos2 = tcosout.Branch('B_s0_DTF_KST2_COSTHETA', AddressOf(cos2,'afloat'), 'B_s0_DTF_KST2_COSTHETA/F')
	#phi = MyStruct()
	#newBranchphi = tcosout.Branch('B_s0_DTF_B_s0_PHI_CORR', AddressOf(phi,'afloat'), 'B_s0_DTF_B_s0_PHI/F')

	#phi_OK = MyStruct()
	#newBranchphi_OK = tcosout.Branch('B_s0_DTF_B_s0_PHI_OK', AddressOf(phi_OK,'afloat'), 'B_s0_DTF_B_s0_PHI_OK/F')

	cos1 = MyStruct()
	newBranchcos1 = tcosout.Branch('B_s0_DTF_KST1_COSTHETA', AddressOf(cos1,'afloat'), 'B_s0_DTF_KST1_COSTHETA/F')
	cos2 = MyStruct()
	newBranchcos2 = tcosout.Branch('B_s0_DTF_KST2_COSTHETA', AddressOf(cos2,'afloat'), 'B_s0_DTF_KST2_COSTHETA/F')

	phi_TRY1 = MyStruct()
	newBranchphi_TRY1 = tcosout.Branch('B_s0_DTF_B_s0_PHI_TRY1', AddressOf(phi_TRY1,'afloat'), 'B_s0_DTF_B_s0_PHI_TRY1/F')
	phi_TRY2 = MyStruct()
	newBranchphi_TRY2 = tcosout.Branch('B_s0_DTF_B_s0_PHI_TRY2', AddressOf(phi_TRY2,'afloat'), 'B_s0_DTF_B_s0_PHI_TRY2/F')
	phi_TRY3 = MyStruct()
	newBranchphi_TRY3 = tcosout.Branch('B_s0_DTF_B_s0_PHI_TRY3', AddressOf(phi_TRY3,'afloat'), 'B_s0_DTF_B_s0_PHI_TRY3/F')
	phi_TRY4 = MyStruct()
	newBranchphi_TRY4 = tcosout.Branch('B_s0_DTF_B_s0_PHI_TRY4', AddressOf(phi_TRY4,'afloat'), 'B_s0_DTF_B_s0_PHI_TRY4/F')

	mKpi1_TRUE = MyStruct()
	newBranchmKpi1_TRUE = tcosout.Branch('B_s0_DTF_KST1_TRUE_M', AddressOf(mKpi1_TRUE,'afloat'), 'B_s0_DTF_KST1_TRUE_M/F')
	mKpi2_TRUE = MyStruct()
	newBranchmKpi2_TRUE = tcosout.Branch('B_s0_DTF_KST2_TRUE_M', AddressOf(mKpi2_TRUE,'afloat'), 'B_s0_DTF_KST2_TRUE_M/F')

	cos1_TRUE = MyStruct()
	newBranchcos1_TRUE = tcosout.Branch('B_s0_DTF_KST1_TRUE_COSTHETA', AddressOf(cos1_TRUE,'afloat'), 'B_s0_DTF_KST1_TRUE_COSTHETA/F')
	cos2_TRUE = MyStruct()
	newBranchcos2_TRUE = tcosout.Branch('B_s0_DTF_KST2_TRUE_COSTHETA', AddressOf(cos2_TRUE,'afloat'), 'B_s0_DTF_KST2_TRUE_COSTHETA/F')

	phi_TRUE_TRY1 = MyStruct()
	newBranchphi_TRUE_TRY1 = tcosout.Branch('B_s0_DTF_B_s0_PHI_TRUE_TRY1', AddressOf(phi_TRUE_TRY1,'afloat'), 'B_s0_DTF_B_s0_PHI_TRUE_TRY1/F')
	phi_TRUE_TRY2 = MyStruct()
	newBranchphi_TRUE_TRY2 = tcosout.Branch('B_s0_DTF_B_s0_PHI_TRUE_TRY2', AddressOf(phi_TRUE_TRY2,'afloat'), 'B_s0_DTF_B_s0_PHI_TRUE_TRY2/F')
	phi_TRUE_TRY3 = MyStruct()
	newBranchphi_TRUE_TRY3 = tcosout.Branch('B_s0_DTF_B_s0_PHI_TRUE_TRY3', AddressOf(phi_TRUE_TRY3,'afloat'), 'B_s0_DTF_B_s0_PHI_TRUE_TRY3/F')
	phi_TRUE_TRY4 = MyStruct()
	newBranchphi_TRUE_TRY4 = tcosout.Branch('B_s0_DTF_B_s0_PHI_TRUE_TRY4', AddressOf(phi_TRUE_TRY4,'afloat'), 'B_s0_DTF_B_s0_PHI_TRUE_TRY4/F')

	kp = TLorentzVector()
	pim = TLorentzVector()
	km = TLorentzVector()
	pip = TLorentzVector()

	kp_TRUE = TLorentzVector()
	pim_TRUE = TLorentzVector()
	km_TRUE = TLorentzVector()
	pip_TRUE = TLorentzVector()

	def corrrange(x):
		if x<0: return x + 2.*pi
		elif x>2.*pi: return x - 2.*pi
		else: return x

	print "Processing events ..."
	for i in tcosout:

		kp.SetXYZM(eval('i.'+KpPx_name),eval('i.'+KpPy_name),eval('i.'+KpPz_name),493.667)
		pim.SetXYZM(eval('i.'+PimPx_name),eval('i.'+PimPy_name),eval('i.'+PimPz_name),139.570)
		km.SetXYZM(eval('i.'+KmPx_name),eval('i.'+KmPy_name),eval('i.'+KmPz_name),493.667)
		pip.SetXYZM(eval('i.'+PipPx_name),eval('i.'+PipPy_name),eval('i.'+PipPz_name),139.570)

		kp_TRUE.SetXYZM(eval('i.'+KpPx_TRUE_name),eval('i.'+KpPy_TRUE_name),eval('i.'+KpPz_TRUE_name),493.667)
		pim_TRUE.SetXYZM(eval('i.'+PimPx_TRUE_name),eval('i.'+PimPy_TRUE_name),eval('i.'+PimPz_TRUE_name),139.570)
		km_TRUE.SetXYZM(eval('i.'+KmPx_TRUE_name),eval('i.'+KmPy_TRUE_name),eval('i.'+KmPz_TRUE_name),493.667)
		pip_TRUE.SetXYZM(eval('i.'+PipPx_TRUE_name),eval('i.'+PipPy_TRUE_name),eval('i.'+PipPz_TRUE_name),139.570)

		if i.itype<0:
			angles_TRUE = get_Angles(kp_TRUE,pim_TRUE,km_TRUE,pip_TRUE)
			cos1_TRUE.afloat = angles_TRUE[0]
			cos2_TRUE.afloat = angles_TRUE[1]
			mKpi1_TRUE.afloat = (kp_TRUE+pim_TRUE).M()
			mKpi2_TRUE.afloat = (km_TRUE+pip_TRUE).M()
			phi_TRUE_TRY1.afloat = corrrange(angles_TRUE[2])
			phi_TRUE_TRY2.afloat = corrrange(-angles_TRUE[2])
			phi_TRUE_TRY3.afloat = corrrange(angles_TRUE[2] + pi)
			phi_TRUE_TRY4.afloat = corrrange(-angles_TRUE[2] + pi)
		else:
			cos1_TRUE.afloat = -10
			cos2_TRUE.afloat = -10
			mKpi1_TRUE.afloat = -10
			mKpi2_TRUE.afloat = -10
			phi_TRUE_TRY1.afloat = -10
			phi_TRUE_TRY2.afloat = -10
			phi_TRUE_TRY3.afloat = -10
			phi_TRUE_TRY4.afloat = -10

		angles = get_Angles(kp,pim,km,pip)
		cos1.afloat = angles[0]
		cos2.afloat = angles[1]
		phi_TRY1.afloat = corrrange(angles[2])
		phi_TRY2.afloat = corrrange(-angles[2])
		phi_TRY3.afloat = corrrange(angles[2] + pi)
		phi_TRY4.afloat = corrrange(-angles[2] + pi)

		newBranchcos1.Fill()
		newBranchcos2.Fill()
		newBranchphi_TRY1.Fill()
		newBranchphi_TRY2.Fill()
		newBranchphi_TRY3.Fill()
		newBranchphi_TRY4.Fill()

		newBranchmKpi1_TRUE.Fill()
		newBranchmKpi2_TRUE.Fill()
		newBranchcos1_TRUE.Fill()
		newBranchcos2_TRUE.Fill()
		newBranchphi_TRUE_TRY1.Fill()
		newBranchphi_TRUE_TRY2.Fill()
		newBranchphi_TRUE_TRY3.Fill()
		newBranchphi_TRUE_TRY4.Fill()

	print "All events processed."

	tcosout.Write()
	fcosout.Close()


def ApplyPSmearing(inputfilename):
	
	fin = TFile(NTUPLE_PATH + inputfilename + '.root')
	tinn = fin.Get('AnalysisTree')
	fout = TFile(NTUPLE_PATH + inputfilename + '_wSmearing.root','RECREATE')
	print "Copying the original tree ..."
	tout = tinn.CopyTree("")
	print "Tree copied."

	trecowsmear = MyStruct()
	newBranchtrecowsmear = tout.Branch('B_s0_DTF_TAU_WSMEAR', AddressOf(trecowsmear,'afloat'), 'B_s0_DTF_TAU_WSMEAR/F')

	kp = TLorentzVector()
	pim = TLorentzVector()
	km = TLorentzVector()
	pip = TLorentzVector()
	kp_smear = TLorentzVector()
	pim_smear = TLorentzVector()
	km_smear = TLorentzVector()
	pip_smear = TLorentzVector()

	ran = TRandom()

	print "Processing events ..."
	for i in tout:

		kp.SetXYZM(eval('i.'+KpPx_name),eval('i.'+KpPy_name),eval('i.'+KpPz_name),493.667)
		pim.SetXYZM(eval('i.'+PimPx_name),eval('i.'+PimPy_name),eval('i.'+PimPz_name),139.570)
		km.SetXYZM(eval('i.'+KmPx_name),eval('i.'+KmPy_name),eval('i.'+KmPz_name),493.667)
		pip.SetXYZM(eval('i.'+PipPx_name),eval('i.'+PipPy_name),eval('i.'+PipPz_name),139.570)

		p1 = kp.P()
		p2 = pim.P()
		p3 = km.P()
		p4 = pip.P()

		f1 = (p1+ran.Gaus(0,1)*deltap(p1))/p1
		f2 = (p2+ran.Gaus(0,1)*deltap(p2))/p2
		f3 = (p3+ran.Gaus(0,1)*deltap(p3))/p3
		f4 = (p4+ran.Gaus(0,1)*deltap(p4))/p4

		kp_smear.SetXYZM(f1*eval('i.'+KpPx_name),f1*eval('i.'+KpPy_name),f1*eval('i.'+KpPz_name),493.667)
		pim_smear.SetXYZM(f2*eval('i.'+PimPx_name),f2*eval('i.'+PimPy_name),f2*eval('i.'+PimPz_name),139.570)
		km_smear.SetXYZM(f3*eval('i.'+KmPx_name),f3*eval('i.'+KmPy_name),f3*eval('i.'+KmPz_name),493.667)
		pip_smear.SetXYZM(f4*eval('i.'+PipPx_name),f4*eval('i.'+PipPy_name),f4*eval('i.'+PipPz_name),139.570)

		pcomb = kp+pim+km+pip
		pcomb_smear = kp_smear+pim_smear+km_smear+pip_smear

		trecowsmear.afloat = i.B_s0_DTF_TAU*pcomb.P()/pcomb_smear.P()*pcomb_smear.M()/pcomb.M()
		newBranchtrecowsmear.Fill()

	print "All events processed."

	tout.Write()
	fout.Close()


def ApplyCuts(inputfilename,outputfilename):

	fselin = TFile(NTUPLE_PATH+inputfilename+'.root')
	tselin = fselin.Get('DecayTree')
	fselout = TFile(NTUPLE_PATH+outputfilename+'.root','RECREATE')

	# Cuts in the granddaughters.
	cuts_tracks_pt = "Piplus_PT>500 && Kminus_PT>500 && Piminus_PT>500 && Kplus_PT>500"
	cuts_tracks_chi2 = "&& Piplus_IPCHI2_OWNPV>36. && Kminus_IPCHI2_OWNPV>36. && Piminus_IPCHI2_OWNPV>36. && Kplus_IPCHI2_OWNPV>36."
	cuts_PID = "&& !Piplus_isMuon && !Piminus_isMuon && !Kplus_isMuon && !Kminus_isMuon && Kplus_ProbNNp<0.6 && Kminus_ProbNNp<0.6 && Piplus_ProbNNpi>0.2 && Piminus_ProbNNpi>0.2 && Kplus_ProbNNk>0.2 && Kminus_ProbNNk>0.2"
	cuts_trchi2dof = "&& Piplus_TRACK_CHI2NDOF<5 && Kminus_TRACK_CHI2NDOF<5 && Piminus_TRACK_CHI2NDOF<5 && Kplus_TRACK_CHI2NDOF<5"
	cuts_GD = cuts_tracks_pt + cuts_tracks_chi2 + cuts_PID + cuts_trchi2dof

	# Cuts in the daughters.
	cuts_Ks_pt = "&& Kstb_PT>900. && Kst_PT>900."
	cuts_Ks_mass = "&& Kst_M>750. && Kst_M<1700. && Kstb_M>750. && Kstb_M<1700."
	cuts_Ks_Vchi2ndof = "&& Kstb_ENDVERTEX_CHI2<9. && Kst_ENDVERTEX_CHI2<9."
	cuts_Ks_DIRA = "&& Kstb_DIRA_OWNPV>0. && Kst_DIRA_OWNPV>0."
	cuts_D = cuts_Ks_pt + cuts_Ks_mass + cuts_Ks_Vchi2ndof + cuts_Ks_DIRA

	# Variable range cuts.
	cuts_range = "&& abs(B_s0_MM-5365)<=450. && B_s0_TAU>=0. && B_s0_TAU*1000.<=12."

	# All cuts.
	cuts = cuts_GD + cuts_D + cuts_range

	print 'Selecting events ...'
	tselout = tselin.CopyTree(cuts)
	print 'Events selected.'
	tselout.Write()
	fselout.Close()

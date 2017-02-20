## A module containing variable containers which are reused in various scripts.
from numpy import zeros as z

# First the dalitz variables.
M_SSKpi = z(1, dtype=float)
M_OSKpi = z(1, dtype=float)
M_KK    = z(1, dtype=float)
M_Ds    = z(1, dtype=float)
resFlag = z(1, dtype=int)

Beta_OSK  = z(1, dtype=float)
Beta_SSK  = z(1, dtype=float)
Beta_pi   = z(1, dtype=float)

WM_Lc_SSKasproton = z(1, dtype=float)
WM_Dp_SSKaspi     = z(1, dtype=float)

WM_Dst_FullReco         = z(1, dtype=float)
WM_Dst_SSKaspi_fromDz   = z(1, dtype=float)
WM_Dst_OSKaspi_fromDz   = z(1, dtype=float)
WM_Dst_SSKaspi_fromDst  = z(1, dtype=float)
WM_Dst_OSKaspi_fromDst  = z(1, dtype=float)

WM_Jpsi_piasmu  = z(1, dtype=float)
WM_Jpsi_SSKasmu = z(1, dtype=float)
WM_Jpsi_OSKasmu = z(1, dtype=float)

WM_Kstar_SSKaspi  = z(1, dtype=float)
WM_Kstar_OSKaspi  = z(1, dtype=float)

WM_phi_piasK    = z(1, dtype=float)
WM_KS_OSKaspi   = z(1, dtype=float)

# Kinematics
SSK_Px = z(1, dtype=float)
SSK_Py = z(1, dtype=float)
SSK_Pz = z(1, dtype=float)
SSK_Pe = z(1, dtype=float)
SSK_P  = z(1, dtype=float)

OSK_Px = z(1, dtype=float)
OSK_Py = z(1, dtype=float)
OSK_Pz = z(1, dtype=float)
OSK_Pe = z(1, dtype=float)
OSK_P  = z(1, dtype=float)

pi_Px = z(1, dtype=float)
pi_Py = z(1, dtype=float)
pi_Pz = z(1, dtype=float)
pi_Pe = z(1, dtype=float)
pi_P  = z(1, dtype=float)

pi_isMuon = z(1, dtype=int)
OSK_isMuon = z(1, dtype=int)
SSK_isMuon = z(1, dtype=int)

mu_Px = z(1, dtype=float)
mu_Py = z(1, dtype=float)
mu_Pz = z(1, dtype=float)
mu_Pe = z(1, dtype=float)
mu_P  = z(1, dtype=float)

Ds_M = z(1, dtype=float)

OSK_PIDK = z(1, dtype=float)
OSK_PIDp = z(1, dtype=float)
SSK_PIDK = z(1, dtype=float)
SSK_PIDp = z(1, dtype=float)
pi_PIDK = z(1, dtype=float)
pi_PIDp = z(1, dtype=float)

OSK_ProbNNK = z(1, dtype=float)
OSK_ProbNNp = z(1, dtype=float)
SSK_ProbNNK = z(1, dtype=float)
SSK_ProbNNp = z(1, dtype=float)
pi_ProbNNK  = z(1, dtype=float)

OSK_IPChi2 = z(1, dtype=float)
SSK_IPChi2 = z(1, dtype=float)
pi_IPChi2 = z(1, dtype=float)

# Kinematics for the COM vars.
mB  = z(1, dtype=float)
pzB = z(1, dtype=float)
PVx = z(1, dtype=float)
PVy = z(1, dtype=float)
PVz = z(1, dtype=float)
BVx = z(1, dtype=float)
BVy = z(1, dtype=float)
BVz = z(1, dtype=float)
muPx = z(1, dtype=float)
muPy = z(1, dtype=float)
muPz = z(1, dtype=float)
muPe = z(1, dtype=float)
DPx = z(1, dtype=float)
DPy = z(1, dtype=float)
DPz = z(1, dtype=float)
DPe = z(1, dtype=float)
q2   = z(1, dtype=float)
Emu  = z(1, dtype=float)
MM2  = z(1, dtype=float)

pxBT = z(1, dtype=float)
pyBT = z(1, dtype=float)
pzBT = z(1, dtype=float)
peBT = z(1, dtype=float)
muPxT = z(1, dtype=float)
muPyT = z(1, dtype=float)
muPzT = z(1, dtype=float)
muPeT = z(1, dtype=float)
DPxT = z(1, dtype=float)
DPyT = z(1, dtype=float)
DPzT = z(1, dtype=float)
DPeT = z(1, dtype=float)
q2True   = z(1, dtype=float)
EmuTrue  = z(1, dtype=float)
MM2True  = z(1, dtype=float)

# Neutral vars for gamma
MassDsG1_0_40 = z(1, dtype=float)
MassDsG2_0_40 = z(1, dtype=float)
MassDsG3_0_40 = z(1, dtype=float)

Ds_0_40_nc_maxPt_PE = z(1, dtype=float)
Ds_0_40_nc_maxPt_PX = z(1, dtype=float)
Ds_0_40_nc_maxPt_PY = z(1, dtype=float)
Ds_0_40_nc_maxPt_PZ = z(1, dtype=float)

Ds_0_40_nc_secPt_PE = z(1, dtype=float)
Ds_0_40_nc_secPt_PX = z(1, dtype=float)
Ds_0_40_nc_secPt_PY = z(1, dtype=float)
Ds_0_40_nc_secPt_PZ = z(1, dtype=float)

Ds_0_40_nc_thiPt_PE = z(1, dtype=float)
Ds_0_40_nc_thiPt_PX = z(1, dtype=float)
Ds_0_40_nc_thiPt_PY = z(1, dtype=float)
Ds_0_40_nc_thiPt_PZ = z(1, dtype=float)

isGamma1InCone = z(1, dtype=int)
isGamma2InCone = z(1, dtype=int)
isGamma3InCone = z(1, dtype=int)

# Neutral vars for pi0
MassDsPi01_0_40 = z(1, dtype=float)
MassDsPi02_0_40 = z(1, dtype=float)
MassDsPi03_0_40 = z(1, dtype=float)

Ds_0_40_pi0_maxPt_PE = z(1, dtype=float)
Ds_0_40_pi0_maxPt_PX = z(1, dtype=float)
Ds_0_40_pi0_maxPt_PY = z(1, dtype=float)
Ds_0_40_pi0_maxPt_PZ = z(1, dtype=float)

Ds_0_40_pi0_secPt_PE = z(1, dtype=float)
Ds_0_40_pi0_secPt_PX = z(1, dtype=float)
Ds_0_40_pi0_secPt_PY = z(1, dtype=float)
Ds_0_40_pi0_secPt_PZ = z(1, dtype=float)

Ds_0_40_pi0_thiPt_PE = z(1, dtype=float)
Ds_0_40_pi0_thiPt_PX = z(1, dtype=float)
Ds_0_40_pi0_thiPt_PY = z(1, dtype=float)
Ds_0_40_pi0_thiPt_PZ = z(1, dtype=float)

isPi01InCone = z(1, dtype=int)
isPi02InCone = z(1, dtype=int)
isPi03InCone = z(1, dtype=int)

# Neutral vars for pi0 + gamma.
MassDsPi0G1_0_40 = z(1, dtype=float)
MassDsPi0G2_0_40 = z(1, dtype=float)
MassDsPi0G3_0_40 = z(1, dtype=float)

# Vars for the trigger.
triggerTag = z(1, dtype=int)
Kpl_P = z(1, dtype=float)
Kmi_P = z(1, dtype=float)
pi_P  = z(1, dtype=float)
Kpl_PT= z(1, dtype=float)
Kmi_PT= z(1, dtype=float)
pi_PT= z(1, dtype=float)
Ds_PT= z(1, dtype=float)
Bs_0_BDTS_DOCA= z(1, dtype=float)
Bs_0_FDCHI2_TOPPV= z(1, dtype=float)
Ds_MM= z(1, dtype=float)

# Stuff for sWeights
N_LsigR_sw = z(1, dtype=float)
L_N_LsigR  = z(1, dtype=float)
N_LbkgR_sw = z(1, dtype=float)
L_N_LbkgR  = z(1, dtype=float)

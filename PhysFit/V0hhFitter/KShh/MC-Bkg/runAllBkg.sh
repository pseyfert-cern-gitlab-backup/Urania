#!/bin/bash -l

#sels=('Loose' 'Tight' 'DP1' 'DP2')
sels=('DP1')
Modes=('Bd2etapKS02pipigamma_pipi' 'Bd2pipiKS0gamma_pipi' 'Bd2Kst0rho02KS0pi0pipi_pipi' 'Bu2D0pi2KS0pipi_pipi' 'Bs2KstKst2KS0piKpi0_Kpi' 'Bu2D0K2KS0pipi_Kpi' 'Bd2Kst0phi2KS0pi0KK_KK' 'Bd2etacKS2KKpi0_KK' 'Bu2Kstphi2KS0piKK_KK')

. SetupProject.sh Urania v2r4

for sel in "${sels[@]}"
do
   rm -f ../WS/MC-Bkg-WS-${sel}.root
   for mode in "${Modes[@]}"
   do 
      ../../x86_64-slc6-gcc48-opt/B2KShh-MC-fitter-PartiallyBkg-boost.exe -m $mode -b $sel
   done
done

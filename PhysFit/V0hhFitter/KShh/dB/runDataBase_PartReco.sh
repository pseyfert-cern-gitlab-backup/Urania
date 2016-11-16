#!/bin/bash -l

. SetupProject.sh Urania v2r4

#Modes=('Bd2etapKS02pipigamma' 'Bd2pipiKS0gamma' 'Bd2Kst0rho02KS0pi0pipi' 'Bu2D0pi2KS0pipi' 'Bs2KstKst2KS0piKpi0' 'Bu2D0K2KS0pipi' 'Bd2Kst0phi2KS0pi0KK' 'Bd2etacKS2KKpi0')
Modes=('Charmless-Bd' 'Charmless-Bs' 'Charmed-Bd' 'Charmed-Bs' 'Charmonia-Bd' 'Charmonia-Bs' 'MissGamNR-Bd' 'MissGamNR-Bs' 'MissGamRes-Bd' 'MissGamRes-Bs')
#Modes=('Charmless-Bd')
#Modes=('Bd2Kst0rho02KS0pi0pipi')
Years=('2011' '2012a' '2012b')
#Years=('2011')
ksTypes=('DD' 'LL')
selSteps=('Loose' 'Tight' 'DP1' 'DP2')
#selSteps=('Loose')
treeNames=('pipi' 'Kpi' 'piK' 'KK')

Counter=1
BF=$1
echo $BF
../../x86_64-slc6-gcc48-opt/createStructure_PartReco.exe $BF
for mode in "${Modes[@]}"
do
    for year in "${Years[@]}"
    do
	for sel in "${selSteps[@]}"
	do
            for ks in "${ksTypes[@]}"
            do
		for tree in "${treeNames[@]}"
		do
#			echo "FAILED"
#			exit 1;
#		    fi
		    ../../x86_64-slc6-gcc48-opt/createDataBase_PartReco.exe $Counter $sel $mode $tree $ks $year $BF
		    if [ $? -ne 0 ]
		    then
				exit
		    fi
		    let Counter=Counter+1 
		done
            done
	done
    done
done

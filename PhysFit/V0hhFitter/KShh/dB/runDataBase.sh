#!/bin/bash -l
. SetupProject.sh Urania v2r4

Modes=('Bd2KSpipi' 'Bs2KSpipi' 'Bd2KSKpi' 'Bd2KSpiK' 'Bs2KSKpi' 'Bs2KSpiK' 'Bd2KSKK' 'Bs2KSKK')
#Modes=('Bs2KSKpi' 'Bd2KSKK')
Years=('2011' '2012a' '2012b')
ksTypes=('DD' 'LL')
#Years=('2011')
#ksTypes=('DD')
selSteps=('Loose' 'Tight' 'DP1' 'DP2')
#selSteps=('Loose')
treeNames=('pipi' 'Kpi' 'piK' 'KK')

Counter=1
if [ $# -eq 1 ]
then
	../../x86_64-slc6-gcc48-opt/createStructure.exe PIDcrit
else
	../../x86_64-slc6-gcc48-opt/createStructure.exe
fi

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
			echo Signal $sel $mode $ks $year
		    if  [[ $mode = "Bd2KSpipi" && $tree = "pipi" ]] || \
				[[ $mode = "Bs2KSpipi" && $tree = "pipi" ]] || \
				[[ $mode = "Bd2KSKpi" && $tree = "Kpi" ]]   || \
				[[ $mode = "Bd2KSpiK" && $tree = "piK" ]]   || \
				[[ $mode = "Bs2KSKpi" && $tree = "Kpi" ]]   || \
				[[ $mode = "Bs2KSpiK" && $tree = "piK" ]]   || \
				[[ $mode = "Bd2KSKK" && $tree = "KK" ]]     || \
				[[ $mode = "Bs2KSKK" && $tree = "KK" ]]
		    then
				if [ "$#" -eq 1 ]
				then
					../../x86_64-slc6-gcc48-opt/createDataBase.exe $Counter Signal $sel $mode $ks $year PIDcrit
				else
					../../x86_64-slc6-gcc48-opt/createDataBase.exe $Counter Signal $sel $mode $ks $year
				fi
			else
				if [ "$#" -eq 1 ]
				then
					../../x86_64-slc6-gcc48-opt/createDataBase.exe $Counter CrossFeed $sel $mode $ks $year $tree PIDcrit
				else
					../../x86_64-slc6-gcc48-opt/createDataBase.exe $Counter CrossFeed $sel $mode $ks $year $tree
				fi
		    fi
		    let Counter=Counter+1 
		done
            done
	done
    done
done

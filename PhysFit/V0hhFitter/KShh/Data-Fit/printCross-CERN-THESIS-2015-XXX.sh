#!/bin/bash

Modes=("Bd2KSpipi_as_Kpi" "Bd2KSpipi_as_piK" "Bd2KSKK_as_Kpi" "Bd2KSKK_as_piK" "Bs2KSKpi_as_pipi" "Bs2KSKpi_as_KK")
Years=("2011" "2012a" "2012b")
KSTypes=("DD" "LL")

for mode in "${Modes[@]}"
do
   for ks in "${KSTypes[@]}"
   do
      Values=""
      for year in "${Years[@]}"
      do
	    Val=`grep "frac_cross_${mode}${ks}_${year}" logNewResults.log  | rev | cut -d" " -f6 | rev`
	    Error=`grep "frac_cross_${mode}${ks}_${year}" logNewResults.log  | rev | cut -d" " -f3 | rev`
	    line=" \$$Val \\pm $Error\$ "
	    echo $mode $ks $year
	    echo $line
      done
      echo 
   done
   echo
   echo "----"
   echo 
done


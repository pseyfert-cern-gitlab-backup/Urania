#!/bin/bash

Modes=("KSpipi" "KSKK" "KSKpi" "KSpiK")
Years=("2011" "2012a" "2012b")
KSTypes=("DD" "LL")
Parameters=("Bd2" "Bs2" "combinatoric_")

for mode in "${Modes[@]}"
do
   for ks in "${KSTypes[@]}"
   do
      for year in "${Years[@]}"
      do
         Values=""
	 for par in "${Parameters[@]}"
	 do
	    Val=`grep "${par}${mode}${ks}_${year}_pdf_${mode}${ks}_${year}_Yield" logNewResults.log  | rev | cut -d" " -f6 | rev`
	    Error=`grep "${par}${mode}${ks}_${year}_pdf_${mode}${ks}_${year}_Yield" logNewResults.log  | rev | cut -d" " -f3 | rev`
	    line=" \$$Val \\pm $Error\$ "
	    Values+=$line
	    Values+="&"
	    #echo "$mode $ks $year $par: $Val \\pm $Error\$"
	 done
	 echo $mode $ks $year
	 echo $Values
	 echo
      done
      echo
      echo "-------"
      echo
   done
done

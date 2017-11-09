#!/bin/bash

#Prevent core dump
ulimit -c 0

#Get options
export seed=$1
export stop=$2
export eosoutput=$3
export nickname=$4
export config=$5
export pyscriptpath=$6
export runpath=$7

while (( $seed < $stop )); do
    
    cd $pyscriptpath

    ${runpath}run python ${pyscriptpath}toyFactory.py --HFAG --configName $config --seed $seed --workfileOut GenToyWorkspace_${nickname}_${seed}.root --treefileOut GenToyTree_${nickname}_${seed}.root  --debug --outputdir $eosoutput #>& ${eosoutput}log_${nickname}_${seed}.txt

    seed=$(($seed + 1))

done

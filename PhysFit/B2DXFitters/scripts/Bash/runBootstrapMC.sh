#!/bin/bash

#Prevent core dump
ulimit -c 0

#Get options
export seed=$1
export stop=$2
export runpath=$3
export inputfile=$4
export inputworkspace=$5
export output=$6
export eosoutput=$7
export nickname=$8
export config=$9
export pyscriptpath=${10}
export maxcand=${11}

export preselection="TagDecOS!=0"

while (( $seed < $stop )); do

    cd $pyscriptpath

    #Run script
    ${runpath}run python ${pyscriptpath}BootstrapMC.py -d --cheatTagging --seed $seed --preselection $preselection --configName $config --inputFile $inputfile --inputWorkspace $inputworkspace --outputFile ${output}BootstrapMC_${nickname}_${seed}.root --outputWorkspace workspace --merge both --decay Bd2DPi --mode kpipi --year run1 --hypo Bd2DPi --maxcand $maxcand >& ${output}log_${nickname}_${seed}.txt  

    #Dump to EOS
    xrdcp -f ${output}BootstrapMC_${nickname}_${seed}.root root://eoslhcb.cern.ch/${eosoutput}BootstrapMC_${nickname}_${seed}.root
    rm -f ${output}BootstrapMC_${nickname}_${seed}.root

    xrdcp -f ${output}log_${nickname}_${seed}.txt root://eoslhcb.cern.ch/${eosoutput}log_${nickname}_${seed}.txt
    
    seed=$(($seed + 1))

done
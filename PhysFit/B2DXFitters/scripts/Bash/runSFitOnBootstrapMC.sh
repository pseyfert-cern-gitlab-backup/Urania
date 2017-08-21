#!/bin/bash

#Prevent core dump
ulimit -c 0

#Get options
export seed=$1
export stop=$2
export input=$3
export output=$4
export eosoutput=$5
export nickname=$6
export timefitdescr=$7
export config=$8
export pol=$9
export mode=${10}
export year=${11}
export hypo=${12}
export workspace=${13}
export dataset=${14}
export pyscriptpath=${15}
export runpath=${16}

export Start=`date`
echo "==> Start fitting at ${Start}"

export preselection="TagDecOS!=0"

while (( $seed < $stop )); do 
    
    cd $pyscriptpath

    ${runpath}run python ${pyscriptpath}runSFit_Bd.py --preselection $preselection --pereventmistag --HFAG --sampleConstr --MC --inputdata $dataset --workMC $workspace --debug --fileName ${input}BootstrapMC_${nickname}_${seed}.root --save ${output}TimeFitBootstrapResult_${nickname}_${timefitdescr}_${seed}.root --fileNamePull ${output}PullTreeTimeFit_${nickname}_${timefitdescr}_${seed}.root --outputdir $output --configName $config --pol $pol --mode $mode --year $year --hypo $hypo --merge both --noweight --seed $seed >& ${output}log_${nickname}_${timefitdescr}_${seed}.txt

    xrdcp -f ${output}TimeFitBootstrapResult_${nickname}_${timefitdescr}_${seed}.root root://eoslhcb.cern.ch/${eosoutput}TimeFitBootstrapResult_${nickname}_${timefitdescr}_${seed}.root
    rm -f ${output}TimeFitBootstrapResult_${nickname}_${timefitdescr}_${seed}.root

    xrdcp -f ${output}PullTreeTimeFit_${nickname}_${timefitdescr}_${seed}.root root://eoslhcb.cern.ch/${eosoutput}PullTreeTimeFit_${nickname}_${timefitdescr}_${seed}.root
    rm -f ${output}PullTreeTimeFit_${nickname}_${timefitdescr}_${seed}.root

    xrdcp -f ${output}log_${nickname}_${timefitdescr}_${seed}.txt root://eoslhcb.cern.ch/${eosoutput}log_${nickname}_${timefitdescr}_${seed}.txt

    seed=$(($seed + 1))

done

export Stop=`date`
echo "==> Stop fitting at ${Stop}"
#!/bin/bash

# @title Batch_runSFitOnBootstrapMC.sh
#
# @author Vincenzo Battista
# @date 28/02/2017
#
# @brief Run sFit in parallel on boostrapped MC samples
#        using the LSF CERN batch system
#        on lxplus machines
#
#        Example: 1000 samples with seeds from 1000 to 2000,
#        10 toys per job
#        ./Batch_runSFitOnBootstrapMC.sh 1000 1010 2000

#---Setup toy info
#Job name
export jobname="Bd2DPiBootstrapSFit"
#Starting toy
export start=$1
#Stop toy for the first node (if stop=start+1, one toy per node is made)
export stop=$2
#Final toy seed
export fullstop=$3
#Batch candidate queues
export queue="2nd"
#Memory limit (kB)
export mlimit="80000"
#Nickname for the current configuration
#Choose a meaningful name (e.g. SgnAndBkgMeanResSplineAcc2TaggersNoAsymm etc...)
export nickname="Bd2DPiMCFilteredS21RunIBothOSTaggedOnlyShortTime"
#Tag to describe time fit configuration
#Choose a meaningful name (e.g. SSbarFloating etc...) 
export timefitdescr="SSbarAccAsymmFloatDMGammaFTConstrOSTaggedOnlyRLOGITResampleFixParsbroadTrigBDTAUWeight"
#Name of workspace
export workspace="workspace"
#Name of dataset
export dataset="combData"
#Bachelor mass hypothesys
export hypo="Bd2DPi"
#D decay mode
export mode="kpipi"
#Year
export year="run1"
#Magnet polarity
export pol="both"
#Configuration file
export config="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForSFitOnBootstrapMC.py"
#Pathname of fitted toys
export input="root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MCBootstrap/${nickname}/Generator/" 
#Pathname to dump results
export output="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/MCBootstrap/${nickname}/TimeFit/${timefitdescr}/"
export eosoutput="/eos/lhcb/wg/b2oc/TD_DPi_3fb/MCBootstrap/${nickname}/TimeFit/${timefitdescr}/"
#Path where scripts are located
export bashscriptpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/scripts/Bash/"
export pyscriptpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/scripts/"
export runpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/"

#Clear directories
rm -rf $output
mkdir -p $output

/usr/bin/eos rm -r ${eosoutput}
/usr/bin/eos mkdir -p ${eosoutput}

cd $pyscriptpath

job=1
seed=$start
export step=$(($stop - $start))

echo ""
echo "################################"
echo "Submitting jobs from ${start} to ${fullstop}"
echo "in steps of ${step}"
echo "################################"
echo ""

while (( $stop <= $fullstop )); do

    echo "...submitting job ${job} with starting seed ${seed}"

    #Submit job
    bsub -q $queue -M $mlimit -e ${output}ERROR -o ${output}OUTPUT -n 8,32 -R "span[hosts=-1]" -J ${jobname}_${job} source ${bashscriptpath}runSFitOnBootstrapMC.sh $seed $stop $input $output $eosoutput $nickname $timefitdescr $config $pol $mode $year $hypo $workspace $dataset $pyscriptpath $runpath

    #source ${bashscriptpath}runSFitOnBootstrapMC.sh $seed $stop $input $output $eosoutput $nickname $timefitdescr $config $pol $mode $year $hypo $workspace $dataset $pyscriptpath $runpath

    #Sleep to avoid afs overload (not sure this is the best trick)
    if [[ "$(($job % 100))" -eq 0 ]]; then
        echo "Sleeping..."
        sleep 30
    fi

    #Increase counters
    job=$(($job + 1))
    stop=$(($stop + $step))
    seed=$(($seed + $step))

done

#List submitted jobs
bjobs
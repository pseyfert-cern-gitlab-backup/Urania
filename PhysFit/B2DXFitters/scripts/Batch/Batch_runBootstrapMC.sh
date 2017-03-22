#!/bin/bash

# @title Batch_runBootstrapMC.sh
#
# @author Vincenzo Battista
# @date 13/02/2017 
#
# @brief Run MC bootstrapping (aka resampling)
#        using the LSF CERN batch system
#        on lxplus machines
#
#        Example: 1000 samples with seeds from 1000 to 2000,
#        10 toys per job:
#        ./Batch_runBootstrapMC.sh 1000 1010 2000 

#---Setup toy info
#Job name
export jobname="Bd2DPiMCBootstrap"
#Starting toy seed
export start=$1
#Stop toy seed for first job (if stop=start+1, one toy per job is made)
export stop=$2
#Final toy seed
export fullstop=$3
#Batch queue
export queue="1nh"
#Memory limit (kB)
export mlimit="500000"
#Nickname
#Choose a meaningful name
export nickname="Bd2DPiMCFilteredS21RunIBothTaggedOnlyShortTimeNoProdDetCPAsymmAfter"
#Configuration file
export config="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForBootstrapMC.py"
#Input file
export inputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/work_dpi_mc_large_shorttime.root"
#Input workspace
export inputworkspace="workspace"
#Temporary pathname to dump results
export output="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/MCBootstrap/${nickname}/Generator/"
#Pathname to dump outputfiles (eos recommendend)
export eosoutput="/eos/lhcb/wg/b2oc/TD_DPi_3fb/MCBootstrap/${nickname}/Generator/"
#Number of candidates to store in the tuple
export maxcand="600000"
#Path where scripts are located
export bashscriptpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/scripts/Bash/"
export pyscriptpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/scripts/"
export runpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/"

#Clear directories
rm -rf $output
mkdir -p $output

/afs/cern.ch/project/eos/installation/lhcb/bin/eos.select rm -r ${eosoutput}
/afs/cern.ch/project/eos/installation/lhcb/bin/eos.select mkdir -p ${eosoutput}

cd $pyscriptpath

job=1
seed=$start
export step=$(($stop - $start))

echo ""
echo "################################"
echo "Submitting MC resampling jobs" 
echo "from ${start} to ${fullstop}"
echo "in steps of ${step}"
echo "################################"
echo ""

while (( $stop <= $fullstop )); do
    
    echo "...submitting job ${job} with starting seed ${seed}"

    #Submit jobs
    #bsub -q $queue -M $mlimit -e ${output}ERROR -o ${output}OUTPUT -n 1,2 -R "span[hosts=-1]" -J ${jobname}_${seed} source ${bashscriptpath}runBootstrapMC.sh $seed $stop $runpath $inputfile $inputworkspace $output $eosoutput $nickname $config $pyscriptpath $maxcand

    source ${bashscriptpath}runBootstrapMC.sh $seed $stop $runpath $inputfile $inputworkspace $output $eosoutput $nickname $config $pyscriptpath $maxcand

    #Sleep to avoid afs overload and buffer space consumption (not sure this is the best trick)
    if [[ "$(($job % 100))" -eq 0 ]]; then
        echo "Sleeping..."
        sleep 30
    fi

    #Increase counters
    job=$(($job + 1))
    seed=$(($seed + $step))
    stop=$(($stop + $step))

done

#List submitted jobs
bjobs
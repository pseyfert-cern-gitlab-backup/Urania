#!/bin/bash

#Prevent core dump
ulimit -c 0

export rundir="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/"

#Options
export nickname="SSbarAccAsymmFloatingDMGammaConstrTaggedOnlyBlinded_Nov2016"
#export inputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sWeights/Nominal/sWeights_RunIdata_OSCombined.root"
export inputfile="/eos/lhcb/wg/b2oc/TD_DPi_3fb/sWeightedData_Bd/sWeights_AllData_OScombined_splinePreCalib_Nov2016.root"
export outputdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/${nickname}/"
export outputfile=${outputdir}"workResults.root"
#export config="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForSFitOnData.py"
export config="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForSFitOnData_Nov2016.py"
export pol="both"
export mode="kpipi"
export year="run1"
export hypo="Bd2DPi"
export pyscriptpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/scripts/"

rm -rf $outputdir
mkdir -p $outputdir

export Start=`date`
echo "==> Start fitting at ${Start}"
${rundir}run python ${pyscriptpath}runSFit_Bd.py --debug --pereventmistag --fileName $inputfile --save $outputfile --configName $config --pol $pol --mode $mode --year $year --hypo $hypo --merge both --UniformBlinding --NCPU 8 --HFAG --fiexport Stop=`date`
echo "==> Stop fitting at ${Stop}"xtagging --preselection "TagDecOS!=0||TagDecSS!=0" | tee ${outputdir}logfile.txt

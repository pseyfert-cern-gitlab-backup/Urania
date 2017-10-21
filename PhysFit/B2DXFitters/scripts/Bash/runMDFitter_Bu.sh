#!/bin/bash

export workdir="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/scripts/"
export inputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bu2D0Pi/Workspace/Nominal/work_d0pi_data.root"
export outputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bu2D0Pi/Workspace/Nominal/work_d0pi_mdfit_bu.root"
export outputweightstree="/afs/cern.ch/work/v/vibattis/public/B2DX/Bu2D0Pi/sWeights/Nominal/sWeights_RunIdata.root"
export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bu2D0Pi/Bu2D0PiConfigForMDFitter_Bu.py"
export outputplotdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bu2D0Pi/MDFitPlots_Bu/"
export runpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/"

rm -rf $outputplotdir
mkdir -p $outputplotdir

rm -f $outputfile

${runpath}run python ${workdir}runMDFitter_Bd.py -d --configName $conf --inputFile $inputfile --sWeightsName $outputweightstree --decay Bu2D0Pi --mode kpi --merge both --hypo Bu2D0Pi_Bu2D0K --outputplotdir $outputplotdir --outputFile $outputfile --dim 1 --binned --sWeights | tee ${outputplotdir}log_fit_Bu2D0Pi.txt


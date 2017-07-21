#!/bin/bash

export workdir="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/scripts/"
export rundir="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/"
export file="/eos/lhcb/wg/b2oc/TD_DPi_3fb/MCBootstrap/Bd2DPiMCFilteredS21RunIBothTaggedOnlyShortTime/TimeFit/SSbarAccAsymmFloatDMGammaConstrOSTaggedOnly/"
export outdir="/eos/lhcb/wg/b2oc/TD_DPi_3fb/Toys/SgnOnlyTrueTagProdDetAsymmAccMeanResTime04to12/TimeFit/SSbarAccAsymmFloatDMGammaConstrTrueTag/"
export config="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForSFitOnToys.py"
export data="dataSet_time"
export pdf="time_signal_RawTimePdf"
export label="LHCb Fast Simulation"

mkdir -p $outdir

${rundir}run python ${workdir}plotSFit.py $file -v BeautyTime --legend -w workspace --outdir $outdir --configName $config --dataSetToPlot $data --pdfToPlot $pdf --plotLabel "${label}"
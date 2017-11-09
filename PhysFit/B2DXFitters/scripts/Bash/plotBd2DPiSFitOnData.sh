#!/bin/bash

export workdir="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/scripts/"
export rundir="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/"
export file="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/SSbarAccAsymmFloatingDMGammaConstrOSInclusiveBlinded/workResults.root"
export outdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/SSbarAccAsymmFloatingDMGammaConstrOSInclusiveBlinded/"
export config="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForSFitOnData.py"
export data="combData"
export pdf="time_signal_TimePdf"
export label="LHCb Preliminary"

#mkdir -p $outdir

${rundir}run python ${workdir}plotSFit.py $file -v BeautyTime --legend -w workspace --outdir $outdir --configName $config --dataSetToPlot $data --pdfToPlot $pdf --plotLabel "${label}"
${rundir}run python ${workdir}plotSFit.py $file -v BeautyTime --legend -w workspace --outdir $outdir --configName $config --dataSetToPlot $data --pdfToPlot $pdf --plotLabel "${label}" --logscale
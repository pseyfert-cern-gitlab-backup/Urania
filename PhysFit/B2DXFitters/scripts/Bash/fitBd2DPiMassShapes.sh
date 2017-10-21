#!/bin/bash

export inputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/work_dpi_mcfiltered_forMassFits.root"
export outputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/work_dpi_pdfs.root"
export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMassFit.py"
export outputplotdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/TemplateFitPlots/"

export runpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/"

#rm -rf $outputplotdir
#mkdir -p $outputplotdir

rm -f $outputfile

#Bd->DPi
#${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Signal --mode kpipi --year 2012 --merge pol --hypo Bd2DPi --outputplotdir $outputplotdir --outputFile $outputfile --binned >& ${outputplotdir}log_Signal_PiHypo_BMass.txt

${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Signal --mode kpipi --year 2012 --merge pol --hypo Bd2DK --outputplotdir $outputplotdir --outputFile $outputfile --binned >& ${outputplotdir}log_Signal_KHypo_BMass.txt

#Bd->DK
#${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Bd2DK --mode kpipi --year 2012 --merge pol --hypo Bd2DPi --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Bd2DK_PiHypo_BMass.txt

${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Bd2DK --mode kpipi --year 2012 --merge pol --hypo Bd2DK --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Bd2DK_KHypo_BMass.txt

#Bd->DRho
#${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Bd2DRho --mode kpipi --year 2012 --merge pol --hypo Bd2DPi --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Bd2DRho_PiHypo_BMass.txt

${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Bd2DRho --mode kpipi --year 2012 --merge pol --hypo Bd2DK --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Bd2DRho_KHypo_BMass.txt

#Bd->DstPi
#${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Bd2DstPi --mode kpipi --year 2012 --merge pol --hypo Bd2DPi --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Bd2DstPi_PiHypo_BMass.txt

#Bd->DKst
${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Bd2DKst --mode kpipi --year 2012 --merge pol --hypo Bd2DK --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Bd2DKst_KHypo_BMass.txt
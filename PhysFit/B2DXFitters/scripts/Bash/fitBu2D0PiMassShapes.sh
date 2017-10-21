#!/bin/bash

export inputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bu2D0Pi/Workspace/Nominal/work_d0pi_mcfiltered_forMassFits.root"
export outputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bu2D0Pi/Workspace/Nominal/work_d0pi_pdfs.root"
export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bu2D0Pi/Bu2D0PiConfigForMassFit.py"
export outputplotdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bu2D0Pi/TemplateFitPlots/"

export runpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/"

#rm -rf $outputplotdir
#mkdir -p $outputplotdir

rm -f $outputfile

#Bu->D0Pi
#${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Signal --mode kpi --year 2012 --merge pol --hypo Bu2D0Pi --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Signal_PiHypo_BMass.txt

#${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Signal --mode kpi --year 2012 --merge pol --hypo Bu2D0K --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Signal_KHypo_BMass.txt

#Bu->D0K
#${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Bu2D0K --mode kpi --year 2012 --merge pol --hypo Bu2D0Pi --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Bu2D0K_PiHypo_BMass.txt

#${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Bu2D0K --mode kpi --year 2012 --merge pol --hypo Bu2D0K --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Bu2D0K_KHypo_BMass.txt

#Bd->D0PiPi
${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Bd2D0PiPi --mode kpi --year 2012 --merge pol --hypo Bu2D0Pi --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Bd2D0PiPi_PiHypo_BMass.txt

#Bu->Dst0Pi
${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Bu2Dst0Pi --mode kpi --year 2012 --merge pol --hypo Bu2D0Pi --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Bu2Dst0Pi_PiHypo_BMass.txt

${runpath}run python fitShapes.py -d --configName $conf --inputFile $inputfile --variable BeautyMass --component Bu2Dst0Pi --mode kpi --year 2012 --merge pol --hypo Bu2D0K --outputplotdir $outputplotdir --outputFile $outputfile >& ${outputplotdir}log_Bu2Dst0Pi_KHypo_BMass.txt
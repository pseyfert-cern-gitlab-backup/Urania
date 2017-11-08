#!/bin/bash

#Prevent core dump
ulimit -c 0

#Bd2DPi
export nickname="MCSSbarAccAsymmFloatingDMGammaConstrTrueTaggingOnlyTaggedShortTime"
export config="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForSFitOnMC.py"
export pyscriptpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/scripts/"
export runpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/"
export preselection="TagDecOS!=0||TagDecSS!=0"

#All, true tagging
export inputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/work_dpi_mc_large_shorttime.root"
export outputdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/${nickname}/AllData/"
export outputfile=${outputdir}"workResults.root"
export pol="both"
export mode="kpipi"
export year="run1"
export hypo="Bd2DPi"
#rm -rf $outputdir
#mkdir -p $outputdir
export Start=`date`
echo "==> Start fitting at ${Start}"
${runpath}run python ${pyscriptpath}runSFit_Bd.py --debug --outputdir $outputdir --fileName $inputfile --save $outputfile --configName $config --pol $pol --mode $mode --year $year --hypo $hypo --merge both --truetag --HFAG --MC --workMC "workspace" --noweight --preselection $preselection | tee ${outputdir}logfile.txt
export Stop=`date`
echo "==> Stop fitting at ${Stop}"
exit

#2011 MU, true tagging
export inputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/work_dpi_mc_large_shorttime.root"
export outputdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/${nickname}/2011MU/"
export outputfile=${outputdir}"workResults.root"
export pol="up"
export mode="kpipi"
export year="2011"
export hypo="Bd2DPi"
rm -rf $outputdir
mkdir -p $outputdir
export Start=`date`
echo "==> Start fitting at ${Start}"
${runpath}run python ${pyscriptpath}runSFit_Bd.py --debug --outputdir $outputdir --fileName $inputfile --save $outputfile --configName $config --pol $pol --mode $mode --year $year --hypo $hypo --truetag --HFAG --MC --workMC "workspace" --noweight --preselection $preselection | tee ${outputdir}logfile.txt
export Stop=`date`
echo "==> Stop fitting at ${Stop}"

#2011 MD, true tagging
export inputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/work_dpi_mc_large_shorttime.root"
export outputdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/${nickname}/2011MD/"
export outputfile=${outputdir}"workResults.root"
export pol="down"
export mode="kpipi"
export year="2011"
export hypo="Bd2DPi"
rm -rf $outputdir
mkdir -p $outputdir
export Start=`date`
echo "==> Start fitting at ${Start}"
${runpath}run python ${pyscriptpath}runSFit_Bd.py --debug --outputdir $outputdir --fileName $inputfile --save $outputfile --configName $config --pol $pol --mode $mode --year $year --hypo $hypo --truetag --HFAG --MC --workMC "workspace" --noweight --preselection $preselection | tee ${outputdir}logfile.txt
export Stop=`date`
echo "==> Stop fitting at ${Stop}"

#2012 MU, true tagging
export inputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/work_dpi_mc_large_shorttime.root"
export outputdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/${nickname}/2012MU/"
export outputfile=${outputdir}"workResults.root"
export pol="up"
export mode="kpipi"
export year="2012"
export hypo="Bd2DPi"
rm -rf $outputdir
mkdir -p $outputdir
export Start=`date`
echo "==> Start fitting at ${Start}"
${runpath}run python ${pyscriptpath}runSFit_Bd.py --debug --outputdir $outputdir --fileName $inputfile --save $outputfile --configName $config --pol $pol --mode $mode --year $year --hypo $hypo --truetag --HFAG --MC --workMC "workspace" --noweight --preselection $preselection | tee ${outputdir}logfile.txt
export Stop=`date`
echo "==> Stop fitting at ${Stop}"

#2012 MD, true tagging
export inputfile="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/work_dpi_mc_large_shorttime.root"
export outputdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/sFit/${nickname}/2012MD/"
export outputfile=${outputdir}"workResults.root"
export pol="down"
export mode="kpipi"
export year="2012"
export hypo="Bd2DPi"
rm -rf $outputdir
mkdir -p $outputdir
export Start=`date`
echo "==> Start fitting at ${Start}"
${runpath}run python ${pyscriptpath}runSFit_Bd.py --debug --outputdir $outputdir --fileName $inputfile --save $outputfile --configName $config --pol $pol --mode $mode --year $year --hypo $hypo --truetag --HFAG --MC --workMC "workspace" --noweight --preselection $preselection | tee ${outputdir}logfile.txt
export Stop=`date`
echo "==> Stop fitting at ${Stop}"
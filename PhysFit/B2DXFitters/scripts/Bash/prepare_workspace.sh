#!/bin/bash

export workpath="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/"
export scriptpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/scripts/"
export runpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/"

#rm -rf $workpath
#mkdir -p $workpath

export save=${workpath}"work_dpi_mc_large_shorttime.root"
export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForWorkspace_PiHypo_MC_large.py"
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Signal --debug -s $save --configName $conf
rm Trash/*.root

exit

export save=${workpath}"work_dpi_mc.root"
export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForWorkspace_PiHypo_MC.py"
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --MC --debug -s $save --configName $conf
rm Trash/*.root
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Signal --debug -i $save -s $save --configName $conf
rm Trash/*.root
export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForWorkspace_KHypo_MC.py"
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --MC --debug -i $save -s $save --configName $conf
rm Trash/*.root
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Signal --debug -i $save -s $save --configName $conf
rm Trash/*.root

export save=${workpath}"work_dpi_data.root"
export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForWorkspace_PiHypo_Data.py"
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Data --debug -s $save --configName $conf
rm Trash/*.root
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Comb --debug -i $save -s $save --configName $conf
rm Trash/*.root
export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForWorkspace_KHypo_Data.py"
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Data --debug -i $save -s $save --configName $conf
rm Trash/*.root
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Comb --debug -i $save -s $save --configName $conf
rm Trash/*.root
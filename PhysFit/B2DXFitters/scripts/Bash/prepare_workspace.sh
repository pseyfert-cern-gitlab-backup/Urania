#!/bin/bash

export workpath="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/Workspace/Nominal/"
export scriptpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/scripts/"
export runpath="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/"

export save=${workpath}"work_dpi_mcfiltered_forTimeFits.root"
export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForWorkspace_PiHypo_MC_large.py"
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Signal --debug -s $save --configName $conf >& logWorkspace_mc_forTimeFits.txt
rm Trash/*.root

export save=${workpath}"work_dpi_mcfiltered_forMassFits.root"
export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForWorkspace_PiHypo_MC.py"
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --MC --debug -s $save --configName $conf >& logWorkspace_pihypo_mc_forMassFits.txt
rm Trash/*.root
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Signal --debug -i $save -s $save --configName $conf >& logWorkspace_sgn_pihypo_mc_forMassFits.txt
rm Trash/*.root
export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForWorkspace_KHypo_MC.py"
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --MC --debug -i $save -s $save --configName $conf >& logWorkspace_khypo_mc_forMassFits.txt
rm Trash/*.root
${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Signal --debug -i $save -s $save --configName $conf >& logWorkspace_sgn_khypo_mc_forMassFits.txt
rm Trash/*.root

#export save=${workpath}"work_dpi_data.root"
#export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForWorkspace_PiHypo_Data.py"
#${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Data --debug -s $save --configName $conf >& logWorkspace_pihypo_data.txt
#rm Trash/*.root
#export conf="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r2p1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForWorkspace_KHypo_Data.py"
#${runpath}run python ${scriptpath}prepareWorkspace.py --noRooKeysPdf --Data --debug -i $save -s $save --configName $conf >& logWorkspace_khypo_data.txt
#rm Trash/*.root
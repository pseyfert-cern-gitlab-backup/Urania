#!/bin/bash

export workdir="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/scripts/"
export rundir="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/"
export outputplotdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/MCAcceptance/"
#rm -rf $outputplotdir
#mkdir -p $outputplotdir

#All MC
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_PID-corrected_new_TagsCombined.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_PID-corrected_new_TagsCombined.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_PID-corrected_new_TagsCombined.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_PID-corrected_new_TagsCombined.root]"
export inputtree="Bd2Dpi"
export nickname="All_NewKnots"
export LHCbText="LHCb Simulation"
${rundir}run python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" | tee ${outputplotdir}logfile_${nickname}.txt
exit
#MC 2011 MU tagged
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/Urania_v5r0/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_PID-corrected_new_TagsCombined.root]"
export inputtree="Bd2Dpi"
export nickname="2011MU"
export LHCbText="LHCb Simulation 2011 MU tagged"
#python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" >& ${outputplotdir}logfile_${nickname}.txt

#MC 2011 MD tagged
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/Urania_v5r0/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_PID-corrected_new_TagsCombined.root]"
export inputtree="Bd2Dpi"
export nickname="2011MD"
export LHCbText="LHCb Simulation 2011 MD tagged"
#python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" >& ${outputplotdir}logfile_${nickname}.txt

#MC 2012 MU tagged
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/Urania_v5r0/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_PID-corrected_new_TagsCombined.root]"
export inputtree="Bd2Dpi"
export nickname="2012MU"
export LHCbText="LHCb Simulation 2012 MU tagged"
#python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" >& ${outputplotdir}logfile_${nickname}.txt

#MC 2012 MD tagged
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/Urania_v5r0/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_PID-corrected_new_TagsCombined.root]"
export inputtree="Bd2Dpi"
export nickname="2012MD"
export LHCbText="LHCb Simulation 2012 MD tagged"
#python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" >& ${outputplotdir}logfile_${nickname}.txt

#MC 2011 OSexcl
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/Urania_v5r0/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance_OSexcl.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_PID-corrected_new_TagsCombined.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_PID-corrected_new_TagsCombined.root]"
export inputtree="Bd2Dpi"
export nickname="2011OSexcl"
export LHCbText="LHCb Simulation 2011 OS exclusive"
python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" >& ${outputplotdir}logfile_${nickname}.txt

#MC 2011 SSincl
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/Urania_v5r0/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance_SSincl.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_PID-corrected_new_TagsCombined.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_PID-corrected_new_TagsCombined.root]"
export inputtree="Bd2Dpi"
export nickname="2011SSincl"
export LHCbText="LHCb Simulation 2011 SS inclusive"
python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" >& ${outputplotdir}logfile_${nickname}.txt

#MC 2012 OSexcl
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/Urania_v5r0/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance_OSexcl.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_PID-corrected_new_TagsCombined.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_PID-corrected_new_TagsCombined.root]"
export inputtree="Bd2Dpi"
export nickname="2012OSexcl"
export LHCbText="LHCb Simulation 2012 OS exclusive"
python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" >& ${outputplotdir}logfile_${nickname}.txt

#MC 2012 SSincl
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/Urania_v5r0/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance_SSincl.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_PID-corrected_new_TagsCombined.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_PID-corrected_new_TagsCombined.root]"
export inputtree="Bd2Dpi"
export nickname="2012SSincl"
export LHCbText="LHCb Simulation 2012 SS inclusive"
python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" >& ${outputplotdir}logfile_${nickname}.txt
#!/bin/bash

export workdir="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/scripts/"
export rundir="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/"
export outputplotdir="/afs/cern.ch/work/v/vibattis/public/B2DX/Bd2DPi/MCAcceptance/"
rm -rf $outputplotdir
mkdir -p $outputplotdir

#All MC tagged
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance_New2.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root]"
export preselection="lab0_BKGCAT==0&&(TagDecOS!=0||obsTagSS_PionInvBoost_ProtonInvBoost!=0)"
export inputtree="Bd2Dpi"
export nickname="All_Tag"
export LHCbText="LHCb Simulation Tagged"
${rundir}run python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" --preselection $preselection >& ${outputplotdir}logfile_${nickname}.txt

#All MC, tagged, all triggers, old knots
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance_New2.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root]"
export preselection="lab0_BKGCAT==0&&(TagDecOS!=0||obsTagSS_PionInvBoost_ProtonInvBoost!=0)&&lab0_Hlt2Topo2BodyBBDTDecision_TOS==1&&(lab0_Hlt2Topo3BodyBBDTDecision_TOS==1||lab0_Hlt2Topo4BodyBBDTDecision_TOS==1)" 
export inputtree="Bd2Dpi"
export nickname="All_Tag_234B"
export LHCbText="LHCb Simulation Tagged AllTOS"
${rundir}run python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" --preselection $preselection >& ${outputplotdir}logfile_${nickname}.txt

#All MC, tagged, 2B TOS, old knots
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance_New2.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root]"
export preselection="lab0_BKGCAT==0&&(TagDecOS!=0||obsTagSS_PionInvBoost_ProtonInvBoost!=0)&&lab0_Hlt2Topo2BodyBBDTDecision_TOS==1&&lab0_Hlt2Topo3BodyBBDTDecision_TOS==0&&lab0_Hlt2Topo4BodyBBDTDecision_TOS==0"
export inputtree="Bd2Dpi"
export nickname="All_Tag_2B"
export LHCbText="LHCb Simulation Tagged 2BodyTOS"
${rundir}run python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" --preselection $preselection >& ${outputplotdir}logfile_${nickname}.txt

#All MC, tagged, 34B TOS, old knots
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance_New2.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root]"
export preselection="lab0_BKGCAT==0&&(TagDecOS!=0||obsTagSS_PionInvBoost_ProtonInvBoost!=0)&&lab0_Hlt2Topo2BodyBBDTDecision_TOS==0&&(lab0_Hlt2Topo3BodyBBDTDecision_TOS==1||lab0_Hlt2Topo4BodyBBDTDecision_TOS==1)"
export inputtree="Bd2Dpi"
export nickname="All_Tag_34B"
export LHCbText="LHCb Simulation Tagged 34BodyTOS"
${rundir}run python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" --preselection $preselection >& ${outputplotdir}logfile_${nickname}.txt

exit

#All MC, tagged, 4B TOS, old knots
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root]"
export preselection="lab0_BKGCAT==0&&(TagDecOS!=0||obsTagSS_PionInvBoost_ProtonInvBoost!=0)&&lab0_Hlt2Topo2BodyBBDTDecision_TOS==0&&lab0_Hlt2Topo3BodyBBDTDecision_TOS==0&&lab0_Hlt2Topo4BodyBBDTDecision_TOS==1"
export inputtree="Bd2Dpi"
export nickname="All_Tag_4B_OldAcc"
export LHCbText="LHCb Sim Tag 4BodyTOS"
${rundir}run python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" --preselection $preselection | tee ${outputplotdir}logfile_${nickname}.txt

#All MC, tagged, 23B TOS, old knots
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root]"
export preselection="lab0_BKGCAT==0&&(TagDecOS!=0||obsTagSS_PionInvBoost_ProtonInvBoost!=0)&&lab0_Hlt2Topo2BodyBBDTDecision_TOS==1&&lab0_Hlt2Topo3BodyBBDTDecision_TOS==1&&lab0_Hlt2Topo4BodyBBDTDecision_TOS==0"
export inputtree="Bd2Dpi"
export nickname="All_Tag_23B_OldAcc"
export LHCbText="LHCb Sim Tag 23BodyTOS"
${rundir}run python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" --preselection $preselection | tee ${outputplotdir}logfile_${nickname}.txt

#All MC, tagged, 24B TOS, old knots 
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root]"
export preselection="lab0_BKGCAT==0&&(TagDecOS!=0||obsTagSS_PionInvBoost_ProtonInvBoost!=0)&&lab0_Hlt2Topo2BodyBBDTDecision_TOS==1&&lab0_Hlt2Topo3BodyBBDTDecision_TOS==0&&lab0_Hlt2Topo4BodyBBDTDecision_TOS==1"
export inputtree="Bd2Dpi"
export nickname="All_Tag_24B_OldAcc"
export LHCbText="LHCb Sim Tag 24BodyTOS"
${rundir}run python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" --preselection $preselection | tee ${outputplotdir}logfile_${nickname}.txt

#All MC, tagged, 34B TOS, old knots
export configfile="/afs/cern.ch/user/v/vibattis/cmtuser/UraniaDev_v6r1/PhysFit/B2DXFitters/data/Bd2DPi_3fbCPV/Bd2DPi/Bd2DPiConfigForMCAcceptance.py"
export inputfile="[root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2011_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magUp_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root;root://eoslhcb.cern.ch//eos/lhcb/wg/b2oc/TD_DPi_3fb/MC/MCfiltered_Bd2DPi_Bd2DPiHypo_magDown_2012_S21_afterSelection_OSandSSCombined_PID-corrected_new.root]"
export preselection="lab0_BKGCAT==0&&(TagDecOS!=0||obsTagSS_PionInvBoost_ProtonInvBoost!=0)&&lab0_Hlt2Topo2BodyBBDTDecision_TOS==0&&lab0_Hlt2Topo3BodyBBDTDecision_TOS==1&&lab0_Hlt2Topo4BodyBBDTDecision_TOS==1"
export inputtree="Bd2Dpi"
export nickname="All_Tag_34B_OldAcc"
export LHCbText="LHCb Sim Tag 34BodyTOS"
${rundir}run python ${workdir}FitAcceptance.py --configName $configfile --inputfile $inputfile --inputtree $inputtree --outputplotdir $outputplotdir --nickname $nickname --LHCbText "${LHCbText}" --preselection $preselection | tee ${outputplotdir}logfile_${nickname}.txt 
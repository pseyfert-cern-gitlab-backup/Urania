#********
#S24
#********
#./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/DoubleCharm.root -conf config/config_LowBins.txt -twd -flag Trig24DoubleCharm -mc &> output/DoubleCharm_Trig24.log

./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/RDS_BdDstDs_Down.root -conf config/config_MCStudy_Down.txt -twd -flag MCstuTemDBdDstDs -mc &> output/BdDstDs_MCstuTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/RDS_BuD0Ds_Down.root -conf config/config_MCStudy_Down.txt -twd -flag MCstuTemDBuD0Ds -mc &> output/BuD0Ds_MCstuTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/RDS_LbLcDs_Down.root -conf config/config_MCStudy_Down.txt -twd -flag MCstuTemDLbLcDs -mc &> output/LbLcDs_MCstuTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/RDS_BsDsDs_Down.root -conf config/config_MCStudy_Down.txt -twd -flag MCstuTemDBsDsDs -mc &> output/BsDsDs_MCstuTemD.log

./Templater -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/TupleRDS_DataDown_allNeutrals_iso.root -conf config/config_MCStudy_Down.txt -twd -flag MCstuTemDSideBands -side &> output/SideBands_MCstuTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/TupleRDS_DataDown_allNeutrals_iso.root -ss -conf config/config_MCStudy_Down.txt -twd -flag MCstuTemDSameSide &> output/SameSide_MCstuTemD.log

./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCStudy_Down.txt -twd -flag MCstuTemDSignal_Bs0DsMu -mc -mat 1 &> output/Signal_Bs0DsMu_MCstuTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCStudy_Down.txt -twd -flag MCstuTemDSignal_Bs0DstaMu -mc -mat 2 &> output/Signal_Bs0DstaMu_MCstuTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCStudy_Down.txt -twd -flag MCstuTemDSignal_Bs0Ds1Mu -mc -mat 3 &> output/Signal_Bs0Ds1Mu_MCstuTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCStudy_Down.txt -twd -flag MCstuTemDSignal_Bs0D1pMu -mc -mat 4 &> output/Signal_Bs0Ds1pMu_MCstuTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCStudy_Down.txt -twd -flag MCstuTemDSignal_Bs0Ds0staMu -mc -mat 5 &> output/Signal_Bs0Ds0staMu_MCstuTemD.log



./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCStudy_Down.txt -twd -flag TauMCstuTemDSignal_Bs0DsTau -mc -mat 1 &> output/Signal_Bs0DsTau_TauMCstuTemD.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCStudy_Down.txt -twd -flag TauMCstuTemDSignal_Bs0DstaTau -mc -mat 2 &> output/Signal_Bs0DstaTau_TauMCstuTemD.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCStudy_Down.txt -twd -flag TauMCstuTemDSignal_Bs0Ds1Tau -mc -mat 3 &> output/Signal_Bs0Ds1Tau_TauMCstuTemD.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCStudy_Down.txt -twd -flag TauMCstuTemDSignal_Bs0Ds1pTau -mc -mat 4 &> output/Signal_Bs0Ds1pTau_TauMCstuTemD.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCStudy_Down.txt -twd -flag TauMCstuTemDSignal_Bs0Ds0staTau -mc -mat 5 &> output/Signal_Bs0Ds0staTau_TauMCstuTemD.log

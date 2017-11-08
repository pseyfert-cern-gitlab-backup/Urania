#********
#S24
#********
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/RDS_BdDstDs_Down.root -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag MCLowBinTemDBdDstDs -mc &> output/BdDstDs_MCLowBinTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/RDS_BuD0Ds_Down.root -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag MCLowBinTemDBuD0Ds -mc &> output/BuD0Ds_MCLowBinTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/RDS_LbLcDs_Down.root -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag MCLowBinTemDLbLcDs -mc &> output/LbLcDs_MCLowBinTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/RDS_BsDsDs_Down.root -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag MCLowBinTemDBsDsDs -mc &> output/BsDsDs_MCLowBinTemD.log

./Templater -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/TupleRDS_DataDown_allNeutrals_iso.root -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag MCLowBinTemDSideBands -side &> output/SideBands_MCLowBinTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/TupleRDS_DataDown_allNeutrals_iso.root -ss -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag MCLowBinTemDSameSide &> output/SameSide_MCLowBinTemD.log

./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag MCLowBinTemDSignal_Bs0DsMu -mc -mat 1 &> output/Signal_Bs0DsMu_MCLowBinTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag MCLowBinTemDSignal_Bs0DstaMu -mc -mat 2 &> output/Signal_Bs0DstaMu_MCLowBinTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag MCLowBinTemDSignal_Bs0Ds1Mu -mc -mat 3 &> output/Signal_Bs0Ds1Mu_MCLowBinTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag MCLowBinTemDSignal_Bs0D1pMu -mc -mat 4 &> output/Signal_Bs0Ds1pMu_MCLowBinTemD.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag MCLowBinTemDSignal_Bs0Ds0staMu -mc -mat 5 &> output/Signal_Bs0Ds0staMu_MCLowBinTemD.log



./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag TauMCLowBinTemDSignal_Bs0DsTau -mc -mat 1 &> output/Signal_Bs0DsTau_TauMCLowBinTemD.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag TauMCLowBinTemDSignal_Bs0DstaTau -mc -mat 2 &> output/Signal_Bs0DstaTau_TauMCLowBinTemD.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag TauMCLowBinTemDSignal_Bs0Ds1Tau -mc -mat 3 &> output/Signal_Bs0Ds1Tau_TauMCLowBinTemD.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag TauMCLowBinTemDSignal_Bs0Ds1pTau -mc -mat 4 &> output/Signal_Bs0Ds1pTau_TauMCLowBinTemD.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/TupleRDS_MCSignalDown_allNeutrals_iso.root   -conf config/config_MCLowBin_Up2DQsq.txt -twd -flag TauMCLowBinTemDSignal_Bs0Ds0staTau -mc -mat 5 &> output/Signal_Bs0Ds0staTau_TauMCLowBinTemD.log

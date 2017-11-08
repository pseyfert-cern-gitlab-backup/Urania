#********
#S24
#********
#./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/DoubleCharm.root -conf config/config_LowBins.txt -twd -flag Trig24DoubleCharm -mc &> output/DoubleCharm_Trig24.log


./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BdDstDs.root -conf config/config_VeryLowBins.txt -twd -flag TWFewBBdDstDs -mc &> output/BdDstDs_TWFewB.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BuD0Ds.root -conf config/config_VeryLowBins.txt -twd -flag TWFewBBuD0Ds -mc &> output/BuD0Ds_TWFewB.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/LbLcDs.root -conf config/config_VeryLowBins.txt -twd -flag TWFewBLbLcDs -mc &> output/LbLcDs_TWFewB.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BsDsDs.root -conf config/config_VeryLowBins.txt -twd -flag TWFewBBsDsDs -mc &> output/BsDsDs_TWFewB.log

./Templater -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/DataAN_S24_RDS_FromTauMu.root -conf config/config_VeryLowBins.txt -twd -flag TWFewBSideBands -side &> output/SideBands_TWFewB.log
./Templater -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/DataAN_S24_RDS_FromTauMu.root -ss -conf config/config_VeryLowBins.txt -twd -flag TWFewBSameSide &> output/SameSide_TWFewB.log

./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN.root   -conf config/config_VeryLowBins.txt -twd -flag TWFewBSignal_Bs0DsMu -mc -mat 1 &> output/Signal_Bs0DsMu_TWFewB.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN.root   -conf config/config_VeryLowBins.txt -twd -flag TWFewBSignal_Bs0DstaMu -mc -mat 2 &> output/Signal_Bs0DstaMu_TWFewB.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN.root   -conf config/config_VeryLowBins.txt -twd -flag TWFewBSignal_Bs0Ds1Mu -mc -mat 3 &> output/Signal_Bs0Ds1Mu_TWFewB.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN.root   -conf config/config_VeryLowBins.txt -twd -flag TWFewBSignal_Bs0D1pMu -mc -mat 4 &> output/Signal_Bs0Ds1pMu_TWFewB.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN.root   -conf config/config_VeryLowBins.txt -twd -flag TWFewBSignal_Bs0Ds0staMu -mc -mat 5 &> output/Signal_Bs0Ds0staMu_TWFewB.log


./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BdDstDs.root -conf config/config_VeryLowBins.txt -twd -flag TauTWFewBBdDstDs -mc &> output/BdDstDs_TauTWFewB.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BuD0Ds.root -conf config/config_VeryLowBins.txt -twd -flag TauTWFewBBuD0Ds -mc &> output/BuD0Ds_TauTWFewB.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/LbLcDs.root -conf config/config_VeryLowBins.txt -twd -flag TauTWFewBLbLcDs -mc &> output/LbLcDs_TauTWFewB.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BsDsDs.root -conf config/config_VeryLowBins.txt -twd -flag TauTWFewBBsDsDs -mc &> output/BsDsDs_TauTWFewB.log

./Templater -tau -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/DataAN_S24_RDS_FromTauMu.root -conf config/config_VeryLowBins.txt -twd -flag TauTWFewBSideBands -side &> output/SideBands_TauTWFewB.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/DataAN_S24_RDS_FromTauMu.root -ss -conf config/config_VeryLowBins.txt -twd -flag TauTWFewBSameSide &> output/SameSide_TauTWFewB.log

./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN.root   -conf config/config_VeryLowBins.txt -twd -flag TauTWFewBSignal_Bs0DsTau -mc -mat 1 &> output/Signal_Bs0DsTau_TauTWFewB.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN.root   -conf config/config_VeryLowBins.txt -twd -flag TauTWFewBSignal_Bs0DstaTau -mc -mat 2 &> output/Signal_Bs0DstaTau_TauTWFewB.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN.root   -conf config/config_VeryLowBins.txt -twd -flag TauTWFewBSignal_Bs0Ds1Tau -mc -mat 3 &> output/Signal_Bs0Ds1Tau_TauTWFewB.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN.root   -conf config/config_VeryLowBins.txt -twd -flag TauTWFewBSignal_Bs0Ds1pTau -mc -mat 4 &> output/Signal_Bs0Ds1pTau_TauTWFewB.log
./Templater -tau -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN.root   -conf config/config_VeryLowBins.txt -twd -flag TauTWFewBSignal_Bs0Ds0staTau -mc -mat 5 &> output/Signal_Bs0Ds0staTau_TauTWFewB.log

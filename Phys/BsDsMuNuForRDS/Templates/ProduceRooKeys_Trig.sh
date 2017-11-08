#********
#S24
#********
#./Templater -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/DoubleCharm.root -conf config/config_LowBins.txt -twd -flag Trig24DoubleCharm -mc &> output/DoubleCharm_Trig24.log

./Templater -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BdDstDs_iso.root -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKLBNoBMNopTBdDstDs -mc &> output/RooKBdDstDs_LBNoBMNopT.log
./Templater -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BuD0Ds_iso.root -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKLBNoBMNopTBuD0Ds -mc &> output/RooKBuD0Ds_LBNoBMNopT.log
./Templater -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/LbLcDs_iso.root -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKLBNoBMNopTLbLcDs -mc &> output/RooKLbLcDs_LBNoBMNopT.log
./Templater -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BsDsDs_iso.root -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKLBNoBMNopTBsDsDs -mc &> output/RooKBsDsDs_LBNoBMNopT.log

./Templater -rook -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/DataAN_S24_RDS_FromTauMu_iso.root -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKLBNoBMNopTSideBands -side &> output/RooKSideBands_LBNoBMNopT.log
./Templater -rook -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/DataAN_S24_RDS_FromTauMu_iso.root -ss -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKLBNoBMNopTSameSide &> output/RooKSameSide_LBNoBMNopT.log

./Templater -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN_iso.root   -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKLBNoBMNopTSignal_Bs0DsMu -mc -mat 1 &> output/RooKSignal_Bs0DsMu_LBNoBMNopT.log
./Templater -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN_iso.root   -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKLBNoBMNopTSignal_Bs0DstaMu -mc -mat 2 &> output/RooKSignal_Bs0DstaMu_LBNoBMNopT.log
./Templater -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN_iso.root   -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKLBNoBMNopTSignal_Bs0Ds1Mu -mc -mat 3 &> output/RooKSignal_Bs0Ds1Mu_LBNoBMNopT.log
./Templater -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN_iso.root   -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKLBNoBMNopTSignal_Bs0D1pMu -mc -mat 4 &> output/RooKSignal_Bs0Ds1pMu_LBNoBMNopT.log
./Templater -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN_iso.root   -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKLBNoBMNopTSignal_Bs0Ds0staMu -mc -mat 5 &> output/RooKSignal_Bs0Ds0staMu_LBNoBMNopT.log


./Templater -tau -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN_iso.root   -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKTauLBNoBMNopTSignal_Bs0DsTau -mc -mat 1 &> output/RooKSignal_Bs0DsTau_TauLBNoBMNopT.log
./Templater -tau -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN_iso.root   -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKTauLBNoBMNopTSignal_Bs0DstaTau -mc -mat 2 &> output/RooKSignal_Bs0DstaTau_TauLBNoBMNopT.log
./Templater -tau -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN_iso.root   -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKTauLBNoBMNopTSignal_Bs0Ds1Tau -mc -mat 3 &> output/RooKSignal_Bs0Ds1Tau_TauLBNoBMNopT.log
./Templater -tau -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN_iso.root   -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKTauLBNoBMNopTSignal_Bs0Ds1pTau -mc -mat 4 &> output/RooKSignal_Bs0Ds1pTau_TauLBNoBMNopT.log
./Templater -tau -rook -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/SignalAN_iso.root   -conf config/config_LowBin_IsoNoBMNopT_Q2.txt  -flag RooKTauLBNoBMNopTSignal_Bs0Ds0staTau -mc -mat 5 &> output/RooKSignal_Bs0Ds0staTau_TauLBNoBMNopT.log

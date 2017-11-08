#********
#S24
#********

./Templater -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/BdDstDs_iso.root -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag NorBIsoPIDCutBdDstDs -mc &> output/BdDstDs_NorBIsoPIDCut.log
./Templater -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/BuD0Ds_iso.root -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag NorBIsoPIDCutBuD0Ds -mc &> output/BuD0Ds_NorBIsoPIDCut.log
./Templater -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/LbLcDs_iso.root -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag NorBIsoPIDCutLbLcDs -mc &> output/LbLcDs_NorBIsoPIDCut.log
./Templater -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/BsDsDs_iso.root -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag NorBIsoPIDCutBsDsDs -mc &> output/BsDsDs_NorBIsoPIDCut.log

./Templater -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/SignalAN_iso.root   -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag NorBIsoPIDCutSignal_Bs0DsMu -mc -mat 1 &> output/Signal_Bs0DsMu_NorBIsoPIDCut.log
./Templater -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/SignalAN_iso.root   -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag NorBIsoPIDCutSignal_Bs0DstaMu -mc -mat 2 &> output/Signal_Bs0DstaMu_NorBIsoPIDCut.log
./Templater -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/SignalAN_iso.root   -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag NorBIsoPIDCutSignal_Bs0Ds1Mu -mc -mat 3 &> output/Signal_Bs0Ds1Mu_NorBIsoPIDCut.log
./Templater -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/SignalAN_iso.root   -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag NorBIsoPIDCutSignal_Bs0D1pMu -mc -mat 4 &> output/Signal_Bs0Ds1pMu_NorBIsoPIDCut.log
./Templater -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/SignalAN_iso.root   -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag NorBIsoPIDCutSignal_Bs0Ds0staMu -mc -mat 5 &> output/Signal_Bs0Ds0staMu_NorBIsoPIDCut.log

./Templater -tau -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/SignalAN_iso.root   -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag TauNorBIsoPIDCutSignal_Bs0DsTau -mc -mat 1 &> output/Signal_Bs0DsTau_TauNorBIsoPIDCut.log
./Templater -tau -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/SignalAN_iso.root   -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag TauNorBIsoPIDCutSignal_Bs0DstaTau -mc -mat 2 &> output/Signal_Bs0DstaTau_TauNorBIsoPIDCut.log
./Templater -tau -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/SignalAN_iso.root   -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag TauNorBIsoPIDCutSignal_Bs0Ds1Tau -mc -mat 3 &> output/Signal_Bs0Ds1Tau_TauNorBIsoPIDCut.log
./Templater -tau -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/SignalAN_iso.root   -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag TauNorBIsoPIDCutSignal_Bs0Ds1pTau -mc -mat 4 &> output/Signal_Bs0Ds1pTau_TauNorBIsoPIDCut.log
./Templater -tau -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/SignalAN_iso.root   -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag TauNorBIsoPIDCutSignal_Bs0Ds0staTau -mc -mat 5 &> output/Signal_Bs0Ds0staTau_TauNorBIsoPIDCut.log

./Templater -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/DataAN_S24_RDS_FromTauMu_iso.root -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag NorBIsoPIDCutSideBands -side &> output/SideBands_NorBIsoPIDCut.log
./Templater -in /eos/lhcb/user/s/sogilvy/RDs/WithVetoes/DataAN_S24_RDS_FromTauMu_iso.root -ss -conf config/config_NorBin_IsoPIDCut_Q2.txt  -flag NorBIsoPIDCutSameSide &> output/SameSide_NorBIsoPIDCut.log


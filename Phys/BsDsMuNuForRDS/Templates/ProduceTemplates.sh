# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/DataFake.root -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPDataFake -fake &> output/DataFake_FB_PhiP.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPSignalAll -mc &> output/SignalAll_FB_PhiP.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPSignal_Bs0DsMu -mc -mat 1 &> output/Signal_Bs0DsMu_FB_PhiP.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPSignal_Bs0DstaMu -mc -mat 2 &> output/Signal_Bs0DstaMu_FB_PhiP.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPSignal_Bs0Ds2460Mu -mc -mat 3 &> output/Signal_Bs0Ds2460Mu_FB_PhiP.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPSignal_Bs0Ds2536Mu -mc -mat 4 &> output/Signal_Bs0Ds2536Mu_FB_PhiP.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPSignal_Bs0Ds0staMu -mc -mat 5 &> output/Signal_Bs0Ds0staMu_FB_PhiP.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/BdDstDs.root  -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPBdDstDs -mc &> output/BdDstDs_FB_PhiP.log 
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/BuD0Ds.root   -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPBuD0Ds -mc &> output/BuD0Ds_FB_PhiP.log 
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/LbLcDs.root   -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPLbLcDs -mc &> output/LbLcDs_FB_PhiP.log  
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/DoubleCharm.root -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPDoubleCharm -mc &> output/DoubleCharm_FB_PhiP.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/DataFake.root -conf config/config_LowBins_PhiPi.txt -flag FB_PhiPSideBands -side &> output/SideBands_FB_PhiP.log

#********
#S23
#********


# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/DataFake.root -conf config/config_LowBins.txt -flag FBDefDataFake -fake &> output/DataFake_FBDef.log

# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/DataFake.root -trueds -conf config/config_LowBins.txt -flag FBDefDsTrueComb -fake &> output/DsTrueComb_FBDef.log

# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins.txt -flag FBDefSignalAll -mc &> output/SignalAll_FBDef.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins.txt -flag FBDefSignal_Bs0DsMu -mc -mat 1 &> output/Signal_Bs0DsMu_FBDef.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins.txt -flag FBDefSignal_Bs0DstaMu -mc -mat 2 &> output/Signal_Bs0DstaMu_FBDef.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins.txt -flag FBDefSignal_Bs0Ds2460Mu -mc -mat 3 &> output/Signal_Bs0Ds2460Mu_FBDef.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins.txt -flag FBDefSignal_Bs0Ds2536Mu -mc -mat 4 &> output/Signal_Bs0Ds2536Mu_FBDef.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/Signal.root   -conf config/config_LowBins.txt -flag FBDefSignal_Bs0Ds0staMu -mc -mat 5 &> output/Signal_Bs0Ds0staMu_FBDef.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/BdDstDs.root  -conf config/config_LowBins.txt -flag FBDefBdDstDs -mc &> output/BdDstDs_FBDef.log 
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/BuD0Ds.root   -conf config/config_LowBins.txt -flag FBDefBuD0Ds -mc &> output/BuD0Ds_FBDef.log 
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/LbLcDs.root   -conf config/config_LowBins.txt -flag FBDefLbLcDs -mc &> output/LbLcDs_FBDef.log  
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/DoubleCharm.root -conf config/config_LowBins.txt -flag FBDefDoubleCharm -mc &> output/DoubleCharm_FBDef.log
# ./Templater -in /data/Shared/TupleProd_Dec15/RDS/DataFake.root -conf config/config_LowBins.txt -flag FBDefSideBands -side &> output/SideBands_FBDef.log
# ./Templater -in /data/Shared/TupleProd_Dec15/DataMagUp_S24_RDS_FromTauMu.root -ss -conf config/config_LowBins.txt -flag FBDefSameSide &> output/SameSide_FBDef.log



#********
#S24
#********

#./Templater -in /data/Shared/TupleProd_Dec15/RDS/Data_S24_RDS_FromTauMu.root -conf config/config_LowBins.txt -flag FBS24DataFake -fake &> output/DataFake_FBS24.log

#./Templater -in /data/Shared/TupleProd_Dec15/RDS/Data_S24_RDS_FromTauMu.root -trueds -conf config/config_LowBins.txt -flag FBS24DsTrueComb -fake &> output/DsTrueComb_FBS24.log

#./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BdDstDs.root  -conf config/config_LowBins.txt -flag FBS24BdDstDs -mc &> output/BdDstDs_FBS24.log 
#./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/BuD0Ds.root   -conf config/config_LowBins.txt -flag FBS24BuD0Ds -mc &> output/BuD0Ds_FBS24.log 
#./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/LbLcDs.root   -conf config/config_LowBins.txt -flag FBS24LbLcDs -mc &> output/LbLcDs_FBS24.log  
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/DoubleCharm.root -conf config/config_LowBins.txt -flag FBS24DoubleCharm -mc &> output/DoubleCharm_FBS24.log
./Templater -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/Data_S24_RDS_FromTauMu.root -conf config/config_LowBins.txt -flag FBS24SideBands -side &> output/SideBands_FBS24.log
./Templater -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/Data_S24_RDS_FromTauMu.root -ss -conf config/config_LowBins.txt -flag FBS24SameSide &> output/SameSide_FBS24.log



# ./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/Signal.root   -conf config/config_LowBins.txt -flag FBS24SignalAll -mc &> output/SignalAll_FBS24.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/Signal.root   -conf config/config_LowBins.txt -flag FBS24Signal_Bs0DsMu -mc -mat 1 &> output/Signal_Bs0DsMu_FBS24.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/Signal.root   -conf config/config_LowBins.txt -flag FBS24Signal_Bs0DstaMu -mc -mat 2 &> output/Signal_Bs0DstaMu_FBS24.log
# ./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/Signal.root   -conf config/config_LowBins.txt -flag FBS24Signal_Bs0Ds2460Mu -mc -mat 3 &> output/Signal_Bs0Ds2460Mu_FBS24.log
# ./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/Signal.root   -conf config/config_LowBins.txt -flag FBS24Signal_Bs0Ds2536Mu -mc -mat 4 &> output/Signal_Bs0Ds2536Mu_FBS24.log
./Templater -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/Signal.root   -conf config/config_LowBins.txt -flag FBS24Signal_Bs0Ds0staMu -mc -mat 5 &> output/Signal_Bs0Ds0staMu_FBS24.log

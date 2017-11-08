#./FullFit -in /data/Shared/TupleProd_Dec15/RDS/DataFake.root -flag DataTest -conf FB_PhiP  -cfg config/config_LowBins_PhiPi.txt

#./FullFit -in /data/Shared/TupleProd_Dec15/RDS/DataFake.root -flag DataTest -conf FBDef  -cfg config/config_LowBins.txt
#./FullFit -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/Data_S24_RDS_FromTauMu.root -flag DataS24SideBand -conf FBS24  -cfg config/config_LowBins.txt

./FullFit -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/Data_S24_RDS_FromTauMu.root -flag DataS24SameSign -conf FBS24  -cfg config/config_LowBins.txt &> output/SameSign_BkgDataSB.log

./FullFit -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/Data_S24_RDS_FromTauMu.root -flag DataS24SameSign -conf Trig24  -cfg config/config_LowBins.txt -ss &> output/SameSign_BkgDataSS.log


./FullFit -in /data/Shared/TupleProd_Dec15/Data_WithDsVetoes/DataAN_S24_RDS_FromTauMu.root -flag DataANSS -conf SmaDOneT -cfg config/config_LowBins.txt -ss &> output/DataANSS_SmaDOneT.log

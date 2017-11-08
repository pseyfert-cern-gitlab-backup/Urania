#./FullFit -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/Signal.root -flag MCCheck -conf TrigxsS24  -cfg config/config_LowBins.txt &> output/MCCocktailTest.log

./FullFit -in /data/Shared/TupleProd_Dec15/MC_WithDsVetoes/Signal.root -sigO -flag MCCheckSigO -conf Trig24  -cfg config/config_LowBins.txt &> output/MCCocktailTest_SigO.log

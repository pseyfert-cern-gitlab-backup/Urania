#! /bin/tcsh
source /data/lhcb/sw/scripts/lbsetup.csh
SetupErasmus
foreach chrg (Pos Neg)
$CALIBDATASCRIPTSROOT/$CMTCONFIG/CharmXsec_KaonTuple.exe $1 0 49 0 $chrg
sleep 3
$CALIBDATASCRIPTSROOT/$CMTCONFIG/CharmXsec_KaonTuple.exe $1 50 99 1 $chrg
sleep 3
$CALIBDATASCRIPTSROOT/$CMTCONFIG/CharmXsec_KaonTuple.exe $1 100 149 2 $chrg
sleep 3
$CALIBDATASCRIPTSROOT/$CMTCONFIG/CharmXsec_KaonTuple.exe $1 150 199 3 $chrg
sleep 3
$CALIBDATASCRIPTSROOT/$CMTCONFIG/CharmXsec_KaonTuple.exe $1 200 249 4 $chrg
sleep 3
$CALIBDATASCRIPTSROOT/$CMTCONFIG/CharmXsec_KaonTuple.exe $1 250 260 5 $chrg
end

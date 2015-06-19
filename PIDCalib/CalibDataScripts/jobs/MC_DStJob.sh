#! /bin/sh

#source /data/lhcb/sw/scripts/lbsetup.sh
#SetupErasmus

ganga_ID=$1
field_pol=$2
postfix=$3 

for partName in K Pi
do
  echo "$ganga_ID $partName $field_pol Strip${postfix}_0"
  $CALIBDATASCRIPTSROOT/$CMTCONFIG/MC_DStFit.exe $ganga_ID $partName $field_pol Strip${postfix}_0 
  sleep 3
  $CALIBDATASCRIPTSROOT/$CMTCONFIG/MergeCharges.exe DSt $PWD $partName $field_pol $postfix $PWD 0
  sleep 3
done
#! /bin/sh
source /data/lhcb/sw/scripts/lbsetup.sh
SetupErasmus v6r1

#==================================================
# Buffer Up Command Line Arguments
#==================================================
polarity="$1"
ganga_id="$2"
n_subjobs="$3"

#==================================================
# Loop over all JobIDs
#==================================================
for (( n = 0; n < $n_subjobs; n++))
do
  echo $polarity $d0_mode $ganga_id $n_subjobs $n
  $PIDPERFSCRIPTSROOT/$CMTCONFIG/B2DstarX_PerfCalc.exe $ganga_id $polarity $n  
done

if [ "$polarity" = "Down" ] 
then
    python $PIDPERFSCRIPTSROOT/python/B2DstarX/WeightedAveragePIDEffs.py 0 $n_subjobs
elif [ "$polarity" = "Up" ]
then
    python $PIDPERFSCRIPTSROOT/python/B2DstarX/WeightedAveragePIDEffs.py $n_subjobs 0
fi


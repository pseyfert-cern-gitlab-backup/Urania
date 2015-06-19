#! /bin/sh
source /data/lhcb/sw/scripts/lbsetup.sh
SetupErasmus v6r0

#==================================================
# Buffer Up Command Line Arguments
#==================================================
polarity="$1"
d0_mode="$2"
ganga_id="$3"
n_subjobs="$4"

#==================================================
# Loop over all JobIDs
#==================================================
for (( n = 0; n < $n_subjobs; n++))
do
  echo $polarity $d0_mode $ganga_id $n_subjobs $n
  $PIDPERFSCRIPTSROOT/$CMTCONFIG/B2DX_PerfCalc_ProbNN.exe $ganga_id $polarity $d0_mode $n  
done

if [ "$polarity" = "Down" ] 
then
    python $PIDPERFSCRIPTSROOT/python/B2DX/WeightedAveragePIDEffs.py $d0_mode 0 $n_subjobs
elif [ "$polarity" = "Up" ]
then
    python $PIDPERFSCRIPTSROOT/python/B2DX/WeightedAveragePIDEffs.py $d0_mode $n_subjobs 0
fi

#declare -a gangaID_dict=('21' '16' '17' '22' '20')

#==================================================
# Buffer Up First Two Command Line Arguments
#==================================================
#polarity="$1"
#d0_mode="$2"

#==================================================
# Shift over to list of Job IDs
#==================================================
#shift 2
#echo "Job IDs: " "$@"
#tot="$#"
#for (( j=0; j <$tot; j++ ))
#do
##  echo $j "$1" "$#"
#  gangaID_dict[j]="$1"
#  shift
#done

#==================================================
# Loop over all JobIDs
#==================================================
#for (( n = 0; n < ${#gangaID_dict[@]}; n++))
#do
#  #echo $n ${gangaID_dict[$n]}
#  echo ${gangaID_dict[$n]} $polarity $d0_mode $n
#  $PIDPERFSCRIPTSROOT/$CMTCONFIG/B2DX_PerfCalc.exe ${gangaID_dict[$n]} $polarity $d0_mode $n  
#done
#
#if [ "$polarity" = "Down" ] 
#then
#    python $PIDPERFSCRIPTSROOT/python/B2DX/WeightedAveragePIDEffs.py $2 0 $3
#elif [ "$polarity" = "Up" ]
#then
#    python $PIDPERFSCRIPTSROOT/python/B2DX/WeightedAveragePIDEffs.py $2 $3 0
#fi

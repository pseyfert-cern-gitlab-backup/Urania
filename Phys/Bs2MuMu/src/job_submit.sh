#!/bin/bash
# ./job_submit.sh 0 0 1 10 a -C 

BS=$1
BD=$2
VAR=$3
BIN=$4
TRIAL=$5
CONS=$6
NAME="tmp_job_"$BS"_"$BD"_"$VAR"_"$BIN"_"$TRIAL$CONS".sh"
echo "file name"$NAME
cat > $NAME  <<EOF
#!/bin/bash



. /afs/cern.ch/sw/lcg/external/gcc/4.3.5/x86_64-slc5/setup.sh
. /afs/cern.ch/sw/lcg/app/releases/ROOT/5.34.00-rc1/x86_64-slc5-gcc43-opt/root/bin/thisroot.sh

/afs/cern.ch/user/f/fdettori/cmtuser/Erasmus_v6r1/Phys/Bs2MuMu/src/calca -b -bs $BS -bd $BD -var $VAR  -bin $BIN -trial $TRIAL $CONS
EOF

chmod +x $NAME

bsub -q 1nw $NAME

echo "Submitted job "$NAME 

#rm $NAME










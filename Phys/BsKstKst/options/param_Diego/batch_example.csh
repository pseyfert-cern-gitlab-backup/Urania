#!/bin/csh

source $LBSCRIPTS_HOME/LbConfiguration/scripts/LbLogin.csh

¡¡

SetupProject Erasmus

python -V

python $HOME/vol5/ks/kslimit.py $1

## (el $1 es un argumento a mayores, pej una seed)

## Para submitir:
## bsub -q <la cola, tipicamende 2nd esta bien>   blablabla.csh

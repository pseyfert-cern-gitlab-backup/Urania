#!/bin/csh -f

#
# Script to send python sFit toys script
#
    
# -- 2011 neg
echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2011_neg_bin0.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2011_neg_bin0.job
echo  "python fitMassAddsWeights.py 0 2011 neg AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2011_neg_bin0.out" >> jobs/fitMassAddsWeight_2011_neg_bin0.job
chmod a+x jobs/fitMassAddsWeight_2011_neg_bin0.job
./jobs/fitMassAddsWeight_2011_neg_bin0.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2011_neg_bin1.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2011_neg_bin1.job
echo  "python fitMassAddsWeights.py 1 2011 neg AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2011_neg_bin1.out" >> jobs/fitMassAddsWeight_2011_neg_bin1.job
chmod a+x jobs/fitMassAddsWeight_2011_neg_bin1.job
./jobs/fitMassAddsWeight_2011_neg_bin1.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2011_neg_bin2.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2011_neg_bin2.job
echo  "python fitMassAddsWeights.py 2 2011 neg AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2011_neg_bin2.out" >> jobs/fitMassAddsWeight_2011_neg_bin2.job
chmod a+x jobs/fitMassAddsWeight_2011_neg_bin2.job
./jobs/fitMassAddsWeight_2011_neg_bin2.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2011_neg_bin3.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2011_neg_bin3.job
echo  "python fitMassAddsWeights.py 3 2011 neg AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2011_neg_bin3.out" >> jobs/fitMassAddsWeight_2011_neg_bin3.job
chmod a+x jobs/fitMassAddsWeight_2011_neg_bin3.job
./jobs/fitMassAddsWeight_2011_neg_bin3.job

# -- 2011 pos
echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2011_pos_bin0.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2011_pos_bin0.job
echo  "python fitMassAddsWeights.py 0 2011 pos AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2011_pos_bin0.out" >> jobs/fitMassAddsWeight_2011_pos_bin0.job
chmod a+x jobs/fitMassAddsWeight_2011_pos_bin0.job
./jobs/fitMassAddsWeight_2011_pos_bin0.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2011_pos_bin1.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2011_pos_bin1.job
echo  "python fitMassAddsWeights.py 1 2011 pos AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2011_pos_bin1.out" >> jobs/fitMassAddsWeight_2011_pos_bin1.job
chmod a+x jobs/fitMassAddsWeight_2011_pos_bin1.job
./jobs/fitMassAddsWeight_2011_pos_bin1.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2011_pos_bin2.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2011_pos_bin2.job
echo  "python fitMassAddsWeights.py 2 2011 pos AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2011_pos_bin2.out" >> jobs/fitMassAddsWeight_2011_pos_bin2.job
chmod a+x jobs/fitMassAddsWeight_2011_pos_bin2.job
./jobs/fitMassAddsWeight_2011_pos_bin2.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2011_pos_bin3.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2011_pos_bin3.job
echo  "python fitMassAddsWeights.py 3 2011 pos AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2011_pos_bin3.out" >> jobs/fitMassAddsWeight_2011_pos_bin3.job
chmod a+x jobs/fitMassAddsWeight_2011_pos_bin3.job
./jobs/fitMassAddsWeight_2011_pos_bin3.job

# -- 2012 neg
echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2012_neg_bin0.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2012_neg_bin0.job
echo  "python fitMassAddsWeights.py 0 2012 neg AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2012_neg_bin0.out" >> jobs/fitMassAddsWeight_2012_neg_bin0.job
chmod a+x jobs/fitMassAddsWeight_2012_neg_bin0.job
./jobs/fitMassAddsWeight_2012_neg_bin0.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2012_neg_bin1.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2012_neg_bin1.job
echo  "python fitMassAddsWeights.py 1 2012 neg AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2012_neg_bin1.out" >> jobs/fitMassAddsWeight_2012_neg_bin1.job
chmod a+x jobs/fitMassAddsWeight_2012_neg_bin1.job
./jobs/fitMassAddsWeight_2012_neg_bin1.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2012_neg_bin2.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2012_neg_bin2.job
echo  "python fitMassAddsWeights.py 2 2012 neg AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2012_neg_bin2.out" >> jobs/fitMassAddsWeight_2012_neg_bin2.job
chmod a+x jobs/fitMassAddsWeight_2012_neg_bin2.job
./jobs/fitMassAddsWeight_2012_neg_bin2.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2012_neg_bin3.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2012_neg_bin3.job
echo  "python fitMassAddsWeights.py 3 2012 neg AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2012_neg_bin3.out" >> jobs/fitMassAddsWeight_2012_neg_bin3.job
chmod a+x jobs/fitMassAddsWeight_2012_neg_bin3.job
./jobs/fitMassAddsWeight_2012_neg_bin3.job

# -- 2012 pos
echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2012_pos_bin0.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2012_pos_bin0.job
echo  "python fitMassAddsWeights.py 0 2012 pos AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2012_pos_bin0.out" >> jobs/fitMassAddsWeight_2012_pos_bin0.job
chmod a+x jobs/fitMassAddsWeight_2012_pos_bin0.job
./jobs/fitMassAddsWeight_2012_pos_bin0.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2012_pos_bin1.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2012_pos_bin1.job
echo  "python fitMassAddsWeights.py 1 2012 pos AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2012_pos_bin1.out" >> jobs/fitMassAddsWeight_2012_pos_bin1.job
chmod a+x jobs/fitMassAddsWeight_2012_pos_bin1.job
./jobs/fitMassAddsWeight_2012_pos_bin1.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2012_pos_bin2.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2012_pos_bin2.job
echo  "python fitMassAddsWeights.py 2 2012 pos AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2012_pos_bin2.out" >> jobs/fitMassAddsWeight_2012_pos_bin2.job
chmod a+x jobs/fitMassAddsWeight_2012_pos_bin2.job
./jobs/fitMassAddsWeight_2012_pos_bin2.job

echo "#\!/bin/tcsh"   >! jobs/fitMassAddsWeight_2012_pos_bin3.job
echo "cd ${PWD}"      >> jobs/fitMassAddsWeight_2012_pos_bin3.job
echo  "python fitMassAddsWeights.py 3 2012 pos AddsWeight >! jobs/OutPuts/fitMassAddsWeight_2012_pos_bin3.out" >> jobs/fitMassAddsWeight_2012_pos_bin3.job
chmod a+x jobs/fitMassAddsWeight_2012_pos_bin3.job
./jobs/fitMassAddsWeight_2012_pos_bin3.job


 

. NBVars.sh

make

echo "viewing Patrick's Castor directory"

rfdir /castor/cern.ch/user/p/pkoppenb/Lambdab

echo "sleeping for 10 seconds"

sleep 10

echo "starting teacher on Lambdab2Jpsippi-MC11a-Psippi-521.root and Lambdab2Jpsippi-MC11a-IncPsi-501.root"

./teacher.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab2Jpsippi-MC11a-Psippi-521.root  /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab2Jpsippi-MC11a-IncPsi-501.root  | tee test-teach

echo "sleeping for 10 seconds"

sleep 10

echo "starting expert on Lambdab2Jpsippi-MC11a-Psippi-521.root"

./expert.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab2Jpsippi-MC11a-Psippi-521.root | tee test-expert

echo "sleeping for 10 seconds"

sleep 10

echo "starting expert on Lambdab2Jpsippi-MC11a-IncPsi-501.root"

./expert.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab2Jpsippi-MC11a-IncPsi-501.root | tee test-expert

echo "sleeping for 10 seconds"

sleep 10

echo "starting expert on Lambdab2Jpsippi-MC11a-PsiKpi-523.root"

./expert.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab2Jpsippi-MC11a-PsiKpi-523.root | tee test-expert

echo "sleeping for 10 seconds"

sleep 10

echo "starting expert on Lambdab2Jpsippi-MC11a-PsiKstar-522.root"

 ./expert.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab2Jpsippi-MC11a-Bd2JpsiKstar-627.root | tee test-expert

echo "sleeping for 10 seconds"

sleep 10

echo "starting expert on Lambdab2Jpsippi-MC11a-PsipK-516.root"

./expert.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab2Jpsippi-MC11a-PsipK-516.root | tee test-expert

 echo "sleeping for 10 seconds"

 sleep 10

 echo "starting expert on Lambdab-R12S17b-435-436.root"

./expert.exe /castor/cern.ch/user/p/pkoppenb/Lambdab/Lambdab-R12S17b-435-436.root | tee test-expert

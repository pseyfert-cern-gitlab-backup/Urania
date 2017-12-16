#include "iostream"
#include "TFile.h"
#include "TTree.h"
#include "useTMVAntuple.h"
#include <math.h>       /* sqrt */


int main(int argc, char** argv) {
  if (argc!=2) {
    std::cout << "USAGE " << argv[0] << " TMVAfile.root" << std::endl;
    return 1;
  }
  TTree* train;
  TTree* test;
  TFile* ff = new TFile(argv[1],"read");
  if (0==ff) {
    std::cout << "couldn't open file" << std::endl;
    return 2;
  }
  ff->GetObject("TestTree",test);
  ff->GetObject("TrainTree",train);
  useTMVAntuple dup(train,test);
  std::cout << " overtraining on signal ..." << std::endl;
  float d = dup.delta_signal();
  //float kalpha = 1.22; // 90%CL
  float kalpha = 1.36; // 95%CL
  //float kalpha = 1.63; // 99%CL
  float kmax = sqrt((dup.sumoftestsq()+dup.sumoftrainsq())/(dup.sumoftest()*dup.sumoftrain()))*kalpha;
  std::cout << " overtraining on signal: " << d << "\t\t" << "overtrained if > " << kmax << std::endl;
  std::cout << " overtraining on background " << std::endl;
  d = dup.delta_background();
  kmax = sqrt((dup.sumoftestsq()+dup.sumoftrainsq())/(dup.sumoftest()*dup.sumoftrain()))*kalpha;
  std::cout << " overtraining on background: " << d << "\t\t" << "overtrained if > " << kmax << std::endl;

  return 0;


}

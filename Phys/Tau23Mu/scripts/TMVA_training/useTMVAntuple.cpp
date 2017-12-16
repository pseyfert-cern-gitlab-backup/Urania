#include "useTMVAntuple.h"
#include <algorithm>    // std::sort
#include <vector>       // std::vector

float sq(float x) {
  return x*x;
}

bool myfunc(std::pair<float,float> a, std::pair<float,float> b) {
  return a.first<b.first;
}

float useTMVAntuple::delta(int classid) {
  m_sumoftest=0.f;
  m_sumoftestsq=0.f;
  m_sumoftrain=0.f;
  m_sumoftrainsq=0.f;
  Long64_t nentries = t_train.fChain->GetEntriesFast();
  for (Long64_t entry = 0 ; entry < nentries ; ++entry) {
    t_train.GetEntry(entry);
    if (t_train.classID!=classid) continue;
    add_train(t_train.weight);
  }
  nentries = t_test.fChain->GetEntriesFast();
  for (Long64_t entry = 0 ; entry < nentries ; ++entry) {
    t_test.GetEntry(entry);
    if (t_test.classID!=classid) continue;
    add_test(t_test.weight);
  }
  std::vector<std::pair< float, float > > buffer; ///response, weight
  buffer.clear();
  buffer.reserve(t_train.fChain->GetEntriesFast()+t_test.fChain->GetEntriesFast());
  nentries = t_train.fChain->GetEntriesFast();
  for (Long64_t entry = 0 ; entry < nentries ; ++entry) {
    t_train.GetEntry(entry);
    if (t_train.classID!=classid) continue;
    buffer.push_back(std::pair<float,float>(t_train.MLPCJ,t_train.weight/sumoftrain()));
  }
  nentries = t_test.fChain->GetEntriesFast();
  for (Long64_t entry = 0 ; entry < nentries ; ++entry) {
    t_test.GetEntry(entry);
    if (t_test.classID!=classid) continue;
    buffer.push_back(std::pair<float,float>(t_test.MLPCJ,-t_test.weight/sumoftest()));
  }
  std::sort(buffer.begin(), buffer.end(), myfunc);
  float max(0.f);
  float min(0.f);
  float running(0.f);
  for (unsigned k = 0 ; k < buffer.size() ; ++k) {
    running+=buffer[k].second;
    if (running>max) max = running;
    if (running<min) min = running;
  }
  return std::max(max,-min);
}

float useTMVAntuple::delta_signal() {
  return useTMVAntuple::delta(0);
}

float useTMVAntuple::delta_background() {
  return useTMVAntuple::delta(1);
}

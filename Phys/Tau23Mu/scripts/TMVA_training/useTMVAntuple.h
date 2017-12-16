#ifndef USETMVANTUPLE
#define USETMVANTUPLE 1

#include "TMVAntuple.h"

class useTMVAntuple {
  public:
    TMVAntuple t_test;
    TMVAntuple t_train;
    float delta_signal();
    float delta_background();
    float delta(int classid);
    useTMVAntuple(TTree* train, TTree* test) : t_test(test), t_train(train), m_sumoftestsq(0.), m_sumoftrainsq(0.), m_sumoftest(0.), m_sumoftrain(0.) {};
    float sumoftest() {return m_sumoftest;};
    float sumoftrain() {return m_sumoftrain;};
    float sumoftestsq() {return m_sumoftestsq;};
    float sumoftrainsq() {return m_sumoftrainsq;};
    float m_sumoftest;
    float m_sumoftrain;
    float m_sumoftestsq;
    float m_sumoftrainsq;
    void add_test(float x) {m_sumoftest+=x;m_sumoftestsq+=x*x;return;};
    void add_train(float x) {m_sumoftrain+=x;m_sumoftrainsq+=x*x;return;};
};

#endif

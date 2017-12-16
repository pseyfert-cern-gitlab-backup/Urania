#include "deltaLQ.h"
#include "logstream.h"
#include <iostream>
#include "TChain.h"

int main() {
  logstreams::logstream::setLogLevel(1);
  binning b(+0.f,1.f,19u,5u,"GeoMVA");
  binning d(+0.f,1.f,19u,5u,"GeoMVA");
  binning c(+0.f,3.f,19u,5u,"GeoMVA");
  if (d==b) {
    std::cout << "jaha" << std::endl;
  } else {
    std::cout << "neien" << std::endl;
  }
   if (c==b) {
    std::cout << "jaha" << std::endl;
  } else {
    std::cout << "neien" << std::endl;
  }
  return 0;
}

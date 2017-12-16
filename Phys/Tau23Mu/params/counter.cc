#include "limit_interface.h"
#include <stdlib.h>
#include <iostream>


int main(int argc, char** argv) {
  limit_interface* li = new limit_interface();
  std::cout << li->the_geobins() << std::endl;
  return 0;
}

//test function
#include "util.h"
#include <iostream>
int main(int argn,char ** argv) {
  if(argn != 2) {
    std::cout<<"wrong number of arguments\n";
    return -1;
  }
  auto m = file_tobuf(argv[1]);
  if(m == NULL) {
    std::cout<<"file no exists\n";
    return -1;
  }
  std::cout<<m->size()<<std::endl;
  return 0;
}

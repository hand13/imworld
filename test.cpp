//test function
#include "bg.h"
#include <iostream>
#include <fmt/format.h>
class Runner { 
  public:
    DualBuffer * buffer;
  public:
    Runner(DualBuffer *m) : buffer(m) { } 
    void operator()() { 
      for(int i =0;i<10;i++) {
        buffer->render();
        buffer->swap();
        boost::this_thread::sleep(boost::posix_time::microsec(40));
      }
    } 
}; 
int main() {
  boost::mutex mutex;
  DualBuffer b(128,&mutex);
  Runner r(&b);
  boost::thread t(r);
  while(true) {
    mutex.lock();
    fmt::print("the word is {}\n",(const char *)b.getFront());
    mutex.unlock();
    boost::this_thread::sleep(boost::posix_time::microsec(15));
  }
  return 0;
}

#ifndef BG_H
#define BH_H
#include <vector>
#include <string>
#include <boost/thread.hpp>
class DualBuffer{
  private:
    void * front;
    void * back;
    std::vector<std::string> words;
    unsigned int point;
    boost::mutex * mutex;
  public:
    DualBuffer(size_t size,boost::mutex * mutex);
    ~DualBuffer();
    void * getFront();
    void swap();
    virtual void render();
};
#endif

#ifndef BG_H
#define BH_H
#include <vector>
#include <string>
#include <boost/thread.hpp>
class DualBuffer{
  protected:
    void * front;
    boost::mutex * mutex;
    void * back;
  public:
    DualBuffer(boost::mutex * mutex);
    virtual ~DualBuffer();
    void * getFront();
    void swap();
    virtual void render() = 0;
};
class BarBuffer:public DualBuffer{
  private:
    unsigned int index;
  public:
    BarBuffer(boost::mutex * m);
    virtual ~BarBuffer();
    virtual void render();
};
#endif

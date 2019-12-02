#include <memory>
#include "bg.h"
#include <cmath>
#define PI 3.14159
void * DualBuffer::getFront() {
  return this->front;
}
void DualBuffer::swap() {
  this->mutex->lock();
  auto tmp = this->front;
  this->front = this->back;
  this->back = tmp;
  this->mutex->unlock();
}
DualBuffer::DualBuffer(boost::mutex * mutex) {
  this->mutex = mutex;
  this->front = NULL;
  this->back = NULL;
}
DualBuffer::~DualBuffer() {
}
BarBuffer::BarBuffer(boost::mutex * mutex):DualBuffer(mutex){
  this->back = (double *)std::malloc(20 * sizeof(double));
  this->front = (double *)std::malloc(20 * sizeof(double));
  this->index = 0;
}
void BarBuffer::render() {
  auto det = index /100.0 * PI;
  this->mutex->lock();
  for(int j=0;j<20;j++) {
    ((double*)this->back)[j]  = 100*std::sin(j * 2 * PI/20 + det);
  }
  this->mutex->unlock();
  index++;
}
BarBuffer::~BarBuffer(){
  DualBuffer::~DualBuffer();
  if(this->front != NULL) {
    std::free(this->front);
  }
  if(this->back != NULL) {
    std::free(this->back);
  }
}

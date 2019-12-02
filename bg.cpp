#include <memory>
#include "bg.h"
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
  this->index = 0;
  this->reversed = false;
  for(int i=0;i< 100;i++) {
    double * m = (double *)std::malloc(12 * sizeof(double));
    std::memset(m,0,12 * sizeof(double));
    for(int j=0;j<12;j++) {
      m[j] = i + j*5;
    }
    data.push_back(m);
  }
}
void BarBuffer::render() {
  auto word = this->data[this->index];
  this->mutex->lock();
  this->back = word;
  this->mutex->unlock();
  if(this->index == this->data.size()-1) {
    this->reversed = true;
  }
  if(this->index == 0 && reversed) {
    this->reversed = false;
  }
  if(reversed) {
    this->index--;
  }else {
    this->index++;
  }
}
BarBuffer::~BarBuffer(){
  DualBuffer::~DualBuffer();
  for(auto m : data) {
    free(m);
  }
}

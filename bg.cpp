#include <memory>
#include "bg.h"
#define SIZE 10
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
void DualBuffer::render() {
  auto word = words[this->point];
  this->mutex->lock();
  std::memcpy(this->back,word.c_str(),word.size());
  this->mutex->unlock();
  this->point++;
  if(this->point == words.size()) {
    this->point = 0;
  }
}
DualBuffer::DualBuffer(size_t size,boost::mutex * mutex) {
  this->mutex = mutex;
  front = std::malloc(size);
  std::memset(front,0,size);
  back = std::malloc(size);
  std::memset(back,0,size);
  point = 0;
  for(int i =0;i<SIZE;i++) {
    words.push_back(std::string("hello") + std::to_string(i));
  }
}
DualBuffer::~DualBuffer() {
  std::free(front);
  std::free(back);
}

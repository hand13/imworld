#include <windows.h>
#include "util.h"
#include <fmt/format.h>
#include <fstream>
#define BUFFER_SIZE 1024
std::vector<PROCESSENTRY32> getpe32s() {
  std::vector<PROCESSENTRY32> outcome;
  PROCESSENTRY32 pe32;
  pe32.dwSize = sizeof(pe32);
  HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,NULL);
  if(snap == INVALID_HANDLE_VALUE) {  
    fmt::print("CreateToolhelp32Snapshot Error!\n");
 }  
  BOOL result;
  result = Process32First(snap,&pe32);
  if(!result) {
    fmt::print("no such process\n");
    fmt::print("result is{}\n snap is {}\n errorcode is {}",result,snap,GetLastError());
    return outcome;
  }
  outcome.push_back(pe32);
  while(Process32Next(snap,&pe32)) {
    outcome.push_back(pe32);
  }
  CloseHandle(snap);
  return outcome;
}

HLOCAL getErrorMessage(DWORD err){
  DWORD systemLocale = MAKELANGID(LANG_NEUTRAL,SUBLANG_NEUTRAL);
  HLOCAL hLocal = NULL;
  BOOL fOk = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM|FORMAT_MESSAGE_IGNORE_INSERTS|
      FORMAT_MESSAGE_ALLOCATE_BUFFER,NULL,err,systemLocale,(PTSTR)&hLocal,0,NULL);
  if(fOk) {
    return hLocal;
  }else {
    return NULL;
  }
}
void freeMessage(HLOCAL msg) {
  if(msg != NULL) {
    LocalFree(msg);
  }
}
memory_buffer * file_tobuf(const char * path){
  auto result = new memory_buffer(0,0);
  std::ifstream inf;
  inf.open(path,std::ios::binary);
  if(!inf){
    delete result;
    return NULL;
  }
  char buffer[BUFFER_SIZE];
  std::memset(buffer,0,BUFFER_SIZE);
  while(!inf.eof()) {
    int len = inf.read(buffer,BUFFER_SIZE).gcount();
    if(len != 0) {
      result->inc_buffer(buffer,len);
    }
  }
  return result;
}

bool memory_buffer::inc_buffer(void * buffer,int buf_len) {
  if(buf_len > 0) {
    auto tot_len = this->length + buf_len;
    this->buffer_address = (unsigned char*)std::realloc(this->buffer_address,tot_len);
    if(this->buffer_address == NULL) {
      return false;
    }
    std::memcpy((char*)this->buffer_address + this->length,buffer,buf_len);
    this->length = tot_len;
  }
  return true;
}
memory_buffer::memory_buffer() {
  this->length = 0;
  this->buffer_address = NULL;
}
void memory_buffer::release() {
  this->length = 0;
  if(this->buffer_address != NULL) {
    std::free(this->buffer_address);
    this->buffer_address = 0;
  }
}
 memory_buffer::memory_buffer(int length,void * add){
  this->length = length;
  this->buffer_address = add;
}
int memory_buffer::size() {
  return this->length;
}
void * memory_buffer::memory() {
  return this->buffer_address;
}
memory_buffer::~memory_buffer() {
  //this->release();
}
static const char * hex_table = "0123456789ABCDEF";
char fb_tohex(char m) {
  return hex_table[(int)m];
}

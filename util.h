#ifndef UTIL_H
#define UTIL_H
#include <vector>
#include <memory>
#include <windows.h>
#include <tlhelp32.h>
std::vector<PROCESSENTRY32> getpe32s();
HLOCAL getErrorMessage(DWORD err);
void freeMessage(HLOCAL msg);
class memory_buffer{
  private:
    int length;
    void * buffer_address;
  public:
    memory_buffer(int len,void * add);
    bool inc_buffer(void * buffer,int len);
    int size();
    void * memory();
    ~memory_buffer();
};
memory_buffer * file_tobuf(const char * path);
char fb_tohex(char m);
#endif

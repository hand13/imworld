#ifndef MYPAINT_H
#define MYPAINT_H
#include <windows.h>
#include "util.h"
struct Pair{
  void * fst;
  void * snd;
};
void drawMain(struct Pair * data);
class MemoryDrawer{
  private:
    memory_buffer  data;
    std::vector<std::shared_ptr<char> > assembled_data;
    void assemble();
    bool load_memory(char * path);
  public:
    bool fresh_memory(char * path);
    void draw_memory();
    ~MemoryDrawer();
};
#endif

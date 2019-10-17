#ifndef MYLUA_H
#define MYLUA_H
extern "C"{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}
#include <windows.h>
class lua_machine{
  private :
    lua_State * L;
    int machine_state; 
  public:
    lua_machine();
    int do_file(char * file);
    void close();
    ~lua_machine();
};
lua_State * init_lua();
//lib
int fun(lua_State *L);
//
#endif

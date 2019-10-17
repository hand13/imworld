#include "mylua.h"
int fun(lua_State * L) {
  ::MessageBox(NULL,TEXT("few"),TEXT("few"),MB_OK);
  return 1;
}
static luaL_Reg mylibs[] ={
  {"fun",fun},
  {NULL,NULL}
};
lua_State * init_lua() {
  lua_State * L = luaL_newstate();
  lua_gc(L,LUA_GCSTOP,0);
  luaL_openlibs(L);
  lua_gc(L,LUA_GCRESTART,0);
  luaL_register(L,"mylib",mylibs);
  return L;
}
lua_machine::lua_machine() {
  lua_State * L = init_lua();
  this->L = L;
}
lua_machine::~lua_machine() {
  this->close();
}
void lua_machine::close() {
  lua_close(L);
  machine_state = -1;
}
int lua_machine::do_file(char * file) {
  int state = luaL_dofile(this->L,file);
  return state;
}

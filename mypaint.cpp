#include "mypaint.h"
#include "imgui.h"
#include <windows.h>
#include <vector>
#include <fmt/format.h>
#include <memory>
#include "util.h"
#include <fstream>
#define BUFFER_SIZE (1024)
static char buffer[128] = {0};
static memory_buffer * mem_buffer = NULL;
static std::vector<std::shared_ptr<char> > to;
static std::vector<std::shared_ptr<char> > assemble(memory_buffer * buffer);
static void load_memory(char * path);
static ImDrawList* draw_list = NULL;
void drawMain() {
  draw_list = ImGui::GetWindowDrawList();
  static boolean showfile = false;
  if(ImGui::BeginMenu("file")) {
    if(ImGui::MenuItem("open","Ctrl+O")){
      MessageBox(NULL,TEXT("don't touch me"),TEXT("fuck"),MB_OK);
    }
    if(ImGui::MenuItem("save","Ctrl+S")){}
    if(ImGui::MenuItem("close","Ctrl+Q")){
      ExitProcess(0);
    }
    ImGui::EndMenu();
  }
  ImGui::NewLine();
  if(ImGui::Button("touch")) {
    HLOCAL errMsg = getErrorMessage(GetLastError());
    MessageBox(NULL,reinterpret_cast<PTSTR>(errMsg),TEXT("你好"),MB_OK);
    freeMessage(errMsg);
  }
  ImGui::InputText("path",buffer,IM_ARRAYSIZE(buffer));
  ImGui::SameLine();
  if(ImGui::Button("execute")) {
    if(std::strlen(buffer) != 0) {
      showfile = true;
      load_memory(buffer);
      if(mem_buffer == NULL) {
        MessageBox(NULL,TEXT("文件不存在"),TEXT("title"),MB_OK);
        showfile = false;
      }else {
        to = assemble(mem_buffer);
      }
    }
  }
  ImGui::NewLine();
  if(showfile && mem_buffer != NULL) {
    ImGui::BeginChild("memory");
    int address = 0;
    for(auto m = to.begin();m< to.end();m++) {
      //地址
      ImGui::TextColored(ImVec4(1,0,0,1),"%08X",address);
      ImGui::SameLine();
      //数据
      ImGui::TextColored(ImVec4(0,1,0,1),"%s",m->get());
      ImGui::NewLine();
      address += 64;
    }
    ImGui::EndChild();
    ImGui::Text("file size is %d",mem_buffer->size());
  }
}
static void load_memory(char * path) {
    if(mem_buffer != NULL) {
      delete mem_buffer;
      mem_buffer = NULL;
    }
    mem_buffer = file_tobuf(path);
}
std::vector<std::shared_ptr<char> > assemble(memory_buffer * buffer) {
  std::vector<std::shared_ptr<char> > result;
  int cols = 64;
  int rows = buffer->size()/cols;
  int more = buffer->size() % cols;
  int cols_size = cols * 2 + 1 + (cols/4);
  for(int i =0;i<rows + 1;i++) {
    std::shared_ptr<char> tmp(new char[cols_size],std::default_delete<char[]>());
    int j,l = cols;
    if(i == rows) {
      if(more > 0) {
        l = more;
      }else {
        break;
      }
    }
    int point = 0;
    for(j =0;j<l;j++) {
      char value = ((unsigned char *)buffer->memory())[i * 20 + j];
      char fst = fb_tohex((value & 0xf0) >> 4);
      char snd = fb_tohex(value & 0x0f);
      tmp.get()[point] = fst;
      point++;
      tmp.get()[point] = snd;
      point++;
      if(((j+1) % 4) == 0) {
        tmp.get()[point] = ' ';
        point++;
      }
    }
    tmp.get()[point] = 0;
    result.push_back(tmp);
  }
  return result;
}

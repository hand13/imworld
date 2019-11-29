#include "mypaint.h"
#include "imgui.h"
#include <windows.h>
#include <vector>
#include <fmt/format.h>
#include <memory>
#include "util.h"
#include <fstream>
#include "imfilebrowser.h"
#define BUFFER_SIZE (1024)
static char buffer[128] = {0};
static ImDrawList* draw_list = NULL;
void drawMain() {
  static MemoryDrawer memoryDrawer;
  static ImGui::FileBrowser fileDialog;
  draw_list = ImGui::GetWindowDrawList();
  static boolean showMemory= false;
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
    fileDialog.Open();
  }
  ImGui::InputText("path",buffer,IM_ARRAYSIZE(buffer));
  ImGui::SameLine();
  if(ImGui::Button("execute")) {
    showMemory = memoryDrawer.fresh_memory(buffer);
    if(!showMemory) {
      MessageBox(NULL,TEXT("文件不存在"),TEXT("error occurs"),MB_OK);
    }
  }
  if(showMemory) {
    memoryDrawer.draw_memory();
  }
  fileDialog.Display();
  if(fileDialog.HasSelected()) {
    auto selected_path = fileDialog.GetSelected().string();
    std::memcpy(buffer,selected_path.c_str(),128);
    fileDialog.ClearSelected();
  }
}
bool MemoryDrawer::fresh_memory(char *path) {
  bool freshed = false;
  if(std::strlen(path) != 0) {
    if(load_memory(path)){
      this->assemble();
      freshed= true;
    }
  }
  return freshed;
}
void MemoryDrawer::draw_memory() {
  ImGui::NewLine();
  if(this->data.size()!= 0) {
    ImGui::BeginChild("memory");
    int address = 0;
    for(auto m = this->assembled_data.begin();m< this->assembled_data.end();m++) {
      //地址
      ImGui::TextColored(ImVec4(1,0,0,1),"%08X",address);
      ImGui::SameLine();
      //数据
      ImGui::TextColored(ImVec4(0,1,0,1),"%s",m->get());
      ImGui::NewLine();
      address += 64;
    }
    ImGui::EndChild();
    ImGui::Text("file size is %d",this->data.size());
  }
}
bool MemoryDrawer::load_memory(char * path) {
    this->data.release();
    return  file_tobuf(this->data,path);
}
MemoryDrawer::~MemoryDrawer() {
  this->data.release();
}
void MemoryDrawer::assemble() {
  std::vector<std::shared_ptr<char> > result;
  int cols = 64;
  int rows = this->data.size()/cols;
  int more = this->data.size() % cols;
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
      char value = ((unsigned char *)this->data.memory())[i * 20 + j];
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
  this->assembled_data = result;
}

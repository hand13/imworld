#include <windows.h>
#include "util.h"
#include <fmt/format.h>
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

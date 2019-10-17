#ifndef UTIL_H
#define UTIL_H
#include <vector>
#include <tlhelp32.h>
std::vector<PROCESSENTRY32> getpe32s();
#endif

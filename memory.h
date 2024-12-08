#ifndef _memory_h
#define _memory_h

#include <metamod_oslink.h>

#ifndef _WIN32
#include <dlfcn.h>
#endif

int GetOffset(const char* name);
void* GetSignature(const char* name);
void* AccessVTable(const char* module, const char* vTableName);

#endif
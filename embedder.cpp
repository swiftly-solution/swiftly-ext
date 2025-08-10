#include "embedder.h"
#include "files.h"

#include <metamod_oslink.h>
#ifndef _WIN32
#include <dlfcn.h>
#endif

void* GetDotnetPointer(int kind)
{
    void* ptr;
    HINSTANCE m_hModule;
#ifdef _WIN32
    m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
    if (!m_hModule) return nullptr;
#else
    m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
    if (!m_hModule) return nullptr;
#endif

    ptr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_GetDotnetPointer"));
    dlclose(m_hModule);
    return ptr;
}
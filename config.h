#include <any>
#include "files.h"

#include <metamod_oslink.h>

#ifndef _WIN32
#include <dlfcn.h>
#endif

typedef void* (*GetConfigVal)(const char*);

extern void* getConfValuePtr;

template <typename T>
T FetchConfigValue(const char* key)
{
    if(!getConfValuePtr) {
        HINSTANCE m_hModule;
        #ifdef _WIN32
            m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
        #else
            m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
            if(!m_hModule) return (T)0;
        #endif

        getConfValuePtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_GetConfigurationValue"));
        if(!getConfValuePtr) {
            dlclose(m_hModule);
            return (T)0;
        }

        dlclose(m_hModule);
    }

    std::any *val = (std::any*)reinterpret_cast<GetConfigVal>(getConfValuePtr)(key);
    if(val == nullptr) return (T)0;
    
    return std::any_cast<T>(*val);
}
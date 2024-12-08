#include <metamod_oslink.h>

#ifndef _WIN32
#include <dlfcn.h>
#endif

#include <any>

typedef void* (*GetConfigVal)(const char*);

extern void* getConfValuePtr;

template <typename T>
T FetchConfigValue(const char* key)
{
    if(!getConfValuePtr) {
        HINSTANCE m_hModule;
        #ifdef _WIN32
            m_hModule = dlmount("addons/swiftly/bin/win64/swiftly.dll");
        #else
            m_hModule = dlopen("addons/swiftly/bin/linuxsteamrt64/swiftly.so", RTLD_NOW);
            if(!m_hModule) return nullptr;
        #endif

        void* getConfValuePtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_GetConfigurationValue"));
        if(!getConfValuePtr) {
            dlclose(m_hModule);
            return (T)0;
        }
    }

    std::any *val = (std::any*)reinterpret_cast<GetConfigVal>(getConfValuePtr)(key);
    if(val == nullptr) return (T)0;
    
    return std::any_cast<T>(*val);
}
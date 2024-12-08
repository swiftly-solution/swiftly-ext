#include <metamod_oslink.h>

#ifndef _WIN32
#include <dlfcn.h>
#endif

typedef int (*GetOff)(const char*);
typedef void* (*GetSig)(const char*);
typedef void* (*AccVTable)(const char*, const char*);

void* offsetPtr = nullptr;
void* sigPtr = nullptr;
void* vtablePtr = nullptr;

int GetOffset(const char* name)
{
    if(!offsetPtr) {
        HINSTANCE m_hModule;
        #ifdef _WIN32
            m_hModule = dlmount("addons/swiftly/bin/win64/swiftly.dll");
        #else
            m_hModule = dlopen("addons/swiftly/bin/linuxsteamrt64/swiftly.so", RTLD_NOW);
            if(!m_hModule) return -1;
        #endif

        void* offsetPtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_GetOffset"));
        if(!offsetPtr) {
            dlclose(m_hModule);
            return -1;
        }
    }
    
    return reinterpret_cast<GetOff>(offsetPtr)(name);
}

void* GetSignature(const char* name)
{
    if(!sigPtr) {
        HINSTANCE m_hModule;
        #ifdef _WIN32
            m_hModule = dlmount("addons/swiftly/bin/win64/swiftly.dll");
        #else
            m_hModule = dlopen("addons/swiftly/bin/linuxsteamrt64/swiftly.so", RTLD_NOW);
            if(!m_hModule) return nullptr;
        #endif

        void* sigPtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_GetSignature"));
        if(!sigPtr) {
            dlclose(m_hModule);
            return nullptr;
        }
    }

    return reinterpret_cast<GetSig>(sigPtr)(name);
}

void* AccessVTable(const char* module, const char* vTableName)
{
    if(!vtablePtr) {
        HINSTANCE m_hModule;
        #ifdef _WIN32
            m_hModule = dlmount("addons/swiftly/bin/win64/swiftly.dll");
        #else
            m_hModule = dlopen("addons/swiftly/bin/linuxsteamrt64/swiftly.so", RTLD_NOW);
            if(!m_hModule) return nullptr;
        #endif

        void* vtablePtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_AccessVTable"));
        if(!vtablePtr) {
            dlclose(m_hModule);
            return nullptr;
        }
    }

    return reinterpret_cast<AccVTable>(vtablePtr)(module, vTableName);
}
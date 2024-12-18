#include "extension.h"
#include "files.h"

#include <metamod_oslink.h>

#ifndef _WIN32
#include <dlfcn.h>
#endif

typedef void* (*GetGES)();

CGameEntitySystem* ext = nullptr;

CGameEntitySystem* GameEntitySystem()
{
    if(!ext) {
        HINSTANCE m_hModule;
        #ifdef _WIN32
            m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
        #else
            m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
            if(!m_hModule) return nullptr;
        #endif

        void* fnGetClass = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_GameEntitySystem"));
        if(!fnGetClass) {
            dlclose(m_hModule);
            return nullptr;
        }

        ext = (CGameEntitySystem*)(reinterpret_cast<GetGES>(fnGetClass)());

        dlclose(m_hModule);
    }

    return ext;
}
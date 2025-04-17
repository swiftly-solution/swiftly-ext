#include "files.h"
#include <metamod_oslink.h>
#include <string>

#ifndef _WIN32
#include <dlfcn.h>
#endif

typedef void* (*GetSDKPtr)(void*, const char*, const char*);
typedef void (*StateChanged)(void*, const char*, const char*, int);
typedef const char* (*GetGame)();

extern void* funcPtr;
extern void* statePtr;

template <typename T>
T SDKGetProp(void* ptr, const char* className, const char* fieldName)
{
    if (!funcPtr) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return (T)0;
#endif

        funcPtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_GetSDKPtr"));
        if (!funcPtr) {
            dlclose(m_hModule);
            return (T)0;
        }
    }

    void* ret = reinterpret_cast<GetSDKPtr>(funcPtr)(ptr, className, fieldName);
    return *reinterpret_cast<T*>(ret);
}

template <typename T>
T* SDKGetPropPtr(void* ptr, const char* className, const char* fieldName)
{
    if (!funcPtr) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return nullptr;
#endif

        funcPtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_GetSDKPtr"));
        if (!funcPtr) {
            dlclose(m_hModule);
            return nullptr;
        }

        dlclose(m_hModule);
    }

    void* ret = reinterpret_cast<GetSDKPtr>(funcPtr)(ptr, className, fieldName);
    return reinterpret_cast<T*>(ret);
}

template <typename T>
void SDKSetProp(void* ptr, const char* className, const char* fieldName, T value)
{
    if (!funcPtr) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        funcPtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_GetSDKPtr"));
        if (!funcPtr) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    void* ret = reinterpret_cast<GetSDKPtr>(funcPtr)(ptr, className, fieldName);
    if (!ret) return;

    *reinterpret_cast<T*>(ret) = value;
}

void SDKSetStateChanged(void* ptr, const char* className, const char* fieldName, int extraOffset);
std::string GetCurrentGame();
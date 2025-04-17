#include "vfunction.h"
#include "../memory.h"
#include "../files.h"

typedef void* (*Init_VFunctionHook)(const char*, const char*, const char*, bool, dyno::CallbackHandler, const char*, char);
typedef void (*Destroy_VFunctionHook)(void*);
typedef void (*Enable_VFunctionHook)(void*);
typedef void (*Disable_VFunctionHook)(void*);

void* vfhInit = nullptr;
void* vfhPtrInit = nullptr;
void* vfhDestroy = nullptr;
void* vfhEnable = nullptr;
void* vfhDisable = nullptr;

VFunctionHook::VFunctionHook(std::string library, std::string vtable, std::string offsetName, dyno::CallbackType callbackType, dyno::CallbackHandler handler, std::string function_args, char function_return)
{
    if (!vfhInit) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        vfhInit = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_VFunctionHook_Init"));
        if (!vfhInit) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    ptr = reinterpret_cast<Init_VFunctionHook>(vfhInit)(library.c_str(), vtable.c_str(), offsetName.c_str(), (bool)callbackType, handler, function_args.c_str(), function_return);
}

VFunctionHook::~VFunctionHook()
{
    if (!ptr) return;

    if (!vfhDestroy) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        vfhDestroy = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_VFunctionHook_Destroy"));
        if (!vfhDestroy) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    reinterpret_cast<Destroy_VFunctionHook>(vfhDestroy)(ptr);
}

void VFunctionHook::Enable()
{
    if (!ptr) return;

    if (!vfhEnable) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        vfhEnable = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_VFunctionHook_Enable"));
        if (!vfhEnable) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    reinterpret_cast<Enable_VFunctionHook>(vfhEnable)(ptr);
}

void VFunctionHook::Disable()
{
    if (!ptr) return;

    if (!vfhDisable) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        vfhDisable = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_VFunctionHook_Disable"));
        if (!vfhDisable) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    reinterpret_cast<Disable_VFunctionHook>(vfhDisable)(ptr);
}

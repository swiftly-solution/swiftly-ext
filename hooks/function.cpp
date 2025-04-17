#include "function.h"
#include "../memory.h"
#include "../files.h"

typedef void* (*Init_FunctionHook)(const char*, bool, dyno::CallbackHandler, const char*, char);
typedef void* (*Init_FunctionHookPtr)(void*, bool, dyno::CallbackHandler, const char*, char);
typedef void (*Destroy_FunctionHook)(void*);
typedef void (*Enable_FunctionHook)(void*);
typedef void (*Disable_FunctionHook)(void*);

void* fhInit = nullptr;
void* fhPtrInit = nullptr;
void* fhDestroy = nullptr;
void* fhEnable = nullptr;
void* fhDisable = nullptr;

FunctionHook::FunctionHook(std::string signature_name, dyno::CallbackType callbackType, dyno::CallbackHandler handler, std::string function_args, char function_return)
{
    if (!fhInit) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        fhInit = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_FunctionHook_Init"));
        if (!fhInit) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    ptr = reinterpret_cast<Init_FunctionHook>(fhInit)(signature_name.c_str(), (bool)callbackType, handler, function_args.c_str(), function_return);
}

FunctionHook::FunctionHook(const char* signature_name, dyno::CallbackType callbackType, dyno::CallbackHandler handler, std::string function_args, char function_return)
{
    if (!fhInit) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        fhInit = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_FunctionHook_Init"));
        if (!fhInit) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    ptr = reinterpret_cast<Init_FunctionHook>(fhInit)(signature_name, (bool)callbackType, handler, function_args.c_str(), function_return);
}

FunctionHook::FunctionHook(void* signature_name, dyno::CallbackType callbackType, dyno::CallbackHandler handler, std::string function_args, char function_return)
{
    if (!fhPtrInit) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        fhPtrInit = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_FunctionHook_InitPtr"));
        if (!fhPtrInit) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    ptr = reinterpret_cast<Init_FunctionHookPtr>(fhPtrInit)(signature_name, (bool)callbackType, handler, function_args.c_str(), function_return);
}

FunctionHook::~FunctionHook()
{
    if (!ptr) return;

    if (!fhDestroy) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        fhDestroy = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_FunctionHook_Destroy"));
        if (!fhDestroy) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    reinterpret_cast<Destroy_FunctionHook>(fhDestroy)(ptr);
}

void FunctionHook::Enable()
{
    if (!ptr) return;

    if (!fhEnable) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        fhEnable = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_FunctionHook_Enable"));
        if (!fhEnable) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    reinterpret_cast<Enable_FunctionHook>(fhEnable)(ptr);
}

void FunctionHook::Disable()
{
    if (!ptr) return;

    if (!fhDisable) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        fhDisable = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_FunctionHook_Disable"));
        if (!fhDisable) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    reinterpret_cast<Disable_FunctionHook>(fhDisable)(ptr);
}

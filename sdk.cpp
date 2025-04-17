#include "sdk.h"

void* funcPtr = nullptr;
void* statePtr = nullptr;

void SDKSetStateChanged(void* ptr, const char* className, const char* fieldName, int extraOffset)
{
    if (!statePtr) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        statePtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_SetStateChanged"));
        if (!statePtr) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    reinterpret_cast<StateChanged>(statePtr)(ptr, className, fieldName, extraOffset);
}

void* gamePtr = nullptr;

std::string GetCurrentGame()
{
    if (!gamePtr) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return;
#endif

        gamePtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_GetGameName"));
        if (!gamePtr) {
            dlclose(m_hModule);
            return "unknown";
        }

        dlclose(m_hModule);
    }

    return reinterpret_cast<GetGame>(gamePtr)();
}
#include "sdk.h"

void* funcPtr = nullptr;
void* statePtr = nullptr;

void SDKSetStateChanged(void* ptr, const char* className, const char* fieldName, int extraOffset)
{
    if(!statePtr) {
        HINSTANCE m_hModule;
        #ifdef _WIN32
            m_hModule = dlmount("addons/swiftly/bin/win64/swiftly.dll");
        #else
            m_hModule = dlopen("addons/swiftly/bin/linuxsteamrt64/swiftly.so", RTLD_NOW);
            if(!m_hModule) return;
        #endif

        void* statePtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_SetStateChanged"));
        if(!statePtr) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    reinterpret_cast<StateChanged>(statePtr)(ptr, className, fieldName, extraOffset);
}
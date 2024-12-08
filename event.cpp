#include "event.h"

typedef int (*TrigEvent)(const char*, const char*, void*, void*);

void* trigPtr = nullptr;

EventResult TriggerEvent(std::string extension_id, std::string event, std::vector<std::any> args, std::any& eventReturn)
{
    if(!trigPtr) {
        HINSTANCE m_hModule;
        #ifdef _WIN32
            m_hModule = dlmount("addons/swiftly/bin/win64/swiftly.dll");
        #else
            m_hModule = dlopen("addons/swiftly/bin/linuxsteamrt64/swiftly.so", RTLD_NOW);
            if(!m_hModule) return EventResult::Continue;
        #endif

        void* trigPtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_TriggerEvent"));
        if(!trigPtr) {
            dlclose(m_hModule);
            return EventResult::Continue;
        }

        dlclose(m_hModule);
    }

    return (EventResult)reinterpret_cast<TrigEvent>(trigPtr)(extension_id.c_str(), event.c_str(), (void*)&args, (void*)&eventReturn);
}
#include "callstack.h"

void* regPtr = nullptr;
void* unregPtr = nullptr;

typedef uint64_t (*Reg)(const char*, const char*);
typedef void (*Unreg)(const char*, uint64_t);

RegisterCallstack::RegisterCallstack(std::string plugin_name, std::string stack_msg)
{
    this->plugin_name = plugin_name;
    if(!regPtr) {
        HINSTANCE m_hModule;
        #ifdef _WIN32
            m_hModule = dlmount("addons/swiftly/bin/win64/swiftly.dll");
        #else
            m_hModule = dlopen("addons/swiftly/bin/linuxsteamrt64/swiftly.so", RTLD_NOW);
            if(!m_hModule) return;
        #endif

        regPtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_RegisterCallstack"));
        if(!regPtr) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }
    
    this->id = reinterpret_cast<Reg>(regPtr)(plugin_name.c_str(), stack_msg.c_str());
}

RegisterCallstack::~RegisterCallstack()
{
    if(!unregPtr) {
        HINSTANCE m_hModule;
        #ifdef _WIN32
            m_hModule = dlmount("addons/swiftly/bin/win64/swiftly.dll");
        #else
            m_hModule = dlopen("addons/swiftly/bin/linuxsteamrt64/swiftly.so", RTLD_NOW);
            if(!m_hModule) return;
        #endif

        unregPtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_UnregisterCallstack"));
        if(!unregPtr) {
            dlclose(m_hModule);
            return;
        }

        dlclose(m_hModule);
    }

    reinterpret_cast<Unreg>(unregPtr)(this->plugin_name.c_str(), this->id);
}
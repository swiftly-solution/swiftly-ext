#include "event.h"
#include "files.h"

typedef int (*TrigEvent)(const char*, const char*, void*, void*, const char*);

void* trigPtr = nullptr;

EventResult TriggerEvent(std::string extension_id, std::string event, std::vector<std::any> args, std::any& eventReturn, std::string specific_plugin)
{
    if (!trigPtr) {
        HINSTANCE m_hModule;
#ifdef _WIN32
        m_hModule = dlmount(GeneratePath("addons/swiftly/bin/win64/swiftly.dll"));
#else
        m_hModule = dlopen(GeneratePath("addons/swiftly/bin/linuxsteamrt64/swiftly.so"), RTLD_NOW);
        if (!m_hModule) return EventResult::Continue;
#endif

        trigPtr = reinterpret_cast<void*>(dlsym(m_hModule, "swiftly_TriggerEventV2"));
        if (!trigPtr) {
            dlclose(m_hModule);
            return EventResult::Continue;
        }

        dlclose(m_hModule);
    }

    if (specific_plugin.size() > 127) return EventResult::Continue;
    char plugin_name[128];
    memcpy(plugin_name, specific_plugin.c_str(), specific_plugin.size());

    if (extension_id.size() > 127) return EventResult::Continue;
    char ext_id[128];
    memcpy(ext_id, extension_id.c_str(), extension_id.size());

    if (event.size() > 127) return EventResult::Continue;
    char event_name[128];
    memcpy(event_name, event.c_str(), event.size());

    EventResult res = reinterpret_cast<TrigEvent>(trigPtr)((const char*)ext_id, (const char*)event_name, (void*)&args, (void*)&eventReturn, (const char*)plugin_name);
    return res;
}
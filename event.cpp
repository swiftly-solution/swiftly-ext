#include "event.h"
#include "files.h"

#include <cstring>

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

    char* plugin_name = new char[specific_plugin.size() + 1];
    strcpy(plugin_name, specific_plugin.c_str());

    char* ext_id = new char[extension_id.size() + 1];
    strcpy(ext_id, extension_id.c_str());

    char* event_name = new char[event.size() + 1];
    strcpy(event_name, event.c_str());

    EventResult res = (EventResult)reinterpret_cast<TrigEvent>(trigPtr)((const char*)ext_id, (const char*)event_name, (void*)&args, (void*)&eventReturn, (const char*)plugin_name);

    delete[] event_name;
    delete[] ext_id;
    delete[] plugin_name;

    return res;
}
#ifndef _callstack_h
#define _callstack_h

#include <string>
#include <metamod_oslink.h>
#ifndef _WIN32
#include <dlfcn.h>
#endif

#define REGISTER_CALLSTACK(plugin_name, stack_str) RegisterCallstack DUIHRSGUI8RHG789342VGH78IU34FIUWEF(plugin_name, stack_str)

class RegisterCallstack
{
private:
    std::string plugin_name;
    uint64_t id;

public:
    RegisterCallstack(std::string plugin_name, std::string stack_msg);
    ~RegisterCallstack();
};

#endif
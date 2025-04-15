#ifndef _ext_hooks_function_h
#define _ext_hooks_function_h

#include <string>
#include <vector>

#include <swiftly-ext/hooks/dynohook/core.h>
#include <swiftly-ext/hooks/dynohook/os.h>
#include <swiftly-ext/hooks/dynohook/ihook.h>
#include <swiftly-ext/hooks/dynohook/imanager.h>

#if DYNO_PLATFORM_WINDOWS
#include <dynohook/conventions/x64_windows_call.h>
#define DEFAULT_CALLCONV dyno::x64WindowsCall
#else
#include <dynohook/conventions/x64_systemV_call.h>
#define DEFAULT_CALLCONV dyno::x64SystemVcall
#endif

class FunctionHook
{
private:
    void* ptr;
public:
    FunctionHook(std::string signature_name, dyno::CallbackType callbackType, dyno::CallbackHandler handler, std::string function_args, char function_return);
    FunctionHook(const char* signature_name, dyno::CallbackType callbackType, dyno::CallbackHandler handler, std::string function_args, char function_return);
    FunctionHook(void* signature_name, dyno::CallbackType callbackType, dyno::CallbackHandler handler, std::string function_args, char function_return);
    ~FunctionHook();

    void Enable();
    void Disable();
};

#endif
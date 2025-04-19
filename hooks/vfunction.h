#ifndef _ext_hooks_vfunction_h
#define _ext_hooks_vfunction_h

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

class VFunctionHook
{
private:
    void* ptr;
public:
    VFunctionHook(std::string library, std::string vtable, std::string offsetName, dyno::CallbackType callbackType, dyno::CallbackHandler handler, std::string function_args, char function_return);
    ~VFunctionHook();

    void Enable();
    void Disable();
};

#endif
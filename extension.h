#ifndef _swiftly_extension_h
#define _swiftly_extension_h

#include <ISmmPlugin.h>
#include <string>
#include <entity2/entitysystem.h>
#include "core.h"

EXT_API void* swiftly_GameEntitySystem();

class SwiftlyExt
{
public:
    virtual bool Load(std::string& error, SourceHook::ISourceHook *SHPtr, ISmmAPI* ismm, bool late) = 0;
    virtual bool Unload(std::string& error) = 0;
    virtual void AllExtensionsLoaded() = 0;
    virtual void AllPluginsLoaded() = 0;

    virtual const char* GetAuthor() = 0;
    virtual const char* GetName() = 0;
    virtual const char* GetVersion() = 0;
    virtual const char* GetWebsite() = 0;
};

#endif
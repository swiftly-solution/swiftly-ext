#ifndef _swiftly_extension_h
#define _swiftly_extension_h

#include <ISmmPlugin.h>
#include <string>

class SwiftlyExt
{
public:
    virtual bool Load(std::string& error, SourceHook::ISourceHook *SHPtr, ISmmAPI* ismm)
    {
        return true;
    }

    virtual bool Unload(std::string& error)
    {
        return true;
    }
    
    virtual void AllExtensionsLoaded() = 0;
    virtual void AllPluginsLoaded() = 0;

    virtual const char* GetAuthor();
    virtual const char* GetName();
    virtual const char* GetVersion();
    virtual const char* GetWebsite();
};

#endif
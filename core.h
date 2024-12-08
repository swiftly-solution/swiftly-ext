#ifndef _swiftly_ext_core_h
#define _swiftly_ext_core_h

#define MAX_PLAYERS 64

#if !defined EXT_API
#if defined __WIN32__ || defined _WIN32 || defined WIN32
	#define EXT_API extern "C" __declspec(dllexport)
#elif defined __GNUC__
	#define EXT_API extern "C" __attribute__ ((visibility("default")))	
#endif
#endif

EXT_API void* GetExtensionClass();

#define EXT_EXPOSE(var)	\
	EXT_API void* GetExtensionClass() { return reinterpret_cast<void*>(&var); }

#define SAVE_GLOBALVARS() \
	g_SHPtr = SHPtr;\
	g_SMAPI = ismm

#define DECLARE_GLOBALVARS() \
	extern SourceHook::ISourceHook *g_SHPtr; \
	extern ISmmAPI* g_SMAPI

#define CREATE_GLOBALVARS() \
	SourceHook::ISourceHook *g_SHPtr = nullptr; \
	ISmmAPI* g_SMAPI = nullptr

#endif
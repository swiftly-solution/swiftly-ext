#ifndef _swiftly_ext_core_h
#define _swiftly_ext_core_h

#include <ISmmPlugin.h>

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
	g_SMAPI = ismm;\
	GET_IFACE_CURRENT(GetEngineFactory, g_pCVar, ICvar, CVAR_INTERFACE_VERSION);\
    ConVar_Register((1ull << 19) | (1ull << 24) | (1ull << 25) | (1ull << 2), [](ConVarRefAbstract* ref) {}, [](ConCommandRef* ref) {});


#define DECLARE_GLOBALVARS() \
	extern SourceHook::ISourceHook *g_SHPtr; \
	extern ISmmAPI* g_SMAPI; \
	extern PluginId g_PLID

#define CREATE_GLOBALVARS() \
	SourceHook::ISourceHook *g_SHPtr = nullptr; \
	ISmmAPI* g_SMAPI = nullptr; \
	PluginId g_PLID = 0;

#define GET_IFACE_ANY(v_factory, v_var, v_type, v_name) \
	v_var = (v_type *)ismm->VInterfaceMatch(ismm->v_factory(), v_name, 0); \
	if (!v_var) \
	{ \
		error = "Could not find interface: " v_name; \
		return false; \
	}

#define GET_IFACE_CURRENT(v_factory, v_var, v_type, v_name) \
	v_var = (v_type *)ismm->VInterfaceMatch(ismm->v_factory(), v_name); \
	if (!v_var) \
	{ \
		error = "Could not find interface: " v_name; \
		return false; \
	}

#endif
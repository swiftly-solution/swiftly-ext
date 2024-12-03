#ifndef _swiftly_ext_core_h
#define _swiftly_ext_core_h

#define MAX_PLAYERS 64

#if !defined EXT_API
#if defined __WIN32__ || defined _WIN32 || defined WIN32
	#define EXT_API extern __declspec(dllexport)
#elif defined __GNUC__
	#define EXT_API extern __attribute__ ((visibility("default")))	
#endif
#endif

class SwiftlyExt;

EXT_API SwiftlyExt* GetExtensionClass();

#define EXT_EXPOSE(var)	\
	EXT_API SwiftlyExt* GetExtensionClass() { return reinterpret_cast<SwiftlyExt*>(&var); }

#endif
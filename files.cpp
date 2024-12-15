#include "files.h"
#include <string>
#include <tier0/platform.h>

#ifdef _WIN32
#define WIN_LINUX(win, linux) win
#else
#define WIN_LINUX(win, linux) linux
#endif

const char* GeneratePath(const char* path)
{
    return (std::string(Plat_GetGameDirectory()) + WIN_LINUX("\\", "/") + "csgo" + WIN_LINUX("\\", "/") + path).c_str();
}
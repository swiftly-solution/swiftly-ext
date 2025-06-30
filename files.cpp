#include "files.h"
#include <string>
#include <tier0/platform.h>

#ifdef _WIN32
#define WIN_LINUX(win, linux) win
#else
#define WIN_LINUX(win, linux) linux
#endif

char buf[WIN_LINUX(65535, 8192)];

const char* GeneratePath(const char* path)
{
    std::string formatted = (std::string(Plat_GetGameDirectory()) + WIN_LINUX("\\", "/") + "csgo" + WIN_LINUX("\\", "/") + path);
    if(formatted.size() >= WIN_LINUX(65535, 8192)) return "";

    memset(buf, 0, sizeof(buf));
    memcpy(buf, formatted.c_str(), formatted.size());
    return (const char*)buf;
}
#ifndef UTILITY_HPP_INCLUDED
#define UTILITY_HPP_INCLUDED

#include <Windows.h>
#include <string>

namespace Utility
{
    bool CopyFiles(const char *installPath, const char *wallpapersPath);
    bool SetRegAutoStart(const char *installPath);
    bool SetRegWallpapersPath(const char *wallpapersPath);
    void CreateDesktopLink(const char *installPath);
}

#endif
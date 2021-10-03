#include <Utility.hpp>

bool Utility::CopyFiles(const char *installPath, const char *wallpapersPath)
{
    std::initializer_list<const char *> files = 
    {
        "Qt6Core.dll",
        "Qt6Gui.dll",
        "Qt6Widgets.dll",
        "win32_wallpaper_extractor.exe"
    };

    CreateDirectoryA(installPath, NULL);
    CreateDirectoryA(((std::string)installPath + (std::string)"\\plugins").c_str(), NULL);
    CreateDirectoryA(((std::string)installPath + (std::string)"\\plugins\\platforms").c_str(), NULL);
    CreateDirectoryA(wallpapersPath, NULL);

    for (auto file: files) if (!CopyFileA(file, ((std::string)installPath + (std::string)"\\" + (std::string)file).c_str(), FALSE)) return false;
    if(!CopyFileA("plugins\\platforms\\qwindows.dll", ((std::string)installPath + (std::string)"\\plugins\\platforms\\qwindows.dll").c_str(), FALSE)) return false;
    
    return true;
}

bool Utility::SetRegAutoStart(const char *installPath)
{
    HKEY hKey;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS) return false;
    if (RegSetValueExA(hKey, "WinWallpaper", 0, REG_SZ, (const BYTE *) installPath, (DWORD)strlen(installPath)) != ERROR_SUCCESS) return false;

    return true;
}

bool Utility::SetRegWallpapersPath(const char *wallpapersPath)
{
    HKEY hKey;
    if (RegCreateKeyExA(HKEY_CURRENT_USER, "WinWallpaper", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS) return false;
    if (RegSetValueExA(hKey, "WallpapersPath", 0, REG_SZ, (const BYTE *)wallpapersPath, (DWORD)strlen(wallpapersPath)) != ERROR_SUCCESS) return false;

    return true;
}

void Utility::CreateDesktopLink(const char *installPath)
{

}
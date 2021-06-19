#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>


int APIENTRY WinMain (HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR CmdLine, int nCmdShow)
{
    WIN32_FIND_DATAA fdata;

    char origdir[512] = {0};
    char fnewname[512] = {0};
    char wallpath[512] = {0};
    char tempbuff[512] = {0};
    
    sprintf(wallpath, "%s\\Packages\\Microsoft.Windows.ContentDeliveryManager_cw5n1h2txyewy\\LocalState\\Assets", getenv("LOCALAPPDATA"));

    sprintf(tempbuff, "%s\\*", wallpath);
    HANDLE hfile = FindFirstFileA(tempbuff, &fdata);
    FindNextFileA(hfile, &fdata);
    
    while (FindNextFileA(hfile, &fdata))
    {
        memset(fnewname, 0, 512);
        memset(origdir, 0, 512);

        sprintf(origdir,"%s\\%s", wallpath, fdata.cFileName );
        sprintf(fnewname, "%s.jpg", fdata.cFileName);
        if (fdata.nFileSizeLow > 160000)
        CopyFileA(origdir, fnewname, TRUE);
    }

}

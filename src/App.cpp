#include <App.hpp>


App::App::App(int argc, char **argv)
{
    if (argc > 1) this->isAutoRun = true;
    this->mainApp = new QApplication(argc, argv);

}

App::App::~App()
{
    delete this->mainApp;
}

void App::App::Extract()
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
        sprintf(fnewname, "%s\\%s.jpg", this->wallpaperPath.c_str() ,fdata.cFileName);

        if (fdata.nFileSizeLow > 160000)        //need to work on this
        CopyFileA(origdir, fnewname, TRUE);
    }
}

int App::App::Run()
{
    if (isAutoRun)
    {
        this->Extract();
        return EXIT_SUCCESS;
    }


}
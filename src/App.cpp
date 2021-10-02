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

void App::App::SetupGui()
{
    QWidget mainWindow;
    mainWindow.setFixedSize(657, 308);

    QLabel installLabel, wallpaperLabel;
    installLabel.setGeometry(60, 70, 71, 31);
    installLabel.setText("Install Path: ");
    installLabel.setParent(&mainWindow);
    wallpaperLabel.setGeometry(50, 140, 81, 31);
    wallpaperLabel.setText("Wallpapers Path: ");
    wallpaperLabel.setParent(&mainWindow);

    QLineEdit installLine, wallpaperLine;
    installLine.setGeometry(140, 70, 391, 31);
    installLine.setText(((std::string)getenv("appdata") + (std::string)"\\WinWallpaper").c_str());
    installLine.setParent(&mainWindow);
    wallpaperLine.setGeometry(140, 140, 391, 31);
    wallpaperLine.setText(((std::string)getenv("userprofile") + (std::string)"\\Desktop\\WinWallpapers").c_str());
    wallpaperLine.setParent(&mainWindow);

    QCheckBox runCheck;
    runCheck.setGeometry(140, 200, 121, 21);
    runCheck.setText("Run at startup");
    runCheck.setChecked(true);
    runCheck.setParent(&mainWindow);

    QPushButton installOpen, wallpaperOpen, nextOpen, cancelOpen;
    installOpen.setGeometry(500, 70, 31, 31);
    installOpen.setText("Open");
    installOpen.setParent(&mainWindow);
    wallpaperOpen.setGeometry(500, 140, 31, 31);
    wallpaperOpen.setText("Open");
    wallpaperOpen.setParent(&mainWindow);
    nextOpen.setGeometry(540, 260, 91, 31);
    nextOpen.setText("Next");
    nextOpen.setParent(&mainWindow);
    cancelOpen.setGeometry(430, 260, 91, 31);
    cancelOpen.setText("Cancel");
    cancelOpen.setParent(&mainWindow);


}
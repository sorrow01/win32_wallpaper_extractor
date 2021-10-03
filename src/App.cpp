#include <App.hpp>


App::App::App(int argc, char **argv)
{
    if (argc > 2) this->isAutoRun = true;
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
    
    this->SetupGui();
    return this->mainApp->exec();
}

void App::App::SetupGui()
{
    static QWidget mainWindow;
    mainWindow.setFixedSize(657, 308);

    static QLabel installLabel, wallpaperLabel;
    installLabel.setGeometry(60, 70, 71, 31);
    installLabel.setText("Install Path: ");
    installLabel.setParent(&mainWindow);
    wallpaperLabel.setGeometry(50, 140, 81, 31);
    wallpaperLabel.setText("Wallpapers Path: ");
    wallpaperLabel.setParent(&mainWindow);

    static QLineEdit installLine, wallpaperLine;
    installLine.setGeometry(140, 70, 391, 31);
    installLine.setText(((std::string)getenv("appdata") + (std::string)"\\WinWallpaper").c_str());
    installLine.setParent(&mainWindow);
    wallpaperLine.setGeometry(140, 140, 391, 31);
    wallpaperLine.setText(((std::string)getenv("userprofile") + (std::string)"\\Desktop\\WinWallpapers").c_str());
    wallpaperLine.setParent(&mainWindow);

    static QCheckBox runCheck;
    runCheck.setGeometry(140, 200, 121, 21);
    runCheck.setText("Run at startup");
    runCheck.setChecked(true);
    runCheck.setParent(&mainWindow);

    static QPushButton installOpen, wallpaperOpen, next, cancel;
    installOpen.setGeometry(530, 70, 31, 31);
    installOpen.setText("Open");
    installOpen.setParent(&mainWindow);
    wallpaperOpen.setGeometry(530, 140, 31, 31);
    wallpaperOpen.setText("Open");
    wallpaperOpen.setParent(&mainWindow);
    next.setGeometry(540, 260, 91, 31);
    next.setText("Next");
    next.setParent(&mainWindow);
    cancel.setGeometry(430, 260, 91, 31);
    cancel.setText("Cancel");
    cancel.setParent(&mainWindow);

    QObject::connect(&installOpen, &QPushButton::clicked, [](){installLine.setText(QFileDialog::getExistingDirectory(nullptr, "Select a directory"));});
    QObject::connect(&wallpaperOpen, &QPushButton::clicked, [](){wallpaperLine.setText(QFileDialog::getExistingDirectory(nullptr, "Select a directory"));});
    QObject::connect(&cancel, &QPushButton::clicked, [](){exit(1);});


    QObject::connect(&next, &QPushButton::clicked, [&]{
        if(!Utility::CopyFiles(installLine.text().toStdString().c_str(), wallpaperLine.text().toStdString().c_str()))exit(MessageBoxA(NULL, "Could not copy files", "Error", MB_ICONERROR));
        if (runCheck.isChecked()) if(!Utility::SetRegAutoStart((installLine.text().toStdString() + (std::string)"\\win32_wallpaper_extractor.exe").c_str())) exit(MessageBoxA(NULL, "Could not set autorun", "Error", MB_ICONERROR));
        if (!Utility::SetRegWallpapersPath(wallpaperLine.text().toStdString().c_str())) exit(MessageBoxA(NULL, "Could not set reg key", "Error", MB_ICONERROR));
        Utility::CreateDesktopLink((installLine.text().toStdString() + (std::string)"\\win32_wallpaper_extractor.exe").c_str());
        MessageBoxA(NULL, "Successfully installed the app", "Success !", MB_OK);
        exit(EXIT_SUCCESS);
        });
    

    mainWindow.show();
}
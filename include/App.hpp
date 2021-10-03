#ifndef APP_HPP_INCLUDED
#define APP_HPP_INCLUDED

#include <QApplication>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QFileDialog>
#include <string>
#include <Utility.hpp>
#include <Windows.h>

namespace App
{
    class App
    {
    private:
        QApplication *mainApp;
        bool isAutoRun = false;
        std::string wallpaperPath;
        void SetupGui();
        void Extract();
    public:
        App(int argc, char **argv);
        ~App();
        int Run();
    };
    
    
} // namespace App


#endif
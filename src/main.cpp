#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <App.hpp>


int main (int argc, char *argv[])
{
    App::App mainApp(argc, argv);
    return mainApp.Run();
}

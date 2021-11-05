/**
 * @file   main.cpp
 * @brief  
 */

//#if defined(_MSC_VER)
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//#endif

#include "window.h"

#include <core/core.h>

int main(int, char**)
{
    Core app;
    app.start_thread();

    Window Ui;
    Ui.loop();

    return 0;
}

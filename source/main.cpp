/**
 * @file   main.cpp
 * @brief  
 */

#if defined(_MSC_VER)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "window.h"

#include <thread>
#include <chrono>

#include <core/core.h>

int main(int, char**)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    Core app;
    app.start_thread();

    Window Ui;
    Ui.loop();

    return 0;
}

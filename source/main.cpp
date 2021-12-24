/**
 * @file   main.cpp
 * @brief  
 */

//#if defined(_MSC_VER)
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
//#endif

#include "window.h"

#include <core/core.h>
#include <utilities/event/event_manager.h>

int main(int, char**)
{
    Core app;
    app.start_thread();

    Window Ui;
    Ui.loop();

    EventManager::stop(EventManagerType::eEventManager_Core);

    return 0;
}

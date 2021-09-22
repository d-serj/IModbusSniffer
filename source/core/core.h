/**
 * @file   core.h
 * @brief  
 */

#pragma once

#include <string>
#include <thread>
#include <memory>

#include <utilities/event/event.h>

class Core
{
public:
    Core();
    ~Core();

    void start_thread();

private:
    std::thread m_thread;
    bool m_core_stop = false;

    /**
     * Event handlers.
     */

    /**
     * @brief MQTT login event.
     */
    static void comport_connect(EventConnect *event);

    /**
     * @brief Application exit event.
     */
    static void exit(EventApplicationExit *event);
};

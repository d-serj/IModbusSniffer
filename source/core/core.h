/**
 * @file   core.h
 * @brief  
 */

#pragma once

#include <string>
#include <thread>
#include <memory>

#include <utilities/event/event.h>

#include "comport.h"

class Core
{
public:
    Core();
    ~Core();

    void start_thread();

private:
    std::thread m_thread;
    bool m_core_stop = false;
    Comport comport;

    /**
     * Event handlers.
     */

    /**
     * @brief MQTT login event.
     */
    static void comport_connect(std::shared_ptr<Event> event);

    /**
     * @brief Application exit event.
     */
    static void exit(std::shared_ptr<Event> event);
};

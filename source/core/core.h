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
    std::thread m_thread_serial;
    bool m_core_stop = false;
    Comport comport;

    /**
     * Event handlers.
     */

    /**
     * @brief Serial port open event handler
     * @param event event data
     */
    void comport_connect(std::shared_ptr<Event> event);

    /**
     * @brief Serial port close event handler
     * @param event event data
     */
    void comport_close(std::shared_ptr<Event> event);

    /**
     * @brief Application exit event.
     * @param event event data
     */
    void exit(std::shared_ptr<Event> event);
};

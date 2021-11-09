/**
 * @file   core.h
 * @brief  
 */

#pragma once

#include <string>
#include <thread>
#include <memory>

#include <modbus.h>
#include <utilities/event/event.h>
#include <common/modbus_rtu.h>

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
    modbus_parser parser;
    modbus_parser_settings parser_settings;
    modbus_rtu* m_modbus_packet = nullptr;

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

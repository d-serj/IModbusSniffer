/**
 * @file   core.h
 * @brief  
 */

#pragma once

#include <string>
#include <thread>
#include <memory>

#include <utilities/event/event.h>
#include <common/modbus_log.h>

#include "comport.h"

class Core
{
public:
    Core();
    ~Core();

    void start_thread();
    friend Core* core_get_instance();

protected:
    std::shared_ptr<modbus_rtu> m_modbus_packet;

private:
    static Core* m_core_ptr;
    std::thread m_thread;
    bool m_core_stop = false;
    Comport comport;
    ModbusLog m_modbus_log;

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

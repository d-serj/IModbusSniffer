/**
 * @file   core.cpp
 * @brief  
 */

#include "core.h"

#include <cassert>
#include <array>
#include <iostream>
#include <iomanip>
#include <memory>
#include <thread>
#include <chrono>
#include <functional>

#include <modbus.h>
#include <utilities/event/event.h>
#include <utilities/event/event_manager.h>
#include <utilities/utils.h>

#include <common/modbus_log.h>
#include <common/modbus_rtu.h>

Core* Core::m_core_ptr = nullptr;

Core::Core()
    : comport(), m_modbus_log()
{
    // We can use std::bind here since comport will be destroyed within Core
    EventManager::subscribe(EventManagerType::eEventManager_Core, EventType::eEvent_Connect,  std::bind(&Core::comport_connect, this, std::placeholders::_1));
    EventManager::subscribe(EventManagerType::eEventManager_Core, EventType::eEventPortClose, std::bind(&Core::comport_close, this, std::placeholders::_1));
    EventManager::subscribe(EventManagerType::eEventManager_Core, EventType::eEvent_AppExit,  std::bind(&Core::exit, this, std::placeholders::_1));

    m_core_ptr = this;
}

Core::~Core()
{
    // Close the event thread
    m_core_stop = true;
    m_thread.join();
    m_core_ptr = nullptr;
}

void Core::start_thread()
{
    m_thread = std::thread{ ([this]()
    {
        while (!this->m_core_stop)
        {
            // Receive and process all the events
            EventManager::update(EventManagerType::eEventManager_Core);

            if (!this->comport.is_opened())
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            std::array<uint8_t, 512> buff;

            const int ret = this->comport.read(buff.data(), buff.size());
            if ((ret > 0) && (ret < (sizeof(buff) - 1)))
            {
                for (int i = 0; i < ret; ++i)
                {
                   // printf("%02X ", buff[i]);
                    //std::cout << std::hex << buff[i];
                }

                printf("received size %d\n", ret);
                m_modbus_log.set_raw_data(std::move(buff));
            }
        }
    }) };
}

void Core::comport_connect(std::shared_ptr<Event> event)
{
    const std::shared_ptr<EventPortOpen> port = std::dynamic_pointer_cast<EventPortOpen>(event);
    this->comport.open(port->get_port_name(), port->get_baudrate());
    const std::string msg = this->comport.error_code();

    if (!msg.empty())
    {
        std::shared_ptr<EventShowErrorPopup> ptr_orig(new EventShowErrorPopup{ msg });
        std::shared_ptr<Event> ptr = std::dynamic_pointer_cast<Event>(ptr_orig);
        EventManager::post(EventManagerType::eEventManager_UI, EventType::eEvent_ShowErrorPopup, ptr);
    }
}

void Core::comport_close(std::shared_ptr<Event> event)
{
    UNUSED(event);
    this->comport.close();
}

void Core::exit(std::shared_ptr<Event> event)
{
    UNUSED(event);
    this->comport.close();
}

Core* core_get_instance()
{
    return Core::m_core_ptr;
}

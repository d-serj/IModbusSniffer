/**
 * @file   core.cpp
 * @brief  
 */

#include "core.h"

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <functional>

#include <utilities/event/event.h>
#include <utilities/event/event_manager.h>

Core::Core()
    : comport()
{
    // We can use std::bind here since comport will be destroyed within Core
    EventManager::subscribe(EventManagerType::eEventManager_Core, EventType::eEvent_Connect,  std::bind(&Core::comport_connect, this, std::placeholders::_1));
    EventManager::subscribe(EventManagerType::eEventManager_Core, EventType::eEventPortClose, std::bind(&Core::comport_close, this, std::placeholders::_1));
    EventManager::subscribe(EventManagerType::eEventManager_Core, EventType::eEvent_AppExit,  std::bind(&Core::exit, this, std::placeholders::_1));
}

Core::~Core()
{
    // Close the event thread
    m_core_stop = true;
    m_thread.join();
    EventManager::stop(EventManagerType::eEventManager_Core);
}

void Core::start_thread()
{
    m_thread = std::thread{ ([this]()
    {
        while (!this->m_core_stop)
        {
            EventManager::update(EventManagerType::eEventManager_Core);

            if (!this->comport.is_opened())
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            uint8_t buff[512] = { 0 };

            int ret = this->comport.read(buff, sizeof(buff));
            if ((ret > 0) && (ret < (sizeof(buff) - 1)))
            {
                for (int i = 0; i < ret; ++i)
                {
                    printf("%02X ", buff[i]);
                    //std::cout << std::hex << buff[i];
                }

                std::cout << std::endl;
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
    this->comport.close();
}

void Core::exit(std::shared_ptr<Event> event)
{
    // TODO clear all resources and exit
}

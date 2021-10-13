/**
 * @file   core.cpp
 * @brief  
 */

#include "core.h"

#include <thread>
#include <functional>

#include <utilities/event/event.h>
#include <utilities/event/event_manager.h>

Core::Core()
    : comport()
{
    // We can use std::bind here since comport will be destroyed within Core
    EventManager::subscribe(EventType::eEvent_Connect,  std::bind(&Core::comport_connect, this, std::placeholders::_1));
    EventManager::subscribe(EventType::eEventPortClose, std::bind(&Core::comport_close, this, std::placeholders::_1));
    EventManager::subscribe(EventType::eEvent_AppExit,  std::bind(&Core::exit, this, std::placeholders::_1));
}

Core::~Core()
{
    // Close the event thread
    m_core_stop = true;
    m_thread.join();
}

void Core::start_thread()
{
    m_thread = std::thread{ ([this]()
    {
        while (!this->m_core_stop)
        {
            EventManager::update();
        }
    }) };
}

void Core::comport_connect(std::shared_ptr<Event> event)
{
    const std::shared_ptr<EventPortOpen> port = std::dynamic_pointer_cast<EventPortOpen>(event);
    this->comport.open(port->get_port_name(), port->get_baudrate());
}

void Core::comport_close(std::shared_ptr<Event> event)
{
    this->comport.close();
}

void Core::exit(std::shared_ptr<Event> event)
{
    // TODO clear all resources and exit
}

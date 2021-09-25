/**
 * @file   core.cpp
 * @brief  
 */

#include "core.h"

#include <thread>

#include <utilities/event/event.h>
#include <utilities/event/event_manager.h>

Core::Core()
    : comport()
{
    EventManager::subscribe(EventType::eEvent_Connect, Core::comport_connect);
    EventManager::subscribe(EventType::eEvent_AppExit, Core::exit);
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
    std::shared_ptr<EventPortOpen> port = std::dynamic_pointer_cast<EventPortOpen>(event);
    // TODO investigate how can we initialize MQTT in static function

}

void Core::exit(std::shared_ptr<Event> event)
{
    // TODO clear all resources and exit
}

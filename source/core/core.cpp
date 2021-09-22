/**
 * @file   core.cpp
 * @brief  
 */

#include "core.h"

#include <thread>

#include <utilities/event/event.h>
#include <utilities/event/event_manager.h>

Core::Core()
{
    EventManager::subscribe(EventType::eEvent_Connect,   eventpp::argumentAdapter(Core::comport_connect));
    EventManager::subscribe(EventType::eEvent_AppExit, eventpp::argumentAdapter(Core::exit));
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

void Core::comport_connect(EventConnect *event)
{
    // TODO investigate how can we initialize MQTT in static function
    
    event->clear();
}

void Core::exit(EventApplicationExit* event)
{
    // TODO clear all resources and exit
}

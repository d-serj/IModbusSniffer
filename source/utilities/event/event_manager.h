/**
 * @file   event_manager.h
 * @brief  
 */

#pragma once

#include <memory>

#include <eventpp/eventqueue.h>
#include <eventpp/utilities/argumentadapter.h>

#include "event.h"

enum class EventManagerType { eEventManager_Core, eEventManager_UI };

class EventManager
{
public:
    EventManager() = delete;

    static void subscribe(EventManagerType manager, EventType event, const std::function<void(std::shared_ptr<Event>)> &func);
    static void post(EventManagerType manager, EventType event_type, std::shared_ptr<Event> event = std::make_shared<Event>());
    static void update(EventManagerType manager);
    static void wait_for_event(EventManagerType manager, uint32_t time_ms);
    static void stop(EventManagerType manager);

private:
    static eventpp::EventQueue<EventType, void(std::shared_ptr<Event>)> event_queue[2];
};

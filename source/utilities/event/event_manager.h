/**
 * @file   event_manager.h
 * @brief  
 */

#pragma once

#include <eventpp/eventqueue.h>
#include <eventpp/utilities/argumentadapter.h>

#include "event.h"

class EventManager
{
public:
    EventManager() = delete;

    static void subscribe(EventType event, const std::function<void(Event*)> &func);
    static void post(EventType event_type, Event* event = nullptr);
    static void update();
    static void stop();

private:
    static eventpp::EventQueue<EventType, void(Event *)> event_queue;
};

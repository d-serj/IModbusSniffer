/**
 * @file   event_manager.h
 * @brief  
 */

#pragma once

#include <memory>

#include <eventpp/eventqueue.h>
#include <eventpp/utilities/argumentadapter.h>

#include "event.h"

class EventManager
{
public:
    EventManager() = delete;

    static void subscribe(EventType event, const std::function<void(std::shared_ptr<Event>)> &func);
    static void post(EventType event_type, std::shared_ptr<Event> event = std::make_shared<Event>());
    static void update();
    static void stop();

private:
    static eventpp::EventQueue<EventType, void(std::shared_ptr<Event>)> event_queue;
};

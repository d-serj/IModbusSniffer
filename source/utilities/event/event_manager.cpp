
#include "event_manager.h"

#include <chrono>
#include <memory>

#include <eventpp/eventqueue.h>

#include "event.h"

/** Two event managers for core and UI */
eventpp::EventQueue<EventType, void(std::shared_ptr<Event>)> EventManager::event_queue[2];

void EventManager::subscribe(EventManagerType manager, EventType event, const std::function<void(std::shared_ptr<Event>)> &func)
{
    event_queue[static_cast<uint8_t>(manager)].appendListener(event, func);
}

void EventManager::post(EventManagerType manager, EventType event_type, std::shared_ptr<Event> event)
{
    event_queue[static_cast<uint8_t>(manager)].enqueue(event_type, event);
}

void EventManager::update(EventManagerType manager)
{
    //event_queue.waitFor(std::chrono::milliseconds(10));
    event_queue[static_cast<uint8_t>(manager)].process();
}

void EventManager::wait_for_event(EventManagerType manager, uint32_t time_ms)
{
    const uint8_t idx = static_cast<uint8_t>(manager); 
    event_queue[idx].waitFor(std::chrono::milliseconds(time_ms));
    event_queue[idx].process();
}

void EventManager::stop(EventManagerType manager)
{
    if (event_queue[static_cast<uint8_t>(manager)].emptyQueue())
    {
        return;
    }

    event_queue[static_cast<uint8_t>(manager)].clearEvents();
}

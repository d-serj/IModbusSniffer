
#include "event_manager.h"

#include <chrono>

#include <eventpp/eventqueue.h>

#include "event.h"

eventpp::EventQueue<EventType, void(Event*)> EventManager::event_queue;

void EventManager::subscribe(EventType event, const std::function<void(Event *)> &func)
{
    event_queue.appendListener(event, func);
}

void EventManager::post(EventType event_type, Event *event)
{
    event_queue.enqueue(event_type, event);
}

void EventManager::update()
{
    event_queue.waitFor(std::chrono::milliseconds(10));
    event_queue.process();
}

void EventManager::stop()
{
    event_queue.clearEvents();
}

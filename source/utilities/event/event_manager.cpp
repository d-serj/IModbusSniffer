
#include "event_manager.h"

#include <chrono>
#include <memory>

#include <eventpp/eventqueue.h>

#include "event.h"

eventpp::EventQueue<EventType, void(std::shared_ptr<Event>)> EventManager::event_queue;

void EventManager::subscribe(EventType event, const std::function<void(std::shared_ptr<Event>)> &func)
{
    event_queue.appendListener(event, func);
}

void EventManager::post(EventType event_type, std::shared_ptr<Event> event)
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
    if (event_queue.emptyQueue())
    {
        return;
    }

    event_queue.clearEvents();
}

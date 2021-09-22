#pragma once

#include <string>

enum class EventType { eEvent_Connect, eEvent_AppExit };

class Event
{
public:
    Event() { };
    virtual ~Event() { };

    /**
     * @brief Clear the event, deallocated the memory.
     * @warning Must be called in all of event handlers after event handled!
     */
    void clear();
};

/**
 * @brief EventApplicationExit application exit event
 */
class EventApplicationExit : public Event
{
public:
    explicit EventApplicationExit() = default;
};

/**
 * @brief EventConnect class is an event that passed login and password to the backend.
 */
class EventConnect : public Event
{
public:
    explicit EventConnect(const std::string& portname, const std::string& password)
        : Event(), m_portname(portname), m_passpord(password)
    {
    };

    const std::string& get_username() const;
    const std::string& get_password() const;

private:
    std::string m_portname;
    std::string m_passpord;
};

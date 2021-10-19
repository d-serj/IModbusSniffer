#pragma once

#include <string>
#include <cstdint>

enum class EventType : uint8_t { eEvent_Connect, eEventPortClose, eEvent_AppExit };

/**
 * @brief Base event class
 */
class Event
{
public:
    Event() { };
    virtual ~Event() { };
};

/**
 * @brief EventPortOpen class is an event that passed login and password to the backend.
 */
class EventPortOpen : public Event
{
public:
    explicit EventPortOpen(const std::string& portname, uint32_t baudrate)
        : Event(), m_portname(portname), m_baudrate(baudrate)
    {
    };

    const std::string& get_port_name() const;
    uint32_t get_baudrate() const;

private:
    std::string m_portname;
    uint32_t m_baudrate;
    char test[1024];
};

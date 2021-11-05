#pragma once

#include <string>
#include <cstdint>

enum class EventType : uint8_t { eEvent_Connect, eEventPortClose, eEvent_AppExit, eEvent_ShowErrorPopup };

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
    explicit EventPortOpen(const std::string& portname, int baudrate)
        : Event(), m_portname(portname), m_baudrate(baudrate)
    {
    };

    const std::string& get_port_name() const;
    int get_baudrate() const;

private:
    std::string m_portname;
    int m_baudrate;
    char test[1024];
};

/**
 * @brief EventPortOpen class is an event that passed login and password to the backend.
 */
class EventShowErrorPopup : public Event
{
public:
    explicit EventShowErrorPopup(const std::string& popup_message)
        : Event(), m_popup_msg(popup_message)
    {
    };

    const std::string& get_popup_msg() const;

private:
    std::string m_popup_msg;
};

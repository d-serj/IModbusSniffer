/**
 * @file   event.cpp
 * @brief  
 */

#include "event.h"

#include <string>

const std::string& EventPortOpen::get_port_name() const
{
    return this->m_portname;
}

int EventPortOpen::get_baudrate() const
{
    return this->m_baudrate;
}

const std::string& EventShowErrorPopup::get_popup_msg() const
{
    return this->m_popup_msg;
}

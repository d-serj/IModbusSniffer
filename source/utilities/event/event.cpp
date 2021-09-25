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

uint32_t EventPortOpen::get_baudrate() const
{
    return this->m_baudrate;
}

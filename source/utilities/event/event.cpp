/**
 * @file   event.cpp
 * @brief  
 */

#include "event.h"

#include <string>

void Event::clear()
{
    delete this;
}

const std::string& EventConnect::get_username() const
{
    return this->m_portname;
}

const std::string& EventConnect::get_password() const
{
    return m_passpord;
}

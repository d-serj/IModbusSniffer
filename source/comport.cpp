/**
 * @file comport.cpp
 * @brief 
 */

#include "comport.h"

comport::comport(std::string port, unsigned int baud_rate)
    : io(), serial(io, port)
{
    serial.set_option(boost::asio::serial_port_base::baud_rate(baud_rate));
}

comport::~comport()
{
}

bool comport::is_connected() const
{
    return m_connected;
}

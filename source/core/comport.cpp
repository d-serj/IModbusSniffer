/**
 * @file comport.cpp
 * @brief 
 */

#include "comport.h"

#include <cstdint>
#include <iostream>

using namespace boost;

static asio::serial_port::native_handle_type native_handle;

Comport::Comport()
    : io(), serial(io)
{

}

Comport::Comport(const std::string &port, uint32_t baud_rate)
    : io(), serial(io)
{
    open(port, baud_rate);
}

Comport::~Comport()
{
    if (serial.is_open())
    {
        serial.close();
        m_connected = false;
    }
}

void Comport::open(const std::string &port, uint32_t baud_rate)
{
    if (is_opened())
    {
        return;
    }

    try
    {
        serial.open(port);
        set_serial_default_opts(serial);
        serial.set_option(asio::serial_port_base::baud_rate(baud_rate));

        m_connected = serial.is_open();

#if WIN32
        COMMTIMEOUTS timeouts;
        native_handle = serial.native_handle();
        GetCommTimeouts(native_handle, &timeouts);
        std::cout << timeouts.ReadIntervalTimeout << std::endl;
#endif // WIN32
    } catch(boost::system::system_error& e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

bool Comport::is_opened() const
{
    return m_connected;
}

void Comport::set_serial_default_opts(boost::asio::serial_port &serial)
{
    serial.set_option(asio::serial_port_base::character_size(asio::serial_port_base::character_size(8)));
    serial.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::even));
    serial.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
}

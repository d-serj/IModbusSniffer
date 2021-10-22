/**
 * @file comport.cpp
 * @brief 
 */

#include "comport.h"

#include <cstdint>
#include <iostream>
#include <string>

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
    close();
}

void Comport::open(const std::string &port, uint32_t baud_rate)
{
    if (is_opened())
    {
        return;
    }

    serial_error.clear();

    try
    {
        serial.open(port);
        set_serial_default_opts(serial);
        serial.set_option(asio::serial_port_base::baud_rate(baud_rate));

        m_nBaud = baud_rate;

        m_connected = serial.is_open();

#if WIN32
        // Setup communication timeouts for Modbus RTU
        COMMTIMEOUTS timeouts;
        native_handle = serial.native_handle();
        GetCommTimeouts(native_handle, &timeouts);

        double dblBitsPerByte =
            1 + m_byDataBits + m_byStopBits + (m_byParity ? 1 : 0);
        timeouts.ReadIntervalTimeout =
            (DWORD)ceil((3.5f * dblBitsPerByte / (double)m_nBaud * 1000.0f));
        timeouts.ReadTotalTimeoutMultiplier  = 0;
        timeouts.ReadTotalTimeoutConstant    = 0;
        timeouts.WriteTotalTimeoutMultiplier = 0;
        timeouts.WriteTotalTimeoutConstant   = 0;
        SetCommTimeouts(native_handle, &timeouts);
#endif // WIN32
    }
    catch(boost::system::system_error& e)
    {
        serial_error = e.what();
        std::cerr << "Error: " << serial_error << std::endl;
    }
}

void Comport::close()
{
    if (serial.is_open())
    {
        try
        {
            serial.close();
        }
        catch(boost::system::system_error& e)
        {
            serial_error = e.what();
            std::cerr << "Error: " << serial_error << std::endl;
        }

        m_connected = false;
    }
}

int Comport::read(uint8_t *buff, uint32_t len)
{
    if (!m_connected)
    {
        return -1;
    }

    int ret = 0;

    try
    {
        ret = serial.read_some(asio::buffer(buff, len));
    }
    catch(boost::system::system_error& e)
    {
        serial_error = e.what();
        std::cerr << "Error: " << serial_error << std::endl;
    }

    return ret;
}

const std::string Comport::error_code()
{
    return serial_error;
}

bool Comport::is_opened() const
{
    return m_connected;
}

void Comport::set_serial_default_opts(boost::asio::serial_port &serial)
{
    serial.set_option(asio::serial_port_base::character_size(asio::serial_port_base::character_size(m_byDataBits)));
    serial.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::even));
    serial.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
}

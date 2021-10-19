/**
 * @file comport.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <string>
#include <cstdint>

#include <boost/asio.hpp>

class Comport
{
public:
    Comport();
    Comport(const std::string &port, uint32_t baud_rate);
    ~Comport();

    bool is_opened() const;
    void open(const std::string &port, uint32_t baud_rate);
    void close();

    int read(uint8_t *buff, uint32_t len);
    const std::string &error_code();

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
    bool m_connected = false;

    // Serial port settings
    uint8_t m_byDataBits = 8;
    uint8_t m_byStopBits = 1;
    bool m_byParity      = true;
    uint32_t m_nBaud     = 57600;

    std::string serial_error;

    void set_serial_default_opts(boost::asio::serial_port &serial);
};

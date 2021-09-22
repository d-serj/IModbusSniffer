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

#include <boost/asio.hpp>

class comport
{
public:
    comport(std::string port, unsigned int baud_rate);
    ~comport();

    bool is_connected() const;

private:
    boost::asio::io_service io;
    boost::asio::serial_port serial;
    bool m_connected = false;
};


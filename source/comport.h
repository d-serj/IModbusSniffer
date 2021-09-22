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

#include <boost/asio.hpp>

class comport
{
public:
    comport(/* args */);
    ~comport();

    bool is_connected() const;

private:
    bool m_connected = false;
};


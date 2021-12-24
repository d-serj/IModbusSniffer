/**
 * @file modbus_rtu.h
 * @brief 
 */

#ifndef MODBUS_RTU_H_
#define MODBUS_RTU_H_

#include <cstdint>
#include <vector>

struct modbus_rtu
{
    modbus_rtu() = default;

    uint8_t slave_addr = 0;
    uint8_t function   = 0;
    uint16_t reg       = 0;
    uint16_t crc       = 0;
    std::vector<uint8_t> data;

    /** True if the packet is a request to the slave */
    bool is_master_to_slave;
    /** True if packet contains error */
    bool is_error;

    modbus_rtu& operator=(modbus_rtu const& rhs)
    {
        slave_addr = rhs.slave_addr;
        function   = rhs.function;
        data       = rhs.data;
        crc        = rhs.crc;

        return *this;
    }
};

#endif // MODBUS_RTU_H_

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
    modbus_rtu() = delete;

    uint8_t slave_addr;
    uint8_t function;
    std::vector<uint8_t> data;
    uint16_t crc;

    /** True if the packet is a request to the slave */
    bool master_to_slave;
};

#endif // MODBUS_RTU_H_

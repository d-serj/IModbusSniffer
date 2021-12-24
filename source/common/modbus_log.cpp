/*****************************************************************//**
 * \file   modbus_log.cpp
 * \brief 
 *********************************************************************/

#include "modbus_log.h"

#include <cstdint>
#include <memory>

ModbusLog* ModbusLog::m_modbus_log_ptr = nullptr;

static int on_slave_addr(modbus_parser* objPL_parser);
static int on_function(modbus_parser* objPL_parser);
static int on_addr(modbus_parser* objPL_parser);
static int on_qty(modbus_parser* objPL_parser);
static int on_data_len(modbus_parser* objPL_parser);
static int on_data_end(modbus_parser* objPL_parser);
static int on_crc_error(modbus_parser* objPL_parser);
static int on_complete(modbus_parser* objPL_parser);

ModbusLog::ModbusLog()
{
    m_modbus_log_ptr = this;
    m_core_stop      = false;

    modbus_parser_init(&parser, MODBUS_RESPONSE);
    modbus_parser_settings_init(&parser_settings);

    parser_settings.on_slave_addr = on_slave_addr;
    parser_settings.on_function = on_function;
    parser_settings.on_addr = on_addr;
    parser_settings.on_qty = on_qty;
    parser_settings.on_data_len = on_data_len;
    parser_settings.on_data_end = on_data_end;
    parser_settings.on_crc_error = on_crc_error;
    parser_settings.on_complete = on_complete;

    m_thread = std::thread{ ([this]()
    {
        while (!this->m_core_stop)
        {
            
            std::shared_ptr<modbus_rtu> m_modbus_packet = std::make_shared<modbus_rtu>();
            modbus_parser_init(&parser, MODBUS_RESPONSE);

            if (m_raw.empty())
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
            
            {
                std::unique_lock<std::shared_timed_mutex> w(m_protect_raw);
                modbus_parser_execute(&parser, &parser_settings, m_raw.front().data(), m_raw.front().size());
                m_raw.pop();
            }

            if (!parser.err)
            {
                m_modbus_packet->slave_addr = parser.slave_addr;
                m_modbus_packet->function = parser.function;
                m_modbus_packet->reg = parser.addr;

                m_modbus_packet->crc = parser.calc_crc;
                m_modbus_packet->data.insert(m_modbus_packet->data.end(), parser.data, &parser.data[parser.data_len]);
            }
            else
            {
                m_modbus_packet->slave_addr = 255;
            }

            set_entry(m_modbus_packet);
            notify();
            // Clear entry once all of listeners are notified
            {
                std::unique_lock<std::shared_timed_mutex> w(m_protect_entries);
                m_entries.pop();
            }
        }
     }) };
}

ModbusLog::~ModbusLog()
{
    m_modbus_log_ptr = nullptr;
    m_core_stop = true;
    m_thread.join();
}

void ModbusLog::set_raw_data(std::array<uint8_t, 512>& input)
{
    std::unique_lock<std::shared_timed_mutex> w(m_protect_raw);
    m_raw.push(input);
    m_cond.notify_one();
}

void ModbusLog::set_entry(const std::shared_ptr<modbus_rtu>& entry)
{
    std::unique_lock<std::shared_timed_mutex> w(m_protect_entries);
    m_entries.push(*entry);
}

const modbus_rtu& ModbusLog::get_entry() const
{
    std::shared_lock<std::shared_timed_mutex> r(m_protect_entries);
    return m_entries.front();
}

ModbusLog *ModbusLog::modbus_log_get_instance()
{
    return m_modbus_log_ptr;
}

static int on_slave_addr(modbus_parser* objPL_parser)
{
    return 0;
}

static int on_function(modbus_parser* objPL_parser)
{
    return 0;
}

static int on_addr(modbus_parser* objPL_parser)
{
    return 0;
}

static int on_qty(modbus_parser* objPL_parser)
{
    return 0;
}

static int on_data_len(modbus_parser* objPL_parser)
{
    return 0;
}

static int on_data_end(modbus_parser* objPL_parser)
{
    return 0;
}

static int on_crc_error(modbus_parser* objPL_parser)
{
    return 0;
}

static int on_complete(modbus_parser* objPL_parser)
{
    return 0;
}

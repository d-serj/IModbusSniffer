/**
 * @file   core.cpp
 * @brief  
 */

#include "core.h"

#include <iostream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <functional>

#include <modbus.h>
#include <utilities/event/event.h>
#include <utilities/event/event_manager.h>
#include <utilities/utils.h>

#include <common/modbus_rtu.h>

static int on_slave_addr(modbus_parser* objPL_parser);
static int on_function(modbus_parser* objPL_parser);
static int on_addr(modbus_parser* objPL_parser);
static int on_qty(modbus_parser* objPL_parser);
static int on_data_len(modbus_parser* objPL_parser);
static int on_data_end(modbus_parser* objPL_parser);
static int on_crc_error(modbus_parser* objPL_parser);
static int on_complete(modbus_parser* objPL_parser);

Core::Core()
    : comport()
{
    // We can use std::bind here since comport will be destroyed within Core
    EventManager::subscribe(EventManagerType::eEventManager_Core, EventType::eEvent_Connect,  std::bind(&Core::comport_connect, this, std::placeholders::_1));
    EventManager::subscribe(EventManagerType::eEventManager_Core, EventType::eEventPortClose, std::bind(&Core::comport_close, this, std::placeholders::_1));
    EventManager::subscribe(EventManagerType::eEventManager_Core, EventType::eEvent_AppExit,  std::bind(&Core::exit, this, std::placeholders::_1));

    modbus_parser_init(&parser, MODBUS_RESPONSE);
    modbus_parser_settings_init(&parser_settings);

    parser_settings.on_slave_addr = on_slave_addr;
    parser_settings.on_function   = on_function;
    parser_settings.on_addr       = on_addr;
    parser_settings.on_qty        = on_qty;
    parser_settings.on_data_len   = on_data_len;
    parser_settings.on_data_end   = on_data_end;
    parser_settings.on_crc_error  = on_crc_error;
    parser_settings.on_complete   = on_complete;

    std::cout << sizeof(modbus_rtu) << std::endl;
}

Core::~Core()
{
    // Close the event thread
    m_core_stop = true;
    m_thread.join();
    EventManager::stop(EventManagerType::eEventManager_Core);
}

void Core::start_thread()
{
    m_thread = std::thread{ ([this]()
    {
        while (!this->m_core_stop)
        {
            // Receive and process all the events
            EventManager::update(EventManagerType::eEventManager_Core);

            if (!this->comport.is_opened())
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }

            uint8_t buff[512] = { 0 };

            const int ret = this->comport.read(buff, sizeof(buff));
            if ((ret > 0) && (ret < (sizeof(buff) - 1)))
            {
                for (int i = 0; i < ret; ++i)
                {
                    printf("%02X ", buff[i]);
                    //std::cout << std::hex << buff[i];
                }

                std::cout << std::endl;

                modbus_parser_init(&parser, MODBUS_RESPONSE);
                modbus_parser_execute(&parser, &parser_settings, buff, sizeof(buff));
            }
        }
    }) };
}

void Core::comport_connect(std::shared_ptr<Event> event)
{
    const std::shared_ptr<EventPortOpen> port = std::dynamic_pointer_cast<EventPortOpen>(event);
    this->comport.open(port->get_port_name(), port->get_baudrate());
    const std::string msg = this->comport.error_code();

    if (!msg.empty())
    {
        std::shared_ptr<EventShowErrorPopup> ptr_orig(new EventShowErrorPopup{ msg });
        std::shared_ptr<Event> ptr = std::dynamic_pointer_cast<Event>(ptr_orig);
        EventManager::post(EventManagerType::eEventManager_UI, EventType::eEvent_ShowErrorPopup, ptr);
    }
}

void Core::comport_close(std::shared_ptr<Event> event)
{
    UNUSED(event);
    this->comport.close();
}

void Core::exit(std::shared_ptr<Event> event)
{
    // TODO clear all resources and exit
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

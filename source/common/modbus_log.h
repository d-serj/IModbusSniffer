/*****************************************************************//**
 * \file   modbus_log.h
 * \brief  
 *********************************************************************/

#ifndef MODBUS_LOG_H_
#define MODBUS_LOG_H_

#include <array>
#include <cstdint>
#include <memory>
#include <queue>
#include <thread>
#include <shared_mutex>
#include <condition_variable>

#include <modbus.h>
#include <utilities/observer.h>

#include "modbus_rtu.h"

class ModbusLog : public Subject
{
public:
	ModbusLog();
	~ModbusLog();

	static ModbusLog *modbus_log_get_instance();
	void set_entry(const std::shared_ptr<modbus_rtu>& entry);
	void set_raw_data(std::array<uint8_t, 512>& input);
	const modbus_rtu& get_entry() const;

private:
	ModbusLog(const ModbusLog&) = delete;
	ModbusLog& operator =(const ModbusLog&) = delete;
	//const std::array<uint8_t, 512>& dequeue_raw();

	bool m_core_stop;
	std::thread m_thread;
	mutable std::shared_timed_mutex m_protect_entries;
	mutable std::shared_timed_mutex m_protect_raw;
	std::condition_variable m_cond;

	std::queue<modbus_rtu> m_entries;
	std::queue<std::array<uint8_t, 512>> m_raw;
	modbus_parser parser;
	modbus_parser_settings parser_settings;
	
	static ModbusLog* m_modbus_log_ptr;
};

#endif // MODBUS_LOG_H_

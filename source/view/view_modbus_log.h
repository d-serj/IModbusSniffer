#ifndef VIEW_MODBUS_LOG_H_
#define VIEW_MODBUS_LOG_H_

#include "view.h"

#include <memory>
#include <vector>

#include <utilities/observer.h>
#include <common/modbus_log.h>
#include <common/modbus_rtu.h>

class ViewModbusLog : public View, public Observer
{
public:
	ViewModbusLog(ModbusLog &s);
	~ViewModbusLog();

	void draw() override;
	void update(Subject&) override;

private:
	static constexpr int m_columns_num = 7;
	std::vector<modbus_rtu> m_modbus_entities;
	ModbusLog& m_subject;
	std::shared_ptr<modbus_rtu> m_modbus_rtu;
};

#endif // VIEW_MODBUS_LOG_H_

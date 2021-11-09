#ifndef VIEW_MODBUS_LOG_H_
#define VIEW_MODBUS_LOG_H_

#include "view.h"

class ViewModbusLog : public View
{
public:
	ViewModbusLog();
	~ViewModbusLog();

	void draw() override;

private:
	static constexpr int m_columns_num = 7;
};

#endif // VIEW_MODBUS_LOG_H_

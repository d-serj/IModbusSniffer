/**
 * @file   views_pool.cpp
 * @brief  List of available views in the app
 */

#include "views_pool.h"

#include <cassert>
#include <vector>

#include <common/modbus_log.h>

#include "view_connection.h"
#include "view_error_popup.h"
#include "view_modbus_log.h"

std::vector<View*> ViewsPool::views;

ViewsPool::ViewsPool()
{
    views.emplace_back(new ViewConnection);
    views.emplace_back(new ViewPopup);
    assert(ModbusLog::modbus_log_get_instance());
    views.emplace_back(new ViewModbusLog{ *ModbusLog::modbus_log_get_instance() });
    // Register all new views here
}

ViewsPool::~ViewsPool()
{
    for (auto& view : this->get_pool())
    {
        delete view;
    }
}

void ViewsPool::add(View* view)
{
    get_pool().emplace_back(view);
}

std::vector<View*>& ViewsPool::get_pool()
{
    return views;
}

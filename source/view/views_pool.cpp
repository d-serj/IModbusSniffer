/**
 * @file   views_pool.cpp
 * @brief  List of available views in the app
 */

#include "views_pool.h"

#include <vector>

#include "view_connection.h"

std::vector<View*> ViewsPool::views;
static ViewsPool pool;

ViewsPool::ViewsPool()
{
    views.emplace_back(new ViewConnection);
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

/**
 * @file   init.cpp
 * @brief  
 */

#include "content.h"

#include <vector>
#include <iostream>

#include "view/views_pool.h"
#include "view/view_connection.h"

Content::Content()
{

}

Content::~Content()
{

}

std::vector<View*>& Content::get_views()
{
    return ViewsPool::get_pool();
}

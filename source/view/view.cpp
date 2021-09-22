/**
 * @file   view.cpp
 * @brief  Base abstract class for all views. Source file
 */

#include "view.h"

#include <imgui.h>


View::View(std::string view_name)
    : m_window_name(view_name)
{

}

void View::draw_menu()
{
}

ImVec2 View::get_min_size() const
{
    return ImVec2(480, 720);
}

ImVec2 View::get_max_size() const
{
    return ImVec2(1920, 1080);
}

bool& View::get_view_open_state()
{
    return m_view_is_opened;
}

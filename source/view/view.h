/**
 * @file   ui.h
 * @brief  
 */

#pragma once

#include <string>

#include <imgui.h>

class View
{
public:
    explicit View(std::string view_name);
    virtual ~View() = default;

    virtual void draw() = 0;
    virtual void draw_menu();
    virtual ImVec2 get_min_size() const;
    virtual ImVec2 get_max_size() const;

    /**
     * @brief Get the state of the view.
     * @return reference to boolean with state of the view
     */
    bool& get_view_open_state();

private:
    bool m_view_is_opened = true;
    std::string m_window_name;
};

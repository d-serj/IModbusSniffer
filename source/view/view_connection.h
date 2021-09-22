/**
 * @file   view_login.h
 * @brief  
 */

#ifndef VIEW_LOGIN_H_
#define VIEW_LOGIN_H_

#include <array>

#include <utilities/event/event.h>

#include "view.h"

class ViewConnection : public View
{
public:
    ViewConnection();
    ~ViewConnection();

    void draw() override;
    void draw_menu() override;

private:
    std::array<char, 64> m_port_name{ 0 };
    bool m_connected = false;
};

#endif // VIEW_LOGIN_H_



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
    bool m_connected = false;
    int m_item_current = 0;

    void draw_connection_window();
};

#endif // VIEW_LOGIN_H_



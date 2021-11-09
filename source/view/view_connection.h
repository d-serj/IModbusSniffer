/**
 * @file   view_login.h
 * @brief  
 */

#ifndef VIEW_LOGIN_H_
#define VIEW_LOGIN_H_

#include <array>
#include <string>
#include <vector>
#include <cstdint>

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
    bool m_connected        = false;
    int m_selected_comport  = 0;
    int m_selected_baudrate = 5; // Default baudrate from m_baud_rates is 57600
    bool m_comports_found   = false;

    static constexpr char *m_baud_rates[] = { "2400", "4800", "9600", "19200",  "38400", "57600", "115200" };
    static constexpr char *port_none    = "<none>";
    std::string m_comports_formatted;
    std::vector<std::string> m_comports;

    void draw_connection_window();

    /**
     * @brief Scan for COM ports that are available in the system
     * @return true if we have found at least 1 COM port
     * @return false if there are no available COM ports
     */
    bool scan_comports();
};

#endif // VIEW_LOGIN_H_



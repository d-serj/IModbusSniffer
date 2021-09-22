/**
 * @file   view_login.cpp
 * @brief  Base abstract class for all views. Header file
 */

#include "view.h"
#include "view_connection.h"

#include <vector>
#include <string>

#include <fmt/format.h>
#include <imgui.h>

#include <utilities/event/event.h>
#include <utilities/event/event_manager.h>
#include <utilities/enumser.h>

ViewConnection::ViewConnection()
    : View("view.login")
{

}

ViewConnection::~ViewConnection()
{
    
}

void ViewConnection::draw()
{
    if (!this->get_view_open_state())
    {
        return;
    }

    std::string comports;
    CEnumerateSerial::CPortsArray ports;
    if (CEnumerateSerial::UsingGetCommPorts(ports))
    {
        for (const auto& port : ports)
        {
            // Create 
            const std::string null_term = fmt::format("COM{}", port);
            const std::string formated{null_term.c_str(), null_term.size() + 1};
            comports += formated;
        }
    }

    const ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoNavFocus
        | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse;

    ImGui::SetNextWindowSize(ImVec2(280, 180), ImGuiCond_Appearing);

    ImGui::Begin("COM Port", &View::get_view_open_state(), windowFlags);

    static int item_current = 0;
    ImGui::Combo("COM Port name", &item_current, comports.c_str(), comports.size());

    if (ImGui::Button("Connect"))
    {
        const std::string user_name = m_port_name.data();
        const std::string password  = m_port_name.data();

        EventManager::post(EventType::eEvent_Connect, new EventConnect{ user_name, password });
    }

    ImGui::End();

    ImGui::ShowDemoWindow();
}

void ViewConnection::draw_menu()
{
    if (ImGui::BeginMenu("Connection"))
    {
        if (ImGui::MenuItem("Connect to COM port", nullptr))
        {
            View::get_view_open_state() = true;
        }
        
        ImGui::EndMenu();
    }
}

/**
 * @file   view_login.cpp
 * @brief  Base abstract class for all views. Header file
 */

#include "view.h"
#include "view_connection.h"

#include <vector>
#include <string>
#include <memory>

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

    const char port_none[] = "<none>";
    std::string comports_formatted{ port_none, IM_ARRAYSIZE(port_none) };
    std::vector<std::string> comports{port_none};
    CEnumerateSerial::CPortsArray ports;

    int ports_num = 0;
    if (CEnumerateSerial::UsingGetCommPorts(ports))
    {
        for (const auto& port : ports)
        {
            // Create 
            const std::string entity = fmt::format("COM{}", port);
            comports.emplace_back(entity);
            // Insert with \0 terminator to be drawn on combo box
            comports_formatted += {entity.c_str(), entity.size() + 1};
            ++ports_num;
        }
    }

    if (m_item_current > ports_num)
    {
        m_item_current = 0;
        m_connected    = false;
    }

    const ImGuiWindowFlags windowFlags =
        ImGuiWindowFlags_NoCollapse
        | ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_NoNavFocus
        | ImGuiWindowFlags_NoBringToFrontOnFocus
        | ImGuiWindowFlags_NoScrollbar
        | ImGuiWindowFlags_NoScrollWithMouse;

    ImGui::SetNextWindowSize(ImVec2(280, 220), ImGuiCond_Appearing);

    if (ImGui::Begin("COM Port settings", &View::get_view_open_state(), windowFlags))
    {
        if (m_connected || (ports_num == 0))
        {
            ImGui::BeginDisabled();
        }

        ImGui::Combo("Port name", &m_item_current, comports_formatted.c_str(), comports_formatted.size());

        if (m_connected || (ports_num == 0))
        {
            ImGui::EndDisabled();
        }

        if ((m_item_current == 0) || m_connected)
        {
            ImGui::BeginDisabled();
            ImGui::Button("Connect");
            ImGui::EndDisabled();
        }
        else if (ImGui::Button("Connect"))
        {
            std::shared_ptr<EventPortOpen> ptr_orig(new EventPortOpen{ comports.at(m_item_current), 57600 });
            std::shared_ptr<Event> ptr = std::dynamic_pointer_cast<Event>(ptr_orig);
            EventManager::post(EventManagerType::eEventManager_Core, EventType::eEvent_Connect, ptr);
            m_connected = true;
        }

        ImGui::SameLine();
        ImGui::Separator();
        ImGui::SameLine();

        if (!m_connected)
        {
            ImGui::BeginDisabled();
            ImGui::Button("Disconnect");
            ImGui::EndDisabled();
        }
        else if (ImGui::Button("Disconnect"))
        {
            EventManager::post(EventManagerType::eEventManager_Core, EventType::eEventPortClose);
            m_connected = false;
        }

        ImGui::End();
    }

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

void ViewConnection::draw_connection_window()
{

}

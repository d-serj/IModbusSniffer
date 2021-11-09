/*****************************************************************//**
 * \file   view_modbus_log.cpp
 * \brief  
 *********************************************************************/

#include <imgui.h>

#include "view_modbus_log.h"

ViewModbusLog::ViewModbusLog()
    : View("view.modbus_log")
{
}

ViewModbusLog::~ViewModbusLog()
{
}

void ViewModbusLog::draw()
{
    if (ImGui::Begin("Modbus log", NULL,
        ImGuiWindowFlags_NoResize
        | ImGuiWindowFlags_AlwaysAutoResize
        | ImGuiWindowFlags_NoCollapse))
    {
        const ImGuiTableFlags flags =
            ImGuiTableFlags_ScrollY
            | ImGuiTableFlags_BordersOuter
            | ImGuiTableFlags_BordersV
            | ImGuiTableFlags_Resizable
            | ImGuiTableFlags_Hideable
            | ImGuiTableFlags_BordersInnerH;
        // When using ScrollX or ScrollY we need to specify a size for our table container!
         // Otherwise by default the table will fit all available space, like a BeginChild() call.
        ImVec2 outer_size = ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 8);
        if (ImGui::BeginTable("table_scrolly", m_columns_num, flags, outer_size))
        {
            ImGui::TableSetupScrollFreeze(0, 1); // Make top row always visible
            ImGui::TableSetupColumn("Time", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("<->", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("Addr", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("Cmd", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("Reg", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("Len", ImGuiTableColumnFlags_None);
            ImGui::TableSetupColumn("Data", ImGuiTableColumnFlags_None);
            ImGui::TableHeadersRow();

            // Using clipper for large vertical lists
            ImGuiListClipper clipper;
            clipper.Begin(1000);
            while (clipper.Step())
            {
                for (int row = clipper.DisplayStart; row < clipper.DisplayEnd; row++)
                {
                    ImGui::TableNextRow();
                    for (int column = 0; column < m_columns_num; column++)
                    {
                        ImGui::TableSetColumnIndex(column);
                        ImGui::Text("Hello %d,%d", column, row);
                    }
                }
            }
            ImGui::EndTable();
        }

        ImGui::End();
    }
}

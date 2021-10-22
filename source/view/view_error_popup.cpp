/**
 * @file ViewPopup.cpp
 * @brief 
 */

#include "view_error_popup.h"

#include <imgui.h>

#include <utilities/event/event_manager.h>
#include <utilities/event/event.h>

ViewPopup::ViewPopup(/* args */)
    : View("view.popup")
{
    EventManager::subscribe(EventManagerType::eEventManager_UI, EventType::eEvent_ShowErrorPopup,
        std::bind(&ViewPopup::show_error_popup_event, this, std::placeholders::_1));

    m_popup_msg.clear();
}

ViewPopup::~ViewPopup()
{
}

void ViewPopup::draw()
{
    if (m_show_popup_flag && !m_popup_msg.empty())
    {
        ImGui::OpenPopup("Error");
    }

    if (ImGui::BeginPopupModal("Error", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text(m_popup_msg.c_str());
        ImGui::Separator();
        
        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
            m_popup_msg.clear();
        }

        ImGui::SetItemDefaultFocus();
        ImGui::EndPopup();
    }
}

void ViewPopup::show_error_popup_event(std::shared_ptr<Event> event)
{
    const std::shared_ptr<EventShowErrorPopup> popup = std::dynamic_pointer_cast<EventShowErrorPopup>(event);
    this->show_popup(popup->get_popup_msg());
}

void ViewPopup::show_popup(const std::string &popump_msg)
{
    this->m_popup_msg = popump_msg;
    m_show_popup_flag = true;
}

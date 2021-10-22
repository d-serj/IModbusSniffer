#ifndef VIEW_ERROR_POPUP_H_
#define VIEW_ERROR_POPUP_H_

#include <string>
#include <memory>

#include "view.h"

#include <utilities/event/event.h>

class ViewPopup : public View
{
public:
    ViewPopup();
    ~ViewPopup();

    void draw() override;

private:
    std::string m_popup_msg;
    bool m_show_popup_flag = false;

    void show_error_popup_event(std::shared_ptr<Event> event);
    void show_popup(const std::string &popump_msg);
};

#endif // VIEW_ERROR_POPUP_H_

/**
 * @file   window.h
 * @brief  
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <vector>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers

#include "content.h"

class Window
{
public:
    Window();
    ~Window();

    void loop();

private:
    void terminate();
    void draw_main_view();
    void draw_views();
    void draw_menus();

    Content app_views;
    GLFWwindow* window = nullptr;
    bool should_exit   = false;
};


#endif // WINDOW_H_

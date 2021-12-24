cmake_minimum_required(VERSION 3.15)

add_executable(${TARGET_NAME} WIN32)

target_sources(
  ${TARGET_NAME}
  PRIVATE
  main.cpp
  third_party/imgui/imconfig.h
  third_party/imgui/imgui_draw.cpp
  third_party/imgui/imgui_demo.cpp
  third_party/imgui/imgui.h
  third_party/imgui/imgui.cpp
  third_party/imgui/imgui_tables.cpp
  third_party/imgui/imgui_widgets.cpp

  third_party/imgui/backends/imgui_impl_glfw.cpp
  third_party/imgui/backends/imgui_impl_glfw.h
  third_party/imgui/backends/imgui_impl_opengl3.h
  third_party/imgui/backends/imgui_impl_opengl3_loader.h
  third_party/imgui/backends/imgui_impl_opengl3.cpp

  window.h
  window.cpp
  view/view.h
  view/view.cpp
  "view/view_connection.cpp"          "view/view_connection.h"
  "view/views_pool.h"                 "view/views_pool.cpp"
  "view/view_error_popup.cpp"         "view/view_error_popup.h"

  "utilities/event/event_manager.cpp" "utilities/event/event_manager.h"
  "utilities/event/event.cpp"         "utilities/event/event.h"
  "utilities/enumser.cpp"             "utilities/enumser.h"

  "core/core.cpp"                     "core/core.h"                       
  "core/comport.cpp"                  "core/comport.h"
  "utilities/utils.h"
  "view/view_modbus_log.cpp"          "view/view_modbus_log.h"
  "common/modbus_log.cpp"               "common/modbus_log.h"
  "utilities/observer.h"
)

target_include_directories(
  ${TARGET_NAME} PRIVATE
  third_party/glfw-3.3.4.bin.WIN64/include
  third_party/imgui
  third_party/imgui/backends
  third_party/eventpp/include
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Boost_INCLUDE_DIR}
)

target_compile_definitions(
  ${TARGET_NAME} PUBLIC
  BOOST_ERROR_CODE_HEADER_ONLY
  _WIN32_WINNT=0x0501
)

if (MINGW)
  find_library(GLFW3_LIBRARY NAMES glfw3 glfw PATHS ${CMAKE_SOURCE_DIR}/libs/glfw3/lib-mingw-w64)
elseif (MSVC)
  find_library(GLFW3_LIBRARY NAMES glfw3 glfw PATHS ${CMAKE_SOURCE_DIR}/libs/glfw3/lib-vc2019)
else()
  message(FATAL_ERROR "Compiler is unsupported")
endif()

include(GNUInstallDirs)

# For the paho_mqtt_c module
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third_party/paho.mqtt.cpp/cmake)

find_package(OpenGL REQUIRED)

if (MSVC)
  set_target_properties(
    ${TARGET_NAME} PROPERTIES
    LINK_FLAGS /SUBSYSTEM:CONSOLE
  )
endif()

target_link_libraries(
  ${TARGET_NAME} PRIVATE
  ${GLFW3_LIBRARY}
  OpenGL::GL
  spdlog::spdlog_header_only
  fmt::fmt
  modbus-parser
)

if (MINGW)
  target_link_options(
    ${TARGET_NAME} PRIVATE
    -static
    -static-libgcc
    -static-libstdc++
  )
endif()

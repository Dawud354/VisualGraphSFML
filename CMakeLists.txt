cmake_minimum_required(VERSION 3.31)
project(VisualGraphSFML)

set(CMAKE_CXX_STANDARD 20)


include_directories(${CMAKE_SOURCE_DIR})


if(WIN32)
    # Windows-specific paths
    set(SFML_ROOT "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.2")
    set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
    set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")
    set(SFML_DLL_DIR "${SFML_ROOT}/bin")

    include_directories(${SFML_INCLUDE_DIR})
    link_directories(${SFML_LIBRARY_DIR})
else()
    # Find the system-installed SFML
    find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)
endif()

add_executable(VisualGraphSFML main.cpp
        circle_node.cpp
        circle_node.h
        circle_graph.cpp
        circle_graph.h
        circle_node_box.cpp
        circle_node_box.h
        button.cpp
        button.h
        UserInteractionBox.cpp
        UserInteractionBox.h
        font_manager.cpp
        font_manager.h
        graph.cpp
        graph.h
        "main_frame.cpp"
        "main_frame.h"
        user_interaction_messages.h
        label_box.cpp
        label_box.h
        circle_node_box_messages.h
        line.cpp
        line.h
        TextBox.cpp
        TextBox.h
)


target_link_libraries(VisualGraphSFML sfml-graphics sfml-window sfml-system)

# 5. Copy DLLs ONLY if on Windows
if(WIN32)
    add_custom_command(TARGET VisualGraphSFML POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DLL_DIR}/sfml-graphics-2.dll"
            "$<TARGET_FILE_DIR:VisualGraphSFML>/sfml-graphics-2.dll"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DLL_DIR}/sfml-window-2.dll"
            "$<TARGET_FILE_DIR:VisualGraphSFML>/sfml-window-2.dll"
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SFML_DLL_DIR}/sfml-system-2.dll"
            "$<TARGET_FILE_DIR:VisualGraphSFML>/sfml-system-2.dll"
    )
endif()


cmake_minimum_required(VERSION 3.31)
project(VisualGraphSFML)

set(CMAKE_CXX_STANDARD 20)


include_directories(/libs)

set(SFML_ROOT "${CMAKE_SOURCE_DIR}/libs/SFML-2.6.2")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")
set(SFML_DLL_DIR "${SFML_ROOT}/bin")

include_directories(${SFML_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR})


link_directories(${SFML_LIBRARY_DIR})

add_executable(VisualGraphSFML main.cpp
        CircleNode.cpp
        CircleNode.h
        CircleGraph.cpp
        CircleGraph.h
        CircleNodeBox.cpp
        CircleNodeBox.h
        Button.cpp
        Button.h
        UserInteractionBox.cpp
        UserInteractionBox.h
        FontManager.cpp
        FontManager.h
        Graph.cpp
        Graph.h
        MainFrame.cpp
        MainFrame.h
        UserInteractionMessages.h
        LabelBox.cpp
        LabelBox.h
        CircleNodeBoxMessages.h
        Line.cpp
        Line.h
        TextBox.cpp
        TextBox.h
)


target_link_libraries(VisualGraphSFML sfml-graphics sfml-window sfml-system)

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


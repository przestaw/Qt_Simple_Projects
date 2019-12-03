cmake_minimum_required(VERSION 3.5)

project(QTwidget LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

include_directories(include forms)

set(RESOURCES ${CMAKE_CURRENT_SOURCE_DIR}/res/world.qrc)

QT5_ADD_RESOURCES(RESOURCE_ADDED ${RESOURCES})

set(HEADERS
    include/mainwindow.h
    include/node.h
    include/edge.h
    include/graphview.h
    include/graph.h
    include/coordinatesgrid.h
    include/nodeprop.h
    include/edgeprop.h
    )

set(SOURCES
    main.cpp
    src/mainwindow.cpp
    src/node.cpp
    src/edge.cpp
    src/graphview.cpp
    src/graph.cpp
    src/coordinatesgrid.cpp
    src/nodeprop.cpp
    src/edgeprop.cpp
    )

add_executable(QTwidget
    ${SOURCES}
    forms/mainwindow.ui
    ${HEADERS}
    ${RESOURCE_ADDED}
)

target_link_libraries(QTwidget PRIVATE Qt5::Widgets)

set(RESOURCE_ADDED ${RESOURCE_ADDED} PARENT_SCOPE)

#set_source_files_properties(${RESOURCE_ADDED} PROPERTIES GENERATED ON)

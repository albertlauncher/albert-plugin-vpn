cmake_minimum_required(VERSION 3.16)

project(vpn VERSION 7.0)

find_package(Albert REQUIRED)

file(GLOB_RECURSE I18N_SOURCES src/*)

albert_plugin(
    SOURCES
        src/*.h
        src/*.cpp
        vpn.qrc
    INCLUDE PRIVATE
        src
    I18N_SOURCES
        ${I18N_SOURCES}
    QT
        Widgets
)

if(APPLE)

    #target_compile_options(${PROJECT_NAME} PRIVATE "-fobjc-arc")

    albert_plugin_link(PRIVATE
        "objc"
        "-framework SystemConfiguration"
    )

    albert_plugin_include_directories(PRIVATE src/mac)

    albert_plugin_sources(
        src/mac/*.cpp
        src/mac/*.mm
        src/mac/*.h
    )

elseif(UNIX)

    albert_plugin_link_qt(DBus VERSION 6.0 REQUIRED)

    albert_plugin_dbus_interface(
        XML "src/xdg/nm.xml"
        INCLUDE "custom_types.h"
    )

    albert_plugin_include_directories(PRIVATE
        src/xdg  # for custom_types.h
        ${PROJECT_BINARY_DIR}  # for the generated files
    )

    albert_plugin_sources(GLOB
        src/xdg/*.cpp
        src/xdg/*.h
    )

endif()

# YarpArmarxBridges


cmake_minimum_required(VERSION 2.8)

find_package("ArmarXCore" REQUIRED
    PATHS "$ENV{HOME}/armarx/Core/build" )

include(${ArmarXCore_USE_FILE})

depends_on_armarx_package(MemoryX)
armarx_project("YarpArmarxBridges")

find_package(YARP REQUIRED)
include_directories(${YARP_INCLUDE_DIRS})

add_subdirectory(components)

#install_project()



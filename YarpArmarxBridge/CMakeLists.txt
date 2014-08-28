# YarpArmarxBridge

cmake_minimum_required(VERSION 2.8)

find_package("ArmarXCore" REQUIRED)

find_package(YARP REQUIRED)
include_directories(${YARP_INCLUDE_DIRS})
#find_package(ICUB REQUIRED)


# Include provides all necessary ArmarX CMake macros
include(${ArmarXCore_USE_FILE})

# Name for the project
armarx_project("YarpArmarxBridge")

# Specify each ArmarX Package dependency with the following macro
depends_on_armarx_package(RobotAPI)
depends_on_armarx_package(MemoryX)
depends_on_armarx_package(VisionX)

add_subdirectory(etc)
add_subdirectory(source)

install_project()

add_subdirectory(scenarios)

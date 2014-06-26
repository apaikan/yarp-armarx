# YarpArmarxBridges


cmake_minimum_required(VERSION 2.8)

find_package("ArmarXCore" REQUIRED
    PATHS "$ENV{HOME}/armarx/Core/build" )

include(${ArmarXCore_USE_FILE})

depends_on_armarx_package(MemoryX)
armarx_project("YarpArmarxBridges")

find_package(YARP REQUIRED)
include_directories(${YARP_INCLUDE_DIRS})
#link_directories(${YARP_LINK_DIRECTORIES})



#find_package(IVT QUIET)
#if (IVT_FOUND)
#    include_directories(${IVT_INCLUDE_DIRS})
#    message(STATUS "IVT directory: "${IVT_INCLUDE_DIRS})
#endif()

add_subdirectory(YARPImageProvider)

#install_project()



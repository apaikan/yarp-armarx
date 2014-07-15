armarx_component_set_name("ArmarxMotorControlApp")

find_package(ICUB)
armarx_build_if(ICUB_FOUND "icub not available")
if(ICUB_FOUND)
    include_directories(${ICUB_INCLUDE_DIRS})
endif()


set(COMPONENT_LIBS ArmarXInterfaces ArmarXCore ArmarxMotorControl ${YARP_LIBRARIES} icubmod)

set(EXE_SOURCE main.cpp)

armarx_add_component_executable("${EXE_SOURCE}")

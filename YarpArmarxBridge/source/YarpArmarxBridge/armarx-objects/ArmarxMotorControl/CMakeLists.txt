armarx_component_set_name("ArmarxMotorControl")

find_package(ICUB)
armarx_build_if(ICUB_FOUND "icub not available")
if(ICUB_FOUND)
    include_directories(${ICUB_INCLUDE_DIRS})
endif()


set(COMPONENT_LIBS ArmarXInterfaces ArmarXCore ${YARP_LIBRARIES} icubmod)

set(SOURCES ArmarxMotorControl.cpp)
set(HEADERS ArmarxMotorControl.h)

armarx_add_component("${SOURCES}" "${HEADERS}")

# add unit tests
# add_subdirectory(test)

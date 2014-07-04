armarx_component_set_name("YarpHandUnit")

find_package(Eigen3 QUIET)
armarx_build_if(Eigen3_FOUND "Eigen3 not available")
if(Eigen3_FOUND)
    include_directories(${Eigen3_INCLUDE_DIR})
endif()

find_package(Simox QUIET)
armarx_build_if(Simox_FOUND "Simox-VirtualRobot not available")
if(Simox_FOUND)
    include_directories(${Simox_INCLUDE_DIRS})
endif()

find_package(ICUB)
if(ICUB_FOUND)
    include_directories(${ICUB_INCLUDE_DIRS})
endif()


set(COMPONENT_LIBS ArmarXInterfaces ArmarXCore YarpKinematicUnit ${YARP_LIBRARIES} icubmod)

set(SOURCES YarpHandUnit.cpp)
set(HEADERS YarpHandUnit.h)

armarx_add_component("${SOURCES}" "${HEADERS}")

# add unit tests
# add_subdirectory(test)

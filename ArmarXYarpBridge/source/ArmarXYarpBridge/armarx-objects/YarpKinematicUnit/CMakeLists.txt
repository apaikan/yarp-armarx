armarx_component_set_name("YarpKinematicUnit")

#find_package(MyLib QUIET)
#armarx_build_if(MyLib_FOUND "MyLib not available")
#
# all include_directories must be guarded by if(Xyz_FOUND)
# for multiple libraries write: if(X_FOUND AND Y_FOUND)....
#if(MyLib_FOUND)
#    include_directories(${MyLib_INCLUDE_DIRS})
#endif()

find_package(Eigen3 QUIET)
armarx_build_if(Eigen3_FOUND "Eigen3 not available")
include_directories(${Eigen3_INCLUDE_DIR})


armarx_build_if(BUILD "library disabled")

find_package(Simox QUIET)
armarx_build_if(Simox_FOUND "Simox-VirtualRobot not available")
include_directories(${Simox_INCLUDE_DIRS})

set(COMPONENT_LIBS ArmarXInterfaces ArmarXCore ${YARP_LIBRARIES} ${Simox_LIBRARIES})

set(SOURCES YarpKinematicUnit.cpp)
set(HEADERS YarpKinematicUnit.h)

armarx_add_component("${SOURCES}" "${HEADERS}")

# add unit tests
add_subdirectory(test)

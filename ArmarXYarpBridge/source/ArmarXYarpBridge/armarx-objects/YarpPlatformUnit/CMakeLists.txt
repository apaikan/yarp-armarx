armarx_component_set_name("YarpPlatformUnit")

#find_package(MyLib QUIET)
#armarx_build_if(MyLib_FOUND "MyLib not available")
#
# all include_directories must be guarded by if(Xyz_FOUND)
# for multiple libraries write: if(X_FOUND AND Y_FOUND)....
#if(MyLib_FOUND)
#    include_directories(${MyLib_INCLUDE_DIRS})
#endif()

find_package(Simox QUIET)
armarx_build_if(Simox_FOUND "Simox-VirtualRobot not available")
if(Simox_FOUND)
    include_directories(${Simox_INCLUDE_DIRS})
endif()

set(COMPONENT_LIBS RobotAPIInterfaces RobotAPIUnits ${Simox_LIBRARIES})

set(SOURCES YarpPlatformUnit.cpp)
set(HEADERS YarpPlatformUnit.h)

armarx_add_component("${SOURCES}" "${HEADERS}")

# add unit tests
add_subdirectory(test)

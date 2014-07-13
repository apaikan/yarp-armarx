armarx_component_set_name("ArmarxMotorControl")

#find_package(MyLib QUIET)
#armarx_build_if(MyLib_FOUND "MyLib not available")
#
# all include_directories must be guarded by if(Xyz_FOUND)
# for multiple libraries write: if(X_FOUND AND Y_FOUND)....
#if(MyLib_FOUND)
#    include_directories(${MyLib_INCLUDE_DIRS})
#endif()

set(COMPONENT_LIBS ArmarXInterfaces ArmarXCore)

set(SOURCES ArmarxMotorControl.cpp)
set(HEADERS ArmarxMotorControl.h)

armarx_add_component("${SOURCES}" "${HEADERS}")

# add unit tests
add_subdirectory(test)

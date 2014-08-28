armarx_component_set_name("ArmarxFrameGrabberApp")

find_package(IVT QUIET)
armarx_build_if(IVT_FOUND "ivt library not found")
if(IVT_FOUND)
    include_directories(${IVT_INCLUDE_DIRS})
endif()

set(COMPONENT_LIBS ArmarxFrameGrabber  )
#${IVT_LIBRARIES}  ${YARP_LIBRARIES}
set(EXE_SOURCE main.cpp)

armarx_add_component_executable("${EXE_SOURCE}")

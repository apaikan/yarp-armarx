armarx_component_set_name("ArmarxFrameGrabber")

find_package(IVT QUIET)
armarx_build_if(IVT_FOUND "ivt library not found")
if(IVT_FOUND)
    include_directories(${IVT_INCLUDE_DIRS})
endif()

set(COMPONENT_LIBS ArmarXInterfaces ArmarXCore VisionXInterfaces VisionXCore ${IVT_LIBRARIES} ${Boost_LIBRARIES}  ${YARP_LIBRARIES})

set(SOURCES ArmarxFrameGrabber.cpp)
set(HEADERS ArmarxFrameGrabber.h)
armarx_add_component("${SOURCES}" "${HEADERS}")

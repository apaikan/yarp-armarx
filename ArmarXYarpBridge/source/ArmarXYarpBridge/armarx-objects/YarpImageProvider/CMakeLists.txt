
armarx_component_set_name(YarpImageProvider)

find_package(IVT QUIET)
armarx_build_if(IVT_FOUND "ivt library not found")
if(IVT_FOUND)
    include_directories(${IVT_INCLUDE_DIRS})
endif()

set(COMPONENT_LIBS  VisionXCore ${IVT_LIBRARIES} ${Boost_LIBRARIES}  ${YARP_LIBRARIES})
#VisionXInterfaces VisionXCore VisionXTools 
set(SOURCES YarpImageProvider.cpp)
set(HEADERS YarpImageProvider.h)
armarx_add_component("${SOURCES}" "${HEADERS}")


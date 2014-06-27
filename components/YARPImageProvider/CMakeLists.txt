
armarx_component_set_name(YARPImageProvider)

find_package(VisionX REQUIRED)
armarx_build_if(VisionX_FOUND "VisionX library not found")

find_package(IVT QUIET)
armarx_build_if(IVT_FOUND "ivt library not found")


if (IVT_FOUND)
    include_directories(${IVT_INCLUDE_DIRS})
endif()
include_directories(${VisionX_INCLUDE_DIRS})

set(COMPONENT_LIBS VisionXInterfaces VisionXCore VisionXTools ${IVT_LIBRARIES} ${Boost_LIBRARIES} ${YARP_LIBRARIES})

set(SOURCES YARPImageProvider.cpp)
set(HEADERS YARPImageProvider.h)
armarx_add_component("${SOURCES}" "${HEADERS}")

set(EXE_SOURCES main.cpp YARPImageProviderApp.h)
armarx_add_component_executable("${EXE_SOURCES}")


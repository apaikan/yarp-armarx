armarx_component_set_name("YarpImageProviderApp")

#find_package(MyLib QUIET)
#armarx_build_if(MyLib_FOUND "MyLib not available")
#
# all include_directories must be guarded by if(Xyz_FOUND)
# for multiple libraries write: if(X_FOUND AND Y_FOUND)....
#if(MyLib_FOUND)
#    include_directories(${MyLib_INCLUDE_DIRS})
#endif()


find_package(IVT QUIET)
armarx_build_if(IVT_FOUND "ivt library not found")


if(IVT_FOUND)
    include_directories(${IVT_INCLUDE_DIRS})
endif()

set(COMPONENT_LIBS ArmarXInterfaces ArmarXCore YarpImageProvider VisionXInterfaces VisionXCore ${IVT_LIBRARIES}  ${YARP_LIBRARIES} )

set(EXE_SOURCE main.cpp)

armarx_add_component_executable("${EXE_SOURCE}")

###
### CMakeLists.txt file for YarpArmarxBridge Interfaces
###

# Dependencies on interface libraries to other ArmarX Packages must be specified
# in the following variable separated by whitespaces
# set(YarpArmarxBridge_INTERFACE_DEPEND ArmarXCore)

# generate the interface library
armarx_interfaces_generate_library(YarpArmarxBridge 0.1.0 0 "${YarpArmarxBridge_INTERFACE_DEPEND}")

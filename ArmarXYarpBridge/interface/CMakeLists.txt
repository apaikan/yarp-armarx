###
### CMakeLists.txt file for ArmarXYarpBridge Interfaces
###

# Dependencies on interface libraries to other ArmarX Packages must be specified
# in the following variable separated by whitespaces
# set(ArmarXYarpBridge_INTERFACE_DEPEND ArmarXCore)

# generate the interface library
armarx_interfaces_generate_library(ArmarXYarpBridge 0.1.0 0 "${ArmarXYarpBridge_INTERFACE_DEPEND}")


# Libs required for the tests
SET(LIBS ${LIBS} ArmarXCore ArmarxMotorControl)
 
armarx_add_test(ArmarxMotorControlTest ArmarxMotorControlTest.cpp "${LIBS}")

# Libs required for the tests
SET(LIBS ${LIBS} ArmarXCore YarpPlatformUnit)
 
armarx_add_test(YarpPlatformUnitTest YarpPlatformUnitTest.cpp "${LIBS}")
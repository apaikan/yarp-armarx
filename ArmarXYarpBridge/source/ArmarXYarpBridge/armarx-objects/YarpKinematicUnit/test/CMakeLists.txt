
# Libs required for the tests
SET(LIBS ${LIBS} ArmarXCore YarpKinematicUnit)
 
armarx_add_test(YarpKinematicUnitTest YarpKinematicUnitTest.cpp "${LIBS}")
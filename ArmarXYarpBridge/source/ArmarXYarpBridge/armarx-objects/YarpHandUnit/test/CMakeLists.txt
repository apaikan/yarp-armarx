
# Libs required for the tests
SET(LIBS ${LIBS} ArmarXCore YarpHandUnit)
 
armarx_add_test(YarpHandUnitTest YarpHandUnitTest.cpp "${LIBS}")
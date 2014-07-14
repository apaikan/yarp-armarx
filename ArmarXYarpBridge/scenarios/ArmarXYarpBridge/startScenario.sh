export SCRIPT_PATH=/home/apaikan/Install/armarx/Core/build/bin
# Components
$SCRIPT_PATH/startApplication.sh /home/apaikan/Install/yarp-armarx/ArmarXYarpBridge/build/bin/YarpKinematicUnitAppRun --Ice.Config=config/YarpKinematicUnitApp.cfg &

$SCRIPT_PATH/startApplication.sh /home/apaikan/Install/yarp-armarx/ArmarXYarpBridge/build/bin/YarpImageProviderAppRun --Ice.Config=config/YarpImageProviderApp.cfg &

$SCRIPT_PATH/startApplication.sh /home/apaikan/Install/yarp-armarx/ArmarXYarpBridge/build/bin/YarpHandUnitAppRun --Ice.Config=config/YarpHandUnitApp.cfg &

$SCRIPT_PATH/startApplication.sh /home/apaikan/Install/yarp-armarx/ArmarXYarpBridge/build/bin/YarpPlatformUnitAppRun --Ice.Config=config/YarpPlatformUnitApp.cfg &


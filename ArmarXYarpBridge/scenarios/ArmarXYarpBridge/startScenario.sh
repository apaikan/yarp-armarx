export SCRIPT_PATH=/home/SMBAD/paikan/home/armarx/Core/build/bin
# Components
$SCRIPT_PATH/startApplication.sh /home/SMBAD/paikan/home/yarp-armarx/ArmarXYarpBridge/build/bin/YarpKinematicUnitAppRun --Ice.Config=config/YarpKinematicUnitApp.cfg &

$SCRIPT_PATH/startApplication.sh /home/SMBAD/paikan/home/yarp-armarx/ArmarXYarpBridge/build/bin/YarpImageProviderAppRun --Ice.Config=config/YarpImageProviderApp.cfg &


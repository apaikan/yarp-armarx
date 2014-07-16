export SCRIPT_PATH=/home/SMBAD/paikan/home/armarx/Core/build/bin
# Components
$SCRIPT_PATH/startApplication.sh /home/SMBAD/paikan/home/yarp-armarx/YarpArmarxBridge/build/bin/ArmarxFrameGrabberAppRun --Ice.Config=config/ArmarxFrameGrabberApp.cfg &

$SCRIPT_PATH/startApplication.sh /home/SMBAD/paikan/home/yarp-armarx/YarpArmarxBridge/build/bin/ArmarxMotorControlAppRun --Ice.Config=config/ArmarxMotorControlApp.cfg &


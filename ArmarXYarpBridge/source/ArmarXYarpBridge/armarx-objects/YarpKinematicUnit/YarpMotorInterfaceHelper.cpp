/*
 * This file is part of ArmarX.
 *
 * ArmarX is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * ArmarX is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * @package    ArmarXYarpBridge::ArmarXObjects::YarpMotorInterfaceHelper
 * @author     Ali Paikan ( ali dot paikan at iit dot it )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl.txt
 *             GNU General Public License
 */

#include "YarpMotorInterfaceHelper.h"
#include <Core/core/logging/Logging.h>

using namespace std;
using namespace armarx;
using namespace yarp::dev;
using namespace yarp::os;

// YARP_DECLARE_DEVICES(icubmod)
// YARP_REGISTER_DEVICES(icubmod)

YarpMotorInterfaceHelper::YarpMotorInterfaceHelper(const yarp::os::Property& options) 
{

   iEncoder = NULL;
   iPosition = NULL;
   iVelocity = NULL;
   iTorque = NULL;

   YarpMotorInterfaceHelper::options = options;
}

YarpMotorInterfaceHelper::~YarpMotorInterfaceHelper()
{
    YarpMotorInterfaceHelper::close();
}

void YarpMotorInterfaceHelper::close()
{
    driver.close();
}

bool YarpMotorInterfaceHelper::open()
{
    string robotName = options.find("robot").asString();
    string partName = options.find("part").asString();    
    string unitName = (options.check("unit_name")) ? options.find("unit_name").asString() : "YarpKinematicUnit";

    string remoteName = string("/") + robotName + string("/") + partName;
    string localName = string("/") + unitName + string("/") + robotName + string("/") + partName;

    // put the required options
    options.put("device", "remote_controlboard");    
    options.put("local", localName.c_str());
    options.put("remote", remoteName.c_str());

    // open the driver
    if (!driver.open(options)) {
        ARMARX_ERROR_S <<"Cannot open yarp device driver! options: " << options.toString();
        return false;
    }
        
    // view the interfaces
    driver.view(iEncoder);
    if(!iEncoder) {
        ARMARX_ERROR_S << "Failed to open encoders interface of " << partName; 
        return false;
    }
    
    driver.view(iPosition);
    if(!iPosition) {
        ARMARX_ERROR_S << "Failed to open potitions interface of " << partName; 
        return false;
    }
   
    driver.view(iVelocity);
    if(!iVelocity) {
        ARMARX_ERROR_S << "Failed to open velocities interface of " << partName; 
        return false;
    }
 
    driver.view(iTorque);
    if(!iTorque) {
        ARMARX_ERROR_S << "Failed to open torques interface of " << partName; 
        return false;
    }
 
    return true;
}




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

#ifndef _ARMARX_COMPONENT_ArmarXYarpBridge_YarpMotorInterfaceHelper_H
#define _ARMARX_COMPONENT_ArmarXYarpBridge_YarpMotorInterfaceHelper_H


#include <string>

// yarp os headers 
#include <yarp/os/Property.h>

// yarp interfaces
#include <yarp/dev/Drivers.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/IEncoders.h>
#include <yarp/dev/IPositionControl.h>
#include <yarp/dev/IVelocityControl.h>



namespace armarx
{

    /**
     * @class YarpMotorInterfaceHelper
     * @brief A brief description
     *
     * Detailed Description
     */
    class YarpMotorInterfaceHelper
    {
    public:
        YarpMotorInterfaceHelper(const yarp::os::Property& properties);
        virtual ~YarpMotorInterfaceHelper();
        
        bool open();
        void close();

        yarp::dev::IEncoders* getEncoderInterface() { 
            return iEncoder;
        }
        
        yarp::dev::IPositionControl* getPositionInterface() {
            return iPosition;
        }

    private: 
        yarp::os::Property options;
        yarp::dev::PolyDriver   driver; 
        yarp::dev::IEncoders    *iEncoder;
        yarp::dev::IPositionControl    *iPosition;
    };
}

#endif

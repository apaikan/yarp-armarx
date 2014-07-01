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
 * @package    ArmarXYarpBridge::ArmarXObjects::YarpKinematicUnit
 * @author     Ali Paikan ( ali dot paikan at iit dot it )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl.txt
 *             GNU General Public License
 */

#ifndef _ARMARX_COMPONENT_ArmarXYarpBridge_YarpKinematicUnit_H
#define _ARMARX_COMPONENT_ArmarXYarpBridge_YarpKinematicUnit_H


#include <Core/core/Component.h>

#include <Core/interface/units/KinematicUnitInterface.h>

#include <Core/units/KinematicUnit.h>


// yarp interfaces
#include <yarp/dev/IPositionControl.h>
#include <yarp/dev/IEncoders.h>
#include <yarp/dev/Drivers.h>


namespace armarx
{
    /**
     * @class YarpKinematicUnitPropertyDefinitions
     * @brief
     * @ingroup Components
     */
    class YarpKinematicUnitPropertyDefinitions:
        public KinematicUnitPropertyDefinitions
    {
    public:
        YarpKinematicUnitPropertyDefinitions(std::string prefix):
            KinematicUnitPropertyDefinitions(prefix)
        {
            defineRequiredProperty<std::string>("robot", "icub", "Robot name");
            //defineOptionalProperty<std::string>("device", "remote_controlboard", "");
        }
    };

    /**
     * @class YarpKinematicUnit
     * @brief A brief description
     *
     * Detailed Description
     */
    class YarpKinematicUnit :
        virtual public armarx::Component,
            virtual public KinematicUnit,
            virtual public KinematicUnitInterface
    {
    public:
        /**
         * @see armarx::ManagedIceObject::getDefaultName()
         */
        virtual std::string getDefaultName() const
        {
            return "YarpKinematicUnit";
        }

    protected:

        /**
         * @see PropertyUser::createPropertyDefinitions()
         */
        virtual PropertyDefinitionsPtr createPropertyDefinitions();

        // UnitResourceManagementInterface interface
    public:
        void request(const Ice::Current &);
        void release(const Ice::Current &);

        // UnitExecutionManagementInterface interface
    public:
        void init(const Ice::Current &);
        void start(const Ice::Current &);
        void stop(const Ice::Current &);
        UnitExecutionState getExecutionState(const Ice::Current &);

        // KinematicUnitInterface interface
    public:
        void requestJoints(const StringSequence &, const Ice::Current &);
        void releaseJoints(const StringSequence &, const Ice::Current &);
        void switchControlMode(const NameControlModeMap &, const Ice::Current &);
        void setJointAngles(const NameValueMap &, const Ice::Current &);
        void setJointVelocities(const NameValueMap &, const Ice::Current &);
        void setJointTorques(const NameValueMap &, const Ice::Current &);
        void setJointAccelerations(const NameValueMap &, const Ice::Current &);
        void setJointDecelerations(const NameValueMap &, const Ice::Current &);

        // yarp related properties 
    private: 
        yarp::dev::PolyDriver   driver; 
        yarp::dev::IEncoders    *encoders;
        yarp::dev::IPositionControl    *positions;
    };
}

#endif

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
 * @package    YarpArmarxBridge::ArmarXObjects::ArmarxMotorControl
 * @author     Ali Paikan ( ali dot paikan at gmail dot com )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl.txt
 *             GNU General Public License
 */

#ifndef _ARMARX_MANAGEDICEOBJECT_YarpArmarxBridge_ArmarxMotorControl_H
#define _ARMARX_MANAGEDICEOBJECT_YarpArmarxBridge_ArmarxMotorControl_H


#include <Core/core/Component.h>

namespace armarx
{
    /**
     * @class ArmarxMotorControlPropertyDefinitions
     * @brief
     * @ingroup Components
     */
    class ArmarxMotorControlPropertyDefinitions:
        public ComponentPropertyDefinitions
    {
    public:
        ArmarxMotorControlPropertyDefinitions(std::string prefix):
            ComponentPropertyDefinitions(prefix)
        {
            defineOptionalProperty<std::string>("Robot", std::string("icub"), "Robot name");
            defineOptionalProperty<std::string>("Parts", "left_arm:Left ArmWithHand;right_arm:Right ArmWithHand;head:Head;torso:Hip;left_leg:Left Leg;right_leg:Right Leg", "List of robot part names (icubName:SimoxRobotNodeSetName)");
            //defineOptionalProperty<std::string>("device", "remote_controlboard", "");
        }
    };


    /**
     * @class ArmarxMotorControl
     * @brief A brief description
     *
     * Detailed Description
     */
    class ArmarxMotorControl :
        virtual public armarx::Component
    {
    public:
        /**
         * @see armarx::ManagedIceObject::getDefaultName()
         */
        virtual std::string getDefaultName() const
        {
            return "ArmarxMotorControl";
        }

    protected:

        /**
         * @see PropertyUser::createPropertyDefinitions()
         */
        virtual PropertyDefinitionsPtr createPropertyDefinitions();

        /**
         * @see armarx::ManagedIceObject::onInitComponent()
         */
        virtual void onInitComponent();

        /**
         * @see armarx::ManagedIceObject::onConnectComponent()
         */
        virtual void onConnectComponent();

        /**
         * @see armarx::ManagedIceObject::onDisconnectComponent()
         */
        virtual void onDisconnectComponent();

        /**
         * @see armarx::ManagedIceObject::onExitComponent()
         */
        virtual void onExitComponent();
    };
}

#endif

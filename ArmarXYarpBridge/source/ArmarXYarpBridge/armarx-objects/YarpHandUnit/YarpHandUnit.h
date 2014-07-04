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
 * @package    ArmarXYarpBridge::ArmarXObjects::YarpHandUnit
 * @author     Ali Paikan ( ali dot paikan at iit dot it )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl.txt
 *             GNU General Public License
 */

#ifndef _ARMARX_COMPONENT_ArmarXYarpBridge_YarpHandUnit_H
#define _ARMARX_COMPONENT_ArmarXYarpBridge_YarpHandUnit_H


#include <ArmarXYarpBridge/armarx-objects/YarpKinematicUnit/YarpMotorInterfaceHelper.h>
#include <Core/core/Component.h>
#include <Core/core/services/tasks/RunningTask.h>
#include <Core/units/HandUnit.h>

namespace armarx
{
    /**
     * @class YarpHandUnitPropertyDefinitions
     * @brief
     * @ingroup Components
     */
    class YarpHandUnitPropertyDefinitions:
        public HandUnitPropertyDefinitions
    {
    public:
        YarpHandUnitPropertyDefinitions(std::string prefix):
            HandUnitPropertyDefinitions(prefix)
        {
            defineOptionalProperty<std::string>("Robot", std::string("icub"), "Robot name");
            defineRequiredProperty<std::string>("YarpRobotPart", "Name of the robotpart");

            //defineRequiredProperty<std::string>("PropertyName", "Description");
            //defineOptionalProperty<std::string>("PropertyName", "DefaultValue", "Description");
//            defineOptionalProperty<std::string>("Parts", "left_arm:Left Arm;right_arm:Right Arm", "List of robot part names (icubName:SimoxRobotNodeSetName)");
        }
    };

    /**
     * @class YarpHandUnit
     * @brief A brief description
     *
     * Detailed Description
     */
    class YarpHandUnit :
        virtual public armarx::Component,
        virtual public HandUnit
    {
    public:
        YarpHandUnit();
        /**
         * @see armarx::ManagedIceObject::getDefaultName()
         */
        virtual std::string getDefaultName() const
        {
            return "YarpHandUnit";
        }

    protected:

        /**
         * @see PropertyUser::createPropertyDefinitions()
         */
        virtual PropertyDefinitionsPtr createPropertyDefinitions();

        // HandUnitInterface interface
    public:
        void open(const Ice::Current &);
        void close(const Ice::Current &);
        void preshape(const std::string &preshapeName, const Ice::Current &);
        NameValueMap getPreshapeJointValues(const std::string&, const Ice::Current&);

        // HandUnit interface
    public:
        void onInitHandUnit();
        void onStartHandUnit();
        void onExitHandUnit();
        
    protected:

        std::vector<std::string> getPreShapeSet(const std::string& preshapePrefix);

        YarpMotorInterfaceHelper*   yarpMotorInterface;
        enum HandState
        {
            eUnkown,
            ePreshape,
            eOpen,
            eClosed
        };
        HandState handState;
        typedef std::pair<HandState, std::vector<std::string> >  CommandBuffer;
        CommandBuffer commandBuffer;
        Mutex commandMutex;

        RunningTask<YarpHandUnit>::pointer_type task;
    private: 
        void run();
    };
}

#endif

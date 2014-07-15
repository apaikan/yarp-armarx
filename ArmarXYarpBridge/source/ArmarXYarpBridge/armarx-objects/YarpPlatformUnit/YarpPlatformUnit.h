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
 * @package    ArmarXYarpBridge::ArmarXObjects::YarpPlatformUnit
 * @author     Mirko Waechter ( waechter at kit dot edu )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl.txt
 *             GNU General Public License
 */

#ifndef _ARMARX_COMPONENT_ArmarXYarpBridge_YarpPlatformUnit_H
#define _ARMARX_COMPONENT_ArmarXYarpBridge_YarpPlatformUnit_H


#include <Core/core/Component.h>
#include <Core/core/services/tasks/PeriodicTask.h>

#include <Core/units/PlatformUnit.h>

namespace armarx
{
    /**
     * @class YarpPlatformUnitPropertyDefinitions
     * @brief
     * @ingroup Components
     */
    class YarpPlatformUnitPropertyDefinitions:
        public PlatformUnitPropertyDefinitions
    {
    public:
        YarpPlatformUnitPropertyDefinitions(std::string prefix):
            PlatformUnitPropertyDefinitions(prefix)
        {
            //defineRequiredProperty<std::string>("PropertyName", "Description");
            //defineOptionalProperty<std::string>("PropertyName", "DefaultValue", "Description");
        }
    };

    /**
     * @class YarpPlatformUnit
     * @brief A brief description
     *
     * Detailed Description
     */
    class YarpPlatformUnit :
        virtual public armarx::Component,
            virtual public PlatformUnit
    {
    public:
        /**
         * @see armarx::ManagedIceObject::getDefaultName()
         */
        virtual std::string getDefaultName() const
        {
            return "YarpPlatformUnit";
        }
    public:
        void move(Ice::Float, Ice::Float, Ice::Float, const Ice::Current &);
        void moveRelative(Ice::Float, Ice::Float, Ice::Float, Ice::Float, Ice::Float, const Ice::Current &);
        void setMaxVelocities(Ice::Float, Ice::Float, const Ice::Current &);

        // PlatformUnit interface
        void onInitPlatformUnit();
        void onStartPlatformUnit();
        void onExitPlatformUnit();
    protected:
        /**
         * @see PropertyUser::createPropertyDefinitions()
         */
        virtual PropertyDefinitionsPtr createPropertyDefinitions();

        void report();

        // PlatformUnitInterface interface

        PeriodicTask<YarpPlatformUnit>::pointer_type reportTask;
    };
}

#endif

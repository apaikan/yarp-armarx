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
 * @package    YarpArmarxBridge::application::ArmarxFrameGrabber
 * @author     Ali Paikan ( ali dot paikan at gmail dot com )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl.txt
 *             GNU General Public License
 */

#ifndef _ARMARX_APPLICATION_YarpArmarxBridge_ArmarxFrameGrabber_H
#define _ARMARX_APPLICATION_YarpArmarxBridge_ArmarxFrameGrabber_H


#include <YarpArmarxBridge/armarx-objects/ArmarxFrameGrabber/ArmarxFrameGrabber.h>

#include <Core/core/application/Application.h>

namespace armarx
{
    /**
     * @class ArmarxFrameGrabberApp
     * @brief A brief description
     *
     * Detailed Description
     */
    class ArmarxFrameGrabberApp :
        virtual public armarx::Application
    {
        /**
         * @see armarx::Application::setup()
         */
        void setup(const ManagedIceObjectRegistryInterfacePtr& registry,
                   Ice::PropertiesPtr properties)
        {
            registry->addObject( Component::create<ArmarxFrameGrabber>(properties) );
        }
    };
}

#endif

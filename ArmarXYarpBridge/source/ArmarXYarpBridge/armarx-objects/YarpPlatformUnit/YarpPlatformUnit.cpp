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

#include "YarpPlatformUnit.h"


using namespace armarx;





void armarx::YarpPlatformUnit::move(Ice::Float, Ice::Float, Ice::Float, const Ice::Current &)
{
    ARMARX_WARNING << deactivateSpam(10) << "not yet implemented";
}

void armarx::YarpPlatformUnit::moveRelative(Ice::Float, Ice::Float, Ice::Float, Ice::Float, Ice::Float, const Ice::Current &)
{
    ARMARX_WARNING << deactivateSpam(10) << "not yet implemented";
}

void armarx::YarpPlatformUnit::setMaxVelocities(Ice::Float, Ice::Float, const Ice::Current &)
{
    ARMARX_WARNING << deactivateSpam(10) << "not yet implemented";
}

void armarx::YarpPlatformUnit::onInitPlatformUnit()
{
}

void armarx::YarpPlatformUnit::onStartPlatformUnit()
{
    reportTask = new PeriodicTask<YarpPlatformUnit>(this, &YarpPlatformUnit::report, 100);
    reportTask->start();
}

void armarx::YarpPlatformUnit::onExitPlatformUnit()
{
    reportTask->stop();
}


PropertyDefinitionsPtr YarpPlatformUnit::createPropertyDefinitions()
{
    return PropertyDefinitionsPtr(new YarpPlatformUnitPropertyDefinitions(
                                      getConfigIdentifier()));
}

void YarpPlatformUnit::report()
{
    listenerPrx->reportNewTargetPose(0,0,0);
    listenerPrx->reportPlatformPose(0,0,0);
    listenerPrx->reportPlatformVelocity(0,0,0);
}

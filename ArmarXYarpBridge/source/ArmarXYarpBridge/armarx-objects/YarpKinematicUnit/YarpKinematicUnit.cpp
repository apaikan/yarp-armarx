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

#include "YarpKinematicUnit.h"


using namespace armarx;


void YarpKinematicUnit::onInitComponent()
{

}


void YarpKinematicUnit::onConnectComponent()
{

}


void YarpKinematicUnit::onDisconnectComponent()
{

}


void YarpKinematicUnit::onExitComponent()
{

}

PropertyDefinitionsPtr YarpKinematicUnit::createPropertyDefinitions()
{
    return PropertyDefinitionsPtr(new YarpKinematicUnitPropertyDefinitions(
                                      getConfigIdentifier()));
}



void armarx::YarpKinematicUnit::request(const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::release(const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::init(const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::start(const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::stop(const Ice::Current &)
{
}

UnitExecutionState armarx::YarpKinematicUnit::getExecutionState(const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::requestJoints(const StringSequence &, const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::releaseJoints(const StringSequence &, const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::switchControlMode(const NameControlModeMap &, const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::setJointAngles(const NameValueMap &, const Ice::Current &)
{

}

void armarx::YarpKinematicUnit::setJointVelocities(const NameValueMap &, const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::setJointTorques(const NameValueMap &, const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::setJointAccelerations(const NameValueMap &, const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::setJointDecelerations(const NameValueMap &, const Ice::Current &)
{
}

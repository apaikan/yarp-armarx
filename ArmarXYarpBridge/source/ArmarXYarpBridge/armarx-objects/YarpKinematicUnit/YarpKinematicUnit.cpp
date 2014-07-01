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


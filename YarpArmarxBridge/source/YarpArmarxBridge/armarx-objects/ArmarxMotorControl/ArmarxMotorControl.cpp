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

#include "ArmarxMotorControl.h"
#include "YarpMotorControlHelper.h"

#include <sstream>

// VirtualRobot
#include <VirtualRobot/XML/RobotIO.h>

using namespace std;
using namespace armarx;
using namespace yarp::os;
using namespace yarp::dev;

PropertyDefinitionsPtr ArmarxMotorControl::createPropertyDefinitions()
{
    return PropertyDefinitionsPtr(new ArmarxMotorControlPropertyDefinitions(
                                      getConfigIdentifier()));
}

void ArmarxMotorControl::onInitComponent()
{
    robotName  = getProperty<std::string>("Robot").getValue();
    robotParts  = getProperty<std::string>("Parts").getValue();

    Drivers::factory().add(new DriverCreatorOf<YarpMotorControlHelper>("armarxcontrol", 
                           "controlboard",
                           "ArmarxMotorControl"));

    std::vector<std::string> partPairs;
    boost::split(partPairs,
                 robotParts,
                 boost::is_any_of(";"),
                 boost::token_compress_on);
    for(size_t i = 0; i < partPairs.size(); i++)
    {
        std::vector<std::string> ids;
        boost::split(ids,
                     partPairs.at(i),
                     boost::is_any_of(":"),
                     boost::token_compress_on);
        if(ids.size() != 2)
        {
            ARMARX_WARNING << "wrong size of identifiers: " << ids.size();
        }
        else
        {
            ARMARX_IMPORTANT<<ids[0]<<" : "<<ids[1];
            m_partDrivers[ids[0]] = createPart(ids[0].c_str());
            /*
            RobotNodeSetPtr rns = robot->getRobotNodeSet(ids[1]);
            std::vector<RobotNodePtr> nodes = rns->getAllRobotNodes();
            for(size_t j = 0; j < nodes.size(); j++)
            {
                nameIndexMap[nodes.at(j)->getName()] =  std::make_pair(ids[1], j);
            }
            */
        }
    }
    usingProxy(getProperty<std::string>("KinematicUnitName").getValue());
}


void ArmarxMotorControl::onConnectComponent()
{
    // get proxy to send commands to the kinematic unit
    std::string kinematicUnitInstructionChannel = getProperty<std::string>("KinematicUnitName").getValue();
    kinematicUnitInterfacePrx = getProxy<KinematicUnitInterfacePrx>(kinematicUnitInstructionChannel);

    for(DriverMap::const_iterator it = m_partDrivers.begin(); it != m_partDrivers.end(); ++it)
    {
        YarpMotorControlHelper* ctrlHelper = dynamic_cast<YarpMotorControlHelper*>((it->second)->getImplementation());
        //ctrlHelper->setKinematicUnitInterface(kinematicUnitInterfacePrx);
    }
}


void ArmarxMotorControl::onDisconnectComponent()
{

}


void ArmarxMotorControl::onExitComponent()
{
    ARMARX_IMPORTANT<<"onExitComponent";
    for(DriverMap::const_iterator it = m_partDrivers.begin(); it != m_partDrivers.end(); ++it)
    {
        if(it->second) {
            it->second->close();
            delete it->second;
        }
   }
}

yarp::dev::PolyDriver* ArmarxMotorControl::createPart(const char *name) 
{
    ARMARX_INFO<<"Creating interface for body part " << name;
    yarp::os::Property options;
    options.put("device", "controlboard");
    options.put("subdevice", "armarxcontrol");
    options.put("joint_device", "robot_joints");
    ostringstream portname;
    portname<<"/"<<robotName<<"/"<<name;
    options.put("name", portname.str().c_str());

    // make them to be taken from robot xml description
    options.put("joints_number", 10);

    PolyDriver* driver = new yarp::dev::PolyDriver(options);
    if (!driver->isValid()){
        ARMARX_ERROR<<"Device not available. Here are the known devices:";
        ARMARX_ERROR<<yarp::dev::Drivers::factory().toString();
        return NULL;
    }
    return driver;
}

/*
VirtualRobot::RobotPtr ArmarxMotorControl::loadRobotFile(std::string fileName)
{
    VirtualRobot::RobotPtr robot;

    if (verbose)
        ARMARX_INFO << "Loading KinematicUnit " << kinematicUnitName << " from " << kinematicUnitFile << " ..." << flush;

    if (!ArmarXDataPath::getAbsolutePath(fileName,fileName))
    {
       ARMARX_INFO << "Could not find Robot XML file with name " << fileName << flush;
    }
    robot = RobotIO::loadRobot(fileName);
    if (!robot)
    {
        ARMARX_INFO << "Could not find Robot XML file with name " << fileName << "(" << kinematicUnitName << ")" << flush;
    }

    return robot;
}
*/



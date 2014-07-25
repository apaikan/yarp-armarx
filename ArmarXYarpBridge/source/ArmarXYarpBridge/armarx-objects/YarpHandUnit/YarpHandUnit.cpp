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
 * @author     Mirko Waechter ( mirko.waechter at kit dot edu)
 * @author     Ali Paikan ( ali dot paikan at iit dot it )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl.txt
 *             GNU General Public License
 */

#include "YarpHandUnit.h"


using namespace armarx;

#include <VirtualRobot/Robot.h>
#include <VirtualRobot/RobotNodeSet.h>
#include <VirtualRobot/EndEffector/EndEffector.h>
#include <VirtualRobot/RobotConfig.h>
#include <ArmarXYarpBridge/armarx-objects/YarpKinematicUnit/YarpMotorInterfaceHelper.h>

using namespace VirtualRobot;


YarpHandUnit::YarpHandUnit() :
    yarpMotorInterface(0), task(0)
{

}

PropertyDefinitionsPtr YarpHandUnit::createPropertyDefinitions()
{
    return PropertyDefinitionsPtr(new YarpHandUnitPropertyDefinitions(
                                      getConfigIdentifier()));
}

void YarpHandUnit::run()
{
//    while(!task->isStopped())
//    {
//        {
//            ScopedLock lock(commandMutex);
//            commandBuffer = ;
//        }
//        usleep(10000);
//    }
}



void armarx::YarpHandUnit::open(const Ice::Current &)
{
    //ARMARX_IMPORTANT<<"Received Open command";
    //ScopedLock lock(commandMutex);

}

void armarx::YarpHandUnit::close(const Ice::Current &)
{
    //ARMARX_IMPORTANT<<"Received Close command";
    //ScopedLock lock(commandMutex);
}

void armarx::YarpHandUnit::preshape(const std::string &preshapeName, const Ice::Current &)
{
    ScopedLock lock(commandMutex);
    if(handshapeSequence.find(preshapeName) != handshapeSequence.end())
        handPositionMove(handshapeSequence[preshapeName]);
    else    
        ARMARX_WARNING << "Cannot find preshape command " << preshapeName;
}

void armarx::YarpHandUnit::onInitHandUnit()
{
    handshapeSequence = loadPreshapes(getProperty<std::string>("EndeffectorName").getValue());
    // create a simple mapping of the simox joints name and the robot joint indices 
    if(handshapeSequence.size()) 
    {
        NameValueMap &jointsMap = handshapeSequence.begin()->second;
        int index = 7; // the first hand's joint  
        for(NameValueMap::const_iterator it = jointsMap.begin(); it != jointsMap.end(); it++)
            nameIndexMap[it->first] = index++;
    }
    
    std::string robotName  = getProperty<std::string>("Robot").getValue();
    std::string part  = getProperty<std::string>("YarpRobotPart").getValue();
    std::string unitName = std::string("YarpHandUnit_") + part;
    yarp::os::Property options;
    options.put("robot", robotName.c_str());
    options.put("part", part.c_str());
    options.put("unit_name", unitName.c_str());
    yarpMotorInterface = new YarpMotorInterfaceHelper(options);
    //task = new RunningTask<YarpHandUnit>(this, &YarpHandUnit::run);
}

void armarx::YarpHandUnit::onStartHandUnit()
{
    yarpMotorInterface->open();

    //if(yarpMotorInterface->open())
    //    task->start();
}

void armarx::YarpHandUnit::onExitHandUnit()
{
    //if(task)
    //    task->stop();
    delete yarpMotorInterface;
}



YarpHandUnit::PreshapeSequences YarpHandUnit::loadPreshapes(std::string endEffectorName)
{
    PreshapeSequences eftSeq;
    std::vector<std::string> preshapes = robot->getEndEffector(endEffectorName)->getPreshapes();
    for(size_t i=0; i < preshapes.size(); i++)
    {
        const std::string & preshapeName = preshapes.at(i);
        eftSeq[preshapeName] = getPreshapeJointValues(preshapeName);
    }
    return eftSeq;
}

void YarpHandUnit::handPositionMove(NameValueMap &jointsMap)
{
    if(!yarpMotorInterface)
        return;
    double velocity = getProperty<double>("EndeffectorVelocity").getValue();
    for(NameValueMap::const_iterator it = jointsMap.begin(); it != jointsMap.end(); ++it)
    {
        yarpMotorInterface->getPositionInterface()->setRefSpeed(nameIndexMap[it->first], velocity);
        yarpMotorInterface->getPositionInterface()->positionMove(nameIndexMap[it->first], it->second*180/M_PI);
    }
}


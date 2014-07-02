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
 * @author     Mirko Waechter ( mirko.waechter at kit dot edu)
 * @author     Ali Paikan ( ali dot paikan at iit dot it )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl.txt
 *             GNU General Public License
 */

#include "YarpKinematicUnit.h"
#include "YarpMotorInterfaceHelper.h"

#include <VirtualRobot/Robot.h>
#include <VirtualRobot/RobotNodeSet.h>
#include <VirtualRobot/EndEffector/EndEffector.h>

using namespace armarx;
using namespace VirtualRobot;


void YarpKinematicUnit::onInitKinematicUnit()
{
    std::string robotName  = getProperty<std::string>("Robot").getValue();
    std::string parts  = getProperty<std::string>("Parts").getValue();
    std::vector<std::string> partPairs;
    boost::split(partPairs,
                 parts,
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
            yarp::os::Property options;
            options.put("robot", robotName.c_str());
            options.put("part", ids[0]);
            yarpMotorInterfaces[ids[1]] = new YarpMotorInterfaceHelper(options);
            RobotNodeSetPtr rns = robot->getRobotNodeSet(ids[1]);
            std::vector<RobotNodePtr> nodes = rns->getAllRobotNodes();
            for(size_t j = 0; j < nodes.size(); j++)
            {
                nameIndexMap[nodes.at(j)->getName()] =  std::make_pair(ids[1], j);
            }
        }
    }
}

void YarpKinematicUnit::onStartKinematicUnit()
{
    task = new PeriodicTask<YarpKinematicUnit>(this, &YarpKinematicUnit::report, 20);
    bool success = true;
    for(InterfaceMap::iterator it = yarpMotorInterfaces.begin(); it != yarpMotorInterfaces.end(); it++)
    {
        success &= it->second->open();
    }
    if(success)
        task->start();

}

void YarpKinematicUnit::onExitKinematicUnit()
{
    if(task)
        task->stop();
    for(InterfaceMap::iterator it = yarpMotorInterfaces.begin(); it != yarpMotorInterfaces.end(); it++)
    {
        delete it->second;

    }
    yarpMotorInterfaces.clear();
}


PropertyDefinitionsPtr YarpKinematicUnit::createPropertyDefinitions()
{
    return PropertyDefinitionsPtr(new YarpKinematicUnitPropertyDefinitions(
                                      getConfigIdentifier()));
}



void armarx::YarpKinematicUnit::switchControlMode(const NameControlModeMap &, const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::setJointAngles(const NameValueMap &jointsMap , const Ice::Current &)
{

    VirtualRobot::RobotNodeSetPtr rns = robot->getRobotNodeSet("Left Arm");

    std::vector<VirtualRobot::RobotNodePtr> nodes = rns->getAllRobotNodes();
    for(NameValueMap::const_iterator it = jointsMap.begin(); it != jointsMap.end(); it++)
    {
        std::string setName = nameIndexMap[it->first].first;
        int index = nameIndexMap[it->first].second;
        InterfaceMap::iterator itInterface = yarpMotorInterfaces.find(setName);
        if(itInterface != yarpMotorInterfaces.end())
        {
            if(!itInterface->second->getPositionInterface())
                return;
            itInterface->second->getPositionInterface()->positionMove(index, it->second*180/M_PI);
        }
//        for(size_t i = 0; i < nodes.size(); i++)
//        {
//            if(nodes[i]->getName() == it->first)
//            {
////                ARMARX_IMPORTANT << "i: " << i << " name: " << it->first<< " value: " << it->second;

//                fakeInterface->getPositionInterface()->positionMove(i, it->second*180/M_PI);
//                break;
//            }
//        }
    }
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

void YarpKinematicUnit::report()
{
//    if(!fakeInterface->getEncoderInterface())
//    {
//        ARMARX_ERROR << deactivateSpam(3) << "getEncoderInterface is zero";
//        return;
//    }
//    VirtualRobot::RobotNodeSetPtr rns = robot->getRobotNodeSet("Left Arm");
//    std::vector<VirtualRobot::RobotNodePtr> nodes = rns->getAllRobotNodes();
//    int jointsNum = 0;
//    if(!fakeInterface->getEncoderInterface()->getAxes(&jointsNum))
//    {
//        ARMARX_ERROR << deactivateSpam(3) << "Failed to get joint count";
//        return;
//    }
//    double *  encoderValues = new double[jointsNum];
//    try
//    {

//        fakeInterface->getEncoderInterface()->getEncoders(encoderValues);
//        NameValueMap newValues;
//        for(size_t i = 0; i < nodes.size() && i < jointsNum; i++)
//        {
//            newValues[nodes.at(i)->getName()] = encoderValues[i]/180.0*M_PI;
//        }
//        delete [] encoderValues;
//        encoderValues = NULL;
//        listenerPrx->reportJointAngles(newValues, true);
//    }
//    catch(...)
//    {
//        delete [] encoderValues;
//        throw;
//    }

}


void armarx::YarpKinematicUnit::requestJoints(const StringSequence &, const Ice::Current &)
{
}

void armarx::YarpKinematicUnit::releaseJoints(const StringSequence &, const Ice::Current &)
{
}

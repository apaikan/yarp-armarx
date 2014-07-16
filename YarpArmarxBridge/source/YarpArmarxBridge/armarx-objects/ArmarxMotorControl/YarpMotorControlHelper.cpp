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
 * @package    YarpMotorControlHelper
 * @author     Ali Paikan ( ali dot paikan at gmail dot com )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl.txt
 *             GNU General Public License
 */

#include "YarpMotorControlHelper.h"
#include <yarp/dev/ControlBoardInterfacesImpl.inl>

using namespace armarx;
using namespace yarp::os;
using namespace yarp::dev;


YarpMotorControlHelper::YarpMotorControlHelper() : 
    ImplementPositionControl<YarpMotorControlHelper, IPositionControl>(this)
{
}

YarpMotorControlHelper::~YarpMotorControlHelper()
{

}

void YarpMotorControlHelper::setKinematicUnitInterface(const KinematicUnitInterfacePrx prx)
{
    kinematicUnitInterfacePrx = prx;
}


bool YarpMotorControlHelper::open(yarp::os::Searchable& config)
{

    //printf("YarpMotorControlHelper::open() : %s\n", config.toString().c_str());
    int njoints = config.find("joints_number").asInt();
    axisMap = allocAndCheck<int>(njoints);
    angleToEncoder = allocAndCheck<double>(njoints);
    zeros = allocAndCheck<double>(njoints);
    for(int i=0; i<njoints; i++)
    {
        axisMap[i] = i;                     // joints are ordered incrementally 
        zeros[i] = 0.0;                     // all the joint default value set to zero
        angleToEncoder[i] = 180.0/M_PI;     // radian to degree
    }        
    
    ImplementPositionControl<YarpMotorControlHelper, IPositionControl>::
        initialize(njoints, axisMap, angleToEncoder, zeros);
}

bool YarpMotorControlHelper::close(void)
{
    ImplementPositionControl<YarpMotorControlHelper, IPositionControl>::uninitialize();
    checkAndDestroy<double>(zeros);
    checkAndDestroy<double>(angleToEncoder);
    checkAndDestroy<int>(axisMap);
}

bool YarpMotorControlHelper::getAxes(int *ax) { }
bool YarpMotorControlHelper::setPositionModeRaw() { }
bool YarpMotorControlHelper::positionMoveRaw(int j, double ref) { printf("positionMoveRaw\n");}
bool YarpMotorControlHelper::positionMoveRaw(const double *refs) { printf("positionMoveRaw(doubles)\n");}
bool YarpMotorControlHelper::relativeMoveRaw(int j, double delta) { }
bool YarpMotorControlHelper::relativeMoveRaw(const double *deltas) { }
bool YarpMotorControlHelper::checkMotionDoneRaw(bool *flag) { }
bool YarpMotorControlHelper::checkMotionDoneRaw(int j, bool *flag) { }
bool YarpMotorControlHelper::setRefSpeedRaw(int j, double sp) { }
bool YarpMotorControlHelper::setRefSpeedsRaw(const double *spds) { }
bool YarpMotorControlHelper::setRefAccelerationRaw(int j, double acc) { }
bool YarpMotorControlHelper::setRefAccelerationsRaw(const double *accs) { }
bool YarpMotorControlHelper::getRefSpeedRaw(int j, double *ref) { }
bool YarpMotorControlHelper::getRefSpeedsRaw(double *spds) { }
bool YarpMotorControlHelper::getRefAccelerationRaw(int j, double *acc) { }
bool YarpMotorControlHelper::getRefAccelerationsRaw(double *accs) { }
bool YarpMotorControlHelper::stopRaw(int j) { }
bool YarpMotorControlHelper::stopRaw() { }


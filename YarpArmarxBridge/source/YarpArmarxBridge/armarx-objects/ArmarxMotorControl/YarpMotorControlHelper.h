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
 * @author     Ali Paikan ( ali dot paikan at iit dot it )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl.txt
 *             GNU General Public License
 */

#ifndef _ARMARX_COMPONENT_YarpArmarxBridge_YarpMotorControlHelper_H
#define _ARMARX_COMPONENT_YarpArmarxBridge_YarpMotorControlHelper_H

#include <yarp/dev/DeviceDriver.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/ControlBoardInterfacesImpl.h>

#include <map>

namespace armarx
{

    /**
     * @class YarpMotorControlHelper
     * @brief A brief description
     *
     * Detailed Description
     */
    class YarpMotorControlHelper :
        public yarp::dev::DeviceDriver,
        public yarp::dev::IPositionControlRaw,
        public yarp::dev::ImplementPositionControl<YarpMotorControlHelper, yarp::dev::IPositionControl>
    {
    public:
        YarpMotorControlHelper();
        virtual ~YarpMotorControlHelper();

        /*
         * Implelenting YARP device 
         */
        virtual bool open(yarp::os::Searchable& config);

        virtual bool close(void);

        /*
         * Implementing IPositionControlRaw
         */
        virtual bool getAxes(int *ax);
        virtual bool setPositionModeRaw();
        virtual bool positionMoveRaw(int j, double ref);
        virtual bool positionMoveRaw(const double *refs);
        virtual bool relativeMoveRaw(int j, double delta);
        virtual bool relativeMoveRaw(const double *deltas);
        virtual bool checkMotionDoneRaw(bool *flag);
        virtual bool checkMotionDoneRaw(int j, bool *flag);
        virtual bool setRefSpeedRaw(int j, double sp);
        virtual bool setRefSpeedsRaw(const double *spds);
        virtual bool setRefAccelerationRaw(int j, double acc);
        virtual bool setRefAccelerationsRaw(const double *accs);
        virtual bool getRefSpeedRaw(int j, double *ref);
        virtual bool getRefSpeedsRaw(double *spds);
        virtual bool getRefAccelerationRaw(int j, double *acc);
        virtual bool getRefAccelerationsRaw(double *accs);
        virtual bool stopRaw(int j);
        virtual bool stopRaw();

    private:
        int* axisMap;
        double* angleToEncoder;
        double* zeros;

        typedef std::map<std::string, yarp::dev::PolyDriver> DriverMap;
        DriverMap m_partDrivers; 
        yarp::dev::PolyDriver* createPart(const char *name);
    };
}

#endif

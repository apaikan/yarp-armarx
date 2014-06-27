/*
 * This file is part of ArmarX.
 *
 * ArmarX is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as
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
 * @package    VisionX::Component
 * @author     Ali Paikan ( ali dot paikan at iit dot it )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl-2.0.txt
 *             GNU General Public License
 */


#ifndef ARMARX_COMPONENT_DUMMYIMAGEPROVIDER_H
#define ARMARX_COMPONENT_DUMMYIMAGEPROVIDER_H

#include <Core/core/Component.h>
#include <Core/core/application/properties/Properties.h>

/* VisionX */
#include <VisionX/core/CapturingImageProvider.h>
#include <VisionX/interface/component/Calibration.h>
//#include <VisionX/tools/FPSCounter.h>

/* IVT */
#include <Image/ByteImage.h>
#include <Calibration/StereoCalibration.h>

/* YARP */
#include <yarp/os/BufferedPort.h>
#include <yarp/sig/Image.h>


namespace visionx
{
    class YARPImageProviderPropertyDefinitions:
            public armarx::ComponentPropertyDefinitions
    {
    public:
        YARPImageProviderPropertyDefinitions(std::string prefix):
            ComponentPropertyDefinitions(prefix)
        {
            defineOptionalProperty<std::string>("Camera", std::string("left"), "Which camera image should be provide: 'left', 'right', 'both'");
            defineOptionalProperty<std::string>("RemoteLeft", std::string("/icub/cam/left"), "Romote Yarp port to receive the left image");
            defineOptionalProperty<std::string>("RemoteRight", std::string("/icub/cam/right"), "Romote Yarp port to receive the right image");
            defineOptionalProperty<std::string>("Carrier", std::string("udp"), "Yarp Connection carrier");
            defineOptionalProperty<std::string>("CalibrationFile", "", "Camera calibration file, will be made available in the SLICE interface");
        }
    };

    /**
     * YARP image provider sends a number of random images.
     * Use this for testing and performance measuring.
     *
     * It supports the following image transmission formats:
     *
     *  - Gray Scale
     *
     * \componentproperties
     * \prop VisionX.YARPImageProvider.NumberImages: Number of images to send
     *       (default: 2)
     */
     class YARPImageProvider :
        virtual public visionx::CapturingImageProvider
    {
    public:
        /**
         * @see visionx::ImageProviderBase::onInitImageProvider()
         */
        virtual void onInitCapturingImageProvider();

        /**
         * @see visionx::ImageProviderBase::onExitImageProvider()
         */
        virtual void onExitCapturingImageProvider();

        /**
         * @see visionx::ImageProviderBase::onStartCapture(float frameRate)
         */
        virtual void onStartCapture(float frameRate);

        /**
         * @see visionx::ImageProviderBase::onStopCapture()
         */
        virtual void onStopCapture();

        /**
         * @see visionx::ImageProviderBase::capture()
         */
        bool capture(void** ppImages);

        /**
         * @see PropertyUser::createPropertyDefinitions()
         */
        virtual armarx::PropertyDefinitionsPtr createPropertyDefinitions()
        {
            return armarx::PropertyDefinitionsPtr(
                        new YARPImageProviderPropertyDefinitions(
                                getConfigIdentifier()));
        }

        /**
         * @see armarx::Component::getDefaultName()
         */
        std::string getDefaultName() const
        {
            return "YARPImageProvider";
        }

        
        /**
         * Get the signal to interrupt the block--reading yarp port
         */
        void onExitComponent();

        /**
         * Returns the StereoCalibration as provided in configuration
         *
         * @return visionx::StereoCalibration
         */
        visionx::StereoCalibration getStereoCalibration(const Ice::Current& c = ::Ice::Current());

    private:
        yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> > m_leftImgPort;
        yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> > m_rightImgPort;

        std::string m_strCamera;
        std::string m_strRightPort;
        std::string m_strLeftPort;
        std::string m_strCarrier;
        bool m_bLeftCamUsed;
        bool m_bRightCamUsed;

        /**
         * IVT Stereo Calibration object
         */
        CStereoCalibration ivtStereoCalibration;

        /**
         * VisionX StereoCalibration object
         */
        StereoCalibration stereoCalibration;

    };
}

#endif /* ARMARX_COMPONENT_DUMMYIMAGEPROVIDER_H */

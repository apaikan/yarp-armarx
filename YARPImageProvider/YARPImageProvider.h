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
 * @author     Kai Welke (kai dot welke at kit dot edu)
 * @date       2011
 * @copyright  http://www.gnu.org/licenses/gpl-2.0.txt
 *             GNU General Public License
 */


#ifndef ARMARX_COMPONENT_DUMMYIMAGEPROVIDER_H
#define ARMARX_COMPONENT_DUMMYIMAGEPROVIDER_H

#include <Core/core/Component.h>
#include <Core/core/application/properties/Properties.h>

/* VisionX */
#include <VisionX/core/CapturingImageProvider.h>
#include <VisionX/tools/FPSCounter.h>

/* IVT */
#include <Image/ByteImage.h>

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
            //defineOptionalProperty<int>("NumberImages", 1, "Number of images").setMax(1);
            defineOptionalProperty<std::string>("Remote", std::string("/grabber"), "Romote Yarp port to receive the image");
            defineOptionalProperty<std::string>("Local", std::string("..."), "Local Yarp port");
            defineOptionalProperty<std::string>("Carrier", std::string("udp"), "Yarp Connection carrier");
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

    private:
        yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> > m_imgPort;
        std::string m_strRemotePort;
        std::string m_strLocalPort;
        std::string m_strCarrier;
    };
}

#endif /* ARMARX_COMPONENT_DUMMYIMAGEPROVIDER_H */

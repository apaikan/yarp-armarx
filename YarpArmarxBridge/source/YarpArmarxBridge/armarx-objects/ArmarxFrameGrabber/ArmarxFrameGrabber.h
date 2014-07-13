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
 * @package    YarpArmarxBridge::ArmarXObjects::ArmarxFrameGrabber
 * @author     Ali Paikan ( ali dot paikan at gmail dot com )
 * @date       2014
 * @copyright  http://www.gnu.org/licenses/gpl.txt
 *             GNU General Public License
 */

#ifndef _ARMARX_MANAGEDICEOBJECT_YarpArmarxBridge_ArmarxFrameGrabber_H
#define _ARMARX_MANAGEDICEOBJECT_YarpArmarxBridge_ArmarxFrameGrabber_H


#include <Core/core/ManagedIceObject.h>
#include <Core/core/Component.h>
#include <Core/core/application/properties/Properties.h>

/* VisionX */
#include <VisionX/core/ImageProcessor.h>

/* IVT */
#include <Image/ByteImage.h>

/* YARP */
#include <yarp/os/BufferedPort.h>
#include <yarp/sig/Image.h>


namespace armarx
{


    class ArmarxFrameGrabberPropertyDefinitions:
        public armarx::ComponentPropertyDefinitions
    {
    public:
        ArmarxFrameGrabberPropertyDefinitions(std::string prefix):
            ComponentPropertyDefinitions(prefix)
        {
            defineOptionalProperty<std::string>("ImageProvider.AdapterName", "ImageProvider", "Ice Adapter name of the image provider");
            defineOptionalProperty<std::string>("ImageType", "rgb", "Image color mode");
            defineOptionalProperty<std::string>("ImagePortName", std::string("/ArmarxFrameGrabber/img"), "Yarp port prefix name");
        }
    };

    /**
     * @class ArmarxFrameGrabber
     * @brief A brief description
     *
     * Detailed Description
     */
    class ArmarxFrameGrabber :
        virtual public visionx::ImageProcessor
    {
    public:
        /**
         * @see armarx::ManagedIceObject::getDefaultName()
         */
        virtual std::string getDefaultName() const
        {
            return "ArmarxFrameGrabber";
        }

    protected:
        // inherited from VisionComponent
        void onInitImageProcessor();
        void onConnectImageProcessor();
        void onExitImageProcessor();
        void process();

        /**
         * @see PropertyUser::createPropertyDefinitions()
         */
        virtual armarx::PropertyDefinitionsPtr createPropertyDefinitions()
        {
            return armarx::PropertyDefinitionsPtr(
                        new ArmarxFrameGrabberPropertyDefinitions(
                                getConfigIdentifier()));
        }
    private:
        visionx::ImageFormatInfo    m_ImageFormat;
        CByteImage**                m_ppImages;
        std::string                 m_ProviderName;        
        int                         m_numberImages;
        visionx::ImageProviderInterfacePrx   m_ImageProviderPrx;
        std::string m_imageTypeName;

        std::string m_portPrefix;
        yarp::os::BufferedPort<yarp::sig::ImageOf<yarp::sig::PixelRgb> > *m_imagePorts;
    };
}

#endif

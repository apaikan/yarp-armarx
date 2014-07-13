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

#include "ArmarxFrameGrabber.h"

// VisionXCore
#include <Core/core/exceptions/Exception.h>

// VisionXTools
#include <VisionX/tools/TypeMapping.h>
#include <VisionX/tools/ImageUtil.h>

#include <sstream>

using namespace armarx;
using namespace visionx;
using namespace yarp::sig;
using namespace yarp::os;

void ArmarxFrameGrabber::onInitImageProcessor()
{
    m_ProviderName = getProperty<std::string>("ImageProvider.AdapterName").getValue();
    m_imageTypeName = getProperty<std::string>("ImageType").getValue();
    m_portPrefix =  getProperty<std::string>("ImagePortName").getValue();
  
    usingImageProvider(m_ProviderName);
}

void ArmarxFrameGrabber::onConnectImageProcessor()
{
    visionx::ImageType imageDisplayType = visionx::tools::typeNameToImageType(m_imageTypeName);

    ARMARX_LOG << armarx::eINFO << getName() << " connecting to " << m_ProviderName << flush;

    visionx::ImageProviderInfo imageProviderInfo = getImageProvider(m_ProviderName, imageDisplayType);
    m_ImageProviderPrx = getProxy<ImageProviderInterfacePrx>(m_ProviderName);

    m_ImageFormat = imageProviderInfo.imageFormat;
    m_numberImages = imageProviderInfo.numberImages;

    m_ppImages = new CByteImage*[m_numberImages];
    m_imagePorts = new BufferedPort<ImageOf<PixelRgb> >[m_numberImages];

    for(int i = 0 ; i < m_numberImages ; i++)
    {
        m_ppImages[i] = visionx::tools::createByteImage(imageProviderInfo);
        std::ostringstream strName;
        strName << m_portPrefix << ":" << i+1;
        m_imagePorts[i].open(strName.str().c_str());
    }   
}

void ArmarxFrameGrabber::process()
{
    if(!waitForImages())
    {
        ARMARX_WARNING << "Timeout or error in wait for images" << armarx::flush;
    }
    else
    {
        // poll images
        int nNumberImages = getImages(m_ppImages);
        for(int i = 0 ; i < nNumberImages ; i++)
        {
              //m_ImageFormat.dimension.width, m_ImageFormat.dimension.height;
              ImageOf<PixelRgb>& out = m_imagePorts[i].prepare();
              ImageOf<PixelRgb> ext;
              CByteImage& img = *m_ppImages[i];
              ext.setExternal(img.pixels,
                      img.width,
                      img.height);
              out.copy(ext);  // this could be avoided with a little more work
              m_imagePorts[i].write(); 
        }
    }
}

void ArmarxFrameGrabber::onExitImageProcessor()
{
    for(int i = 0 ; i < m_numberImages ; i++)
    {
        m_imagePorts[i].close();
        delete m_ppImages[i];
    }

    delete [] m_imagePorts;
    delete [] m_ppImages;
}

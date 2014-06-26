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

#include "YARPImageProvider.h"

#include <VisionX/core/exceptions/user/StartingCaptureFailedException.h>
#include <VisionX/core/exceptions/user/FrameRateNotSupportedException.h>

#include "Helpers/helpers.h"

#include <yarp/os/Network.h>
#include<yarp/os/Time.h>

using namespace std;
using namespace yarp::sig;
using namespace yarp::os;

namespace visionx
{
    void YARPImageProvider::onInitCapturingImageProvider()
    {
        setNumberImages(1);
        m_strRemotePort = getProperty<std::string>("Remote").getValue();
        m_strLocalPort = getProperty<std::string>("Local").getValue();
        m_strCarrier = getProperty<std::string>("Carrier").getValue();       

        if (!m_imgPort.open(m_strLocalPort.c_str()))
            throw visionx::exceptions::user::StartingCaptureFailedException(
                            "Opening Yarp port \"" + m_strLocalPort + "\" failed.");

        if (!NetworkBase::connect(m_strRemotePort.c_str(),
                                  m_imgPort.getName().c_str(), 
                                  m_strCarrier.c_str())) {
            throw visionx::exceptions::user::StartingCaptureFailedException(
                    "Connecting to Yarp port \"" + m_strRemotePort + "\" failed");
        }        

        // we could set size/format explicitly.  here choose to wait.
        ImageOf<PixelRgb> *img = NULL;
        //printf("Waiting for input to determine size/format...\n");
        double start = Time::now();
        while (img==NULL && Time::now()-start<3.0) {
            img = m_imgPort.read(false);
            Time::delay(0.05);
        }

        if (img==NULL) {
            throw visionx::exceptions::user::StartingCaptureFailedException(
                            "Timeout on waiting for Yarp image");
        }

        setImageFormat(visionx::ImageDimension(img->width(), img->height()), visionx::eRgb);
    }

    void YARPImageProvider::onExitCapturingImageProvider()
    {
        m_imgPort.interrupt();
        m_imgPort.close();
    }

    void YARPImageProvider::onStartCapture(float fFrameRate)
    {
    }

    void YARPImageProvider::onStopCapture()
    {
    }

    bool YARPImageProvider::capture(void** ppImages)
    {
        ImageOf<PixelRgb> *img = m_imgPort.read();
        if (img==NULL) return false;
        // This memcpy could be avoided with a bit of care
        // assumes no padding issues etc
        memcpy(ppImages[0], img->getRawImage(), 
               getImageFormat().dimension.width * getImageFormat().dimension.height * getImageFormat().bytesPerPixel);
        return true;
    }
}

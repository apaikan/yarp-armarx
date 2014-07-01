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

#include "YarpImageProvider.h"
#include <Core/core/system/ArmarXDataPath.h>

// VisionXCore
#include <VisionX/core/exceptions/user/StartingCaptureFailedException.h>
#include <VisionX/core/exceptions/user/FrameRateNotSupportedException.h>

// VisionXTools
#include <VisionX/tools/TypeMapping.h>
#include <VisionX/tools/ImageUtil.h>
#include <VisionX/tools/exceptions/local/InvalidFrameRateException.h>

#include <Calibration/Calibration.h>

#include "Helpers/helpers.h"

#include <yarp/os/Network.h>
#include <yarp/os/Time.h>

using namespace std;
using namespace yarp::sig;
using namespace yarp::os;

using namespace visionx;

namespace armarx
{
    void YarpImageProvider::onInitCapturingImageProvider()
    {
        m_strRightPort = getProperty<std::string>("RemoteLeft").getValue();
        m_strLeftPort = getProperty<std::string>("RemoteRight").getValue();
        m_strCarrier = getProperty<std::string>("Carrier").getValue();



        m_bLeftCamUsed = (getProperty<SelectedCameras>("Camera").getValue() == eLeftCam || getProperty<SelectedCameras>("Camera").getValue() == eBothCams);
        m_bRightCamUsed = (getProperty<SelectedCameras>("Camera").getValue() == eRightCam || getProperty<SelectedCameras>("Camera").getValue() == eBothCams);

        if (!m_bLeftCamUsed && !m_bRightCamUsed)
        {
            throw visionx::exceptions::user::
            StartingCaptureFailedException("No camera is selected! Please set the 'Camera' property to either 'left', 'right' or 'both'.");
            return;
        }

        if (m_bLeftCamUsed && m_bRightCamUsed)
        {
            setNumberImages(2);
        }
        else
        {
            setNumberImages(1);
        }

        if (m_bLeftCamUsed)
        {
            if (!m_leftImgPort.open("..."))
                throw visionx::exceptions::user::StartingCaptureFailedException(
                    "Opening Yarp port \"" + std::string(m_leftImgPort.getName()) + "\" failed.");

            if (!NetworkBase::connect(m_strLeftPort.c_str(),
                                      m_leftImgPort.getName().c_str(),
                                      m_strCarrier.c_str()))
            {
                throw visionx::exceptions::user::StartingCaptureFailedException(
                    "Connecting to Yarp port \"" + m_strLeftPort + "\" failed");
            }
        }

        if (m_bRightCamUsed)
        {
            if (!m_rightImgPort.open("..."))
                throw visionx::exceptions::user::StartingCaptureFailedException(
                    "Opening Yarp port \"" + std::string(m_rightImgPort.getName()) + "\" failed.");

            if (!NetworkBase::connect(m_strRightPort.c_str(),
                                      m_rightImgPort.getName().c_str(),
                                      m_strCarrier.c_str()))
            {
                throw visionx::exceptions::user::StartingCaptureFailedException(
                    "Connecting to Yarp port \"" + m_strRightPort + "\" failed");
            }
        }

        // keep one of the ports to get the image info
        // we could set size/format explicitly.  here choose to get it from the input image.
        BufferedPort<ImageOf<PixelRgb> > &aPort = (m_bLeftCamUsed) ? m_leftImgPort : m_rightImgPort;
        ImageOf<PixelRgb> *img = NULL;
        double start = Time::now();

        while (img == NULL && Time::now() - start < 3.0)
        {
            img = aPort.read(false);
            Time::delay(0.05);
        }

        if (img == NULL)
        {
            throw visionx::exceptions::user::StartingCaptureFailedException(
                "Timeout on waiting for Yarp image");
        }

        // set the image format
        setImageFormat(visionx::ImageDimension(img->width(), img->height()), visionx::eRgb);

        // stereo calibration
        std::string calibrationFileName = getProperty<std::string>("CalibrationFile").getValue();
        std::string fullCalibrationFileName;

        if (!ArmarXDataPath::getAbsolutePath(calibrationFileName, fullCalibrationFileName))
        {
            ARMARX_ERROR << "Could not find camera calibration file in ArmarXDataPath: " << calibrationFileName;
        }

        if (!ivtStereoCalibration.LoadCameraParameters(
                fullCalibrationFileName.c_str(), true))
        {
            ARMARX_ERROR << "Error loading camera calibration file: " << fullCalibrationFileName;
        }

        stereoCalibration = visionx::tools::convert(ivtStereoCalibration);

    }


    bool YarpImageProvider::getImagesAreUndistorted(const Ice::Current& c)
    {
        return true;
    }


    void YarpImageProvider::onExitCapturingImageProvider()
    {
        m_leftImgPort.close();
        m_rightImgPort.close();

    }

    void YarpImageProvider::onStartCapture(float fFrameRate)
    {
    }

    void YarpImageProvider::onStopCapture()
    {
    }

    void YarpImageProvider::onExitComponent()
    {
        m_leftImgPort.interrupt();
        m_rightImgPort.interrupt();
        ImageProvider::onExitComponent();
    }

    bool YarpImageProvider::capture(void** ppImages)
    {
        if (m_bLeftCamUsed)
        {

            ImageOf<PixelRgb> *img = m_leftImgPort.read();

            if (img == NULL)
            {
                return false;
            }

            // This memcpy could be avoided with a bit of care
            // assumes no padding issues etc
            memcpy(ppImages[1], img->getRawImage(),
                   getImageFormat().dimension.width * getImageFormat().dimension.height * getImageFormat().bytesPerPixel);
        }

        if (m_bRightCamUsed)
        {

            ImageOf<PixelRgb> *img = m_rightImgPort.read();

            if (img == NULL)
            {
                return false;
            }

            // This memcpy could be avoided with a bit of care
            // assumes no padding issues etc
//            int rigth_index = getNumberImages() - 1;
            memcpy(ppImages[0], img->getRawImage(),
                   getImageFormat().dimension.width * getImageFormat().dimension.height * getImageFormat().bytesPerPixel);
        }

        return true;
    }

    StereoCalibration YarpImageProvider::getStereoCalibration(const Ice::Current& c)
    {
        return stereoCalibration;
    }
}


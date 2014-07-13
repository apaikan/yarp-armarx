// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
/* 
 * Copyright (C) 2012 Department of Robotics Brain and Cognitive Sciences - Istituto Italiano di Tecnologia
 * Author: Ali Paikan
 * email:  ali.paikan@iit.it
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
*/

#include "Detector.h"
#include <opencv/cvaux.h>
#include <opencv/highgui.h>
#include <opencv/cxcore.h>

using namespace yarp::sig;
using namespace yarp::os;
using namespace std;
using namespace cv;

typedef struct __circle_t {
    float x;
    float y;
    float r;
}circle_t;



void Detector::loop()
{    
    ImageOf<PixelRgb> *image = imagePort.read();  // read an image
    if (image != NULL) 
    { 
        IplImage *cvImage = (IplImage*)image->getIplImage();        
        ImageOf<PixelRgb> &outImage = outPort.prepare(); //get an output image
        outImage = *image;
        display = (IplImage*) outImage.getIplImage();
        //Mat imgMat = display;       
        CvSize size = cvSize(cvImage->width, cvImage->height);

        IplImage* src_gray = cvCreateImage(size, IPL_DEPTH_8U, 1);
        IplImage* detected_edges = cvCreateImage(size, IPL_DEPTH_8U, 1);

        // convert to gray
        cvCvtColor(cvImage, src_gray, CV_BGR2GRAY);

        /// Reduce noise with a kernel 3x3
        //cvBlur(src_gray, detected_edges, Size(3,3) );

        /// Canny detector
        cvCanny( src_gray, detected_edges, 30, 100, 3);
        cvCvtColor(detected_edges, display, CV_GRAY2RGB);
        outPort.write();  

        // release
        cvReleaseImage(&detected_edges);
        cvReleaseImage(&src_gray);
    }
}



bool Detector::open(yarp::os::ResourceFinder &rf)
{
    bool ret = imagePort.open("/cannyFilter/image:i");  // give the port a name
    ret = ret && outPort.open("/cannyFilter/image:o");
    return ret;
}

bool Detector::close()
{
    imagePort.close();
    outPort.close();
    return true;
}

bool Detector::interrupt()
{
    imagePort.interrupt();
    return true;
}



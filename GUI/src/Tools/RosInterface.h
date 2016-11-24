/*
 * This file is part of ElasticFusion.
 *
 * Copyright (C) 2015 Imperial College London
 * 
 * The use of the code within this file and all code within files that 
 * make up the software that is ElasticFusion is permitted for 
 * non-commercial purposes only.  The full terms and conditions that 
 * apply to the code within this file are detailed within the LICENSE.txt 
 * file and at <http://www.imperial.ac.uk/dyson-robotics-lab/downloads/elastic-fusion/elastic-fusion-license/> 
 * unless explicitly stated.  By downloading this file you agree to 
 * comply with these terms.
 *
 * If you wish to use any of this code for commercial purposes then 
 * please email researchcontracts.engineering@imperial.ac.uk.
 *
 */

#ifndef INTERFACEROS_H_
#define INTERFACEROS_H_

#include <string>
#include <iostream>
#include <algorithm>
#include <map>

#include "ThreadMutexObject.h"
#include <sensor_msgs/Image.h>

class RosInterface
{
public:
    RosInterface(int inWidth = 640, int inHeight = 480, int fps = 30);
    virtual ~RosInterface();

    const int width, height, fps;

    bool ok() {
        return initSuccessful;
    }

    static const int numBuffers = 100;
    ThreadMutexObject<int> latestAllFrameIndex;
    std::pair<uint8_t *, int64_t> depthBuffers[numBuffers];
    std::pair<uint8_t *, int64_t> rgbBuffers[numBuffers];
    void depthRgbMsgCallback(const sensor_msgs::ImageConstPtr& rgbImage, const sensor_msgs::ImageConstPtr& depthImage);

private:
    std::thread rosThread;
    int64_t lastAllFrameTime;
    bool initSuccessful;
};
#endif
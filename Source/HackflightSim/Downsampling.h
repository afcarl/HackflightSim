#pragma once

/*
* Downsampling.h: Header for OpenCV downsampling implementation
*
* Copyright (C) 2017 Simon D. Levy
*
* MIT License
*/

#include "VisionAlgorithm.h"

class Downsampling : public VisionAlgorithm {

public:

    Downsampling(class AVisionHUD*hud, int leftx, int topy);

    ~Downsampling();

	virtual void perform(cv::Mat & bgrimg) override;

private:

	const int DOWNSAMPLE_RATIO = 16;

    const int IMAGE_MARGIN = 20;
};

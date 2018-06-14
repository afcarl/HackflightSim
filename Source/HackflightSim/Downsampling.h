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

    Downsampling(AHUD*hud, int leftx, int topy, int rows, int cols);

    ~Downsampling();

	virtual void perform(cv::Mat & bgrimg) override;

private:

	const int DOWNSAMPLE_RATIO = 2;
    const int IMAGE_MARGIN = 20;

	int _leftx;
	int _topy;
	int _rows;
	int _cols;
	bool _ready;

	AHUD* _hud;
};

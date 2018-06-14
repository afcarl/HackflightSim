#pragma once

/*
* Downsampling.cpp: OpenCV downsampling implementation for HackflightSim vision
*
* Copyright (C) 2017 Simon D. Levy
*
* MIT License
*/

#include "Downsampling.h"
#include <opencv2/video/tracking.hpp>

Downsampling::Downsampling(AHUD * hud, int leftx, int topy) : VisionAlgorithm(hud, leftx, topy)
{
}

Downsampling::~Downsampling()
{
}

void Downsampling::perform(cv::Mat & bgrimg)
{
    // Convert color image to grayscale
    cv::Mat gray;
    cv::cvtColor(bgrimg, gray, cv::COLOR_BGR2GRAY);

    // Downsmaple (resize)
    int smallrows = gray.rows / DOWNSAMPLE_RATIO;
    int smallcols = gray.cols / DOWNSAMPLE_RATIO;
	cv::Mat smallgray(smallrows, smallcols, CV_8UC1);
    cv::resize(gray, smallgray, cv::Size(smallcols,smallrows), 0, 0, CV_INTER_LINEAR);

    // Draw pixels to HUD
    for (int r=0; r<smallrows; ++r) {
        for (int c=0; c<smallcols; ++c) {
            int x = _leftx + gray.cols + IMAGE_MARGIN + c * DOWNSAMPLE_RATIO;
            int y = _topy  + r * DOWNSAMPLE_RATIO;
            uint8_t grayval = smallgray.at<uint8_t>(r,c);
	        FColor color(grayval,grayval,grayval,255); // alpha=255 (opaque)
            _hud->DrawRect(color, x, y, DOWNSAMPLE_RATIO, DOWNSAMPLE_RATIO);
        }
    }
}

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

Downsampling::Downsampling(AHUD* hud, int leftx, int topy, int rows, int cols) : 
	_leftx(leftx), _topy(topy), _hud(hud),  _rows(rows), _cols(cols)
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
    int smallrows = _rows / DOWNSAMPLE_RATIO;
    int smallcols = _cols / DOWNSAMPLE_RATIO;
	cv::Mat smallgray(smallrows, smallcols, CV_8UC1);
    cv::resize(gray, smallgray, cv::Size(smallcols,smallrows), 0, 0, CV_INTER_LINEAR);

    // Draw pixels to HUD
    for (int r=0; r<smallrows; ++r) {
        for (int c=0; c<smallcols; ++c) {
            int x = _leftx + _cols + IMAGE_MARGIN + c;// * DOWNSAMPLE_RATIO;
            int y = _topy  + r;// * DOWNSAMPLE_RATIO;
            uint8_t grayval = smallgray.at<uint8_t>(r,c);
	        FColor color(grayval,grayval,grayval,255); // alpha=255 (opaque)
            _hud->DrawRect(color, x, y, 1, 1);//DOWNSAMPLE_RATIO, DOWNSAMPLE_RATIO);
        }
    }

    /*
    for (int r=0; r<_rows; ++r) {
        for (int c=0; c<_cols; ++c) {
            int x = _leftx + _cols + c + IMAGE_MARGIN;
            int y = _topy  + r;
            uint8_t grayval = gray.at<uint8_t>(r, c);
	        FColor color(grayval,grayval,grayval,255); 
            _hud->DrawRect(color, x, y, 1, 1);
        }
    }*/
}

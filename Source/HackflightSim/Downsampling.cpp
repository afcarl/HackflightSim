#pragma once

/*
* Downsampling.cpp: OpenCV downsampling implementation for HackflightSim vision
*
* Copyright (C) 2017 Simon D. Levy
*
* MIT License
*/

#include "Downsampling.h"

#include <opencv2/core.hpp>
#include <opencv2/video/tracking.hpp>

Downsampling::Downsampling(AHUD* hud, int leftx, int topy, int rows, int cols) : 
	_leftx(leftx), _topy(topy), _hud(hud),  _rows(rows), _cols(cols)
{
    _imagegray = new uint8_t[_rows*cols];
}

Downsampling::~Downsampling()
{
    delete _imagegray;
}

void Downsampling::perform(uint8_t* imagergb)
{
    // RGB->gray formula from https ://www.johndcook.com/blog/2009/08/24/algorithms-convert-color-grayscale/
	for (int k = 0; k < _rows*_cols; ++k) {
		_imagegray[k] = (uint8_t)(0.21 * imagergb[3 * k] + 0.72 * imagergb[3 * k + 1] + 0.07 * imagergb[3 * k + 2]);
	}

    // Downsmaple (resize)
    /*
    int smallrows = _rows / DOWNSAMPLE_RATIO;
    int smallcols = _cols / DOWNSAMPLE_RATIO;
	cv::Mat smallgray(smallrows, smallcols, CV_8UC1);
    cv::resize(gray, smallgray, cv::Size(smallcols,smallrows), 0, 0, CV_INTER_LINEAR);

    // Draw pixels to HUD
    for (int r=0; r<smallrows; ++r) {
        for (int c=0; c<smallcols; ++c) {
            int x = _leftx + c * DOWNSAMPLE_RATIO;
            int y = _topy  + r * DOWNSAMPLE_RATIO;
            uchar grayval = (uchar)smallgray.at<uchar>(c,r);
	        FLinearColor color(grayval,grayval,grayval,255); // alpha=255 (opaque)
            _hud->DrawRect(color, x, y, DOWNSAMPLE_RATIO, DOWNSAMPLE_RATIO);
        }
    }*/
    for (int r=0; r<_rows; ++r) {
        for (int c=0; c<_cols; ++c) {
            int x = _leftx + _cols + c + IMAGE_MARGIN;
            int y = _topy  + r;
            uint8_t grayval = _imagegray[r*_cols+c];
	        FColor color(grayval,grayval,grayval,255); 
            _hud->DrawRect(color, x, y, 1, 1);
        }
    }
}

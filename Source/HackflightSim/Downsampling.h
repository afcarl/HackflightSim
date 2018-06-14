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

	virtual void perform(uint8_t* imagergb) override;

private:

	// Arbitrary edge-detection params
	const int LOW_THRESHOLD = 50;
	const int RATIO         = 3;
	const int KERNEL_SIZE   = 3;

	FColor EDGE_COLOR = FColor::Green;

	int _leftx;
	int _topy;
	int _rows;
	int _cols;
	bool _ready;

	AHUD* _hud;
};

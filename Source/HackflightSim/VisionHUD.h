/*
* VisionHud.h: Class declaration for Vision HUD in HackflightSim
*
* Copyright (C) 2018 Simon D. Levy
*
* MIT License
*/

#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include "GameFramework/HUD.h"
#include "GameFramework/HUD.h"
#include "Engine/TextureRenderTarget2D.h"

#include "VisionAlgorithm.h"

#include <opencv2/core.hpp>

#include "VisionHUD.generated.h"

/**
 * 
 */
UCLASS()
class HACKFLIGHTSIM_API AVisionHUD : public AHUD
{
	GENERATED_BODY()

    public:
	
	AVisionHUD();
	~AVisionHUD();

    void drawBorder(int leftx=LEFTX, int topy=TOPY);

	virtual void DrawHUD() override;

    private:

	static const int LEFTX  = 20;
	static const int TOPY   = 40;
	const float WIDTH  = 256;
	const float HEIGHT = 128;
	
	const FLinearColor BORDER_COLOR = FLinearColor::Yellow;
	const float BORDER_WIDTH = 2.0f;

	void drawBorderLine(float lx, float uy, float rx, float by);

	// Access to Vision camera
	UTextureRenderTarget2D* VisionTextureRenderTarget;
	FRenderTarget* VisionRenderTarget;
	TArray<FColor> VisionSurfData;

	// Support for vision algorithms
	int _rows;
	int _cols;
   
	// BGR color bytes array
	uint8_t* _bgrbytes;
    
	// implementation of your vision algorithm
	class VisionAlgorithm * _algorithm;
};

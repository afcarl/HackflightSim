/*
* VisionHud.h: Class implementation for Vision HUD in HackflightSim
*
* Copyright (C) 2018 Simon D. Levy
*
* MIT License
*/


#include "VisionHUD.h"

AVisionHUD::AVisionHUD()
{
	// Get Vision render target from blueprint
	static ConstructorHelpers::FObjectFinder<UTextureRenderTarget2D> VisionTexObj(TEXT("/Game/Flying/RenderTargets/VisionHUDTarget"));
	VisionTextureRenderTarget = VisionTexObj.Object;

	// Creates Texture2D to store VisionTex content
	UTexture2D* VisionTexture = UTexture2D::CreateTransient(VisionTextureRenderTarget->SizeX, VisionTextureRenderTarget->SizeY, PF_B8G8R8A8);

#if WITH_EDITORONLY_DATA
	VisionTexture->MipGenSettings = TMGS_NoMipmaps;
#endif
	VisionTexture->SRGB = VisionTextureRenderTarget->SRGB;

	VisionRenderTarget = VisionTextureRenderTarget->GameThread_GetRenderTargetResource();

	// Allocate memory for RGB image bytes
	_rows = VisionTextureRenderTarget->SizeY;
	_cols = VisionTextureRenderTarget->SizeX;
	_imagergb = new uint8_t[_rows*_cols * 3];
}


void AVisionHUD::DrawHUD()
{
	Super::DrawHUD();

	// Draw the image to the HUD
	DrawTextureSimple(VisionTextureRenderTarget, LEFTX, TOPY, 1.0f, true);

	// Read the pixels from the RenderTarget and store them in a FColor array
	VisionRenderTarget->ReadPixels(VisionSurfData);

	// Convert the FColor array to an RGB byte array

	for (int x = 0; x < _cols; ++x) {

		for (int y = 0; y < _rows; ++y) {

			int k = x + y * _cols;

			FColor PixelColor = VisionSurfData[k];

			_imagergb[k * 3] = PixelColor.R;
			_imagergb[k * 3 + 1] = PixelColor.G;
			_imagergb[k * 3 + 2] = PixelColor.B;
		}
	}

	// Draw a border around the image

	float rightx = LEFTX + WIDTH;
	float bottomy = TOPY + HEIGHT;

	drawBorder(LEFTX, TOPY, rightx, TOPY);
	drawBorder(rightx, TOPY, rightx, bottomy);
	drawBorder(rightx, bottomy, LEFTX, bottomy);
	drawBorder(LEFTX, bottomy, LEFTX, TOPY);
}

void AVisionHUD::drawBorder(float lx, float uy, float rx, float by)
{
	DrawLine(lx, uy, rx, by, BORDER_COLOR, BORDER_WIDTH);
}











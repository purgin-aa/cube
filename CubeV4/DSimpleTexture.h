#pragma once

#include "Precompiled.h"
#include "DRenderBasicTypes.h"

// WARNING! This code is not optimized. Only for test;
void DGenerateTexture( DPixelColor *pixels, u32 width, u32 height ) {
	assert( pixels );

	const DPixelColor startColor = { 0, 255, 0, 255 };
	const DPixelColor endColor = { 255, 0, 200, 255 };

	f32 redStep = ( endColor.rgba.r - startColor.rgba.r ) / ( f32 )height;
	f32 greenStep = ( endColor.rgba.g - startColor.rgba.g ) / ( f32 )height;
	f32 blueStep = ( endColor.rgba.b - startColor.rgba.b ) / ( f32 )height;

	DPixelColor* currentPixel = pixels;
	DPixelColor currentColor = startColor;

	f32 currentRed = ( f32 )startColor.rgba.r;
	f32 currentGreen = ( f32 )startColor.rgba.g;
	f32 currentBlue = ( f32 )startColor.rgba.b;

	for( u16 j = height; j; --j ) {
		const DPixelColor currentColor = {
			( u8 )currentRed,
			( u8 )currentGreen,
			( u8 )currentBlue,
			255
		};

		for( u32 i = width; i; --i )
			*currentPixel++ = currentColor;
		
		currentRed += redStep;
		currentGreen += greenStep;
		currentBlue += blueStep;
	}
}

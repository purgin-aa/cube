#pragma once

#include "Precompiled.h"
#include "DRenderBasicTypes.h"

// WARNING! This code is not optimized. Only for test;
void DGenerateTexture( DPixelColor *pixels, u16 width, u16 height ) {
	assert( pixels );

	const DPixelColor startColor = { 0u, 255u, 0u, 255u };
	const DPixelColor endColor = { 255u, 0u, 200u, 255u };

	f32 redStep = ( endColor.rgba.r - startColor.rgba.r ) / static_cast<f32>( height );
	f32 greenStep = ( endColor.rgba.g - startColor.rgba.g ) / static_cast<f32>( height );
	f32 blueStep = ( endColor.rgba.b - startColor.rgba.b ) / static_cast<f32>( height );

	DPixelColor *currentPixel = pixels;
	DPixelColor currentColor = startColor;

	f32 currentRed = static_cast<f32>( startColor.rgba.r );
	f32 currentGreen = static_cast<f32>( startColor.rgba.g );
	f32 currentBlue = static_cast<f32>( startColor.rgba.b );

	for( u16 j = height; j; --j )
	{
		const DPixelColor currentColor = {
			static_cast< u8 >( currentRed ),
			static_cast< u8 >( currentGreen ),
			static_cast< u8 >( currentBlue ),
			255u
		};

		for( u16 i = width; i; --i )
			*currentPixel++ = currentColor;
		
		currentRed += redStep;
		currentGreen += greenStep;
		currentBlue += blueStep;
	}
}

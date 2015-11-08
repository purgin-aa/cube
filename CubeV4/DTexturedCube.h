#pragma once

#include "Precompiled.h"
#include "DTexturedMaterial.h"

// Vertices
const DTexturedMaterialController::Vertex DCUBE_VERTICES_TEXTURED[] = {
	{ { -1.0f,  1.0f, -1.0f }, { 0.0f, 0.0f } },
	{ {  1.0f,  1.0f, -1.0f }, { 1.0f, 0.0f } },
	{ {  1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f } },
	{ { -1.0f,  1.0f,  1.0f }, { 0.0f, 1.0f } },

	{ { -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f } },
	{ {  1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f } },
	{ {  1.0f, -1.0f,  1.0f }, { 1.0f, 1.0f } },
	{ { -1.0f, -1.0f,  1.0f }, { 0.0f, 1.0f } },

	{ { -1.0f, -1.0f,  1.0f }, { 0.0f, 0.0f } },
	{ { -1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f } },
	{ { -1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f } },
	{ { -1.0f,  1.0f,  1.0f }, { 0.0f, 1.0f } },

	{ {  1.0f, -1.0f,  1.0f }, { 0.0f, 0.0f } },
	{ {  1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f } },
	{ {  1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f } },
	{ {  1.0f,  1.0f,  1.0f }, { 0.0f, 1.0f } },

	{ { -1.0f, -1.0f, -1.0f }, { 0.0f, 0.0f } },
	{ {  1.0f, -1.0f, -1.0f }, { 1.0f, 0.0f } },
	{ {  1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f } },
	{ { -1.0f,  1.0f, -1.0f }, { 0.0f, 1.0f } },

	{ { -1.0f, -1.0f, 1.0f }, { 0.0f, 0.0f } },
	{ {  1.0f, -1.0f, 1.0f }, { 1.0f, 0.0f } },
	{ {  1.0f,  1.0f, 1.0f }, { 1.0f, 1.0f } },
	{ { -1.0f,  1.0f, 1.0f }, { 0.0f, 1.0f } }
};

// Indices
const u16 DCUBE_INDICES_TEXTURED[] = {
	3,1,0,
	2,1,3,

	6,4,5,
	7,4,6,

	11,9,8,
	10,9,11,

	14,12,13,
	15,12,14,

	19,17,16,
	18,17,19,

	22,20,21,
	23,20,22
};

DSimpleMeshPtr DCreateTexturedCube( DRenderResourceManagerPtr manager, const DPixelColor *pixels, u16 width, u16 height, HRESULT *returnCode );
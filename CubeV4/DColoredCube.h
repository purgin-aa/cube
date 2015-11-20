#pragma once

#include "Precompiled.h"
#include "DColoredMaterial.h"

// Vertices
const DColoredMaterialController::Vertex DCUBE_VERTICES_COLORED[] = {
	{ { -0.5f,  0.5f, -0.5f } },
	{ {  0.5f,  0.5f, -0.5f } },
	{ {  0.5f,  0.5f,  0.5f } },
	{ { -0.5f,  0.5f,  0.5f } },
	{ { -0.5f, -0.5f, -0.5f } },
	{ {  0.5f, -0.5f, -0.5f } },
	{ {  0.5f, -0.5f,  0.5f } },
	{ { -0.5f, -0.5f,  0.5f } }
};

// Indices
const u16 DCUBE_INDICES_COLORED[] = {
	3,1,0,
	2,1,3,

	0,5,4,
	1,5,0,

	3,4,7,
	0,4,3,

	1,6,5,
	2,6,1,

	2,7,6,
	3,7,2,

	6,4,5,
	7,4,6
};


DSimpleMeshPtr DCreateColoredCube( DRenderResourceManagerPtr manager, const XMFLOAT4& color, HRESULT* returnCode );

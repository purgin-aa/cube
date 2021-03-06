#include "Precompiled.h"
#include "DTexturedCube.h"

DSimpleMeshPtr DCreateTexturedCube( DRenderResourceManagerPtr manager, const DPixelColor * pixels, u32 width, u32 height, HRESULT * returnCode ) {
	assert( manager );
	assert( pixels );
	assert( width > 0 );
	assert( height > 0 );

	auto materialControllerPtr = DTexturedMaterialController::Create( manager.Get(), returnCode );
	if( !materialControllerPtr )
		return nullptr;

	auto materialPtr = materialControllerPtr->CreateTexturedMaterial(
			manager.Get(),
			pixels,
			width,
			height,
			returnCode );
	if( !materialPtr )
		return nullptr;

	auto vertexBufferPtr = manager->CreateBuffer(
			sizeof( DCUBE_VERTICES_TEXTURED ),
			DCUBE_VERTICES_TEXTURED,
			D3D11_BIND_VERTEX_BUFFER,
			returnCode );
	if( !vertexBufferPtr )
		return nullptr;

	auto indexBufferPtr = manager->CreateBuffer(
			sizeof( DCUBE_INDICES_TEXTURED ),
			DCUBE_INDICES_TEXTURED,
			D3D11_BIND_INDEX_BUFFER,
			returnCode );
	if( !indexBufferPtr )
		return nullptr;

	auto vertexBufferViewPtr = manager->CreateVertexBufferView(
			vertexBufferPtr,
			sizeof( DTexturedMaterialController::Vertex ),
			0 );
	if( !vertexBufferViewPtr )
		return nullptr;

	auto indexBufferViewptr = manager->CreateIndexBufferView(
			indexBufferPtr,
			DXGI_FORMAT_R16_UINT,
			0 );
	if( !vertexBufferViewPtr )
		return nullptr;

	auto mesh = manager->CreateSimpleMesh(
			vertexBufferViewPtr.Get(),
			indexBufferViewptr.Get(),
			materialPtr.Get(),
			static_cast< u32 >( DTools::StaticArraySize( DCUBE_INDICES_TEXTURED ) ),
			0,
			0 );

	return mesh;
}

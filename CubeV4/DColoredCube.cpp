#include "Precompiled.h"
#include "DColoredCube.h"

DSimpleMeshPtr DCreateColoredCube( DRenderResourceManagerPtr manager, const XMFLOAT4 & color, HRESULT *returnCode ) {
	assert( manager );

	auto materialControllerPtr = DColoredMaterialController::CreateColoredMaterialController( manager.Get(), returnCode );
	if( !materialControllerPtr )
		return nullptr;

	auto materialPtr = materialControllerPtr->CreateColoredMaterial( manager.Get(), color, returnCode );
	if( !materialPtr )
		return nullptr;

	auto vertexBufferPtr =
		manager->CreateBuffer(
			sizeof( DCUBE_VERTICES_COLORED ),
			DCUBE_VERTICES_COLORED,
			D3D11_BIND_VERTEX_BUFFER,
			returnCode );

	if( !vertexBufferPtr )
		return nullptr;

	auto indexBufferPtr =
		manager->CreateBuffer(
			sizeof( DCUBE_INDICES_COLORED ),
			DCUBE_INDICES_COLORED,
			D3D11_BIND_INDEX_BUFFER,
			returnCode );

	if( !indexBufferPtr )
		return nullptr;

	auto vertexBufferViewPtr =
		manager->CreateVertexBufferView(
			vertexBufferPtr,
			sizeof( DColoredMaterialController::Vertex ),
			0u );

	if( !vertexBufferViewPtr )
		return nullptr;

	auto indexBufferViewPtr =
		manager->CreateIndexBufferView(
			indexBufferPtr,
			DXGI_FORMAT_R16_UINT,
			0u );

	if( !indexBufferViewPtr )
		return nullptr;

	auto mesh =
		manager->CreateSimpleMesh(
			vertexBufferViewPtr.Get(),
			indexBufferViewPtr.Get(),
			materialPtr.Get(),
			static_cast< u32 >( DTools::StaticArraySize( DCUBE_INDICES_COLORED ) ),
			0u,
			0u );

	return mesh;
}

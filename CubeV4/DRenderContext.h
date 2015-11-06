#pragma once

#include "DRenderBasicTypes.h"
#include "DRenderResourceManager.h"
#include "DMaterialController.h"

#include "DTools.h"

using namespace DirectX;


//
struct DRenderWVMatrices {
	XMMATRIX world;
	XMMATRIX view;
};


//
struct DRenderPerspectiveModeDesc {
	f32 fov;
	f32 nearZ;
	f32 farZ;
};


//
struct DRenderTargetSize {
	u16 width;
	u16 height;
};


//
class DRenderContext : public DSharedObject {
public:
	// projection mode
	//void SetPerspectiveMode( const DRenderPerspectiveModeDesc &perspectiveModeDesc );
	void SetWVMatrices( const DRenderWVMatrices &stateMatrices );

	// shaders
	void SetVertexShader( DID3D11VertexShaderPtr vertexShader );
	void SetPixelShader( DID3D11PixelShaderPtr pixelShader );

	//
	void SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY topology );

	void DrawIndexed( u32 indexCount, u32 startIndexLocation, u32 startVertexLocation );
	void FillCurrentTargetView( f32 color[4] );

	void SetRenderTargetView( DID3D11RenderTargetViewPtr renderTarget, const DRenderTargetSize &size );

	DID3D11DeviceContextPtr GetDeviceContext() const;

protected:
	//
	DRenderResourceManagerPtr m_manager;

	DID3D11DeviceContextPtr m_deviceContext;
	DID3D11RenderTargetViewPtr m_renderTarget;

	DRenderTargetSize m_renderTargetSize;

	explicit DRenderContext( DRenderResourceManagerPtr manager );
};

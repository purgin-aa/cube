#pragma once

#include "DRenderBasicTypes.h"
#include "DRenderResourceManager.h"
#include "DMaterialController.h"
#include "DTools.h"

//
struct DRenderTargetSize {
	u32 width;
	u32 height;
};


//
class DRenderContext : public DSharedObject {
public:
	// shaders
	void						SetVertexShader( ID3D11VertexShader* vertexShader );
	void						SetPixelShader( ID3D11PixelShader* pixelShader );
	void						SetInputLayout( ID3D11InputLayout* inputLayout );

	// constant buffers
	void						SetPixelShaderConstantBuffer( u32 slot, ID3D11Buffer* buffer );
	void						SetVertexShaderConstantBuffer( u32 slot, ID3D11Buffer* buffer );

	// resource view
	void						SetPixelShaderResourceView( u32 slot, ID3D11ShaderResourceView* resourceView );

	// vertices, indices
	void						SetVertexBuffer( u32 slot, ID3D11Buffer* vertexBuffer, u32 stride, u32 offset );
	void						SetIndexBuffer( ID3D11Buffer* indexBuffer, DXGI_FORMAT format, u32 offset );

	//
	void						SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY topology );

	// draw
	void						DrawIndexed( u32 indexCount, u32 startIndexLocation, u32 startVertexLocation );
	void						FillCurrentTargetView( const f32 color[4] );

	void						SetRenderTargetView( DID3D11RenderTargetViewPtr renderTarget, const DRenderTargetSize &size );
	const DRenderTargetSize&	GetRenderTargetSize() const;

	void						SetSamplers( u32 slot, ID3D11SamplerState* sampler );

	DID3D11DeviceContextPtr		GetDeviceContext() const;
	DRenderResourceManagerPtr	GetResourceManager() const;

protected:
	//
	DRenderResourceManagerPtr	m_manager;
	DID3D11DeviceContextPtr		m_deviceContext;
	DID3D11RenderTargetViewPtr	m_renderTarget;
	DRenderTargetSize			m_renderTargetSize;

	DRenderContext( DRenderResourceManagerPtr manager );
};

//
using DRenderContextPtr = DIntrusivePtr<DRenderContext>;

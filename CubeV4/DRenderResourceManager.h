#pragma once

#include "DIntrusivePtr.h"
#include "DSharedObject.h"
#include "DTools.h"
#include "DRenderBasicTypes.h"

class DRenderResourceManager;
using DRenderResourceManagerPtr = DIntrusivePtr< DRenderResourceManager >;


//
class DRenderResourceManager : public DSharedObject {
public:
	// create func
	static DRenderResourceManagerPtr Create( HRESULT* returnCode );

	//
	~DRenderResourceManager();

	//
	DID3D11RenderTargetViewPtr		CreateRenderTargetView( DID3D11Texture2DPtr texture, HRESULT* returnCode );
	DID3D11VertexShaderPtr			CreateVertexShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT* returnCode );
	DID3D11PixelShaderPtr			CreatePixelShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT* returnCode );
	DID3D11BufferPtr				CreateBuffer( u32 bufferSize, const void* bufferData, UINT bindFlags, HRESULT* returnCode );
	DID3DBlobPtr					CreateBlob( u32 blobSize, HRESULT* returnCode );
	DVertexBufferViewPtr			CreateVertexBufferView( DID3D11BufferPtr vertices, u32 stride, u32 offset );
	DIndexBufferViewPtr				CreateIndexBufferView( DID3D11BufferPtr indexBufferPtr, DXGI_FORMAT format, u32 offset );
	DSimpleMeshPtr					CreateSimpleMesh( DVertexBufferView *vertexView, DIndexBufferView *indexView, DMaterialController::DMaterial *material, u32 indexCount, u32 startVertexLocation, u32 startIndexLocation );
	DID3D11Texture2DPtr				CreateTexture2D( const DPixelColor *pixels, u16 width, u16 height, HRESULT *returnCode );
	DID3D11ShaderResourceViewPtr	CreateTexture2DView( ID3D11Texture2D *texture, HRESULT *returnCode );
	DID3D11InputLayoutPtr			CreateInputLayoutFromVertexShaderBlob( ID3DBlob *vertexShaderBlob, const D3D11_INPUT_ELEMENT_DESC *layout, u16 numLayouts, HRESULT *returnCode );
	DID3D11SamplerStatePtr			CreateSampler( HRESULT *returnCode );


	//
	DID3D11DevicePtr				GetDevice() const {
		return m_device;
	}
	//
	DID3D11DeviceContextPtr			GetDeviceContext() const {
		return m_deviceContext;
	}

private:
	//
	DID3D11DevicePtr			m_device;
	DID3D11DeviceContextPtr		m_deviceContext;

protected:
	//
	DRenderResourceManager( DID3D11DevicePtr device, DID3D11DeviceContextPtr context );
};

#pragma once

#include "DIntrusivePtr.h"
#include "DSharedObject.h"

#include "DTools.h"
#include "DRenderBasicTypes.h"

class DRenderResourceManager;
using DRenderResourceManagerPtr = DIntrusivePtr< DRenderResourceManager >;

class DRenderResourceManager : public DSharedObject {
public:
	//
	~DRenderResourceManager();

	DID3D11RenderTargetViewPtr CreateRenderTargetView( DID3D11Texture2DPtr texture, HRESULT *returnCode );
	DID3D11VertexShaderPtr CreateVertexShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT *returnCode );
	DID3D11PixelShaderPtr CreatePixelShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT *returnCode );
	DID3D11BufferPtr CreateBuffer( u32 bufferSize, const void *bufferData, UINT bindFlags, HRESULT *returnCode );
	DID3DBlobPtr CreateBlob( u32 blobSize, HRESULT *returnCode );

	DVertexBufferViewPtr CreateVertexBufferView( DID3D11BufferPtr vertices, u32 stride, u32 offset );

	DID3D11DevicePtr GetDevice() const;
	DID3D11DeviceContextPtr GetDeviceContext() const;

private:
	//
	DID3D11DevicePtr m_device;
	DID3D11DeviceContextPtr m_deviceContext;

protected:
	//
	friend DRenderResourceManagerPtr DCreateResourceManager( HRESULT *returnCode );

	explicit DRenderResourceManager( DID3D11DevicePtr device, DID3D11DeviceContextPtr context );
};

// Create Func
DRenderResourceManagerPtr DCreateResourceManager( HRESULT *returnCode );

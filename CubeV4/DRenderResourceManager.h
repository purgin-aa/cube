#ifndef _DRENDERRESOURCEMANAGER_H_
#define _DRENDERRESOURCEMANAGER_H_

#include <d3d11.h>
#include <d3dcompiler.h>

#include "DIntrusivePtr.h"
#include "DSharedObject.h"

#include "DTools.h"
#include "DRenderBasicTypes.h"

class DRenderResourceManager;
typedef DIntrusivePtr<DRenderResourceManager> DRenderResourceManagerPtr;

class DRenderResourceManager
	: public DSharedObject
{
public:
	~DRenderResourceManager( void );

	DID3D11RenderTargetViewPtr CreateRenderTargetView( DID3D11Texture2DPtr texture, HRESULT *returnCode );
	DID3D11VertexShaderPtr CreateVertexShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT *returnCode );
	DID3D11PixelShaderPtr CreatePixelShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT *returnCode );
	DID3D11BufferPtr CreateBuffer( u32 bufferSize, const void *bufferData, UINT bindFlags, HRESULT *returnCode );
	DID3DBlobPtr CreateBlob( u32 blobSize, HRESULT *returnCode );
	
	DVertexBufferViewPtr CreateVertexBufferView( DID3D11BufferPtr vertices, u32 stride, u32 offset );

	DID3D11DevicePtr GetDevice( void ) const;
	DID3D11DeviceContextPtr GetDeviceContext( void ) const;

private:
	DID3D11DevicePtr m_device;
	DID3D11DeviceContextPtr m_deviceContext;

protected:
	friend DRenderResourceManagerPtr DCreateResourceManager( HRESULT *returnCode );

	explicit DRenderResourceManager( DID3D11DevicePtr device,
									 DID3D11DeviceContextPtr context );

};

// Create Func
DRenderResourceManagerPtr DCreateResourceManager( HRESULT *returnCode );

#endif

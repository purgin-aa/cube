#include "DRenderResourceManager.h"

#include <assert.h>


//
DRenderResourceManager::~DRenderResourceManager() {
	if( m_deviceContext )
		m_deviceContext->ClearState();
}


//
DID3D11RenderTargetViewPtr DRenderResourceManager::CreateRenderTargetView( DID3D11Texture2DPtr texture, HRESULT* returnCode ) {
	assert( texture );

	DID3D11RenderTargetViewPtr textureView;
	HRESULT hr = m_device->CreateRenderTargetView( texture.Get(), nullptr, &textureView );
	if( returnCode )
		*returnCode = hr;

	return textureView;
}


//
DID3D11VertexShaderPtr DRenderResourceManager::CreateVertexShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT *returnCode ) {
	assert( m_device );
	assert( shaderBlob );

	DID3D11VertexShaderPtr vertexShader;
	HRESULT hr = m_device->CreateVertexShader( 
		shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &vertexShader );
	if( returnCode )
		*returnCode = hr;

	return vertexShader;
}


//
DID3D11PixelShaderPtr DRenderResourceManager::CreatePixelShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT *returnCode ) {
	assert( m_device );
	assert( shaderBlob );

	DID3D11PixelShaderPtr pixelShader;
	HRESULT hr = m_device->CreatePixelShader( 
		 shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),	nullptr, &pixelShader );

	if( returnCode )
		*returnCode = hr;

	return pixelShader;
}


//
DID3D11BufferPtr DRenderResourceManager::CreateBuffer( u32 bufferSize, const void* bufferData, UINT bindFlags, HRESULT* returnCode ) {
	assert( m_device );

	D3D11_BUFFER_DESC bufferDesc;
	DTools::ClearStruct( bufferDesc );
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = bufferSize;
	bufferDesc.BindFlags = bindFlags;
	bufferDesc.CPUAccessFlags = 0;

	DID3D11BufferPtr buffer;
	HRESULT hr = S_OK;

	if( bufferData ) {
		D3D11_SUBRESOURCE_DATA resourceData;
		DTools::ClearStruct( resourceData );
		resourceData.pSysMem = bufferData;
		hr = m_device->CreateBuffer( &bufferDesc, &resourceData, &buffer );
	} else {
		hr = m_device->CreateBuffer( &bufferDesc, nullptr, &buffer );
	}
	if( returnCode )
		*returnCode = hr;

	return buffer;
}


//
DID3DBlobPtr DRenderResourceManager::CreateBlob( u32 blobSize, HRESULT* returnCode ) {
	DID3DBlobPtr blob;
	HRESULT hr = D3DCreateBlob( blobSize, &blob );
	if( returnCode )
		*returnCode = hr;

	return blob;
}


//
DVertexBufferViewPtr DRenderResourceManager::CreateVertexBufferView( DID3D11BufferPtr vertices, u32 stride, u32 offset ) {
	// assert( vertices );
	// assert( stride );
	DVertexBufferViewPtr view( new DVertexBufferView( vertices, stride, offset ) );
	return view;
}


//
DID3D11DevicePtr DRenderResourceManager::GetDevice() const {
	return m_device;
}


//
DID3D11DeviceContextPtr DRenderResourceManager::GetDeviceContext() const {
	return m_deviceContext;
}


//
DRenderResourceManager::DRenderResourceManager( DID3D11DevicePtr device, DID3D11DeviceContextPtr context )
	: m_device( device )
	, m_deviceContext( context ) {
}


//
DRenderResourceManagerPtr DCreateResourceManager( HRESULT * returnCode ) {
	DID3D11DevicePtr device;
	DID3D11DeviceContextPtr deviceContext;
	D3D_FEATURE_LEVEL featureLevel;

	HRESULT hr = S_OK;
	UINT uiFlags = 0;

#if defined( DEBUG ) || defined( _DEBUG )
	uiFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	hr = D3D11CreateDevice( 
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		uiFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&device,
		&featureLevel,
		&deviceContext );

	if( returnCode )
		*returnCode = hr;

	if( FAILED( hr ) )
		return nullptr;

#if defined( DEBUG ) || defined( _DEBUG )
	DID3D11DebugPtr debug;
	device->QueryInterface( __uuidof( ID3D11Debug ), ( void ** )&debug );
	debug->ReportLiveDeviceObjects( D3D11_RLDO_DETAIL );
#endif

	DRenderResourceManagerPtr manager( new DRenderResourceManager( device, deviceContext ) );
	return manager;
}

#include "Precompiled.h"
#include "DRenderResourceManager.h"


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
DID3D11VertexShaderPtr DRenderResourceManager::CreateVertexShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT* returnCode ) {
	assert( shaderBlob );

	DID3D11VertexShaderPtr vertexShader;
	HRESULT hr = m_device->CreateVertexShader( 
		shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &vertexShader );
	if( returnCode )
		*returnCode = hr;

	return vertexShader;
}


//
DID3D11PixelShaderPtr DRenderResourceManager::CreatePixelShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT* returnCode ) {
	assert( shaderBlob );

	DID3D11PixelShaderPtr pixelShader;
	HRESULT hr = m_device->CreatePixelShader( 
		 shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), nullptr, &pixelShader );

	if( returnCode )
		*returnCode = hr;

	return pixelShader;
}


//
DID3D11BufferPtr DRenderResourceManager::CreateBuffer( u32 bufferSize, const void* bufferData, UINT bindFlags, HRESULT* returnCode ) {
	assert( m_device );

	D3D11_BUFFER_DESC bufferDesc;
	DTools::MemZero( bufferDesc );
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = bufferSize;
	bufferDesc.BindFlags = bindFlags;
	bufferDesc.CPUAccessFlags = 0;

	DID3D11BufferPtr buffer;
	HRESULT hr = S_OK;

	if( bufferData ) {
		D3D11_SUBRESOURCE_DATA resourceData;
		DTools::MemZero( resourceData );
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
DIndexBufferViewPtr DRenderResourceManager::CreateIndexBufferView( DID3D11BufferPtr indexBufferPtr, DXGI_FORMAT format, u32 offset ) {
	DIndexBufferViewPtr view( new DIndexBufferView( indexBufferPtr, format, offset ) );
	return view;
}


//
DSimpleMeshPtr DRenderResourceManager::CreateSimpleMesh( DVertexBufferView* vertexView, DIndexBufferView* indexView, DMaterialController::DMaterial* material, u32 indexCount, u32 startVertexLocation, u32 startIndexLocation ) {
	assert( vertexView );
	assert( indexView );
	assert( material );
	assert( indexCount > 0 );

	DSimpleMeshPtr mesh( new DSimpleMesh( vertexView, indexView, material, indexCount, startVertexLocation, startIndexLocation ) );
	return mesh;
}


//
DID3D11Texture2DPtr DRenderResourceManager::CreateTexture2D( const DPixelColor* pixels, u32 width, u32 height, HRESULT* returnCode ) {
	assert( pixels );
	assert( m_device );

	D3D11_TEXTURE2D_DESC textureDesc;
	DTools::MemZero( textureDesc );

	textureDesc.Width = static_cast< UINT > ( width );
	textureDesc.Height = static_cast< UINT > ( height );
	textureDesc.MipLevels = textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA textureData;
	DTools::MemZero( textureData );

	textureData.SysMemPitch = width * sizeof( DPixelColor );
	textureData.pSysMem = pixels;

	DID3D11Texture2DPtr texture;
	HRESULT hr = S_OK;

	hr = m_device->CreateTexture2D(
		&textureDesc,
		&textureData,
		&texture );

	if( FAILED( hr ) ) {
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	return texture;
}


//
DID3D11ShaderResourceViewPtr DRenderResourceManager::CreateTexture2DView( ID3D11Texture2D* texture, HRESULT* returnCode ) {
	assert( texture );

	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	DTools::MemZero( viewDesc );

	viewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	viewDesc.Texture2D.MipLevels = 1;

	DID3D11ShaderResourceViewPtr textureView;
	HRESULT hr = S_OK;

	hr = m_device->CreateShaderResourceView(
		texture,
		&viewDesc,
		&textureView );

	if( FAILED( hr ) ) {
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	return textureView;
}

//
DID3D11InputLayoutPtr DRenderResourceManager::CreateInputLayoutFromVertexShaderBlob( ID3DBlob* vertexShaderBlob, const D3D11_INPUT_ELEMENT_DESC* layout, u16 numLayouts, HRESULT* returnCode ) {
	assert( vertexShaderBlob );
	assert( layout );
	assert( numLayouts );

	DID3D11InputLayoutPtr inputLayout;
	HRESULT hr = S_OK;

	hr = m_device->CreateInputLayout(
		layout,
		numLayouts,
		vertexShaderBlob->GetBufferPointer(),
		vertexShaderBlob->GetBufferSize(),
		&inputLayout );

	if( FAILED( hr ) )
	{
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	return inputLayout;
}


//
DID3D11SamplerStatePtr DRenderResourceManager::CreateSampler( HRESULT* returnCode ) {
	D3D11_SAMPLER_DESC samplerDesc;
	DTools::MemZero( samplerDesc );
	
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	samplerDesc.MinLOD = 0.0f;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	DID3D11SamplerStatePtr sampler;
	HRESULT hr = m_device->CreateSamplerState( &samplerDesc, &sampler );
	if( FAILED( hr ) ) {
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	return sampler;
}


//
DRenderResourceManager::DRenderResourceManager( DID3D11DevicePtr device, DID3D11DeviceContextPtr context )
	: m_device( device )
	, m_deviceContext( context ) {
}


//
DRenderResourceManagerPtr DRenderResourceManager::Create( HRESULT* returnCode ) {
	DID3D11DevicePtr device;
	DID3D11DeviceContextPtr deviceContext;
	D3D_FEATURE_LEVEL featureLevel;

	UINT deviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#if defined( DEBUG ) || defined( _DEBUG )
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		deviceFlags,
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

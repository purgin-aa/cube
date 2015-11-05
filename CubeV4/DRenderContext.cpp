#include "DRenderContext.h"

#include <assert.h>

//
//// IMPLEMENTATION DRenderObjectFactory
//
//DRenderObjectFactory::DRenderObjectFactory( DRenderContextPtr context )
//	: m_context( context )
//{
//}
//
//DID3D11BufferPtr DRenderObjectFactory::CreateBuffer( u32 bufferSize, const void * bufferData, UINT bindFlags, HRESULT * returnCode )
//{
//	assert( m_context );
//
//	D3D11_BUFFER_DESC bufferDesc;
//	DTools::ClearStruct( bufferDesc );
//	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
//	bufferDesc.ByteWidth = bufferSize;
//	bufferDesc.BindFlags = bindFlags;
//	bufferDesc.CPUAccessFlags = 0;
//
//	DID3D11BufferPtr buffer;
//	HRESULT hr = S_OK;
//
//	if ( bufferData )
//	{
//		D3D11_SUBRESOURCE_DATA resourceData;
//		DTools::ClearStruct( resourceData );
//		resourceData.pSysMem = bufferData;
//
//		hr = m_context->GetDevice()->CreateBuffer( &bufferDesc,
//												   &resourceData,
//												   &buffer );
//	}
//	else
//		hr = m_context->GetDevice()->CreateBuffer( &bufferDesc,
//												   nullptr,
//												   &buffer );
//	if ( returnCode )
//		*returnCode = hr;
//
//	return buffer;
//}
//
//DID3D11VertexShaderPtr DRenderObjectFactory::CreateVertexShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT *returnCode )
//{
//	assert( m_context );
//	assert( shaderBlob );
//
//	DID3D11VertexShaderPtr vertexShader;
//	HRESULT hr = S_OK;
//
//	hr = m_context->GetDevice()->CreateVertexShader( shaderBlob->GetBufferPointer(),
//													 shaderBlob->GetBufferSize(),
//													 nullptr,
//													 &vertexShader );
//	if ( returnCode )
//		*returnCode = hr;
//
//	return vertexShader;
//}
//
//DID3D11PixelShaderPtr DRenderObjectFactory::CreatePixelShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT *returnCode )
//{
//	assert( m_context );
//	assert( shaderBlob );
//
//	DID3D11PixelShaderPtr pixelShader;
//	HRESULT hr = S_OK;
//
//	hr = m_context->GetDevice()->CreatePixelShader( shaderBlob->GetBufferPointer(),
//													shaderBlob->GetBufferSize(),
//													nullptr,
//													&pixelShader );
//
//	if ( returnCode )
//		*returnCode = hr;
//
//	return pixelShader;
//}
//
//DID3DBlobPtr DRenderObjectFactory::CreateBlob( u32 blobSize, HRESULT *returnCode )
//{
//	DID3DBlobPtr blob;
//
//	HRESULT hr = D3DCreateBlob( blobSize, &blob );
//
//	if ( returnCode )
//		*returnCode = hr;
//
//	return blob;
//}
//
////DVertexBufferViewPtr DRenderObjectFactory::CreateVertexBufferView( DID3D11BufferPtr vertexBuffer, u32 stride, u32 offset )
////{
////	assert( vertexBuffer );
////	assert( stride != 0 );
////
////	DVertexBufferViewPtr vertexBufferPtr( new DVertexBufferView( DRenderObjectFactoryPtr( this ), vertexBuffer, stride, offset ) );
////
////	return vertexBufferPtr;
////}
////
////DIndexBufferViewPtr DRenderObjectFactory::CreateIndexBufferView( DID3D11BufferPtr indexBuffer, u32 offset, DXGI_FORMAT bufferFormat )
////{
////	assert( indexBuffer );
////	assert( bufferFormat );
////
////	DIndexBufferViewPtr indexBufferPtr( new DIndexBufferView( DRenderObjectFactoryPtr( this ), indexBuffer, bufferFormat, offset ) );
////
////	return indexBufferPtr;
////}
//
//DRenderContextPtr DRenderObjectFactory::GetContext( void )
//{
//	return m_context;
//}
//
////void DRenderObjectFactory::ReleaseChild( DVertexBufferView * vertexBufferView )
////{
////	assert( vertexBufferView );
////	delete vertexBufferView;
////}
////
////void DRenderObjectFactory::ReleaseChild( DIndexBufferView * indexBufferView )
////{
////	assert( indexBufferView );
////	delete indexBufferView;
////}
//// END OF IMPLEMENTATION: DRenderFactory
//
//// IMPLEMENTATION: DRenderContext
//
//
//void DRenderContext::SetFullscreenState( bool blFullscreen )
//{
//	assert( m_swapChain );
//
//	if ( m_config.blFullscreen != blFullscreen )
//	{
//		m_swapChain->SetFullscreenState( blFullscreen, nullptr );
//
//		m_config.blFullscreen = blFullscreen;
//	}
//
//}
//
//void DRenderContext::SetPerspectiveMode( void )
//{
//	assert( m_deviceContext );
//	assert( m_config.fovAngle > 0.0f );
//	assert( m_config.width );
//	assert( m_config.height );
//	assert( m_config.nearZ > 0.0f );
//	assert( m_config.farZ > 0.0f );
//	assert( m_config.nearZ < m_config.farZ );
//
//	m_stateMatrices.projection =
//		XMMatrixTranspose( XMMatrixPerspectiveFovLH( m_config.fovAngle,
//													 m_config.width / ( f32 )m_config.height,
//													 m_config.nearZ,
//													 m_config.farZ ) );
//
//	m_updateStateMatrices = true;
//}
//
//void DRenderContext::SetVertexShader( DID3D11VertexShaderPtr vertexShader )
//{
//	assert( m_deviceContext );
//
//	m_deviceContext->VSSetShader( vertexShader.Get(),
//								  nullptr,
//								  0 );
//}
//
//void DRenderContext::SetPixelShader( DID3D11PixelShaderPtr pixelShader )
//{
//	assert( m_deviceContext );
//
//	m_deviceContext->PSSetShader( pixelShader.Get(),
//								  nullptr,
//								  0 );
//}
//
//DID3D11DevicePtr DRenderContext::GetDevice( void )
//{
//	return m_device;
//}
//
//DID3D11DeviceContextPtr DRenderContext::GetDeviceContext( void )
//{
//	return m_deviceContext;
//}
//
//void DRenderContext::Present( void )
//{
//	assert( m_swapChain );
//
//	m_swapChain->Present( 0, 0 );
//}
//
//void DRenderContext::ClearCurrentTargetView( f32 color[ 4 ] )
//{
//	assert( m_deviceContext );
//	assert( m_renderTargetView );
//
//	m_deviceContext->ClearRenderTargetView( m_renderTargetView.Get(),
//											color );
//}
//
//void DRenderContext::SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY topology )
//{
//	assert( m_deviceContext );
//
//	m_deviceContext->IASetPrimitiveTopology( topology );
//}
//
//void DRenderContext::SetStateMatrices( const DWorldViewMatrices & stateMatrices )
//{
//	assert( m_deviceContext );
//
//	m_stateMatrices.world = XMMatrixTranspose( stateMatrices.world );
//	m_stateMatrices.view = XMMatrixTranspose( stateMatrices.view );
//
//	m_updateStateMatrices = true;
//}
//
//void DRenderContext::DrawIndexed( u32 indexCount, u32 startIndexLocation, u32 startVertexLocation )
//{
//	assert( m_deviceContext );
//
//	m_deviceContext->DrawIndexed( indexCount,
//								  startIndexLocation,
//								  startVertexLocation );
//}
//
//DRenderObjectFactoryPtr DRenderContext::GetRenderObjectFactory( void ) const
//{
//	return m_objectFactory;
//}
//
//DRenderContext::DRenderContext( const DConfig &config,
//								DID3D11DevicePtr device, 
//								DID3D11DeviceContextPtr deviceContext,
//								DIDXGISwapChainPtr swapChain, 
//								DID3D11RenderTargetViewPtr backBufferView, 
//								DID3D11BufferPtr stateMatricesBuffer, 
//								DID3D11SamplerStatePtr samplerState, 
//								const StateMatrices & stateMatrices ) :
//	m_config( config ),
//	m_device( device ), 
//	m_deviceContext( deviceContext ), 
//	m_swapChain( swapChain ), 
//	m_renderTargetView( backBufferView ), 
//	m_stateMatricesBuffer( stateMatricesBuffer ),
//	m_samplerState( samplerState ),
//	m_stateMatrices( stateMatrices ),
//	m_updateStateMatrices( false )
//{
//}
//
//void DRenderContext::UpdateStateMatrices( void )
//{
//	assert( m_deviceContext );
//	assert( m_stateMatricesBuffer );
//
//	if ( m_updateStateMatrices )
//	{
//		m_deviceContext->UpdateSubresource( m_stateMatricesBuffer.Get(),
//											0,
//											nullptr,
//											&m_stateMatrices,
//											0,
//											0 );
//		m_updateStateMatrices = false;
//	}
//}
//
//DRenderContextPtr CreateRenderContext( const DConfig & config, HRESULT * returnCode )
//{
//	DXGI_SWAP_CHAIN_DESC chainDesc;
//	DTools::ClearStruct( chainDesc );
//
//	// Setup chainDesc
//	chainDesc.BufferCount = 1;
//	chainDesc.BufferDesc.Width = config.width;
//	chainDesc.BufferDesc.Height = config.height;
//	chainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	chainDesc.BufferDesc.RefreshRate.Numerator = 60;
//	chainDesc.BufferDesc.RefreshRate.Denominator = 1;
//	chainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	chainDesc.OutputWindow = config.window;
//	chainDesc.SampleDesc = config.sampleDesc;
//	chainDesc.Windowed = !config.blFullscreen;
//	chainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
//
//	DID3D11DevicePtr device;
//	DID3D11DeviceContextPtr deviceContext;
//	DIDXGISwapChainPtr swapChain;
//
//	D3D_FEATURE_LEVEL featureLevel;
//
//	HRESULT hr = D3D11CreateDeviceAndSwapChain( nullptr,
//												D3D_DRIVER_TYPE_HARDWARE,
//												nullptr,
//												D3D11_CREATE_DEVICE_DEBUG,
//												nullptr,
//												0,
//												D3D11_SDK_VERSION,
//												&chainDesc,
//												&swapChain,
//												&device,
//												&featureLevel,
//												&deviceContext
//												);
//
//	if ( FAILED( hr ) )
//	{
//		if ( returnCode )
//			*returnCode = hr;
//		return nullptr;
//	}
//
//	DID3D11Texture2DPtr backBuffer;
//	hr = swapChain->GetBuffer( 0,
//							   _uuidof(ID3D11Texture2D),
//							   ( void ** )&backBuffer );
//
//	if ( FAILED( hr ) )
//	{
//		if ( returnCode )
//			*returnCode = hr;
//		return nullptr;
//	}
//
//	DID3D11RenderTargetViewPtr renderTargetView;
//	hr = device->CreateRenderTargetView( backBuffer.Get(),
//										 nullptr,
//										 &renderTargetView );
//
//	if ( FAILED( hr ) )
//	{
//		if ( returnCode )
//			*returnCode = hr;
//		return nullptr;
//	}
//
//	deviceContext->OMSetRenderTargets( 1,
//									   &renderTargetView,
//									   nullptr );
//
//	D3D11_VIEWPORT viewport =
//	{
//		0.0f,
//		0.0f,
//		static_cast< f32 >( config.width ),
//		static_cast< f32 >( config.height ),
//		0.0f,
//		1.0f
//	};
//
//	deviceContext->RSSetViewports( 1,
//								   &viewport );
//
//
//	DRenderContext::StateMatrices matrices
//	{
//		XMMatrixTranspose( XMMatrixIdentity() ),
//		XMMatrixTranspose( XMMatrixIdentity() ),
//		XMMatrixTranspose( XMMatrixIdentity() ),
//	};
//
//
//	DID3D11BufferPtr stateMatricesBuffer;
//
//	D3D11_BUFFER_DESC bufferDesc =
//	{
//		sizeof( matrices ),
//		D3D11_USAGE_DEFAULT,
//		D3D11_BIND_CONSTANT_BUFFER,
//		0u, // CPU access
//		0u, // Misc flags
//		0u  // structureByteStride 
//	};
//
//	D3D11_SUBRESOURCE_DATA resourceData =
//	{
//		&matrices, 0u, 0u
//	};
//
//	hr = device->CreateBuffer( &bufferDesc,
//							   &resourceData,
//							   &stateMatricesBuffer );
//
//	if ( FAILED( hr ) )
//	{
//		if ( returnCode )
//			*returnCode = hr;
//		return nullptr;
//	}
//
//	deviceContext->VSSetConstantBuffers( 0,
//										 1,
//										 &stateMatricesBuffer );
//
//	DID3D11SamplerStatePtr samplerState;
//
//	D3D11_SAMPLER_DESC samplerDesc =
//	{
//		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
//		D3D11_TEXTURE_ADDRESS_WRAP,
//		D3D11_TEXTURE_ADDRESS_WRAP,
//		D3D11_TEXTURE_ADDRESS_WRAP,
//		0.0f, // MipLODBias
//		0, // MaxLODBias
//		D3D11_COMPARISON_NEVER,
//		{ 0.0f, 0.0f, 0.0f, 0.0f }, // border color
//		0.0f,
//		D3D11_FLOAT32_MAX
//	};
//
//	hr = device->CreateSamplerState( &samplerDesc,
//									 &samplerState );
//
//	if ( FAILED( hr ) )
//	{
//		if ( returnCode )
//			*returnCode = hr;
//		return nullptr;
//	}
//	
//	deviceContext->PSSetSamplers( 0, 
//								  1, 
//								  &samplerState );
//
//	deviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
//
//	DRenderContextPtr renderContext( new DRenderContext( config, 
//														 device, 
//														 deviceContext, 
//														 swapChain, 
//														 renderTargetView, 
//														 stateMatricesBuffer, 
//														 samplerState, 
//														 matrices ) );
//
//
//	return renderContext;
//}

//
//void DRenderContext::SetPerspectiveMode( const DRenderPerspectiveModeDesc & perspectiveModeDesc )
//{
//	// todo
//}

//void DRenderContext::SetWVMatrices( const DRenderWVMatrices & stateMatrices )
//{
//}

void DRenderContext::SetVertexShader( DID3D11VertexShaderPtr vertexShader )
{
	assert( m_deviceContext );

	m_deviceContext->VSSetShader( vertexShader.Get(),
								  nullptr,
								  0 );
}

void DRenderContext::SetPixelShader( DID3D11PixelShaderPtr pixelShader )
{
	assert( m_deviceContext );

	m_deviceContext->PSSetShader( pixelShader.Get(),
								  nullptr,
								  0 );
}

void DRenderContext::SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY topology )
{
	assert( m_deviceContext );

	m_deviceContext->IASetPrimitiveTopology( topology );
}

void DRenderContext::DrawIndexed( u32 indexCount, u32 startIndexLocation, u32 startVertexLocation )
{
	assert( m_deviceContext );

	m_deviceContext->DrawIndexed( indexCount, startIndexLocation, startVertexLocation );
}

void DRenderContext::FillCurrentTargetView( f32 color[ 4 ] )
{
	assert( m_deviceContext );
	assert( m_renderTarget );

	m_deviceContext->ClearRenderTargetView( m_renderTarget.Get(),
											color );
}

void DRenderContext::SetRenderTargetView( DID3D11RenderTargetViewPtr renderTarget, const DRenderTargetSize & size )
{
	assert( m_deviceContext );
	assert( renderTarget );

	assert( ( size.width > 0u ) && ( size.height > 0u ) );

	m_renderTargetSize = size;
	m_renderTarget = renderTarget;

	m_deviceContext->OMSetRenderTargets( 0, &renderTarget, nullptr );
}

DID3D11DeviceContextPtr DRenderContext::GetDeviceContext( void ) const
{
	return m_deviceContext;
}

DRenderContext::DRenderContext( DRenderResourceManagerPtr manager )
	: m_manager( manager )
{
	assert( m_manager );

	m_deviceContext = manager->GetDeviceContext();

	assert( m_deviceContext );

	m_renderTargetSize = { 0u, 0u };
}

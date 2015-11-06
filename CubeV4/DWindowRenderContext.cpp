#include "Precompiled.h"
#include "DWindowRenderContext.h"


//
DWindowRenderContext::~DWindowRenderContext() {
	if( m_swapChain && m_windowContextConfig.fullscreen )
		m_swapChain->SetFullscreenState( false, nullptr );
}


//
void DWindowRenderContext::Present() {
	assert( m_swapChain );
	m_swapChain->Present( 0, 0 );
}


//
void DWindowRenderContext::SetFullscreenState( bool blFullscreen ) {
	assert( m_swapChain );
	m_swapChain->SetFullscreenState( blFullscreen, nullptr );
	m_windowContextConfig.fullscreen = blFullscreen;
}


//
DID3D11RenderTargetViewPtr DWindowRenderContext::GetBackBufferView() const {
	return m_backBufferView;
}


//
DWindowRenderContext::DWindowRenderContext( 
	DRenderResourceManagerPtr manager,
	DIDXGISwapChain1Ptr swapChain,
	DID3D11RenderTargetViewPtr backBufferView,
	const DWindowContextConfig &config )
	: DRenderContext( manager )
	, m_backBufferView( backBufferView )
	, m_swapChain( swapChain )
	, m_windowContextConfig( config ) {
	assert( manager );
	assert( swapChain );
	assert( backBufferView );
	assert( ( config.width > 0 ) && ( config.height > 0 ) );

	DRenderTargetSize size = {
		config.width,
		config.height
	};

	SetRenderTargetView( backBufferView, size );
}


//
DWindowRenderContextPtr DCreateWindowRenderContext( DRenderResourceManagerPtr manager, const DWindowContextConfig& config, HRESULT* returnCode ) {
	assert( manager );
	assert( config.currentWindow );
	assert( ( config.width > 0u ) && ( config.height > 0u ) );

	DID3D11DevicePtr device = manager->GetDevice();
	assert( device );

	DIDXGIDevice2Ptr dxgiDevice;
	HRESULT hr = device->QueryInterface( __uuidof( IDXGIDevice2 ), ( void ** )&dxgiDevice );
	if( FAILED( hr ) ) {
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	DIDXGIAdapter2Ptr dxgiAdapter;
	hr = dxgiDevice->GetParent( __uuidof( IDXGIAdapter2 ), ( void** )&dxgiAdapter );
	if( FAILED( hr ) ) {
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	DIDXGIFactory2Ptr factory;
	hr = dxgiAdapter->GetParent( __uuidof( IDXGIFactory2 ), ( void** )&factory );
	if( FAILED( hr ) ) {
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	DIDXGISwapChain1Ptr swapChain;

	DXGI_SWAP_CHAIN_DESC1 chainDesc;
	DTools::ClearStruct( chainDesc );
	chainDesc.Width = config.width;
	chainDesc.Height = config.height;
	chainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	chainDesc.SampleDesc.Count = 1;
	chainDesc.SampleDesc.Quality = 0;
	chainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	chainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	chainDesc.BufferCount = 1;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDesc;
	DTools::ClearStruct( fullscreenDesc );
	fullscreenDesc.RefreshRate = config.refreshRate;
	fullscreenDesc.Windowed = !config.fullscreen;

	hr = factory->CreateSwapChainForHwnd( 
		device.Get(),
		config.currentWindow,
		&chainDesc,
		&fullscreenDesc,
		nullptr,
		&swapChain );
	if( FAILED( hr ) ) {
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	DID3D11Texture2DPtr backBuffer;
	swapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( void** )&backBuffer );

	DID3D11RenderTargetViewPtr backBufferView = manager->CreateRenderTargetView( backBuffer, 	&hr );
	if( FAILED( hr ) ) {
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	DWindowRenderContextPtr context( new DWindowRenderContext( manager, swapChain, backBufferView, config ) );
	return context;
}

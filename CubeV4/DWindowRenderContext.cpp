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
void DWindowRenderContext::SetFullscreenState( bool enable ) {
	assert( m_swapChain );
	m_swapChain->SetFullscreenState( enable, nullptr );
	m_windowContextConfig.fullscreen = enable;
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
	assert( ( config.displayMode.width > 0 ) && ( config.displayMode.height > 0 ) );
	
	SetRenderTargetView( backBufferView, { config.displayMode.width, config.displayMode.height } );
}

//
DWindowRenderContextPtr DWindowRenderContext::Create( DRenderResourceManagerPtr manager, const DWindowContextConfig& config, HRESULT* returnCode ) {
#define LM_CHECKRESULT( code, pcode, r ) if ( FAILED( code ) ) { if ( pcode ) *pcode = code; return r; }

	assert( manager );
	assert( config.currentWindow );
	assert( ( config.displayMode.width > 0 ) && ( config.displayMode.height > 0u ) );

	DID3D11DevicePtr device = manager->GetDevice();
	assert( device );

	DIDXGIDevice2Ptr dxgiDevice;
	HRESULT hr = device->QueryInterface( __uuidof( IDXGIDevice2 ), ( void ** )&dxgiDevice );
	LM_CHECKRESULT( hr, returnCode, nullptr );

	DIDXGIAdapter2Ptr dxgiAdapter;
	hr = dxgiDevice->GetParent( __uuidof( IDXGIAdapter2 ), ( void** )&dxgiAdapter );
	LM_CHECKRESULT( hr, returnCode, nullptr );

	DWindowContextConfig supportedConfig = config;

	// check display mode
	if( !DCheckDisplayMode(
		dxgiAdapter.Get(),
		&config.displayMode,
		&supportedConfig.displayMode,
		returnCode ) ) {

		DLog::Error( "Expected display mode {%ux%u : %u/%u} not supported\n", 
					 config.displayMode.width, config.displayMode.height, 
					 config.displayMode.refreshRate.Numerator, 
					 config.displayMode.refreshRate.Denominator );
		return nullptr;
	}
	
	DIDXGIFactory2Ptr factory;
	hr = dxgiAdapter->GetParent( __uuidof( IDXGIFactory2 ), ( void** )&factory );
	LM_CHECKRESULT( hr, returnCode, nullptr );

	//
	DIDXGISwapChain1Ptr swapChain;

	DXGI_SWAP_CHAIN_DESC1 chainDesc;
	DTools::MemZero( chainDesc );
	chainDesc.Width = supportedConfig.displayMode.width;
	chainDesc.Height = supportedConfig.displayMode.height;
	chainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	chainDesc.SampleDesc.Count = 1;
	chainDesc.SampleDesc.Quality = 0;
	chainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	chainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	chainDesc.BufferCount = 1;

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDesc;
	DTools::MemZero( fullscreenDesc );
	fullscreenDesc.RefreshRate = supportedConfig.displayMode.refreshRate;
	fullscreenDesc.Windowed = !config.fullscreen;

	hr = factory->CreateSwapChainForHwnd( 
		device.Get(),
		config.currentWindow,
		&chainDesc,
		&fullscreenDesc,
		nullptr,
		&swapChain );
	LM_CHECKRESULT( hr, returnCode, nullptr );

	DID3D11Texture2DPtr backBuffer;
	swapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( void** )&backBuffer );

	DID3D11RenderTargetViewPtr backBufferView = manager->CreateRenderTargetView( backBuffer, &hr );
	LM_CHECKRESULT( hr, returnCode, nullptr );

	DWindowRenderContextPtr context( new DWindowRenderContext( manager, swapChain, backBufferView, supportedConfig ) );
	
	return context;

#undef LM_CHECKRESULT
}

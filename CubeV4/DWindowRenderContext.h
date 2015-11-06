#pragma once

#include "DRenderContext.h"

//
struct DWindowContextConfig {
	HWND			currentWindow;
	DXGI_RATIONAL	refreshRate;
	u16				width;
	u16				height;
	bool			fullscreen;
	// todo quality
};


//
class DWindowRenderContext;
using DWindowRenderContextPtr = DIntrusivePtr< DWindowRenderContext >;


//
class DWindowRenderContext : public DRenderContext {
public:
	//
	~DWindowRenderContext();

	void Present();
	void SetFullscreenState( bool blFullscreen );

	DID3D11RenderTargetViewPtr GetBackBufferView() const;

private:
	//
	DIDXGISwapChain1Ptr			m_swapChain;
	DID3D11RenderTargetViewPtr	m_backBufferView;
	DWindowContextConfig		m_windowContextConfig;

protected:
	//
	friend DWindowRenderContextPtr DCreateWindowRenderContext( 
		DRenderResourceManagerPtr manager,
		const DWindowContextConfig &config,
		HRESULT *returnCode );

	explicit DWindowRenderContext( 
		DRenderResourceManagerPtr manager,
		DIDXGISwapChain1Ptr swapChain,
		DID3D11RenderTargetViewPtr backBufferView,
		const DWindowContextConfig &config );
};


//
DWindowRenderContextPtr DCreateWindowRenderContext( DRenderResourceManagerPtr manager, const DWindowContextConfig &config, HRESULT *returnCode );

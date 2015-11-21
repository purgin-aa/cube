#pragma once

#include "DRenderContext.h"
#include "DDirect3DTools.h"

//
struct DWindowContextConfig {
	HWND			currentWindow;
	DDisplayMode	displayMode;
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
	static DWindowRenderContextPtr	Create( DRenderResourceManagerPtr manager, const DWindowContextConfig& config, HRESULT* returnCode );
	//
	~DWindowRenderContext();

	void							Present();
	void							SetFullscreenState( bool enable );

	DID3D11RenderTargetViewPtr		GetBackBufferView() const;

private:
	//
	DIDXGISwapChain1Ptr			m_swapChain;
	DID3D11RenderTargetViewPtr	m_backBufferView;
	DWindowContextConfig		m_windowContextConfig;

protected:
	//
	DWindowRenderContext( 
		DRenderResourceManagerPtr manager,
		DIDXGISwapChain1Ptr swapChain,
		DID3D11RenderTargetViewPtr backBufferView,
		const DWindowContextConfig &config );
};

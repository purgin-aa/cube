#ifndef _DWINDOWRENDERCONTEXT_H_
#define _DWINDOWRENDERCONTEXT_H_

#include "DRenderContext.h"

struct DWindowContextConfig
{
	HWND currentWindow;
	DXGI_RATIONAL refreshRate;
	u16 width;
	u16 height;
	//
	bool blFullscreen;
	// todo quality
};

class DWindowRenderContext;
typedef DIntrusivePtr<DWindowRenderContext> DWindowRenderContextPtr;

class DWindowRenderContext
	: public DRenderContext
{
public:
	~DWindowRenderContext( void );

	void Present();
	void SetFullscreenState( bool blFullscreen );
	
	DID3D11RenderTargetViewPtr GetBackBufferView( void ) const;

private:
	DIDXGISwapChain1Ptr m_swapChain;
	DID3D11RenderTargetViewPtr m_backBufferView;

	DWindowContextConfig m_windowContextConfig;
protected:
	friend DWindowRenderContextPtr DCreateWindowRenderContext( DRenderResourceManagerPtr manager, 
															   const DWindowContextConfig &config, 
															   HRESULT *returnCode );
	
	explicit DWindowRenderContext( DRenderResourceManagerPtr manager,
								   DIDXGISwapChain1Ptr swapChain,
								   DID3D11RenderTargetViewPtr backBufferView,
								   const DWindowContextConfig &config );

};

DWindowRenderContextPtr DCreateWindowRenderContext( DRenderResourceManagerPtr manager, const DWindowContextConfig &config, HRESULT *returnCode );

#endif
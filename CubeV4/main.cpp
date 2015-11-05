#include <windows.h>

#include <SDL.h>
#include <SDL_events.h>
#include <SDL_syswm.h>

#include "DRenderContext.h"
#include "utility\DScopeGuard.h"
#include "DRenderResourceManager.h"
#include "DWindowRenderContext.h"

int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int )
{
	//DConfig config = {
	//	1024u, // width
	//	768u, // height
	//	false, // fullscreen
	//	3.1415926535f / 4.f, // fov
	//	0.01f, // nearZ
	//	100.0f, // farZ
	//	{ 1, 0 }, // sampler Desc
	//	NULL
	//};

	u16 windowWidth = 1024u;
	u16 windowHeight = 768u;

	SDL_Window *window = nullptr;

	if ( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
		return -1;

	auto sdlQuitGuard = DMakeScopeGuard( SDL_Quit );

	window = SDL_CreateWindow( "Cube",
							   0, 32,
							   windowWidth,
							   windowHeight,
							   SDL_WINDOW_SHOWN );

	if ( !window )
		return -1;

	auto windowDestroyGuard = DMakeScopeGuard( [&]() { SDL_DestroyWindow( window ); } );

	SDL_SysWMinfo info;
	DTools::ClearStruct( info );

	if ( SDL_GetWindowWMInfo( window, &info ) == SDL_FALSE )
	{
		return -1;
	}

	
	DWindowContextConfig windowContextConfig
	{
		info.info.win.window,
		{ 60u, 1u },
		windowWidth,
		windowHeight,
		true
	};

	HRESULT hr = S_OK;

	DRenderResourceManagerPtr manager = DCreateResourceManager( nullptr );

	if ( !manager )
		return -1;

	DWindowRenderContextPtr windowContext = DCreateWindowRenderContext( manager,
																		windowContextConfig,
																		&hr );

	if ( !windowContext )
		return -1;

	bool running = true;
	SDL_Event event;
	
	bool blFullscreen = false;

	while ( running )
	{
		while ( SDL_PollEvent( &event ) )
		{
			switch ( event.type )
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYDOWN:
				switch ( event.key.keysym.sym )
				{
				case SDLK_ESCAPE:
					running = false;
					break;
				case SDLK_F11:
				{
					blFullscreen = !blFullscreen;
					windowContext->SetFullscreenState( blFullscreen );
				}
				}
				break;
			}
		}
		f32 color[ 4 ] = { 0.0f, 1.0f, 0.0f, 1.0f };
		windowContext->FillCurrentTargetView( color );
		windowContext->Present();
	}

	windowContext = nullptr;
	manager = nullptr;

	return 0;
}
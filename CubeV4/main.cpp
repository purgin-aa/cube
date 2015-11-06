#include "Precompiled.h"
#include "DRenderContext.h"
#include "Utility/DScopeGuard.h"
#include "DRenderResourceManager.h"
#include "DWindowRenderContext.h"

//
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	const u16 windowWidth = 1600u;
	const u16 windowHeight = 900u;

	SDL_Window* window = nullptr;

	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 )
		return -1;

	auto sdlQuitGuard = DMakeScopeGuard( SDL_Quit );

	window = SDL_CreateWindow( 
		"Cube", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		windowWidth, windowHeight, 
		SDL_WINDOW_SHOWN );
	if( !window )
		return -1;

	auto windowDestroyGuard = DMakeScopeGuard( [&]() { 
		SDL_DestroyWindow( window ); 
	} );

	SDL_SysWMinfo info;
	DTools::MemZero( info );
	if( SDL_GetWindowWMInfo( window, &info ) == SDL_FALSE ) {
		return -1;
	}

	DWindowContextConfig windowContextConfig {
		info.info.win.window, // window desc
		{ 60u, 1u }, // rate 60/1
		windowWidth, // backbuffer width
		windowHeight, // backbuffer height
		false // fullscreen?
	};

	DRenderResourceManagerPtr manager = DRenderResourceManager::Create( nullptr );
	if( !manager )
		return -1;

	HRESULT hr = S_OK;
	DWindowRenderContextPtr windowContext = DWindowRenderContext::Create( manager, windowContextConfig, &hr );
	if( !windowContext )
		return -1;

	bool running = true;
	SDL_Event event;

	bool fullscreen = false;

	while( running ) {
		while( SDL_PollEvent( &event ) ) {
			switch( event.type ) {
				case SDL_QUIT: {
					running = false;
					break;
				}

				case SDL_KEYDOWN: {
					switch( event.key.keysym.sym ) {
						case SDLK_ESCAPE:
							running = false;
							break;
						case SDLK_F11: {
							fullscreen = !fullscreen;
							windowContext->SetFullscreenState( fullscreen );
							break;
						}
					}
					break;
				}
			}
		}
		const f32 color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
		windowContext->FillCurrentTargetView( color );
		windowContext->Present();
	}

	windowContext = nullptr;
	manager = nullptr;

	return 0;
}

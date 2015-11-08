#include "Precompiled.h"
#include "DRenderContext.h"
#include "Utility/DScopeGuard.h"
#include "DRenderResourceManager.h"
#include "DWindowRenderContext.h"
#include "DRender.h"
#include "DColoredCube.h"
#include "DTexturedCube.h"
#include "DSimpleTexture.h"

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

	DRenderPtr render = DRender::Create( windowContext.Get(), &hr );
	if( !render )
		return -1;

	DRenderPerspectiveModeDesc perspectiveDesc = {
		3.1415926535f / 4.f,
		0.01f,
		100.0f
	};
	
	DID3D11SamplerStatePtr sampler = manager->CreateSampler( &hr );

	if( !sampler )
		return -1;

	windowContext->SetSamplers( 0, sampler.Get() );

	render->SetPerspectiveProjectionMode( perspectiveDesc );
	XMVECTOR Eye = { 0.0f, 4.0f, -10.0f, 0.0f };
	XMVECTOR At =  { 0.0f, 1.0f,   0.0f, 0.0f };
	XMVECTOR Up =  { 0.0f, 1.0f,   0.0f, 0.0f };
	XMMATRIX view = XMMatrixLookAtLH( Eye, At, Up );

	render->SetViewMatrix( view );

	const u16 textureWidth = 256u;
	const u16 textureHeight = 256u;
	DPixelColor *pixels = new DPixelColor[ textureWidth * textureHeight ];
	DGenerateTexture( pixels, textureWidth, textureHeight );

	DSimpleMeshPtr texturedCube =
		DCreateTexturedCube(
			manager,
			pixels,
			textureWidth,
			textureHeight,
			&hr );

	delete[] pixels;

	if( !texturedCube )
		return -1;

	/*DSimpleMeshPtr coloredCube = DCreateColoredCube( manager, { 1.0f, 1.0f, 1.0f, 1.0f }, &hr );
	if( !coloredCube )
		return -1;*/

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
		const XMFLOAT4 color = { 0.0f, 0.0f, 0.0f, 1.0f };
		render->FillBackground( color );
		//render->DrawMesh( coloredCube.Get() );
		render->DrawMesh( texturedCube.Get() );
		windowContext->Present();
	}

	windowContext = nullptr;
	manager = nullptr;

	return 0;
}

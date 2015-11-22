#include "Precompiled.h"
#include "DRenderContext.h"
#include "Utility/DScopeGuard.h"
#include "DRenderResourceManager.h"
#include "DWindowRenderContext.h"
#include "DRender.h"
#include "DColoredCube.h"
#include "DTexturedCube.h"
#include "DSimpleTexture.h"
#include "DSphericalCamera.h"
#include "DLog.h"
#include "DConsoleOutput.h"


//
void InitLog() {
	DIOSys::OutputConsole *console = new DIOSys::OutputConsole( INVALID_HANDLE_VALUE, true );
	DLog::SetDebugOutputDevice( console );
	DLog::SetErrorOutputDevice( console );
	DLog::SetInfoOutputDevice( console );
	DLog::SetWarningOutputDevice( console );
}


//		
int WINAPI WinMain( HINSTANCE, HINSTANCE, LPSTR, int ) {
	InitLog();
	DLog::Info( "DSimpleDx11 application\n" );
	auto pauseGuard = DMakeScopeGuard( [&]() {
		std::system( "pause" );
	} );

	const u32 windowWidth = 1600;
	const u32 windowHeight = 900;
	const DXGI_RATIONAL refreshRate = { 
		60, 
		1 
	};

	SDL_Window* window = nullptr;

	if( SDL_Init( SDL_INIT_EVERYTHING ) != 0 ) {
		DLog::Error( "Failed to init SDL: %s\n", SDL_GetError() );
		return -1;
	}
		
	auto sdlQuitGuard = DMakeScopeGuard( SDL_Quit );

	window = SDL_CreateWindow( 
		"Cube", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		windowWidth, windowHeight, 
		SDL_WINDOW_SHOWN );
	if( !window ) {
		DLog::Error( "Failed to create window: %s\n", SDL_GetError() );
		return -1;
	}

	auto windowDestroyGuard = DMakeScopeGuard( [&]() { 
		SDL_DestroyWindow( window ); 
	} );

	SDL_SysWMinfo info;
	DTools::MemZero( info );
	if( SDL_GetWindowWMInfo( window, &info ) == SDL_FALSE ) {
		DLog::Error( "Failed to get window's info: %s\n", SDL_GetError() );
		return -1;
	}

	DWindowContextConfig windowContextConfig {
		info.info.win.window, // window desc
		{ // display mode
			windowWidth, // backbuffer width
			windowHeight, // backbuffer height
			refreshRate
		}, // 
		false // fullscreen?
	};

	HRESULT hr = S_OK;
	DRenderResourceManagerPtr manager = DRenderResourceManager::Create( &hr );
	if( !manager ) {
		DLog::Error( "Failed to create resource manager: %lX\n", hr );
		return -1;
	}


	DWindowRenderContextPtr windowContext = DWindowRenderContext::Create( manager, windowContextConfig, &hr );
	if( !windowContext ) {
		DLog::Error( "Failed to create window's context: %lX\n", hr );
		return -1;
	}

	DRenderPtr render = DRender::Create( windowContext.Get(), &hr );
	if( !render ) {
		DLog::Error( "Failed to create render: %lX\n", hr );
		return -1;
	}

	// init sampler
	DID3D11SamplerStatePtr sampler = manager->CreateSampler( &hr );
	if( !sampler ) {
		DLog::Error( "Failed to create sampler: %lX\n", hr );
		return -1;
	}

	windowContext->SetSamplers( 0, sampler.Get() );

	// enable perspective mode
	DRenderPerspectiveModeDesc perspectiveDesc = {
		3.1415926535f / 4.f,
		0.01f,
		100.0f
	};
	render->SetPerspectiveProjectionMode( perspectiveDesc );

	// add camera
	DSphericalCamera camera = {
		0.0f,
		0.0f,
		{ 0.0f, 4.0f, -10.0f }
	};

	render->SetViewMatrix( camera.GetViewMatrix() );

	// create textured cube mesh
	const u32 textureWidth = 256;
	const u32 textureHeight = 256;
	DPixelColor* pixels = new DPixelColor[ textureWidth * textureHeight ];
	DGenerateTexture( pixels, textureWidth, textureHeight );

	DSimpleMeshPtr texturedCube = DCreateTexturedCube(
			manager,
			pixels,
			textureWidth,
			textureHeight,
			&hr );

	delete[] pixels;

	if( !texturedCube ) {
		DLog::Error( "Failed to create textured cube: %lX\n", hr );
		return -1;
	}

	// Enable relative mode for mouse
	SDL_SetRelativeMouseMode( SDL_TRUE );

	// player speed
	const f32 playerSpeed = 10.0f;

	// event states
	bool running = true;
	SDL_Event event;

	// fullscreen state
	bool fullscreen = false;

	// enable Timer
	u32 lastTime = SDL_GetTicks();

	while( running ) {
		u32 currentTime = SDL_GetTicks();
		f32 deltaTime = ( f32 )( currentTime - lastTime ) / 1000.f;
		lastTime = currentTime;

		// fast keyboard controll
		const u8 *keyState = SDL_GetKeyboardState( nullptr );
		
		if( keyState[ SDL_SCANCODE_W ] )
			camera.MoveInLocalCoords( 0.0f, 0.0f, playerSpeed*deltaTime );

		if( keyState[ SDL_SCANCODE_S ] )
			camera.MoveInLocalCoords( 0.0f, 0.0f, -playerSpeed*deltaTime );

		if( keyState[ SDL_SCANCODE_A ] )
			camera.MoveInLocalCoords( playerSpeed*deltaTime, 0.0f, 0.0f );

		if( keyState[ SDL_SCANCODE_D ] )
			camera.MoveInLocalCoords( -playerSpeed*deltaTime, 0.0f, 0.0f );

		if( keyState[ SDL_SCANCODE_SPACE ] )
			camera.MoveInLocalCoords( 0.0f, playerSpeed*deltaTime, 0.0f );
		
		if( keyState[ SDL_SCANCODE_LCTRL ] )
			camera.MoveInLocalCoords( 0.0f, -playerSpeed*deltaTime, 0.0f );

		// events
		while( SDL_PollEvent( &event ) ) {
			switch( event.type ) {
				case SDL_QUIT: {
					running = false;
					break;
				}
				case SDL_MOUSEMOTION: {
					//
					const f32 dlongitude = ( f32 )( event.motion.xrel ) * 2.0f / ( f32 )( windowWidth ); // todo
					const f32 dlatitude = -( f32 )( event.motion.yrel ) * 2.0f / ( f32 )( windowHeight ); // todo
					
					//
					camera.AddLongitude( dlongitude );
					camera.AddLatitude( dlatitude );
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

		if( camera.IsUpdated() )
			render->SetViewMatrix( camera.GetViewMatrix() );
		
		const XMFLOAT4 color = { 0.0f, 0.0f, 0.0f, 1.0f };
		render->FillBackground( color );
		render->DrawMesh( texturedCube.Get() );
		windowContext->Present();
	}

	windowContext = nullptr;
	manager = nullptr;



	return 0;
}

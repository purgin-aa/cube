#include "Precompiled.h"
#include "DDirect3DTools.h"


//
DID3DBlobPtr DCompileShaderFromSourceBlob( DID3DBlobPtr sourceBlob, const char* entryPoint, const char* target, HRESULT* returnCode ) {
	assert( sourceBlob );
	assert( target );
	// if entry point is null - entry point is "main"

	DID3DBlobPtr shaderBlob;
	DID3DBlobPtr errorBlob;

	u32 compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
	compileFlags |= D3DCOMPILE_DEBUG;
#endif

	HRESULT hr = D3DCompile(
		sourceBlob->GetBufferPointer(),
		sourceBlob->GetBufferSize(),
		nullptr,
		nullptr,
		nullptr,
		entryPoint,
		target,
		compileFlags,
		0,
		&shaderBlob,
		&errorBlob );

	if( FAILED( hr ) ) {
		if( errorBlob ) {
			DLog::Error( "Shader compile error: %s\n", errorBlob->GetBufferPointer() );
		}

		if( returnCode )
			*returnCode = hr;

		return nullptr;
	}

	return shaderBlob;
}


//
bool DCheckDisplayMode( IDXGIAdapter2* adapter, u32 width, u32 height, DXGI_RATIONAL refreshRate, HRESULT* returnCode ) {
#define LM_CHECKRESULT( code, pcode, r ) if ( FAILED( code ) ) { if ( pcode ) *pcode = code; return r; }
	assert( adapter );

	// get output
	DIntrusivePtr<IDXGIOutput> output;
	HRESULT hr = adapter->EnumOutputs( 0, &output );
	LM_CHECKRESULT( hr, returnCode, false );

	const u32 MaxModes = 128;
	u32 numModes = 0;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// get numModes
	hr = output->GetDisplayModeList( format, 0, &numModes, nullptr );
	LM_CHECKRESULT( hr, returnCode, false );
	if( numModes > MaxModes )
		numModes = MaxModes;
	DXGI_MODE_DESC displayModes[ MaxModes ];

	// get mode descs
	output->GetDisplayModeList( format, 0, &numModes, displayModes );

	DXGI_MODE_DESC* current = displayModes;
	DXGI_MODE_DESC* end = displayModes + numModes;

	while( current != end ) {
		DLog::Info(
			"Display mode: %ux%u; Rate:{%u/%u}\n",
			current->Width, current->Height,
			current->RefreshRate.Numerator,
			current->RefreshRate.Denominator );
		++current;
	}
	current = displayModes;

	//
	// WARNING: this check is plain wrong, we can't compare float numbers reliably
	// but this is better than the original check which didn't work on my system at all
	//
	// better don't deal with refresh rates at all
	//
	const f32 TargetRate = refreshRate.Numerator / ( f32 ) refreshRate.Denominator;
	while( current != end ) {
		if( current->Width == width && current->Height == height ) {
			const f32 rate = current->RefreshRate.Numerator / ( f32 ) current->RefreshRate.Denominator;
			if( rate == TargetRate )
				break;
		}

		++current;
	}

	return current != end;
#undef LM_CHECKRESULT
}

bool DGetDisplayModeList( IDXGIAdapter2 *adapter, DBuffer **ppBuffer, HRESULT *returnCode ) {
#define LM_CHECKRESULT( code, pcode, r ) if ( FAILED( code ) ) { if ( pcode ) *pcode = code; return r; }
	assert( adapter );
	assert( ppBuffer );

	// get output
	DIntrusivePtr<IDXGIOutput> output;
	HRESULT hr = adapter->EnumOutputs( 0, &output );
	LM_CHECKRESULT( hr, returnCode, false );

	u32 numModes = 0;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// get numModes
	hr = output->GetDisplayModeList( format, 0, &numModes, nullptr );
	LM_CHECKRESULT( hr, returnCode, false );

	//
	DIntrusivePtr<DBuffer> modeBuffer( new DBuffer( numModes * sizeof( DXGI_MODE_DESC ), nullptr ) );

	//
	DXGI_MODE_DESC *displayModes = nullptr;
	modeBuffer->Lock( ( void ** ) &displayModes );
	auto modeBufferUnlockGuard = DBuffer::UnlockGuard( modeBuffer.Get() );

	//
	hr = output->GetDisplayModeList( format, 0, &numModes, displayModes );
	LM_CHECKRESULT( hr, returnCode, false );

	//
	modeBuffer->AddRef();
	*ppBuffer = modeBuffer.Get();
	return true;
#undef LM_CHECKRESULT
}

//
bool DCheckDisplayMode( IDXGIAdapter2 *adapter, const DDisplayMode *expectedMode, DDisplayMode *supportedMode, HRESULT *returnCode ) {
	assert( adapter );
	assert( expectedMode );
	assert( ( expectedMode->width ) > 0 && ( expectedMode->height > 0 ) );
	assert( expectedMode->refreshRate.Denominator != 0 );

	//
	DIntrusivePtr<DBuffer> modeBuffer;
	if( !DGetDisplayModeList(
		adapter,
		&modeBuffer,
		returnCode ) ) {
		DLog::Error( "Failed to get display mode list\n" );
		return false;
	}

	//
	DXGI_MODE_DESC *displayModes = nullptr;
	modeBuffer->Lock( ( void** ) &displayModes );
	u32 numModes = modeBuffer->GetBufferSize() / sizeof( DXGI_MODE_DESC );
	auto unlockGuard = DBuffer::UnlockGuard( modeBuffer.Get() );

	//
	const f32 expectedRate = ( f32 ) expectedMode->refreshRate.Numerator / ( f32 ) expectedMode->refreshRate.Denominator;
	DXGI_MODE_DESC *current = displayModes;
	DXGI_MODE_DESC *end = displayModes + numModes;

#if defined( DEBUG ) || defined( _DEBUG )
	while( current != end ) {
		DLog::Debug(
			"Display mode: %ux%u; Rate:{%u/%u}\n",
			current->Width, current->Height,
			current->RefreshRate.Numerator,
			current->RefreshRate.Denominator );
		++current;
	}
	current = displayModes;
#endif

	// todo width and height
	while( current != end ) {
		if( current->Width == expectedMode->width && current->Height == expectedMode->height ) {
			const f32 modeRate = ( f32 ) current->RefreshRate.Numerator / ( f32 ) current->RefreshRate.Denominator;
			if( fabs( modeRate - expectedRate ) < FLT_EPSILON )
				break;
		}
		++current;
	}

	if( current != end ) {
#if defined( DEBUG ) || defined( _DEBUG )
		DLog::Debug(
			"Selected mode: %ux%u; Rate:{%u/%u}\n",
			current->Width, current->Height,
			current->RefreshRate.Numerator,
			current->RefreshRate.Denominator );
#endif
		if( supportedMode ) {
			supportedMode->width = current->Width;
			supportedMode->height = current->Height;
			supportedMode->refreshRate = current->RefreshRate;
		}
		return true;
	}
	else
		return false;
}

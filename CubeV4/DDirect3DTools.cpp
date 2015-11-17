#include "Precompiled.h"
#include "DDirect3DTools.h"

DID3DBlobPtr DCompileShaderFromSourceBlob( DID3DBlobPtr sourceBlob, const char * entryPoint, const char * target, HRESULT * returnCode ) {
	assert( sourceBlob );
	assert( target );
	// if entry point is null - entry point is "main"

	DID3DBlobPtr shaderBlob;
	DID3DBlobPtr errorBlob;

	UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;

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

	if( FAILED( hr ) )
	{
		if( errorBlob )
		{
			DLog::Error( "Shader compile error: %s\n", errorBlob->GetBufferPointer() );
		}

		if( returnCode )
			*returnCode = hr;

		return nullptr;
	}

	return shaderBlob;
}

//
bool DCheckDisplayMode( IDXGIAdapter2 * adapter, u16 width, u16 height, DXGI_RATIONAL refreshRate, HRESULT * returnCode ) {
#define LM_CHECKRESULT( code, pcode, r ) if ( FAILED( code ) ) { if ( pcode ) *pcode = code; return r; }
	assert( adapter );

	HRESULT hr = S_OK;

	// Get output
	DIntrusivePtr<IDXGIOutput> output;
	hr = adapter->EnumOutputs( 0, &output );

	LM_CHECKRESULT( hr, returnCode, false );

	UINT numModes = 0;
	DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;

	// Get numModes
	hr = output->GetDisplayModeList(
		format,
		0,
		&numModes,
		nullptr );

	LM_CHECKRESULT( hr, returnCode, false );

	DXGI_MODE_DESC *displayModes = new DXGI_MODE_DESC[ numModes ];

	// get mode descs
	output->GetDisplayModeList(
		format,
		0,
		&numModes,
		displayModes );

	DXGI_MODE_DESC *current = displayModes;
	DXGI_MODE_DESC *end = displayModes + numModes;

	while( current != end ) {
		DLog::Info( 
			"Display mode: %ux%u; Rate:{%u/%u}\n", 
			current->Width, current->Height, 
			current->RefreshRate.Numerator, 
			current->RefreshRate.Denominator );
		++current;
	}
	current = displayModes;

	while( current != end )
	{
		if( ( current->Width == static_cast< UINT >( width ) ) &&
			( current->Height == static_cast< UINT >( height ) ) &&
			( current->RefreshRate.Numerator == refreshRate.Numerator ) &&
			( current->RefreshRate.Denominator == refreshRate.Denominator ) )
			break;
		else ++current;
	}

	delete[] displayModes;

	return ( current != end ) ? true : false;
#undef LM_CHECKRESULT
}

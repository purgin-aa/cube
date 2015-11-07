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
			// todo: write message to log
		}

		if( returnCode )
			*returnCode = hr;

		return nullptr;
	}

	return shaderBlob;
}

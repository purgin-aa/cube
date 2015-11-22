#pragma once

#include "Precompiled.h"
#include "DDirect3D11.h"
#include "DLog.h"
#include "DBuffer.h"

DID3DBlobPtr DCompileShaderFromSourceBlob( DID3DBlobPtr sourceBlob, const char *entryPoint, const char *target, HRESULT *returnCode );

//
struct DDisplayMode {
	u32 width;
	u32 height;
	DXGI_RATIONAL refreshRate;
};

//
[ [ deprecated( "DCheckDisplayMode will be removed in next commit" ) ] ]
bool DCheckDisplayMode( IDXGIAdapter2 *adapter, u32 width, u32 height, DXGI_RATIONAL refreshRate, HRESULT *returnCode );

//
bool DGetDisplayModeList( IDXGIAdapter2 *adapter, DBuffer **ppbuffer, HRESULT *returnCode );

//
bool DStrongCheckDisplayMode( IDXGIAdapter2 *adapter, const DDisplayMode *expectedMode, DDisplayMode *supportedMode, HRESULT *returnCode );

//
bool DWeakCheckDisplayMode( IDXGIAdapter2 *adapter, const DDisplayMode *expectedMode, DDisplayMode *supportedMode, HRESULT *returnCode );

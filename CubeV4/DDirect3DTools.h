#pragma once

#include "Precompiled.h"
#include "DDirect3D11.h"
#include "DLog.h"

DID3DBlobPtr DCompileShaderFromSourceBlob( DID3DBlobPtr sourceBlob, const char *entryPoint, const char *target, HRESULT *returnCode );

//
bool DCheckDisplayMode( IDXGIAdapter2 *adapter, u32 width, u32 height, DXGI_RATIONAL refreshRate, HRESULT *returnCode );

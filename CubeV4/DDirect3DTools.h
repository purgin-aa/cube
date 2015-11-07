#pragma once

#include "Precompiled.h"
#include "DDirect3D11.h"

DID3DBlobPtr DCompileShaderFromSourceBlob( DID3DBlobPtr sourceBlob, const char *entryPoint, const char *target, HRESULT *returnCode );
#pragma once

#include <d3d11.h>
#include <dxgi1_2.h>

#include <d3dcompiler.h>
#include "DIntrusivePtr.h"

using DID3D11DevicePtr = DIntrusivePtr< ID3D11Device >;
using DID3D11DeviceContextPtr = DIntrusivePtr< ID3D11DeviceContext >;
using DID3D11DebugPtr = DIntrusivePtr< ID3D11Debug >;

using DID3D11RenderTargetViewPtr = DIntrusivePtr< ID3D11RenderTargetView >;
using DID3D11SamplerStatePtr = DIntrusivePtr< ID3D11SamplerState >;

using DID3D11VertexShaderPtr = DIntrusivePtr< ID3D11VertexShader >;
using DID3D11PixelShaderPtr = DIntrusivePtr< ID3D11PixelShader >;
using DID3D11BufferPtr = DIntrusivePtr< ID3D11Buffer >;
using DID3DBlobPtr = DIntrusivePtr< ID3DBlob >;
using DID3D11Texture2DPtr = DIntrusivePtr< ID3D11Texture2D >;

// DXGI
// SwapChain
using DIDXGISwapChainPtr = DIntrusivePtr< IDXGISwapChain >;
using DIDXGISwapChain1Ptr = DIntrusivePtr< IDXGISwapChain1 >;
// Factory
using DIDXGIFactoryPtr = DIntrusivePtr< IDXGIFactory >;
using DIDXGIFactory2Ptr = DIntrusivePtr< IDXGIFactory2 >;
// Adapater
using DIDXGIAdapter2Ptr = DIntrusivePtr< IDXGIAdapter2 >;
// Device
using DIDXGIDevice2Ptr = DIntrusivePtr< IDXGIDevice2 >;

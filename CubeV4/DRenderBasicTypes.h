#pragma once
#include <d3d11.h>
#include <dxgi1_2.h>

#include <d3dcompiler.h>
#include "DIntrusivePtr.h"

typedef DIntrusivePtr<ID3D11Device> DID3D11DevicePtr;
typedef DIntrusivePtr<ID3D11DeviceContext> DID3D11DeviceContextPtr;
typedef DIntrusivePtr<ID3D11Debug> DID3D11DebugPtr;

typedef DIntrusivePtr<ID3D11RenderTargetView> DID3D11RenderTargetViewPtr;
typedef DIntrusivePtr<ID3D11SamplerState> DID3D11SamplerStatePtr;

typedef DIntrusivePtr<ID3D11VertexShader> DID3D11VertexShaderPtr;
typedef DIntrusivePtr<ID3D11PixelShader> DID3D11PixelShaderPtr;
typedef DIntrusivePtr<ID3D11Buffer> DID3D11BufferPtr;
typedef DIntrusivePtr<ID3DBlob> DID3DBlobPtr;
typedef DIntrusivePtr<ID3D11Texture2D> DID3D11Texture2DPtr;

typedef DIntrusivePtr<IDXGISwapChain> DIDXGISwapChainPtr;
typedef DIntrusivePtr<IDXGISwapChain1> DIDXGISwapChain1Ptr;

typedef DIntrusivePtr<IDXGIFactory> DIDXGIFactoryPtr;
typedef DIntrusivePtr<IDXGIFactory2> DIDXGIFactory2Ptr;

typedef DIntrusivePtr<IDXGIAdapter2> DIDXGIAdapter2Ptr;

typedef DIntrusivePtr<IDXGIDevice2> DIDXGIDevice2Ptr;


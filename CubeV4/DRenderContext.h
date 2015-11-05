#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

#include "DRenderBasicTypes.h"
#include "DRenderResourceManager.h"

#include "DTools.h"

using namespace DirectX;

struct DRenderWVMatrices
{
	XMMATRIX world;
	XMMATRIX view;
};

struct DRenderPerspectiveModeDesc
{
	f32 fov;
	f32 nearZ;
	f32 farZ;
};

struct DRenderTargetSize
{
	u16 width;
	u16 height;
};

class DRenderContext
	: public DSharedObject
{
public:
	// projection mode
	//void SetPerspectiveMode( const DRenderPerspectiveModeDesc &perspectiveModeDesc );
	void SetWVMatrices( const DRenderWVMatrices &stateMatrices );

	// shaders
	void SetVertexShader( DID3D11VertexShaderPtr vertexShader );
	void SetPixelShader( DID3D11PixelShaderPtr pixelShader );

	//
	void SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY topology );

	void DrawIndexed( u32 indexCount, u32 startIndexLocation, u32 startVertexLocation );
	void FillCurrentTargetView( f32 color[ 4 ] );

	void SetRenderTargetView( DID3D11RenderTargetViewPtr renderTarget, const DRenderTargetSize &size );

	DID3D11DeviceContextPtr GetDeviceContext( void ) const;

protected:

	DRenderResourceManagerPtr m_manager;

	DID3D11DeviceContextPtr m_deviceContext;
	DID3D11RenderTargetViewPtr m_renderTarget;

	DRenderTargetSize m_renderTargetSize;

	explicit DRenderContext( DRenderResourceManagerPtr manager );
};

//
//#include <windows.h>
//
//// D3D11
//#include <d3d11.h>
//#include <d3dcompiler.h>
//#include <DirectXMath.h>
//
//#include "DTools.h"
//
//#include "DIntrusivePtr.h"
//#include "DSharedObject.h"
//#include "DFactoryChild.h"
//
//using namespace DirectX;
//
//struct DConfig
//{
//	u16 width;
//	u16 height;
//	bool blFullscreen;
//
//	// projection
//	f32 fovAngle;
//	f32 nearZ;
//	f32 farZ;
//
//	DXGI_SAMPLE_DESC sampleDesc;
//	HWND window;
//};
//
//typedef DIntrusivePtr<ID3D11Device> DID3D11DevicePtr;
//typedef DIntrusivePtr<ID3D11DeviceContext> DID3D11DeviceContextPtr;
//typedef DIntrusivePtr<IDXGISwapChain> DIDXGISwapChainPtr;
//typedef DIntrusivePtr<ID3D11RenderTargetView> DID3D11RenderTargetViewPtr;
//typedef DIntrusivePtr<ID3D11SamplerState> DID3D11SamplerStatePtr;
//
//
//typedef DIntrusivePtr<ID3D11VertexShader> DID3D11VertexShaderPtr;
//typedef DIntrusivePtr<ID3D11PixelShader> DID3D11PixelShaderPtr;
//typedef DIntrusivePtr<ID3D11Buffer> DID3D11BufferPtr;
//typedef DIntrusivePtr<ID3DBlob> DID3DBlobPtr;
//typedef DIntrusivePtr<ID3D11Texture2D> DID3D11Texture2DPtr;
//
//class DRenderContext;
//class DRenderObjectFactory;
//class DVertexBufferView;
//class DIndexBufferView;
//
//typedef DIntrusivePtr<DRenderContext> DRenderContextPtr;
//typedef DIntrusivePtr<DRenderObjectFactory> DRenderObjectFactoryPtr;
//typedef DIntrusivePtr<DVertexBufferView> DVertexBufferViewPtr;
//typedef DIntrusivePtr<DIndexBufferView> DIndexBufferViewPtr;
//
//class DRenderContext
//	: public DSharedObject
//{
//public:
//	struct DWorldViewMatrices
//	{
//		XMMATRIX world;
//		XMMATRIX view;
//	};
//
//	void SetFullscreenState( bool blFullscreen );
//	void SetPerspectiveMode( void );
//	
//	void SetVertexShader( DID3D11VertexShaderPtr vertexShader );
//	void SetPixelShader( DID3D11PixelShaderPtr pixelShader );
//
//	DID3D11DevicePtr GetDevice( void );
//	DID3D11DeviceContextPtr GetDeviceContext( void );
//	
//	void Present( void );
//	void ClearCurrentTargetView( f32 color[ 4 ] );
//	void SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY topology );
//	void SetStateMatrices( const DWorldViewMatrices &stateMatrices );
//	void DrawIndexed( u32 indexCount, u32 startIndexLocation, u32 startVertexLocation );
//
//	DRenderObjectFactoryPtr GetRenderObjectFactory( void ) const;
//
//protected:
//	friend DRenderContextPtr CreateRenderContext( const DConfig &config, HRESULT *returnCode );
//
//	struct StateMatrices
//	{
//		XMMATRIX world;
//		XMMATRIX view;
//		XMMATRIX projection;
//	};
//
//	explicit DRenderContext( const DConfig &config,
//							 DID3D11DevicePtr device,
//							 DID3D11DeviceContextPtr deviceContext,
//							 DIDXGISwapChainPtr swapChain,
//							 DID3D11RenderTargetViewPtr backBufferView,
//							 DID3D11BufferPtr stateMatricesBuffer,
//							 DID3D11SamplerStatePtr samplerState,
//							 const StateMatrices &stateMatrices );
//
//private:
//
//	void UpdateStateMatrices( void );
//
//
//	
//	DConfig m_config;
//
//	DID3D11DevicePtr m_device;
//	DID3D11DeviceContextPtr m_deviceContext;
//	DIDXGISwapChainPtr m_swapChain;
//	DID3D11RenderTargetViewPtr m_renderTargetView;
//
//	DRenderObjectFactoryPtr m_objectFactory;
//
//	DID3D11SamplerStatePtr m_samplerState;
//	DID3D11BufferPtr m_stateMatricesBuffer;
//
//	StateMatrices m_stateMatrices;
//	bool m_updateStateMatrices;
//};
//
//DRenderContextPtr CreateRenderContext( const DConfig &config, HRESULT *returnCode );
//
//
//class DRenderObjectFactory
//	: public DSharedObject
//{
//public:
//	explicit DRenderObjectFactory( DRenderContextPtr context );
//
//	DID3D11BufferPtr CreateBuffer( u32 bufferSize, const void *bufferData, UINT bindFlags, HRESULT *returnCode );
//	DID3D11VertexShaderPtr CreateVertexShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT *returnCode );
//	DID3D11PixelShaderPtr CreatePixelShaderFromBlob( DID3DBlobPtr shaderBlob, HRESULT *returnCode );
//	DID3DBlobPtr CreateBlob( u32 blobSize, HRESULT *returnCode );
//
//	//DVertexBufferViewPtr CreateVertexBufferView( DID3D11BufferPtr vertexBuffer, u32 stride, u32 offset );
//	//DIndexBufferViewPtr CreateIndexBufferView( DID3D11BufferPtr indexBuffer, u32 offset, DXGI_FORMAT bufferFormat );
//
//	DRenderContextPtr GetContext( void );
//
//	//void ReleaseChild( DVertexBufferView *vertexBufferView );
//	//void ReleaseChild( DIndexBufferView *indexBufferView );
//
//private:
//	DRenderContextPtr m_context;
//
//};
//
//class DVertexBufferView
//	: public DFactoryChild<DRenderObjectFactory>
//{
//public:
//	explicit DVertexBufferView( DRenderObjectFactoryPtr factory,
//								DID3D11BufferPtr vertexBuffer,
//								u32 stride,
//								u32 offset )
//		: DFactoryChild( factory ), m_vertexBuffer( vertexBuffer ), m_stride( stride ), m_offset( offset )
//	{
//	}
//	~DVertexBufferView( void )
//	{
//	}
//
//	inline DID3D11BufferPtr GetVertexBuffer( void ) const
//	{
//		return m_vertexBuffer;
//	}
//
//	inline u32 GetStride( void ) const
//	{
//		return m_stride;
//	}
//
//	inline u32 GetOffset( void ) const
//	{
//		return m_offset;
//	}
//
//protected:
//	DID3D11BufferPtr m_vertexBuffer;
//	u32 m_stride;
//	u32 m_offset;
//};
//
//class DIndexBufferView
//	: public DFactoryChild<DRenderObjectFactory>
//{
//public:
//	explicit DIndexBufferView( DRenderObjectFactoryPtr factory,
//							   DID3D11BufferPtr indexBuffer,
//							   DXGI_FORMAT format,
//							   u32 offset )
//		: DFactoryChild( factory ), m_indexBuffer( indexBuffer ), m_format( format ), m_offset( offset )
//	{ }
//
//	inline DID3D11BufferPtr GetIndexBuffer( void ) const
//	{
//		return m_indexBuffer;
//	}
//
//	inline DXGI_FORMAT GetFormat( void ) const
//	{
//		return m_format;
//	}
//
//	inline u32 GetOffset( void ) const
//	{
//		return m_offset;
//	}
//
//private:
//	DID3D11BufferPtr m_indexBuffer;
//	DXGI_FORMAT m_format;
//	u32 m_offset;
//};
//
//

#pragma once

#include "Precompiled.h"
#include "DRenderContext.h"

using namespace DirectX;

//
class DRender;
using DRenderPtr = DIntrusivePtr< DRender >;

//
struct DRenderWVMatrices {
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
};


//
struct DRenderPerspectiveModeDesc {
	f32 fov;
	f32 nearZ;
	f32 farZ;
};

//
class DRender : public DSharedObject {
public:
	void				DrawMesh( DSimpleMesh *simpleMesh );
	void				FillBackground( const XMFLOAT4 color );
	void				SetViewMatrix( const XMMATRIX &matrix );
	void				SetWorldMatrix( const XMMATRIX &matrix );
	void				SetPerspectiveProjectionMode( const struct DRenderPerspectiveModeDesc &perspectiveDesc );

	static DRenderPtr	Create( DRenderContext *context, HRESULT *returnCode );

private:	
	void				SetMaterial( DMaterialController::DMaterial *material );
	void				SetMaterialController( DMaterialController *controller );
	void				SetVertexBufferView( DVertexBufferView *vertexBufferView );
	void				SetIndexBufferView( DIndexBufferView *indexBufferView );
	void				SetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY topology );

	void				InitMatrices();
	void				UpdateMatrices();

	struct WVPMatrices {
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	DRenderContextPtr			m_context;
	DID3D11BufferPtr			m_stateMatricesBuffer;

	bool						m_updateWVPMatrices;
	WVPMatrices					m_WVPMatrices;

	DMaterialControllerPtr		m_currentMaterialController;
	DMaterialPtr				m_currentMaterial;
	DVertexBufferViewPtr		m_currentVertexBufferView;
	DIndexBufferViewPtr			m_currentIndexBufferView;

	D3D_PRIMITIVE_TOPOLOGY		m_currentPrimitiveTopology;

	explicit DRender( DRenderContext *context, DID3D11BufferPtr wvpBuffer );
};
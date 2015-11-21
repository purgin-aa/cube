#include "Precompiled.h"
#include "DRender.h"

//
void DRender::DrawMesh( DSimpleMesh * simpleMesh ) {
	assert( simpleMesh );
	assert( m_context );

	UpdateMatrices();

	DMaterialController::DMaterial *material = nullptr;
	simpleMesh->GetMaterial( &material );
	assert( material );

	SetMaterial( material );

	auto vertexViewPtr = simpleMesh->GetVertices();
	assert( vertexViewPtr );
	auto indexViewPtr = simpleMesh->GetIndices();
	assert( indexViewPtr );

	SetVertexBufferView( vertexViewPtr.Get() );
	SetIndexBufferView( indexViewPtr.Get() );

	SetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	m_context->DrawIndexed(
		simpleMesh->GetIndexCount(),
		simpleMesh->GetStartIndexLocation(),
		simpleMesh->GetStartVertexLocation()
		);
}

//
void DRender::FillBackground( const XMFLOAT4 color ) {
	assert( m_context );
	m_context->FillCurrentTargetView( reinterpret_cast<const f32 *>( &color ) );
}

//
void DRender::SetViewMatrix( const XMMATRIX & matrix ) {
	m_WVPMatrices.view = XMMatrixTranspose( matrix );
	m_updateWVPMatrices = true;
}

//
void DRender::SetWorldMatrix( const XMMATRIX & matrix ) {
	m_WVPMatrices.world = XMMatrixTranspose( matrix );
	m_updateWVPMatrices = true;
}

//
void DRender::SetPerspectiveProjectionMode( const struct DRenderPerspectiveModeDesc & perspectiveDesc ) {
	assert( m_context );
	// check perspective
	assert( ( perspectiveDesc.fov   > 0.f ) && 
			( perspectiveDesc.nearZ > 0.f ) && 
			( perspectiveDesc.farZ  > 0.f ) );
	
	const DRenderTargetSize &targetSize = m_context->GetRenderTargetSize();
	
	assert( ( targetSize.width > 0 ) && ( targetSize.height > 0 ) );

	const f32 aspectRatio = static_cast< f32 >( targetSize.width ) / static_cast< f32 >( targetSize.height );
	
	m_WVPMatrices.projection = 
		XMMatrixTranspose( 
			XMMatrixPerspectiveFovLH( 
				perspectiveDesc.fov, 
				aspectRatio, 
				perspectiveDesc.nearZ, 
				perspectiveDesc.farZ ) 
			);

	m_updateWVPMatrices = true;
}

DRenderPtr DRender::Create( DRenderContext * context, HRESULT * returnCode ) {
	assert( context );

	auto manager = context->GetResourceManager();
	assert( manager );

	WVPMatrices matrices = {
		XMMatrixTranspose( XMMatrixIdentity() ),
		XMMatrixTranspose( XMMatrixIdentity() ),
		XMMatrixTranspose( XMMatrixIdentity() ),
	};

	auto constantWVPBuffer =
		manager->CreateBuffer(
			sizeof( WVPMatrices ),
			&matrices,
			D3D11_BIND_CONSTANT_BUFFER,
			returnCode );

	if( !constantWVPBuffer )
		return nullptr;

	
	DRenderPtr render( new DRender( context, constantWVPBuffer ) );
	return render;
}

//
void DRender::SetMaterial( DMaterialController::DMaterial * material ) {
	assert( material );
	assert( m_context );

	if( m_currentMaterial.Get() == material )
		return; // do nothing

	DMaterialController *controller = nullptr;
	material->GetMaterialController( &controller );
	assert( controller );

	SetMaterialController( controller );
	controller->BindMaterial( m_context.Get(), material );

	m_currentMaterial = material;
}

//
void DRender::SetMaterialController( DMaterialController * controller ) {
	assert( controller );
	assert( m_context );
	
	if( m_currentMaterialController.Get() == controller )
		return; // do nothing

	if( m_currentMaterialController )
		m_currentMaterialController->FreeContext( m_context.Get() );

	m_currentMaterialController = controller;

	m_currentMaterialController->PrepareContext( m_context.Get() );
}

//
void DRender::SetVertexBufferView( DVertexBufferView * vertexBufferView ) {
	assert( vertexBufferView );
	assert( m_context );

	if( m_currentVertexBufferView.Get() == vertexBufferView )
		return; // do nothing
	
	auto vertexBufferPtr = vertexBufferView->GetVertexBuffer();
	assert( vertexBufferPtr );

	m_context->SetVertexBuffer(
		0,
		vertexBufferPtr.Get(),
		vertexBufferView->GetStride(),
		vertexBufferView->GetOffset()
		);

	m_currentVertexBufferView = vertexBufferView;
}

//
void DRender::SetIndexBufferView( DIndexBufferView * indexBufferView ) {
	assert( indexBufferView );
	assert( m_context );

	if( m_currentIndexBufferView.Get() == indexBufferView )
		return; // do nothing


	auto indexBufferPtr = indexBufferView->GetIndexBuffer();
	assert( indexBufferPtr );

	m_context->SetIndexBuffer(
		indexBufferPtr.Get(),
		indexBufferView->GetIndexBufferFormat(),
		indexBufferView->GetIndexBufferOffset()
		);

	m_currentIndexBufferView = indexBufferView;
}

//
void DRender::SetPrimitiveTopology( D3D_PRIMITIVE_TOPOLOGY topology ) {
	assert( m_context );
	if( m_currentPrimitiveTopology == topology )
		return; // do nothing

	m_context->SetPrimitiveTopology( topology );
	m_currentPrimitiveTopology = topology;
}

//
void DRender::InitMatrices() {
	m_WVPMatrices = {
		XMMatrixTranspose( XMMatrixIdentity() ),
		XMMatrixTranspose( XMMatrixIdentity() ),
		XMMatrixTranspose( XMMatrixIdentity() )
	};
	m_updateWVPMatrices = true;
}

//
void DRender::UpdateMatrices() {
	assert( m_context );
	assert( m_stateMatricesBuffer );

	if( m_updateWVPMatrices )
	{
		auto deviceContext = m_context->GetDeviceContext();
		assert( deviceContext );

		deviceContext->UpdateSubresource(
			m_stateMatricesBuffer.Get(),
			0,
			nullptr,
			&m_WVPMatrices,
			0,
			0 );

		m_updateWVPMatrices = false;
	}
}

//
DRender::DRender( DRenderContext * context, DID3D11BufferPtr wvpBuffer )
	: m_context( context )
	, m_stateMatricesBuffer( wvpBuffer )
	, m_updateWVPMatrices( false )
	, m_WVPMatrices{ 
		XMMatrixTranspose( XMMatrixIdentity() ), 
		XMMatrixTranspose( XMMatrixIdentity() ), 
		XMMatrixTranspose( XMMatrixIdentity() ) }
{
	assert( wvpBuffer );

	m_context->SetVertexShaderConstantBuffer( 0, wvpBuffer.Get() );
}

#include "Precompiled.h"
#include "DRenderContext.h"

//
void DRenderContext::SetVertexShader( DID3D11VertexShaderPtr vertexShader ) {
	assert( m_deviceContext );
	m_deviceContext->VSSetShader( vertexShader.Get(), nullptr, 0 );
}


//
void DRenderContext::SetPixelShader( DID3D11PixelShaderPtr pixelShader ) {
	assert( m_deviceContext );
	m_deviceContext->PSSetShader( pixelShader.Get(), nullptr, 0 );
}


//
void DRenderContext::SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY topology ) {
	assert( m_deviceContext );
	m_deviceContext->IASetPrimitiveTopology( topology );
}


//
void DRenderContext::DrawIndexed( u32 indexCount, u32 startIndexLocation, u32 startVertexLocation ) {
	assert( m_deviceContext );
	m_deviceContext->DrawIndexed( indexCount, startIndexLocation, startVertexLocation );
}


//
void DRenderContext::FillCurrentTargetView( const f32 color[4] ) {
	assert( m_deviceContext );
	assert( m_renderTarget );
	m_deviceContext->ClearRenderTargetView( m_renderTarget.Get(), color );
}


//
void DRenderContext::SetRenderTargetView( DID3D11RenderTargetViewPtr renderTarget, const DRenderTargetSize & size ) {
	assert( m_deviceContext );
	assert( renderTarget );
	assert( ( size.width > 0u ) && ( size.height > 0u ) );

	m_renderTargetSize = size;
	m_renderTarget = renderTarget;
	m_deviceContext->OMSetRenderTargets( 0, &renderTarget, nullptr );
}


//
DID3D11DeviceContextPtr DRenderContext::GetDeviceContext() const {
	return m_deviceContext;
}


//
DRenderContext::DRenderContext( DRenderResourceManagerPtr manager )
	: m_manager( manager ) {
	assert( m_manager );
	m_deviceContext = manager->GetDeviceContext();
	assert( m_deviceContext );
	m_renderTargetSize = { 0u, 0u };
}

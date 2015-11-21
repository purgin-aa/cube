#include "Precompiled.h"
#include "DRenderContext.h"


//
void DRenderContext::SetVertexShader( ID3D11VertexShader* vertexShader ) {
	m_deviceContext->VSSetShader( vertexShader, nullptr, 0 );
}


//
void DRenderContext::SetPixelShader( ID3D11PixelShader* pixelShader ) {
	m_deviceContext->PSSetShader( pixelShader, nullptr, 0 );
}


//
void DRenderContext::SetInputLayout( ID3D11InputLayout* inputLayout ) {
	m_deviceContext->IASetInputLayout( inputLayout );
}


//
void DRenderContext::SetPixelShaderConstantBuffer( u32 slot, ID3D11Buffer* buffer ) {
	m_deviceContext->PSSetConstantBuffers( slot, 1, &buffer );
}


//
void DRenderContext::SetVertexShaderConstantBuffer( u32 slot, ID3D11Buffer* buffer ) {
	m_deviceContext->VSSetConstantBuffers( slot, 1, &buffer );
}


//
void DRenderContext::SetPixelShaderResourceView( u32 slot, ID3D11ShaderResourceView* resourceView ) {
	m_deviceContext->PSSetShaderResources( slot, 1, &resourceView );
}


//
void DRenderContext::SetVertexBuffer( u32 slot, ID3D11Buffer* vertexBuffer, u32 stride, u32 offset ) {
	assert( vertexBuffer );
	assert( stride );
	m_deviceContext->IASetVertexBuffers( slot, 1, &vertexBuffer, &stride, &offset );
}


//
void DRenderContext::SetIndexBuffer( ID3D11Buffer* indexBuffer, DXGI_FORMAT format, u32 offset ) {
	assert( indexBuffer );
	m_deviceContext->IASetIndexBuffer( indexBuffer, format, offset );
}


//
void DRenderContext::SetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY topology ) {
	m_deviceContext->IASetPrimitiveTopology( topology );
}


//
void DRenderContext::DrawIndexed( u32 indexCount, u32 startIndexLocation, u32 startVertexLocation ) {
	m_deviceContext->DrawIndexed( indexCount, startIndexLocation, startVertexLocation );
}


//
void DRenderContext::FillCurrentTargetView( const f32 color[4] ) {
	assert( m_renderTarget );
	m_deviceContext->ClearRenderTargetView( m_renderTarget.Get(), color );
}


//
void DRenderContext::SetRenderTargetView( DID3D11RenderTargetViewPtr renderTarget, const DRenderTargetSize& size ) {
	assert( renderTarget );
	assert( size.width > 0 && size.height > 0 );

	m_renderTargetSize = size;
	m_renderTarget = renderTarget;
	m_deviceContext->OMSetRenderTargets( 1, &renderTarget, nullptr );

	D3D11_VIEWPORT viewport;
	viewport.Width = static_cast< f32 >( size.width );
	viewport.Height = static_cast< f32 >( size.height );
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	m_deviceContext->RSSetViewports( 1, &viewport );
}


//
const DRenderTargetSize & DRenderContext::GetRenderTargetSize() const {
	return m_renderTargetSize;
}


//
void DRenderContext::SetSamplers( u32 slot, ID3D11SamplerState* sampler ) {
	m_deviceContext->PSSetSamplers( slot, 1, &sampler );
}


//
DID3D11DeviceContextPtr DRenderContext::GetDeviceContext() const {
	return m_deviceContext;
}


//
DRenderResourceManagerPtr DRenderContext::GetResourceManager() const {
	return m_manager;
}


//
DRenderContext::DRenderContext( DRenderResourceManagerPtr manager ) {
	assert( manager );
	m_manager = manager;
	m_deviceContext = manager->GetDeviceContext();
	assert( m_deviceContext );
	m_renderTargetSize = { 0, 0 };
}

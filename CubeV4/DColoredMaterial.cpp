#include "Precompiled.h"
#include "DColoredMaterial.h"

//
void DColoredMaterialController::PrepareContext( DRenderContext *context ) {
	assert( context );
	assert( m_vertexShader );
	assert( m_pixelShader );
	assert( m_inputLayout );

	context->SetVertexShader( m_vertexShader.Get() );
	context->SetPixelShader( m_pixelShader.Get() );
	context->SetInputLayout( m_inputLayout.Get() );
}

//
void DColoredMaterialController::FreeContext( DRenderContext *context ) {
	assert( context );

	context->SetVertexShader( nullptr );
	context->SetPixelShader( nullptr );
	context->SetInputLayout( nullptr );

	context->SetPixelShaderConstantBuffer( 0, nullptr );
}

//
void DColoredMaterialController::BindMaterial( DRenderContext *context, DMaterial *material ) {
	assert( context );
	assert( material );

	DColoredMaterial *coloredMaterial = static_cast< DColoredMaterial* >( material );
	assert( coloredMaterial->m_colorBuffer );

	context->SetPixelShaderConstantBuffer( 0, coloredMaterial->m_colorBuffer.Get() );
}

//
DIntrusivePtr<DColoredMaterialController::DColoredMaterial> DColoredMaterialController::CreateColoredMaterial( DRenderResourceManager *manager, const XMFLOAT4 color, HRESULT *returnCode ) {
	assert( manager );
	
	DID3D11BufferPtr constantBuffer = manager->CreateBuffer( sizeof( XMFLOAT4 ), &color, D3D11_BIND_CONSTANT_BUFFER, returnCode );

	if( !constantBuffer )
		return nullptr;

	return DIntrusivePtr<DColoredMaterial>( new DColoredMaterial( this, constantBuffer, color ) );
}

//
DColoredMaterialControllerPtr DColoredMaterialController::CreateColoredMaterialController( DRenderResourceManager * manager, HRESULT * returnCode ) {
	assert( manager );
	auto device = manager->GetDevice();
	assert( device );

	// load files
	// vertex shader
	auto vertexShaderSourceBlob = DCreateBlobFromFile( DVERTEX_SHADER_COLORED_FILE_PATH );
	if( !vertexShaderSourceBlob )
		return nullptr;

	// pixel shader
	auto pixelShaderSourceBlob = DCreateBlobFromFile( DPIXEL_SHADER_COLORED_FILE_PATH );
	if( !pixelShaderSourceBlob )
		return nullptr;

	// compile shaders
	// vertex shader
	auto vertexShaderBlob =
		DCompileShaderFromSourceBlob(
			vertexShaderSourceBlob,
			"main",
			"vs_4_0",
			returnCode );

	if( !vertexShaderBlob )
		return nullptr;

	// pixel shader
	auto pixelShaderBlob =
		DCompileShaderFromSourceBlob(
			pixelShaderSourceBlob,
			"main",
			"ps_4_0",
			returnCode );

	if( !pixelShaderBlob )
		return nullptr;

	HRESULT hr = S_OK;

	DID3D11VertexShaderPtr vertexShader;
	hr = device->CreateVertexShader(
		vertexShaderBlob->GetBufferPointer(),
		vertexShaderBlob->GetBufferSize(),
		nullptr,
		&vertexShader );

	if( FAILED( hr ) )
	{
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	DID3D11PixelShaderPtr pixelShader;
	hr = device->CreatePixelShader(
		pixelShaderBlob->GetBufferPointer(),
		pixelShaderBlob->GetBufferSize(),
		nullptr,
		&pixelShader );

	if( FAILED( hr ) )
	{
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	std::size_t numLayouts = DTools::StaticArraySize( layout );

	DID3D11InputLayoutPtr inputLayout;
	hr = device->CreateInputLayout(
		layout,
		static_cast< UINT >( numLayouts ),
		vertexShaderBlob->GetBufferPointer(),
		vertexShaderBlob->GetBufferSize(),
		&inputLayout );

	if( FAILED( hr ) )
	{
		if( returnCode )
			*returnCode = hr;
		return nullptr;
	}

	return DColoredMaterialControllerPtr( new DColoredMaterialController( vertexShader, pixelShader, inputLayout ) );
}

//
DColoredMaterialController::DColoredMaterialController( DID3D11VertexShaderPtr vertexShader, DID3D11PixelShaderPtr pixelShader, DID3D11InputLayoutPtr inputLayout ) 
	: m_vertexShader( vertexShader )
	, m_pixelShader( pixelShader )
	, m_inputLayout( inputLayout )
{
	assert( vertexShader );
	assert( pixelShader );
	assert( inputLayout );
}

//
DColoredMaterialController::DColoredMaterial::DColoredMaterial( DColoredMaterialController *controller, DID3D11BufferPtr buffer, const XMFLOAT4 color )
	: DMaterial( controller )
	, m_colorBuffer( buffer )
	, m_color( color ) {
	assert( controller );
	assert( buffer );
}

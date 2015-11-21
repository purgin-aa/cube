#include "Precompiled.h"
#include "DTexturedMaterial.h"


//
void DTexturedMaterialController::PrepareContext( DRenderContext *context ) {
	assert( context );

	context->SetVertexShader( m_vertexShader.Get() );
	context->SetPixelShader( m_pixelShader.Get() );
	context->SetInputLayout( m_inputLayout.Get() );
}


//
void DTexturedMaterialController::FreeContext( DRenderContext *context ) {
	assert( context );

	context->SetVertexShader( nullptr );
	context->SetPixelShader( nullptr );
	context->SetInputLayout( nullptr );

	context->SetPixelShaderResourceView( 0, nullptr );
}


//
void DTexturedMaterialController::BindMaterial( DRenderContext *context, DMaterial *material ) {
	assert( context );
	assert( material );

	DTexturedMaterial *texturedMaterial = static_cast< DTexturedMaterial * >( material );

	assert( texturedMaterial->m_textureView );

	context->SetPixelShaderResourceView( 
		0,
		texturedMaterial->m_textureView.Get() );
}


//
DIntrusivePtr<DTexturedMaterialController::DTexturedMaterial> DTexturedMaterialController::CreateTexturedMaterial( DRenderResourceManager * manager, const PixelColor *pixels, u16 width, u16 height, HRESULT *returnCode ) {
	assert( manager );
	assert( pixels );
	assert( width > 0 );
	assert( height > 0 );

	auto texture =
		manager->CreateTexture2D(
			pixels,
			width,
			height,
			returnCode );

	if( !texture )
		return nullptr;

	auto textureView =
		manager->CreateTexture2DView(
			texture.Get(),
			returnCode );

	if( !textureView )
		return nullptr;

	return DIntrusivePtr<DTexturedMaterialController::DTexturedMaterial>( new DTexturedMaterial( this, texture, textureView ) );
}


//
DTexturedMaterialControllerPtr DTexturedMaterialController::Create( DRenderResourceManager* manager, HRESULT* returnCode ) {
	assert( manager );

	// load files
	// vertex shader
	auto vertexShaderSourceBlob = DCreateBlobFromFile( DVERTEX_SHADER_TEXTURED_FILE_PATH );
	if( !vertexShaderSourceBlob )
		return nullptr;

	// pixel shader
	auto pixelShaderSourceBlob = DCreateBlobFromFile( DPIXEL_SHADER_TEXTURED_FILE_PATH );
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

	DID3D11VertexShaderPtr vertexShader = manager->CreateVertexShaderFromBlob( vertexShaderBlob, returnCode );

	if( !vertexShader )
		return nullptr;

	DID3D11PixelShaderPtr pixelShader = manager->CreatePixelShaderFromBlob( pixelShaderBlob, returnCode );

	if( !pixelShader )
		return nullptr;

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	0,					 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,		0,	sizeof( XMFLOAT3 ), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	std::size_t numLayouts = DTools::StaticArraySize( layout );

	DID3D11InputLayoutPtr inputLayout =
		manager->CreateInputLayoutFromVertexShaderBlob(
			vertexShaderBlob.Get(),
			layout,
			static_cast< u16 > ( numLayouts ),
			returnCode );

	if( !inputLayout )
		return nullptr;

	return DTexturedMaterialControllerPtr( new DTexturedMaterialController( vertexShader, pixelShader, inputLayout ) );
}


//
DTexturedMaterialController::DTexturedMaterialController( DID3D11VertexShaderPtr vertexShader, DID3D11PixelShaderPtr pixelShader, DID3D11InputLayoutPtr inputLayout ) 
	: m_vertexShader( vertexShader )
	, m_pixelShader( pixelShader )
	, m_inputLayout( inputLayout )
{
	assert( vertexShader );
	assert( pixelShader );
	assert( inputLayout );
}


//
DTexturedMaterialController::DTexturedMaterial::DTexturedMaterial( DTexturedMaterialController *controller, DID3D11Texture2DPtr texture, DID3D11ShaderResourceViewPtr textureView ) 
	: DMaterialController::DMaterial( controller )
	, m_texture( texture )
	, m_textureView( textureView )
{
	assert( controller );
	assert( texture );
	assert( textureView );
}

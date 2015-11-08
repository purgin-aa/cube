#pragma once

#include "Precompiled.h"

#include "DMaterialController.h"
#include "DRenderContext.h"
#include "DFileTools.h"
#include "DDirect3DTools.h"

using namespace DirectX;

//
class DTexturedMaterialController;
using DTexturedMaterialControllerPtr = DIntrusivePtr< DTexturedMaterialController >;

//
const char *const DVERTEX_SHADER_TEXTURED_FILE_PATH = "VertexShader.Textured.vs";
const char *const DPIXEL_SHADER_TEXTURED_FILE_PATH = "PixelShader.Textured.ps";

//
class DTexturedMaterialController : public DMaterialController {
public:
	struct Vertex {
		XMFLOAT3 pos;
		XMFLOAT2 uv;
	};

	using PixelColor = DPixelColor;

	//
	class DTexturedMaterial : public DMaterialController::DMaterial {
	public:

	protected:
		friend DTexturedMaterialController;

		explicit DTexturedMaterial( DTexturedMaterialController *controller, DID3D11Texture2DPtr texture, DID3D11ShaderResourceViewPtr textureView );

		DID3D11Texture2DPtr				m_texture;
		DID3D11ShaderResourceViewPtr	m_textureView;
	};

	// ������������ ����� DMaterialController
	virtual void							PrepareContext( DRenderContext *context ) override;
	virtual void							FreeContext( DRenderContext *context ) override;
	virtual void							BindMaterial( DRenderContext *context, DMaterial *material ) override;

	DIntrusivePtr<DTexturedMaterial>		CreateTexturedMaterial( DRenderResourceManager *manager, const PixelColor *pixels, u16 width, u16 height, HRESULT *returnCode );
	static DTexturedMaterialControllerPtr	Create( DRenderResourceManager *manager, HRESULT *returnCode );

private:
	DID3D11VertexShaderPtr		m_vertexShader;
	DID3D11PixelShaderPtr		m_pixelShader;
	DID3D11InputLayoutPtr		m_inputLayout;

	explicit DTexturedMaterialController( DID3D11VertexShaderPtr vertexShader, DID3D11PixelShaderPtr pixelShader, DID3D11InputLayoutPtr inputLayout );
};
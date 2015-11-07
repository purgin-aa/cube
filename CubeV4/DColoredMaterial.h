#pragma once

#include "DMaterialController.h"
#include "DRenderContext.h"
#include "DFileTools.h"
#include "DDirect3DTools.h"

using namespace DirectX;

class DColoredMaterialController;

using DColoredMaterialControllerPtr = DIntrusivePtr<DColoredMaterialController>;

const char *const DVERTEX_SHADER_COLORED_FILE_PATH = "VertexShader.Colored.vs";
const char *const DPIXEL_SHADER_COLORED_FILE_PATH = "PixelShader.Colored.ps";

//
class DColoredMaterialController : public DMaterialController {
public:
	struct Vertex {
		XMFLOAT3 pos;
	};

	class DColoredMaterial;

	virtual void							PrepareContext( DRenderContext *context ) override;
	virtual void							FreeContext( DRenderContext *context ) override;
	virtual void							BindMaterial( DRenderContext *context, DMaterial *material ) override;
	DIntrusivePtr<DColoredMaterial>			CreateColoredMaterial( DRenderResourceManager *manager, const XMFLOAT4 color, HRESULT *returnCode );
	static DColoredMaterialControllerPtr	CreateColoredMaterialController( DRenderResourceManager *manager, HRESULT *returnCode );

	//
	class DColoredMaterial : public DMaterialController::DMaterial {
	public:

	protected:
		explicit DColoredMaterial( DColoredMaterialController *controller, DID3D11BufferPtr buffer, const XMFLOAT4 color );

		friend DColoredMaterialController;

		DID3D11BufferPtr	m_colorBuffer;
		XMFLOAT4			m_color;

	}; // End DColoredMaterial

	
private:

	DID3D11VertexShaderPtr	m_vertexShader;
	DID3D11PixelShaderPtr	m_pixelShader;
	DID3D11InputLayoutPtr	m_inputLayout;

	explicit DColoredMaterialController( DID3D11VertexShaderPtr vertexShader, DID3D11PixelShaderPtr pixelShader, DID3D11InputLayoutPtr inputLayout );
};
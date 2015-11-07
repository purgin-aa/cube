#pragma once

#include "DDirect3D11.h"

#include "DSharedObject.h"
#include "DTools.h"

#include "DMaterialController.h"

class DRenderResourceManager;


class DVertexBufferView;
class DIndexBufferView;
class DSimpleMesh;

using DVertexBufferViewPtr = DIntrusivePtr< DVertexBufferView >;
using DIndexBufferViewPtr = DIntrusivePtr< DIndexBufferView >;
using DSimpleMeshPtr = DIntrusivePtr< DSimpleMesh >;


//
class DVertexBufferView : public DSharedObject {
public:
	//
	DID3D11BufferPtr	GetVertexBuffer() const;
	u32					GetStride() const;
	u32					GetOffset() const;

private:
	//
	DID3D11BufferPtr	m_vertexBuffer;
	u32					m_stride;
	u32					m_offset;

protected:
	//
	friend DRenderResourceManager;
	explicit DVertexBufferView( DID3D11BufferPtr buffer, u32 stride, u32 offset );
};


//
class DIndexBufferView : public DSharedObject {
public:
	//
	DID3D11BufferPtr	GetIndexBuffer() const;
	DXGI_FORMAT			GetIndexBufferFormat() const;
	u32					GetIndexBufferOffset() const;

private:
	//
	DID3D11BufferPtr	m_indexBuffer;
	DXGI_FORMAT			m_format;
	u32					m_offset;

protected:
	//
	friend DRenderResourceManager;
	explicit DIndexBufferView( DID3D11BufferPtr buffer, DXGI_FORMAT format, u32 offset );
};


//
class DSimpleMesh : public DSharedObject {
public:
	//
	DVertexBufferViewPtr		GetVertices() const;
	DIndexBufferViewPtr			GetIndices() const;
	u32							GetIndexCount() const;
	u32							GetStartVertexLocation() const;
	u32							GetStartIndexLocation() const;
	void						GetMaterial( DMaterialController::DMaterial **pMaterial ) const;
private:
	//
	DVertexBufferViewPtr		m_vertices;
	DIndexBufferViewPtr			m_indices;
	DMaterialPtr				m_material;
	u32							m_indexCount;
	u32							m_startVertexLocation;
	u32							m_startIndexLocation;

protected:
	//
	friend DRenderResourceManager;
	explicit DSimpleMesh( DVertexBufferView *vertices, DIndexBufferView *indices, DMaterialController::DMaterial *material, u32 indexCount, u32 startVertexLocation, u32 startIndexLocation );
};

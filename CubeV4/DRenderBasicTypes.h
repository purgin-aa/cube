#ifndef _RENDERBASISTYPES_H_
#define _RENDERBASISTYPES_H_

#include "DDirect3D11.h"

#include "DSharedObject.h"
#include "DTools.h"

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
	DID3D11BufferPtr GetVertexBuffer() const;
	u32 GetStride() const;
	u32 GetOffset() const;

private:
	//
	DID3D11BufferPtr m_vertexBuffer;
	u32 m_stride;
	u32 m_offset;

protected:
	//
	friend DRenderResourceManager;

	explicit DVertexBufferView( DID3D11BufferPtr buffer, u32 stride, u32 offset );
};


//
class DIndexBufferView : public DSharedObject {
public:
	//
	DID3D11BufferPtr GetIndexBuffer() const;
	DXGI_FORMAT GetIndexBufferFormat() const;
	u32 GetIndexBufferOffset() const;

private:
	//
	DID3D11BufferPtr m_indexBuffer;
	DXGI_FORMAT m_format;
	u32 m_offset;

protected:
	//
	friend DRenderResourceManager;

	explicit DIndexBufferView( DID3D11BufferPtr buffer, DXGI_FORMAT format, u32 offset );
};


class DSimpleMesh : DSharedObject {
public:
	//
	DVertexBufferViewPtr GetVertices() const;
	DIndexBufferViewPtr GetIndices() const;
	u32 GetIndexCount() const;

private:
	//
	DVertexBufferViewPtr m_vertices;
	DIndexBufferViewPtr m_indices;
	u32 m_indexCount;

protected:
	//
	friend DRenderResourceManager;

	explicit DSimpleMesh( DVertexBufferViewPtr vertices, DIndexBufferViewPtr indices, u32 indexCount );
};

#endif

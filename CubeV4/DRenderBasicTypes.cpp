#include "DRenderBasicTypes.h"


//
inline DID3D11BufferPtr DVertexBufferView::GetVertexBuffer() const {
	return m_vertexBuffer;
}


//
inline u32 DVertexBufferView::GetStride() const {
	return m_stride;
}


//
inline u32 DVertexBufferView::GetOffset() const {
	return m_offset;
}


//
DVertexBufferView::DVertexBufferView( DID3D11BufferPtr buffer, u32 stride, u32 offset ):
	m_vertexBuffer( buffer ),
	m_stride( stride ),
	m_offset( offset ) {
}


//
inline DID3D11BufferPtr DIndexBufferView::GetIndexBuffer() const {
	return m_indexBuffer;
}


//
inline DXGI_FORMAT DIndexBufferView::GetIndexBufferFormat() const {
	return m_format;
}


//
inline u32 DIndexBufferView::GetIndexBufferOffset() const {
	return m_offset;
}


//
inline DIndexBufferView::DIndexBufferView( DID3D11BufferPtr buffer, DXGI_FORMAT format, u32 offset ):
	m_indexBuffer( buffer ),
	m_format( format ),
	m_offset( offset ) {
}


//
inline DVertexBufferViewPtr DSimpleMesh::GetVertices() const {
	return m_vertices;
}


//
inline DIndexBufferViewPtr DSimpleMesh::GetIndices() const {
	return m_indices;
}


//
inline u32 DSimpleMesh::GetIndexCount() const {
	return m_indexCount;
}


//
inline DSimpleMesh::DSimpleMesh( DVertexBufferViewPtr vertices, DIndexBufferViewPtr indices, u32 indexCount ):
	m_vertices( vertices ),
	m_indices( indices ),
	m_indexCount( indexCount ) {
}

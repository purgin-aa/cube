#include "Precompiled.h"
#include "DBuffer.h"

//
DBuffer::DBuffer( u32 size, void *data ) 
	: m_data(nullptr)
	, m_size(size)
{
	if( size ) {
		m_data = malloc( size );
		if( data )
			memcpy( m_data, data, size );
	}
}

//
DBuffer::~DBuffer() {
	if( m_data ) {
		free( m_data );
	}
}

//
void DBuffer::Lock( void ** ppData ) {
	m_lockMutex.lock();
	*ppData = m_data;
}

//
void DBuffer::Unlock() {
	m_lockMutex.unlock();
}

//
u32 DBuffer::GetBufferSize() const {
	return m_size;
}

//
DBuffer::UnlockGuard::UnlockGuard( DBuffer *buffer ) 
	: m_buffer( buffer ){
}

//
DBuffer::UnlockGuard::~UnlockGuard() {
	if ( m_buffer ) 
		m_buffer->Unlock();
}

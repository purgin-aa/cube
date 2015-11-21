#pragma once

#include "Precompiled.h"
#include "DSharedObject.h"
#include <mutex>


// simple buffer class
// todo: add a various allocator support
class DBuffer : public DSharedObject {
public:
	DBuffer( u32 size, void *data );
	~DBuffer();

	//void	Resize( bool copy );
	void	Lock( void **ppData );
	void	Unlock();
	u32		GetBufferSize() const;

	//
	class UnlockGuard {
	public:
		UnlockGuard( DBuffer *buffer );
		~UnlockGuard();
	private:
		DBuffer *m_buffer;
	};

private:
	void*		m_data;
	u32			m_size;
	std::mutex	m_lockMutex;
};
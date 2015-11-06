#pragma once

#include <atomic>

class DSharedObject {
public:
	//
	virtual ~DSharedObject() {
	}

	//
	std::size_t AddRef() {
		return m_refs.fetch_add( 1 ) + 1;
	}

	//
	std::size_t Release() {
		if( std::size_t oldValue = m_refs.fetch_sub( 1 ) == 1 ) {
			delete this;
			return 0;
		} else {
			return oldValue - 1;
		}
	}

private:
	//
	std::atomic_size_t m_refs;
};

#pragma once

//
class DSharedObject {
public:
	//
	virtual ~DSharedObject() {
	}

	//
	size_t AddRef() {
		return m_refs.fetch_add( 1 ) + 1;
	}

	//
	size_t Release() {
		if( size_t oldValue = m_refs.fetch_sub( 1 ) == 1 ) {
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

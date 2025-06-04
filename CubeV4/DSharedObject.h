#pragma once

//
class DSharedObject {
public:
        //
        DSharedObject() : m_refs( 0 ) {
        }

        virtual ~DSharedObject() {
        }

	//
	size_t AddRef() {
		return m_refs.fetch_add( 1 ) + 1;
	}

	//
        size_t Release() {
                size_t oldValue = m_refs.fetch_sub( 1 );
                if( oldValue == 1 ) {
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

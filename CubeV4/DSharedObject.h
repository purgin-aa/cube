#ifndef _DSHAREDOBJECT_H_
#define _DSHAREDOBJECT_H_

#include <atomic>

class DSharedObject
{
public:

	virtual ~DSharedObject()
	{
	}

	inline std::size_t AddRef( void )
	{
		return m_refs.fetch_add( 1 ) + 1;
	}

	inline std::size_t Release( void )
	{
		if ( std::size_t oldValue = m_refs.fetch_sub( 1 ) == 1 )
		{
			delete this;
			return 0;
		}
		else
			return oldValue - 1;

	}

private:
	std::atomic_size_t m_refs;
};

#endif

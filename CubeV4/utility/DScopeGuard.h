#pragma once

#include <utility>

template <class func_t>
struct DScopeGuard
{
	inline explicit DScopeGuard( func_t &&exit_fn )
		: m_exit_fn( std::move( exit_fn ) ), m_enabled( true )
	{}

	DScopeGuard( DScopeGuard &&other )
		: m_exit_fn( other.m_exit_fn ), m_enabled( other.m_enabled )
	{
		other.m_enabled = false;
	}

	~DScopeGuard() noexcept
	{
		if ( m_enabled )
			m_exit_fn();
	}

	DScopeGuard( const DScopeGuard & ) = delete;
	DScopeGuard &operator=( const DScopeGuard & ) = delete;

private:
	func_t m_exit_fn;
	bool m_enabled;
};

template <class func_t>
DScopeGuard<func_t> DMakeScopeGuard( func_t &&func )
{
	return DScopeGuard<func_t>( std::forward<func_t>( func ) );
}
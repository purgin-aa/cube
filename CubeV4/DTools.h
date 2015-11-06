#pragma once

namespace DTools {
	//
	template< typename T >
	void MemZero( T& object ) {
		static_assert( !std::is_pointer< T >::value, "We want to zero only values, not pointers" );
		std::memset( &object, 0, sizeof( T ) );
	}

	//
	template< typename T, std::size_t N >
	std::size_t StaticArraySize( const T( &)[N] ) {
		return N;
	}
}

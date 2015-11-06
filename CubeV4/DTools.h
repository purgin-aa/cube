#pragma once

namespace DTools {
	//
	template< typename T >
	void ClearStruct( T &object ) {
		std::memset( &object, 0, sizeof( T ) );
	}

	//
	template< typename T, std::size_t N >
	std::size_t StaticArraySize( const T( &)[N] ) {
		return N;
	}
}

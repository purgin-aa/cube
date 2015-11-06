#pragma once

#include <algorithm>

using u8 = uint8_t;
using u16 = uint16_t;
using i16 = int16_t;
using u32 = uint32_t;
using i32 = int32_t;
using u64 = uint64_t;
using i64 = int64_t;

using f32 = float;
using f64 = double;

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

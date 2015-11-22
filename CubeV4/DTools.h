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

	//
	template <typename T, typename K, typename F>
	std::pair<T, T> WeakLinearSearch( T first, T last, const K& key, F& penaltyFunc ) {
		using ResultType = std::pair<T, T>;

		assert( first <= last );

		if( first == last )
			return ResultType( first, last );

		auto penalty = penaltyFunc( key, *first );
		auto sequenceStart = first++;
		auto sequenceEnd = last;

		while( first != last ) {
			auto currentPenalty = penaltyFunc( key, *first );
			if( currentPenalty < penalty ) {
				penalty = currentPenalty;
				sequenceStart = first;
			}
			else if( currentPenalty > penalty ) {
				sequenceEnd = first;
				break;
			}
			++first;
		}

		return ResultType( sequenceStart, sequenceEnd );
	}

}

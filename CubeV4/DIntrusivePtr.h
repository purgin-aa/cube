#ifndef _DINTRUSIVEPTR_H_
#define _DINTRUSIVEPTR_H_

#include <type_traits>

template< class T >
class DIntrusivePtr {
public:
	explicit DIntrusivePtr() noexcept
		: m_ptr( nullptr ) {
	}

	explicit DIntrusivePtr( T *ptr, bool addref = true ) noexcept
		: m_ptr( ptr ) {
		if( ptr && addref )
			m_ptr->AddRef();
	}

	template< class Y >
	explicit DIntrusivePtr( DIntrusivePtr<Y> &other )
		: m_ptr( other.Get() ) {
		static_assert( std::is_base_of<T, Y>::value, "Incorrect type conversion" );
		if( m_ptr )
			m_ptr->AddRef();
	}

	DIntrusivePtr( std::nullptr_t )
		: DIntrusivePtr() {
	}

	DIntrusivePtr( DIntrusivePtr &&other ) noexcept
		: m_ptr( other.m_ptr ) {
		other.m_ptr = nullptr;
	}

	DIntrusivePtr( const DIntrusivePtr &other ) noexcept
		: m_ptr( other.m_ptr ) {
		if( m_ptr )
			m_ptr->AddRef();
	}

	~DIntrusivePtr() {
		if( m_ptr )
			m_ptr->Release();
	}

	T *operator->() const noexcept {
		return m_ptr;
	}

	T **operator&() noexcept {

		return &m_ptr;
	}

	T &operator *() const {
		return *m_ptr;
	}

	bool IsValid() const noexcept {
		return m_ptr != nullptr;
	}

	bool operator == ( const DIntrusivePtr & other ) const {
		return m_ptr == other.m_ptr;
	}

	bool operator != ( const DIntrusivePtr &other ) const {
		return m_ptr != other.m_ptr;
	}

	DIntrusivePtr &operator = ( const DIntrusivePtr &other ) {
		Reset( other.m_ptr );

		return *this;
	}

	template <class Y>
	DIntrusivePtr<T> &operator = ( const DIntrusivePtr<Y> &other ) {
		static_assert( std::is_base_of<T, Y>::value, "Incorrect type conversion" );

		Reset( other.Get() );
		return *this;
	}

	DIntrusivePtr &operator = ( T* ptr ) noexcept {
		Reset( ptr );
		return *this;
	}

	DIntrusivePtr &operator = ( std::nullptr_t ) {
		Reset();
		return *this;
	}

	T* Get() const {
		return m_ptr;
	}

	void Reset() {
		if( m_ptr ) {
			m_ptr->Release();
			m_ptr = nullptr;
		}
	}

	void Reset( T *ptr, bool addRef = true ) {
		if( m_ptr == ptr )
			return;

		if( m_ptr )
			m_ptr->Release();

		m_ptr = ptr;

		if( ptr && addRef )
			m_ptr->AddRef();
	}

	operator bool() const {
		return IsValid();
	}

private:
	//
	T *m_ptr;
};

#endif

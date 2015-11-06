#pragma once

template< class T >
class DIntrusivePtr {
public:
	explicit DIntrusivePtr() : m_ptr( nullptr ) {
	}

	explicit DIntrusivePtr( T* ptr, bool addref = true ) : m_ptr( ptr ) {
		if( ptr && addref )
			m_ptr->AddRef();
	}

	template< class Y >
	explicit DIntrusivePtr( DIntrusivePtr< Y >& other ) : m_ptr( other.Get() ) {
		static_assert( std::is_base_of< T, Y >::value, "Incorrect type conversion" );
		if( m_ptr )
			m_ptr->AddRef();
	}

	DIntrusivePtr( std::nullptr_t )
		: DIntrusivePtr() {
	}

	DIntrusivePtr( DIntrusivePtr&& other ) : m_ptr( other.m_ptr ) {
		other.m_ptr = nullptr;
	}

	DIntrusivePtr( const DIntrusivePtr& other ) : m_ptr( other.m_ptr ) {
		if( m_ptr )
			m_ptr->AddRef();
	}

	~DIntrusivePtr() {
		if( m_ptr )
			m_ptr->Release();
	}

	T* operator ->() const {
		return m_ptr;
	}

	T** operator &() {

		return &m_ptr;
	}

	T& operator *() const {
		return *m_ptr;
	}

	bool IsValid() const {
		return m_ptr != nullptr;
	}

	bool operator ==( const DIntrusivePtr& other ) const {
		return m_ptr == other.m_ptr;
	}

	bool operator !=( const DIntrusivePtr& other ) const {
		return m_ptr != other.m_ptr;
	}

	DIntrusivePtr& operator =( const DIntrusivePtr& other ) {
		Reset( other.m_ptr );
		return *this;
	}

	template< class Y >
	DIntrusivePtr< T >& operator =( const DIntrusivePtr< Y >& other ) {
		static_assert( std::is_base_of< T, Y >::value, "Incorrect type conversion" );
		Reset( other.Get() );
		return *this;
	}

	DIntrusivePtr& operator =( T* ptr ) {
		Reset( ptr );
		return *this;
	}

	DIntrusivePtr& operator =( std::nullptr_t ) {
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

	void Reset( T* ptr, bool addRef = true ) {
		if( m_ptr == ptr )
			return;

		if( m_ptr )
			m_ptr->Release();

		m_ptr = ptr;

		if( ptr && addRef )
			m_ptr->AddRef();
	}

	explicit operator bool() const {
		return IsValid();
	}

private:
	//
	T* m_ptr;
};

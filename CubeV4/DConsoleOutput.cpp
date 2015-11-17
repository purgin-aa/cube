#include "Precompiled.h"
#include "DConsoleOutput.h"

DIOSys::OutputConsole::OutputConsole( HANDLE consoleOutput, bool init ) 
	: m_output( consoleOutput)
	, m_owner( init )
{
	if( init && ( consoleOutput == INVALID_HANDLE_VALUE ) ) {
		if( AllocConsole() ) {
			m_output = GetStdHandle( STD_OUTPUT_HANDLE );
		}
	}
}

DIOSys::OutputConsole::~OutputConsole() {
	if( m_owner )
		FreeConsole();
}

void DIOSys::OutputConsole::Write( const void * buffer, std::size_t size ) {
	assert( m_output != INVALID_HANDLE_VALUE );

	DWORD numWriten = 0u;

	WriteConsoleA( m_output,
				   buffer,
				   static_cast< DWORD >( size ),
				   &numWriten,
				   nullptr );
}

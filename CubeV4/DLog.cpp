#include "Precompiled.h"
#include "DLog.h"
#include "DIntrusivePtr.h"
#include <stdarg.h>


// GlobalOutputs
static DIntrusivePtr<DIOSys::IOutputDevice> __errorOutput;
static DIntrusivePtr<DIOSys::IOutputDevice> __warningOutput;
static DIntrusivePtr<DIOSys::IOutputDevice> __infoOutput;
static DIntrusivePtr<DIOSys::IOutputDevice> __debugOutput;

//
static const std::size_t __MAX_BUFFER_LEN = 1024u;

/*
	PRIVATE FUNCTION DEFINITION
*/
static void __FormatToOutput( DIOSys::IOutputDevice *output, const char *str, va_list args );
static void __PutStrToOutput( DIOSys::IOutputDevice *output, const char *str );


/*
	IMPLEMENTATION 
*/
void DLog::Warning( const char * str, ... ) {
	if( __warningOutput ) {
		va_list	arguments;
		va_start( arguments, str );
		__PutStrToOutput( __warningOutput.Get(), "WARNING: " );
		__FormatToOutput( __warningOutput.Get(), str, arguments );
	}
}

//
void DLog::Error( const char * str, ... ) {
	if( __errorOutput ) {
		va_list	arguments;
		va_start( arguments, str );
		__PutStrToOutput( __errorOutput.Get(), "ERROR: " );
		__FormatToOutput( __errorOutput.Get(), str, arguments );
	}
}

//
void DLog::Info( const char * str, ... ) {
	if( __infoOutput ) {
		va_list	arguments;
		va_start( arguments, str );
		__PutStrToOutput( __infoOutput.Get(), "INFO: " );
		__FormatToOutput( __infoOutput.Get(), str, arguments );
	}
}

//
void DLog::Debug( const char * str, ... ) {
#if defined( DEBUG ) || defined( _DEBUG )
	if( __debugOutput ) {
		va_list	arguments;
		va_start( arguments, str );
		__PutStrToOutput( __debugOutput.Get(), "DEBUG: " );
		__FormatToOutput( __debugOutput.Get(), str, arguments );
	}
#endif
}

//
void DLog::SetErrorOutputDevice( DIOSys::IOutputDevice * output ) {
	__errorOutput = output;
}

//
void DLog::SetWarningOutputDevice( DIOSys::IOutputDevice * output ) {
	__warningOutput = output;
}

//
void DLog::SetInfoOutputDevice( DIOSys::IOutputDevice * output ) {
	__infoOutput = output;
}


void DLog::SetDebugOutputDevice( DIOSys::IOutputDevice * output ) {
#if defined( DEBUG ) || defined( _DEBUG )
	__debugOutput = output;
#endif
}

/*
	PRIVATE FUNCTIONS IMPLEMENTATION
*/
static void __FormatToOutput( DIOSys::IOutputDevice *output, const char *str, va_list args ) {
	assert( output );

	char buffer[ __MAX_BUFFER_LEN ];
	int bytesWriten = vsnprintf(
		&buffer[ 0 ],
		__MAX_BUFFER_LEN,
		str,
		args );

	output->Write( &buffer, static_cast< std::size_t > ( bytesWriten ) );
}
//
static void __PutStrToOutput( DIOSys::IOutputDevice *output, const char *str ) {
	assert( output );
	if( str ) {
		const std::size_t len = strlen( str );
		output->Write( str, len );
	}

}
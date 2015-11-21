#include "Precompiled.h"
#include "DLog.h"
#include "DIntrusivePtr.h"
#include <stdarg.h>


using namespace DIOSys;


// GlobalOutputs
static DIntrusivePtr< IOutputDevice > errorOutput;
static DIntrusivePtr< IOutputDevice > warningOutput;
static DIntrusivePtr< IOutputDevice > infoOutput;
static DIntrusivePtr< IOutputDevice > debugOutput;

//
static const std::size_t MAX_BUFFER_LEN = 1024;

/*
	PRIVATE FUNCTION DEFINITION
*/
static void FormatToOutput( IOutputDevice* output, const char* str, va_list args );
static void PutStrToOutput( IOutputDevice* output, const char* str );


/*
	IMPLEMENTATION 
*/
void DLog::Warning( const char* str, ... ) {
	if( warningOutput ) {
		va_list	arguments;
		va_start( arguments, str );
		PutStrToOutput( warningOutput.Get(), "WARNING: " );
		FormatToOutput( warningOutput.Get(), str, arguments );
	}
}


//
void DLog::Error( const char* str, ... ) {
	if( errorOutput ) {
		va_list	arguments;
		va_start( arguments, str );
		PutStrToOutput( errorOutput.Get(), "ERROR: " );
		FormatToOutput( errorOutput.Get(), str, arguments );
	}
}


//
void DLog::Info( const char* str, ... ) {
	if( infoOutput ) {
		va_list	arguments;
		va_start( arguments, str );
		PutStrToOutput( infoOutput.Get(), "INFO: " );
		FormatToOutput( infoOutput.Get(), str, arguments );
	}
}


//
void DLog::Debug( const char* str, ... ) {
#if defined( DEBUG ) || defined( _DEBUG )
	if( debugOutput ) {
		va_list	arguments;
		va_start( arguments, str );
		PutStrToOutput( debugOutput.Get(), "DEBUG: " );
		FormatToOutput( debugOutput.Get(), str, arguments );
	}
#endif
}


//
void DLog::SetErrorOutputDevice( IOutputDevice* output ) {
	errorOutput = output;
}


//
void DLog::SetWarningOutputDevice( IOutputDevice* output ) {
	warningOutput = output;
}


//
void DLog::SetInfoOutputDevice( IOutputDevice* output ) {
	infoOutput = output;
}


//
void DLog::SetDebugOutputDevice( IOutputDevice* output ) {
#if defined( DEBUG ) || defined( _DEBUG )
	debugOutput = output;
#endif
}


/*
	PRIVATE FUNCTIONS IMPLEMENTATION
*/
static void FormatToOutput( IOutputDevice* output, const char* str, va_list args ) {
	assert( output );

	char buffer[ MAX_BUFFER_LEN ];
	int bytesWriten = vsnprintf(
		&buffer[ 0 ],
		MAX_BUFFER_LEN,
		str,
		args );

	output->Write( &buffer, bytesWriten );
}


//
static void PutStrToOutput( IOutputDevice* output, const char* str ) {
	assert( output );
	if( str ) {
		const std::size_t len = strlen( str );
		output->Write( str, len );
	}
}

#include "Precompiled.h"
#include "DFileTools.h"
#include "DLog.h"

//
DID3DBlobPtr DCreateBlobFromFile( const char* path ) {
	assert( path );

	// open file
	HANDLE file = CreateFileA(
			path,
			GENERIC_READ,
			FILE_SHARE_READ,
			nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr );
	if( file == INVALID_HANDLE_VALUE ) {
		DLog::Error( "Failed to open file \"%s\"\n", path );
		return nullptr;
	}

	auto fileCloseGuard = DMakeScopeGuard( [&]() {
		CloseHandle( file );
	} );
		
	// get file size
	DWORD fileSizeLow = 0;
	DWORD fileSizeHigh = 0;
	fileSizeLow = GetFileSize( file, &fileSizeHigh );
	if( fileSizeHigh > 0 ) {// file too big
		DLog::Error( "File \"%s\" too big\n", path );
		return nullptr;
	}

	// allocate blob
	DID3DBlobPtr fileBlob;
	HRESULT hr = D3DCreateBlob( fileSizeLow, &fileBlob );
	if( FAILED( hr ) ) {
		DLog::Error( "Failed to create a file blob\n" );
		return nullptr; // todo log message
	}

	// read file data
	DWORD numBytesRead = 0;
	if( !ReadFile( file, fileBlob->GetBufferPointer(), fileSizeLow, &numBytesRead, nullptr ) ) {
		DLog::Error( "Failed to read data from file \"%s\"\n", path );
		return nullptr;
	}

	return fileBlob;
}

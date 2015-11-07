#include "Precompiled.h"
#include "DFileTools.h"

DID3DBlobPtr DCreateBlobFromFile( const char * path ) {
	assert( path );

	// open file
	HANDLE file =
		CreateFileA(
			path,
			GENERIC_READ,
			FILE_SHARE_READ,
			nullptr,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			nullptr );

	if( file == INVALID_HANDLE_VALUE )
		return nullptr;

	auto fileCloseGuard = DMakeScopeGuard( [&]() {
		CloseHandle( file );
	} );
		
	// Get file size
	DWORD fileSizeLow = 0u;
	DWORD fileSizeHight = 0u;
	
	fileSizeLow = GetFileSize( file, &fileSizeHight );

	if( fileSizeHight > 0u ) // file too big
		return nullptr;

	// allocate blob
	DID3DBlobPtr fileBlob;
	HRESULT hr = D3DCreateBlob(
		static_cast< SIZE_T >( fileSizeLow ),
		&fileBlob );

	if( FAILED( hr ) )
		return nullptr; // todo log message

	// read file data
	DWORD numBytesRead = 0u;

	if( !ReadFile(
		file,
		fileBlob->GetBufferPointer(),
		fileSizeLow,
		&numBytesRead,
		0 ) )
	{
		return nullptr;
	}

	return fileBlob;
}

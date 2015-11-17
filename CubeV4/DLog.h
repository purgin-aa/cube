#pragma once

#include "DOutputDevice.h"

namespace DLog {

	//
	void Warning( const char* str, ... );
	void Error( const char* str, ... );
	void Info( const char *str, ... );
	void Debug( const char *str, ... );

	void SetErrorOutputDevice( DIOSys::IOutputDevice *output );
	void SetWarningOutputDevice( DIOSys::IOutputDevice *output );
	void SetInfoOutputDevice( DIOSys::IOutputDevice *output );
	void SetDebugOutputDevice( DIOSys::IOutputDevice *output );

}
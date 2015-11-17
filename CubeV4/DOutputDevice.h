#pragma once

#include "Precompiled.h"
#include "DSharedObject.h"

namespace DIOSys {

	//
	struct IOutputDevice : public DSharedObject {
		virtual ~IOutputDevice() {};
		virtual void Write( const void *buffer, std::size_t size ) = 0;
	};


}
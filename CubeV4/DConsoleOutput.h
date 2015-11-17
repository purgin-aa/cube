#pragma once

#include "DOutputDevice.h"

namespace DIOSys {

	//
	class OutputConsole : public IOutputDevice {
	public:
		OutputConsole( HANDLE consoleOutput, bool init = true );
		virtual ~OutputConsole() override;

		//
		virtual void Write( const void * buffer, std::size_t size ) override;
	private:
		HANDLE m_output;
		bool m_owner;
	};

}
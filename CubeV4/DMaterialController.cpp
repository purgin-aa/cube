#include "Precompiled.h"
#include "DMaterialController.h"

DMaterialController::DMaterial::DMaterial( DMaterialController * controller ) :
	m_controller( controller )
{
	assert( controller );
}

void DMaterialController::DMaterial::GetMaterialController( DMaterialController ** pController ) {
	assert( m_controller );

	if( pController )
		*pController = m_controller.Get();
}

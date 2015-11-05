#ifndef _DMATERIALCONTROLLER_H_
#define _DMATERIALCONTROLLER_H_

#include "DIntrusivePtr.h"
#include "DSharedObject.h"


class DRenderContextPtr;

class DMaterialController
	: DSharedObject
{
public:
	class DMaterial
		: public DSharedObject
	{
	public:
		virtual ~DMaterial(){ }
	};

	virtual ~DMaterialController() {};

	virtual void PrepareContext( DRenderContextPtr ) = 0;
	virtual void FreeContext( DRenderContextPtr ) = 0;
	virtual void BindMaterial( DIntrusivePtr<DMaterial> ) = 0;
};

#endif
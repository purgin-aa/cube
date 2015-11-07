#pragma once

#include "DIntrusivePtr.h"
#include "DSharedObject.h"

class DRenderContext;

class DMaterialController : public DSharedObject {
public:
	//
	class DMaterial : public DSharedObject {
	public:
		explicit DMaterial( DMaterialController *controller );

		virtual ~DMaterial() {}

		void GetMaterialController( DMaterialController **pController );
	protected:
		DIntrusivePtr<DMaterialController> m_controller;
	};

	virtual ~DMaterialController() {};

	virtual void PrepareContext( DRenderContext * ) = 0;
	virtual void FreeContext( DRenderContext * ) = 0;
	virtual void BindMaterial( DRenderContext *, DMaterial * ) = 0;
};

using DMaterialControllerPtr = DIntrusivePtr<DMaterialController>;
using DMaterialPtr = DIntrusivePtr<DMaterialController::DMaterial>;
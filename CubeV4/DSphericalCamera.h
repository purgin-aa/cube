#pragma once

#include "Precompiled.h"

using namespace DirectX; // XMVECTOR, XMMATRIX...

//
class DSphericalCamera {
public:
	DSphericalCamera();
	DSphericalCamera( f32 latitude, f32 longitude, const XMVECTOR &pos );

	void				SetLatitude( f32 latitude );
	void				SetLongitude( f32 longitude );
	void				SetPos( const XMVECTOR &pos );
	void				AddLatitude( f32 delta );
	void				AddLongitude( f32 delta );
	void				MoveInLocalCoords( f32 dx, f32 dy, f32 dz );
	
	f32					GetLatitude() const;
	f32					GetLongitude() const;
	const XMVECTOR&		GetPos() const;
	const XMMATRIX&		GetViewMatrix() const;
	bool				IsUpdated() const;

private:
	mutable f32			m_latitude;
	mutable f32			m_longitude;
	XMVECTOR			m_pos;

	mutable bool		m_updateMatrix;
	mutable bool		m_updateOrientationVectors;
	mutable XMMATRIX	m_viewMatrix;

	mutable XMVECTOR	m_right;
	mutable XMVECTOR	m_up;
	mutable XMVECTOR	m_direction;
private:

	void				EnableUpdateMatrixFlag() const;
	void				DisableUpdateMatrixFlag() const;
	void				EnableUpdateOrientationVectorsFlag() const;
	void				DisableUpdateOrientationVectorsFlag() const;
	void				UpdateOrientationVectors() const;
	void				EvaluateOrientationVectors() const;
	void				EvaluateMatrix() const;
	void				CheckAngles() const;
	void				FixAngle( f32 &angle ) const;
};
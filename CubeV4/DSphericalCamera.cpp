#include "Precompiled.h"
#include "DSphericalCamera.h"

//
DSphericalCamera::DSphericalCamera()
	: m_latitude( 0.0f )
	, m_longitude( 0.0f )
	, m_pos{ 0.0f, 0.0f, 0.0f, 0.0f }
	, m_updateMatrix( true )
	, m_viewMatrix( XMMatrixIdentity() )
{}

//
DSphericalCamera::DSphericalCamera( f32 latitude, f32 longitude, const XMVECTOR & pos )
	: m_latitude( latitude )
	, m_longitude( longitude )
	, m_pos( pos )
	, m_updateMatrix( true )
	, m_viewMatrix( XMMatrixIdentity() ) {
	CheckAngles();
}

//
void DSphericalCamera::SetLatitude( f32 latitude ) {
	EnableUpdateOrientationVectorsFlag();
	m_latitude = latitude;
	CheckAngles();
}

//
void DSphericalCamera::SetLongitude( f32 longitude ) {
	EnableUpdateOrientationVectorsFlag();
	m_longitude = longitude;
	CheckAngles();
}

//
void DSphericalCamera::SetPos( const XMVECTOR & pos ) {
	m_pos = pos;
	EnableUpdateMatrixFlag();
}

//
void DSphericalCamera::AddLatitude( f32 delta ) {
	EnableUpdateOrientationVectorsFlag();
	m_latitude += delta;
	CheckAngles();
}

//
void DSphericalCamera::AddLongitude( f32 delta ) {
	EnableUpdateOrientationVectorsFlag();
	m_longitude += delta;
	CheckAngles();
}

//
void DSphericalCamera::MoveInLocalCoords( f32 dx, f32 dy, f32 dz ) {
	EvaluateOrientationVectors();
	m_pos += m_direction * dz + m_right * dx + m_up * dy;
	EnableUpdateMatrixFlag();
}

//
f32 DSphericalCamera::GetLatitude() const {
	return m_latitude;
}

//
f32 DSphericalCamera::GetLongitude() const {
	return m_longitude;
}

//
const XMVECTOR & DSphericalCamera::GetPos() const {
	return m_pos;
}

//
const XMMATRIX & DSphericalCamera::GetViewMatrix() const {
	if( IsUpdated() )
	{
		EvaluateOrientationVectors();
		EvaluateMatrix();
		DisableUpdateMatrixFlag();
	}

	return m_viewMatrix;
}

//
bool DSphericalCamera::IsUpdated() const {
	return m_updateMatrix || m_updateOrientationVectors;
}

//
void DSphericalCamera::EnableUpdateMatrixFlag() const {
	m_updateMatrix = true;
}

//
void DSphericalCamera::DisableUpdateMatrixFlag() const {
	m_updateMatrix = false;
}

//
void DSphericalCamera::EnableUpdateOrientationVectorsFlag() const {
	EnableUpdateMatrixFlag();
	m_updateOrientationVectors = true;
}

//
void DSphericalCamera::DisableUpdateOrientationVectorsFlag() const {
	m_updateOrientationVectors = false;
}

//
void DSphericalCamera::UpdateOrientationVectors() const {
	if( m_updateOrientationVectors )
	{
		EvaluateOrientationVectors();
		DisableUpdateOrientationVectorsFlag();
	}
}

//
void DSphericalCamera::EvaluateOrientationVectors() const {
	const f32 cos_latitude = cosf( m_latitude );
	const f32 sin_latitude = sinf( m_latitude );
	const f32 cos_longitude = cosf( m_longitude );
	const f32 sin_longitude = sinf( m_longitude );

	m_direction = {
		cos_latitude * sin_longitude,
		sin_latitude,
		cos_latitude * cos_longitude
	};

	m_right = {
		-cos_longitude, // sin( longitude - pi/2 )
		0.0f,
		sin_longitude // cos( longitude - pi/2 )
	};

	m_up = XMVector3Cross(
		m_right,
		m_direction );

	m_updateOrientationVectors = false;
}

//
void DSphericalCamera::EvaluateMatrix() const {
	const f32 cos_latitude = cosf( m_latitude );
	const f32 sin_latitude = sinf( m_latitude );
	const f32 cos_longitude = cosf( m_longitude );
	const f32 sin_longitude = sinf( m_longitude );

	m_viewMatrix =
		XMMatrixLookToLH(
			m_pos,
			m_direction,
			m_up );
}

//
void DSphericalCamera::CheckAngles() const {
	FixAngle( m_latitude );
	FixAngle( m_longitude );
}

//
void DSphericalCamera::FixAngle( f32 & angle ) const {
	static const f32 __2pi = 2.0f*3.14159265f;

	const f32 angleModule = fabs( angle );
	if( angleModule > __2pi )
	{
		f32 n = floorf( angle / __2pi );
		angle -= n*__2pi;
	}

	if( angle < 0.0f )
		angle = __2pi - angleModule;
	else
		angle = angleModule;
}

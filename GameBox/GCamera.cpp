#include "GCamera.h"

GCamera::GCamera()
	:GObject(GT_CAMERA), 
	m_v3Position(0, 0, 0), m_v3DestPosition(0, 0, 0), m_v3Up(0, 0, 0),
	m_mViewMatrixInverse(*dxGetUnitMatrix())
{

}

GCamera::GCamera( GObjectTypes type )
	:GObject(type), 
	m_v3Position(0, 0, 0), m_v3DestPosition(0, 0, 0), m_v3Up(0, 0, 0),
	m_mViewMatrixInverse(*dxGetUnitMatrix())
{

}

GCamera::~GCamera()
{

}

void GCamera::setView( 
	const D3DXVECTOR3* ePos, 
	const D3DXVECTOR3* dPos, 
	const D3DXVECTOR3* up )
{
	m_v3Position = *ePos;
	m_v3DestPosition = *dPos;
	m_v3Up = *up;
	dxMatrixLookAtLHInverse(&m_mViewMatrixInverse, ePos, dPos, up);
}

void GCamera::setView( 
	float ex, float ey, float ez,
	float dx, float dy, float dz,
	float upx, float upy, float upz )
{
	setView(&D3DXVECTOR3(ex, ey, ez),
		&D3DXVECTOR3(dx, dy, dz),
		&D3DXVECTOR3(upx, upy, upz));
}

void GCamera::setupCamera()
{
	Update();
	D3DXMATRIX lookMatrix;
	D3DXMatrixInverse(&lookMatrix, nullptr, &m_mViewMatrixInverse);
	dxSetView(&lookMatrix);
}

void GCamera::Update()
{
	if(!isEnableFlag(GCAMERA_UPDATE))
		return;
	setView(&m_v3Position, &m_v3DestPosition, &m_v3Up);
	TurnOffFlag(GCAMERA_UPDATE);
}

void GCamera::UpdateDirect()
{
	setView(&m_v3Position, &m_v3DestPosition, &m_v3Up);
}

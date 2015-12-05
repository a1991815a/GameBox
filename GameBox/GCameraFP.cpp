#include "GCameraFP.h"

GCameraFP::GCameraFP()
	:GCamera(GT_CAMERA_FP)
{

}

GCameraFP::~GCameraFP()
{

}

void GCameraFP::Move( float x, float y, float z )
{
	D3DXVECTOR3 move_vec3(0, 0, 0);
	move_vec3 += x * *getAxisX();
	move_vec3 += y * *getAxisY();
	move_vec3 += z * *getAxisZ();

	setPosition(&(*getPosition() + move_vec3));
	setDestPosition(&(*getDestPosition() + move_vec3));
}

void GCameraFP::MoveX( float x )
{
	D3DXVECTOR3 move_vec3(0, 0, 0);
	move_vec3 += x * *getAxisX();
	setPosition(&(*getPosition() + move_vec3));
	setDestPosition(&(*getDestPosition() + move_vec3));
}

void GCameraFP::MoveY( float y )
{
	D3DXVECTOR3 move_vec3(0, 0, 0);
	move_vec3 += y * *getAxisY();
	setPosition(&(*getPosition() + move_vec3));
	setDestPosition(&(*getDestPosition() + move_vec3));
}

void GCameraFP::MoveZ( float z )
{
	D3DXVECTOR3 move_vec3(0, 0, 0);
	move_vec3 += z * *getAxisZ();
	setPosition(&(*getPosition() + move_vec3));
	setDestPosition(&(*getDestPosition() + move_vec3));
}

void GCameraFP::Rotate( float x, float y )
{
	RotateX(x);
	RotateY(y);
}

void GCameraFP::RotateX( float x )
{
	D3DXVECTOR3 direction = *getDestPosition() - *getPosition();
	float tmp_angle = dxVec3Angle(&direction, getUp()) + x;
	if(tmp_angle <= 0 || tmp_angle >= D3DX_PI)
		return;
	D3DXMATRIX matrix;
	D3DXMatrixRotationAxis(&matrix, getAxisX(), x);
	D3DXVec3TransformNormal(&direction, &direction, &matrix);
	setDestPosition(&(*getPosition() + direction));
}

void GCameraFP::RotateY( float y )
{
	D3DXVECTOR3 direction = *getDestPosition() - *getPosition();
	D3DXMATRIX matrix;
	D3DXMatrixRotationAxis(&matrix, getAxisY(), y);
	D3DXVec3TransformNormal(&direction, &direction, &matrix);
	setDestPosition(&(*getPosition() + direction));
	UpdateDirect();
}

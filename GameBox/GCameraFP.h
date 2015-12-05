#ifndef __GCAMERAFP__
#define __GCAMERAFP__
#include "GCamera.h"

class GCameraFP: public GCamera{
public:
	GCameraFP();
	~GCameraFP();

	void Move(float x, float y, float z);
	void MoveX(float x);
	void MoveY(float y);
	void MoveZ(float z);

	void Rotate(float x, float y);
	void RotateX(float x);
	void RotateY(float y);
};
#endif
#ifndef __GCAMERA__
#define __GCAMERA__
#include "GObject.h"

#define GCAMERA_UPDATE 0x00000001

class GCamera: public GObject{
protected:
	GCamera(GObjectTypes type);
public:
	GCamera();
	~GCamera();

	void setView(
		const D3DXVECTOR3* ePos,
		const D3DXVECTOR3* dPos,
		const D3DXVECTOR3* up
		);
	void setView(
		float ex, float ey, float ez,
		float dx, float dy, float dz,
		float upx, float upy, float upz
		);

	void setupCamera();
	void Update();
	void UpdateDirect();

//setter getter
	inline const D3DXVECTOR3* getAxisX() const{
		return (const D3DXVECTOR3*)m_mViewMatrixInverse.m[0];
	};
	inline const D3DXVECTOR3* getAxisY() const{
		return (const D3DXVECTOR3*)m_mViewMatrixInverse.m[1];
	};
	inline const D3DXVECTOR3* getAxisZ() const{
		return (const D3DXVECTOR3*)m_mViewMatrixInverse.m[2];
	};
	inline const D3DXVECTOR3* getPosition() const { return &m_v3Position; };
	inline const D3DXVECTOR3* getDestPosition() const { return &m_v3DestPosition; };
	inline const D3DXVECTOR3* getUp() const { return &m_v3Up; };
	inline const D3DXMATRIX* getMatrix() const { return &m_mViewMatrixInverse; };


	inline void setPosition(const D3DXVECTOR3* pos){
		m_v3Position = *pos;
		TurnOnFlag(GCAMERA_UPDATE);
	};
	inline void setPositionX(float x){
		m_v3Position.x = x;
		TurnOnFlag(GCAMERA_UPDATE);
	};
	inline void setPositionY(float y){
		m_v3Position.y = y;
		TurnOnFlag(GCAMERA_UPDATE);
	};
	inline void setPositionZ(float z){
		m_v3Position.z = z;
		TurnOnFlag(GCAMERA_UPDATE);
	};
	inline void setDestPosition(const D3DXVECTOR3* pos){
		m_v3DestPosition = *pos;
		TurnOnFlag(GCAMERA_UPDATE);
	};
	inline void setDestPositionX(float x){
		m_v3DestPosition.x = x;
		TurnOnFlag(GCAMERA_UPDATE);
	};
	inline void setDestPositionY(float y){
		m_v3DestPosition.y = y;
		TurnOnFlag(GCAMERA_UPDATE);
	};
	inline void setDestPositionZ(float z){
		m_v3DestPosition.z = z;
		TurnOnFlag(GCAMERA_UPDATE);
	};
	inline void setUp(const D3DXVECTOR3* up){
		m_v3Up = *up;
		TurnOnFlag(GCAMERA_UPDATE);
	};
	inline void setUpX(float x){
		m_v3Up.x = x;
		TurnOnFlag(GCAMERA_UPDATE);
	};
	inline void setUpY(float y){
		m_v3Up.y = y;
		TurnOnFlag(GCAMERA_UPDATE);
	};
	inline void setUpZ(float z){
		m_v3Up.z = z;
		TurnOnFlag(GCAMERA_UPDATE);
	};
private:
	D3DXVECTOR3		m_v3Position;
	D3DXVECTOR3		m_v3DestPosition;
	D3DXVECTOR3		m_v3Up;
	D3DXMATRIX		m_mViewMatrixInverse;
};
#endif
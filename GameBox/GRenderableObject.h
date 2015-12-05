#ifndef __GRENDERABLEOBJECT__
#define __GRENDERABLEOBJECT__
#include "GObject.h"
#include "GMaterial.h"
#include "Texture.h"
#include "DXUtils.h"

#define MESH_LOCK(VERTEX, INDEX) \
getMesh()->LockVertexBuffer(0, (void**)&VERTEX); \
getMesh()->LockIndexBuffer(0, (void**)&INDEX)

#define MESH_UNLOCK() \
getMesh()->UnlockVertexBuffer(); \
getMesh()->UnlockIndexBuffer()

#define GRENDERABLE_UPDATE 0x00000001

class GRenderableObject : public GObject {
protected:
	GRenderableObject(GObjectTypes type);
public:
	GRenderableObject();
	~GRenderableObject() {
		SAFE_RELEASE_COM(m_pMesh);
	};

	virtual void Update();
	virtual void Draw();
	virtual void DrawSubset(DWORD index);

	inline ID3DXMesh* getMesh() { return m_pMesh; };
	inline const ID3DXMesh* getMesh() const { return m_pMesh; };
	
	inline const D3DXVECTOR3* getPosition() const { return &m_v3Position; };
	inline const D3DXVECTOR3* getScaling() const { return &m_v3Scaling; };
	inline const D3DXVECTOR3* getRotation() const { return &m_v3Rotation; };
	inline const D3DXMATRIX* getMatrix() const { return &m_mMatrix; };

	inline D3DXVECTOR3* getPosition() { return &m_v3Position; };
	inline D3DXVECTOR3* getScaling() { return &m_v3Scaling; };
	inline D3DXVECTOR3* getRotation() { return &m_v3Rotation; };
	inline D3DXMATRIX* getMatrix() { return &m_mMatrix; };

	inline void setPosition(const D3DXVECTOR3* pos) {
		m_v3Position = *pos;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	inline void setPositionX(float x) {
		m_v3Position.x = x;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	inline void setPositionY(float y) {
		m_v3Position.y = y;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	inline void setPositionZ(float z) {
		m_v3Position.z = z;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	inline void setScaling(const D3DXVECTOR3* scaling) {
		m_v3Scaling = *scaling;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	inline void setScalingX(float x) {
		m_v3Scaling.x = x;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	inline void setScalingY(float y) {
		m_v3Scaling.y = y;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	inline void setScalingZ(float z) {
		m_v3Scaling.z = z;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	inline void setRotation(const D3DXVECTOR3* rotation) {
		m_v3Rotation = *rotation;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	inline void setRotationX(float x) {
		m_v3Rotation.x = x;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	inline void setRotationY(float y) {
		m_v3Rotation.y = y;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	inline void setRotationZ(float z) {
		m_v3Rotation.z = z;
		TurnOnFlag(GRENDERABLE_UPDATE);
	};
	void setAttributeCount(DWORD _count);
	size_t getAttributeCount() const;

protected:
	inline void setMesh(ID3DXMesh* mesh) {	 m_pMesh = mesh;};
private:
	ID3DXMesh*				m_pMesh;				//网格
	D3DXVECTOR3				m_v3Position;			//位置
	D3DXVECTOR3				m_v3Scaling;			//缩放
	D3DXVECTOR3				m_v3Rotation;			//旋转
	D3DXMATRIX				m_mMatrix;				//模型矩阵

	size_t					m_iNumAttributeId;		//子集总数
	Vector<GMaterial*>		m_pMaterialArray;		//材质(数组长度=子集总数)		
	Vector<Texture*>		m_pTextureArray;		//纹理(数组长度=子集总数)
};
#endif
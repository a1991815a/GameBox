#include "GRenderableObject.h"

GRenderableObject::GRenderableObject() 
	:GObject(GT_RENDERABLEOBJ), m_pMesh(nullptr),
	m_v3Position(0, 0, 0), m_v3Scaling(1, 1, 1), m_v3Rotation(0, 0, 0),
	m_mMatrix(*dxGetUnitMatrix()), m_iNumAttributeId(0)
{};

GRenderableObject::GRenderableObject(GObjectTypes type)
	:GObject(type), m_pMesh(nullptr),
	m_v3Position(0, 0, 0), m_v3Scaling(1, 1, 1), m_v3Rotation(0, 0, 0),
	m_mMatrix(*dxGetUnitMatrix()), m_iNumAttributeId(0)
{};

void GRenderableObject::Update()
{
	if (!(getFlag() & GRENDERABLE_UPDATE))
		return;
	D3DXMatrixIdentity(&m_mMatrix);
	D3DXMATRIX matrix;
	D3DXMatrixRotationX(&matrix, m_v3Rotation.x);
	m_mMatrix = m_mMatrix * matrix;
	D3DXMatrixRotationY(&matrix, m_v3Rotation.y);
	m_mMatrix = m_mMatrix * matrix;
	D3DXMatrixRotationZ(&matrix, m_v3Rotation.z);
	m_mMatrix = m_mMatrix * matrix;
	D3DXMatrixScaling(&matrix, m_v3Scaling.x, m_v3Scaling.y, m_v3Scaling.z);
	m_mMatrix = m_mMatrix * matrix;
	D3DXMatrixTranslation(&matrix, m_v3Position.x, m_v3Position.y, m_v3Position.z);
	m_mMatrix = m_mMatrix * matrix;


	TurnOffFlag(GRENDERABLE_UPDATE);
}

void GRenderableObject::Draw()
{
	dxSetWorld(&m_mMatrix);
	
	for (size_t i = 0; i < m_iNumAttributeId; ++i)
	{
		m_pMaterialArray.at(i)->setupMaterial_Safe();
		m_pTextureArray.at(i)->setupTexture_Safe(0);
		m_pMesh->DrawSubset(i);
	}
}

void GRenderableObject::DrawSubset(DWORD index)
{
	dxSetWorld(&m_mMatrix);
	m_pMaterialArray.at(index)->setupMaterial_Safe();
	m_pTextureArray.at(index)->setupTexture_Safe(0);
	m_pMesh->DrawSubset(index);
}

void GRenderableObject::setAttributeCount(DWORD _count)
{
	m_iNumAttributeId = _count;
	m_pMaterialArray.resize(_count, nullptr);
	m_pTextureArray.resize(_count, nullptr);

}

size_t GRenderableObject::getAttributeCount() const
{
	return m_iNumAttributeId;
}

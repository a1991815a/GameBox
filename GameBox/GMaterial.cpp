#include "GMaterial.h"
#include "DXUtils.h"

GMaterial::GMaterial()
	:m_pMaterial(nullptr)
{

}

GMaterial::~GMaterial()
{

}

GMaterial* GMaterial::createWithName(const std::string& name)
{
	GMaterial* ret = nullptr;
	if(ret && ret->init(name))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

bool GMaterial::init()
{

	return true;
}

bool GMaterial::init(const std::string& name)
{

	return true;
}

void GMaterial::setDiffuse(const D3DXCOLOR* color)
{
	if(m_pMaterial)
		m_pMaterial->Diffuse = *color;
}

void GMaterial::setAmbient(const D3DXCOLOR* color)
{
	if(m_pMaterial)
		m_pMaterial->Ambient = *color;
}

void GMaterial::setSpecular(const D3DXCOLOR* color, float power)
{
	if(m_pMaterial)
	{
		m_pMaterial->Specular = *color;
		m_pMaterial->Power = power;
	}
}

void GMaterial::setEmissive(const D3DXCOLOR* color)
{
	if(m_pMaterial)
		m_pMaterial->Emissive = *color;
}

void GMaterial::setupMaterial() const
{
	if(m_pMaterial)
		dxGetDevice()->SetMaterial(m_pMaterial);
}

void GMaterial::setupMaterial_Safe() const
{
	if (this == nullptr)
		return;
	if (m_pMaterial)
		dxGetDevice()->SetMaterial(m_pMaterial);
}

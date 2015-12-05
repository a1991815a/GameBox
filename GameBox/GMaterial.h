#ifndef __GMATERIAL__
#define __GMATERIAL__
#include "GameHeader.h"
#include "Ref.h"

class GMaterial: public Ref{
public:
	GMaterial();
	~GMaterial();
	CREATE_FUNC(GMaterial);
	static GMaterial* createWithName(const std::string& name);
	bool init();
	bool init(const std::string& name);

	void setDiffuse(const D3DXCOLOR* color);
	void setAmbient(const D3DXCOLOR* color);
	void setSpecular(const D3DXCOLOR* color, float power);
	void setEmissive(const D3DXCOLOR* color);

	void setupMaterial() const;
	void setupMaterial_Safe() const;
private:
	D3DMATERIAL9*		m_pMaterial;
};
#endif
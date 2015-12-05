#ifndef __GTERRIAN__
#define __GTERRIAN__
#include "GRenderableObject.h"

class GTerrian: public GRenderableObject{
public:
	GTerrian() 
		:GRenderableObject(GT_TERRIAN)
	{};

	bool init(
		float cx, float cz, 
		size_t xCount, size_t zCount, 
		size_t texFactor,
		float xOffset = 0, float zOffset = 0,
		float height = 0);

	void setHeight(float height);
	inline Size getTerrianSize() const { return m_size; };
	inline float getHeight() const { return m_fHeight; };
	inline size_t getRowCount() const { return m_iRow; };
	inline size_t getColCount() const { return m_iCol; };
private:
	Size			m_size;					//���γߴ�
	float			m_fHeight;				//��͸߶�
	size_t			m_iRow;					//��������
	size_t			m_iCol;					//��������
};
#endif
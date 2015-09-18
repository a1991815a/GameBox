#ifndef __GVIEW__
#define __GVIEW__
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Ref.h"
#include "Vec.h"
#include "Color.h"
#include "GuiBase.h"

class GView: public GuiBase, public Ref{
public:
	
	void setBgColor(const Color4f& color);
	void setBgColor(float r, float g, float b, float a);
	Color4f getBgColor() const;

private:
	IDirect3DSwapChain9* m_d3SwapChain;
	Rect m_rRect;
	D3DCOLOR m_d3cBgColor;

};
#endif
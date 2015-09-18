#ifndef __GUIDEFINETYPES__
#define __GUIDEFINETYPES__
#include <windows.h>
#include "utils/GString.h"
#include "utils/Value.h"
#include "Vec.h"
#include "Color.h"
#include "GuiBase.h"

class GWnd;

struct GBWindowStyle{
	Vec2 pos;
	Size size;
	DWORD exStyle;
	DWORD dwStyle;
	GString caption;
	HCURSOR hCursor;
	Color4f bkColor;
	HICON hIcon;
	HICON hIconSm;
	GWnd* pParent;
};




#endif
#ifndef __GWND__
#define __GWND__
#include <windows.h>
#include "Ref.h"
#include "GuiBase.h"
#include "Vec.h"
#include "GuiDefineTypes.h"

class GWnd: public GuiBase, public Ref{
public:
	GWnd(GuiObjId id);
	~GWnd();
protected:
	HWND m_hWnd;
	gb_msg LRESULT OnEvent(UINT message, WPARAM wParam, LPARAM lParam);

	gb_msg void OnPrepareStyle(GBWindowStyle& style){};					//窗口样式准备
	gb_msg void OnCreate(){};											//窗口创建和销毁事件
	gb_msg void OnDestroy(){};
	gb_msg void OnClose(){};

	gb_msg void OnChar(char key){};										//输入事件

	gb_msg void OnKeyDown(char key){};									//按键事件
	gb_msg void OnKeyUp(char key){};

	gb_msg void OnLButtonDblClk(const Vec2& point){};					//鼠标事件
	gb_msg void OnMButtonDblClk(const Vec2& point){};
	gb_msg void OnRButtonDblClk(const Vec2& point){};

	gb_msg void OnLButtonDown(const Vec2& point){};
	gb_msg void OnMButtonDown(const Vec2& point){};
	gb_msg void OnRButtonDown(const Vec2& point){};

	gb_msg void OnLButtonUp(const Vec2& point){};
	gb_msg void OnMButtonUp(const Vec2& point){};
	gb_msg void OnRButtonUp(const Vec2& point){};

	gb_msg void OnMouseWheel(){};
	gb_msg void OnMouseMove(const Vec2& point){};
	gb_msg void OnMouseMoveIn(const Vec2& point){};

	gb_msg void OnMMoveInWhenLBDown(const Vec2& point){};

	gb_msg void OnSysCommand(WPARAM wParam, LPARAM lParam){};			//系统命令事件
	gb_msg void OnCommand(WPARAM wParam, LPARAM lParam){};

	gb_msg void OnCloseClick(){};										//点击关闭
	gb_msg void OnMaxBoxClick(){};
	gb_msg void OnMinBoxClick(){};
};
#endif
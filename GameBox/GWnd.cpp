#include "GWnd.h"

GWnd::GWnd(GuiObjId id)
	:GuiBase(GT_GWND, id)
{

}

GWnd::~GWnd()
{

}

LRESULT GWnd::OnEvent(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message){
	case WM_CREATE:
		OnCreate();
		break;
	case WM_DESTROY:
		OnDestroy();
		break;
	case WM_CLOSE:
		OnClose();
		break;
	case WM_CHAR:
		OnChar(wParam);
		break;
	case WM_KEYDOWN:
		OnKeyDown(wParam);
		break;
	case WM_KEYUP:
		OnKeyUp(wParam);
		break;
	case WM_LBUTTONDBLCLK:
		OnLButtonDblClk(Vec2(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_MBUTTONDBLCLK:
		OnMButtonDblClk(Vec2(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_RBUTTONDBLCLK:
		OnRButtonDblClk(Vec2(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_LBUTTONDOWN:
		OnLButtonDown(Vec2(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_MBUTTONDOWN:
		OnMButtonDown(Vec2(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_RBUTTONDOWN:
		OnRButtonDown(Vec2(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_LBUTTONUP:
		OnLButtonUp(Vec2(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_MBUTTONUP:
		OnMButtonUp(Vec2(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_RBUTTONUP:
		OnRButtonUp(Vec2(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_MOUSEMOVE:
		OnMouseMove(Vec2(LOWORD(lParam), HIWORD(lParam)));
		break;
	case WM_MOUSEWHEEL:
		OnMouseWheel();
		break;
	case WM_SYSCOMMAND:
		OnSysCommand(wParam, lParam);
		break;
	case WM_COMMAND:
		OnCommand(wParam, lParam);
		break;
	default:
		return DefWindowProcA(m_hWnd, message, wParam, lParam);
	}


	return 0;
}

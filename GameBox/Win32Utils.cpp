#include "Win32Utils.h"
#include <assert.h>
#include "utils\GString.h"

Win32Utils* Win32Utils::m_instance = nullptr;

Win32Utils::Win32Utils()
	:m_hWnd(nullptr), m_width(0), m_height(0)
{

}

Win32Utils::~Win32Utils()
{

}


Win32Utils* Win32Utils::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new Win32Utils();
	return m_instance;
}

void Win32Utils::destroyInstance()
{
	if (m_instance) {
		delete m_instance;
		m_instance = nullptr;
	}
}




HWND Win32Utils::createWindow(const char* wind_text, int width, int height)
{
	WNDCLASSEXA wnd_class = { 0 };
	wnd_class.cbSize = sizeof(wnd_class);
	wnd_class.hInstance = GetModuleHandleA(nullptr);
	wnd_class.hCursor = LoadCursorFromFileA("../res/windows/pointer.cur");
	wnd_class.lpfnWndProc = Win32Utils::WndProc;
	wnd_class.lpszClassName = wind_text;
	wnd_class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	
	RegisterClassExA(&wnd_class);

	m_hWnd = ::CreateWindowExA(
		0,
		wind_text,
		wind_text,
		WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX,
		20, 20,
		width, height,
		nullptr,
		nullptr,
		GetModuleHandleA(nullptr),
		nullptr
		);

	{
		char szBuf[128];
		memset(szBuf, 0, 128);
		LPVOID lpMsgBuf;
		DWORD dw = GetLastError();
		FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(char*)&lpMsgBuf,
			0, NULL);
		sprintf_s(szBuf,
			"%d 出错信息 (出错码=%d): %s",
			"CreateDirectory", dw, lpMsgBuf);
		LocalFree(lpMsgBuf);
		//输出提示。
		OutputDebugStringA("输出错误: \n");
		OutputDebugStringA(szBuf);
	}

	assert(m_hWnd != nullptr);
	
	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	::UpdateWindow(m_hWnd);

	RECT rect;
	::GetClientRect(m_hWnd, &rect);
	m_width = rect.right - rect.left;
	m_height = rect.bottom - rect.top;
	

	return m_hWnd;
}



LRESULT CALLBACK Win32Utils::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:

		break;
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		GString text = "点击 x=";
		text += x;
		text += ",";
		text += y;
		text += "\n";
		OutputDebugStringA(text.c_str());
		POINT p = { x, y };
		ClientToScreen(hwnd, &p);
		text.clear();
		text += "屏幕坐标: x=";
		text += p.x;
		text += ", y= ";
		text += p.y;
		text += "\n";
		OutputDebugStringA(text.c_str());
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return ::DefWindowProcA(hwnd, message, wParam, lParam);
	}

	return S_OK;
}



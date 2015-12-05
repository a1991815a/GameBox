#include "Application.h"

extern bool WinCreate(HWND hwnd);
extern void WinDraw();
extern void WinDestroy();

static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto app = dxGetApp();
	for (size_t i = 0; i < app->m_vFuncVector.size(); ++i)
		if(app->m_vFuncVector.at(i)(hwnd, message, wParam, lParam))
			return 0;


	switch (message)
	{
	case WM_CREATE:
		if(!WinCreate(hwnd))
			DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		WinDestroy();
		PostQuitMessage(0);
		break;
	case WM_ACTIVATE:
		switch (wParam)
		{
		case WA_ACTIVE:
			app->SetState(AS_NORMAL);
			break;
		case WA_INACTIVE:
			app->SetState(AS_PAUSE);
			break;
		default:
			break;
		}
		break;
	default:
		return ::DefWindowProcA(hwnd, message, wParam, lParam);
	}

	return 0;
}

Application* dxGetApp()
{
	return Application::m_instance;
}

Application* Application::m_instance = nullptr;

Application::Application(const char* wnd_name, size_t x, size_t y, size_t cx, size_t cy)
{
	m_clsRect.left = x;
	m_clsRect.top = y;
	m_clsRect.right = cx;
	m_clsRect.bottom = cy;
	m_sName = wnd_name;
	m_instance = this;

	RegisteState(AS_NORMAL, BIND_STATE_FUNC(Application::RunNormal));
	RegisteState(AS_PAUSE, BIND_STATE_FUNC(Application::RunPause));
	SetState(AS_NORMAL);
}

Application::~Application()
{

}

int Application::run()
{
	WNDCLASSEXA wnd_class = { 0 };
	wnd_class.cbSize = sizeof(wnd_class);
	wnd_class.hbrBackground = nullptr;
	wnd_class.hCursor = LoadCursorA(GetModuleHandleA(nullptr), IDC_ARROW);
	wnd_class.hInstance = GetModuleHandleA(nullptr);
	wnd_class.lpfnWndProc = WndProc;
	wnd_class.lpszClassName = m_sName.c_str();
	wnd_class.style = CS_VREDRAW | CS_HREDRAW;
	
	::RegisterClassExA(&wnd_class);

	m_hWnd = CreateWindowExA(
		0,
		m_sName.c_str(),
		m_sName.c_str(),
		WS_OVERLAPPEDWINDOW,
		m_clsRect.left, m_clsRect.top, m_clsRect.right, m_clsRect.bottom,
		nullptr,
		nullptr,
		::GetModuleHandleA(nullptr),
		nullptr
		);

	::GetClientRect(m_hWnd, &m_clsRect);

	::ShowWindow(m_hWnd, SW_SHOWNORMAL);
	::UpdateWindow(m_hWnd);

	::UnregisterClassA(m_sName.c_str(), GetModuleHandleA(nullptr));

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
//		使用状态机来执行循环内容
// 		if(PeekMessageA(&msg, nullptr, 0, 0, PM_REMOVE))
// 		{
// 			TranslateMessage(&msg);
// 			DispatchMessageA(&msg);
// 		}else
// 			WinDraw();
		RunMachine((void*)&msg);
	}

	return msg.wParam;
}

const std::string& Application::getName() const
{
	return m_sName;
}

void Application::pushProcess(WinProcFunc_t func)
{
	m_vFuncVector.push_back(func);
}

void Application::RunNormal(void* msg)
{
	MSG* in_msg = (MSG*)msg;
	if (PeekMessageA(in_msg, nullptr, 0, 0, PM_REMOVE))	
	{
		TranslateMessage(in_msg);
		DispatchMessageA(in_msg);
	}
	else if(getState() != AS_PAUSE)
		WinDraw();
}

void Application::RunPause(void* msg)
{
	MSG* in_msg = (MSG*)msg;
	if (PeekMessageA(in_msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(in_msg);
		DispatchMessageA(in_msg);
	}
	else
		Sleep(1);
}

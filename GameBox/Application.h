#ifndef __APPLICATION__
#define __APPLICATION__
#include <windows.h>
#include <string>
#include <vector>

typedef bool(*WinProcFunc_t)(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class Application {
	friend Application* dxGetApp();
	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
public:
	Application(const char* wnd_name, size_t x, size_t y, size_t cx, size_t cy);
	~Application();
	int run();

	const std::string& getName() const;

	void pushProcess(WinProcFunc_t func);
private:
	HWND							m_hWnd;
	RECT							m_clsRect;
	std::string						m_sName;
	std::vector<WinProcFunc_t>		m_vFuncVector;
	static Application* m_instance;
};

Application* dxGetApp();
#endif
#ifndef __APPLICATION__
#define __APPLICATION__
#include <windows.h>
#include <string>
#include <vector>
#include "StateMachine.h"
#include "StateEnum.h"

typedef bool(*WinProcFunc_t)(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

class Application: public StateMachine {
	friend Application* dxGetApp();
	friend LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
public:
	Application(const char* wnd_name, size_t x, size_t y, size_t cx, size_t cy);
	~Application();
	//开始运行
	int run();

	//得到窗口名
	const std::string& getName() const;
	//插入消息处理函数
	void pushProcess(WinProcFunc_t func);

	void RunNormal(void* msg);
	void RunPause(void* msg);

private:
	HWND							m_hWnd;
	RECT							m_clsRect;
	std::string						m_sName;
	std::vector<WinProcFunc_t>		m_vFuncVector;
	static Application* m_instance;
};

Application* dxGetApp();
#endif
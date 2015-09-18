#ifndef __WIN32UTILS__
#define __WIN32UTILS__
#include <windows.h>

class Win32Utils{
public:
	static Win32Utils* getInstance();
	static void destroyInstance();
private:
	static Win32Utils* m_instance;
	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
	Win32Utils();
	~Win32Utils();

	HWND createWindow(const char* wind_text, int width, int height);
	void destroyWindow();
	inline HWND getWin32Window() {
		return m_hWnd;
	};

	inline int getWidth() const {
		return m_width;
	}

	inline int getHeight() const {
		return m_height;
	}
private:
	HWND m_hWnd;
	int m_width;
	int m_height;
};
#endif
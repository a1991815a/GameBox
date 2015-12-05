#ifndef __D3DXINPUTENGINE__
#define __D3DXINPUTENGINE__

#define DIRECTINPUT_VERSION 0x0800

#include "GSingleInstance.h"
#include <dinput.h>
#include <functional>


#define KEY_COUNT 256
#define MOUSEBUFFER_SIZE 32

typedef std::function<void(unsigned char)> InputKeyCallFunc_t;
typedef std::function<void(DWORD, DWORD)> InputMouseCallFunc_t;
typedef std::function<void(DWORD)> InputMouseWheelCallFunc_t;

#define _dxInputEngine		D3DXInputEngine::getInstance()

class D3DXInputEngine: public GSingleInstance<D3DXInputEngine>{
	GSingleIns(D3DXInputEngine);
public:
	void loop();

	bool Init(HWND hwnd);
	bool ReadyInputData();
	void CleanUp();

	bool getKeyState(unsigned char key) const;

	void PostKeyboardEvent() const;
	void PostMouseEvent(DWORD dwType, DWORD dwData) const;

	void AcquireKeyboard() const;
	void AcquireMouse() const;

	//注册回调
	void RegisterKeyDown(InputKeyCallFunc_t pFn);
	void RegisterKeyUp(InputKeyCallFunc_t pFn);
	void RegisterMouseButton(InputMouseCallFunc_t pFn);
	void RegisterMouseMove(InputMouseCallFunc_t pFn);
	void RegisterMouseWheel(InputMouseWheelCallFunc_t pFn);
	//注销回调
	void UnRegisterKeyDown();
	void UnRegisterKeyUp();
	void UnRegisterMouseButton();
	void UnRegisterMouseMove();
	void UnRegisterMouseWheel();
private:
	IDirectInput8*				m_pDirectInput;				//DXInput接口
	IDirectInputDevice8*		m_pKeyboardDevice;			//键盘设备
	IDirectInputDevice8*		m_pMouseDevice;				//鼠标设备
	char*						m_pPreKeyStateArray;		//上一次键盘状态
	char*						m_pCurKeyStateArray;		//本次键盘状态
	DIDEVICEOBJECTDATA*			m_pMouseBuffer;				//鼠标缓冲
	DWORD						m_dwMouseBufferCount;		//本次取得的鼠标缓冲个数


	InputKeyCallFunc_t			m_pfnKeyDown;				//按键按下回调
	InputKeyCallFunc_t			m_pfnKeyUp;					//按键弹起回调
	InputMouseCallFunc_t		m_pfnMouseButton;			//鼠标按键按下回调
	InputMouseCallFunc_t		m_pfnMouseMove;				//鼠标移动回调
	InputMouseWheelCallFunc_t	m_pfnMouseWheel;			//鼠标滚轮回调
};
#endif
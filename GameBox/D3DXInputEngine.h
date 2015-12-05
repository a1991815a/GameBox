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

	//ע��ص�
	void RegisterKeyDown(InputKeyCallFunc_t pFn);
	void RegisterKeyUp(InputKeyCallFunc_t pFn);
	void RegisterMouseButton(InputMouseCallFunc_t pFn);
	void RegisterMouseMove(InputMouseCallFunc_t pFn);
	void RegisterMouseWheel(InputMouseWheelCallFunc_t pFn);
	//ע���ص�
	void UnRegisterKeyDown();
	void UnRegisterKeyUp();
	void UnRegisterMouseButton();
	void UnRegisterMouseMove();
	void UnRegisterMouseWheel();
private:
	IDirectInput8*				m_pDirectInput;				//DXInput�ӿ�
	IDirectInputDevice8*		m_pKeyboardDevice;			//�����豸
	IDirectInputDevice8*		m_pMouseDevice;				//����豸
	char*						m_pPreKeyStateArray;		//��һ�μ���״̬
	char*						m_pCurKeyStateArray;		//���μ���״̬
	DIDEVICEOBJECTDATA*			m_pMouseBuffer;				//��껺��
	DWORD						m_dwMouseBufferCount;		//����ȡ�õ���껺�����


	InputKeyCallFunc_t			m_pfnKeyDown;				//�������»ص�
	InputKeyCallFunc_t			m_pfnKeyUp;					//��������ص�
	InputMouseCallFunc_t		m_pfnMouseButton;			//��갴�����»ص�
	InputMouseCallFunc_t		m_pfnMouseMove;				//����ƶ��ص�
	InputMouseWheelCallFunc_t	m_pfnMouseWheel;			//�����ֻص�
};
#endif
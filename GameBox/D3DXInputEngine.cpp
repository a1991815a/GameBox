#include "D3DXInputEngine.h"
#include "DXUtils.h"
#include "Application.h"
#include "GameMacro.h"

#pragma warning(push)
#pragma warning(disable:4800)
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define SAFE_UNACQUIRE(p) do {if(p) p->Unacquire();} while(0)

#define FAILED_CLEAN(RESULT) \
	if(FAILED(RESULT)){ \
	CleanUp(); \
	return false; \
	}

static bool WinProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message)
	{
	case WM_ACTIVATE:
		switch (wParam)
		{
		case WA_ACTIVE:
			_dxInputEngine->AcquireKeyboard();
			_dxInputEngine->AcquireMouse();
			break;
		case WA_INACTIVE:

			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	return false;
};

D3DXInputEngine::D3DXInputEngine()
	:m_pDirectInput(nullptr), 
	m_pKeyboardDevice(nullptr), m_pMouseDevice(nullptr),
	m_pPreKeyStateArray(nullptr), m_pCurKeyStateArray(nullptr),
	m_pMouseBuffer(nullptr), m_dwMouseBufferCount(0),
	m_pfnKeyDown(nullptr), m_pfnKeyUp(nullptr),
	m_pfnMouseButton(nullptr), m_pfnMouseMove(nullptr),
	m_pfnMouseWheel(nullptr)
{
	dxGetApp()->pushProcess(WinProcess);
}

D3DXInputEngine::~D3DXInputEngine()
{

}

void D3DXInputEngine::loop()
{
	ReadyInputData();
	PostKeyboardEvent();
	for (size_t i = 0; i < m_dwMouseBufferCount; ++i)
		PostMouseEvent(m_pMouseBuffer[i].dwOfs, m_pMouseBuffer[i].dwData);
	m_dwMouseBufferCount = 0;
}

/**
*	��ʼ����5��:
*	1>�����ӿ�:					DirectInput8Create
*	2>�����豸:					IDirectInput8::CreateDevice
*	3>�������ݸ�ʽ				IDirectInputDevice8::SetDataFormat
*	4>����Э������				IDirectInputDevice8::SetCooperativeLevel
*	5>��ÿ���Ȩ				IDirectInputDevice8::Acquire
*	6>�趨��������С(����ģʽ)	IDirectInputDevice8::SetProperty
*/
bool D3DXInputEngine::Init( HWND hwnd )
{

	//��1��
	HRESULT result = D3DERR_INVALIDCALL;
	result = DirectInput8Create(
		GetModuleHandleA(nullptr), 
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_pDirectInput,
		nullptr
		);
	FAILED_CLEAN(result);
	
	//��2��
	result = m_pDirectInput->CreateDevice(GUID_SysKeyboard, &m_pKeyboardDevice, nullptr);
	FAILED_CLEAN(result);
	result = m_pDirectInput->CreateDevice(GUID_SysMouse, &m_pMouseDevice, nullptr);
	FAILED_CLEAN(result);

	//��3��
	result = m_pKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	FAILED_CLEAN(result);
	result = m_pMouseDevice->SetDataFormat(&c_dfDIMouse2);
	FAILED_CLEAN(result);

	//��4��
	result = m_pKeyboardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	FAILED_CLEAN(result);
	result = m_pMouseDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	FAILED_CLEAN(result);

	//����������
	DIPROPDWORD dipdw = { 0 };
	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = MOUSEBUFFER_SIZE;
	result = m_pMouseDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	FAILED_CLEAN(result);

// 	//��5��
// 	result = m_pKeyboardDevice->Acquire();
// 	FAILED_CLEAN(result);
// 	result = m_pMouseDevice->Acquire();
// 	FAILED_CLEAN(result);

	//��ʼ���洢���ݵ��ڴ�ռ�
	m_pPreKeyStateArray = new char[KEY_COUNT];
	m_pCurKeyStateArray = new char[KEY_COUNT];
	m_pMouseBuffer = new DIDEVICEOBJECTDATA[MOUSEBUFFER_SIZE];
	memset(m_pPreKeyStateArray, 0, KEY_COUNT * sizeof(char));
	memset(m_pCurKeyStateArray, 0, KEY_COUNT * sizeof(char));
	memset(m_pMouseBuffer, 0, MOUSEBUFFER_SIZE * sizeof(DIDEVICEOBJECTDATA));

	return SUCCEEDED(result);
}

/**
*	��ȡӲ�����ݷ�2��:
*	1)ʵʱ��ȡ: GetDeviceState(�ܳߴ磬 ָ��)
*	2)�����ȡ: GetDeviceData(�ṹ�ߴ�, ����ָ��, ���峤��(�������), �Ƿ�Ӷ����Ƴ�)
*/
bool D3DXInputEngine::ReadyInputData()
{
	//��������״ָ̬��, ������ȡ�õ�ǰ����״̬
	char* tmp_state = m_pPreKeyStateArray;
	m_pPreKeyStateArray = m_pCurKeyStateArray;
	m_pCurKeyStateArray = tmp_state;

	HRESULT result = m_pKeyboardDevice->GetDeviceState(
		sizeof(char) * KEY_COUNT, 
		(void*)m_pCurKeyStateArray);
	if (FAILED(result))
	{
		AcquireKeyboard();
		result = m_pKeyboardDevice->GetDeviceState(
			sizeof(char) * KEY_COUNT,
			(void*)m_pCurKeyStateArray);
		GTHROW_RUNTIME(SUCCEEDED(result), "DInput Error!");
	}

	//������״̬ ����
	m_dwMouseBufferCount = MOUSEBUFFER_SIZE;
	result = m_pMouseDevice->GetDeviceData(
		sizeof(DIDEVICEOBJECTDATA),
		m_pMouseBuffer,
		&m_dwMouseBufferCount,
		0
		);

	if (FAILED(result))
	{
		m_dwMouseBufferCount = MOUSEBUFFER_SIZE;
		AcquireMouse();
		result = m_pMouseDevice->GetDeviceData(
			sizeof(DIDEVICEOBJECTDATA),
			m_pMouseBuffer,
			&m_dwMouseBufferCount,
			0
			);
		GTHROW_RUNTIME(SUCCEEDED(result), "DInput Error!");
	}

	return true;
}

void D3DXInputEngine::CleanUp()
{
	SAFE_UNACQUIRE(m_pKeyboardDevice);
	SAFE_UNACQUIRE(m_pMouseDevice);
	SAFE_RELEASE_COM(m_pKeyboardDevice);
	SAFE_RELEASE_COM(m_pMouseDevice);
	SAFE_RELEASE_COM(m_pDirectInput);
	SAFE_DELETE_ARRAY(m_pPreKeyStateArray);
	SAFE_DELETE_ARRAY(m_pCurKeyStateArray);
	SAFE_DELETE_ARRAY(m_pMouseBuffer);
}

bool D3DXInputEngine::getKeyState(unsigned char key) const {
	return m_pCurKeyStateArray[key] & 0x80;
};

void D3DXInputEngine::PostKeyboardEvent() const
{
	if (m_pfnKeyDown == nullptr)
		return;

	for (size_t i = 0; i < KEY_COUNT; ++i)
	{
		if (!(m_pPreKeyStateArray[i] & 0x80) &&
			m_pCurKeyStateArray[i] & 0x80)
			m_pfnKeyDown((unsigned char)i);
		else if (m_pPreKeyStateArray[i] & 0x80 &&
			!(m_pCurKeyStateArray[i] & 0x80))
			m_pfnKeyUp((unsigned char)i);
	}
}

void D3DXInputEngine::PostMouseEvent(DWORD dwType, DWORD dwData) const
{
	switch (dwType)
	{
	case DIMOFS_X:
	case DIMOFS_Y:
		if (m_pfnMouseMove == nullptr)
			return;
		m_pfnMouseMove(dwType, dwData);
		break;
	case DIMOFS_Z:
		if (m_pfnMouseWheel == nullptr)
			return;
		m_pfnMouseWheel(dwData);
		break;
	case DIMOFS_BUTTON0:
	case DIMOFS_BUTTON1:
	case DIMOFS_BUTTON2:
	case DIMOFS_BUTTON3:
	case DIMOFS_BUTTON4:
	case DIMOFS_BUTTON5:
	case DIMOFS_BUTTON6:
	case DIMOFS_BUTTON7:
		if (m_pfnMouseButton == nullptr)
			return;
		m_pfnMouseButton(dwType, dwData & 0x80);
		break;
	default:
		break;
	}
}

void D3DXInputEngine::AcquireKeyboard() const
{
	if (m_pKeyboardDevice)
		m_pKeyboardDevice->Acquire();
}

void D3DXInputEngine::AcquireMouse() const
{
	if (m_pMouseDevice)
		m_pMouseDevice->Acquire();
}

void D3DXInputEngine::RegisterKeyDown(InputKeyCallFunc_t pFn)
{
	m_pfnKeyDown = pFn;
}

void D3DXInputEngine::RegisterKeyUp(InputKeyCallFunc_t pFn)
{
	m_pfnKeyUp = pFn;
}

void D3DXInputEngine::RegisterMouseButton(InputMouseCallFunc_t pFn)
{
	m_pfnMouseButton = pFn;
}

void D3DXInputEngine::RegisterMouseMove(InputMouseCallFunc_t pFn)
{
	m_pfnMouseMove = pFn;
}

void D3DXInputEngine::RegisterMouseWheel(InputMouseWheelCallFunc_t pFn)
{
	m_pfnMouseWheel = pFn;
}

void D3DXInputEngine::UnRegisterKeyDown()
{
	m_pfnKeyDown = nullptr;
}

void D3DXInputEngine::UnRegisterKeyUp()
{
	m_pfnKeyUp = nullptr;
}

void D3DXInputEngine::UnRegisterMouseButton()
{
	m_pfnMouseButton = nullptr;
}

void D3DXInputEngine::UnRegisterMouseMove()
{
	m_pfnMouseMove = nullptr;
}

void D3DXInputEngine::UnRegisterMouseWheel()
{
	m_pfnMouseWheel = nullptr;
}

#pragma warning(pop)
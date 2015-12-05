#include "GEventDispatcher.h"
#include "D3DXInputEngine.h"
#include "Application.h"

#pragma warning(push)
#pragma warning(disable:4800)

static bool WinProcess(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	GEventDispatcher* _dispatcher = GEventDispatcher::getInstance();
	switch (message)
	{
	case WM_CREATE:
	{
		POINT location;
		GetCursorPos(&location);
		ScreenToClient(hwnd, &location);
		_dispatcher->m_piLocation = Point((float)location.x, (float)location.y);
	}
		break;
	default:
		break;
	}

	return false;
};

GEventDispatcher::GEventDispatcher()
{
	dxGetApp()->pushProcess(WinProcess);
	m_opEventPool.reserve(160);
	m_piLocation = m_piMouseMove = Point();
	_dxInputEngine->RegisterKeyDown(GCALLBACK_1(GEventDispatcher::ReceiveKeyDown, this));
	_dxInputEngine->RegisterKeyUp(GCALLBACK_1(GEventDispatcher::ReceiveKeyUp, this));
	_dxInputEngine->RegisterMouseButton(GCALLBACK_2(GEventDispatcher::ReceiveMouseButton, this));
	_dxInputEngine->RegisterMouseMove(GCALLBACK_2(GEventDispatcher::ReceiveMouseMove, this));
	_dxInputEngine->RegisterKeyDown(GCALLBACK_1(GEventDispatcher::ReceiveMouseWheel, this));
}

GEventDispatcher::~GEventDispatcher()
{

}

void GEventDispatcher::DispatcherAll()
{
	auto event_itor = m_vEventVector.begin();
	for (; event_itor != m_vEventVector.end(); ++event_itor)
	{
		auto itor = m_mListenerMap.begin();
		for (; itor != m_mListenerMap.end(); ++itor)
			if (itor->second->Trigger(*event_itor))
				break;
		m_opEventPool.deallocate(*event_itor);
	}
	m_vEventVector.clear();
}

void GEventDispatcher::ReadyEvent()
{
	//准备好信息
	_dxInputEngine->loop();

	//准备好按键事件
	auto itor = m_vKeyDownVector.begin();
	for (; itor != m_vKeyDownVector.end(); ++itor)
	{
		switch (*itor)
		{
		case DIMOFS_BUTTON0:
		case DIMOFS_BUTTON1:
		case DIMOFS_BUTTON2:
		case DIMOFS_BUTTON3:
		case DIMOFS_BUTTON4:
		case DIMOFS_BUTTON5:
		case DIMOFS_BUTTON6:
		case DIMOFS_BUTTON7:
			PostEvent(ET_MOUSEDOWN, *itor);
			break;
		default:
			PostEvent(ET_KEYDOWN, *itor);
			break;
		}
	}
}

void GEventDispatcher::PostEvent(int m_iEventId, DWORD m_dwParam /*= 0*/, void* m_pData /*= nullptr*/)
{
	GEvent* _event = m_opEventPool.allocate();
	if (_event == nullptr)
	{
		m_opEventPool.reserve(m_opEventPool.size() * 2);
		_event = m_opEventPool.allocate();
	}
	_event->m_iEventId = m_iEventId;
	_event->m_dwParam = m_dwParam;
	_event->m_pData = m_pData;
	m_vEventVector.push_back(_event);
}

void GEventDispatcher::PostKeyDown(DWORD wParam)
{
	auto itor = m_vKeyDownVector.begin();
	for (; itor != m_vKeyDownVector.end(); ++itor)
		if (*itor == wParam)
			return;
	m_vKeyDownVector.push_back(wParam);
}

void GEventDispatcher::PostKeyUp(DWORD wParam)
{
	auto itor = m_vKeyDownVector.begin();
	for (; itor != m_vKeyDownVector.end(); ++itor)
		if (*itor == wParam)
		{
			m_vKeyDownVector.erase(itor);
			break;
		}
	switch (wParam)
	{
	case DIMOFS_BUTTON0:
	case DIMOFS_BUTTON1:
	case DIMOFS_BUTTON2:
	case DIMOFS_BUTTON3:
	case DIMOFS_BUTTON4:
	case DIMOFS_BUTTON5:
	case DIMOFS_BUTTON6:
	case DIMOFS_BUTTON7:
		PostEvent(ET_MOUSEUP, wParam);
		break;
	default:
		PostEvent(ET_KEYUP, wParam);
		break;
	}

}

bool GEventDispatcher::getKeyState(int key)
{
	return GetAsyncKeyState(key) & 0x80;
}

void GEventDispatcher::addListener(GListener* listener)
{
	GTHROW_RUNTIME(!listener->getName().empty(), "Listener Name is Null!");
	m_mListenerMap.insert(decltype(m_mListenerMap)::value_type(listener->getName(), listener));
}

void GEventDispatcher::removeListener(const std::string& name)
{
	auto itor = m_mListenerMap.find(name);
	GTHROW_RUNTIME(itor != m_mListenerMap.end(), "The Listener is not in map!");
	m_mListenerMap.erase(itor);
}

void GEventDispatcher::removeListener(GListener* listener)
{
	auto itor = m_mListenerMap.find(listener->getName());
	GTHROW_RUNTIME(itor != m_mListenerMap.end(), "The Listener is not in map!");
	m_mListenerMap.erase(itor);
}

void GEventDispatcher::removeListener_Safe(GListener* listener)
{
	auto itor = m_mListenerMap.find(listener->getName());
	if(itor != m_mListenerMap.end())
		m_mListenerMap.erase(itor);
}

void GEventDispatcher::loop()
{
	ReadyEvent();
	DispatcherAll();
}

void GEventDispatcher::ReceiveKeyDown(unsigned char key)
{
	PostKeyDown(key);
}

void GEventDispatcher::ReceiveKeyUp(unsigned char key)
{
	PostKeyUp(key);
}

void GEventDispatcher::ReceiveMouseButton(DWORD dwType, DWORD dwData)
{
	if (dwData & 0x80)
		PostKeyDown(dwType);
	else
		PostKeyUp(dwType);
}

void GEventDispatcher::ReceiveMouseMove(DWORD dwType, DWORD dwData)
{
	switch (dwType)
	{
	case DIMOFS_X:
		m_piMouseMove.x = (float)dwData;
		break;
	case DIMOFS_Y:
		m_piMouseMove.y = (float)dwData;
		break;
	default:
		break;
	}
}

void GEventDispatcher::ReceiveMouseWheel(DWORD dwData)
{
	PostEvent(ET_WHEEL, dwData);
}

#pragma warning(pop)
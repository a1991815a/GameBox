#include "GEventDispatcher.h"
#include "D3DXInputEngine.h"
#include "Application.h"
#include "GDebugEngine.h"

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
	_dxInputEngine->RegisterMouseWheel(GCALLBACK_1(GEventDispatcher::ReceiveMouseWheel, this));
}

GEventDispatcher::~GEventDispatcher()
{

}

void GEventDispatcher::DispatcherAll()
{
	std::vector<GEvent*>::iterator event_itor = m_vEventVector.begin();
	for (; event_itor != m_vEventVector.end(); ++event_itor)
	{
		std::vector<GListener*>::iterator itor = m_mListenerVector.begin();
		for (; itor != m_mListenerVector.end(); ++itor)
		{
			if ((*itor)->Trigger(*event_itor))
				break;
// 			GLOG_INFO("Event: %d, Listener:%s \n",
// 				(*event_itor)->getEventId(), (*itor)->getName().c_str());
		}
		
		m_opEventPool.deallocate(*event_itor);
	}
	m_vEventVector.clear();
}

void GEventDispatcher::ReadyEvent()
{
	//准备好信息
	_dxInputEngine->loop();
	if (m_piMouseMove.x != 0 || m_piMouseMove.y != 0)
		PostEvent(ET_MOUSEMOVE);
}

void GEventDispatcher::PostEvent(int m_iEventId, DWORD m_dwParam /*= 0*/, void* m_pData /*= nullptr*/)
{
	GEvent* _event = m_opEventPool.allocate();
	if (_event == nullptr)
	{
		m_opEventPool.reserve(m_opEventPool.size() * 2);
		_event = m_opEventPool.allocate();
		GLOG_INFO("Pool对象池生长... \n");
	}
	_event->m_iEventId = m_iEventId;
	_event->m_dwParam = m_dwParam;
	_event->m_pData = m_pData;
	m_vEventVector.push_back(_event);
}

void GEventDispatcher::PostKeyDown(DWORD wParam)
{
	PostEvent(ET_KEYDOWN, wParam);
}

void GEventDispatcher::PostKeyUp(DWORD wParam)
{
	PostEvent(ET_KEYUP, wParam);
}

bool GEventDispatcher::getKeyState(int key)
{
	return GetAsyncKeyState(key) & 0x80;
}

void GEventDispatcher::addListener(GListener* listener)
{
	GASSERT(listener, "Listener is Null!");
	m_mListenerVector.push_back(listener);
}

void GEventDispatcher::removeListener(const std::string& name)
{
	GASSERT(name.size(), "removeListener: Name is Null!");
	auto itor = m_mListenerVector.begin();
	for (; itor != m_mListenerVector.end(); ++itor)
	{
		if ((*itor)->getName() == name)
		{
			m_mListenerVector.erase(itor);
			return;
		}
	}

	GTHROW_RUNTIME(false, "The Listener is not in Vector!");
}

void GEventDispatcher::removeListener(GListener* listener)
{
	GASSERT(listener, "removeListener: Listener is Null!");
	auto itor = m_mListenerVector.begin();
	for (; itor != m_mListenerVector.end(); ++itor)
	{
		if (*itor == listener)
		{
			m_mListenerVector.erase(itor);
			return;
		}
	}
	GTHROW_RUNTIME(false, "The Listener is not in Vector!");
}

void GEventDispatcher::removeListener_Safe(GListener* listener)
{
	GASSERT(listener, "removeListener: Listener is Null!");
	auto itor = m_mListenerVector.begin();
	for (; itor != m_mListenerVector.end(); ++itor)
	{
		if (*itor == listener)
		{
			m_mListenerVector.erase(itor);
			return;
		}
	}
}

void GEventDispatcher::removeListener_Safe(const std::string& name)
{
	GASSERT(name.size(), "removeListener: Name is Null!");
	auto itor = m_mListenerVector.begin();
	for (; itor != m_mListenerVector.end(); ++itor)
	{
		if ((*itor)->getName() == name)
		{
			m_mListenerVector.erase(itor);
			return;
		}
	}
}

void GEventDispatcher::loop()
{
	ReadyEvent();
	DispatcherAll();
	m_piMouseMove.x = m_piMouseMove.y = 0;
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
		PostEvent(ET_MOUSEDOWN, dwType);
	else
		PostEvent(ET_MOUSEUP, dwType);
}

void GEventDispatcher::ReceiveMouseMove(DWORD dwType, DWORD dwData)
{
	switch (dwType)
	{
	case DIMOFS_X:
		m_piMouseMove.x = (float)(int)dwData;
		break;
	case DIMOFS_Y:
		m_piMouseMove.y = (float)(int)dwData;
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
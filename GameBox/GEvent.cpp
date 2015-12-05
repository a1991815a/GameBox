#include "GEvent.h"
#include "GEventDispatcher.h"



GEvent::GEvent()
	:m_iEventId(0), m_dwParam(0), m_pData(nullptr)
{

}

const Point& GEvent::getLocation() const
{
	return GEventDispatcher::getInstance()->m_piLocation;
}

const Point& GEvent::getMouseMove() const
{
	return GEventDispatcher::getInstance()->m_piMouseMove;
}

bool GEvent::getKeyState(int key)
{
	return GetAsyncKeyState(key) != 0;
}

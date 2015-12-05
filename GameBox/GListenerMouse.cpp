#include "GListenerMouse.h"

GListenerMouse::GListenerMouse()
	:OnButtonDown(nullptr), OnButtonUp(nullptr), OnMouseMove(nullptr)
{

}

bool GListenerMouse::Trigger(GEvent* e)
{
	switch (e->getEventId())
	{
	case ET_MOUSEDOWN:
		LISTENER_SAFE_TRIGGER(OnButtonDown, e);
		break;
	case ET_MOUSEUP:
		LISTENER_SAFE_TRIGGER(OnButtonUp, e);
		break;
	case ET_MOUSEMOVE:
		LISTENER_SAFE_TRIGGER(OnMouseMove, e);
		break;
	default:
		break;
	}
	return false;
}

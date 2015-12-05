#include "GListenerKeyboard.h"



GListenerKeyboard::GListenerKeyboard()
	:OnKeyDown(nullptr), OnKeyUp(nullptr)
{

}

bool GListenerKeyboard::Trigger(GEvent* e)
{
	switch (e->getEventId())
	{
	case ET_KEYDOWN:
		LISTENER_SAFE_TRIGGER(OnKeyDown, e);
		break;
	case ET_KEYUP:
		LISTENER_SAFE_TRIGGER(OnKeyUp, e);
		break;
	default:
		break;
	}
	return false;
}

#ifndef __GLISTENERMOUSE__
#define __GLISTENERMOUSE__
#include "GListener.h"

class GListenerMouse: public GListener{
public:
	GListenerMouse();
	virtual bool Trigger(GEvent* e) override;

public:
	ListenerFunc_t	OnButtonDown;
	ListenerFunc_t	OnButtonUp;
	ListenerFunc_t	OnMouseMove;
};
#endif
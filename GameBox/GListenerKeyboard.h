#ifndef __GLISTENERKEYBOARD__
#define __GLISTENERKEYBOARD__
#include "GListener.h"

class GListenerKeyboard: public GListener{
public:
	GListenerKeyboard();
	virtual bool Trigger(GEvent* e) override;

public:
	ListenerFunc_t	OnKeyDown;
	ListenerFunc_t	OnKeyUp;
};
#endif
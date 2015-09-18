#ifndef __GGAMEWND__
#define __GGAMEWND__
#include "GWnd.h"

class GGameWnd: public GWnd{
public:
	


protected:
	gb_msg LRESULT OnEvent(UINT message, WPARAM wParam, LPARAM lParam);
	

};
#endif
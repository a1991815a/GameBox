#ifndef __GDEBUGENGINE__
#define __GDEBUGENGINE__
#include "GSingleInstance.h"

#define DEBUG_BUFFER_SIZE 102400

#define GLOG_DEBUG(TEXT, ...)	GDebugEngine::getInstance()->DebugLog(TEXT,##__VA_ARGS__)
#define GLOG_ERROR(TEXT, ...)	GDebugEngine::getInstance()->ErrorLog(TEXT,##__VA_ARGS__)
#define GLOG_INFO(TEXT, ...)	GDebugEngine::getInstance()->InfoLog(TEXT,##__VA_ARGS__)
#define GLOG_WARNING(TEXT, ...) GDebugEngine::getInstance()->WarningLog(TEXT,##__VA_ARGS__)

#define DEBUG_ENABLE 0x00000001

class GDebugEngine: public GSingleInstance<GDebugEngine>{
	GSingleIns(GDebugEngine);
public:
	void DebugLog(const char* text, ...);
	void ErrorLog(const char* text, ...);
	void InfoLog(const char* text, ...);
	void WarningLog(const char* text, ...);

	void TurnOn(int flag);
	void TurnOff(int flag);
private:
	char*		m_sBuf;
	int			m_bFlag;
};
#endif
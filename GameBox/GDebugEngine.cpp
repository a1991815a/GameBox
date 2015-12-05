#include "GDebugEngine.h"
#include <stdio.h>
#include <stdarg.h>
#include <memory>
#include <windows.h>

GDebugEngine::GDebugEngine()
{
	m_sBuf = new char[DEBUG_BUFFER_SIZE];
	memset(m_sBuf, 0, DEBUG_BUFFER_SIZE);
#if defined(_DEBUG)
	m_bFlag = DEBUG_ENABLE;
#else
	m_bFlag = 0;
#endif

}

GDebugEngine::~GDebugEngine()
{
	if (m_sBuf)
	{
		delete[] m_sBuf;
		m_sBuf = nullptr;
	}
}

void GDebugEngine::DebugLog(const char* text, ...)
{
	if (!(m_bFlag & DEBUG_ENABLE))
		return;
	va_list ap;
	va_start(ap, text);
	vsprintf_s(m_sBuf, DEBUG_BUFFER_SIZE, text, ap);
	va_end(ap);
	OutputDebugStringA("Debug: ");
	OutputDebugStringA(m_sBuf);
	memset(m_sBuf, 0, DEBUG_BUFFER_SIZE);
}

void GDebugEngine::ErrorLog(const char* text, ...)
{
	if (!(m_bFlag & DEBUG_ENABLE))
		return;
	va_list ap;
	va_start(ap, text);
	vsprintf_s(m_sBuf, DEBUG_BUFFER_SIZE, text, ap);
	va_end(ap);
	OutputDebugStringA("Error: ");
	OutputDebugStringA(m_sBuf);
	memset(m_sBuf, 0, DEBUG_BUFFER_SIZE);
}

void GDebugEngine::InfoLog(const char* text, ...)
{
	if (!(m_bFlag & DEBUG_ENABLE))
		return;
	va_list ap;
	va_start(ap, text);
	vsprintf_s(m_sBuf, DEBUG_BUFFER_SIZE, text, ap);
	va_end(ap);
	OutputDebugStringA("Info: ");
	OutputDebugStringA(m_sBuf);
	memset(m_sBuf, 0, DEBUG_BUFFER_SIZE);
}

void GDebugEngine::WarningLog(const char* text, ...)
{
	if (!(m_bFlag & DEBUG_ENABLE))
		return;
	va_list ap;
	va_start(ap, text);
	vsprintf_s(m_sBuf, DEBUG_BUFFER_SIZE, text, ap);
	va_end(ap);
	OutputDebugStringA("Warning: ");
	OutputDebugStringA(m_sBuf);
	memset(m_sBuf, 0, DEBUG_BUFFER_SIZE);
}

void GDebugEngine::TurnOn(int flag)
{
	m_bFlag |= flag;
}

void GDebugEngine::TurnOff(int flag)
{
	m_bFlag &= ~flag;
}

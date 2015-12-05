#include "GDebugEngine.h"
#include <stdio.h>
#include <stdarg.h>
#include <memory>
#include <windows.h>

GDebugEngine::GDebugEngine()
{
	m_sBuf = new char[DEBUG_BUFFER_SIZE];
	memset(m_sBuf, 0, DEBUG_BUFFER_SIZE);
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
	va_list ap;
	va_start(ap, text);
	vsprintf_s(m_sBuf, DEBUG_BUFFER_SIZE, text, ap);
	va_end(ap);
	OutputDebugStringA("Debug: ");
	OutputDebugStringA(text);
	memset(m_sBuf, 0, DEBUG_BUFFER_SIZE);
}

void GDebugEngine::ErrorLog(const char* text, ...)
{
	va_list ap;
	va_start(ap, text);
	vsprintf_s(m_sBuf, DEBUG_BUFFER_SIZE, text, ap);
	va_end(ap);
	OutputDebugStringA("Error: ");
	OutputDebugStringA(text);
	memset(m_sBuf, 0, DEBUG_BUFFER_SIZE);
}

void GDebugEngine::InfoLog(const char* text, ...)
{
	va_list ap;
	va_start(ap, text);
	vsprintf_s(m_sBuf, DEBUG_BUFFER_SIZE, text, ap);
	va_end(ap);
	OutputDebugStringA("Info: ");
	OutputDebugStringA(text);
	memset(m_sBuf, 0, DEBUG_BUFFER_SIZE);
}

void GDebugEngine::WarningLog(const char* text, ...)
{
	va_list ap;
	va_start(ap, text);
	vsprintf_s(m_sBuf, DEBUG_BUFFER_SIZE, text, ap);
	va_end(ap);
	OutputDebugStringA("Warning: ");
	OutputDebugStringA(text);
	memset(m_sBuf, 0, DEBUG_BUFFER_SIZE);
}

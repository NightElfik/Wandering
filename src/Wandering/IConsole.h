#pragma once
#include "ScreenBuffer.h"

class IConsole {
public:
	virtual int ReadCharUnbuffered() = 0;
	virtual bool GetWindowSize(short& outWidth, short& outHeight) = 0;
	virtual void PrintBuffer(ScreenBuffer* sb) = 0;
};
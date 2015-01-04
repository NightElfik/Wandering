#pragma once
#include "ScreenBuffer.h"

class IMenuItem {
public:
	enum Align { Left, Center, Right };

	virtual void GetSize(int& outWidth, int& outHeight) { outWidth = _width; outHeight = _height; }

	virtual bool IsFocusable() { return _isFocusable; }
	
	virtual Align GetAlign() { return _itemAlign; }

	virtual int GetYOffset() { return _yOffset; }

	virtual std::string GetHint() { return ""; }

	virtual bool KeyPressed(int key) = 0;

	virtual void PrintAt(ScreenBuffer* buffer, int x, int y) = 0;

protected:
	bool _isFocusable;
	int _yOffset, _width, _height;
	Align _itemAlign;
};
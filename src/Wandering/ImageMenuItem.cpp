#pragma once
#include <string>
#include "IMenuItem.h"
#include "AsciiFont.h"

class ImageMenuItem : public IMenuItem {
protected:
	std::string _strImage;
	void (*_action)();

public:
	ImageMenuItem(const std::string& text, void(*onPressed)() = nullptr, int yOffset = 1, bool focusable = false, Align align = Center) {
		AsciiFont::MeasureText(text, _width, _height);
		_strImage = AsciiFont::ConvertText(text);
		_itemAlign = align;
		_yOffset = yOffset;
		_isFocusable = focusable;
		_action = onPressed;
	}

	ImageMenuItem(int width, int height, std::string stringImage, void(*onPressed)() = nullptr, int yOffset = 1, bool focusable = false, Align align = Center) {
		if (width * height != stringImage.length()) {
			stringImage = "width * height != str.length";
			width = stringImage.length();
			height = 1;
		}
		_strImage = stringImage;
		_width = width;
		_height = height;
		_itemAlign = align;
		_yOffset = yOffset;
		_isFocusable = focusable;
		_action = onPressed;
	}

	~ImageMenuItem() {
		_action = nullptr;
	}

	void ChangeToAsciiArtText(const std::string& text) {
		AsciiFont::MeasureText(text, _width, _height);
		_strImage = AsciiFont::ConvertText(text);
	}

	virtual bool KeyPressed(int key) { 
		if (_action != nullptr && key == 13) {
			_action();
			return true;
		}
		return false;
	}

	virtual void PrintAt(ScreenBuffer* buffer, int x, int y) {
		for (int yStr = 0; yStr < _height; yStr++) {
			for (int xStr = 0; xStr < _width; xStr++) {
				buffer->SetCharAt(x + xStr, y + yStr, _strImage[yStr * _width + xStr]);
			}
		}
	}
};
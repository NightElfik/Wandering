#pragma once
#include "IMenuItem.h"

class TextMenuItem : public IMenuItem {
protected:
	std::string _text, _hint;
	void (*_action)();

public:
	TextMenuItem(std::string text, void(*onPressed)() = nullptr, int yOffset = 1, bool focusable = true, Align align = Center, std::string hint = "") {
		_text = text;
		_height = 1;
		_width = text.length();
		_action = onPressed;
		_itemAlign = align;
		_yOffset = yOffset;
		_isFocusable = focusable;
		_hint = hint;
	}

	~TextMenuItem() {
		_action = nullptr;
	}

	void SetText(const std::string& text) {
		_width = text.length();
		_text = text;
	}
	
	void SetCallback(void (*onPressed)()) {
		_action = onPressed;
	}

	virtual std::string GetHint() { return _hint; };

	virtual bool KeyPressed(int key) {
		if (_action != nullptr && key == 13) {
			_action();
			return true;
		}
		return false;
	}

	virtual void PrintAt(ScreenBuffer* buffer, int x, int y) {
		buffer->PrintStringAt(x, y, _text);
	}
};
#pragma once
#include "Constants.h"
#include "IMenuItem.h"

class TextBoxMenuItem : public IMenuItem {
protected:
	bool _activated, _onlyNums;
	int _cursor, _maxTextLen;
	std::string _label;
	char* _text;
	void(*_onTextChanged)();

	void textChanged() {
		if (_onTextChanged != nullptr) {
			_onTextChanged();
		}
	}

public:
	TextBoxMenuItem(std::string strLabel, std::string defaultText = "", int maxTextWidth = 20, bool allowNumbersOnly = false, int yOffset = 1, Align align = Center) {
		_label = strLabel;
		_yOffset = yOffset;
		_width = strLabel.size() + maxTextWidth + 2;
		_height = 1;
		_itemAlign = align;
		_activated = false;
		_onlyNums = allowNumbersOnly;
		_cursor = 0;
		_maxTextLen = maxTextWidth;
		_onTextChanged = nullptr;

		_text = new char[_maxTextLen];
		int i = 0;
		for (; i < defaultText.length() && i < _maxTextLen; i++) {
			_text[i] = defaultText[i];
		}
		for (; i < _maxTextLen; i++) {
			_text[i] = ' ';
		}
	}

	~TextBoxMenuItem() {
		delete[] _text;
		_text = nullptr;
	}

	void SetTextChanged(void(*onTextChanged)()) {
		_onTextChanged = onTextChanged;
	}

	std::string GetText() {
		int from = 0,
			to = _maxTextLen - 1;
		while (from < _maxTextLen && _text[from] == ' ') {
			from++;
		}

		if (from == _maxTextLen) {
			return "";
		}

		while (_text[to] == ' ') {
			to--;
		}

		return std::string(&_text[from], to - from + 1);
	}

	virtual std::string GetHint() {
		if (_activated) {
			return "press enter to stop editing";
		}
		else if (_onlyNums) {
			return "press enter to edit number";
		}
		else {
			return "press enter to edit";
		}
	}

	virtual bool KeyPressed(int key) {
		if (_activated) {
			if (key == ENTER_KEY || key == ESC_KEY) {
				_activated = false;
			}
			else if (key == SPEC_KEY_LEFT) {
				_cursor--;
			}
			else if (key == SPEC_KEY_RIGHT) {
				_cursor++;
			}
			else if (key == BACKSPACE_KEY && _cursor > 0) {
				_text[--_cursor] = ' ';
				textChanged();
			}
			else if (key == SPEC_KEY_DEL) {
				_text[_cursor++] = ' ';
				textChanged();
			}
			else if (_onlyNums) {
				if ((key >= '0' && key <= '9') || key == ' ') {
					_text[_cursor++] = key;
					textChanged();
				}
				else {
					return true;
				}
			}
			else if (key >= ' ' && key <= '~') {
				_text[_cursor++] = key;
				textChanged();
			}
			else {
				return true;
			}

			if (_cursor < 0) {
				_cursor = 0;
			}
			else if (_cursor >= _maxTextLen) {
				_cursor = _maxTextLen - 1;
			}

			return true;
		}
		else if (key == 13) {	// enter
			_activated = true;
			_cursor = 0;
			return true;
		}

		return false;
	}

	virtual void PrintAt(ScreenBuffer* buffer, int x, int y) {
		x = buffer->PrintStringAt(x, y, _label);
		buffer->SetCharAt(x++, y, _activated ? 0xAF : ' ');

		for (int i = 0; i < _maxTextLen; i++) {
			if (_activated && i == _cursor) {
				buffer->SetCharAt(x, y + 1, '~');	// curosr
			}
			buffer->SetCharAt(x++, y, _text[i]);
		}

		buffer->SetCharAt(x++, y, _activated ? 0xAE : ' ');
	}
};
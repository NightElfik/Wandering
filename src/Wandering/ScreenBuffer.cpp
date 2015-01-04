#include "ScreenBuffer.h"
#include <sstream>

ScreenBuffer::ScreenBuffer(int width, int height) {
	_wid = width;
	_hei = height;
	_buffWidth = _wid + 1; // + new line
	_buffHeight = _hei;
	_buffLen = _buffWidth * _buffHeight; // + 0 at and

	_buffer = new char[_buffLen];
	_bgPattern = "        \"]):([\"            ,ad88P`Y88ba,       ad88888' `88888ba   ,d88888P'   `Y88888b,,d888P\"'       `\"Y888b:([\"               \"])`Y88ba,         ,ad88P `88888ba     ad88888'  `Y88888b, ,d88888P'     `\"Y888b,d888P\"'   ";
	_bgPattWid = 22;
	_bgPattHei = 10;

	Clear();
}

ScreenBuffer::~ScreenBuffer() {
	_wid = _hei = _buffWidth = _buffHeight = _buffLen = -1;

	delete[] _buffer;
	_buffer = nullptr;
}

void ScreenBuffer::GetSize(int& outWidth, int& outHeight) {
	outWidth = _wid;
	outHeight = _hei;
}

char ScreenBuffer::GetCharAt(int x, int y) {
	if (x < 0 || x >= _wid || y < 0 || y >= _hei) {
		return 0;
	}

	return _buffer[y * _buffWidth + x];
}

void ScreenBuffer::SetCharAt(int x, int y, char c) {
	if (x < 0 || x >= _wid || y < 0 || y >= _hei) {
		return;
	}

	_buffer[y * _buffWidth + x] = c;
}

int ScreenBuffer::PrintStringAt(int x, int y, const std::string& str) {
	if (y < 0 || y >= _hei) {
		return x;
	}

	unsigned int i;
	if (x < 0) {
		i = -x;
		x = 0;
	}
	else {
		i = 0;
	}

	for (; i < str.length() && x < _wid; i++, x++) {
		_buffer[y * _buffWidth + x] = str[i];
	}

	return x;
}

int ScreenBuffer::PrintIntAt(int x, int y, int value) {
	std::stringstream ss;
	ss << value;
	return PrintStringAt(x, y, ss.str());
}

void ScreenBuffer::Clear() {
	for (int y = 0; y < _buffHeight; y++) {
		for (int x = 0; x < _wid; x++) {
			_buffer[y * _buffWidth + x] = _bgPattern[(y % _bgPattHei) * _bgPattWid + (x % _bgPattWid)];
		}
		_buffer[y * _buffWidth + _buffWidth - 1] = '\n';
	}
	_buffer[_buffLen - 1] = 0;
}

void ScreenBuffer::ClearArea(int x, int y, int width, int height) {
	if (x < 0) {
		width += x;
		x = 0;
	}

	if (y < 0) {
		height += y;
		y = 0;
	}

	if (x + width >= _wid) {
		width -= x + width - _wid;
	}

	if (y + height >= _hei) {
		height -= x + height - _hei;
	}

	if (width <= 0 || height <= 0) {
		return;
	}

	for (int baseY = 0; baseY < height; baseY++) {
		for (int baseX = 0; baseX < width; baseX++) {
			_buffer[(y + baseY) * _buffWidth + x + baseX] = ' ';
		}
	}
}

void ScreenBuffer::DrawBorder(int left, int top, int right, int bottom) {
	// corners
	if (left >= 0 && left < _wid && top >= 0 && top < _hei) {
		_buffer[top * _buffWidth + left] = _borderLT;
	}
	if (left >= 0 && left < _wid && bottom >= 0 && bottom < _hei) {
		_buffer[bottom * _buffWidth + left] = _borderLB;
	}
	if (right >= 0 && right < _wid && top >= 0 && top < _hei) {
		_buffer[top * _buffWidth + right] = _borderRT;
	}
	if (right >= 0 && right < _wid && bottom >= 0 && bottom < _hei) {
		_buffer[bottom * _buffWidth + right] = _borderRB;
	}

	int width = right - left,
		hright = bottom - top;

	for (int x = 1; x < width; x++) {
		SetCharAt(left + x, top, _borderH);
		SetCharAt(left + x, bottom, _borderH);
	}
	for (int y = 1; y < hright; y++) {
		SetCharAt(left, top + y, _borderV);
		SetCharAt(right, top + y, _borderV);
	}
}

void ScreenBuffer::DrawBorderWithShadow(int left, int top, int right, int bottom) {
	if (left >= 0 && left < _wid && top >= 0 && top < _hei) {
		_buffer[top * _buffWidth + left] = _borderLT;
	}
	if (left >= 0 && left < _wid && bottom >= 0 && bottom < _hei) {
		_buffer[bottom * _buffWidth + left] = _borderLB;
	}
	if (right >= 0 && right < _wid && top >= 0 && top < _hei) {
		_buffer[top * _buffWidth + right] = _borderRT;
	}
	if (right >= 0 && right < _wid && bottom >= 0 && bottom < _hei) {
		_buffer[bottom * _buffWidth + right] = _borderRB;
	}

	int width = right - left,
		hright = bottom - top;

	for (int x = 1; x < width; x++) {
		SetCharAt(left + x, top, _borderH);
		SetCharAt(left + x, bottom, _borderH);
		SetCharAt(left + x + 1, bottom + 1, _shadow);
	}
	for (int y = 1; y < hright; y++) {
		SetCharAt(left, top + y, _borderV);
		SetCharAt(right, top + y, _borderV);
		SetCharAt(right + 1, top + y + 1, _shadow);
	}

	SetCharAt(right + 1, bottom + 1, _shadow);
}

int ScreenBuffer::DrawBorderText(int x, int y, const std::string& str) {
	SetCharAt(x++, y, _arrowsLeft);
	SetCharAt(x++, y, ' ');
	x = PrintStringAt(x, y, str);
	SetCharAt(x++, y, ' ');
	SetCharAt(x++, y, _arrowsRight);
	return x;
}

// prints buffer into console
void ScreenBuffer::Flush() {
	// slowest
	//std::cout << buffer;

	// little faster
	/*for (int i = 0; i < buffLen - 1; i++)
		putchar(buffer[i]);*/

	// fastest	
	// printf is 1000x faster then cout
	printf(_buffer);
}
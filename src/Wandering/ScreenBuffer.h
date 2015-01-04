#pragma once
#include <string>

class ScreenBuffer {
private:
	static const unsigned char _borderLT = 0xC9, _borderH = 0xCD, _borderRT = 0xBB, _borderV = 0xBA, _borderRB = 0xBC, _borderLB = 0xC8,
		_arrowsLeft = 0xAE, _arrowsRight = 0xAF, _shadow = 0xB1;

	int _buffLen,	// length of buffer
		_buffWidth,	// width of buffer
		_buffHeight,	// height of buffer
		_wid, _hei;
	char* _buffer;

	std::string _bgPattern;
	int _bgPattWid, _bgPattHei;

public:
	ScreenBuffer(int width, int height);
	
	~ScreenBuffer();

	void GetSize(int& outWidth, int& outHeight);
	char GetCharAt(int x, int y);
	void SetCharAt(int x, int y, char c);
	
	int PrintStringAt(int x, int y, const std::string& str);
	
	int PrintIntAt(int x, int y, int value);

	void Clear();
	
	void ClearArea(int x, int y, int width, int height);
	
	void DrawBorder(int left, int top, int right, int bottom);

	void DrawBorderWithShadow(int left, int top, int right, int bottom);

	int DrawBorderText(int x, int y, const std::string& str);

	// prints buffer into console
	void Flush();
};
#pragma once
#include <string>

class AsciiFont {
protected:
	static const int _asciiMin = ' ', _asciiMax = '~', _count = _asciiMax - _asciiMin + 1,
		_textHeight = 8;
	static int _symbolLengths[], _prefixLength[];
	static std::string _data[], _dala[];
	
public:
	static void Initialize();

	static void MeasureText(const std::string& text, int& outAsciiWidth, int& outAsciiHeight);

	static std::string* GetData();

	static std::string ConvertText(const std::string& text);
};
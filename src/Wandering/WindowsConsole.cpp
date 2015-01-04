#include <windows.h>
#include <conio.h>
#include "IConsole.h"

class Console : public IConsole {
private:
	static const unsigned long CURSOR_OFF = 1,
		CURSOR_ON = 2;
	HANDLE _stdOutHandle;

	bool setCursorState(unsigned long state) {
		CONSOLE_CURSOR_INFO CursoInfo;
		CursoInfo.dwSize = state;
		CursoInfo.bVisible = false;
		return SetConsoleCursorInfo(_stdOutHandle, &CursoInfo) != 0;
	}

	void setCursorPosition(short x, short y) {
		COORD position = { x, y };
		SetConsoleCursorPosition(_stdOutHandle, position);
	}

public:
	Console() {
		_stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		//setCursorState(CURSOR_OFF);
	}

	~Console() {
		//setCursorState(CURSOR_ON);
		_stdOutHandle = INVALID_HANDLE_VALUE;
	}

	virtual int ReadCharUnbuffered() {
		return _getch();
	}

	virtual bool GetWindowSize(short& outWidth, short& outHeight) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(_stdOutHandle, &csbi)) {
			return false;
		}

		outWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
		outHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
		return true;
	}

	virtual void PrintBuffer(ScreenBuffer* sb) {
		setCursorPosition(0, 0);
		sb->Flush();
	}
};
#pragma once
#include <vector>
#include "ScreenBuffer.h"

class IScreen;

class ScreenManager {
private:
	std::vector<IScreen*> _screens;

public:
	void AddScreen(IScreen* screen);
	void RemoveTopScreen();
	int GetScreensCount() { return _screens.size(); }

	bool KeyPressed(int key);
	void PrintScreens(ScreenBuffer* screenBuff);
};

class IScreen {
protected:
	ScreenManager* _screenManager;
	bool _renderLower;

public:
	IScreen() { _screenManager = nullptr; }

	virtual ScreenManager* GetScreenManager() { return _screenManager; }
	virtual void SetScreenManager(ScreenManager* manager) { _screenManager = manager; }

	virtual bool RenderLowerScreens() { return _renderLower; }

	virtual bool KeyPressed(int key) = 0;

	virtual void Print(ScreenBuffer* buffer) = 0;
};
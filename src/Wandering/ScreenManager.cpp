#include "ScreenManager.IScreen.h"

void ScreenManager::AddScreen(IScreen* screen) {
	_screens.push_back(screen);
	screen->SetScreenManager(this);
}

void ScreenManager::RemoveTopScreen() {
	_screens.pop_back();
}

bool ScreenManager::KeyPressed(int key) {
	return (*_screens.rbegin())->KeyPressed(key);
	/*list<IScreen*>::reverse_iterator it = screens.rbegin(),
		endIt = screens.rend();

	for (; it != endIt; it++) {
		if ((*it)->KeyPressed(key)) {
			return true;
		}
	}

	return false;*/
}

void ScreenManager::PrintScreens(ScreenBuffer* screenBuff) {
	int i = _screens.size() - 1;
	for (; i >= 0; i--) {
		if (!_screens[i]->RenderLowerScreens()) {
			break;
		}
	}

	for (; i < _screens.size(); i++) {
		_screens[i]->Print(screenBuff);
	}
}
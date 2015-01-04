#pragma once
#include <vector>
#include "Constants.h"
#include "IMenuItem.h"
#include "ScreenManager.IScreen.h"

class MenuScreen : public IScreen {
protected:
	std::vector<IMenuItem*> _menuItems;
	int _itemCount,
		_selectedItem;
	bool _shadow;

public:
	MenuScreen(bool renderLowerScreens = false, bool withShadow = false) {
		_itemCount = 0;
		_selectedItem = -1;
		_shadow = withShadow;
		_renderLower = renderLowerScreens;
	}

	void SetSelectedItemIndex(int index) {
		_selectedItem = index;
		while (!_menuItems[_selectedItem]->IsFocusable()) {
			_selectedItem = (_selectedItem + 1) % _itemCount;
		}
	}

	void AddMenuItem(IMenuItem* menuItem) {
		_menuItems.push_back(menuItem);

		if (_selectedItem < 0 && menuItem->IsFocusable())
			_selectedItem = _itemCount;

		_itemCount++;
	}

	virtual bool KeyPressed(int key) {
		if (_menuItems[_selectedItem]->KeyPressed(key)) {
			return true;
		}

		switch (key) {
			case 'w':
			case 'W':
			case 'a':
			case 'A':
			case SPEC_KEY_LEFT:
			case SPEC_KEY_UP:
				do {
					_selectedItem = (_selectedItem + _itemCount - 1) % _itemCount;
				} while (!_menuItems[_selectedItem]->IsFocusable());
				return true;

			case 's':
			case 'S':
			case 'd':
			case 'D':
			case SPEC_KEY_RIGHT:
			case SPEC_KEY_DOWN:
				do {
					_selectedItem = (_selectedItem + 1) % _itemCount;
				} while (!_menuItems[_selectedItem]->IsFocusable());
				return true;

			case BACKSPACE_KEY:
			case ESC_KEY:
				if (_screenManager->GetScreensCount() > 1) {
					_screenManager->RemoveTopScreen();
				}
				else {
					_selectedItem = _itemCount - 1;
					while (!_menuItems[_selectedItem]->IsFocusable()) {
						_selectedItem = (_selectedItem + _itemCount - 1) % _itemCount;
					}
					_menuItems[_selectedItem]->KeyPressed(13);
				}
		}

		return false;
	}

	virtual void Print(ScreenBuffer* buffer) {
		static int marginX = 3,
			marginY = 1;
		int buffWid, buffHei, itemWid, itemHei,
			itemsHeight = 0, itemsMaxWidth = 0;
		buffer->GetSize(buffWid, buffHei);

		for (int i = 0; i < _itemCount; i++) {
			_menuItems[i]->GetSize(itemWid, itemHei);
			itemsHeight += itemHei + _menuItems[i]->GetYOffset();
			if (itemWid > itemsMaxWidth)
				itemsMaxWidth = itemWid;
		}

		int boxWid = itemsMaxWidth + 2 * marginX,
			boxHei = itemsHeight + 2 * marginY,
			x = (buffWid - boxWid) / 2,
			y = (buffHei - boxHei) / 2;

		buffer->ClearArea(x, y, boxWid, boxHei);
		if (_shadow) {
			buffer->DrawBorderWithShadow(x - 1, y - 1, x + boxWid, y + boxHei);
		}
		else {
			buffer->DrawBorder(x - 1, y - 1, x + boxWid, y + boxHei);
		}

		int currY = y + marginY;
		for (int i = 0; i < _itemCount; i++) {
			int itemWid, itemHei, itemX;
			_menuItems[i]->GetSize(itemWid, itemHei);

			IMenuItem::Align mAl = _menuItems[i]->GetAlign();
			if (mAl == IMenuItem::Left) {
				itemX = x + marginX;
			}
			else if (mAl == IMenuItem::Center) {
				itemX = x + (boxWid - itemWid) / 2;
			}
			else {
				itemX = x + (boxWid - itemWid) - marginX;
			}

			_menuItems[i]->PrintAt(buffer, itemX, currY);

			if (_selectedItem == i) {
				int lX = itemX - 2, rX = itemX + itemWid + 1, tY = currY - 1, bY = currY + itemHei;
				buffer->SetCharAt(lX, tY, (char)0xDA);
				buffer->SetCharAt(rX, tY, (char)0xBF);
				for (int j = 0; j < itemHei; j++) {
					buffer->SetCharAt(lX, currY + j, (char)0xB3);
					buffer->SetCharAt(rX, currY + j, (char)0xB3);
				}
				buffer->SetCharAt(lX, bY, (char)0xC0);
				buffer->SetCharAt(rX, bY, (char)0xD9);
			}

			currY += itemHei + _menuItems[i]->GetYOffset();;
		}

		std::string strHint = _menuItems[_selectedItem]->GetHint();
		if (strHint.length() > 0) {
			buffer->DrawBorderText(x + 1, y + boxHei, strHint);
		}
	}
};
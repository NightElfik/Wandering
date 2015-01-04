#pragma once
#include "Constants.h"
#include "MazeScreen.cpp"
#include "ScreenManager.IScreen.h"

class SplitScreen : public IMazeScreen {
private:
	MazeScreen *_left, *_right;

	void reset(bool left = true, bool right = true) {
		if (left) {
			_left->ResetGame();
		}

		if (right) {
			_right->ResetGame();
		}
	}

public:
	SplitScreen(void(*onMenu)(), void(*onLeftVictory)(), void(*onRightVictory)(), char player1Char = 0x01, char player2Char = 0x02) {
		_renderLower = false;
		_left = new MazeScreen(onMenu, onLeftVictory, player1Char);
		_right = new MazeScreen(nullptr, onRightVictory, player2Char);
	}

	~SplitScreen() {
		if (_left != nullptr) {
			delete _left;
			_left = nullptr;
		}

		if (_right != nullptr) {
			delete _right;
			_right = nullptr;
		}
	}

	virtual void Initialize(IMaze* iMaze) {
		_left->Initialize(iMaze);
		_right->Initialize(iMaze, false);

		if (iMaze != nullptr) {
			reset(false, false);
		}
	}

	virtual void ResetGame() {
		reset();
	}

	virtual void RegenerateMazeAndReset()  {
		_left->RegenerateMazeAndReset();
		_right->SetShortestWayLen(_left->GetShortestWayLen());
		_right->ResetGame();
	}

	virtual void ShowHint(int steps) {
		_left->ShowHint(steps);
		_right->ShowHint(steps, false);
	}

	virtual bool KeyPressed(int key) {
		switch (key) {
			case SPEC_KEY_UP:
			case SPEC_KEY_RIGHT:
			case SPEC_KEY_DOWN:
			case SPEC_KEY_LEFT:
				return _right->KeyPressed(key);

			default:
				return _left->KeyPressed(key);
		}
	}

	virtual void Print(ScreenBuffer* buffer) {
		int buffWid, buffHei;
		buffer->GetSize(buffWid, buffHei);
		int y = 0, hei = buffHei,
			leftX = 0, leftWid = buffWid / 2 + 1,
			rightX = leftWid - 1,
			rightWid = buffWid - rightX;

		_left->Print(buffer, leftX, y, leftWid, hei);
		_right->Print(buffer, rightX, y, rightWid, hei);

		int lpx, lpy, rpx, rpy;
		_left->GetPlayerWorldCoords(lpx, lpy);
		_right->GetPlayerWorldCoords(rpx, rpy);
		if (lpx != rpx || lpy != rpy) {
			_left->WorldCoordsToLocal(rpx, rpy, rpx, rpy);
			_right->WorldCoordsToLocal(lpx, lpy, lpx, lpy);

			lpx += rightX;

			if (rpx > leftX && rpx + 1 < leftX + leftWid && rpy > y && rpy + 1 < y + hei) {
				buffer->SetCharAt(leftX + rpx, y + rpy, _right->GetPlayerChar());
			}

			if (lpx > rightX && lpx + 1 < rightX + rightWid && lpy > y && lpy + 1 < y + hei) {
				buffer->SetCharAt(lpx, y + lpy, _left->GetPlayerChar());
			}
		}

		// border fix
		buffer->SetCharAt(rightX, y, (char)0xCB);
		buffer->SetCharAt(rightX, y + hei - 1, (char)0xCA);
	}

	virtual bool Save(const std::string& filePath) {
		return false;
	}

	virtual bool Load(const std::string& filePath) {
		return false;
	}

	virtual bool ExportToFile(const std::string& filePath) {
		return false;
	}
};
#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Constants.h"
#include "AsciiFont.h"
#include "IMazeScreen.h"
#include "SpecialMaze.cpp"
#include "RecursiveBacktrackerMazeSolver.cpp"
#include "RecursiveBacktrackerMazeGenerator.cpp"

class MazeScreen : public IMazeScreen {
private:
	static const unsigned char arrowsLeft = 0xAE, arrowsRight = 0xAF;
	std::string _stepsLabel;

	int _playerX, _playerY, _playerCellId,
		_endCellId,
		_cameraX, _cameraY,
		_steps, _shortestWay, _cnt,
		_mazeWid, _mazeHei;
	char _player;
	bool _win;

	void(*_onVictory)();
	void(*_onMenu)();
	IMaze* _maze;


	void refreshCamera(int wid, int hei) {
		_cameraX = refreshCameraCoord(_cameraX, _playerX, wid, _mazeWid);
		_cameraY = refreshCameraCoord(_cameraY, _playerY, hei, _mazeHei);
	}

	int refreshCameraCoord(int camera, int player, int screenSize, int mazeSize) {
		if (mazeSize <= screenSize) {
			return camera = (mazeSize - screenSize) / 2;
		}

		int diff = camera + screenSize / 2 - player,
			maxDiff = screenSize / 4;

		if (diff > maxDiff) {
			camera -= diff - maxDiff;
		}
		else if (diff < -maxDiff) {
			camera -= diff + maxDiff;
		}

		if (camera < -1) {
			return -1;
		}

		if (camera + screenSize >= mazeSize) {
			return mazeSize - screenSize + 1;
		}

		return camera;
	}

	void refreshPlayerPosition() {
		int newCellId = _maze->GetCellIdByCoords(_playerX, _playerY);
		if (newCellId != _playerCellId) {
			_playerCellId = newCellId;
			_steps++;
		}

		if (_playerCellId == _endCellId) {
			_win = true;
			_onVictory();
		}
	}

	void reset(bool dontResetPlayer = false) {
		if (!dontResetPlayer) {
			_playerCellId = _maze->GetStartCellId();
			_steps = 0;
		}
		_win = false;
		_maze->GetAsciiSize(_mazeWid, _mazeHei);
		_maze->GetCoordsbyCellId(_playerCellId, _playerX, _playerY);
		_endCellId = _maze->GetEndCellId();
	}

	void recountShortestWay() {
		RecursiveBacktrackerMazeSolver rbms;
		std::vector<int> path;
		_maze->ResetCellMarked(false);

		_shortestWay = rbms.Solve(_maze, _maze->GetStartCellId(), _endCellId) - 1;
	}

public:
	MazeScreen(void(*onMenu)(), void(*onVictory)(), char playerChar = 0x01) {
		_renderLower = false;
		_onMenu = onMenu;
		_onVictory = onVictory;
		_stepsLabel = "steps: ";
		_player = playerChar;
		_maze = nullptr;
	}

	void GetPlayerWorldCoords(int& outX, int& outY) {
		outX = _playerX;
		outY = _playerY;
	}

	void WorldCoordsToLocal(int worldX, int worldY, int& outLocalX, int& outLocalY) {
		outLocalX = worldX - _cameraX;
		outLocalY = worldY - _cameraY;
	}

	char GetPlayerChar() {
		return _player;
	}

	int GetShortestWayLen() {
		return _shortestWay;
	}

	void SetShortestWayLen(int length) {
		_shortestWay = length;
	}

	virtual void Initialize(IMaze* iMaze) {
		if (_maze != nullptr) {
			delete _maze;
			_maze = nullptr;
		}

		if (iMaze == nullptr) {
			return;
		}

		_maze = iMaze;
		_cnt = 0;
		reset();
		recountShortestWay();
	}

	void Initialize(IMaze* iMaze, bool deleteMaze){
		if (_maze != nullptr) {
			if (deleteMaze)
				delete _maze;
			_maze = nullptr;
		}

		if (iMaze == nullptr) {
			return;
		}

		_maze = iMaze;
		reset();
		recountShortestWay();
	}

	virtual void ResetGame() {
		reset();
	}

	virtual void RegenerateMazeAndReset() {
		RecursiveBacktrackerMazeGenerator rbmg;
		_maze->Initialize(true);
		rbmg.Generate(_maze);
		_cnt++;
		if (_cnt >= 8) {
			Initialize(new SpecialMaze(AsciiFont::GetData(), 112));
			return;
		}
		reset();
		recountShortestWay();
	}

	virtual void ShowHint(int steps) {
		ShowHint(steps, true);
	}

	void ShowHint(int steps, bool eraseMarking) {
		RecursiveBacktrackerMazeSolver rbms;
		std::vector<int> path;
		if (eraseMarking) {
			_maze->ResetCellMarked(false);
		}

		int n = rbms.Solve(_maze, _playerCellId, _endCellId, &path);
		for (int i = 0; i < n && i < steps; i++) {
			_maze->SetCellMarked(path[i], true);
		}
	}

	virtual bool KeyPressed(int key) {
		switch (key) {
			case 'w':	// up
			case SPEC_KEY_UP:
				if (_maze->CanPlayerStepAt(_playerX, _playerY - 1))
					_playerY--;
				break;

			case 'W':
				while (_maze->CanPlayerStepAt(_playerX, _playerY - 1) && !_win) {
					_playerY--;
					refreshPlayerPosition();
				}
				return true;

			case 'd':	// right
			case SPEC_KEY_RIGHT:
				if (_maze->CanPlayerStepAt(_playerX + 1, _playerY))
					_playerX++;
				break;

			case 'D':
				while (_maze->CanPlayerStepAt(_playerX + 1, _playerY) && !_win) {
					_playerX++;
					refreshPlayerPosition();
				}
				return true;

			case 's':	// down
			case SPEC_KEY_DOWN:
				if (_maze->CanPlayerStepAt(_playerX, _playerY + 1))
					_playerY++;
				break;

			case 'S':
				while (_maze->CanPlayerStepAt(_playerX, _playerY + 1) && !_win) {
					_playerY++;
					refreshPlayerPosition();
				}
				return true;

			case 'a':	// left	
			case SPEC_KEY_LEFT:
				if (_maze->CanPlayerStepAt(_playerX - 1, _playerY))
					_playerX--;
				break;

			case 'A':
				while (_maze->CanPlayerStepAt(_playerX - 1, _playerY) && !_win) {
					_playerX--;
					refreshPlayerPosition();
				}
				return true;

			case 'p':
			case 'P':
			case 8:	// backspace
			case 27:	// esc
				_onMenu();
				return true;

			case 'c':
			case 'C':
				_maze->ResetCellMarked(false);
				return true;

			case ' ':
				_maze->SetCellMarked(_playerCellId, !_maze->IsCellMarked(_playerCellId));
				return true;

			default:
				return false;
		}

		refreshPlayerPosition();
		return true;
	}

	virtual void Print(ScreenBuffer* buffer) {
		int buffWid, buffHei;
		buffer->GetSize(buffWid, buffHei);
		Print(buffer, 0, 0, buffWid, buffHei);
	}
	void Print(ScreenBuffer* buffer, int buffX, int buffY, int width, int height) {
		refreshCamera(width, height);
		// maze
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++)  {
				buffer->SetCharAt(x + buffX, y + buffY, _maze->GetAsciiCharAt(_cameraX + x, _cameraY + y));
			}
		}

		// player
		buffer->SetCharAt(buffX + _playerX - _cameraX, buffY + _playerY - _cameraY, _player);

		// border
		buffer->DrawBorder(buffX, buffY, buffX + width - 1, buffY + height - 1);

		int x = buffX + 2;
		buffer->SetCharAt(x++, buffY, arrowsLeft);
		buffer->SetCharAt(x++, buffY, ' ');
		x = buffer->PrintStringAt(x, buffY, _stepsLabel);
		x = buffer->PrintIntAt(x, buffY, _steps);
		buffer->SetCharAt(x++, buffY, ' ');
		buffer->SetCharAt(x++, buffY, '(');
		x = buffer->PrintIntAt(x, buffY, _shortestWay);
		buffer->SetCharAt(x++, buffY, ')');
		buffer->SetCharAt(x++, buffY, ' ');
		buffer->SetCharAt(x++, buffY, arrowsRight);
	}

	/*virtual bool Save(string filePath) {
		ofstream file(filePath);
		if (!file.is_open())
		return false;

		file << _playerCellId << endl;
		file << _steps << endl << endl;

		bool result = _maze->Save(file);

		file.close();

		return result;
		}

		virtual bool Load(string filePath) {
		ifstream file(filePath);
		string line;
		if (!file.is_open())
		return false;

		file >> _playerCellId;
		file >> _steps;
		getline(file, line);

		bool result = _maze->Load(file);

		file.close();

		if (result) {
		reset(true);
		recountShortestWay();
		}
		else {
		Initialize(nullptr);
		_screenManager->RemoveTopScreen();
		}

		return result;
		}*/

	virtual bool ExportToFile(const std::string& filePath) {
		std::ofstream file(filePath);
		if (!file.is_open()) {
			return false;
		}

		int asciiWid, asciiHei;
		_maze->GetAsciiSize(asciiWid, asciiHei);

		for (int y = 0; y < asciiHei; y++) {
			for (int x = 0; x < asciiWid; x++) {
				if (x == _playerX && y == _playerY) {
					file << '*';
				}
				else {
					file << _maze->GetAsciiCharAt(x, y);
				}
			}
			file << std::endl;
		}

		file.close();

		return true;
	}
};
#pragma once
#include <string>
#include <vector>
#include "IMaze.h"

class SpecialMaze : public IMaze {
protected:
	int _asciiWid, _asciiHei,
		_startCellId, _endCellId;

	std::string* _data;

public:
	SpecialMaze(std::string* data, int height) {
		_data = data;
		_asciiWid = 0;
		_asciiHei = height;
		for (int i = 0; i < _asciiHei; i++) {
			if (_data[i].length() > _asciiWid) {
				_asciiWid = _data[i].length();
			}
		}
		_startCellId = 0;
		_endCellId = 101 * _asciiWid + 46;
	}

	~SpecialMaze() {
		_asciiWid = _asciiHei = _startCellId = _endCellId = -1;
		_data = nullptr;
	}

	virtual void GetAsciiSize(int& outWidth, int& outHeight) {
		outWidth = _asciiWid;
		outHeight = _asciiHei;
	}

	virtual int GetStartCellId() { return _startCellId; }

	virtual int GetEndCellId() { return _endCellId; }

	virtual bool IsCellMarked(int cellId) { return false; }

	virtual void SetCellMarked(int cellId, bool marked) { }

	virtual char GetAsciiCharAt(int x, int y) {
		if (x < 0 || y < 0 || y >= _asciiHei) {
			return ' ';
		}

		std::string line = _data[y];
		if (x >= line.length()) {
			return ' ';
		}

		return line[x];
	}

	virtual void ResetCellMarked(bool marked) {	}

	virtual void GetCellIdUniverse(int& outMinId, int& outMaxId, bool& outIsContinous) {
		outMinId = 0;
		outMaxId = _asciiWid * _asciiHei;
		outIsContinous = true;
	}

	virtual int GetCellIdByCoords(int x, int y) {
		return y * _asciiWid + x;
	}

	virtual void GetCoordsbyCellId(int cellId, int& outX, int& outY) {
		outX = cellId % _asciiWid;
		outY = cellId / _asciiWid;
	}

	virtual int GetNeighboursOf(int cellId, std::vector<int>& outNeighbours) {
		return 0;
	}

	virtual int GetWalledNeighboursOf(int cellId, std::vector<int>& outNeighbours) {
		return 0;
	}

	virtual bool CanPlayerStepAt(int x, int y)  {
		return x >= 0 && x < _asciiWid && y >= 0 && y < _asciiHei;
	}

	virtual void Initialize(bool walls) { }

	virtual void SetWallStateBetween(int cellId1, int cellId2, bool wallState) { }

};
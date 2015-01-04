#pragma once
#include <vector>
#include "IMaze.h"

class RectMaze : public IMaze {
protected:
	static const int _cellWid = 3, _cellHei = 2;
	static const char _emptyCell = ' ', _emptyCellMarked = '.', _cellEnd = 3;

	enum Wall : char { Top = 0x01, Right = 0x02, Bott = 0x04, Left = 0x08, Marked = 0x10 };

	int _wid, _hei, _dataLen,
		_asciiWid, _asciiHei,
		_startCellId, _endCellId;

	char* _data;

	void init() {
		_dataLen = _wid * _hei;
		_asciiWid = _wid * _cellWid + 1;
		_asciiHei = _hei * _cellHei + 1;
		_startCellId = 0;
		_endCellId = _dataLen - 1;
		if (_data != nullptr) {
			delete[] _data;
		}
		_data = new char[_dataLen];
	}

	bool isWallAt(int x, int y, Wall wall) {
		if (x < 0) {
			if (x == -1 && y >= 0 && y < _hei && wall == Right) {
				return (_data[y * _wid] & Left) == 0 ? false : true;
			}
			return false;
		}

		if (y < 0) {
			if (y == -1 && x >= 0 && x < _wid && wall == Bott) {
				return (_data[x] & Top) == 0 ? false : true;
			}
			return false;
		}

		if (x >= _wid) {
			if (x == _wid && y >= 0 && y < _hei && wall == Left) {
				return (_data[(y + 1) * _wid - 1] & Right) == 0 ? false : true;
			}
			return false;
		}

		if (y >= _hei) {
			if (y == _hei && x >= 0 && x < _wid && wall == Top) {
				return (_data[(_hei - 1) * _wid + x] & Bott) == 0 ? false : true;
			}
			return false;
		}

		return (_data[y * _wid + x] & wall) == 0 ? false : true;
	}

	void setWallStateAt(int x, int y, Wall wall, bool state) {
		int x2, y2;
		Wall wall2;

		switch (wall) {
		case Top: x2 = x; y2 = y - 1; wall2 = Bott; break;
		case Right: x2 = x + 1; y2 = y; wall2 = Left; break;
		case Bott: x2 = x; y2 = y + 1; wall2 = Top; break;
		case Left: x2 = x - 1; y2 = y; wall2 = Right; break;
		}

		if (state) {
			_data[y * _wid + x] |= wall;
			if (x2 >= 0 && x2 < _wid && y2 >= 0 && y2 < _hei) {
				_data[y2 * _wid + x2] |= wall2;
			}
		}
		else {
			_data[y * _wid + x] &= ~wall;
			if (x2 >= 0 && x2 < _wid && y2 >= 0 && y2 < _hei) {
				_data[y2 * _wid + x2] &= ~wall2;
			}
		}
	}

	char getAsciiCharAt(int x, int y) {
		if (x < 0 || y < 0 || x >= _asciiWid || y >= _asciiHei) {
			return _emptyCell;
		}

		int mazeX = x / _cellWid,
			modX = x % _cellWid,
			mazeY = y / _cellHei,
			modY = y % _cellHei;

		if (mazeX > _wid || mazeY > _hei) {
			return _emptyCell;
		}

		if (modY == 0) {
			if (modX == 0) {
				return '+';
			}
			else {
				return isWallAt(mazeX, mazeY, Top) ? '-' : _emptyCell;
			}
		}
		else {
			if (modX == 0) {
				return isWallAt(mazeX, mazeY, Left) ? '|' : _emptyCell;
			}
			else {
				int cellId = mazeY * _wid + mazeX;
				if (cellId == _endCellId)
					return _cellEnd;
				else
					return (_data[cellId] & Marked) == 0 ? _emptyCell : _emptyCellMarked;
			}
		}
	}

public:
	RectMaze(int width, int height) {
		_wid = width;
		_hei = height;
		_data = nullptr;
		init();
	}

	~RectMaze() {
		_wid = _hei = _dataLen = _asciiWid = _asciiHei = _startCellId = _endCellId = -1;

		if (_data != nullptr) {
			delete[] _data;
			_data = nullptr;
		}
	}

	virtual void GetAsciiSize(int& outWidth, int& outHeight) {
		outWidth = _asciiWid;
		outHeight = _asciiHei;
	}

	virtual int GetStartCellId() { return _startCellId; }

	virtual int GetEndCellId() { return _endCellId; }

	virtual bool IsCellMarked(int cellId) {
		return (_data[cellId] & Marked) == 0 ? false : true;
	}

	virtual void SetCellMarked(int cellId, bool marked) {
		if (marked) {
			_data[cellId] |= Marked;
		}
		else {
			_data[cellId] &= ~Marked;
		}
	}

	virtual char GetAsciiCharAt(int x, int y) {
		return getAsciiCharAt(x, y);
	}

	virtual void ResetCellMarked(bool marked) {
		if (marked) {
			for (int i = 0; i < _dataLen; i++) {
				_data[i] |= Marked;
			}
		}
		else {
			for (int i = 0; i < _dataLen; i++) {
				_data[i] &= ~Marked;
			}
		}
	}

	virtual void GetCellIdUniverse(int& outMinId, int& outMaxId, bool& outIsContinous) {
		outMinId = 0;
		outMaxId = _dataLen - 1;
		outIsContinous = true;
	}

	virtual int GetCellIdByCoords(int x, int y) {
		return (y / _cellHei) * _wid + (x / _cellWid);
	}

	virtual void GetCoordsbyCellId(int cellId, int& outX, int& outY) {
		outX = (cellId % _wid) * _cellWid + 1;
		outY = (cellId / _wid) * _cellHei + 1;
	}

	virtual int GetNeighboursOf(int cellId, std::vector<int>& outNeighbours) {
		if (cellId < 0) {
			return 0;
		}

		int x = cellId % _wid;
		int y = cellId / _wid;

		if (y >= _hei) {
			return 0;
		}

		int n = 0;

		if (!isWallAt(x, y, Top)) {
			outNeighbours.push_back((y - 1) * _wid + x);
			n++;
		}

		if (!isWallAt(x, y, Right)) {
			outNeighbours.push_back(y * _wid + x + 1);
			n++;
		}

		if (!isWallAt(x, y, Bott)) {
			outNeighbours.push_back((y + 1) * _wid + x);
			n++;
		}

		if (!isWallAt(x, y, Left)) {
			outNeighbours.push_back(y * _wid + x - 1);
			n++;
		}

		return n;
	}

	virtual int GetWalledNeighboursOf(int cellId, std::vector<int>& outNeighbours) {
		if (cellId < 0) {
			return 0;
		}

		int x = cellId % _wid;
		int y = cellId / _wid;

		if (y >= _hei) {
			return 0;
		}

		int n = 0;

		if (y - 1 >= 0 && isWallAt(x, y, Top)) {
			outNeighbours.push_back((y - 1) * _wid + x);
			n++;
		}

		if (x + 1 < _wid && isWallAt(x, y, Right)) {
			outNeighbours.push_back(y * _wid + x + 1);
			n++;
		}

		if (y + 1 < _hei && isWallAt(x, y, Bott)) {
			outNeighbours.push_back((y + 1) * _wid + x);
			n++;
		}

		if (x - 1 >= 0 && isWallAt(x, y, Left)) {
			outNeighbours.push_back(y * _wid + x - 1);
			n++;
		}

		return n;
	}

	virtual bool CanPlayerStepAt(int x, int y)  {
		char c = getAsciiCharAt(x, y);
		return c == _emptyCell || c == _emptyCellMarked || c == _cellEnd;
	}

	virtual void Initialize(bool walls) {
		char mask;
		if (walls) {
			mask = Top | Right | Bott | Left;
		}
		else {
			mask = 0;
		}

		for (int i = 0; i < _dataLen; i++) {
			_data[i] = mask;
		}

		// border
		for (int x = 0; x < _wid; x++) {
			_data[x] |= Top;
			_data[(_hei - 1) * _wid + x] |= Bott;
		}
		for (int y = 0; y < _hei; y++) {
			_data[y * _wid] |= Left;
			_data[(y + 1) * _wid - 1] |= Right;
		}
	}

	virtual void SetWallStateBetween(int cellId1, int cellId2, bool wallState) {
		int x1 = cellId1 % _wid, y1 = cellId1 / _wid,
			x2 = cellId2 % _wid, y2 = cellId2 / _wid;

		if (std::abs(x1 - x2) + std::abs(y1 - y2) != 1) {
			return;
		}

		if (std::abs(x1 - x2) == 1) {
			if (x1 > x2) {
				setWallStateAt(x1, y1, Left, wallState);
			}
			else {
				setWallStateAt(x1, y1, Right, wallState);
			}
		}
		else {
			if (y1 > y2) {
				setWallStateAt(x1, y1, Top, wallState);
			}
			else {
				setWallStateAt(x1, y1, Bott, wallState);
			}
		}
	}

	/*virtual bool Save(ofstream& outStream) {
		outStream << _wid << endl << _hei << endl;
		for (int y = 0; y < _hei; y++)
		for (int x = 0; x < _wid; x++)
		outStream << (int)_data[y * _wid + x] << " ";

		return true;
		}

		virtual bool Load(ifstream& inStream) {
		inStream >> _wid;
		if(inStream.bad())
		return false;

		inStream >> _hei;
		if(inStream.bad())
		return false;

		init();

		for (int y = 0; y < _hei; y++)
		for (int x = 0; x < _wid; x++)
		if (inStream.bad())
		return false;
		else {
		int i;
		inStream >> i;
		_data[y * _wid + x] = (char)i;
		}

		return true;
		}*/
};
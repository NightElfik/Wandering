#pragma once
#include <vector>
#include "IMaze.h"

class HexaMaze : public IMaze {
private:
	static const char _emptyCell = ' ', _emptyCellMarked = '.', _cellEnd = 3;
	enum Wall : char { Top = 0x01, RightTop = 0x02, RightBott = 0x04, Bott = 0x08, LeftBott = 0x10, LeftTop = 0x20, Marked = 0x40 };

	char* _data;

	int _wid, _hei, _dataLen,
		_asciiWid, _asciiHei,
		_startCellId, _endCellId;

	void init() {
		_dataLen = _wid * _hei;
		_asciiWid = _wid * 6 + 2;
		_asciiHei = _hei * 4 + 3;
		_startCellId = 0;
		_endCellId = _dataLen - 1;
		if (_data != nullptr) {
			delete[] _data;
		}
		_data = new char[_dataLen];

	}

	bool isWallAt(int x, int y, Wall wall) {
		if (y < 0 && y == -1 && x >= 0 && x < _wid && wall == Bott) {
			return (_data[x] & Top) == 0 ? false : true;
		}

		if ((y < 0 || x >= _wid) && (x % 2 == 1 || y >= 0) && wall == LeftBott && x - 1 < _wid && y + (x % 2) >= 0 && y + (x % 2) < _hei && x > 0) {
			return (_data[(y + (x % 2)) * _wid + x - 1] & RightTop) == 0 ? false : true;
		}

		if ((y >= _hei || x >= _wid) && (x % 2 == 0 || x >= _wid) && wall == LeftTop && y - 1 < _hei && x - 1 < _wid && x > 0 && y - (1 - x % 2) >= 0) {
			return (_data[(y - (1 - x % 2)) * _wid + x - 1] & RightBott) == 0 ? false : true;
		}

		if (x < 0 || y < 0 || x >= _wid || y >= _hei) {
			return false;
		}

		return (_data[y * _wid + x] & wall) == 0 ? false : true;
	}

	virtual void getCellIdByCoords(int x, int y, int& outMazeX, int& outMazeY) {
		int xMod12 = x % 12, xMod6 = x % 6;
		bool even = xMod12 / 6 == 0;
		y--;
		if (!even)
			y -= 2;
		int yMod4 = y % 4;

		int mazeX = x / 6,
			mazeY = y / 4;

		if (yMod4 < 0) {
			yMod4 += 4;
			mazeY--;
		}

		if (xMod6 == 0 && yMod4 == 0) {
			mazeX--;
			if (even)
				mazeY--;
		}
		else if ((xMod6 == 0 && (yMod4 == 2 || yMod4 == 3)) || xMod6 == 1 && yMod4 == 3) {
			mazeX--;
			if (!even)
				mazeY++;
		}

		outMazeX = mazeX;
		outMazeY = mazeY;
	}

	void setWallStateAt(int x, int y, Wall wall, bool wallState) {
		if (wallState)
			_data[y * _wid + x] |= wall;
		else
			_data[y * _wid + x] &= ~wall;
	}

public:
	HexaMaze(int width, int height) {
		_wid = width;
		_hei = height;
		_data = nullptr;
		init();
	}

	~HexaMaze() {
		_wid = _hei = _dataLen = _asciiWid = _asciiHei = _startCellId = _endCellId = -1;

		if (_data != nullptr) {
			delete[] _data;
			_data = nullptr;
		}
	}

	virtual void GetAsciiSize(int& outWidth, int& outHeight) { outWidth = _asciiWid; outHeight = _asciiHei; }

	virtual int GetStartCellId() { return _startCellId; }
	virtual int GetEndCellId() { return _endCellId; }

	virtual bool IsCellMarked(int cellId) {
		return (_data[cellId] & Marked) == 0 ? false : true;
	}

	virtual void SetCellMarked(int cellId, bool marked) {
		if (marked)
			_data[cellId] |= Marked;
		else
			_data[cellId] &= ~Marked;
	}

	virtual void ResetCellMarked(bool marked) {
		if (marked)
			for (int i = 0; i < _dataLen; i++)
				_data[i] |= Marked;
		else
			for (int i = 0; i < _dataLen; i++)
				_data[i] &= ~Marked;
	}

	virtual char GetAsciiCharAt(int x, int y) {
		if (x < 0 || y < 0 || x >= _asciiWid || y >= _asciiHei)
			return _emptyCell;

		int xMod12 = x % 12, xMod6 = x % 6;
		bool even = xMod12 / 6 == 0;
		y--;
		if (!even)
			y -= 2;
		int yMod4 = y % 4;

		int mazeX = x / 6,
			mazeY = y / 4;

		if (yMod4 < 0) {
			yMod4 += 4;
			mazeY--;
		}

		if ((xMod6 == 0 && yMod4 == 1) || (xMod6 == 1 && yMod4 == 0)) {
			if (isWallAt(mazeX, mazeY, LeftTop))
				return '/';
		}
		else if ((xMod6 == 0 && yMod4 == 2) || (xMod6 == 1 && yMod4 == 3)) {
			if (isWallAt(mazeX, mazeY, LeftBott))
				return '\\';
		}
		else if (yMod4 == 3 && xMod6 > 1) {
			if (isWallAt(mazeX, mazeY, Bott))
				return '_';
		}

		if (mazeX < 0 || mazeY < 0 || mazeX >= _wid || mazeY >= _hei) {
			return _emptyCell;
		}

		if ((xMod6 == 3 || xMod6 == 4) && (yMod4 == 1 || yMod4 == 2)) {
			int cellId = mazeY * _wid + mazeX;
			if (cellId == _endCellId)
				return _cellEnd;
			else
				return (_data[cellId] & Marked) == 0 ? _emptyCell : _emptyCellMarked;
		}

		return _emptyCell;
	}

	virtual void GetCellIdUniverse(int& outMinId, int& outMaxId, bool& outIsContinous) {
		outMinId = 0;
		outMaxId = _dataLen - 1;
		outIsContinous = true;
	}

	virtual int GetCellIdByCoords(int x, int y) {
		int mazeX, mazeY;
		getCellIdByCoords(x, y, mazeX, mazeY);

		return mazeY * _wid + mazeX;
	}

	virtual void GetCoordsbyCellId(int cellId, int& outX, int& outY) {
		int mazeX = cellId % _wid,
			mazeY = cellId / _wid;

		outX = mazeX * 6 + 4;
		outY = mazeY * 2 + 2;
		if (mazeX % 2 == 1)
			outY += 2;
	}

	virtual int GetNeighboursOf(int cellId, std::vector<int>& outNeighbours) {
		if (cellId < 0)
			return 0;

		int mazeX = cellId % _wid,
			mazeY = cellId / _wid;
		bool even = mazeX % 2 == 0;

		if (mazeY >= _hei) {
			return 0;
		}

		int n = 0;

		if (!isWallAt(mazeX, mazeY, Top)) {	// y--
			outNeighbours.push_back((mazeY - 1) * _wid + mazeX);
			n++;
		}
		if (!isWallAt(mazeX, mazeY, RightTop)) {
			if (even)	// x++,  y--
				outNeighbours.push_back((mazeY - 1) * _wid + mazeX + 1);
			else	// x++
				outNeighbours.push_back(mazeY * _wid + mazeX + 1);
			n++;
		}
		if (!isWallAt(mazeX, mazeY, RightBott)) {
			if (even)	// x++
				outNeighbours.push_back(mazeY * _wid + mazeX + 1);
			else	// x++, y++
				outNeighbours.push_back((mazeY + 1) * _wid + mazeX + 1);
			n++;
		}

		if (!isWallAt(mazeX, mazeY, Bott)) {	// y++
			outNeighbours.push_back((mazeY + 1) * _wid + mazeX);
			n++;
		}
		if (!isWallAt(mazeX, mazeY, LeftBott)) {
			if (even)	// x--
				outNeighbours.push_back(mazeY * _wid + mazeX - 1);
			else	// x--, y++
				outNeighbours.push_back((mazeY + 1) * _wid + mazeX - 1);
			n++;
		}
		if (!isWallAt(mazeX, mazeY, LeftTop)) {
			if (even)	// x--, y--
				outNeighbours.push_back((mazeY - 1) * _wid + mazeX - 1);
			else	// x--
				outNeighbours.push_back(mazeY * _wid + mazeX - 1);
			n++;
		}


		return n;
	}

	virtual int GetWalledNeighboursOf(int cellId, std::vector<int>& outNeighbours) {
		if (cellId < 0) {
			return 0;
		}

		int mazeX = cellId % _wid,
			mazeY = cellId / _wid;
		bool even = mazeX % 2 == 0;

		if (mazeY >= _hei) {
			return 0;
		}

		int n = outNeighbours.size();

		if (mazeY - 1 >= 0 && isWallAt(mazeX, mazeY, Top)) {	// y--
			outNeighbours.push_back((mazeY - 1) * _wid + mazeX);
		}

		if (mazeX + 1 < _wid) {
			if (isWallAt(mazeX, mazeY, RightTop)) {
				if (even) {	// x++,  y--
					if (mazeY - 1 >= 0)
						outNeighbours.push_back((mazeY - 1) * _wid + mazeX + 1);
				}
				else	// x++
					outNeighbours.push_back(mazeY * _wid + mazeX + 1);
			}
			if (isWallAt(mazeX, mazeY, RightBott)) {
				if (even)	// x++
					outNeighbours.push_back(mazeY * _wid + mazeX + 1);
				else if (mazeY + 1 < _hei)	// x++, y++
					outNeighbours.push_back((mazeY + 1) * _wid + mazeX + 1);
			}
		}

		if (mazeY + 1 < _hei && isWallAt(mazeX, mazeY, Bott)) {	// y++
			outNeighbours.push_back((mazeY + 1) * _wid + mazeX);
		}

		if (mazeX - 1 >= 0) {
			if (isWallAt(mazeX, mazeY, LeftBott)) {
				if (even)	// x--
					outNeighbours.push_back(mazeY * _wid + mazeX - 1);
				else if (mazeY + 1 < _hei)	// x--, y++
					outNeighbours.push_back((mazeY + 1) * _wid + mazeX - 1);
			}
			if (isWallAt(mazeX, mazeY, LeftTop)) {
				if (even) {	// x--, y--
					if (mazeY - 1 >= 0)
						outNeighbours.push_back((mazeY - 1) * _wid + mazeX - 1);
				}
				else	// x--
					outNeighbours.push_back(mazeY * _wid + mazeX - 1);
			}
		}


		return outNeighbours.size() - n;
	}

	virtual bool CanPlayerStepAt(int x, int y) {
		char c = GetAsciiCharAt(x, y);
		return c == _emptyCell || c == _emptyCellMarked || c == _cellEnd;
	}

	virtual void Initialize(bool walls) {
		walls = true;	// delete after TODO

		char mask;
		if (walls) {
			mask = Top | LeftTop | LeftBott | Bott | RightBott | RightTop;
		}
		else {
			mask = 0;
		}

		for (int i = 0; i < _dataLen; i++) {
			_data[i] = mask;
		}

		// border
		// TODO... now I do not have any algorithm wich needs empty maze and adds walls
	}

	virtual void SetWallStateBetween(int cellId1, int cellId2, bool wallState) {
		int x1 = cellId1 % _wid, y1 = cellId1 / _wid,
			x2 = cellId2 % _wid, y2 = cellId2 / _wid;

		if (x1 == x2) {
			if (y1 < y2) {
				setWallStateAt(x1, y1, Bott, wallState);
				setWallStateAt(x2, y2, Top, wallState);
			}
			else {
				setWallStateAt(x1, y1, Top, wallState);
				setWallStateAt(x2, y2, Bott, wallState);

			}
			return;
		}

		if (x2 % 2 == 0) {
			std::swap(x1, x2);
			std::swap(y1, y2);
		}

		// now 1 is even
		if (y1 == y2) {
			if (x1 > x2) {
				setWallStateAt(x1, y1, LeftBott, wallState);
				setWallStateAt(x2, y2, RightTop, wallState);
			}
			else {
				setWallStateAt(x1, y1, RightBott, wallState);
				setWallStateAt(x2, y2, LeftTop, wallState);

			}
			return;
		}

		if (x1 > x2) {
			setWallStateAt(x1, y1, LeftTop, wallState);
			setWallStateAt(x2, y2, RightBott, wallState);
		}
		else {
			setWallStateAt(x1, y1, RightTop, wallState);
			setWallStateAt(x2, y2, LeftBott, wallState);

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
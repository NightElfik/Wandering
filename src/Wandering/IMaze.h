#pragma once

class IMaze {
public:
	virtual void GetAsciiSize(int& outWidth, int& outHeight) = 0;

	virtual int GetStartCellId() = 0;
	virtual int GetEndCellId() = 0;

	virtual bool IsCellMarked(int cellId) = 0;
	virtual void SetCellMarked(int cellId, bool marked) = 0;
	virtual void ResetCellMarked(bool marked) = 0;

	virtual char GetAsciiCharAt(int x, int y) = 0;

	// returns range of cell IDs and information wether between ids are unused ones or not
	virtual void GetCellIdUniverse(int& outMinId, int& outMaxId, bool& outIsContinous) = 0;

	// returns cell id from ascii coords
	virtual int GetCellIdByCoords(int x, int y) = 0;

	// returns ascii coords from
	virtual void GetCoordsbyCellId(int cellId, int& outX, int& outY) = 0;

	// returns all reachable neighbours
	virtual int GetNeighboursOf(int cellId, std::vector<int>& outNeighbours) = 0;

	// returns all neighbours wich are behind wall
	virtual int GetWalledNeighboursOf(int cellId, std::vector<int>& outNeighbours) = 0;

	// returns true if player can step at given point at ascii coords 
	virtual bool CanPlayerStepAt(int x, int y) = 0;

	// initializes maze with/without all walls
	virtual void Initialize(bool walls) = 0;
	
	// sets wall state between two neighbours
	virtual void SetWallStateBetween(int cellId1, int cellId2, bool wallState) = 0;
	
	/*virtual bool Save(std::ofstream& outStream) = 0;

	virtual bool Load(std::ifstream& inStream) = 0;*/
};
#pragma once
#include "IMaze.h"

class IMazeSolver {
public:
	virtual int Solve(IMaze* maze, int fromCellId, int toCellId, std::vector<int>* outPath = nullptr) = 0;
};
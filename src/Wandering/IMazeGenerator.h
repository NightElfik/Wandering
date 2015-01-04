#pragma once
#include "IMaze.h"

class IMazeGenerator {
public:
	virtual unsigned int GetRandomSeed() = 0;
	virtual void SetRandomSeed(unsigned int seed) = 0;

	virtual void Generate(IMaze* maze) = 0;
};
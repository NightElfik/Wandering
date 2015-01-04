#pragma once
#include "IMaze.h"
#include "ScreenManager.IScreen.h";

class IMazeScreen : public IScreen {
public:
	// initializes screen with new maze, to clear (dispose), call with nullptr
	virtual void Initialize(IMaze* iMaze) = 0;

	virtual void ResetGame() = 0;

	virtual void RegenerateMazeAndReset() = 0;

	virtual void ShowHint(int steps) = 0;

	/*virtual bool Save(cons tstd::string& filePath) = 0;

	virtual bool Load(const std::string& filePath) = 0;*/

	virtual bool ExportToFile(const std::string& filePath) = 0;
};
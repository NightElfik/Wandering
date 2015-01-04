#pragma once
#include <vector>
#include <stack>
#include "IMazeGenerator.h"


class RecursiveBacktrackerMazeGenerator : public IMazeGenerator {
private:
	unsigned int _seed;

public:
	virtual unsigned int GetRandomSeed() { return _seed; }
	virtual void SetRandomSeed(unsigned int randomSeed) { _seed = randomSeed; }

	virtual void Generate(IMaze* maze) {
		int minCellId, maxCellId;
		bool isCont;
		maze->GetCellIdUniverse(minCellId, maxCellId, isCont);

		int visitedLen = maxCellId - minCellId + 1;
		bool* visited = new bool[visitedLen];
		for (int i = 0; i < visitedLen; i++)
			visited[i] = false;

		std::stack<int> stack;
		int startId = maze->GetStartCellId();
		stack.push(startId);
		visited[startId - minCellId] = true;

		std::vector<int> nghbrs, candidates;

		while (stack.size() > 0) {
			int id = stack.top();

			nghbrs.clear();
			int nCount = maze->GetWalledNeighboursOf(id, nghbrs);

			candidates.clear();
			for (int i = 0; i < nCount; i++) {
				if (!visited[nghbrs[i] - minCellId]) {
					candidates.push_back(nghbrs[i]);
				}
			}

			if (candidates.size() == 0) {
				stack.pop();
				continue;
			}

			int rnd = rand() % candidates.size(),
				winnerId = candidates[rnd];
			visited[winnerId - minCellId] = true;
			stack.push(winnerId);

			maze->SetWallStateBetween(id, winnerId, false);
		}
	}
};
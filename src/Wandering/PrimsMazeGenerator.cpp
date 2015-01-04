#pragma once
#include <vector>
#include <list>
#include "IMazeGenerator.h"


class PrimsMazeGenerator : public IMazeGenerator {
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
		for (int i = 0; i < visitedLen; i++) {
			visited[i] = false;
		}

		std::list<int> toVisit, fromVisit;
		std::vector<int> nghbrs, candidates;

		int startId = maze->GetStartCellId();
		maze->GetWalledNeighboursOf(startId, nghbrs);
		visited[startId] = true;
		for (int i = 0; i < nghbrs.size(); i++) {
			fromVisit.push_back(startId);
			toVisit.push_back(nghbrs[i]);
			visited[nghbrs[i]] = true;
		}

		while (toVisit.size() > 0) {
			int rnd = rand() % toVisit.size();
			std::list<int>::iterator itF = fromVisit.begin(),
				itT = toVisit.begin();

			for (int i = 0; i < rnd; i++) {
				itF++;
				itT++;
			}

			int idFrom = *itF,
				idTo = *itT;

			fromVisit.erase(itF);
			toVisit.erase(itT);

			maze->SetWallStateBetween(idFrom, idTo, false);

			nghbrs.clear();
			candidates.clear();
			maze->GetWalledNeighboursOf(idTo, nghbrs);
			for (int i = 0; i < nghbrs.size(); i++) {
				if (visited[nghbrs[i]]) {
					continue;
				}
				fromVisit.push_back(idTo);
				toVisit.push_back(nghbrs[i]);
				visited[nghbrs[i]] = true;
			}
		}
	}
};
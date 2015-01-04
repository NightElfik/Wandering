#pragma once
#include <vector>
#include <stack>
#include "IMazeSolver.h"

class RecursiveBacktrackerMazeSolver : public IMazeSolver {
public:
	virtual int Solve(IMaze* maze, int fromCellId, int toCellId, std::vector<int>* outPath = nullptr) {
		std::swap(fromCellId, toCellId);
		int minCellId, maxCellId;
		bool isCont;
		maze->GetCellIdUniverse(minCellId, maxCellId, isCont);
		int visitedLen = maxCellId - minCellId + 1;
		bool* visited = new bool[visitedLen];
		for (int i = 0; i < visitedLen; i++) {
			visited[i] = false;
		}

		std::stack<int> stack;
		stack.push(fromCellId);
		visited[fromCellId - minCellId] = true;

		std::vector<int> nghbrs;

		while (stack.size() > 0) {
			int id = stack.top();

			nghbrs.clear();
			int nCount = maze->GetNeighboursOf(id, nghbrs);

			int winner;
			bool found = false;
			for (int i = 0; i < nCount; i++) {
				if (!visited[nghbrs[i] - minCellId]) {
					winner = nghbrs[i];
					found = true;
					break;
				}
			}

			if (!found) {
				stack.pop();
				continue;
			}

			if (winner == toCellId) {
				int n = stack.size() + 1;
				if (outPath == nullptr) {
					return n;
				}

				outPath->push_back(winner);

				while (stack.size() > 0) {
					outPath->push_back(stack.top());
					stack.pop();
				}

				return n;
			}

			visited[winner - minCellId] = true;
			stack.push(winner);
		}
	}
};
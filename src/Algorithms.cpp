#include "../include/Algorithms.h"
#include <unordered_set>
#include <queue>

std::vector<int> Algorithms::BFS(Graph& graph, int start) 
{
	std::vector<int> order;
	std::unordered_set<int> visited;
	std::queue<int> queue;

	queue.push(start);
	visited.insert(start);

	while (!queue.empty()) 
	{
		int current = queue.front();
		queue.pop();
		order.push_back(current);

		for (auto& neighbors : graph.GetNeighbors(current)) {
			int nodeID = neighbors.first;
			if (visited.find(nodeID) == visited.end()) {
				queue.push(nodeID);
				visited.insert(nodeID);
			}
		}
	}

	return order;
}
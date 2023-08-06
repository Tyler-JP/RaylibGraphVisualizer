#pragma once

#include <vector>
#include <map>
#include <set>

class Graph
{
public:
	Graph(bool weighted = false);
	~Graph();

	void AddNode(int node);
	void RemoveNode(int node);
	void AddEdge(int node1, int node2, double weight = 1.0);
	void RemoveEdge(int node1, int node2);

	bool HasNode(int node);
	bool HasEdge(int node1, int node2);
	double GetEdgeWeight(int node1, int node2);
	const std::vector<std::pair<int, double>>& GetNeighbors(int node);

private:
	bool weighted;
	std::map<int, std::vector<std::pair<int, double>>> adjacencyList;
};
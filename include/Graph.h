#pragma once
class Renderer;
#include "../include/Renderer.h"
#include "../include/Node.h"
#include <vector>
#include <map>
#include <set>

class Graph
{
public:
	Graph(Renderer& renderer, bool weighted = false) : renderer(renderer), weighted(weighted) { }
	~Graph();

	void AddNode(int id, float x, float y);
	void RemoveNode(int node);
	void AddEdge(int node1, int node2, double weight = 1.0);
	void RemoveEdge(int node1, int node2);

	bool HasNode(int node);
	bool HasEdge(int node1, int node2);
	double GetEdgeWeight(int node1, int node2);
	const std::vector<std::pair<int, double>>& GetNeighbors(int node);
	std::vector<Node>& GetNodes() { return nodes; }
	Node* GetNode(int id) {
		auto it = std::find_if(nodes.begin(), nodes.end(), [id](const Node& node) { return node.GetId() == id; });
		return it != nodes.end() ? &(*it) : nullptr;
	}
	const std::map<int, std::vector<std::pair<int, double>>>& GetEdges() { return adjacencyList; }
	void PrintGraph();
	


private:
	bool weighted;
	std::map<int, std::vector<std::pair<int, double>>> adjacencyList;
	Renderer& renderer;
	std::vector<Node> nodes;
};
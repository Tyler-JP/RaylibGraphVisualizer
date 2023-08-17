#include "../include/Graph.h"
#include "../include/Node.h"
#include "../include/Renderer.h"

#include <map>
#include <vector>
#include <iostream>

using namespace std;

Graph::~Graph()
{
}

void Graph::AddNode(int id, float x, float y)
{
	if (!HasNode(id))
	{
		Node node(id, x, y);
		adjacencyList[id] = vector<pair<int, double>>();
		nodes.push_back(node);
	}
}

void Graph::RemoveNode(int node)
{
	if (!HasNode(node)) {
		return;
	}

	for (auto& item : adjacencyList) {
		item.second.erase(remove_if(item.second.begin(), item.second.end(), [node](pair<int, double> edge) { return edge.first == node; }), item.second.end());
	}

	adjacencyList.erase(node);
	
}

void Graph::AddEdge(int node1, int node2, double weight)
{
	if (!HasNode(node1) || !HasNode(node2)) {
		return;
	}
	
	if (!HasEdge(node1, node2)) {
		adjacencyList[node1].push_back(make_pair(node2, weight));
		adjacencyList[node2].push_back(make_pair(node1, weight));
	}
}

void Graph::RemoveEdge(int node1, int node2)
{
	if (!HasNode(node1) || !HasNode(node2)) {
		return;
	}
	
	if (HasEdge(node1, node2)) {
		adjacencyList[node1].erase(remove_if(adjacencyList[node1].begin(), adjacencyList[node1].end(), [node2](pair<int, double> edge) { return edge.first == node2; }), adjacencyList[node1].end());
	}
}

bool Graph::HasNode(int node)
{
	return adjacencyList.find(node) != adjacencyList.end();
}

bool Graph::HasEdge(int node1, int node2)
{
	if (!HasNode(node1) || !HasNode(node2)) {
		return false;
	}

	for (auto edge : adjacencyList[node1]) {
		if (edge.first == node2) {
			return true;
		}
	}
	return false;
}

double Graph::GetEdgeWeight(int node1, int node2) 
{
	if (!HasNode(node1) || !HasNode(node2))
	{
		return 1.0;
	}

	for (auto edge : adjacencyList[node1])
	{
		if (edge.first == node2)
		{
			return edge.second;
		}
	}
	return 1.0;
}

const vector<pair<int, double>>& Graph::GetNeighbors(int node)
{
	static std::vector<std::pair<int, double>> empty;
	if (!HasNode(node)) {
		return empty;
	}

	return adjacencyList[node];
}

void Graph::PrintGraph() {
for (auto node : adjacencyList) {
		std::cout << node.first << ": ";
		for (auto edge : node.second) {
			cout << edge.first << " ";
		}
		std::cout << std::endl;
	}
}


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

void Graph::ClearGraph()
{
	adjacencyList.clear();
	nodes.clear();
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

void Graph::LoadPreset1() {
	AddNode(1, 300, 400);
	AddNode(2, 500, 600);
	AddNode(3, 500, 200);
	AddNode(4, 800, 200);
	AddNode(5, 800, 600);
	AddNode(6, 1000, 400);
	AddEdge(1, 2);
	AddEdge(1, 3);
	AddEdge(2, 5);
	AddEdge(3, 4);
	AddEdge(4, 6);
	AddEdge(5, 6);

}

void Graph::LoadPreset2() {
	AddNode(1, 300, 400);
	AddNode(2, 600, 200);
	AddNode(3, 600, 100);
	AddNode(4, 900, 400);
	AddNode(5, 1100, 600);
	AddNode(6, 600, 400);
	AddNode(7, 700, 700);
	AddEdge(1, 2);
	AddEdge(1, 3);
	AddEdge(2, 4);
	AddEdge(3, 4);
	AddEdge(4, 5);
	AddEdge(4, 6);
	AddEdge(7, 6);
	AddEdge(7, 5);
	AddEdge(7, 4);
}

void Graph::LoadPreset3() {
	AddNode(1, 400, 200);
	AddNode(2, 600, 200);
	AddNode(3, 800, 200);
	AddNode(4, 1000, 200);
	AddNode(5, 400, 400);
	AddNode(6, 600, 400);
	AddNode(7, 800, 400);
	AddNode(8, 1000, 400);
	AddNode(9, 400, 600);
	AddNode(10, 600, 600);
	AddNode(11, 800, 600);
	AddNode(12, 1000, 600);
	AddEdge(1, 2);
	AddEdge(2, 3);
	AddEdge(3, 4);
	AddEdge(1, 5);
	AddEdge(2, 6);
	AddEdge(3, 7);
	AddEdge(4, 8);
	AddEdge(5, 6);
	AddEdge(6, 7);
	AddEdge(7, 8);
	AddEdge(5, 9);
	AddEdge(6, 10);
	AddEdge(7, 11);
	AddEdge(8, 12);
	AddEdge(9, 10);
	AddEdge(10, 11);
	AddEdge(11, 12);
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


#pragma once
#include "Graph.h"
#include "Node.h"
#include <vector>
#include <string>

#define MAX_INPUT_CHARS_ADD_NODE     2

class Graph;

class Renderer
{
private:
	char nodeID[MAX_INPUT_CHARS_ADD_NODE + 1] = "\0";
	std::string nodeEdges = "";
	int nodeIDIndex = 0;

public:
	void DrawNodes(std::vector<Node>& nodes);
	void DrawNodeEdges(const int screenWidth, const int screenHeight, std::vector<Node>& nodes, Graph& graph);
	void DrawNodeInput(const int screenWidth, const int screenHeight);
	void DrawEdgeConnectionInput(const int screenWidth, const int screenHeight, std::vector<Node>& nodes);
	void DrawAddNodeButton(const int screenWidth, const int screenHeight, Graph& graph, std::vector<Node>& nodes);
	void DrawOnScreenText(const int screenWidth, const int screenHeight);
	void DraggableNode(std::vector<Node>& nodes);
	bool isNodePresentInNodeEdges(int nodeId, const std::string& nodeEdges);
};
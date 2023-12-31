#pragma once
#include "Graph.h"
#include "Node.h"
#include "raylib.h"
#include "Checkbox.h"
#include "Conditionals.h"
#include <vector>
#include <string>

#define MAX_INPUT_CHARS_ADD_NODE     2

class Graph;

class Renderer
{
private:
	char addNodeID[MAX_INPUT_CHARS_ADD_NODE + 1] = "\0";
	char delNodeID[MAX_INPUT_CHARS_ADD_NODE + 1] = "\0";
	char bfsStartNode[MAX_INPUT_CHARS_ADD_NODE + 1] = "\0";
	std::vector<int> nodeEdges;
	int addNodeIDIndex = 0;
	int delNodeIDIndex = 0;
	int bfsStartNodeIndex = 0;

public:
	static Texture2D blackNodeTexture;
	static Texture2D maroonNodeTexture;
	static Texture2D checkmarkInactiveTexture;
	static Texture2D checkmarkActiveTexture;
	void DrawNodes(std::vector<Node>& nodes);
	void DrawNodeEdges(const int screenWidth, const int screenHeight, std::vector<Node>& nodes, Graph& graph);
	void DrawNodeInput(const int screenWidth, const int screenHeight);
	void DrawNodeDeleteInput(const int screenWidth, const int screenHeight);
	void DrawEdgeConnectionInput(const int screenWidth, const int screenHeight, std::vector<Node>& nodes);
	void DrawBFSStartNodeInput(const int screenWidth, const int screenHeight, std::vector<Node>& nodes);
	void DrawAddNodeButton(const int screenWidth, const int screenHeight, Graph& graph, std::vector<Node>& nodes);
	void DrawRemoveNodeButton(const int screenWidth, const int screenHeight, Graph& graph, std::vector<Node>& nodes);
	void DrawBFSStartButton(const int screenWidth, const int screenHeight, Graph& graph, std::vector<Node>& nodes);
	void DrawOnScreenText(const int screenWidth, const int screenHeight, Conditionals activeState);
	void DrawUpdates(const int screenWidth, const int screenHeight);
	void DraggableNode(std::vector<Node>& nodes);
	void UpdateBFSAnimation(std::vector<Node>& nodes);
	bool isNodePresentInNodeEdges(int nodeId);
	void LoadNodeTexture();
	void UnloadNodeTexture();

	void SetActiveState(Conditionals state) { activeState = state; }

private:
	std::vector<int> bfsTraversalOrder;
	int currentBFSIndex = -1;
	double lastUpdateTime = 0;
	const double animationInterval = 1;
	Conditionals activeState;
};
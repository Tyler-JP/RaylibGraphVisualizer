#include "../include/Renderer.h"
#include "../include/Graph.h"
#include "../include/Node.h"
#include "../include/raylib.h"
#include "../include/ResourceLoader.h"
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <sstream>
#include <iostream>


using namespace std;

void Renderer::LoadNodeTexture() {
	blackNodeTexture = ResourceLoader::LoadTextures("assets/images/blacknode.png");
}

void Renderer::UnloadNodeTexture() {
	UnloadTexture(blackNodeTexture);
}

void Renderer::DrawNodes(std::vector<Node>& nodes)
{
	for (const auto& node : nodes) {
		Vector2 pos = { node.GetX(), node.GetY() };
		DrawTexture(blackNodeTexture, pos.x - blackNodeTexture.width / 2, pos.y - blackNodeTexture.height / 2, WHITE);
		if (node.GetId() >= 10) { // change text position for single & multi digit
			DrawText(TextFormat("%d", node.GetId()), node.GetX() - 10, node.GetY() - 10, 20, WHITE); 
		}
		else {
			DrawText(TextFormat("%d", node.GetId()), node.GetX() - 5, node.GetY() - 10, 20, WHITE);
		}
	}
}

void Renderer::DrawNodeEdges(const int screenWidth, const int screenHeight, std::vector<Node>& nodes, Graph& graph) {
	for (const auto& node : nodes) {
		Vector2 pos = { node.GetX(), node.GetY() };
		int nodeId = node.GetId();
		const auto& neighbors = graph.GetNeighbors(nodeId);
		for (const auto& neighbor : neighbors) {
			Node* neighborNode = graph.GetNode(neighbor.first);
			if (neighborNode) {
				Vector2 edgePos = { neighborNode->GetX(), neighborNode->GetY() };
				DrawLineEx(pos, edgePos, 2.0f, BLACK);
			}
		}
	}
}	

void Renderer::DrawNodeInput(const int screenWidth, const int screenHeight)
{
	Rectangle textBox = { screenWidth / 4.0f - 140, screenHeight / 1.1f + 30, 85, 35 };
	DrawRectangleRounded(textBox, 0.2, 4, LIGHTGRAY);

	if (CheckCollisionPointRec(GetMousePosition(), textBox))
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		int key = GetKeyPressed();
		DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, RED);
		while (key > 0)
		{
			if (key >= 48 && key <= 57 && (addNodeIDIndex < MAX_INPUT_CHARS_ADD_NODE))
			{
				addNodeID[addNodeIDIndex] = (char)key;
				addNodeID[addNodeIDIndex + 1] = '\0';
				addNodeIDIndex++;
			}
			key = GetKeyPressed();
			if (IsKeyPressed(KEY_BACKSPACE)) {
				if (addNodeIDIndex > 0) {
					addNodeIDIndex--;
					addNodeID[addNodeIDIndex] = '\0';
				}
			}
		}
	}
	else
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
	DrawText(addNodeID, textBox.x + 5, textBox.y + 3.3, 32, MAROON);
}

void Renderer::DrawNodeDeleteInput(const int screenWidth, const int screenHeight)
{
	Rectangle textBox = { screenWidth / 4.0f - 154, screenHeight / 1.1f - 32, 85, 35 };
	DrawRectangleRounded(textBox, 0.2, 4, LIGHTGRAY);

	if (CheckCollisionPointRec(GetMousePosition(), textBox))
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		int key = GetKeyPressed();
		DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, RED);
		while (key > 0)
		{
			if (key >= 48 && key <= 57 && (delNodeIDIndex < MAX_INPUT_CHARS_ADD_NODE))
			{
				delNodeID[delNodeIDIndex] = (char)key;
				delNodeID[delNodeIDIndex + 1] = '\0';
				delNodeIDIndex++;
			}
			key = GetKeyPressed();
			if (IsKeyPressed(KEY_BACKSPACE)) {
				if (delNodeIDIndex > 0) {
					delNodeIDIndex--;
					delNodeID[delNodeIDIndex] = '\0';
				}
			}
		}
	}
	else
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
	DrawText(delNodeID, textBox.x + 5, textBox.y + 3.3, 32, MAROON);
}

void Renderer::DrawEdgeConnectionInput(int screenWidth, int screenHeight, std::vector<Node>& nodes)
{
	Rectangle textBox = { screenWidth / 4.0f - 40, screenHeight / 1.1f + 30, 175, 35 };
	DrawRectangleRounded(textBox, 0.2, 4, LIGHTGRAY);

	for (const auto& node : nodes)
	{
		int nodeID = node.GetId();
		Vector2 nodePos = { node.GetX(), node.GetY() };
		if (CheckCollisionPointCircle(GetMousePosition(), nodePos, 30.0f) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			auto it = std::find(nodeEdges.begin(), nodeEdges.end(), nodeID);
			if (it != nodeEdges.end())
			{
				nodeEdges.erase(it);
			}
			else
			{
				nodeEdges.push_back(nodeID);
			}
		}
	}

	std::string nodeEdgesStr = "";
	for (int edge : nodeEdges)
	{
		if (!nodeEdgesStr.empty())
		{
			nodeEdgesStr += ',';
		}
		nodeEdgesStr += std::to_string(edge);
	}
	DrawText(nodeEdgesStr.c_str(), textBox.x + 5, textBox.y + 3.3, 32, MAROON);
}

Vector2 posDiff;
int draggableNodeIdx = -1;
void Renderer::DraggableNode(std::vector<Node>& nodes)
{
	if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
	{
		for (auto& node : nodes) {
			Vector2 pos = { node.GetX(), node.GetY() };
				if (CheckCollisionPointCircle(GetMousePosition(), pos, 31.0f))
				{
					draggableNodeIdx = node.GetId();
					posDiff.x = node.GetX() - GetMousePosition().x;
					posDiff.y = node.GetY() - GetMousePosition().y;
					break;
				}
		}
	}
	if (draggableNodeIdx != -1 && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
	{
		for (auto& node : nodes)
		{
			if (node.GetId() == draggableNodeIdx)
			{
				node.SetPosition(GetMousePosition().x + posDiff.x, GetMousePosition().y + posDiff.y);
				break;
			}
		}
	}
	if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) 
	{
		draggableNodeIdx = -1;
	}
}

void Renderer::DrawAddNodeButton(const int screenWidth, const int screenHeight, Graph& graph, std::vector<Node>& nodes) {
	Rectangle button = { screenWidth / 4.0f + 150, screenHeight / 1.1f + 30, 140, 35 };
	DrawRectangleRounded(button, 0.5, 0, LIGHTGRAY);
	DrawText("Add Node", button.x + 15, button.y + 7, 24, MAROON);

	if (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && addNodeID[0] != '\0')
	{
		int id = stoi(addNodeID);
		graph.AddNode(id, 150, 100);
		addNodeID[0] = '\0';
		addNodeIDIndex = 0;
		for(auto & node : nodes)
		{
			if (isNodePresentInNodeEdges(node.GetId())) {
				std::cout << "Adding edge to node: " << node.GetId() << std::endl;
				graph.AddEdge(id, node.GetId(), 1.0f);
			}
		}
		nodeEdges.clear();
	}
}

void Renderer::DrawRemoveNodeButton(const int screenWidth, const int screenHeight, Graph& graph, std::vector<Node>& nodes) {
	Rectangle button = { screenWidth / 4.0f - 55, screenHeight / 1.1f - 32, 180, 35 };
	DrawRectangleRounded(button, 0.5, 0, LIGHTGRAY);
	DrawText("Remove Node", button.x + 15, button.y + 7, 24, MAROON);

	if (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && delNodeID[0] != '\0' && graph.HasNode(stoi(delNodeID)))
	{
		int id = stoi(delNodeID);
		graph.RemoveNode(id);
		auto it = std::remove_if(nodes.begin(), nodes.end(), [id](const Node& node) { return node.GetId() == id; });
		nodes.erase(it, nodes.end());
		delNodeID[0] = '\0';
		delNodeIDIndex = 0;
	}
}

bool Renderer::isNodePresentInNodeEdges(int nodeId) {
	return std::find(nodeEdges.begin(), nodeEdges.end(), nodeId) != nodeEdges.end();
}

void Renderer::DrawOnScreenText(const int screenWidth, const int screenHeight) 
{
	DrawText("Remove Node: ", screenWidth / 4.0f - 375, screenHeight / 1.1f - 30, 32, MAROON);
	DrawText("Add New Node: ", screenWidth / 4.0f - 375, screenHeight / 1.1f + 33, 32, MAROON);
	DrawText("Node ID", screenWidth / 4.0f - 120, screenHeight / 1.1f + 68, 13, BLACK); // add node
	DrawText("Node ID", screenWidth / 4.0f - 138, screenHeight / 1.1f + 6, 13, BLACK); // remove node
	DrawText("Add Edge Connections", screenWidth / 4.0f - 21, screenHeight / 1.1f + 68, 13, BLACK);
}
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
		DrawTexture(blackNodeTexture, pos.x - blackNodeTexture.width / 2, pos.y - blackNodeTexture.height / 2, WHITE); // You may need to adjust the offset		Texture2D texture = LoadTextureFromImage(nodeImage);
		DrawText(TextFormat("%d", node.GetId()), node.GetX() - 5, node.GetY() - 10, 20, WHITE);
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
	Rectangle textBox = { screenWidth / 4.0f - 30, screenHeight / 1.1f, 85, 35 };
	DrawRectangleRec(textBox, LIGHTGRAY);

	if (CheckCollisionPointRec(GetMousePosition(), textBox))
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		int key = GetKeyPressed();
		DrawRectangleLines(textBox.x, textBox.y, textBox.width, textBox.height, RED);
		while (key > 0)
		{
			if (key >= 32 && key <= 125 && (nodeIDIndex < MAX_INPUT_CHARS_ADD_NODE))
			{
				nodeID[nodeIDIndex] = (char)key;
				nodeID[nodeIDIndex + 1] = '\0';
				nodeIDIndex++;
			}
			key = GetKeyPressed();
			if (IsKeyPressed(KEY_BACKSPACE)) {
				if (nodeIDIndex > 0) {
					nodeIDIndex--;
					nodeID[nodeIDIndex] = '\0';
				}
			}
		}
	}
	else
	{
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	}
	DrawText(nodeID, textBox.x + 5, textBox.y + 3.3, 32, MAROON);
}

void Renderer::DrawEdgeConnectionInput(int screenWidth, int screenHeight, std::vector<Node>& nodes)
{
	Rectangle textBox = { screenWidth / 4.0f + 60, screenHeight / 1.1f, 175, 35 };
	DrawRectangleRec(textBox, LIGHTGRAY);

	for (const auto& node : nodes) 
	{
		int nodeID = node.GetId();
		Vector2 nodePos = {node.GetX(), node.GetY()};
		if(CheckCollisionPointCircle(GetMousePosition(), nodePos, 30.0f) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))
		{
			string nodeIDStr = to_string(nodeID);
			size_t pos = nodeEdges.find(nodeIDStr);
			if (pos != string::npos)
			{
				nodeEdges.erase(pos, nodeIDStr.length()+1);
				if (pos > 0 && nodeEdges[pos - 1] == ',')
				{
					nodeEdges.erase(pos-1, 1);
				}
			} else {
				if (!nodeEdges.empty())
				{
					nodeEdges += ',';
				}
				nodeEdges += to_string(nodeID);
			}
		}
	}
	DrawText(nodeEdges.c_str(), textBox.x + 5, textBox.y + 3.3, 32, MAROON);
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
	Rectangle button = { screenWidth / 4.0f + 250, screenHeight / 1.1f, 140, 35 };
	DrawRectangleRounded(button, 0.5, 0, LIGHTGRAY);
	DrawText("Add Node", button.x + 15, button.y + 7, 24, MAROON);

	if (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && nodeID[0] != '\0')
	{
		int id = stoi(nodeID);
		graph.AddNode(id, 150, 100);
		nodeID[0] = '\0';
		nodeIDIndex = 0;
		for(auto & node : nodes)
		{
			if (isNodePresentInNodeEdges(node.GetId(), nodeEdges)) {
				std::cout << "Adding edge to node: " << node.GetId() << std::endl;
				graph.AddEdge(id, node.GetId(), 1.0f);
			}
		}
		nodeEdges = "";
	}
}

bool Renderer::isNodePresentInNodeEdges(int nodeId, const std::string& nodeEdges) {
	std::istringstream iss(nodeEdges);
	std::string token;
	while (std::getline(iss, token, ',')) {
		if (std::stoi(token) == nodeId) {
			return true;
		}
	}
	return false;
}

void Renderer::DrawOnScreenText(const int screenWidth, const int screenHeight) 
{
	DrawText("Add New Node: ", screenWidth / 4.0f - 275, screenHeight / 1.1f + 3, 32, MAROON);
	DrawText("Node ID", screenWidth / 4.0f - 12, screenHeight / 1.1f + 38, 12, BLACK);
	DrawText("Add Edge Connections", screenWidth / 4.0f + 80, screenHeight / 1.1f + 38, 12, BLACK);
}
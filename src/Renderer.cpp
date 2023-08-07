#include "../include/Renderer.h"
#include "../include/Graph.h"
#include "../include/Node.h"
#include "../include/raylib.h"
#include <map>
#include <vector>
#include <utility>
#include <string>
#include <sstream>


using namespace std;

void Renderer::DrawNode(Node node)
{
	Vector2 pos = { node.GetX(), node.GetY() };
	DrawCircleV(pos, 40.0f, BLUE); // TODO: Need to change this to ImageDrawCircle to check for better pixelation
	DrawCircleLines(node.GetX(), node.GetY(), 40.0f, BLACK);
	DrawText(TextFormat("%d", node.GetId()), node.GetX() - 5, node.GetY() - 10, 20, BLACK);
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
			if (key >= 32 && key <= 125 && (nodeIDIndex < MAX_INPUT_CHARS))
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

void Renderer::DrawEdgeConnectionInput(const int screenWidth, const int screenHeight)
{
	Rectangle textBox = { screenWidth / 4.0f + 60, screenHeight / 1.1f, 175, 35 };
	DrawRectangleRec(textBox, LIGHTGRAY);

	if (CheckCollisionPointCircle(GetMousePosition(), nodes)
	{

	}
}

void Renderer::DrawOnScreenText(const int screenWidth, const int screenHeight) 
{
	DrawText("Add New Node: ", screenWidth / 4.0f - 275, screenHeight / 1.1f + 3, 32, MAROON);
	DrawText("Node ID", screenWidth / 4.0f - 12, screenHeight / 1.1f + 38, 12, BLACK);
	DrawText("Add Edge Connections", screenWidth / 4.0f + 80, screenHeight / 1.1f + 38, 12, BLACK);
}
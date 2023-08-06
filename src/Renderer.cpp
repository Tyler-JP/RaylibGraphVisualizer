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
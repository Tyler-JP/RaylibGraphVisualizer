#include "../include/Renderer.h"
#include "../include/Graph.h"
#include "../include/Node.h"
#include "../include/raylib.h"
#include "../include/Renderer.h"
#include <map>
#include <vector>
#include <utility>

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 750;
    InitWindow(screenWidth, screenHeight, "Graph Visualizer");

    Renderer renderer;
    Graph graph(renderer);

    Node nodeTest(3, 750, 500);
	// graph.AddNode(4, 750, 500); // TODO: Need to fix AddNode implementation
    // Need to add user input to add nodes
    while (!WindowShouldClose())
    {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		renderer.DrawNode(nodeTest);
        renderer.DrawNodeInput(screenWidth, screenHeight);
		EndDrawing();
    }

    CloseWindow();

    return 0;
}
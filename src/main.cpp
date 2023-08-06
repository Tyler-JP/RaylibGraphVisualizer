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
    InitWindow(1200, 750, "Graph Visualizer");

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
		EndDrawing();
    }

    CloseWindow();

    return 0;
}
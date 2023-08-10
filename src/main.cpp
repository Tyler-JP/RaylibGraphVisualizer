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

    SetTargetFPS(60);

    Renderer renderer;
    Graph graph(renderer);

    Node nodeTest(3, 750, 500);
    Node nodeTest2(17, 500, 250);
	// graph.AddNode(4, 750, 500); // TODO: Need to fix AddNode implementation
    // Need to add user input to add nodes

    renderer.LoadNodeTexture();
    while (!WindowShouldClose())
    {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		renderer.DrawNodes(graph.GetNodes());
        renderer.DrawNodeEdges(screenWidth, screenHeight, graph.GetNodes(), graph);
        renderer.DraggableNode(graph.GetNodes());
        renderer.DrawNodeInput(screenWidth, screenHeight);
        renderer.DrawEdgeConnectionInput(screenWidth, screenHeight, graph.GetNodes());
        renderer.DrawAddNodeButton(screenWidth, screenHeight, graph, graph.GetNodes());
        renderer.DrawOnScreenText(screenWidth, screenHeight);
        //graph.PrintGraph();
		EndDrawing();
    }
    renderer.UnloadNodeTexture();

    CloseWindow();

    return 0;
}
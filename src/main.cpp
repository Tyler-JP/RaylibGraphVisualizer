#include "../include/Renderer.h"
#include "../include/Graph.h"
#include "../include/Node.h"
#include "../include/raylib.h"
#include "../include/Renderer.h"
#include "../include/UI.h"
#include <map>
#include <vector>
#include <utility>

int main(void)
{
    const int screenWidth = 1600;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "Graph Visualizer");

    SetTargetFPS(60);

    Renderer renderer;
    UI ui;
    Graph graph(renderer);

    Node nodeTest(3, 750, 500);
    Node nodeTest2(17, 500, 250);
	// graph.AddNode(4, 750, 500); // TODO: Need to fix AddNode implementation
    // Need to add user input to add nodes

    renderer.LoadNodeTexture();
    while (!WindowShouldClose())
    {
        ui.UpdateCheckbox(100,100);
		BeginDrawing();
		ClearBackground(RAYWHITE);
        renderer.DrawNodeEdges(screenWidth, screenHeight, graph.GetNodes(), graph);
        renderer.DraggableNode(graph.GetNodes());
        renderer.DrawNodeInput(screenWidth, screenHeight);
        renderer.DrawNodeDeleteInput(screenWidth, screenHeight);
        renderer.DrawEdgeConnectionInput(screenWidth, screenHeight, graph.GetNodes());
        renderer.DrawAddNodeButton(screenWidth, screenHeight, graph, graph.GetNodes());
        renderer.DrawRemoveNodeButton(screenWidth, screenHeight, graph, graph.GetNodes());
        renderer.DrawOnScreenText(screenWidth, screenHeight);
        ui.DrawCheckbox(100, 100, "BFS");
        renderer.DrawNodes(graph.GetNodes());
        //graph.PrintGraph();
		EndDrawing();
    }
    renderer.UnloadNodeTexture();

    CloseWindow();

    return 0;
}
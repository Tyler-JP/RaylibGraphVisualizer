#include "../include/Renderer.h"
#include "../include/Graph.h"
#include "../include/Node.h"
#include "../include/raylib.h"
#include "../include/Renderer.h"
#include "../include/Checkbox.h"
#include "../include/Conditionals.h"
#include <map>
#include <vector>
#include <utility>
#include <iostream>

int main(void)
{
    Conditionals activeState = NONE;
    const int screenWidth = 1600;
    const int screenHeight = 1000;
    InitWindow(screenWidth, screenHeight, "Graph Visualizer");

    SetTargetFPS(60);

    Renderer renderer;
    Checkbox BFSCheckbox(100, 700,"BFS");
    Graph graph(renderer);

	// graph.AddNode(4, 750, 500); // TODO: Need to fix AddNode implementation

    renderer.LoadNodeTexture();
    while (!WindowShouldClose())
    {
        BFSCheckbox.UpdateCheckbox();
        renderer.UpdateBFSAnimation(graph.GetNodes());
		BeginDrawing();
		ClearBackground(RAYWHITE);
        renderer.DrawNodeEdges(screenWidth, screenHeight, graph.GetNodes(), graph);
        renderer.DraggableNode(graph.GetNodes());
        renderer.DrawNodeInput(screenWidth, screenHeight);
        renderer.DrawNodeDeleteInput(screenWidth, screenHeight);
        renderer.DrawEdgeConnectionInput(screenWidth, screenHeight, graph.GetNodes());
        renderer.DrawAddNodeButton(screenWidth, screenHeight, graph, graph.GetNodes());
        renderer.DrawRemoveNodeButton(screenWidth, screenHeight, graph, graph.GetNodes());
        renderer.DrawOnScreenText(screenWidth, screenHeight, activeState);
        BFSCheckbox.DrawCheckbox();
        renderer.DrawNodes(graph.GetNodes());
        //graph.PrintGraph();

        if (BFSCheckbox.IsActive())
        {
            activeState = BFS;
            renderer.DrawBFSStartNodeInput(screenWidth, screenHeight, graph.GetNodes());
            renderer.DrawBFSStartButton(screenWidth, screenHeight, graph, graph.GetNodes());
        }
        else {
            activeState = NONE;
        }
        renderer.SetActiveState(activeState);
		EndDrawing();
    }
    renderer.UnloadNodeTexture();

    CloseWindow();

    return 0;
}
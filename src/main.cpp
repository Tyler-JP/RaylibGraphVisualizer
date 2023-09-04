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
    bool graphCleared = false;

    SetTargetFPS(60);

    Renderer renderer;
    Checkbox BFSCheckbox(100, 700,"BFS");
    Checkbox Preset1Checkbox(25, 50, "Preset 1");
    Checkbox Preset2Checkbox(25, 90, "Preset 2");
    Checkbox Preset3Checkbox(25, 130, "Preset 3");
    Graph graph(renderer);

	// graph.AddNode(4, 750, 500); // TODO: Need to fix AddNode implementation

    renderer.LoadNodeTexture();
    while (!WindowShouldClose())
    {
        BFSCheckbox.UpdateCheckbox();
        Preset1Checkbox.UpdateCheckbox();
        Preset2Checkbox.UpdateCheckbox();
        Preset3Checkbox.UpdateCheckbox();
        if (!Preset1Checkbox.IsActive() && !Preset2Checkbox.IsActive() && !Preset3Checkbox.IsActive())
        {
            if (!graphCleared) {
                graph.ClearGraph();
                graphCleared = true;
            }
        }
        else {
			graphCleared = false;
		}
        if (Preset1Checkbox.IsActive()) graph.LoadPreset1();
        if (Preset2Checkbox.IsActive()) graph.LoadPreset2();
        if (Preset3Checkbox.IsActive()) graph.LoadPreset3();
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
        Preset1Checkbox.DrawCheckbox();
        Preset2Checkbox.DrawCheckbox();
        Preset3Checkbox.DrawCheckbox();
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
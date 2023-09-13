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
    bool preset1Loaded = false;
    bool preset2Loaded = false;
    bool preset3Loaded = false;

    SetTargetFPS(60);

    Renderer renderer;
    Checkbox BFSCheckbox(25, 250,"BFS");
    Checkbox Preset1Checkbox(25, 50, "Preset 1");
    Checkbox Preset2Checkbox(25, 90, "Preset 2");
    Checkbox Preset3Checkbox(25, 130, "Preset 3");
    Graph graph(renderer);

	// graph.AddNode(4, 750, 500); // TODO: Need to fix AddNode implementation

    renderer.LoadNodeTexture();
    while (!WindowShouldClose())
    {
        bool canChangePreset1 = !Preset2Checkbox.IsActive() && !Preset3Checkbox.IsActive();
        bool canChangePreset2 = !Preset1Checkbox.IsActive() && !Preset3Checkbox.IsActive();
        bool canChangePreset3 = !Preset1Checkbox.IsActive() && !Preset2Checkbox.IsActive();

        BFSCheckbox.UpdateCheckbox(true);

        Preset1Checkbox.UpdateCheckbox(canChangePreset1);
        Preset2Checkbox.UpdateCheckbox(canChangePreset2);
        Preset3Checkbox.UpdateCheckbox(canChangePreset3);
        if (Preset1Checkbox.IsActive()) {
            if (!preset1Loaded) {
                graph.ClearGraph();
                graph.LoadPreset1();
                preset1Loaded = true;
            }
            preset2Loaded = false;
            preset3Loaded = false;
            Preset2Checkbox.SetState(Checkbox::UNCHECKED);
            Preset3Checkbox.SetState(Checkbox::UNCHECKED);
        }
        else if (Preset2Checkbox.IsActive()) {
            if (!preset2Loaded) {
				graph.ClearGraph();
				graph.LoadPreset2();
				preset2Loaded = true;
			}
            preset1Loaded = false;
            preset3Loaded = false;
            Preset1Checkbox.SetState(Checkbox::UNCHECKED);
            Preset3Checkbox.SetState(Checkbox::UNCHECKED);
        }
        else if (Preset3Checkbox.IsActive()) {
            if (!preset3Loaded) {
                graph.ClearGraph();
                graph.LoadPreset3();
                preset3Loaded = true;
            }
            preset1Loaded = false;
            preset2Loaded = false;
            Preset1Checkbox.SetState(Checkbox::UNCHECKED);
            Preset2Checkbox.SetState(Checkbox::UNCHECKED);
        }
        else if (!Preset1Checkbox.IsActive() && !Preset2Checkbox.IsActive() && !Preset3Checkbox.IsActive()) {
            if (!graphCleared) {
                graph.ClearGraph();
                graphCleared = true;
            }
        }

        if (!Preset1Checkbox.IsActive() && !Preset2Checkbox.IsActive() && !Preset3Checkbox.IsActive())
        {
            if (!graphCleared) {
                graph.ClearGraph();
                graphCleared = true;
            }
            preset1Loaded = false;
            preset2Loaded = false;
            preset3Loaded = false;
        }
        else {
			graphCleared = false;
		}
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
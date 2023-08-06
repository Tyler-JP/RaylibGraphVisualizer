#include "raylib.h"

int main(void)
{
    InitWindow(1200, 750, "Graph Visualizer");

    while (!WindowShouldClose())
    {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Hello World", 10, 10, 20, LIGHTGRAY);
		EndDrawing();
    }

    CloseWindow();

    return 0;
}
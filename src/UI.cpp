#include "../include/UI.h"
#include "../include/Graph.h"
#include "../include/Node.h"
#include "../include/Renderer.h"
#include <iostream>

UI::UI() {
	state = 0;
}

void UI::DrawCheckbox(float xPos, float yPos, std::string label)
{
	DrawRectangle(xPos, yPos, 25, 25, LIGHTGRAY);
	DrawLineEx(linePos, endPos, 3, MAROON);
	DrawLineEx(linePos2, endPos2, 3, MAROON);
	DrawLineEx(linePos3, endPos3, 3, MAROON);
	DrawLineEx(linePos4, endPos4, 3, MAROON);
}

void UI::UpdateCheckbox(float xPos, float yPos)
{
	Rectangle rec = { xPos, yPos, 25, 25 };
	if (CheckCollisionPointRec(GetMousePosition(), rec)) {
		if (state == 0)
		{
			leftLineE += 0.5;
			topLineS += 0.5;
			rightLineE -= 0.49;
			botLineS -= 0.5;
			endPos = { leftLineS, leftLineE };
			endPos2 = { topLineS, topLineE };
			endPos3 = { rightLineS, rightLineE };
			endPos4 = { botLineS, botLineE };
			if (leftLineE >= 127) state = 1;
		}
	} 
	else
	{
		leftLineS = 100;
		leftLineE = 100;
		topLineS = 98;
		topLineE = 100;
		rightLineS = 124;
		rightLineE = 125;
		botLineS = 125;
		botLineE = 125;
		endPos = { leftLineS, leftLineE };
		endPos2 = { topLineS, topLineE };
		endPos3 = { rightLineS, rightLineE };
		endPos4 = { botLineS, botLineE };
		state = 0;


	}
}
	
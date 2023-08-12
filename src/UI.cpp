#include "../include/UI.h"
#include "../include/Graph.h"
#include "../include/Node.h"
#include "../include/Renderer.h"
#include "../include/ResourceLoader.h"
#include <iostream>


UI::UI() {
	state = 0;
	alpha = 0.0f;
}

void UI::DrawCheckbox(float xPos, float yPos, std::string label)
{
	Color active = BLACK;
	if (checkmarkActive) {
		active = MAROON;
	}
	DrawRectangle(xPos, yPos, 25, 25, LIGHTGRAY);
	DrawLineEx(linePos, endPos, 3, active);
	DrawLineEx(linePos2, endPos2, 3, active);
	DrawLineEx(linePos3, endPos3, 3, active);
	DrawLineEx(linePos4, endPos4, 3, active);
	DrawText(label.c_str(), xPos + 34, yPos, 28, active);
	Color modulatedColor = WHITE;
	modulatedColor.a = (unsigned char)alpha;
	if (checkmarkInactive == true) DrawTexture(Renderer::checkmarkInactiveTexture, xPos + 2, yPos + 3, modulatedColor);
	if (checkmarkActive == true) DrawTexture(Renderer::checkmarkActiveTexture, xPos + 2, yPos + 3, WHITE);

}

void UI::UpdateCheckbox(float xPos, float yPos)
{
	Rectangle rec = { xPos, yPos, 25, 25 };
	if (CheckCollisionPointRec(GetMousePosition(), rec) || checkmarkActive) {
		if (!checkmarkActive) {
			checkmarkInactive = true;
		}
		if (checkmarkInactive) {
			alpha += 5;
			if (alpha > 255) alpha = 255;
		}
		else {
			alpha = 0;
		}

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
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (checkmarkInactive)
			{
				checkmarkInactive = false;
				checkmarkActive = true;
			}
			else if (checkmarkActive)
			{
				checkmarkInactive = true;
				checkmarkActive = false;
			}
		}
	} 
	else if(!checkmarkActive)
	{
		checkmarkInactive = false;
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
		alpha = 0;

	}
}
	
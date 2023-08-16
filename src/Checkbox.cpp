#include "../include/Checkbox.h"
#include "../include/Graph.h"
#include "../include/Node.h"
#include "../include/Renderer.h"
#include "../include/ResourceLoader.h"
#include <iostream>

const Vector2 CHECKBOX_SIZE = { 25, 25 };
const float LINE_WIDTH = 3;
const float ANIM_SPEED = 0.5;
const float ALPHA_INCREMENT = 5;


Checkbox::Checkbox(float x, float y, const std::string& label) : position({x,y}), label(label), state(UNCHECKED), alpha(0.0f) { 
}

bool Checkbox::IsActive() const {
	return state == CHECKED;
}

void Checkbox::DrawCheckbox()
{
	Color active = BLACK;
	Color color = (state == CHECKED) ? MAROON : BLACK;
	DrawRectangleV(position, CHECKBOX_SIZE, LIGHTGRAY);
	DrawLineEx(linePos, endPos, LINE_WIDTH, color);
	DrawLineEx(linePos2, endPos2, LINE_WIDTH, color);
	DrawLineEx(linePos3, endPos3, LINE_WIDTH, color);
	DrawLineEx(linePos4, endPos4, LINE_WIDTH, color);
	DrawText(label.c_str(), position.x + 34, position.y, 28, color);
	Color modulatedColor = WHITE;
	modulatedColor.a = (unsigned char)alpha;
	if (state == HOVER) DrawTexture(Renderer::checkmarkInactiveTexture, position.x + 2, position.y + 3, modulatedColor);
	if (state == CHECKED) DrawTexture(Renderer::checkmarkActiveTexture, position.x + 2, position.y + 3, WHITE);

}

void Checkbox::UpdateCheckbox()
{
	Rectangle rec = { position.x, position.y, CHECKBOX_SIZE.x, CHECKBOX_SIZE.y };
	if (CheckCollisionPointRec(GetMousePosition(), rec) || state == CHECKED) {
		if (state == UNCHECKED) {
			state = HOVER;
		}
		if (state == HOVER) {
			alpha += ALPHA_INCREMENT;
			if (alpha > 255) alpha = 255;
		}
		else {
			alpha = 0;
		}

		if (animState == 0)
		{
			leftLineE += ANIM_SPEED;
			topLineS += ANIM_SPEED;
			rightLineE -= ANIM_SPEED - 0.01; //IDK why this is needed but it is to smooth corners
			botLineS -= ANIM_SPEED;
			endPos = { leftLineS, leftLineE };
			endPos2 = { topLineS, topLineE };
			endPos3 = { rightLineS, rightLineE };
			endPos4 = { botLineS, botLineE };
			if (leftLineE >= position.y + 27) animState = 1;
		}
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
		{
			if (state == UNCHECKED || state == HOVER)
			{
				state = CHECKED;
			}
			else if (state == CHECKED)
			{
				state = UNCHECKED;
			}
		}
	} 
	else
	{
		resetAnim();
		alpha = 0;
		animState = 0;
	}
}
	
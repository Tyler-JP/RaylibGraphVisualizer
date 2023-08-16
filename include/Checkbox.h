#pragma once
#include "Graph.h"
#include "Node.h"
#include "raylib.h"
#include <vector>
#include <string>

enum CheckboxState {
	UNCHECKED,
	HOVER,
	CHECKED
};

class Checkbox {
public:
	Checkbox(float x, float y, const std::string& label);
	void UpdateCheckbox();
	void DrawCheckbox();
	bool IsActive() const;
	int framesCounter = 0;

private:
	Vector2 position;
	std::string label;
	CheckboxState state;
	int animState = 0;
	float alpha;
	float leftLineS, leftLineE, topLineS, topLineE, rightLineS, rightLineE, botLineS, botLineE;
	Vector2 linePos, endPos, linePos2, endPos2, linePos3, endPos3, linePos4, endPos4;
	void resetAnim() {
		leftLineS = position.x;
		leftLineE = position.y;
		topLineS = position.x - 2; // -2 to smooth corners
		topLineE = position.y;
		linePos = { leftLineS, leftLineE }; // top-left down start
		endPos = { leftLineS, leftLineE }; // top-left down end
		linePos2 = { topLineS, topLineE }; // top-left right start
		endPos2 = { topLineS, topLineE }; // top-left right end
		rightLineS = position.x + 24; // +24 to smooth corners
		rightLineE = position.y + 25;
		botLineS = position.x + 25;
		botLineE = position.y + 25;
		linePos3 = { rightLineS, rightLineE }; // top-left down start
		endPos3 = { rightLineS, rightLineE }; // top-left down end
		linePos4 = { botLineS, botLineE }; // top-left right start
		endPos4 = { botLineS, botLineE }; // top-left right end
	}
};
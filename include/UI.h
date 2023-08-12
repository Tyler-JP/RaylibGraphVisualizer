#pragma once
#include "Graph.h"
#include "Node.h"
#include "raylib.h"
#include <vector>
#include <string>

class UI {
public:
	UI();
	void UpdateCheckbox(float xPos, float yPos);
	void DrawCheckbox(float xPos, float yPos, std::string label);
	int framesCounter = 0;
	float alpha = 0.0f;

private:
	int state = 0;
	float leftLineS = 100;
	float leftLineE = 100;
	float topLineS = 98;
	float topLineE = 100;
	Vector2 linePos = { leftLineS, leftLineE }; // top-left down start
	Vector2 endPos = { leftLineS, leftLineE }; // top-left down end
	Vector2 linePos2 = { topLineS, topLineE }; // top-left right start
	Vector2 endPos2 = { topLineS, topLineE }; // top-left right end
	float rightLineS = 124;
	float rightLineE = 125;
	float botLineS = 125;
	float botLineE = 125;
	Vector2 linePos3 = { rightLineS, rightLineE }; // top-left down start
	Vector2 endPos3 = { rightLineS, rightLineE }; // top-left down end
	Vector2 linePos4 = { botLineS, botLineE }; // top-left right start
	Vector2 endPos4 = { botLineS, botLineE }; // top-left right end

	bool checkmarkInactive = false;
	bool checkmarkActive = false;

};
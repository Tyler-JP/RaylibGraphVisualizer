#pragma once
#include "../include/Graph.h"
#include "../include/Node.h"

#define MAX_INPUT_CHARS     4

class Renderer
{
private:
	char nodeID[MAX_INPUT_CHARS + 1] = "\0";
	int nodeIDIndex = 0;
public:
	void DrawNode(Node node);
	void DrawNodeInput(const int screenWidth, const int screenHeight);
};
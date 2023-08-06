#pragma once

class Node {
public:
	Node(int id, float x, float y) : id(id), x(x), y(y) {}

	int GetId() const { return id; }
	float GetX() const { return x; }
	float GetY() const { return y; }

	void SetPosition(float newX, float newY) { x = newX; y = newY; }

private:
	int id;
	float x, y;
};
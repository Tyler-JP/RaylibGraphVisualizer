#pragma once

#include <vector>

class Node {
public:
	Node(int id, float x, float y) : id(id), x(x), y(y) { positions.push_back(std::make_pair(x, y)); }

	int GetId() const { return id; }
	float GetX() const { return x; }
	float GetY() const { return y; }

	static std::vector<std::pair<float, float>>& GetAllPositions() { return positions; }

	void SetPosition(float newX, float newY) { x = newX; y = newY; }

private:
	int id;
	float x, y;
	static std::vector<std::pair<float, float>> positions;
};
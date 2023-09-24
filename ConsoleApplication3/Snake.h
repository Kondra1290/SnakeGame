#pragma once
#include <vector>
#include <array>
using namespace std;

class Snake
{
private:
	int x, y, len;
	int score;
	

public:
	vector<array<int, 2>> tail;

	Snake() {
		score = 0;
	}

	void snakeBigger(int dx, int dy) {
		if (tail.size() == 1) {
			tail.push_back({x-dx,y-dy});
		}
		else {
			int tailX = tail.at(0)[0];
			int tailY = tail.at(0)[1];
			auto iter = tail.cbegin();
			tail.insert(iter, { tailX - dx, tailY - dy });
		}
	}

	bool checkTail(int newX, int newY) {
		for (array<int, 2> arr : tail)
			if (newX == arr[0] && newY == arr[1]) return true;

		return false;
	}

	int getHeadX() { return x; }
	void setHeadX(int value) { x = value; };
	int getHeadY() { return y; }
	void setHeadY(int value) { y = value; };
	int getScore() { return score; }
	void setScore(int value) { score = value; };
};


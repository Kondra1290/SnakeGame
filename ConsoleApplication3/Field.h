#pragma once
#include <iostream>
#include <time.h>
#include "Snake.h"
#include "Fruit.h"
using namespace std;

class Field
{
private:
	char** field;
	int rows, cells;
	Snake* snake;
	Fruit* fruit;

public:
	Field(int rows, int cells) {
		this->rows = rows;
		this->cells = cells;

		field = new char* [rows];
		for (int i = 0; i < rows; i++) {
			field[i] = new char[cells];
			for (int j = 0; j < cells; j++) {
				if (i == 0 || i == rows - 1 || j == cells - 1 || j == 0) field[i][j] = '#';
				else field[i][j] = ' ';
			}
		}
	}

	void setSnake(Snake& snake) {
		srand(time(NULL));
		this->snake = &snake;
		int x = 1 + rand() % (cells - 2);
		int y = 1 + rand() % (rows - 2);
		(*this->snake).setHeadX(x);
		(*this->snake).setHeadY(y);
		(*this->snake).tail.push_back({x,y});
		field[y][x] = 'S';

		//snake.tail.push_back({x,y});
	}

	void setFruit(Fruit& fruit) {
		srand(time(NULL));
		int x = 1 + rand() % (cells - 2);
		int y = 1 + rand() % (rows - 2);

		while(x == (*snake).getHeadX() && y == (*snake).getHeadY()) {
			x = 1 + rand() % (cells - 2);
			y = 1 + rand() % (rows - 2);
		}

		this->fruit = &fruit;
		(*this->fruit).setX(x);
		(*this->fruit).setY(y);
		field[y][x] = 'F';
	}

	void setFruit() {
		srand(time(NULL));
		int x = 1 + rand() % (cells - 2);
		int y = 1 + rand() % (rows - 2);

		while ((*snake).checkTail(x, y)) {
			x = 1 + rand() % (cells - 2);
			y = 1 + rand() % (rows - 2);
		}

		field[y][x] = 'F';
		(*fruit).setX(x);
		(*fruit).setY(y);
		
	}

	bool moveSnake(int newX, int newY) {
		bool flag = true, bigger = false;
		int px, py;

		if ((*snake).getHeadX() == 1 && newX == -1) return false;
		else if ((*snake).getHeadX() == cells - 2 && newX == 1) return false;
		else if ((*snake).getHeadY() == 1 && newY == -1) return false;
		else if ((*snake).getHeadY() == rows - 2 && newY == 1) return false;
		else if ((*snake).checkTail(newX, newY)) return false;

		(*snake).setHeadX((*snake).getHeadX() + newX);
		(*snake).setHeadY((*snake).getHeadY() + newY);

		if ((*snake).getHeadY() == (*fruit).getY() && (*snake).getHeadX() == (*fruit).getX()){
			bigger = true;
		}
		
		auto iter = (*snake).tail.begin();
		(*snake).tail.insert(iter, { (*snake).getHeadX(),(*snake).getHeadY()});

		field[(*snake).getHeadY()][(*snake).getHeadX()] = 'S';
		if((*snake).tail.size() == 1) field[(*snake).getHeadY() - newY][(*snake).getHeadX() - newX] = ' ';
		else {
			for (int i = 1; i < (*snake).tail.size(); i++) {
				field[(*snake).tail.at(i)[1]][(*snake).tail.at(i)[0]] = '@';
			}
			if (!bigger) {
				px = (*snake).tail.at((*snake).tail.size() - 1)[0];
				py = (*snake).tail.at((*snake).tail.size() - 1)[1];
				(*snake).tail.pop_back();
				field[py][px] = ' ';
			}
			else setFruit();
		}
		
		return true;
	}

	void Drow() {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cells; j++)
				cout << field[i][j] << ' ';
			cout << endl;
		}
	}

	~Field() {
		for (int i = 0; i < rows; i++) {
			delete field[i];
			field[i] = nullptr;
		}

		delete field;
		field = nullptr;
		snake = nullptr;
		fruit = nullptr;
	}

};


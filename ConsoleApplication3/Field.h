#pragma once
#include <iostream>
#include <time.h>
#include "Snake.h"
#include "Fruit.h"
using namespace std;

class Field
{
public:
	char** field;
	int rows, cells;

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

	~Field() {
		for (int i = 0; i < rows; i++) {
			delete field[i];
			field[i] = nullptr;
		}

		delete field;
		field = nullptr;
	}
};


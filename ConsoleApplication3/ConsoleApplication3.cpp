#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>
#include "Field.h"
#include "Snake.h"
#include "Fruit.h"

using namespace sf;
using namespace std;

const int rows = 20; // высота игрового поля
const int cells = 20; // ширина игрового поля

//Field field(rows, cells);
Snake snake;
Fruit fruit;

void setSnake() {
	srand(time(NULL));
	int x = 1 + rand() % (cells - 3);
	int y = 1 + rand() % (rows - 3);
	snake.setHeadX(x);
	snake.setHeadY(y);
	snake.tail.push_back({ x,y });
	//field.field[y][x] = 'S';
}

void setFruit() {
	srand(time(NULL));

	int x = 1 + rand() % (cells - 3);
	int y = 1 + rand() % (rows - 3);

	while (snake.checkTail(x, y) ||
			(x == snake.getHeadX() && 
			 y == snake.getHeadY())) {
		x = 1 + rand() % (cells - 3);
		y = 1 + rand() % (rows - 3);
	}

	fruit.setX(x);
	fruit.setY(y);
	//field.field[y][x] = 'F';
}

bool moveSnake(int newX, int newY) {
	bool bigger = false;

	if (snake.getHeadX() == 1 && newX == -1) return false;
	else if (snake.getHeadX() == cells - 2 && newX == 1) return false;
	else if (snake.getHeadY() == 1 && newY == -1) return false;
	else if (snake.getHeadY() == rows - 2 && newY == 1) return false;
	else if (snake.checkTail(snake.getHeadX() + newX, snake.getHeadY() + newY)) return false;

	snake.setHeadX(snake.getHeadX() + newX);
	snake.setHeadY(snake.getHeadY() + newY);

	if (snake.getHeadY() == fruit.getY() && 
		snake.getHeadX() == fruit.getX()) {
		bigger = true;
	}

	auto iter = snake.tail.begin();
	snake.tail.insert(iter, { snake.getHeadX(),snake.getHeadY() });

	if (!bigger) snake.tail.pop_back();
	else setFruit();
		 
	//field.field[snake.getHeadY()][snake.getHeadX()] = 'S';
	//if (snake.tail.size() == 1) 
	//	field.field[snake.getHeadY() - newY][snake.getHeadX() - newX] = ' ';
	//else {
	//	for (int i = 1; i < snake.tail.size(); i++)
	//		field.field[snake.tail.at(i)[1]][snake.tail.at(i)[0]] = '@';
	//	if (!bigger) {
	//		px = snake.tail.at(snake.tail.size() - 1)[0];
	//		py = snake.tail.at(snake.tail.size() - 1)[1];
	//		snake.tail.pop_back();
	//		//field.field[py][px] = ' ';
	//	}
	//	else setFruit();
	//}

	return true;
}

void Drow(Sprite &sprite, RenderWindow &window) {
	window.clear(Color::White);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cells; j++) {
			if (i == 0 || i == rows - 1 || j == 0 || j == cells - 1)
				sprite.setTextureRect(IntRect(6*18, 0, 18, 18));
			else if (j == snake.getHeadX() && i == snake.getHeadY())
				sprite.setTextureRect(IntRect(18, 0, 18, 18));
			else if (j == fruit.getX() &&  i == fruit.getY())
				sprite.setTextureRect(IntRect(2*18, 0, 18, 18));
			else if (snake.checkTail(j, i))
				sprite.setTextureRect(IntRect(3 * 18, 0, 18, 18));
			else 
				sprite.setTextureRect(IntRect(4*18, 0, 18, 18));
			
			sprite.setPosition(j * 18, i * 18);
			window.draw(sprite);
		}	
	}
}

void Game(Field &field, Snake &snake, Fruit &fruit) {
	//while (true) {
	//	
	//	prevCommand = command;
	//	
	//	this_thread::sleep_for(chrono::milliseconds(500));
	//	system("cls");
	//	if (command == 27) break;
	//	else if (command == 97) { dx = -1; dy = 0; }
	//	else if (command == 119) { dx = 0; dy = -1; }
	//	else if (command == 100) { dx = 1; dy = 0; }
	//	else if (command == 115) { dx = 0; dy = 1; }
	//	if(!field.moveSnake(dx, dy)) break;
	//	//this_thread::sleep_for(chrono::microseconds(450));
	//	field.Drow();
	//}
}

int main()
{
	//Game(field, snake, fruit);
	RenderWindow window(VideoMode(400, 400), "Snake game");
	Texture texture;
	texture.loadFromFile("C:\\Users\\shura\\source\\repos\\SFML_prog\\x64\\Debug\\tetris.png");
	Sprite sprite(texture);
	Clock clock;
	setSnake();
	setFruit();

	bool next = true;
	int dx = 0, dy = 0;

	float timer = 0, delay = 0.3;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up) {
					dx = 0; dy = -1;
					this_thread::sleep_for(chrono::milliseconds(100));
				}
				else if (event.key.code == Keyboard::Down) {
					dx = 0; dy = 1;
					this_thread::sleep_for(chrono::milliseconds(100));
				}
				else if (event.key.code == Keyboard::Left) {
					dx = -1; dy = 0;
					this_thread::sleep_for(chrono::milliseconds(100));
				}
				else if (event.key.code == Keyboard::Right) {
					dx = 1; dy = 0;
					this_thread::sleep_for(chrono::milliseconds(100));
				}
			}
		}

		if (timer > delay && (dx != 0 || dy != 0)) {
			next = moveSnake(dx, dy);
			timer = 0;
		}
			

		if (!next) break;
		Drow(sprite, window);
		window.display();
		//this_thread::sleep_for(chrono::milliseconds(2000));
	}

	return 0;
}
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include <ctime>

using namespace sf;
using namespace std;

Game::Game() {
	init();
}
void Game::init() {
	this->board_image.loadFromFile(File);
	this->map.loadFromImage(board_image);
	this->sprite.setTexture(map);

	setShips();

}
void Game::set(int sizeOfShip) {
	srand(time(NULL));
	int deck = sizeOfShip - 1;
	bool temp = false;
	Direction dir;

	while (!temp) {
		dir = static_cast<Direction>(rand() % 2);
		int e = 0;
		x = rand() % 10 + 1; y = rand() % 10 + 1;
		switch (dir) {
		case h:
			if (!((y + sizeOfShip) > 10)) {
				if (board[x][y] == 0 && board[x][y + deck] == 0) {
					e = checkShips(x, y, dir, sizeOfShip);
					if (e == 0) {
						for (int c = 0; c < sizeOfShip; c++) {
							board[x][y + c] = 1;
						}
						temp = true;
					}
				}
			}
			break;
		case v:
			if (!((x + sizeOfShip) > 10)) {
				if (board[x][y] == 0 && board[x + deck][y] == 0) {
					e = checkShips(x, y, dir, sizeOfShip);
					if (e == 0) {
						for (int c = 0; c < sizeOfShip; c++) {
							board[x + c][y] = 1;
						}
						temp = true;
					}
				}
			}
			break;
		}
	}
}
int Game::checkShips(int i, int j, Direction dir, int sizeOfShips) {
	int e = 0;
	switch (dir) {
	case h:
		if (board[i - 1][j - 1] == 1) e = 1;
		if (board[i - 1][j + sizeOfShips] == 1) e = 1;
		if (board[i + 1][j - 1] == 1) e = 1;
		if (board[i + 1][j + sizeOfShips] == 1) e = 1;
		if (board[i][j - 1] == 1) e = 1;
		if (board[i][j + sizeOfShips] == 1) e = 1;
		for (int c = 0; c < sizeOfShips; c++) {
			if (board[i - 1][j + c] == 1) e = 1;
			if (board[i + 1][j + c] == 1) e = 1;
		}
		break;
	case v:
		if (board[i - 1][j - 1] == 1) e = 1;
		if (board[i - 1][j + 1] == 1) e = 1;
		if (board[i + sizeOfShips][j - 1] == 1) e = 1;
		if (board[i + sizeOfShips][j + 1] == 1) e = 1;
		if (board[i - 1][j] == 1) e = 1;
		if (board[i + sizeOfShips][j] == 1) e = 1;
		for (int c = 0; c < sizeOfShips; c++) {
			if (board[i + c][j - 1] == 1) e = 1;
			if (board[i + c][j + 1] == 1) e = 1;
		}
		break;
	}
	return e;
}
void Game::setShips() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			board[i][j] = 5;
		}
	}

	for (int i = 1; i < N - 1; i++) {
		for (int j = 1; j < N - 1; j++) {
			board[i][j] = 0;
		}
	}

	set(4);
	set(3); set(3);
	set(2); set(2); set(2);
	set(1); set(1); set(1); set(1);
}
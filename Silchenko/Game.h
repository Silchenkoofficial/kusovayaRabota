#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

const int N = 12;

enum Direction { h, v };

class Game {
public:
	String File = "C:\\Users\\Никита\\Desktop\\kursovik\\SeaWars3\\SeaWars3\\assets\\sprites.png";
	Image board_image;
	Texture map;
	Sprite sprite;

	int x, y;
	bool win = false;

	int board[N][N] = {
		{5,5,5,5,5,5,5,5,5,5,5,5},
		{5,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,0,0,0,0,5},
		{5,0,0,0,0,0,0,0,0,0,0,5},
		{5,5,5,5,5,5,5,5,5,5,5,5},
	}; // игровое поле

	Game();
	void init();
	void setShips();
	void set(int sizeOfShip);
	int checkShips(int i, int j, Direction dir, int sizeOfShips);

};
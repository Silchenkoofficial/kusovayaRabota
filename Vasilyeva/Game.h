#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <stdio.h>
#include <string>

using namespace sf;
using namespace std;

class Game {
public:
	// ========== Свойства ========== //
		// =============== Data Network ======== //
	//    TcpSocket socket;
	//    Packet packet;
		// =============== Центр окна ========== //
	Vector2f centerWindow;
	// =============== Шрифт =============== //
	Font font;
	// =============== Цвета =============== //
	Color mainBGColor;
	// =============== Текст =============== //
	Text text;
	Text word;
	RectangleShape descriptionField;
	// =============== Изображения ============= //
	Image cellImage;
	// =============== Текстуры ============= //
	Texture cellTexture;
	// =============== Спрайты ============= //
	Sprite cell;
	// =============== Экраны ============== //
	int screen;
	// =============== Bool ================ //
	bool painted = false;
	// =============== Массивы ============= //
	char addArray[100];
	int sizeArr;
	// =============== Переменные ========== //
	int attemptCount = 9;

// ========== Методы ========== //
	Game(Vector2f centerWindow);
	void update();
	void drawCell(RenderWindow &window, char word[], string letter, bool correctWord);
	bool checkWord();
};

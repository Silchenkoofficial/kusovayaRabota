#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <stdio.h>
#include <string>

using namespace sf;
using namespace std;

class Game {
public:
	// ========== �������� ========== //
		// =============== Data Network ======== //
	//    TcpSocket socket;
	//    Packet packet;
		// =============== ����� ���� ========== //
	Vector2f centerWindow;
	// =============== ����� =============== //
	Font font;
	// =============== ����� =============== //
	Color mainBGColor;
	// =============== ����� =============== //
	Text text;
	Text word;
	RectangleShape descriptionField;
	// =============== ����������� ============= //
	Image cellImage;
	// =============== �������� ============= //
	Texture cellTexture;
	// =============== ������� ============= //
	Sprite cell;
	// =============== ������ ============== //
	int screen;
	// =============== Bool ================ //
	bool painted = false;
	// =============== ������� ============= //
	char addArray[100];
	int sizeArr;
	// =============== ���������� ========== //
	int attemptCount = 9;

// ========== ������ ========== //
	Game(Vector2f centerWindow);
	void update();
	void drawCell(RenderWindow &window, char word[], string letter, bool correctWord);
	bool checkWord();
};

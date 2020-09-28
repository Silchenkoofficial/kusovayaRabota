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
    TcpSocket socket;
    Packet packet;
    // =============== Центр окна ========== //
    Vector2f centerWindow;
    // =============== Шрифт =============== //
    Font font;
    // =============== Цвета =============== //
    Color mainBGColor;
    // =============== Текст =============== //
    Text text;
    RectangleShape descriptionField;
    // =============== Изображения ============= //
    
    // =============== Текстуры ============= //
    
    // =============== Спрайты ============= //
    
    // =============== Экраны ============== //
    int screen;
    // =============== Bool ================ //
    bool painted = false;
    
// ========== Методы ========== //
    Game(Vector2f centerWindow);
    void update();
    void drawCell(RenderWindow &window, char word[]);
};

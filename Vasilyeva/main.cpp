#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include "Game.h"

using namespace sf;
using namespace std;

char connect(TcpSocket& socket) {
	IpAddress ip = IpAddress::getLocalAddress();
	int type;
	char mode = ' ';
	string text = "Connect to: ";

	cout << ip << endl;
	cout << "Enter type of connection:\n1. Client\n2. Server" << endl;
	cin >> type;
	//    type = 1;
	switch (type) {
	case 1: {
		//            cout << "Введите IP-адрес: "; cin >> ip; cout << endl;
		socket.connect(ip, 2000);
		text += "Client";
		mode = 'c';
		break;
	}
	case 2: {
		TcpListener listener;
		listener.listen(2000);
		listener.accept(socket);
		text += "Server";
		mode = 's';
		break;
	}
	}
	return mode;
}

int main() {
	setlocale(LC_ALL, "");
	TcpSocket socket;
	Packet packet;
	char mode = connect(socket);

	RenderWindow window(VideoMode(1000, 600), "Hangman");
	Vector2f centerWindow = Vector2f(window.getSize().x / 2, window.getSize().y / 2);
	Event e;
	Vector2i pos;
	Game game(centerWindow);

	Text attemptsText("", game.font, 60);
	Text attempts("Your attempts: ", game.font, 60);
	attemptsText.setFillColor(Color::Black);
	attemptsText.setPosition(750 - attemptsText.getGlobalBounds().width, 50);
	attempts.setFillColor(Color::Black);
	attempts.setPosition(800, 50);

	char word[] = "";
	string letter;
	bool correctWord = false;
	bool painted = false;
	int attemptsCount = 9;

	while (window.isOpen()) {
		while (window.pollEvent(e)) {
			if (e.type == Event::Closed) window.close();
			if (e.type == Event::TextEntered) {
				if (mode == 'c' && game.screen == 2) {
					if (e.text.unicode < 128) {
						letter = static_cast<char>(e.text.unicode);
						for (int i = 0; i < strlen(word); i++) {
							if (word[i] == letter) {
								correctWord = true;
							}
						}
						if (correctWord)
							cout << "Correct!" << endl;
						else {
							cout << "Incorrect!" << endl;
							attemptsCount--;
						}
						packet << word << letter << correctWord << attemptsCount;
						socket.send(packet);
						packet.clear();
					}
				}
			}
		}
		if (mode == 's') {
			if (game.screen == 1) {
				game.text.setString("Please write your word in the terminal (In English)");
				game.text.setCharacterSize(58);
				game.text.setOutlineThickness(2);
				game.update();
				window.draw(game.text);
			}
			else if (game.screen == 2) {
				game.text.setString("Opponent guesses the word");
				game.update();
				if (painted) {
					if (socket.receive(packet) == Socket::Done)
						packet >> word >> letter >> correctWord >> attemptsCount;
					else
						cout << "Пакет не найден" << endl;
				}
			}
		}
		if (mode == 'c') {
			if (game.screen == 1) {
				game.text.setString("Waiting for your opponent!");
				game.text.setCharacterSize(58);
				game.text.setOutlineThickness(2);
				game.update();
				window.clear(game.mainBGColor);
				window.draw(game.text);
				window.display();
				socket.receive(packet);
				packet >> word >> letter >> correctWord >> attemptsCount;
				game.screen = 2;
			}
			else if (game.screen == 2) {
				window.clear(game.mainBGColor);
				game.text.setString("Enter a letter...");
				game.update();
			}
		}
		// Отрисовка ===================
		window.clear(game.mainBGColor);
		switch (game.screen) {
			case 1: {
				window.draw(game.text);
				window.display();
				cout << "Your word: ";
				cin >> word;
				packet << word << letter << correctWord << attemptsCount;
				socket.send(packet);
				packet.clear();
				game.screen = 2;
				break;
			}
			case 2: {
				window.draw(game.text);
				if (attemptsCount != 0) {
					game.drawCell(window, word, letter, correctWord);
					if (game.checkWord()) {
						if (mode == 's') {
							game.text.setString("You lose!");
							game.screen = 3;
						}
						if (mode == 'c') {
							game.text.setString("You win!");
							game.screen = 3;
						}
					}
				}
				else {
					if (mode == 's') {
						game.text.setString("You win!");
						game.screen = 3;
					}
					if (mode == 'c') {
						game.text.setString("You lose!");
						game.screen = 3;
					}
				}
				window.draw(attemptsText);
				attempts.setString(to_string(attemptsCount));
				window.draw(attempts);
				correctWord = false;
				painted = true;
				break;
			}
			case 3: {
				window.draw(game.text);
				break;
			}
		}
		window.display();
	}

	return 0;
}

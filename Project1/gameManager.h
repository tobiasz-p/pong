#ifndef GAMEMANAGER_H
#define GMAEMANAGER_H

#include "ball.h"
#include "menu.h"
#include "paddle.h"
#include "sizeUp.h"
#include "sizeDown.h"
#include <sstream>
#include <queue>
#include <fstream>
class gameManager
{
private:
	int score1, score2, scoreSpace;
	bool quit;
	Ball* ball;
	Paddle* player1;
	Paddle* player2;
	Menu* menu;
	sf::Font fontRetro, fontCourier;
	sf::Text text, timer, pressStartKey;
	sf::RectangleShape table, middle, win;
	std::stringstream ss;
	int windowWidth, windowHeight;
	std::clock_t start;
	Item* item1, * item2;
	bool startgame;
	bool run;
	int lastRandomized;
	bool endGame, pressStart;
	bool rules, runScoreBoard;
	sf::Texture texture_player1, texture_player2, itemTexture1, itemTexture2;
	sf::Text name[2];
	sf::RenderWindow window;
	sf::Event event;
	sf::Text playerText;
public:
	
	gameManager(int w, int h);
	~gameManager();
	int sec, min;
	void ScoreUp(Paddle* player);
	void Logic();
	void randomizeItems();
	void Run();
	void Win(sf::RenderWindow& window);
	void checkItem(Item *item);
	void saveToFile();

};
#endif

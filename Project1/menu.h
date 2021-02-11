#include <SFML/Graphics.hpp>
#include <sstream>
#ifndef MENU_H
#define MENU_H
class Menu
{
	float width;
	float height;
	float positionX;
	float positionY;
	sf::RectangleShape menuShape, buttonShape[4], zasady, scoreBoard;
	sf::Texture textureStart, textureRules, textureStats, textureQuit, textureRulesMenu;
	int selectedItemIndex;
	sf::Text scoreText, toReturn;

public:
	Menu(float w, float h, float posX, float posY);
	void moveDown();
	void moveUp();
	void draw(sf::RenderWindow& window);
	void displayScores(sf::RenderWindow& window, sf::Font& font);
	int getPressedItem();
	void displayRules(sf::RenderWindow& window);
};
#endif

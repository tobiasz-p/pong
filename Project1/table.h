#include <SFML/Graphics.hpp>
#ifndef TABLE_H
#define TABLE_H
#define THICKNESS 10
class Table
{
private:
	sf::RectangleShape tableShape;
	float x, y;

public:
	Table(float posX, float posY, float w,float h);
	inline float getX() { return x; }
	inline float getY() { return y; }

	sf::FloatRect getPosition();
	sf::RectangleShape getShape();
};
#endif
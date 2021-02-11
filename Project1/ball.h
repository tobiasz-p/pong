#include <SFML/Graphics.hpp>
#ifndef ball_h
#define ball_h

class Ball
{
private:
	sf::CircleShape ballShape;
	float x, y;
	float xV, yV;
	float originalX, originalY;

public:
	Ball(float posX, float posY);
	void Reset();
	float getX();
	float getY();
	void Move();
	void update();
	void negateXv();
	void negateYv();
	float getxV();
	float getyV();
	void setSpeed(float X, float Y);

	sf::FloatRect getPosition();
	sf::CircleShape getShape();

};
#endif
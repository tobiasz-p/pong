#include <SFML/Graphics.hpp>

#ifndef PADDLE_H
#define PADDLE_H
class Paddle
{
private:
	float x, y;
	float originalX, originalY;
	float paddleSpeed;
	sf::RectangleShape paddleShape;
	Paddle* enemy;
public:
	Paddle();
	Paddle(float posX, float posY, float sizeX, float sizeY);
	void Reset();
	float getX();
	float getY();
	void moveUp();
	void moveDown();
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();
	void update();
	void setColor(int r, int g, int b, int transparency);
	void setSize(float width, float height);
	void setSpeed(float speed);
	void setEnemy(Paddle* enemy);
	Paddle* getEnemy();
};
#endif

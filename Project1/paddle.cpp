#include <Paddle.h>
#include <SFML/Graphics.hpp>

Paddle::Paddle(float posX, float posY, float sizeX, float sizeY)
{
	originalX = posX;
	originalY = posY;
	x = posX;
	y = posY;
	paddleSpeed = .4f;

	paddleShape.setSize(sf::Vector2f(15, 150));
	paddleShape.setPosition(originalX, originalY);
	paddleShape.setFillColor(sf::Color(255, 56, 56,255));
	//paddleShape.setOutlineThickness(1);
}
sf::FloatRect Paddle::getPosition()
{
	return paddleShape.getGlobalBounds();
}
sf::RectangleShape Paddle::getShape() {
	return paddleShape;
}
void Paddle::update(){
	paddleShape.setPosition(x, y);
}
void Paddle::setColor(int r, int g, int b, int transparency) {
	paddleShape.setFillColor(sf::Color(r, g, b, transparency));
}

void Paddle::setSize(float width, float height)
{
	paddleShape.setSize(sf::Vector2f(width, height));
}

void Paddle::setSpeed(float speed) {
	paddleSpeed = speed;
}

void Paddle::setEnemy(Paddle* enemy) {
	this->enemy = enemy;
}
void Paddle::Reset() {
	x = originalX;
	y = originalY;
}

float Paddle::getX() {
	return x;
}

float Paddle::getY() {
	return y;
}
void Paddle::moveUp()
{
	y -= paddleSpeed;
}

void Paddle::moveDown()
{
	y += paddleSpeed;
}

Paddle* Paddle::getEnemy() {
	return enemy;
}


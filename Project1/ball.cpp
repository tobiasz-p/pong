#include "ball.h"

Ball::Ball(float posX, float posY)
{
	originalX = posX;
	originalY = posY;
	x = posX; y = posY;
	xV = yV = .4f;
	ballShape.setRadius(10);
	ballShape.setPosition(originalX, originalY);
	ballShape.setFillColor(sf::Color(255, 128, 0, 255));
	ballShape.setOrigin(sf::Vector2f((ballShape.getLocalBounds().left + ballShape.getLocalBounds().width) / 2.0f, (ballShape.getLocalBounds().top + ballShape.getLocalBounds().height) / 2.0f));
}

void Ball::Reset()
{
	x = originalX; y = originalY;
}


float Ball::getX() {
	return x;
}
float Ball::getY() {
	return y;
}

void Ball::update() {
	ballShape.setPosition(x, y);
}

void Ball::negateXv() {
	xV = -xV;
}
void Ball::negateYv() {
	yV = -yV;
}

sf::FloatRect Ball::getPosition(){
	return ballShape.getGlobalBounds();
}

sf::CircleShape Ball::getShape(){
	return ballShape;
}

float Ball::getxV(){
	return xV;
}

float Ball::getyV(){
	return yV;
}

void Ball::setSpeed(float X, float Y) {
	xV = X;
	yV = Y;
}
void Ball::Move() { 
	x += xV; y += yV; 
}
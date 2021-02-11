#include <item.h>
#include <SFML/Graphics.hpp>

Item::Item(int x, int y, sf::Color color, Paddle* belongingTo) {
	used = false;
	this->belongingTo = belongingTo;
	itemShape.setSize(sf::Vector2f(50, 50));
	itemShape.setPosition(x, y);
	itemShape.setFillColor(color);
	itemShape.setOutlineThickness(1);
}
Item::~Item() {
	printf("usunieto \n");
}
sf::RectangleShape Item::getShape() {
	return itemShape;
}
sf::FloatRect Item::getPosition() {
	return itemShape.getGlobalBounds();
}
void Item::setUsed() {
	used = true;
}
void Item::setNotUsed() {
	used = false;
}
bool Item::getUsed() {
	return used;
}
void Item::setColor(int r, int g, int b, int transparency) {
	itemShape.setFillColor(sf::Color(r, g, b, transparency));
}
void Item::setUseTime(std::clock_t time) {
	useTime = time;
}
std::clock_t Item::getUseTime() {
	return useTime;
}
Paddle* Item::whos() {
	return belongingTo;
}
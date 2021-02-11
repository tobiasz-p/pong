#include <table.h>


Table::Table (float posX, float posY, float w, float h)
{
	x = posX;
	y = posY;
	
	tableShape.setSize(sf::Vector2f(w, h));
	tableShape.setPosition(x, y);
	tableShape.setOutlineColor(sf::Color::Yellow);
	tableShape.setFillColor(sf::Color::Transparent);
	tableShape.setOutlineThickness(THICKNESS);
}

sf::FloatRect Table::getPosition()
{
	return tableShape.getGlobalBounds();
}

sf::RectangleShape Table::getShape()
{
	return tableShape;
}

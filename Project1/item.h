#include "paddle.h"
#ifndef ITEM_H
#define ITEM_H
class Item {
private:
	int x;
	int y;
	bool used;
	Paddle* belongingTo;
	std::clock_t useTime;
	sf::RectangleShape itemShape;
public:
	Item(int x, int y, sf::Color color, Paddle* belongingTo);
	virtual ~Item();
	virtual void use()=0;
	virtual void reset()=0;
	void setUsed();
	void setNotUsed();
	void setUseTime(std::clock_t time);
	std::clock_t getUseTime();
 	bool getUsed();
	void setColor(int r, int g, int b, int transparency);
	Paddle* whos();
	sf::RectangleShape getShape();
	sf::FloatRect getPosition();
};
#endif
#include "sizeDown.h"

void sizeDown::use() {
	Paddle* enemy = whos()->getEnemy();
	enemy->setSize(15, 75);
	setUsed();
}
void sizeDown::reset() {
	Paddle* enemy = whos()->getEnemy();
	enemy->setSize(15, 150);
}
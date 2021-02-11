#include "sizeUp.h"

void sizeUp::use() {
	whos()->setSize(15, 300);
	setUsed();

}
void sizeUp::reset() {
	whos()->setSize(15, 150);
}
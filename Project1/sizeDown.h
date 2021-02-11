#ifndef SIZEDOWN_H
#define SIZEDOWN_H
#include "item.h"
class sizeDown : public Item {
public:
	using Item::Item;
	~sizeDown() { printf("usun2\n"); };
	void use() override;
	void reset() override;
};
#endif

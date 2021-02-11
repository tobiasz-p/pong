#ifndef SIZEUP_H
#define SIZEUP_H
#include "item.h"
class sizeUp : public Item {
public:
	using Item::Item;
	~sizeUp() { printf("usun1\n"); };
	void use() override;
	void reset() override;
};
#endif
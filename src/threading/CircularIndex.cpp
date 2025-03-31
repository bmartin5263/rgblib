#include "CircularIndex.h"
#include "Assertions.h"

CircularIndex::CircularIndex(int buffSize) {
	this->size = buffSize;
	this->mask = buffSize - 1;
	this->index = 0;
}


// postfix
int CircularIndex::operator++(int) {
	this->index++;

	// Circular
	this->index = this->index & this->mask;

	return this->index;
}

bool CircularIndex::operator==(const CircularIndex &tmp) {
	ASSERT(this->size == tmp.size, "Size is not same");
	return (this->index == tmp.index);
}

bool CircularIndex::operator!=(const CircularIndex &tmp) {
  ASSERT(this->size == tmp.size, "Size is not same");
	return (this->index != tmp.index);
}

int CircularIndex::getIndex() const {
	return this->index;
}



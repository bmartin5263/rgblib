#ifndef CIRCULAR_INDEX_H
#define CIRCULAR_INDEX_H


class CircularIndex {
public:

	CircularIndex(int buffSize);
	CircularIndex() = delete;
	CircularIndex(const CircularIndex &) = delete;
	const CircularIndex &operator = (const CircularIndex &) = delete;
	~CircularIndex() = default;

	// postfix
	int operator++(int);
	bool operator==(const CircularIndex &tmp);
	bool operator!=(const CircularIndex &tmp);

	int getIndex() const;


private:
	int index;
	int size;
	unsigned int mask;
};

#endif

#pragma once
#include <vector>
#include <map>
#include <iostream>

using namespace std;

class Card
{
	friend ostream& operator<<(ostream& os, const Card& card);

public:
	Card() = default;
	Card(const char shape, const int number);
	~Card() = default;

	bool operator==(const Card& c) const;
	bool operator!=(const Card& c) const;
	bool operator>(const Card& c) const;
	bool operator>=(const Card& c) const;
	bool operator<(const Card& c) const;
	bool operator<=(const Card& c) const;

	char GetShape(void) const;
	int GetNumber(void) const;

private:
	char shape;
	int number;
	static const map<char, int> shapes;
};

ostream& operator<<(ostream& os, const vector<Card>& cards);
#include "stdafx.h"
#include "Card.h"

ostream& operator<<(ostream& os, const Card& card)
{
	return os << card.GetShape() << (card.GetNumber() > 13 ? card.GetNumber() - 13 : card.GetNumber());
}

const map<char, int> Card::shapes = {
	make_pair('S', 4),
	make_pair('D', 3),
	make_pair('H', 2),
	make_pair('C', 1)
};

Card::Card(const char shape, const int number)
	: shape(shape), number(number)
{
}

bool Card::operator==(const Card& c) const
{
	return shape == c.shape && number == c.number;
}

bool Card::operator!=(const Card& c) const
{
	return !(*this == c);
}

bool Card::operator>(const Card& c) const
{
	return number > c.number || (number == c.number && shapes.at(shape) > c.shapes.at(c.shape));
}

bool Card::operator>=(const Card& c) const
{
	return (*this == c || *this > c);
}

bool Card::operator<(const Card& c) const
{
	return !(*this >= c);
}

bool Card::operator<=(const Card& c) const
{
	return !(*this > c);
}

char Card::GetShape(void) const
{
	return shape;
}

int Card::GetNumber(void) const
{
	return number;
}

ostream& operator<<(ostream& os, const vector<Card>& cards)
{
	for (auto iter = cards.cbegin(); iter != cards.cend(); ++iter)
	{
		if (iter != cards.cbegin())
			os << ", ";
		os << *iter;
	}
	return os;
}
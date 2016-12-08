#include "stdafx.h"
#include "AnalyzedDeckForWhoIsLow.h"

ostream& operator<<(ostream& os, const AnalyzedDeckForWhoIsLow& other)
{
	return os << other.sum;
}

ostream& operator<<(ostream& os, const AnalyzedDeckForWhoIsLow* other)
{
	return os << *other;
}


AnalyzedDeckForWhoIsLow::AnalyzedDeckForWhoIsLow(const int sum)
	: sum(sum)
{
}

bool AnalyzedDeckForWhoIsLow::operator<(const AnalyzedDeckForWhoIsLow& other) const
{
	return sum < other.sum;
}

string AnalyzedDeckForWhoIsLow::GetStringOfAnalyzedDeck(void) const
{
	return to_string(sum);
}

Card AnalyzedDeckForWhoIsLow::GetHighCard(void) const
{
	throw runtime_error("Unsupported Function.");
}

Genealogy AnalyzedDeckForWhoIsLow::GetAnalyzedDeck(void) const
{
	throw runtime_error("Unsupported Function.");
}

vector<Card> AnalyzedDeckForWhoIsLow::GetDeck(void) const
{
	throw runtime_error("Unsupported Function.");
}
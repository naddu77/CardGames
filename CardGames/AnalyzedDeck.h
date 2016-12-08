#pragma once
#include "Card.h"
#include <string>

enum class Genealogy
{
	Nothing,
	HighCard,
	OnePair,
	TwoPairs,
	ThreeOfAKind,
	Straight,
	Flush,
	FullHouse,
	FourOfAKind,
	StraightFlush,
	Royal_Flush,
};

class AnalyzedDeck
{
public:
	virtual string GetStringOfAnalyzedDeck(void) const = 0;
	virtual Card GetHighCard(void) const = 0;
	virtual Genealogy GetAnalyzedDeck(void) const = 0;
	virtual vector<Card> GetDeck(void) const = 0;
};
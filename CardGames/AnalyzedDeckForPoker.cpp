#include "stdafx.h"
#include "AnalyzedDeckForPoker.h"
#include <algorithm>

const map<Genealogy, string> AnalyzedDeckForPoker::genealogy_string = {
	make_pair(Genealogy::Royal_Flush, "Royal Flush"),
	make_pair(Genealogy::StraightFlush, "Straight Flush"),
	make_pair(Genealogy::FourOfAKind, "Four of a kind"),
	make_pair(Genealogy::FullHouse, "Full House"),
	make_pair(Genealogy::Flush, "Flush"),
	make_pair(Genealogy::Straight, "Straight"),
	make_pair(Genealogy::ThreeOfAKind, "Three of a kind"),
	make_pair(Genealogy::TwoPairs, "Two Pairs"),
	make_pair(Genealogy::OnePair, "One Pair"),
	make_pair(Genealogy::HighCard, "High Card"),
	make_pair(Genealogy::Nothing, "Nothing")
};

AnalyzedDeckForPoker::AnalyzedDeckForPoker(Genealogy genealogy, const vector<Card>& deck)
	: genealogy(genealogy), deck(deck)
{
}

// sort 알고리즘을 위해 정의
bool AnalyzedDeckForPoker::operator<(const AnalyzedDeckForPoker & other) const
{
	return genealogy < other.genealogy ||
		((genealogy == other.genealogy) && (GetHighCard() < other.GetHighCard()));
}

string AnalyzedDeckForPoker::GetStringOfAnalyzedDeck(void) const
{
	return genealogy_string.at(genealogy);
}

Card AnalyzedDeckForPoker::GetHighCard(void) const
{
	return genealogy == Genealogy::FullHouse ? GetHighCard_FullHouse() : *max_element(deck.begin(), deck.end());
}

Genealogy AnalyzedDeckForPoker::GetAnalyzedDeck(void) const
{
	return genealogy;
}

vector<Card> AnalyzedDeckForPoker::GetDeck(void) const
{
	return deck;
}

Card AnalyzedDeckForPoker::GetHighCard_FullHouse(void) const
{
	return deck[2];
}

ostream& operator<<(ostream& os, const vector<AnalyzedDeckForPoker>& other)
{
	for (auto i = 0u; i < other.size(); ++i)
		os << "Player" << i + 1 << ": " << other[i] << endl;
	return os;
}

ostream& operator<<(ostream& os, const vector<AnalyzedDeckForPoker>* other)
{
	return os << *other;
}
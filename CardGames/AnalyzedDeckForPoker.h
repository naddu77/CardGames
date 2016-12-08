#pragma once
#include "AnalyzedDeck.h"
#include <memory>

class AnalyzedDeckForPoker final : public AnalyzedDeck
{
	friend ostream& operator<<(ostream& os, const AnalyzedDeckForPoker& other)
	{
		return os << other.GetStringOfAnalyzedDeck() << " [ " << other.GetDeck() << " ]";
	}

	friend ostream& operator<<(ostream& os, const AnalyzedDeckForPoker* other)
	{
		return os << *other;
	}

public:
	AnalyzedDeckForPoker(Genealogy genealogy = Genealogy::Nothing, const vector<Card>& deck = vector<Card>());
	~AnalyzedDeckForPoker() = default;

	bool operator<(const AnalyzedDeckForPoker& other) const;

	virtual string GetStringOfAnalyzedDeck(void) const override;
	virtual Card GetHighCard(void) const override;
	virtual Genealogy GetAnalyzedDeck(void) const override;
	virtual vector<Card> GetDeck(void) const override;

private:
	Genealogy genealogy;
	vector<Card> deck;
	static const map<Genealogy, string> genealogy_string;
	Card GetHighCard_FullHouse(void) const;
};

ostream& operator<<(ostream& os, const vector<AnalyzedDeckForPoker>& other);
ostream& operator<<(ostream& os, const vector<AnalyzedDeckForPoker>* other);
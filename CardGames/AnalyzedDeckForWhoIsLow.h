#pragma once
#include "AnalyzedDeck.h"
class AnalyzedDeckForWhoIsLow : public AnalyzedDeck
{
	friend ostream& operator<<(ostream& os, const AnalyzedDeckForWhoIsLow& other);
	friend ostream& operator<<(ostream& os, const AnalyzedDeckForWhoIsLow* other);

public:
	AnalyzedDeckForWhoIsLow(const int sum);
	~AnalyzedDeckForWhoIsLow() = default;

	bool operator<(const AnalyzedDeckForWhoIsLow& other) const;

	virtual string GetStringOfAnalyzedDeck(void) const override;
	virtual Card GetHighCard(void) const override;
	virtual Genealogy GetAnalyzedDeck(void) const override;
	virtual vector<Card> GetDeck(void) const override;

private:
	int sum;
};
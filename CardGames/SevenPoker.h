#pragma once
#include "CardGameFramework.h"
class SevenPoker :
	public CardGameFramework
{
public:
	SevenPoker();
	virtual ~SevenPoker() = default;

protected:
	virtual vector<shared_ptr<AnalyzedDeck>> Play(const vector<Player>& players) const override;
	virtual bool ShowResult(const vector<Player>& players, const vector<shared_ptr<AnalyzedDeck>>& result) const override;

private:
	static const vector<string> rule;
};
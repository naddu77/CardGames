#pragma once
#include "CardGameFramework.h"
#include "Player.h"

class WhoIsLow : public CardGameFramework
{
public:
	WhoIsLow();
	~WhoIsLow() = default;

protected:
	virtual vector<shared_ptr<AnalyzedDeck>> Play(const vector<Player>& players) const override;
	virtual bool ShowResult(const vector<Player>& players, const vector<shared_ptr<AnalyzedDeck>>& result) const override;

private:
	void ShowWinner(int player_number) const;
};
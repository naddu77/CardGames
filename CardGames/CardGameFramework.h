#pragma once

#include <string>
#include <random>
#include <vector>
#include <memory>
#include "Player.h"
#include "AnalyzedDeck.h"

using namespace std;

class CardGameFramework
{
public:
	CardGameFramework() = delete;
	CardGameFramework(const int player_count, const int max_card_count);
	virtual ~CardGameFramework() = default;

	void PlayTheGame(const string& start_message = "-= Start The Card Game =-");

protected:
	random_device rd;
	static const vector<char> shape;
	static const vector<int> number;
	vector<Card> cards;

	void Suffle(void);
	virtual vector<Player> HandOutCards(void) const;
	virtual vector<shared_ptr<AnalyzedDeck>> Play(const vector<Player>& players) const = 0;
	virtual bool ShowResult(const vector<Player>& players, const vector<shared_ptr<AnalyzedDeck>>& result) const = 0;

	int GetPlayerCount(void) const;
	int GetMaxCardCount(void) const;
	int GetTotalNeededCardCount(void) const;
	int GetTotalCardCount(void) const;

private:
	int player_count;
	int max_card_count;
	int total_needed_card_count;
	int total_card_count = shape.size() * number.size();

	void MakeCards(void);
};
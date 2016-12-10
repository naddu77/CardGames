#include "stdafx.h"
#include "WhoIsLow.h"
#include "Player.h"
#include "AnalyzedDeckForWhoIsLow.h"
#include <iostream>
#include <algorithm>
#include <numeric>

using namespace std;
WhoIsLow::WhoIsLow()
	: CardGameFramework(4, 7)
{
}

vector<shared_ptr<AnalyzedDeck>> WhoIsLow::Play(const vector<Player>& players) const
{
	vector<shared_ptr<AnalyzedDeck>> result;
	for (auto i = 0; i < GetPlayerCount(); ++i)
	{
		vector<int> numbers(GetMaxCardCount());
		auto deck = players[i].GetDeck();
		transform(deck.begin(), deck.end(), numbers.begin(), [](Card card) { return card.GetNumber() > 13 ? card.GetNumber() - 13 : card.GetNumber(); });
		result.emplace_back(new AnalyzedDeckForWhoIsLow(accumulate(numbers.begin(), numbers.end(), 0)));
	}
	return result;
}

bool WhoIsLow::ShowResult(const vector<Player>& players, const vector<shared_ptr<AnalyzedDeck>>& result) const
{
	for (auto i = 0; i < GetPlayerCount(); ++i)
	{
		cout << "Player" << i + 1 << ": ";
		players[i].ShowDeck();
		cout << " : sum = " << result[i]->GetStringOfAnalyzedDeck() << endl;
	}
	cout << endl;

	auto min_number = min_element(result.begin(), result.end(), [](auto element1, auto element2) {
		return stol(element1->GetStringOfAnalyzedDeck()) < stol(element2->GetStringOfAnalyzedDeck());
	});

	auto min_number_count = count_if(result.begin(), result.end(), [min_number](auto element) {
		return stol(min_number->get()->GetStringOfAnalyzedDeck()) == stol(element->GetStringOfAnalyzedDeck());
	});

	if (min_number_count < 2)
	{
		ShowWinner(min_number - result.begin());
		return true;
	}

	return false;
}

void WhoIsLow::ShowWinner(int player_number) const
{
	cout << "Winner : Player" << player_number + 1 << endl;
}
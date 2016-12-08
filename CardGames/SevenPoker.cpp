#include "stdafx.h"
#include "SevenPoker.h"
#include "SevenPokerRule.h"
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

SevenPoker::SevenPoker()
	: CardGameFramework(4, 7)
{
}

vector<shared_ptr<AnalyzedDeck>> SevenPoker::Play(const vector<Player>& players) const
{
	vector<shared_ptr<AnalyzedDeck>> result;
	for (auto player : players)
		result.emplace_back(new AnalyzedDeckForPoker(SevenPokerRule(player.GetDeck()).AnalyzeTheDeck()));
	return result;
}

bool SevenPoker::ShowResult(const vector<Player>& players, const vector<shared_ptr<AnalyzedDeck>>& result) const
{
	cout << "- Deck" << endl;
	cout << players << endl;
	cout << "- Result" << endl;
	for (auto analyzed_deck : result)
		cout << analyzed_deck->GetStringOfAnalyzedDeck() << " [ " << analyzed_deck->GetDeck() << " ]" << endl;

	// todo:: 승리조건 수정 필요
	auto winner_iter = max_element(result.begin(), result.end(), [](auto element1, auto element2)
	{
		return (element1->GetAnalyzedDeck() < element2->GetAnalyzedDeck()) ||
			((element1->GetAnalyzedDeck() == element2->GetAnalyzedDeck()) && (element1->GetHighCard() < element2->GetHighCard()));
	});

	cout << endl << "Winner : Player" << winner_iter - result.begin() + 1 << endl;

	return true;
}
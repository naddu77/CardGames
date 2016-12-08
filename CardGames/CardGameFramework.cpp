#include "stdafx.h"
#include "CardGameFramework.h"
#include <algorithm>

const vector<char> CardGameFramework::shape = { 'S', 'D', 'H', 'C' };
const vector<int> CardGameFramework::number = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14 };

CardGameFramework::CardGameFramework(const int player_count, const int max_card_count)
	: player_count(player_count), max_card_count(max_card_count)
{
	total_needed_card_count = max_card_count * player_count;
	if (total_needed_card_count > total_card_count)
		throw invalid_argument("카드 수가 부족하여 게임을 진행할 수 없습니다.");
	MakeCards();
}

void CardGameFramework::PlayTheGame(const string & start_message)
{
	cout << start_message << endl;
	Suffle();
	auto players = HandOutCards();
	auto result = Play(players);
	if (!ShowResult(players, result))
		PlayTheGame("Regame...");
}

int CardGameFramework::GetPlayerCount(void) const
{
	return player_count;
}

int CardGameFramework::GetMaxCardCount(void) const
{
	return max_card_count;
}

int CardGameFramework::GetTotalNeededCardCount(void) const
{
	return total_needed_card_count;
}

int CardGameFramework::GetTotalCardCount(void) const
{
	return total_card_count;
}

void CardGameFramework::Suffle(void)
{
	shuffle(cards.begin(), cards.end(), rd);
}

vector<Player> CardGameFramework::HandOutCards(void) const
{
	vector<Player> players(GetPlayerCount());
	for (auto i = 0; i < GetTotalNeededCardCount(); ++i)
		players[i % GetPlayerCount()].ReceiveCard(cards[i]);
	return players;
}

void CardGameFramework::MakeCards(void)
{
	for (auto i : shape)
		for (auto j : number)
			cards.emplace_back(Card(i, j));
}
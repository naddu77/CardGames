#include "stdafx.h"
#include "Player.h"
#include <iostream>

ostream& operator<<(ostream& os, const Player& other)
{
	return os << other.GetDeck();
}

void Player::ReceiveCard(const Card & card)
{
	deck.emplace_back(card);
}

void Player::ShowDeck(void) const
{
	for (auto i = 0u; i < deck.size(); ++i)
	{
		if (i != 0)
			cout << ", ";
		cout << deck[i].GetShape() << (deck[i].GetNumber() > 13 ? deck[i].GetNumber() - 13 : deck[i].GetNumber());
	}
}

const vector<Card>& Player::GetDeck(void) const
{
	return deck;
}

ostream& operator<<(ostream& os, const vector<Player>& players)
{
	for (auto i = 0u; i < players.size(); ++i)
		os << "Player" << i + 1 << ": " << players[i] << endl;
	return os;
}
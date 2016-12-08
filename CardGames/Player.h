#pragma once
#include "Card.h"
#include <vector>

using namespace std;

class Player
{
	friend ostream& operator<<(ostream& os, const Player& other);

public:
	Player() = default;
	~Player() = default;
	void ReceiveCard(const Card& card);
	void ShowDeck(void) const;
	const vector<Card>& GetDeck(void) const; 

private:
	vector<Card> deck;
};

ostream& operator<<(ostream& os, const vector<Player>& players);
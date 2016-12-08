// CardGames.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WhoIsLow.h"
#include "SevenPoker.h"
#include "SevenPokerRule.h"
#include <iostream>

using namespace std;

void TestCase(void)
{
	vector<Card> royal_flush_deck{ Card('S', 14), Card('S', 13), Card('S', 12), Card('S', 11), Card('S', 10), Card('H', 7), Card('D', 10) };
	vector<Card> straight_flush{ Card('C', 4), Card('C', 5), Card('C', 6), Card('C', 7), Card('C', 8), Card('C', 9), Card('C', 10) };
	vector<Card> four_of_a_card{ Card('C', 7), Card('S', 7), Card('D', 7), Card('H', 7), Card('C', 10), Card('S', 11), Card('S', 14) };
	vector<Card> full_house_deck{ Card('S', 14), Card('D', 14), Card('H', 14), Card('S', 7), Card('D', 7), Card('H', 7), Card('D', 10) };
	vector<Card> flush{ Card('C', 4), Card('C', 5), Card('C', 6), Card('C', 7), Card('C', 14), Card('C', 2), Card('C', 13) };
	vector<Card> straight{ Card('H', 2), Card('D', 3), Card('C', 4), Card('D', 5), Card('S', 6), Card('C', 9), Card('C', 10) };
	vector<Card> three_of_a_card{ Card('C', 3), Card('S', 3), Card('D', 3), Card('H', 7), Card('C', 10), Card('S', 11), Card('S', 14) };
	vector<Card> two_pairs{ Card('C', 3), Card('S', 3), Card('D', 7), Card('H', 7), Card('C', 10), Card('S', 11), Card('C', 11) };
	vector<Card> one_pairs{ Card('C', 3), Card('S', 3), Card('D', 7), Card('H', 8), Card('C', 10), Card('S', 14), Card('S', 11) };
	vector<Card> high_card{ Card('C', 3), Card('S', 2), Card('D', 7), Card('H', 8), Card('C', 10), Card('S', 14), Card('S', 11) };
	
	cout << SevenPokerRule(royal_flush_deck).AnalyzeTheDeck() << endl;
	cout << SevenPokerRule(straight_flush).AnalyzeTheDeck() << endl;
	cout << SevenPokerRule(full_house_deck).AnalyzeTheDeck() << endl;
	cout << SevenPokerRule(four_of_a_card).AnalyzeTheDeck() << endl;
	cout << SevenPokerRule(flush).AnalyzeTheDeck() << endl;
	cout << SevenPokerRule(straight).AnalyzeTheDeck() << endl;
	cout << SevenPokerRule(three_of_a_card).AnalyzeTheDeck() << endl;
	cout << SevenPokerRule(two_pairs).AnalyzeTheDeck() << endl;
	cout << SevenPokerRule(one_pairs).AnalyzeTheDeck() << endl;
	cout << SevenPokerRule(high_card).AnalyzeTheDeck() << endl;
}

int main()
{
	TestCase();
	try
	{
		shared_ptr<CardGameFramework> card_game(new SevenPoker);
		card_game->PlayTheGame();
		cout << endl;
		card_game.reset(new WhoIsLow);
		card_game->PlayTheGame();
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}
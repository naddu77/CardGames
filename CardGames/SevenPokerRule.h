#pragma once

#include "Card.h"
#include "AnalyzedDeckForPoker.h"
#include <vector>
#include <functional>

class SevenPokerRule
{
public:
	SevenPokerRule() = delete;
	SevenPokerRule(const vector<Card>& deck);
	~SevenPokerRule() = default;
	AnalyzedDeckForPoker AnalyzeTheDeck(void);

private:
	vector<Card> deck;
	map<int, vector<Card>> group_by_number;
	map<char, vector<Card>> group_by_shape;
	const vector<function<AnalyzedDeckForPoker(void)>> AnalyzeFunctions = {
		bind(&SevenPokerRule::IsRoyalFlush, this),
		bind(&SevenPokerRule::IsStraightFlush, this),
		bind(&SevenPokerRule::IsFourOfAKind, this),
		bind(&SevenPokerRule::IsFullHouse, this),
		bind(&SevenPokerRule::IsFlush, this),
		bind(&SevenPokerRule::IsStraight, this),
		bind(&SevenPokerRule::IsThreeOfAKind, this),
		bind(&SevenPokerRule::IsTwoPairs, this),
		bind(&SevenPokerRule::IsOnePair, this),
		bind(&SevenPokerRule::IsHighCard, this),
	};

	AnalyzedDeckForPoker IsRoyalFlush(void) const;		// 동률일 때 문양 비교
	AnalyzedDeckForPoker IsStraightFlush(void) const;	// 동률일 때 숫자 비교 후 문양 비교
	AnalyzedDeckForPoker IsFourOfAKind(void) const;		// 동률일 때 숫자 비교
	AnalyzedDeckForPoker IsFullHouse(void) const;		// 동률일 때 ThreeOfAKind를 우선적으로 숫자 비교
	AnalyzedDeckForPoker IsFlush(void) const;			// 동률일 때 문양 비교 후 숫자 비교
	AnalyzedDeckForPoker IsStraight(void) const;		// 동률일 때 숫자 비교 후 문양 비교
	AnalyzedDeckForPoker IsThreeOfAKind(void) const;	// 동률일 때 숫자 비교
	AnalyzedDeckForPoker IsTwoPairs(void) const;		// 동률일 때 숫자 비교 후 문양 비교
	AnalyzedDeckForPoker IsOnePair(void) const;			// 동률일 때 숫자 비교 후 문양 비교
	AnalyzedDeckForPoker IsHighCard(void) const;		// 동률일 때 숫자 비교 후 문양 비교

	void GroupByNumber(void);
	void GroupByShape(void);

	template<typename T>
	vector<Card> Sort(const map<T, vector<Card>>& group, bool is_ascending = true) const;

	template<typename T>
	auto Filter(const map<T, vector<Card>>& group, function<bool(const pair<T, vector<Card>>&)> Func) const;
};

template<typename T>
inline vector<Card> SevenPokerRule::Sort(const map<T, vector<Card>>& group, bool is_ascending) const
{
	vector<Card> result;
	for (auto element : group)
	{
		for (auto card : element.second)
		{
			result.push_back(card);
		}
	}
	is_ascending ? sort(result.begin(), result.end()) : sort(result.rbegin(), result.rend());
	return result;
}

template<typename T>
inline auto SevenPokerRule::Filter(const map<T, vector<Card>>& group, function<bool(const pair<T, vector<Card>>&)> Func) const
{
	map<T, vector<Card>> result;
	for (auto element : group)
	{
		if (Func(element))
			result.insert(element);
	}
	return result;
}

#include "stdafx.h"
#include "SevenPokerRule.h"
#include <functional>
#include <algorithm>

SevenPokerRule::SevenPokerRule(const vector<Card>& deck)
	: deck(deck)
{
	GroupByNumber();
	GroupByShape();
}

AnalyzedDeckForPoker SevenPokerRule::AnalyzeTheDeck(void)
{
	for (auto func : AnalyzeFunctions)
	{
		auto result_value = func();
		if (result_value.GetAnalyzedDeck() != Genealogy::Nothing)
			return result_value;
	}
	
	return AnalyzedDeckForPoker();
}

AnalyzedDeckForPoker SevenPokerRule::IsRoyalFlush(void) const
{
	auto filtered_deck = Filter<char>(group_by_shape, [](auto element) {
		return element.second.size() >= 5;
	});
	
	if (filtered_deck.empty())
		return AnalyzedDeckForPoker();
	
	auto result = SevenPokerRule(filtered_deck.begin()->second).IsStraight();
	
	return result.GetAnalyzedDeck() == Genealogy::Straight && result.GetHighCard().GetNumber() == 14 ? AnalyzedDeckForPoker(Genealogy::Royal_Flush, result.GetDeck()) : AnalyzedDeckForPoker();
}

AnalyzedDeckForPoker SevenPokerRule::IsStraightFlush(void) const
{
	auto filtered_deck = Filter<char>(group_by_shape, [](auto element) {
		return element.second.size() >= 5;
	});
	
	if (filtered_deck.empty())
		return AnalyzedDeckForPoker();
	
	auto result = SevenPokerRule(filtered_deck.begin()->second).IsStraight();
	
	return result.GetAnalyzedDeck() == Genealogy::Straight ? AnalyzedDeckForPoker(Genealogy::StraightFlush, result.GetDeck()) : AnalyzedDeckForPoker();
}

AnalyzedDeckForPoker SevenPokerRule::IsFourOfAKind(void) const
{
	auto filtered_deck = Filter<int>(group_by_number, [](auto element) {
		return element.second.size() == 4;
	});
	
	auto result_deck = Sort(filtered_deck);
	
	return !result_deck.empty() ? AnalyzedDeckForPoker(Genealogy::FourOfAKind, result_deck) : AnalyzedDeckForPoker();
}

AnalyzedDeckForPoker SevenPokerRule::IsFullHouse(void) const
{
	auto filtered_deck = Filter<int>(group_by_number, [](auto element) {
		return element.second.size() > 1;
	});
	
	if (filtered_deck.size() < 2)
		return AnalyzedDeckForPoker();
	
	auto exist_three_of_a_kind = any_of(filtered_deck.begin(), filtered_deck.end(), [](auto element) {
		return element.second.size() == 3;
	});
	
	if (!exist_three_of_a_kind)
		return AnalyzedDeckForPoker();
	
	auto sorted_deck = Sort(filtered_deck, false);
	sorted_deck.resize(5);
	
	return AnalyzedDeckForPoker(Genealogy::FullHouse, sorted_deck);
}

AnalyzedDeckForPoker SevenPokerRule::IsFlush(void) const
{
	auto filtered_deck = Filter<char>(group_by_shape, [](auto element) {
		return element.second.size() >= 5;
	});

	auto result_deck = Sort(filtered_deck, false);
	if (!result_deck.empty())
	{
		for (int i = 0; i < static_cast<int>(result_deck.size()) - 5; ++i)
			result_deck.pop_back();
	}

	return !result_deck.empty() ? AnalyzedDeckForPoker(Genealogy::Flush, result_deck) : AnalyzedDeckForPoker();
}

AnalyzedDeckForPoker SevenPokerRule::IsStraight(void) const
{
	auto top_number = -1;
	vector<Card> sorted_deck(deck);
	sort(sorted_deck.begin(), sorted_deck.end());
	auto count = 1;
	auto first_card = sorted_deck.begin();
	auto prev_card = first_card;
	for (auto iter = first_card + 1; iter != sorted_deck.end(); ++iter)
	{
		if (iter->GetNumber() == prev_card->GetNumber())
			continue;
		if (iter->GetNumber() == prev_card->GetNumber() + 1)
			count++;
		else
			count = 1;
		if (count >= 5)
			top_number = iter->GetNumber();

		prev_card = iter;
	}
	 
	vector<Card> temp(sorted_deck.size());
	auto it = copy_if(sorted_deck.begin(), sorted_deck.end(), temp.begin(), [&top_number](auto card) { return card.GetNumber() > top_number - 5 && card.GetNumber() <= top_number; });
	temp.resize(distance(temp.begin(), it));
	
	return top_number != -1 ? AnalyzedDeckForPoker(Genealogy::Straight, temp) : AnalyzedDeckForPoker();
}

// Three of a kind가 2개인 경우는 Full House에서 걸리므로 예외처리가 필요없음
AnalyzedDeckForPoker SevenPokerRule::IsThreeOfAKind(void) const
{
	auto result_deck = Filter<int>(group_by_number, [](auto element) {
		return element.second.size() == 3;
	});

	return !result_deck.empty() ? AnalyzedDeckForPoker(Genealogy::ThreeOfAKind, result_deck.begin()->second) : AnalyzedDeckForPoker();
}

AnalyzedDeckForPoker SevenPokerRule::IsTwoPairs(void) const
{
	auto filtered_deck = Filter<int>(group_by_number, [](auto element) {
		return element.second.size() == 2;
	});

	auto result_deck = Sort(filtered_deck, false);

	// Three Pairs인 경우
	if (result_deck.size() == 6)
	{
		result_deck.pop_back();
		result_deck.pop_back();
	}

	return result_deck.size() == 4 ? AnalyzedDeckForPoker(Genealogy::TwoPairs, result_deck) : AnalyzedDeckForPoker();
}

// Two Pairs 검사후 검사하기 때문에 원페어가 하나이거나 없는 경우만 해당
AnalyzedDeckForPoker SevenPokerRule::IsOnePair(void) const
{
	auto iter = find_if(group_by_number.begin(), group_by_number.end(), [](auto element) { return element.second.size() == 2; });

	return iter != group_by_number.end() ? AnalyzedDeckForPoker(Genealogy::OnePair, iter->second) : AnalyzedDeckForPoker();
}

AnalyzedDeckForPoker SevenPokerRule::IsHighCard(void) const
{
	return AnalyzedDeckForPoker(Genealogy::HighCard, vector<Card>(1, *max_element(deck.begin(), deck.end())));
}

void SevenPokerRule::GroupByNumber(void)
{
	for_each(deck.begin(), deck.end(), [&](auto card) { group_by_number[card.GetNumber()].emplace_back(card); });
}

void SevenPokerRule::GroupByShape(void)
{
	for_each(deck.begin(), deck.end(), [&](auto card) { group_by_shape[card.GetShape()].emplace_back(card); });
}
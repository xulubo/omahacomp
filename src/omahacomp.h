/*
 * omahacomp.h
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */

#ifndef OMAHACOMP_H_
#define OMAHACOMP_H_

#include <stdio.h>
#include <string.h>

class Hand {
public:
	int rank;
	int score;
	int size;
	int low8;
	char raw[5][3];	//5 cards at maxmium

	//index0:  diamonds - 0, clubs - 1, hearts - 2, spades - 3
	//index1:  'A' - 0,  '2' - 1, ... , 'J' - 10, 'Q' - 11, 'K' - 12, 'A' - 13
	//
	char cards[4][14];

	Hand();

	bool addCard(char *card);
	bool addCards(Hand& hand);
	void print();
	void clear();
	void dump();
	bool operator> (Hand& h);
	bool operator< (Hand& h);
	bool operator== (Hand& h);
	void operator= (Hand& h);
};


class RankingFilter {
protected:
	int mRank;
	char mName[100];

public:
	RankingFilter(int rank, const char* name) {
		mRank = rank;
		strcpy(mName, name);
	}

	const char* getName() {
		return mName;
	}

	virtual bool filter(Hand& hand){return false;}
};


class StraightFlush : public RankingFilter {
public:
	StraightFlush() : RankingFilter(9, "Straight Flush") {}
	bool filter(Hand& hand);

};

class FourOfAKind : public RankingFilter {
public:
	FourOfAKind() : RankingFilter(8, "4-of-a-kind") {}
	bool filter(Hand& hand);

};

class FullHouse : public RankingFilter {
public:
	FullHouse() : RankingFilter(7, "Full House") {}
	bool filter(Hand& hand);

};

class Flush : public RankingFilter {
public:
	Flush() : RankingFilter(6, "Flush") {}
	bool filter(Hand& hand);

};

class Straight : public RankingFilter {
public:
	Straight() : RankingFilter(5, "Straight") {}
	bool filter(Hand& hand);

};

class ThreeOfAKind : public RankingFilter {
public:
	ThreeOfAKind() : RankingFilter(4, "3-of-a-kind") {}
	bool filter(Hand& hand);

};

class TwoPair : public RankingFilter {
public:
	TwoPair() : RankingFilter(3, "Two Pair") {}
	bool filter(Hand& hand);

};

class OnePair : public RankingFilter {
public:
	OnePair() : RankingFilter(2, "One Pair") {}
	bool filter(Hand& hand);

};

class HighCard : public RankingFilter {
public:
	HighCard() : RankingFilter(1, "High Card") {}
	bool filter(Hand& hand);

};

class Low8 : public RankingFilter {
public:
	Low8() : RankingFilter(1, "Low 8") {}
	bool filter(Hand& hand);	
};

extern FILE *fpOutput;

#endif /* OMAHACOMP_H_ */

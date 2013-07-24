/*
 * HighCard.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */


#include "omahacomp.h"


bool HighCard::filter(Hand& hand)
{
	int cnt = 0;
	int score = 0;
	for(int i=13; i>0; i--) {
		cnt = hand.cards[0][i] + hand.cards[1][i] +  hand.cards[2][i] + hand.cards[3][i];
		if (cnt == 1) {
			score <<= 4;
			score += i;
		}
	}

	hand.rank = mRank;
	hand.score = score;
	return true;
}

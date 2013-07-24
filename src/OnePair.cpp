/*
 * OnePair.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */

#include "omahacomp.h"



bool OnePair::filter(Hand& hand)
{

	int pairs = 0;
	int cnt = 0;
	int score = 0;

	for(int i=13; i>0; i--) {
		cnt = hand.cards[0][i] + hand.cards[1][i] +  hand.cards[2][i] + hand.cards[3][i];
		if (cnt == 2) {
			pairs++;
			hand.score = i << 12;
		}
		else if (cnt == 1) {
			score <<= 4;
			score += i;
		}

	}

	if (pairs == 1) {
		hand.rank = mRank;
		hand.score += score;
		return true;
	}

	return false;
}


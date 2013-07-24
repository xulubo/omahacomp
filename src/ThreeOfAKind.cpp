/*
 * 3OfAKind.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */

#include "omahacomp.h"


bool ThreeOfAKind::filter(Hand& hand)
{
	bool found3 = false;
	int cnt = 0;
	int score = 0;

	for(int i=13; i>0; i--) {
		cnt = hand.cards[0][i] + hand.cards[1][i] +  hand.cards[2][i] + hand.cards[3][i];
		if (cnt == 3) {
			found3 = true;
			hand.score = i*10000;
		}
		else if (cnt == 1) {
			score *= 100;
			score += i;
		}
	}

	if (found3) {
		hand.rank = mRank;
		hand.score += score;
		return true;
	}

	return false;
}


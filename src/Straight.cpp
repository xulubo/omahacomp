/*
 * Straight.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */


#include "omahacomp.h"


bool Straight::filter(Hand& hand)
{
	int cnt = 0;
	int score = 0;
	int set = 0;
	for(int i=0; i<14 && cnt < 5; i++) {
		set = hand.cards[0][i] + hand.cards[1][i] + hand.cards[2][i] + hand.cards[3][i];
		if (set) {
			cnt ++;
			score = i;
		}
		else {
			cnt = 0;
		}
	}

	if (cnt == 5) {
		hand.rank = mRank;
		hand.score = score;
		return true;
	}

	return false;
}


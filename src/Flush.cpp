/*
 * Flush.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */


#include "omahacomp.h"



bool Flush::filter(Hand& hand)
{
	int cnt = 0;
	int score = 0;

	for(int i=0; i<4 && cnt<5; i++) {
		cnt = 0;
		score = 0;
		for(int j=13; j>0; j--) {
			cnt += hand.cards[i][j];
			if (hand.cards[i][j]) {
				score <<= 4;
				score += j;
			}
		}
	}

	if (cnt == 5) {
		hand.rank = mRank;
		hand.score = score;
		return true;
	}
	else {
	}

	return false;
}

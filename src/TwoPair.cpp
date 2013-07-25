/*
 * TwoPair.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */


#include "omahacomp.h"

bool TwoPair::filter(Hand& hand){

	int pairs = 0;
	int cnt = 0;
	int pairScore = 0;
	int singleScore = 0;

	for(int i=13; i>0; i--) {
		cnt = hand.cards[0][i] + hand.cards[1][i] +  hand.cards[2][i] + hand.cards[3][i];
		if (cnt == 2) {
			pairs++;
			pairScore <<= 4;
			pairScore += i;
		}
		else if (cnt == 1) {
			singleScore = i;
		}

	}

	if (pairs == 2) {
		hand.rank = mRank;
		hand.score = (pairScore << 4) + singleScore;
		return true;
	}

	return false;
}

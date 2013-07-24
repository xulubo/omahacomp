/*
 * FullHouse.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */


#include "omahacomp.h"


bool FullHouse::filter(Hand& hand)
{
	bool found3=0, found2=0;
	int cnt = 0;

	//A is the biggest, ignore element 0
	for(int i=1; i<14; i++) {
		cnt = hand.cards[0][i] + hand.cards[1][i] +  hand.cards[2][i] + hand.cards[3][i];
		if (cnt == 3) {
			hand.score += i * 100;
			found3 = true;
		}
		else if (cnt == 2) {
			hand.score += i;
			found2 = true;
		}
	}

	if (found3 && found2) {
		hand.rank = mRank;
		return true;
	}

	return false;
}


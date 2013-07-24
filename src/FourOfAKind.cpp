/*
 * 4OfAKind.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */


#include "omahacomp.h"
#include <stdio.h>

bool FourOfAKind::filter(Hand& hand)
{
	bool found = false;
	hand.score = 0;

	//A is the biggest, so skip the first element
	for(int i=1; i< 14; i++) {

		if (hand.cards[0][i] && hand.cards[1][i] &&  hand.cards[2][i] && hand.cards[3][i] ) {
			hand.rank = mRank;
			hand.score += i*100;
			found = true;
		}
		else {
			hand.score += (hand.cards[0][i] + hand.cards[1][i] +  hand.cards[2][i] + hand.cards[3][i]) *i;
		}
	}

	return found;
}


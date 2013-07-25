/*
 * Low8.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */


#include "omahacomp.h"

bool Low8::filter(Hand& hand){

	int cnt = 0;
	int score = 0;

	for(int i=7; i>=0; i--) {
		cnt = hand.cards[0][i] + hand.cards[1][i] +  hand.cards[2][i] + hand.cards[3][i];
		if (cnt == 1) {
			score <<= 4;
			score += (i+1);
		}
		else if (cnt > 1) {
			return false;
		}
	}

	if (score > 0x10000) {
		hand.score = score;
		hand.low8 = (score & 0x0F) == 1 ? score + 0x09 : score;
		return true;
	}

	return false;
}

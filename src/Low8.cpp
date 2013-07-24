/*
 * Low8.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */


#include "omahacomp.h"

bool Low8::filter(Hand& hand){

	int cnt = 0;
	int low8 = 0;

	for(int i=7; i>=0; i--) {
		cnt = hand.cards[0][i] + hand.cards[1][i] +  hand.cards[2][i] + hand.cards[3][i];
		if (cnt == 1) {
			low8 <<= 4;
			low8 += i == 0 ? 0xA : i+1;
		}
		else if (cnt > 1) {
			return false;
		}
	}

	if (low8 > 0x10000) {
		hand.low8 = low8;
		return true;
	}

	return false;
}

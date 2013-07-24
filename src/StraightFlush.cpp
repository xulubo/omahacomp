/*
 * StraightFlush.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */



#include "omahacomp.h"
#include <stdio.h>

extern FILE *fpOutput;
bool StraightFlush::filter(Hand& hand) {
	int cnt=0;
	int score;

	//find 5 continous cards
	for(int i=0; i<4 && cnt<5; i++) {
		cnt = 0;
		score = 0;
		for(int j=0; j<14 && cnt<5; j++) {
			if (hand.cards[i][j]) {
				cnt++;
				score = j;
			}
			else {
				cnt = 0;
				score = 0;
			}
		}
	}

	if (cnt == 5) {
		hand.rank = mRank;
		hand.score = score;
		return true;
	}

	return false;
}

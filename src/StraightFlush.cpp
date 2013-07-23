/*
 * StraightFlush.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */



#include "omahacomp.h"

class StraightFlush : public RankingFilter {
public:
	StraightFlush() : RankingFilter(9) {}
	bool filter(Hand& hand);

};

bool StraightFlush::filter(Hand& hand) {
	int count;
	int score;

	//find 5 continous cards
	for(int i=0; i<4 && count<=5; i++) {
		hand.cards[i][13] = hand.cards[i][0];
		count = 0;
		score = -1;
		for(int j=0; j<14 && count <= 5; j++) {
			if (hand.cards[i][j]) {
				count ++;
				if (score == -1) {
					score = hand.cards[i][j];
				}
			}
			else {
				count = 0;
				score = -1;
			}
		}
	}

	if (count == 5) {
		hand.setRank(mRank);
		hand.setScore(score);
		return true;
	}

	return false;
}

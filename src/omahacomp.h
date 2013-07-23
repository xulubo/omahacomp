/*
 * omahacomp.h
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */

#ifndef OMAHACOMP_H_
#define OMAHACOMP_H_


struct Hand {
	int rank;
	int score;
	//index0:  diamonds - 0, clubs - 1, hearts - 2, spades - 3
	//index1:  'A' - 0,  '2' - 1, ... , 'J' - 10, 'Q' - 11, 'K' - 12, 'A' - 13
	//
	char cards[4][14];

	Hand();
	void setRank(int rank);
	void setScore(int score);
	void addCard(char *card);
	bool operator>= (Hand h);
};


class RankingFilter {
protected:
	int mRank;

public:
	RankingFilter(int rank) {
		mRank = rank;
	}

	bool filter(Hand& hand);
};


#endif /* OMAHACOMP_H_ */

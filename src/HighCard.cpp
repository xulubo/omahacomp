/*
 * HighCard.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */




class HighCard : public RankingFilter {
public:
	HighCard() : RankingFilter(1) {}
	bool filter(Hand& hand);

};

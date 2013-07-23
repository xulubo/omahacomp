/*
 * TwoPair.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */




class TwoPair : public RankingFilter {
public:
	TwoPair() : RankingFilter(3) {}
	bool filter(Hand& hand);

};

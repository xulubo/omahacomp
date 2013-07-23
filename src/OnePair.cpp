/*
 * OnePair.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */




class OnePair : public RankingFilter {
public:
	OnePair() : RankingFilter(2) {}
	bool filter(Hand& hand);

};

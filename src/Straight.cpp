/*
 * Straight.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */




class Straight : public RankingFilter {
public:
	Straight() : RankingFilter(5) {}
	bool filter(Hand& hand);

};

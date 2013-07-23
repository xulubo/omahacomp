/*
 * FullHouse.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */




class FullHouse : public RankingFilter {
public:
	FullHouse() : RankingFilter(7) {}
	bool filter(Hand& hand);

};

/*
 * Flush.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */





class Flush : public RankingFilter {
public:
	Flush() : RankingFilter(6) {}
	bool filter(Hand& hand);

};

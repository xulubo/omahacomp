/*
 * 4OfAKind.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */




class ForOfAKind : public RankingFilter {
public:
	ForOfAKind() : RankingFilter(8) {}
	bool filter(Hand& hand);

};

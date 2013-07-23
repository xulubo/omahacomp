/*
 * 3OfAKind.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: LUBO
 */




class ThreeOfAKind : public RankingFilter {
public:
	ThreeOfAKind() : RankingFilter(4) {}
	bool filter(Hand& hand);

};

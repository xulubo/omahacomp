//============================================================================
// Name        : omahacomp.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : 
//============================================================================


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omahacomp.h"

#define CARD_IN_HAND 4
#define BUFSIZE 1024


FILE *fpOutput = NULL;

RankingFilter *gFilters[9];
StraightFlush straightFlush;
FourOfAKind fourOfAKind;
FullHouse fullHouse;
Flush flush;
Straight straight;
ThreeOfAKind threeOfAKind;
TwoPair twoPair;
OnePair onePair;
HighCard highCard;
Low8 low8Filter;

int  gIndex=0;
Hand *gTwoOutOfHands = NULL;
Hand *gThreeOutOfBoards = NULL;
char subset[3][3];

/**
 * List all combinations of cards C(m, n) and save the result in an    
 * array pointed to by out
 * Params:
 *     cards:  pointing to an array of cards, each card consist of 2 char
 *     k:      number of cards to take out in total cards, non changeable
 *     m:      total number of cards
 *     n:      number of cards to take out in the left cards, used in the recursion algorithm
 *     out:    used to save all the combination of cards
 */
void combine(char (*cards)[3], const int k, int m, int n, Hand* out) 
{ 
	int i, j; 

	for (i = m; i >= n; i--){
		strcpy(subset[n-1], cards[i-1]);
		//out[n] = i;
		if (n > 1){ 
			combine(cards, k, i - 1, n - 1, out); 
		}else{ 
			Hand hand;
			for (j = k; j > 0; j--){ 
				out[gIndex].addCard(subset[j-1]);
			} 
			//out[gIndex].print();
			gIndex++;
		} 
	} 

	return; 
} 

/**
 * Used to set the hand's rank
 * Params:
 *      hand: hand of cards
 * 
 * Return:
 *      hand.rank and hand.score will be set upon success return
 */
bool rank(Hand& hand) {
	for(int i=8; i>=0; i--) {
		if (gFilters[i]->filter(hand)) {
			return true;
		}
	}
	return false;
}

/** 
 * Find cards with highest rank and lowest rank in the combination of cards
 * Params:
 *      pHands: pointing to an array of hand
 *      hi:     save the hand with highest rank
 *      lo:     save the hand with lowest rank
 */
void findHiAndLo(char (*pHands)[3], Hand& hi, Hand& lo) {

	gIndex = 0;

	//C(4, 2) = 6
	gTwoOutOfHands = new Hand[6];
	combine(pHands, 2, CARD_IN_HAND, 2, gTwoOutOfHands);
	
	Hand handCombinations[60];
	Hand *p = handCombinations;
	for(int i=0; i<6; i++) {
		for(int j=0; j<10; j++) {
			p->addCards(gTwoOutOfHands[i]);
			p->addCards(gThreeOutOfBoards[j]);
			
			if (rank(*p)) {
				if (*p > hi) {
					hi = *p;
				}
			}

			if (low8Filter.filter(*p)) {
				if (lo.low8 == 0 || p->low8 < lo.low8) {
					lo = *p;
				}
			}

			p++;
		}
	}


	delete[] gTwoOutOfHands;
}

/** 
 * Get the highest rank of cards and lowest card in the combinations
 */
int evaluate(char* sHandA, char* sHandB, char* sBoard) {
	char handA[CARD_IN_HAND][3],  handB[CARD_IN_HAND][3], board[5][3];
	if (4 != sscanf(sHandA, "%[^-]-%[^-]-%[^-]-%s", handA[0], handA[1], handA[2], handA[3])) {
		return 1;
	}

	if (4 != sscanf(sHandB, "%[^-]-%[^-]-%[^-]-%s", handB[0], handB[1], handB[2], handB[3])) {
		return 2;
	}

	if (5 != sscanf(sBoard, "%[^-]-%[^-]-%[^-]-%[^-]-%s", board[0], board[1], board[2], board[3], board[4])) {
		return 3;
	}

	gIndex = 0;
	gThreeOutOfBoards = new Hand[10];
	combine(board, 3, 5, 3, gThreeOutOfBoards);


	Hand hiA, loA, hiB, loB;
	findHiAndLo(handA, hiA, loA);
	findHiAndLo(handB, hiB, loB);

	fprintf(fpOutput, "=> ");

	if (hiA > hiB) {
		fprintf(fpOutput, "HandA wins Hi (%s);\t", gFilters[hiA.rank-1]->getName());
	}
	else if (hiA == hiB) {
		fprintf(fpOutput, "Split Pot Hi (%s);\t", gFilters[hiA.rank-1]->getName());
	}
	else {
		fprintf(fpOutput, "HandB wins Hi (%s);\t", gFilters[hiB.rank-1]->getName());
	}

	if (loA.low8 == 0 && loB.low8 == 0) {
		fprintf(fpOutput, "No hand qualified for Low");
	}
	else if (loA.low8 == loB.low8) {
		fprintf(fpOutput, "Split Pot Low (%X)", loA.low8);
	}
	else if (loB.low8 == 0 || (loA.low8 < loB.low8 && loA.low8 != 0) ) {
		fprintf(fpOutput, "HandA wins Lo (%X);", loA.low8);
	}
	else {
		fprintf(fpOutput, "HandB wins Lo (%X);", loB.low8);
	}

	fprintf(fpOutput, "\n\n");
	delete[] gThreeOutOfBoards;
	return 0;
}

void init() {

	gFilters[8] = &straightFlush;
	gFilters[7] = &fourOfAKind;
	gFilters[6] = &fullHouse;
	gFilters[5]= &flush;
	gFilters[4] = &straight;
	gFilters[3] = &threeOfAKind;
	gFilters[2] = &twoPair;
	gFilters[1] = &onePair;
	gFilters[0] = &highCard;

}
int main(int argc, char*argv[]) {
	char line[BUFSIZE];
	char sHandA[BUFSIZE], sHandB[BUFSIZE], sBoard[BUFSIZE];
	int n;
	int ret = 0;

	if (argc != 3) {
		fprintf(stderr, "Usage: omahacomp.cpp input.txt output.txt\r\n");
		return 1;
	}

	FILE *fpInput = fopen(argv[1], "r");
	if (fpInput == NULL) {
		fprintf(stderr, "Input file can't be opened\r\n");
		return 2;
	}

	fpOutput = fopen(argv[2], "w");
	if (fpOutput == NULL) {
		fprintf(stderr, "Ouput file can't be opened\r\n");
		fclose(fpInput);
		return 3;
	}

	init();


	while(fgets(line, BUFSIZE, fpInput)) {
		n = sscanf(line, "HandA:%s HandB:%s Board:%s", sHandA, sHandB, sBoard);
		if (n != 3) {
			fprintf(stderr, "Input format must be: HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-7d Board:Ah-Kh-5s-2s-Qd\r\n");
			return 4;
		}

		fprintf(fpOutput, "HandA:%s ", sHandA);
		fprintf(fpOutput, "HandB:%s ", sHandB);
		fprintf(fpOutput, "Board:%s\n", sBoard);

		if (evaluate(sHandA, sHandB, sBoard) != 0) {
			ret = 5;
			fprintf(stderr, "evaluate error\n");
			break;
		}
	}

	fclose(fpInput);
	fclose(fpOutput);

	return ret;
}

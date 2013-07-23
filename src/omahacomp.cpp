//============================================================================
// Name        : omahacomp.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//mapping 'a', 'b', 'c' , 'd', 'e','f','g','h','i','j','k','l','m','n','o','p','q','r', 's'
//to suit index
char SUIT_INDEX[] = {-1, -1, 1 , 0, -1, -1, -1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3};

//mapping '0','1','2','3','4','5', '6','7','8','9', ':',';','<','=','>','?','@','A','B','C','D','E','F','G',
//        'H','I','J','K','L','M','N','O','P','Q','R','S','T'
//to point index
char POINT_INDEX[] = {0,1,2,3,4,5,6,7,8,9,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1
		,10,12,-1,-1,-1,11,-1,-1,-1,-1,9};

#include "omahacomp.h"
// Ad (Ace diamonds)
// Kc (King clubs)
// Qh (Queen hearts)
// Js (Jack spades)
// Td (10 diamonds)
// 9s (9 spades)

Hand::Hand() {
	rank = 0;
	score = -1;
	memset(cards, 0, sizeof(cards));
}

void Hand::addCard(char *card) {
	int suit = SUIT_INDEX[card[1]-'a'];
	int point = POINT_INDEX[card[0]-'0'];
	cards[suit][point] = 1;
}

bool Hand::operator>=(Hand h) {
	if (rank > h.rank) {
		return true;
	}
	else if (rank == h.rank) {
		return score >= h.score ? true : false;
	}
	else {
		return false;
	}
}
#define BUFSIZE 1024

int findHiAndLo(char** hand, char** board,  Hand& hi, Hand& lo) {

}

int evaluate(char* sHandA, char* sHandB, char* sBoard) {
	char handA[4][3],  handB[4][3], board[5][3];
	if (4 != sscanf(sHandA, "%s-%s-%s-%s", handA[0], handA[1], handA[2], handA[3])) {
		return 1;
	}

	if (4 != sscanf(sHandB, "%s-%s-%s-%s", handB[0], handB[1], handB[2], handB[3])) {
		return 2;
	}

	if (5 != sscanf(sBoard, "%s-%s-%s-%s-%s", board[0], board[1], board[2], board[3], board[4])) {
		return 3;
	}

	Hand hiA, loA, hiB, loB;
	findHiAndLow(handA, board, hiA, loA);
	findHiAndLow(handB, board, hiB, loB);

	return 0;
}

int main(int argc, char*argv[]) {
	char line[BUFSIZE];
	char sHandA[BUFSIZE], sHandB[BUFSIZE], sBoard[BUFSIZE];
	int n;

	if (argc != 3) {
		fprintf(stderr, "Usage: omahacomp.cpp input.txt output.txt\r\n");
		return 1;
	}

	FILE *fp = fopen(argv[1], "r");
	if (fp == NULL) {
		fprintf(stderr, "Input file can't be opened\r\n");
		return 2;
	}

	while(fgets(line, BUFSIZE, fp)) {
		n = sscanf(line, "HandA:%s HandB:%s Board:%s", sHandA, sHandB, sBoard);
		if (n != 3) {
			fprintf(stderr, "Input format must be: HandA:Ac-Kd-Jd-3d HandB:5c-5d-6c-7d Board:Ah-Kh-5s-2s-Qd\r\n");
			return 2;
		}

		printf("HandA:%s\r\n", sHandA);
		printf("HandB:%s\r\n", sHandB);
		printf("Board:%s\r\n", sBoard);

		if (evaluate(sHandA, sHandB, sBoard) != 0) {
			break;
		}

		break;
	}
	return 0;
}

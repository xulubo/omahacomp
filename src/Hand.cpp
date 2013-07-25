#include "omahacomp.h"

// Ad (Ace diamonds)
// Kc (King clubs)
// Qh (Queen hearts)
// Js (Jack spades)
// Td (10 diamonds)
// 9s (9 spades)

#define SUIT_INDEX(c) (suit_index[(c) - 'a'])
#define POINT_INDEX(c) (point_index[(c) - '2'])

//mapping 'a', 'b', 'c' , 'd', 'e','f','g','h','i','j','k','l','m','n','o','p','q','r', 's'
//to suit index
char suit_index[] = {-1, -1, 1 , 0, -1, -1, -1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 3};

//mapping '0','1','2','3','4','5', '6','7','8','9', ':',';','<','=','>','?','@','A','B','C','D','E','F','G',
//        'H','I','J','K','L','M','N','O','P','Q','R','S','T'
//to point index
char point_index[] = {1,2,3,4,5,6,7,8,-1,-1,-1,-1,-1,-1,-1,0,-1,-1,-1,-1,-1,-1,-1,-1
,10,12,-1,-1,-1,-1,-1,11,-1,-1,9};


Hand::Hand() {
	clear();
}

bool Hand::addCard(char *card) {
	//5 cards maximum
	if (this->size >= 5) {
		return false;
	}

	int suit = SUIT_INDEX(card[1] | 0x20);
	int point = POINT_INDEX(card[0]);
	if (suit == -1 || point == -1) {
		fprintf(stderr, "illegal value  %s\r\n", card);
		return false;
	}

	cards[suit][point] = 1;
	if (point == 0) {
		cards[suit][13] = 1;
	}

	strcpy(this->raw[this->size], card);

	this->size++;
	return true;
}

bool Hand::addCards(Hand& hand) {
	for(int i=0; i<hand.size; i++) {
		if (!addCard(hand.raw[i])) {
			return false;
		}
	}

	return true;
}

void Hand::print() {
	for(int i=0; i<this->size; i++) {
		fprintf(fpOutput, "%s, ", this->raw[i]);
	}
}

void Hand::dump() {
	print();
	fprintf(fpOutput, "\n   A 2 3 4 5 6 7 8 9 T J Q K A\n");
	for(int i=0; i<4; i++) {
		fprintf(fpOutput, "%d:", i);
		for(int j=0; j<14; j++) {
			fprintf(fpOutput, "% d", this->cards[i][j]); 
		}
		fprintf(fpOutput, "\n");
	}


}

void Hand::clear() {
	this->rank = 0;
	this->score = 0;
	this->size = 0;
	this->low8 = 0;
	memset(this->cards, 0, sizeof(this->cards));
	memset(this->raw, 0, sizeof(this->raw));
}

bool Hand::operator>(Hand& h) {
	if (this->rank > h.rank) {
		return true;
	}
	else if (this->rank == h.rank) {
		return this->score > h.score ? true : false;
	}
	else {
		return false;
	}
}

bool Hand::operator<(Hand& h) {
	if (this->rank < h.rank) {
		return true;
	}
	else if (this->rank == h.rank) {
		return this->score < h.score ? true : false;
	}
	else {
		return false;
	}
}

bool Hand::operator==(Hand& h) {
	return this->rank == h.rank && this->score == h.score;
}

void Hand::operator=(Hand& h) {
	this->clear();
	this->addCards(h);
	this->rank = h.rank;
	this->score = h.score;
	this->low8 = h.low8;
}

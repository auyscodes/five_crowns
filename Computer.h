//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_COMPUTER_H
#define FIVECROWNS_COMPUTER_H


#include "Player.h"

class Computer: public Player {
public:
	bool playGame();
	static void helpPick(CardCollection _hand);
	static void helpThrow(CardCollection _hand, CardInterface* _card);
	static bool canGoOutWithoutPicking(CardCollection hand, int&score, vector<vector<CardInterface*>>& arrgnmnt);
	static bool pickCardFromDiscardPile(CardCollection hand, int hand_score , int&index, vector<vector<CardInterface*>>& arrgnmnt, int&score);
	
private:
	static int getIndxToRmvCardAtHlpr( CardInterface* card, int& newScore, vector<vector<CardInterface*>>& newArrgnmnt, const int& currScore, CardCollection currHand);
	static void printCardsArrgmnt(const vector<vector<CardInterface*>>& cardsArgmnt);
	

	
};


#endif //FIVECROWNS_COMPUTER_H


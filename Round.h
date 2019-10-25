//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_ROUND_H
#define FIVECROWNS_ROUND_H


#include "Player.h"
#include "DrawPile.h"
#include "Deck.h"
#include "DiscardPile.h"
#include "CardPile.h"
#include "DataLayer.h"


#include <map>

class Round {
public:

	
    Round( DataLayer* dataLayer);
	void startGame();
    int getRoundNumber(){
        return this->numCardsToDeal - 2; // in round 1 we deal 3 cards
    }
	void printCardsArrangement(const vector<vector<CardInterface*>>& cardsArrgnment);
    void collectCardsFromPiles();
   
	// destructor not needed 
private:

    int numCardsToDeal;
    const int startRound = 1;
	int playersGoneOut = 0; // 
    DataLayer* dataLayer;
    string convertNumCardsToDealToWildCards(int numCardsToDeal);
    bool checkGoOutPossible(CardCollection hand, int& score, vector<vector<CardInterface*>>& minBranch);
	void notifyOtherPlayers(const vector<Player*>* players); 
	void forceGoOut(CardCollection hand, int& score, vector<vector<CardInterface*>>& cardsArgmnt);
	bool tryGoOut(CardCollection hand, int& minScore, vector<vector<CardInterface*>>& arrgnMnt);
	void deal();
	
};


#endif //FIVECROWNS_ROUND_H

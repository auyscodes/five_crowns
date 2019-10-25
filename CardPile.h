//
// Created by nbhat on 9/16/2019.
//

#ifndef FIVECROWNS_CARDPILE_H
#define FIVECROWNS_CARDPILE_H


#include "CardCollection.h"

/*
	Singleton instance made for the purpose of holding multiple decks in the card
*/
class CardPile: public CardCollection {
public:
	/*
		Gets the singleton instance of the class
	*/
    static CardPile* getInstance();
	// Do not need destructor 
	// Active throughout the lifecycle of the program
private:
	/*
		Constructor hidden for creating singleton
	*/
    CardPile();
	/*
		Stores the singleton instance
	*/
    static CardPile* instance;
};


#endif //FIVECROWNS_CARDPILE_H

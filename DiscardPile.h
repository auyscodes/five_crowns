//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_DISCARDPILE_H
#define FIVECROWNS_DISCARDPILE_H

#include <iostream>
#include "CardCollection.h"

/*
	Singleton class that stores discard pile cards
*/
class DiscardPile: public CardCollection {
public:
	/*
		Gets the singleton instance of the class
	*/
    static DiscardPile* getInstance();
	// Do not need destructor 
	// Active throughout the lifecycle of the program


private:
	/*
		Constructor hidden for creating singleton
	*/
    DiscardPile();
	/*
		Stores the singleton instance
	*/
    static DiscardPile * instance;
};


#endif //FIVECROWNS_DISCARDPILE_H

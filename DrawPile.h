//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_DRAWPILE_H
#define FIVECROWNS_DRAWPILE_H


#include "CardCollection.h"

/*
	Singleton class that holds the drawpile
*/
class DrawPile: public CardCollection {
public:
    static DrawPile* getInstance();
	// Do not need destructor 
	// Active throughout the lifecycle of the program
private:
	
    DrawPile();
	
    static DrawPile* instance;

};


#endif //FIVECROWNS_DRAWPILE_H

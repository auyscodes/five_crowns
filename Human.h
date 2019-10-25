//
// Created by nbhat on 9/15/2019.
//

#ifndef FIVECROWNS_HUMAN_H
#define FIVECROWNS_HUMAN_H


#include "Player.h"

class Human: public Player {
public:
	// Constructor and destructor not required

	// returns true if the player wants to go out
	bool playGame();
	
private:
	
	bool moveHelper(); 
	
	void throwCardAtIndex();

	bool getCardOrGoOut(CardInterface*& pickedCard);
	
};


#endif //FIVECROWNS_HUMAN_H

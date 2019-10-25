//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_JOKER_H
#define FIVECROWNS_JOKER_H


#include "CardInterface.h"

/*
 * Card of type Joker is represented by saving as suit J in the project.
	The number of joker ie. 1 in J1 is represented as face in the game.
	project*/

class Joker: public CardInterface {
public:
	
    string toString();
    string getFace();
    string getSuit();
    void setFace(string face);
    void setSuit(string suit);

};


#endif //FIVECROWNS_JOKER_H

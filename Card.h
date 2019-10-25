//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_CARD_H
#define FIVECROWNS_CARD_H


#include <iostream>
#include <string>
#include "CardInterface.h"

using namespace std;
/*
	Represents a normal card 
	For five crowns: Cards with face 3-K and suits Hearts, Spades, Diamond, Tridents and Clubs
*/

class Card: public CardInterface{
public:
	// Default constructor not required 
	/*
		Virtual function implementation of CardInterface
	*/
    string toString();
	/*
		Accessor for face
	*/
    string getFace();
	/*
		Accessor for suit
	*/
    string getSuit();
	/*
		Mutator for face
	*/
    void setFace(string face);
	/*
		Mutator for suit
	*/
    void setSuit(string suit);
	// does not need destructor


};
#endif //FIVECROWNS_CARD_H

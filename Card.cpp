//
// Created by nbhat on 9/9/2019.
//

#include "Card.h"


/*
Function Name: toString
Purpose: Get string representation of card object 3S, JD, etc.
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
string Card::toString() {
    return CardInterface::getFace() + CardInterface::getSuit();
}
/*
Function Name: getFace
Purpose: Get string representation a cards face i.e in 3S => 3 is the face
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
string Card::getFace() {
    return CardInterface::getFace();
}
/*
Function Name: getSuit
Purpose: Get string representation of suit i.e. in 3S => S is the suit
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
string Card::getSuit() {
    return CardInterface::getSuit();
}


/*
Function Name: setFace
Purpose: Set the card's face ie. 3 for the 3 of spades
Parameters: face, face of the card 
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Card::setFace(string face) {
    CardInterface::setFace(face);
}
/*
Function Name: setSuit
Purpose: set the suit of the card, ie for spades => S
Parameters: suit, suit of the card as string
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Card::setSuit(string suit) {
    CardInterface::setSuit(suit);
}

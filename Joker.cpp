//
// Created by nbhat on 9/9/2019.
//

#include "Joker.h"

/*
Function Name: toString
Purpose: Get string representation of joker object e.g. J1, J2, J3
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
string Joker::toString() {

    return CardInterface::getSuit()+ CardInterface::getFace();
}
/*
Function Name: getFace
Purpose: Get string representation of joker's number i.e in J1 => 1 is the face
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
string Joker::getFace() {

    return CardInterface::getFace();
}
/*
Function Name: getSuit
Purpose: Get string representation of joker's type i.e. in J1 => J is the type
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
string Joker::getSuit() {

    return CardInterface::getSuit();
}


/*
Function Name: setFace
Purpose: Set the joker number 
Parameters: face, number representing joker i.e 1 in joker J1
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Joker::setFace(string face) {
    CardInterface::setFace(face);
}
/*
Function Name: setSuit
Purpose: set the card is joker type i.e. J
Parameters: suit, represent joker type
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Joker::setSuit(string suit) {
    CardInterface::setSuit(suit);
}

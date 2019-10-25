//
// Created by nbhat on 9/16/2019.
//

#include "CardPile.h"
/*
Function Name: getInstance
Purpose: Gets the singleton instance of object that represents cardPile
Parameters: none
Return Value: cardPile object
Local Variables: none
Algorithm: If instance is null, create new or return the already created instance
Assistance Received: none

*/
CardPile *CardPile::getInstance() {
    if (instance==NULL){
        instance = new CardPile();
    }
    return instance;
}

CardPile* CardPile::instance = 0;
/*
Function Name: CardPile
Purpose: Constructor for creating singleton instance of cardPile. Private constructor
Parameters: none
Return Value: CardPile object
Local Variables: none
Algorithm: none
Assistance Received: none

*/
CardPile::CardPile() {

}

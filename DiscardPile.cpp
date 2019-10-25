//
// Created by nbhat on 9/15/2019.
//

#include "DiscardPile.h"
/*
Function Name: getInstance
Purpose: Gets the singleton instance of object that represents discardpile
Parameters: none
Return Value: DiscardPile object
Local Variables: none
Algorithm: If instance is null, create new or return the already created instance
Assistance Received: none

*/
DiscardPile *DiscardPile::getInstance() {
    if (instance == NULL){
        instance = new DiscardPile();
    }
    return instance;
}
// C++'s way to set instance as null since constructor is private
DiscardPile* DiscardPile::instance = 0;
/*
Function Name: DiscarPile
Purpose: Constructor for creating singleton instance of discardPile. Private constructor
Parameters: none
Return Value: DiscardPile object
Local Variables: none
Algorithm: none
Assistance Received: none

*/
DiscardPile::DiscardPile() {

}

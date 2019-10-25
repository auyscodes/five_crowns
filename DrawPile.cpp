//
// Created by nbhat on 9/15/2019.
//

#include "DrawPile.h"
/*
Function Name: getInstance
Purpose: Gets the singleton instance of object that represents drawpile
Parameters: none
Return Value: DrawPile object
Local Variables: none
Algorithm: If instance is null, create new or return the already created instance
Assistance Received: none

*/
DrawPile *DrawPile::getInstance() {
    if (instance==NULL) {
        instance = new DrawPile();
    }
    return instance;
}
// C++'s way to set instance as null since constructor is private
DrawPile* DrawPile::instance = 0;
/*
Function Name: DrawPile
Purpose: Constructor for creating singleton instance of drawpile. Private constructor
Parameters: none
Return Value: DrawPile object 
Local Variables: none
Algorithm: none
Assistance Received: none

*/
DrawPile::DrawPile() {

}

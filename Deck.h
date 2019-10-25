//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_DECK_H
#define FIVECROWNS_DECK_H



#include "CardCollection.h"
#include "Card.h"
#include "Joker.h"
#include <vector>

/*
	Representation of Deck.
	Contains builder class that helps in building deck.

	Note: Built this way so that it will be easier if deck class might have
	some specific functions
*/
using namespace std;
class Deck: public CardCollection {
public:
	/*
		Builder class for making a check
	*/
    static class Builder{
    public:
		/*
		Function Name: numericFace
		Purpose: set the numeric faces in deck that begins at 3 and ends at 9
		Parameters: begin, beginning of numeric face, inclusive (3 for this project)
					end, end of numeric face, inclusive (10 for this project)
		Return Value: Builder object, object that builds deck
		Local Variables: none
		Algorithm: none
		Assistance Received: none

		*/
        Builder numericFace(int begin, int end){
               this->begin = begin;
               this->end = end;
               return *this;
        }
		/*
		Function Name: specialFace
		Purpose: set the special faces in deck like Jack, Queen, King, etc.
		Parameters: special_face, collection of special_faces
		Return Value: Builder object, object that builds deck
		Local Variables: none
		Algorithm: none
		Assistance Received: none

		*/
        Builder specialFace(vector<string> special_face){
            this->special_face = special_face;
            return *this;
        }
		/*
		Function Name: suits
		Purpose: set the suits to build a deck
		Parameters: _suits, collection of string representing hearts, diamonds, etc.
		Return Value: Builder object, object that builds deck
		Local Variables: none
		Algorithm: none
		Assistance Received: none

		*/
        Builder suits(vector<string> _suits){
            this->_suits = _suits;
            return *this;
        }
		
		/*
		Function Name: joker
		Purpose: set the number of joker to build a deck
		Parameters: numJokers, number of jokers in a deck
		Return Value: Builder object, object that builds deck
		Local Variables: none
		Algorithm: none
		Assistance Received: none

		*/
        Builder joker(int numJokers){
            this->numJokers = numJokers;
            return *this;
        }
		
		Deck build(); 
            
        

    private:
		// beginning of numeric face e.g 3 for five crowns
        int begin; 
		// end of face numeric face e.g. 10 for five crowns
        int end; 
		// J,Q, K etc. faces
        vector<string> special_face; 
		// H (hearts), D(diamonds), T(tridents) faces
        vector<string> _suits; 
		// number of Jokers
        int numJokers;
    };


};


#endif //FIVECROWNS_DECK_H


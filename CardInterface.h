//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_CARDINTERFACE_H
#define FIVECROWNS_CARDINTERFACE_H
#include <iostream>
#include <string>

using namespace std;
/*
	Represents abstract card class.
*/
class CardInterface{
public:
	/*
		Cards inheriting this class need to define their own toString functions.
	*/
    virtual string toString() = 0;

	/*
		Accessor function
	*/
    string getFace(){
        if (face.empty()){
            throw "card doesn't have any face";
        }
        return this->face;
    }
	/*
		Accessor function
	*/
    string getSuit(){

        if (suit.empty()){
            throw "card doesn't have any suit";
        }
        return this->suit;
    }
	/*
		Mutator function
		@param string representing face of the card
	*/
    void setFace(string face) {
		if (face.empty()) throw "Face cannot be empty";
        this->face = face;
    }
	/*
		Mutator function
		@param string representing suit of the card
	*/
    void setSuit(string suit){
		if (suit.empty()) throw "Suit cannot be empty";
        this->suit = suit;
    }

   /*
		Compares if two cards have the same face or suit
		@param pointer to object representing card
		@return true if two cards are equal
		Side Note: J1=J1 but J1!=J2
   */
    bool operator== (CardInterface* card){
            return this->getFace() == card->getFace() && this->getSuit() == card->getSuit();
    }
    /*
		Compares if the value of one card is greater than the value of the other
		@param pointer to object representing card
		@return true if value of lvalue is less than value of rvalue
		Side Note: J1 is not less than J2
	*/
    bool operator<(CardInterface* card){
        return this->getValue() < card->getValue();
    }

	/*
		Compares if the value of one card is less than the value of the other
		@param pointer to object representing card
		@return true if value of lvalue is greater than value of rvalue
		Side Note: J1 is not greater than J2

	*/
    bool operator>(CardInterface* card){
        return this->getValue() > card->getValue();
    }

	/*
		Returns value of the card
		Note: only applicable for five crowns game.
		It is better if deck class sets the value of each card during initialization
		Recommendation: add value field, set that value field in deck builder and return the value
		@return value of the card
	*/
    int getValue(){
        // Note: only applicable for this game
        // It will be better if deck builder intialized this value

        // if joker return 50
        if (this->suit=="J") return 50;

        // if wildcard return 20
        if (this->isWildCard()) return 20;

        if (this->face == "K"){
            return 13;
        }
        if (this->face == "Q") return 12;
        if (this->face == "J") return 11;
		if (this->face == "X") return 10;
        return stoi(this->face);
    }

    /**
     * Checks whether string value equals to the card.
     * for eg. passing 8D as string should match 8D card
     * @param card card in string format eg. 8D
     * @return true if string matches the card
     */

    bool match(string card){
        if (card.empty()) throw "card empty";
		return this->toString() == card;
		
		// Note: this was last minute edit, should work though
		// return this->getFace() + this->getSuit() == card;
		
        
    }

	/*
		Check if it is a joker or wildcard
		@return true if joker or wildcard otherwise false
	*/

	bool isSpecialCard() {
		if (this->isJoker() == true || this->isWCard==true) {
			return true;
		}
		return false;
	}
	bool isWildCard() {
		return this->isWCard;
	}
	
	void makeWildCard() {
		this->isWCard = true;
	}
	void unmakeWildCard() {
		this->isWCard = false;
	}

	static bool isJoker(string _card) {
		if (_card == "J1" || _card == "J2" || _card == "J3") return true;
		return false;
	}
	bool isJoker() {
		if (this->toString() == "J1" || this->toString() == "J2" || this->toString() == "J3") return true;
		return false;
	}
private:
    string suit;
    string face;
	bool isWCard = false; // if it's a wildcard
	
};



#endif //FIVECROWNS_CARDINTERFACE_H


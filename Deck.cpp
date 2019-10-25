//
// Created by nbhat on 9/9/2019.
//
#include "Deck.h"
/*
Function Name: build
Purpose: builds a deck
Parameters: none
Return Value: Deck object 
Local Variables: none
Algorithm: deck, instace of object representing a deck
Assistance Received: none

*/
Deck Deck::Builder::build()
{
	Deck* deck = new Deck();
	if (_suits.empty() || (special_face.empty() && (begin == NULL || end == NULL))) throw "Deck properly not initialized";
	for (auto _suit : _suits) {
		for (auto i = begin; i <= end; i++) {
			CardInterface* card = new Card();
			card->setFace(to_string(i));
			card->setSuit(_suit);
			deck->addFront(card);
		}
		for (auto sp_face : special_face) {
			CardInterface* card = new Card();
			card->setFace(sp_face);
			card->setSuit(_suit);
			deck->addFront(card);
		}
	}
	for (auto i = 1; i <= numJokers; i++) {
		CardInterface* card = new Joker();
		card->setFace(to_string(i));
		card->setSuit("J");
		deck->addFront(card);
	}
	return *deck;
}

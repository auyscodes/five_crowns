//
// Created by nbhat on 9/23/2019.
//

#ifndef FIVECROWNS_DATALAYER_H
#define FIVECROWNS_DATALAYER_H


#include "CardCollection.h"
#include "DrawPile.h"
#include "DiscardPile.h"
#include "CardPile.h"
#include "Player.h"
#include "Deck.h"


/*
	Stores the context of the game. Information that is persistant throughout the lifecycle of the game and needed by Round class is present here.
	This class is the heart of the game and used by round and serialization class to load and unload data.
*/
class DataLayer {
public:
	/*
	Function Name: DataLayer
	Purpose: Stores the context of the game. Information that is persistant throughout the lifecycle of the game and needed by Round class is present here.
		This class is the heart of the game and used by round and serialization class to load and unload data.

	Parameters: none
	Return Value: Object of the class
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	DataLayer() {
		players = new vector<Player*>();
		humanPlayerIndex = 0;
		computerPlayerIndex = 1;
		nextPlayerIndex = 0;
		round = 1;
	}
	/*
	Function Name: DataLayer
	Purpose: Stores the context of the game. Information that is persistant throughout the lifecycle of the game and needed by Round class is present here.
		This class is the heart of the game and used by round and serialization class to load and unload data.

	Parameters:
			players, Human and computer player's of the game
			nextPlayerIndex, Keeps track of who plays next. Determined at first by toss.
			startRound, From 1 to 11. 1 when starting a new game. Other values when loading a game
			humnaPlayerIndex, Index of the human player in players vector
			computerPlayerIndex, Index of the computer player in players vector

	Return Value: Object of the class
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	DataLayer(vector<Player*>* players, int nextPlayerIndex, int startRound, int humanPlayerIndex, int computerPlayerIndex) {
		this->players = players;
		this->nextPlayerIndex = nextPlayerIndex;
		this->round = startRound;
		this->humanPlayerIndex = humanPlayerIndex;
		this->computerPlayerIndex = computerPlayerIndex;
	}
	/*
	Function Name: getDrawPile
	Purpose: Get the drawPile
	Parameters: none
	Return Value: pointer to draw pile 
	Local Variables: none
	Algorithm: none
	Assistance Received: none

*/
    CardCollection* getDrawPile() const {
        return DrawPile::getInstance();
    }
	/*
	Function Name: getDiscardPile
	Purpose: Get the discardPile
	Parameters: none
	Return Value: pointer to discard Pile
	Local Variables: none
	Algorithm: none
	Assistance Received: none

*/
    CardCollection* getDisCardPile() const{
        return DiscardPile::getInstance();
    }
	/*
	Function Name: getCardPile
	Purpose: Get the drawPile
	Parameters: none
	Return Value: pointer to cardPile
	Local Variables: none
	Algorithm: none
	Assistance Received: none

*/
    CardPile* getCardPile() const{
        return CardPile::getInstance();
    }
	/*
	Function Name: getPlayers
	Purpose: Get the players in the game
	Parameters: none
	Return Value: pointer to collection of players 
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
    vector<Player*>* getPlayers() const{
        return players;
    }
	/*
	Function Name: getNextPlayerIndex
	Purpose: Get the players in the game
	Parameters: none
	Return Value: index in collection of players that plays next
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	int getNextPlayerIndex() {
		return nextPlayerIndex;
	}
	/*
	Function Name: getRound
	Purpose: Gets the current round
	Parameters: none
	Return Value: integer representing round that is being played 
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	int getRound() {
		return this->round;
	}
	/*
	Function Name: getHumanPlayerIndex
	Purpose: Gets the index of human player stored in collection of players
	Parameters: none
	Return Value: index of the computer player in collection
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	int getHumanPlayerIndex() {
		return this->humanPlayerIndex;
	}
	/*
	Function Name: getComputerPlayerIndex
	Purpose: Gets the index of human player stored in collection of players
	Parameters: none
	Return Value: index of the human player in collection
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	int getComputerPlayerIndex() {

		return this->computerPlayerIndex;
	}
	/*
	Function Name: setPlayers
	Purpose: Set collection of players playing the game
	Parameters: none
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
    void setPlayers(vector<Player*> * players){
		if (players->size() < 2) {
			throw "Player's size should be greater than two";
		}
        this->players = players;
    }
	/*
	Function Name: setNextPlayerIndex 
	Purpose: Sets the next player that plays the game. 
	Parameters: index, index of the player in the collection of players
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	void setNextPlayerIndex(int index) {
		if (index < 0) throw "Index cannot be less than 0";
		this->nextPlayerIndex = index;
	}
	/*
	Function Name: setRound
	Purpose: Sets the round to play
	Parameters: round, values between 1 to 11, since there are 11 rounds in the game
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	void setRound(int round) {
		if (round < 1) throw "Round number cannot be less than 1";
		this->round = round;
	}
	/*
	Function Name:  setHumanPlayerIndex
	Purpose: To know where human player is present in the collection of players
	Parameters: index, index of the player in the collection of players
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	void setHumanPlayerIndex(int index) {
		if (index < 0) throw "Index cannot be less than 0";
		this->humanPlayerIndex = index;
	}
	/*
	Function Name:  setComputerPlayerIndex
	Purpose: To know where computer player is present in the collection of players
	Parameters: index, index of the player in the collection of players
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	void setComputerPlayerIndex(int index) {
		if (index < 0) throw "Index cannot be less than 0";
		this->computerPlayerIndex = index;
	}
	/*
	Function Name:  getNextPlayer
	Purpose: Helper for serialization of the game state. Gets string representing next player
	Parameters: none
	Return Value: player who goes next when loading the game
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	string getNextPlayer() {
		if (nextPlayerIndex == humanPlayerIndex) return "Human";
		if (nextPlayerIndex == computerPlayerIndex) return "Computer";
	}
	/*
	Function Name:  isLoad
	Purpose: To know if the current round is loaded or not
	Parameters: none
	Return Value: bool, true if the game was loaded from the serialization file
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	bool isLoad() {
		return this->_isLoad;
	}
	/*
	Function Name:  turnIsLoadOn
	Purpose: To tell that current round is loaded from file
	Parameters: none
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	void turnIsLoadOn() {
		this->_isLoad = true;
	}
	/*
	Function Name:  turnIsLoadOff
	Purpose: To turn of after the round loaded from file finishes
	Parameters: none
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	void turnIsLoadOff() {
		this->_isLoad = false;
	}
	/*
	Function Name:  buildCardCollection
	Purpose: Builds two deck in puts it in a card pile for playing
	Parameters: none
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	void buildCardCollection() {
		Deck deck1 = Deck::Builder().numericFace(3, 9).specialFace({ "J", "Q", "K", "X" }).suits(
			{ "C", "H", "D", "S", "T" }).joker(3).build();
		deck1.shuffle();
		Deck deck2 = Deck::Builder().numericFace(3, 9).specialFace({ "J", "Q", "K", "X" }).suits(
			{ "C", "H", "D", "S", "T" }).joker(3).build();
		deck2.shuffle();
		CardPile* cardCollection = CardPile::getInstance();
		cardCollection->collect(&deck1);
		cardCollection->collect(&deck2);
		cardCollection->shuffle();
	}
	/*
	Function Name:  ~DataLayer
	Purpose: destroys the object. deletes players while doing so
	Parameters: none
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none

	*/
	~DataLayer() {
		delete players;
	}
private:
	// collection of players
    vector<Player*> * players;
	// next player to play in round, updated after each players turn
	int nextPlayerIndex;
	// round number
	int round;
	// index of the human player
	int humanPlayerIndex;
	// index of the computer player
	int computerPlayerIndex;
	// determines whether the game is loaded from file
	bool _isLoad = false;
};


#endif //FIVECROWNS_DATALAYER_H

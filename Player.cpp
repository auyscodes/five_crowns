//
// Created by nbhat on 9/15/2019.
//

#include "Player.h"
#include "DrawPile.h"
#include "DiscardPile.h"

/*
Function Name: Player 
Purpose: Represents a player in Game. 
		Intializes new hand object.
Parameters:	none
Return Value: Player object
Local Variables: none
			
Algorithm: none
Assistance Received: none

*/
Player::Player() {
    hand = new CardCollection();
}

/*
Function Name: setCard
Purpose: Set a card in player's hand.
Parameters:
			card, Represents a card. 
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Player::setCard(CardInterface *card) {
	if (card == NULL) throw "CardInterface cannot be NULL";
    hand->addFront(card);
}
/*
Function Name: getHand
Purpose: To get the current hand of the player
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
CardCollection *Player::getHand() const {
    return hand;
}


/*
Function Name: setName
Purpose: Set name of the player.
Parameters: name, a string containing player's name
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Player::setName(string name) {
	if (name.empty()) throw "name is empty";
    this->name = name;
}
/*
Function Name: getName
Purpose: To get the name of the player.
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
string Player::getName() {
    return this->name;
}
/*
Function Name: setSaveGameCallback
Purpose: To save current game.
Parameters: iSave, Exposes saveGame function so that player can save the current state of the game.
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Player::setSaveGameCallback(Save* iSave)
{
	this->iSave = iSave;
}
/*
Function Name: addToScore
Purpose: Store the score received by player in each round
Parameters: none
Return Value: none
Local Variables: none
Algorithm: Adds to the current score of the player
Assistance Received: none

*/
void Player::addToScore(int score) {
    this->score += score;
}


/*
Function Name: playerGoOut
Purpose: To get notification that one of the player has gone out.
		Note: Not used.
Parameters: hasToGoOut, one of the player has already gone out, so, this
		player knows that they have to go out.
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Player::playerGoOut(bool hasToGoOut) {
	this->haveToGoOut = hasToGoOut;
}

/*
Function Name: showDrawAndDiscardPile
Purpose: Display cards on the drawPile and discardPile
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Player::showDrawAndDiscardPile() {
	cout << endl;
	cout << "showing drawpile : " << endl;
	cout << DrawPile::getInstance()->toString();
	cout << endl;
	cout << "showing discardpile : " << endl;
	cout << DiscardPile::getInstance()->toString();
	cout << endl;
	cout << endl;
}

/*
Function Name: showHand
Purpose: Display cards in the hand of the player
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Player::showHand() {
	cout << " hand : ";
	cout << hand->toString();
	cout << endl;
}

/*
Function Name: getScore
Purpose: Get the total score received by player on each round.
Parameters: none
Return Value: Total score received by player
Local Variables: none
Algorithm: none
Assistance Received: none

*/

int Player::getScore() {
	return this->score;
}
/*
Function Name: 
Purpose: Sets the hand of the player.
Parameters: hand, Represents the collection of cards in player's hand
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Player::setPlayerHand(CardCollection* hand)
{
	if (hand == NULL) throw "Hand cannot be null";
	this->hand = hand;
}
/*
Function Name: setScore
Purpose: Replaces the players' current score with new one.
		Note: Use addToScore for keeping track of players score.
Parameters: score, total score received by player in each round
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Player::setScore(int score)
{
	
	this->score = score;
}
/*
Function Name: ~Player
Purpose: Destructor. Deletes player object
Parameters: none
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
Player::~Player()
{
	delete hand;
	
}

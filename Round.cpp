//
// Created by nbhat on 9/15/2019.
//

#include "Round.h"
#include "DataLayer.h"


/*
Function Name: Round
Purpose: Represent a round in game.
		Constructor.
		Sets number of cards to deal.
		Sets dataLayer object.
		
Parameters:
			dataLayer, pointer to DataLayer class. dataLayer is the model in MVC
			of the game.
Return Value: Object of the class
Local Variables: none
Algorithm: none
Assistance Received: none

*/
Round::Round(DataLayer* dataLayer) {

	this->numCardsToDeal = dataLayer->getRound() + 2;
	this->dataLayer = dataLayer;

}

/*
Function Name: deal
Purpose: Deals the cards to players. Puts cards in draw pile and discard pile.
		Transforms wildcard for the round before dealing
Parameters: none
Return Value: none
Local Variables:
			cardCollection, pointer to object that holds the two decks.
Algorithm: 
			1. Distribute cards to players in a circular fashion
			2. Put the remaining cards in drawPile
			3. Put the top card from the drawPile in discardPile.
Assistance Received: none

*/
void Round::deal() {

	
	CardCollection* cardCollection = dataLayer->getCardPile();
	// this means player started a new game 
	cardCollection->transformCards(convertNumCardsToDealToWildCards(numCardsToDeal));
		
	for (int i=0;i<numCardsToDeal;i++){

		for (auto player: *dataLayer->getPlayers()){
             player->setCard(cardCollection->popFront());
        }
	}
	dataLayer->getDrawPile()->collect(cardCollection);
	dataLayer->getDisCardPile()->addFront(dataLayer->getDrawPile()->popFront());
}


/*
Function Name: collectCardsFromPiles
Purpose: Collect cards from drawPile, discardPile and all the hand of all the players
		and put it back on the cardCollection
		Undoes wildcard transformation for the next round
Parameters: none
Return Value: none
Local Variables:
			cardCollection, pointer to object that holds the two decks.
Algorithm:
			1. Collect card from DrawPile
			2. Collect card from DiscardPile
			3. Collect card from hand of all the players
Assistance Received: none

*/
void Round::collectCardsFromPiles(){

	CardCollection* cardCollection = dataLayer->getCardPile();


    cardCollection->collect(dataLayer->getDrawPile());
    cardCollection->collect(dataLayer->getDisCardPile());


    for (auto player:*dataLayer->getPlayers()){
        cardCollection->collect(player->getHand());
    }
	
    cardCollection->shuffle();
	cardCollection->undoCardsTmation();

}





/*
Function Name: tryGoOut
Purpose: Check if a player can go out with current set of cards in thier hand.
		Notify other players that a player has gone out.
		Keep track of number of players that have successfully gone out.
Parameters: 
			hand, hand of the player
			score, a reference to minimum score the player can receive
					for the hand
			cardsArrgnmnt, a reference to a vector of vector of cards.
				The vector holds the best possible way the 
Return Value: bool, true if a player successfully went out. false otherwise
Local Variables: none
Algorithm:
			Check if go out possible.
			If possible notify other players
Assistance Received: none

*/
bool Round::tryGoOut(CardCollection hand, int& score, vector<vector<CardInterface*>>& cardsArrgnmnt) {
		if (checkGoOutPossible(hand, score, cardsArrgnmnt)) {
			

			this->playersGoneOut++;
			notifyOtherPlayers(this->dataLayer->getPlayers());
			return true;
		}
		return false;
	
}



/*
Function Name: printCardArrangement
Purpose: Prints vector of vector of card in certain format
		 E.g. of the format is [ [ J1 3S 4S ] [ 5D ] ]
Parameters: cardsArrangements, collection of collection of cards
			
Return Value: none
Local Variables: none
Algorithm: 
		1. For each collection of cards, print all the cards
Assistance Received: none

*/
void Round::printCardsArrangement(const vector < vector<CardInterface*>> & cardsArrgnment) {
	cout << " [ ";
	for (auto elem : cardsArrgnment) {
		cout << " [ ";
		for (auto e : elem) {
			cout << e->toString() << " ";
		}
		cout << " ] ";
	}
	cout << " ] ";
}

/*
Function Name: notifyOtherPlayers
Purpose: To notify other players that a player has gone out
		Note: Function not used now. This was created with
		the intention to improve logic.
Parameters: players, constant reference to vector of players

Return Value: none
Local Variables: none
Algorithm:
		none
Assistance Received: none

*/
void Round::notifyOtherPlayers(const vector<Player*>* players) {
	// vector<Player*>& playersRef = *players;
	for (int i = 0; i < players->size(); i++) {
		players->at(i)->playerGoOut(true);

		/*Player* player = playersRef[i];
		player->playerGoOut(true);*/
	}
}

/*
Function Name: forceGoOut
Purpose: Calculate mimimum score and best possible arrangement of cards
		for the hand. Increase count of number of players that have gone
		out for the current round and notify other players.
Parameters: hand, a copy of the hand of the player after they finish playing.
			score, a reference to mimimum score player received
			branch, a reference to best possible arrangement of cards
				for the mimimum score the player receives

Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Round::forceGoOut(CardCollection hand, int&score, vector<vector<CardInterface*>>& branch)
{ 
	hand.minScoreAndBranch(score, branch);
	this->playersGoneOut++;
	notifyOtherPlayers(this->dataLayer->getPlayers());

}


/*
Function Name: convertNumCardsToDealToWildCards
Purpose: To determine face of the wildcard
Parameters: numCardsToDeal, number of cards dealt in the current round

Return Value: face of the wildcard in the form of string
Local Variables: none
Algorithm: none
Assistance Received: none

*/
string Round::convertNumCardsToDealToWildCards(int numCardsToDeal) {
    if (numCardsToDeal <= 9) return to_string(numCardsToDeal);
	if (numCardsToDeal == 10) return "X";
    if (numCardsToDeal == 11) return "J";
    if (numCardsToDeal == 12) return "Q";
    if (numCardsToDeal == 13) return "K";
}

/*
Function Name: checkGoOutPossible
Purpose: Check if a player can go out with the hand passed.
		Lets the calling function know  mimium score that a player
		receives and  best possible arrangement for the score 
		player receives through respective parameters passed as reference
Parameters: hand, a copy of the hand of the player after they finish playing.
			score, a reference to mimimum score player receives
			minBranch, a reference to best possible arrangement of cards
				for the mimimum score the player receives

Return Value: bool, true if cards in hand result in the score of 0
Local Variables: none
Algorithm: none
Assistance Received: none

*/
bool Round::checkGoOutPossible(CardCollection hand, int& score, vector<vector<CardInterface*>>&minBranch) {
	
	
	if (hand.isGoingOutPossible(score, minBranch)) {
		return true; 
	}
    return false;
}

/*
Function Name: startGame
Purpose: Executes a round. A driver function for the round.
Parameters: none
Return Value: none
Local Variables: none
Algorithm: 
		1. If the game was loaded from file then transform all the cards to wildcards.
		2. If the game was not loaded deal cards from files and transform cards.
		3. Print information about the round
		4. Loop while the numberOfPlayers have gone out is less than total 
			number of players.

			Inside the loop: 
				If one of the players has gone out then force all the other 
				players to go out
				If the player wants to go out try if the player can go out. Notify other players for successful going out.
					Otherwise, let the player know that they cannot go out.
		5. Unset player has to go out.
		6. Collect cards from hand of the players, drawpile and discardPile.
		7. Undo wildcard transformations.

Assistance Received: none

*/
void Round::startGame() {

	cout << "-----------------------" << "Round " << dataLayer->getRound() << "-----------------------------" << endl;
	if (!dataLayer->isLoad()) {
		
		deal();
	}
	if (dataLayer->isLoad()) {
		// just transforms cards in hand of players, discard pile and drawpile
		// to wild card
		// can make a function that transforms all the card piles
		dataLayer->getPlayers()->front()->getHand()->transformCards(convertNumCardsToDealToWildCards(numCardsToDeal));
		dataLayer->getPlayers()->front()->getHand()->transformCards(convertNumCardsToDealToWildCards(numCardsToDeal));
		dataLayer->getDisCardPile()->transformCards(convertNumCardsToDealToWildCards(numCardsToDeal));
		dataLayer->getDrawPile()->transformCards(convertNumCardsToDealToWildCards(numCardsToDeal));		
	}
	
	// print information about round
	cout << "DrawPile: " << dataLayer->getDrawPile()->toString() << endl;
	cout << "DiscardPile: " << dataLayer->getDisCardPile()->toString() << endl;

	for (auto player : *dataLayer->getPlayers()) {

		cout << "\n\t\tname : " << player->getName() << endl;
		cout << "\n\t\thand : " << player->getHand()->toString() << endl;
		cout << "\n\t\tscore : " << player->getScore() << endl;

	}



	int nextPlayerIndex = dataLayer->getNextPlayerIndex();
	int totalNumberOfPlayers = dataLayer->getPlayers()->size();


	cout << "totalNumberOfPlayers : " << totalNumberOfPlayers << endl;
	// cout << "playersGoneOut : " << playersGoneOut << endl;

	while (playersGoneOut < totalNumberOfPlayers) {
		Player* nextPlayer = (*dataLayer->getPlayers())[nextPlayerIndex];

		cout << "Next Player : " << nextPlayer->getName() << endl;

		bool goOutFlag = nextPlayer->playGame();

		if (this->playersGoneOut > 0) {
			vector<vector<CardInterface*>> arrgnmnt;
			int score;
			forceGoOut(*nextPlayer->getHand(), score, arrgnmnt);
			nextPlayer->addToScore(score);


			cout << "Player gone out " << endl;
			cout << "Arragement of cards while going out : ";
			printCardsArrangement(arrgnmnt);
			cout << "Score Player received : " << score << endl;



		}

		if (goOutFlag && playersGoneOut == 0) {
			vector<vector<CardInterface*>> arrgnmnt;
			int score;
			bool successful = tryGoOut(*nextPlayer->getHand(), score, arrgnmnt);
			if (successful) {
				nextPlayer->addToScore(score);


				cout << "Player successfully gone out " << endl;
				cout << "Arragement of cards while going out : ";
				this->printCardsArrangement(arrgnmnt);
				cout << "Score Player received : " << score << endl;


			}
			else {

				cout << "!!! Going out was not possible " << endl;
			}
		}

		nextPlayerIndex = (++nextPlayerIndex) % (*dataLayer->getPlayers()).size();
		dataLayer->setNextPlayerIndex(nextPlayerIndex);


		
		// collects cards at the end of every round and puts it in the card collection
		
		
		

	}

	for (auto player : *dataLayer->getPlayers()) {
		player->playerGoOut(false); // cleared at round end
	}
	collectCardsFromPiles();
	dataLayer->turnIsLoadOff();
	cout << "--------------------------------------------------------------------------------" << endl;


}





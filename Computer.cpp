//
// Created by nbhat on 9/15/2019.
//

#include "Computer.h"
#include "DiscardPile.h"
#include "DrawPile.h"

/*
Function Name: playGame
Purpose: Executes computer's strategy to play the game. Round calls this function for computer to play the game.
Parameters:	none
Return Value: bool, true if the computer wants to go out
Local Variables: currHand, copies and stores the hand computer has before picking or throwing
				currArrangement, stores the best possible arrangement of the cards to get the mimimum score present in computer's hand
				newArrangement, stores the best possible arrangement of the cards replacing a card picked from the discard pile results in mimimum score
					later this variables stores the same thing for card picked from the drawpile
Algorithm: 1. If mimimum score in current hand is 0, then go out
			2. See if replacing a card in current hand with card from the discard pile can make book or run and lower the minimum score,
				if yes then replace the card in current hand with the card from top of the discard pile
				otherwise pick card from drapile
			3. See if the replacing a card in current hand with card picked from the drawpile results in 
			getting a minimum score by making run or a book. if yes than replace the card in the hand with
			the card picked from the drawpile. otherwise throw the card picked from the discard pile.
Assistance Received: none

*/
bool Computer::playGame() {

	cout << "---------Computer Playing----------------" << endl;
	cout << "I am a " << this->name << endl;
	showDrawAndDiscardPile();
	showHand();
	CardCollection currHand = *(this->hand);
	int currScore;
	vector<vector<CardInterface*>> currArrgnmnt;
	currHand.minScoreAndBranch(currScore, currArrgnmnt);
	if (currScore == 0) {
		return true;
	}

	int newScore;
	vector<vector<CardInterface*>> newArrgnmnt;
	//CardInterface* disCard = DiscardPile::getInstance()->getFront(); // gets card from discardPile doesn't change the discard pile card
	int cardIndex = getIndxToRmvCardAtHlpr(DiscardPile::getInstance()->getFront(), newScore, newArrgnmnt, currScore, currHand);


	if (cardIndex != -1) {

		hand->addCardAt(cardIndex, DiscardPile::getInstance()->popFront()); // removes the discard pile card permanently and adds it to players hand

		DiscardPile::getInstance()->addFront(hand->popCardAt(cardIndex + 1)); // // removes card permanently from hand and adds it to the discard pile
		// notice that cardIndex above increases by 1

		cout << "The computer chose to pick up from the discard pile because replacing a card with " << hand->getCardAt(cardIndex)->toString() << " card " << " helped make ";
		printCardsArrgmnt(newArrgnmnt);
		cout << endl;

		cout << "It discarded " << DiscardPile::getInstance()->getFront()->toString() << " card because replacing it with " << hand->getCardAt(cardIndex)->toString() << " card reduced the minimum score from "
			<< currScore << " to " << newScore << endl;

		if (newScore == 0) return true; // goes out if score is equals to 0

	}
	else {

		cout << "The computer chose to pick from drawpile because the card present in discard pile did not reduce the minimum score " << endl;

		CardInterface* drawCard = DrawPile::getInstance()->popFront(); // removes the card from drawpile permanently
		int index = getIndxToRmvCardAtHlpr(drawCard, newScore, newArrgnmnt, currScore, currHand);




		if (index == -1) {
			DiscardPile::getInstance()->addFront(drawCard);

			cout << "The computer chose to throw the card picked up from drawpile because the card did not reduce the minimum score " << endl;

			
			return false;
		}
		else {
			

			// condition so that computer doesn't throw joker or wildcard 
			/*if (!hand->getCardAt(index)->isSpecialCard()) {*/
				hand->addCardAt(index, drawCard); // adds card permanently to hand
				DiscardPile::getInstance()->addFront(hand->popCardAt(index + 1)); // removes card permanently from hand

				cout << "Replacing a card in computer's hand with " << hand->getCardAt(index)->toString() << " card " << " helped make ";
				printCardsArrgmnt(newArrgnmnt);
				cout << endl;
				cout << " It discarded " << DiscardPile::getInstance()->getFront()->toString() << " card because replacing it with " << hand->getCardAt(index)->toString() << " card reduced the minimum score from "
					<< currScore << " to " << newScore << endl;
				if (newScore == 0) return true;
			/*}*/
			/*else
			{
				DiscardPile::getInstance()->addFront(drawCard);
				cout << "The computer chose to throw card picked from discard pile because it decided to keep special card " << endl;

				return false;
			}*/


		}
	}
	return false;
}

/*
Function Name: getIndxToRmvCardAtHlpr
Purpose: To check if replacing a card in hand with another card would result in minimum score
Parameters:	card, pointer to object representing card
			newScore, score that the player would receive if replacing a card in their hand with 
			another card would result in mimimum score by making books and runs
			newArrgnmnt, best possible arrangement of the cards in hand so that it results in minimum score
			currScore, minimum score of the player in the current hand
			currHand, hand of the player at present
Return Value: index of the card to remove from hand otherwise -1
Local Variables: handCard, card at some index in players hand

Algorithm: 1. Replace each card at a time in player's hand with passed card and see if it lowers the 
			minimum score 
			2. If it lowers the minimum score, return the index the of the card in hand at which
			replacing lowers the minimum score, otherwise return -1
			
Assistance Received: none

*/
int Computer::getIndxToRmvCardAtHlpr( CardInterface* card, int& newScore, vector<vector<CardInterface*>>& newArrgnmnt, const int& currScore, CardCollection currHand) {
	

	
	
	
	newScore = currScore;
	int cardIndex = -1;
	for (int i = 0; i < currHand.getSize(); i++) {
		vector<vector<CardInterface*>> arrgnmnt;
		int score;
		CardInterface* handCard = currHand.popCardAt(i); // removes card permanently and returns it
		
		currHand.addCardAt(i, card);
		currHand.minScoreAndBranch(score, arrgnmnt);
		
		if (score < newScore) {
			newScore = score;
			newArrgnmnt = arrgnmnt;
			cardIndex = i;
		}
		currHand.popCardAt(i);
		currHand.addCardAt(i, handCard);

	}
	return cardIndex;
}

/*
Function Name: canGoOutWithoutPicking
Purpose: Check to see if the user can go without picking any card
Parameters:	card, pointer to object representing card
			score, score that the player would receive if replacing a card in their hand with
			another card would result in mimimum score by making books and runs
Return Value: index of the card to remove from hand otherwise -1
Local Variables: handCard, card at some index in players hand

Algorithm: 1. Replace each card at a time in player's hand with passed card and see if it lowers the
			minimum score
			2. If it lowers the minimum score, return the index the of the card in hand at which
			replacing lowers the minimum score, otherwise return -1

Assistance Received: none

*/
bool Computer::canGoOutWithoutPicking(CardCollection _hand, int&score, vector<vector<CardInterface*>>& arrgnmnt) {
	CardCollection& currHand = _hand;
	int currScore;
	vector<vector<CardInterface*>> currArrgnmnt;
	currHand.minScoreAndBranch(currScore, currArrgnmnt);
	score = currScore;
	arrgnmnt = currArrgnmnt;
	if (currScore == 0) {
		return true;
	}
	return false;
}


/*
Function Name: pickCardFromDiscardPile
Purpose: To check if replacing a card in hand with another card would result in minimum score
Parameters:	
			newScore, score that the player would receive if replacing a card in their hand with
			card from the discardpile would result in mimimum score by making books and runs
			newArrgnmnt, best possible arrangement of the cards if card picked from discard would result in minimum score
			hand_score, minimum score of the player in the current hand
			hand, hand of the player at present
Return Value: index of the card to remove from hand otherwise -1
Local Variables: handCard, card at some index in players hand

Algorithm: Determine if replacing a card from discard pile results in minimum score by calling a function
			If yes than update the respective reference variables and return true
			otherwise return false

Assistance Received: none

*/
bool Computer::pickCardFromDiscardPile(CardCollection hand, int hand_score , int& index, vector<vector<CardInterface*>>& arrgnmnt, int&score) {
	index = -1;
	int newScore;
	vector<vector<CardInterface*>> newArrgnmnt;
	//CardInterface* disCard = DiscardPile::getInstance()->getFront(); // gets card from discardPile doesn't change the discard pile card
	int cardIndex = getIndxToRmvCardAtHlpr(DiscardPile::getInstance()->getFront(), newScore, newArrgnmnt, hand_score, hand);
	if (cardIndex >= 0) {
		index = cardIndex;
		arrgnmnt = newArrgnmnt;
		score = newScore;
		return true;
	}
	return false;
}

/*
Function Name: helpPick
Purpose: Helps the user to pick from drawPile, discardPile or go out without picking
Parameters:
			hand, hand of the player at present
Return Value: none
Local Variables: currScore, minimum score of the player in current hand
				currArrangement, best of arragement of card in current hand that results in minimum score
				arrgnmnt, best possible arragnement of cards that results when the card from the discard pile
				replaces a card in the current hand


Algorithm: 1. If going out without replacing a card is possible than recommend to go out
			2. If replacing a card from the discard pile results in minimum score then recommend to replace the card
			3. Otherwise recommend to pick card from the drawpile

Assistance Received: none

*/
void Computer::helpPick(CardCollection _hand) { 
		int currScore; 
		vector<vector<CardInterface*>> currArrgnmnt;
		bool goOutWithoutPicking = canGoOutWithoutPicking(_hand, currScore, currArrgnmnt);
		if (goOutWithoutPicking) {
			cout << "I recommend you to go out without picking any card" << endl;
			cout << "Current score is : " << currScore << endl;;
			cout << "Current arrangement of cards is : ";
			printCardsArrgmnt(currArrgnmnt);
			cout << endl;
			return;
		}
		int index;
		vector<vector<CardInterface*>> arrgnmnt;
		int score;
		bool keepDisCard = pickCardFromDiscardPile(_hand, currScore, index, arrgnmnt, score);
		if (keepDisCard) {
			cout << "I recommed you to pick card from discard pile " << endl;
			cout << "I recommend you to pick up from the discard pile because replacing a card with " << DiscardPile::getInstance()->getFront()->toString() << " card " << " helps make ";
			printCardsArrgmnt(arrgnmnt);
			cout << endl;

			cout << "Replacing " << _hand.getCardAt(index)->toString() << " with " << DiscardPile::getInstance()->getFront()->toString() << " card reduced the minimum score from "
				<< currScore << " to " << score << endl;
			return;
		}
		cout << "I recommend you to pick card from drawPile " << endl;
		cout << "Picking the card in discard pile doesn't reduce your minimu score " << endl;
		return;
		

		
	
}
/*
Function Name: helpThrow
Purpose: Help the user throw after they pick a card
Parameters:
			card, the card that user picked 
			_hand, hand of the player before picking the card
Return Value: none
Local Variables: currScore, minimum score of the player in current hand
				currArrangement, best of arragement of card in current hand that results in minimum score
				arrgnmnt, best possible arragnement of cards that results when the card from the discard pile
				replaces a card in the current hand
				newScore, score that the player would receive if replacing a card in their hand with
				card from the picked would result in mimimum score by making books and runs
				newArrgnmnt, best possible arrangement of the cards if the picked card  would result in minimum score
Algorithm: 1. Check if the hand before picking any card results in a score of 0
			2. If yes then recommend to go out
			3. Otherwise check to see if replacing picked card would result in minimum score
			4. If yes, then recommend to throw the card from the hand
			5. Otherwise throw the picked card
Assistance Received: none

*/
void Computer::helpThrow(CardCollection _hand, CardInterface* card) {
	
	// all this to curr score
	int currScore; // needed for deciding to pick from discard pile
	vector<vector<CardInterface*>> currArrgnmnt;
	_hand.minScoreAndBranch(currScore, currArrgnmnt);

	cout << "Current hand score " << currScore << endl;
	cout << "Current hand arrgnment "; 
	printCardsArrgmnt(currArrgnmnt);

	if (currScore == 0) {
		cout << "I recommend you to throw " << card->toString() << " card because all the cards in your hand can be arragned to ";
		printCardsArrgmnt(currArrgnmnt);
		cout << " to get minimum score of " << currScore;
		return;
	}
	// end of all this

	int new_score;
	vector<vector<CardInterface*>> newArrgnmnt;
	int index = getIndxToRmvCardAtHlpr(card, new_score, newArrgnmnt, currScore, _hand);
	cout << "new_score " << endl;
	cout << "new arrangement ";
	printCardsArrgmnt(newArrgnmnt);

	if (index == -1) {
		cout << "I recommend you to throw card " << card->toString() << " because replacing any other card with the card will increase minimum score " << endl;
		return;
	}
	cout << "index : " << index << endl;
	cout << "I recommed you to throw " << _hand.getCardAt(index)->toString() << " card because replacing that card with " << card->toString()
		<< " card reduces minimum score from " << currScore << " to " << new_score << endl;

	cout << "Your new cards arrangement will be ";
	printCardsArrgmnt(newArrgnmnt);
	cout << endl;
	cout << "Your old cards arrangement was ";
	printCardsArrgmnt(currArrgnmnt);
	cout << endl;

}
/*
Function Name: pickCardsArrgmnt
Purpose: Help to print collection of collection of cards in certain format
Parameters: cardsArgmnt, collection of collection of cards received after the algorithm arranges the cards
			to get minimum score
Return Value: none
Local Variables: none
Algorithm: none
Assistance Received: none

*/
void Computer::printCardsArrgmnt(const vector<vector<CardInterface*>>& cardsArgmnt)
{
	cout << " [ ";
	for (auto argmnt : cardsArgmnt) {
		cout << " [ ";
		for (auto elem : argmnt) {
			cout << elem->toString() << " ";
		}
		cout << " ] ";
	}
	cout << " ] ";
}
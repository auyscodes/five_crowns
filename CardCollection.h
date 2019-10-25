//
// Created by nbhat on 9/9/2019.
//

#ifndef FIVECROWNS_CARDCOLLECTION_H
#define FIVECROWNS_CARDCOLLECTION_H


#include <random>
#include <vector>
#include "CardInterface.h"
#include <algorithm>
#include <iostream>

#include <map>

// Note: This class is not fully commented out yet.
class CardCollection{

public:
	/*
	Function Name: addFront
	Purpose: Adds the card to the front of the collection
	Parameters: card, pointer to abstract class representing a card
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    void addFront(CardInterface* card){
        this->collection.insert(collection.begin(), card);
    }
	/*
	Function Name: addBack
	Purpose: Adds the card to the back of the collection
	Parameters: card, pointer to abstract class representing a card
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    void addBack(CardInterface* card) {
        this->collection.insert(collection.end(), card);
    }
	/*
	Function Name: getFront
	Purpose: gets the card from the front of the collection
	Parameters: none
	Return Value: card, pointer to abstract class representing a card
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    CardInterface* getFront(){
        return *collection.begin();
    }
	/*
	Function Name: getBack
	Purpose: gets the card from the back of the collection
	Parameters: none
	Return Value: card, pointer to abstract class representing a card
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    CardInterface* getBack(){
        return *(collection.begin() + collection.size());
    }
	/*
	Function Name: popFront
	Purpose: gets the card from the front of the collection and removes it
	Parameters: none
	Return Value: card, pointer to abstract class representing a card
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    CardInterface* popFront(){
        CardInterface* card = *(collection.begin());
        collection.erase(collection.begin());
        return card;
    }
	/*
	Function Name: getBack
	Purpose: gets the card from the back of the collection and removes it
	Parameters: none
	Return Value: card, pointer to abstract class representing a card
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    CardInterface * popBack(){
        CardInterface * card = *(collection.begin() + collection.size());
        collection.erase(collection.begin()+ collection.size());
        return card;
    }
	/*
	Function Name: isEmpty
	Purpose: checks if the collection is empty
	Parameters: none
	Return Value: bool, true if the collection is empty otherwise false
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    bool isEmpty(){
        return collection.empty() || false;
    }
	/*
	Function Name: getSize
	Purpose: gets the size of the collection
	Parameters: none
	Return Value: size of the collection
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    int getSize(){
        return collection.size();
    }
	/*
	Function Name: getCardAt
	Purpose: gets card at certain position in the collection
	Parameters: position, index of the card in the collection
	Return Value: card, pointer to abstract class representing a card
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    CardInterface*  getCardAt(int position){
        return collection[position];
    }

	/*
	Function Name: popCardAt
	Purpose: gets card at certain position in the collection and permanently removes it
	Parameters: position, index of the card in the collection
	Return Value: card, pointer to abstract class representing a card
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    CardInterface* popCardAt(int position){
        CardInterface* card = *(collection.begin() + position);
        collection.erase(collection.begin() + position);
        return card;
    }
	/*
	Function Name: addCardAt
	Purpose: adds card at certain index in the collection
	Parameters: position, index where the card is inserted in the collection
				card, pointer to abstract class representing a card
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
	void addCardAt(int position, CardInterface* card) {
		collection.insert(collection.begin() + position, card);
	}
	/*
	Function Name: shuffle
	Purpose: shuffle the cards in the collection
	Parameters: none
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    void shuffle(){
        std::shuffle(collection.begin(), collection.end(), std::mt19937(std::random_device()()));
    }

	/*
	Function Name: collect
	Purpose: collect all the cars in another collection
	Parameters: cardCollection, pointer to object that represents collection of cards 
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/

    void collect(CardCollection* cardCollection){
        int size = cardCollection->getSize(); // !!! important to put cardcollection size in a variable otherwise will get error
        for (int i=0;i<size;i++){
            collection.push_back(cardCollection->popFront());
        }
    }

	/*
	Function Name: transformCards
	Purpose: Converts cards with certain face to wildcard in the collection
	Parameters: face, face of the cards that needs to be converted to wildcard
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    void transformCards(string face){
        // since Joker is of suit J and has 1 2 3 . Conflicts with regular 3 card. So have to check. Could make Joker start at 0 1 and 2 for ease
        for (auto card: this->collection){
			if (card->getFace() == face && card->getSuit() != "J") card->makeWildCard();
        }
    }
	/*
	Function Name: undoCardsTmation
	Purpose: Undoes transformation of any cards converted to wildcard in the collection
	Parameters: face, face of the cards that needs to be converted to wildcard
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
	void undoCardsTmation() {
		for (auto card : this->collection) {
			if (card->isWildCard()) card->unmakeWildCard();
		}
	}
	/*
	Function Name: separateNormalFromSpecialCards
	Purpose: Separating normal and special cards. Special cards are jokers and wildcards.
			All the other cards are normal cards.
	Parameters: none
	Return Value: separated collections of normal and special cards in a collection
	Local Variables: normalCards, collection of cards that stores normal cards( cards which are not special cards)
					specialCards, collection of cards that stores special cards (jokers and wildcards)
	Algorithm: none
	Assistance Received: none
	*/
    vector<CardCollection*> separateNormalCardsFromOthers(){
        CardCollection* normalCards = new CardCollection();
        CardCollection* specialCards = new CardCollection();
        for (CardInterface* card : collection){
            if (card->getSuit()=="J" || card->isWildCard()){
                specialCards->addFront(card);
                continue;
            }
            normalCards->addFront(card);

        }
        return {normalCards, specialCards};
    }

	/*
	Function Name: toString
	Purpose: Converts the cards collection to string
	Parameters: none
	Return Value: string representation of collection of cards
	Local Variables: none
	Algorithm: append the result of calling toString on each card to output of the function
	Assistance Received: none
	*/
	
    string toString(){
        string output;
		
		for (int i = 0; i < collection.size(); i++) {
			output += collection[i]->toString() + " ";
		}
        
        
        return output;
    }
	/*
	Function Name: sameSuit
	Purpose: checks if all the cards in collection belong to same suit
	Parameters: none
	Return Value: true if all the card in collection belong to same suit
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    bool sameSuit(){
		if (collection.empty()) {
			cerr << "collection empty" << endl;
			throw "Empty collection";
		}
        string suitOfFirstCard = collection.front()->getSuit(); //this was throwing vector iterator out of range error
        for (int i=1;i<collection.size();i++){
            if (collection[i]->getSuit() != suitOfFirstCard) return false;
        }
        return true;
    }
	/*
	Function Name:	sortCardByValue
	Purpose: sorts each card by their respective value.
			Order after sorting is 3-9, X, J, Q, K, wildcard, joker
	Parameters: none
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    void sortCardsByValue(){
        std::sort(collection.begin(), collection.end(), compareCardsByValue);
    }

	/*
	Function Name:	compareCardsByValue
	Purpose: functor passes to the sort function
	Parameters:  card1, pointer to abstract class representing a card
				 card2, pointer to abstract class representing a card
	Return Value: true if card1 is less than card 2
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    static bool compareCardsByValue(CardInterface* card1, CardInterface* card2){
        return card1->getValue() < card2->getValue();
    }
	/*
	Function Name:	setCollectionVector
	Purpose: set the collection of cards
	Parameters:  col, collection of cards 
	Return Value: none
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    void setCollectionVector(vector<CardInterface*> col){
        this->collection  = col;
    }

	/*
	Function Name:	checkBook
	Purpose: check if a collection of cards is the book
			Note: Jokers and wildcards are considered while checking book
			collection of books return false
			i.e. true for [ 4H 4J 4D ] but not for [ 4H 4J 4D 5H 5J 5D ]
			also, true for [ 5H 5J J1 ]
	Parameters:  col, collection of cards
	Return Value: true if the collection of cards are book
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    bool checkBook(vector<CardInterface*> cards){
        CardCollection hand;
        hand.setCollectionVector(cards);
        return checkBook(hand);
    }
	/*
	Function Name:	checkRun
	Purpose: check if a collection of cards is the run
			Note: Jokers and wildcards are considered while checking book
			collection of runs return false
			i.e. true for [ 4H 5H 6H ] but not for [ 4H 5H 6H 4D 5D 6D ]
			also, true for [ 4H 5H J1 ]
	Parameters:  col, collection of cards
	Return Value: true if the collection of cards are run
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    bool checkRun(vector<CardInterface*> cards){
        CardCollection hand;
        hand.setCollectionVector(cards);
        return checkRun(hand);
    }
	/*
	Function Name:	removeCards
	Purpose: remove card present in one hand if also present in another hand
	Parameters:  col, collection of vectors
	Return Value: true if the collection of cards are run
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
	vector<CardInterface*> removeCards(vector<CardInterface*>& hand, vector<CardInterface*> curr) {
		vector<CardInterface*> output;
		bool currContains = false;
		
		for (int i = hand.size()-1; i >= 0; i--) {
			CardInterface* handCard = hand[i];

			for (int j = curr.size()-1; j >=0 ; j--) {
				if (handCard == curr[j]) currContains = true;
			}
			if (currContains) {
				output.push_back(handCard);
				hand.erase(hand.begin() + i);
				
				currContains = false;
			}


		}
		return output;
	}
	

    void addCards(vector<CardInterface*>&hand, vector<CardInterface*> curr){
        hand.insert(hand.end(), curr.begin(), curr.end());
        sort(hand.begin(), hand.end(), compareCardsByValue);
    }

	
	// returns true if going out is possible
	bool isGoingOutPossible(int& score, vector<vector<CardInterface*>>& arrangedCards) {
		
		vector<CardInterface*> hand = this->collection;
		// don't remove sort here
		sort(hand.begin(), hand.end(), compareCardsByValue);


		vector<vector<CardInterface*>> branch;
		vector<vector<CardInterface*>> minBranch;
		 int minScore = INT_MAX;
		genBestHelper(hand, branch, minBranch, minScore);
		 if (minScore == 0) {
		
			score = minScore;
			arrangedCards = minBranch;
			return true;
		}
		return false;
	}

	void minScoreAndBranch(int& minScore, vector<vector<CardInterface*>>& minBranch) {
		vector<CardInterface*> hand = this->collection;
		sort(hand.begin(), hand.end(), compareCardsByValue);
		minScore = INT_MAX;
		minBranch.clear();
		vector<vector<CardInterface*>> branch;
		genBestHelper(hand, branch, minBranch, minScore);
	}

	vector<vector<CardInterface*>> getBestPossibleBooksAndRuns() {

		vector<vector<CardInterface*>> listOfBooksAndRuns;
		vector<CardInterface*> hand = this->collection;
		// don't remove sort here
		sort(hand.begin(), hand.end(), compareCardsByValue);


		vector<vector<CardInterface*>> branch;
		vector<vector<CardInterface*>> minBranch;
		int minScore = INT_MAX;
		
		genBestHelper(hand, branch, minBranch, minScore);
		
		cout << "::::::::::::::::::::minScore : " << minScore << endl;
		return minBranch;


	}

	

	void genBestHelper(vector<CardInterface*>& hand, vector<vector<CardInterface*>>& branch, vector<vector<CardInterface*>>& minBranch, int& minScore) {
		
		vector<vector<CardInterface*>>  listOfBooksAndRuns = genBooksAndRuns(hand);
		
		if (listOfBooksAndRuns.empty()) { 
			int score = countScore(hand);
			if (score <= minScore) {
				minScore = score;
				minBranch = branch;
				if (!hand.empty()) {
					minBranch.push_back(hand);

					
				}
				

			}
			
		}
		else {
			for (unsigned int i = 0; i < listOfBooksAndRuns.size(); i++) {

				vector<CardInterface*> curr = listOfBooksAndRuns[i];
				vector<CardInterface*> removedCards = removeCards(hand, curr);
				if (!removedCards.empty()) {
					branch.push_back(removedCards);
				}
				

				genBestHelper(hand, branch, minBranch, minScore);
				
				
				if (!removedCards.empty()) {
					branch.pop_back();
				}
				
				
				addCards(hand, removedCards);

			}
		}
	}
	int countScore(vector<CardInterface*> hand) {
		int sum = 0;
		for (auto card : hand) {
			sum += card->getValue();
		}
		return sum;
	}





	vector<vector<CardInterface*>> genBooksAndRuns(vector<CardInterface*> cardsCol) {
		vector<vector<CardInterface*>> output;
		if (cardsCol.size() < 3) return output;

		vector<vector<CardInterface*>> books = genBooks(cardsCol);
		vector<vector<CardInterface*>> run = genRuns(cardsCol);
		
		
		output.insert(output.begin(), books.begin(), books.end());
		output.insert(output.begin(), run.begin(), run.end());
		return output;
    	
		
	}

	vector<vector<CardInterface*>> genBooks(vector<CardInterface*> cardsCol)
    {
		vector<vector<CardInterface*>> separateCards = separateNormalAndSpecialCards(cardsCol);
		vector<CardInterface*>& normalCards = separateCards[0];
		vector<CardInterface*>& specialCards = separateCards[1];

		vector<vector<CardInterface*>> dividedCards = divideCards(normalCards);
		/*for (int i=0;i<dividedCards.size();i++)
		{
			vector<CardInterface*>& elem = dividedCards[i];
			for (auto specialCard : specialCards) {
				elem.push_back(specialCard);
			}
		}*/
		vector<vector<CardInterface*>> dividedCardsWSpCards = addSpecialCards(dividedCards, specialCards);

		vector<vector<CardInterface*>> output;
		for (auto elem : dividedCardsWSpCards) {
			if (checkBook(elem)) output.push_back(elem);
		}
		return output;
    	
    	
    }

	
	
	vector<vector<CardInterface*>> genRuns(vector<CardInterface*> cardsCol)
    {
    	
		
		
		vector<vector<CardInterface*>> separateCards = separateNormalAndSpecialCards(cardsCol);
		vector<CardInterface*> normalCards = separateCards[0];
		vector<CardInterface*> specialCards = separateCards[1];

		vector<vector<CardInterface*>> divideSuits = separateSuits(normalCards);

		vector<vector<CardInterface*>> output;

		for (auto suitOfCards : divideSuits) {
			vector < vector<CardInterface*>> dividedSuitOfCards = divideCards(suitOfCards);
			vector<vector<CardInterface*>> dividedSuitsWithSpCards = addSpecialCards(dividedSuitOfCards, specialCards);
			for (auto elem : dividedSuitsWithSpCards) {
				if (checkRun(elem)) {
					output.push_back(elem);
				}
			}
		}

		return output;
    }

	


	// Not your simple addition
	// to make so that keeps cards without special cards as well
	vector<vector<CardInterface*>> addSpecialCards(vector<vector<CardInterface*>> cardsCol , vector<CardInterface*> specialCards) {

		
		vector<vector<CardInterface*>> spCardsList;
		for (int i = 0; i < specialCards.size(); i++) {
			vector<CardInterface*> spCards;
			for (int j = 0; j <=i; j++) {
				spCards.push_back(specialCards[j]);
			}
			spCardsList.push_back(spCards);
		}
		
		vector<vector<CardInterface*>> output;
		for (int i = 0; i < cardsCol.size(); i++) {
			
			for (int j = 0; j < spCardsList.size(); j++) {
				vector<CardInterface*> elem = cardsCol[i];
				vector<CardInterface*> spCards = spCardsList[j];
				elem.insert(elem.end(), spCards.begin(), spCards.end());
				if (elem.size() >= 3) {
					output.push_back(elem);
				}
			}
			// also need to add cardsCol where elem size is greater than 3
			if (cardsCol[i].size() >= 3) output.push_back(cardsCol[i]);

		}
		
		return output;
	}

	// cards passed here should not be special cards
	vector<vector<CardInterface*>> separateSuits(vector<CardInterface*> cardsCol)
    {
		
		
		vector<CardInterface*> hearts;
		vector<CardInterface*> diamonds;
		vector<CardInterface*> clubs;
		vector<CardInterface*> tridents;
		vector<CardInterface*> spades;

    	for (auto card: cardsCol)
    	{
			if (card->getSuit() == "H") hearts.push_back(card);
			if (card->getSuit() == "T") tridents.push_back(card);
			if (card->getSuit() == "C") clubs.push_back(card);
			if (card->getSuit() == "S") spades.push_back(card);
			if (card->getSuit() == "D") diamonds.push_back(card);
    		
    	}
		
		
		return { hearts, diamonds, clubs, spades, tridents };
    }


	// duplicate function
	
	vector<vector<CardInterface*>> separateNormalAndSpecialCards(vector<CardInterface*> cardsCol)
    {
		
		
		vector<CardInterface*> normalCards;
		vector<CardInterface*> specialCards;
		for (unsigned int i = 0; i < cardsCol.size(); i++) {
			CardInterface* card = cardsCol[i];
			if (card->getSuit() == "J" || card->isWildCard()) {
				specialCards.push_back(card);
				continue;
			}
			normalCards.push_back(card);

		}
		
		return { normalCards, specialCards };
    }


	vector<vector<CardInterface*>> divideCards(vector<CardInterface*> cardsCol) {
		sort(cardsCol.begin(), cardsCol.end(), compareCardsByValue);
		
		vector<vector<CardInterface*>> output;

    	// for now
		if (cardsCol.empty()) return output;
    	
		for (int i = 0; i < cardsCol.size(); i++)
		{
			for (int j = i; j < cardsCol.size(); j++)
			{
				vector<CardInterface*> result;
				// change this for loop later to more nicer code to copy
				for (int k = i; k <= j; k++)
				{
					result.push_back(cardsCol[k]);
				}
				output.push_back(result);
			}
		}
		
		return output;
	}

	
   
    // Note: this doesn't modify the passed hand
    static vector<CardCollection> separateCards(CardCollection collection1){
        CardCollection normalCards;
        CardCollection specialCards;
        for (unsigned int i=0;i<collection1.getSize();i++){
            CardInterface* card = collection1.getCardAt(i);
//        for (CardInterface* card : collection1){
            if (card->getSuit()=="J" || card->isWildCard()){
                specialCards.addFront(card);
                continue;
            }
            normalCards.addFront(card);

        }
        return {normalCards, specialCards};
    }

	/*
	Function Name:	checkRun
	Purpose: check if a collection of cards is the run
			Note: Jokers and wildcards are considered while checking book
			collection of runs return false
			i.e. true for [ 4H 5H 6H ] but not for [ 4H 5H 6H 4D 5D 6D ]
			also, true for [ 4H 5H J1 ]
	Parameters:  col, collection of vectors
	Return Value: true if the collection of cards are run
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    static bool checkRun(CardCollection hand){
		
        if (hand.getSize()<3) return false;
		
        vector<CardCollection> normalAndSpecialCardsOfHands = separateCards(hand);

        CardCollection normalCards = normalAndSpecialCardsOfHands[0];
        CardCollection specialCards = normalAndSpecialCardsOfHands[1];

		
        if (normalCards.isEmpty()) return true;

        CardCollection checkedSpecialCards;

        normalCards.sortCardsByValue();

        if (normalCards.sameSuit()){
            int size = normalCards.getSize();
            CardInterface* prevCard = normalCards.getFront();
            CardInterface* currCard;
            int count = 1;
            while(count< size){
                currCard = normalCards.getCardAt(count);
                if (prevCard->getValue() != currCard->getValue() - 1){
                    if (specialCards.isEmpty()) return false;
                    if (prevCard->getValue() != currCard->getValue()-2) {
                        return false;
                    }
                    else{
                        checkedSpecialCards.addFront(specialCards.popFront());
                    }

                }
                prevCard = currCard;
                count++;
            }
            return true;
        }
        return false;
    }
	/*
	Function Name:	checkBook
	Purpose: check if a collection of cards is the book
			Note: Jokers and wildcards are considered while checking book
			collection of books return false
			i.e. true for [ 4H 4J 4D ] but not for [ 4H 4J 4D 5H 5J 5D ]
			also, true for [ 5H 5J J1 ]
	Parameters:  col, collection of vectors
	Return Value: true if the collection of cards are book
	Local Variables: none
	Algorithm: none
	Assistance Received: none
	*/
    static bool checkBook(CardCollection  hand){

        if (hand.getSize()<3) return false;

        vector<CardCollection> normalAndSpecialCards = separateCards(hand);
        CardCollection normalCards = normalAndSpecialCards[0];
        CardCollection specialCards = normalAndSpecialCards[1];

        if (normalCards.isEmpty()) return true;

        // no need to sort cards by value
        int size = normalCards.getSize();
        int count = 1;
        CardInterface* prevCard = normalCards.getFront();
        CardInterface* currCard;

        while(count<size){
            currCard = normalCards.getCardAt(count);
            if (prevCard->getValue() != currCard->getValue()){
                return false;
            }
            prevCard = currCard;
            count++;
        }


        return true;
    }
	void printWildCards() {
		for (auto card : collection) {
			cout << card->toString() << endl;
		}
	}

   
private:
    vector <CardInterface* > collection;

};


#endif //FIVECROWNS_CARDCOLLECTION_H

